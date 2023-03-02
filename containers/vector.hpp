#ifndef _VECTOR_HPP_
#define _VECTOR_HPP_

#include <iostream>
#include <memory>		// add allocator<T>
#include <cstddef> 	// add ptrdiff_t
#include "../inc/reverse_iterator.hpp"
#include "../inc/bidirectional_iterator.hpp"
#include "../inc/random_access_iterator.hpp"
#include "../inc/enable_if.hpp"
#include "../inc/distance.hpp"
#include "../inc/lex_compare.hpp"

/** @details The <memory> header provides a class, called allocator<T>, that allocates
 *	a block of uninitialized memory that is intended to contain objects of type T, and
 *	returns a pointer to the initial element of that memory. 
 *	@brief Vectors are sequence containers representing arrays that can change in size.
 *	@container_properties:
 *	->	Vectors are sequence containers that are ordered in a strict linear sequence.
 *			Individual elements are accessed by their position in this sequence.
 *	-> Vectors are dynamic arrays that allow direct access to any element in the sequence,
 *			even through pointer arithmetics, and provides relatively fast addition/removal of
 *			elements at the end of the sequence. 
 *	-> A Vector container uses an allocator object to dynamically handle its storage needs.
 *	@template_class: We want to allow users to use vector to hold a variety of types.
 */

namespace ft {

	/*-----------*/
 /**	VECTOR: */
/*-----------*/

	//	Vector class template - container definition
	template < class T, class Alloc = std::allocator<T> > // generic template
	class vector {														

	public:

	/*-----------------*/
 /**	MEMBER:TYPES: */
/*-----------------*/

//	Definition																															Member type				notes
		typedef	T																																value_type;				
		typedef Alloc																														allocator_type;		//allocator<value_type>
		typedef typename allocator_type::reference															reference;				//allocator: value_type&
		typedef typename allocator_type::const_reference 												const_reference;	//allocator: const value_type&
		typedef typename allocator_type::pointer																pointer;					//allocator: value_type*
		typedef typename allocator_type::const_pointer													const_pointer;		//allocator: const value_type*
		typedef	typename ft::random_access_iterator<pointer>										iterator;
		typedef	typename ft::random_access_iterator<const_pointer>							const_iterator;
		typedef typename ft::reverse_iterator<iterator>													reverse_iterator;
		typedef typename ft::reverse_iterator<const_iterator>										const_reverse_iterator;
		typedef typename ft::random_access_iterator<iterator>::difference_type	difference_type;	//signed integral type: ptrdiff_t		
		typedef					 std::size_t																						size_type;				//unsigned integral type: difference_type

	private: // implementation
		allocator_type	_allocator;				// Allocator object
		pointer					_data;						// First element
		pointer 				_finish;					// Last element in the vector 
		pointer					_capacity;				// Las allocated piece of memory

	public:

 	/*---------------------*/
 /**	MEMBER:FUNCTIONS: */
/*---------------------*/

/**	CONSTRUCTOR: 	*/

//	DEFAULT CONSTRUCTOR
		explicit vector (const allocator_type& alloc = allocator_type()) :
		_allocator(alloc), _data(NULL),	_finish(NULL), _capacity(NULL) {}

/** FILL CONSTRUCTOR
		@uninitialized_fill: Constructs all the elements in the range (first, last)
		initializing them to the value of 'val' */
		explicit	vector (size_type n, const value_type& val = value_type(),
											const allocator_type& alloc= allocator_type()) :
		_allocator(alloc), _data(NULL), _finish(NULL), _capacity(NULL)
		{
			_data = _allocator.allocate(n);
			_finish = _data;
			_capacity = _data + n;
			for(; n > 0; --n, _finish++)
				_allocator.construct(_finish, val);
		}
			
/**	@range_constructor:	*/
/** @brief Given the distance between first and last as N,
 *	if first and last are both forward, bidirectional or random-access iterators,
 *	the copy constructor of T is only called N times, and no reallocation occurs.
 * 	Otherwise (first and last are just input iterators), the copy constructor of T
 *	is called O(N) times, and	reallocation occurs O(log N) times.
 * 
 *	This constructor has the same effect as:
 *	vector(static_cast<size_type>(first), static_cast<value_type>(last), a)
 *	if Input_Iterator is an integral type */
		template <typename InputIterator>								
		vector(	InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(),
						typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL) :
		_allocator(alloc), _data(NULL),	_finish(NULL), _capacity(NULL)
		{
			const size_type n = ft::distance(first, last);
			_data = _allocator.allocate(n);
			_finish = _data;
			_capacity = _data + n;
			for(; first != last; ++first, _finish++)
				_allocator.construct(_finish, *first);
		}

/** @copy_constructor:
 *	@details Memory is allocated equal to the capacity of the original vector
 *	Elements of the original vector are copied to the new allocated space */ 
		vector (const vector& other) :
		_allocator(other._allocator), _data(other._data), _finish(other._finish), _capacity(other._capacity)
		{
			size_type n = other._capacity - other._data;
			if (other.size() > 0) {
				_data = _allocator.allocate(other.capacity());
				_finish = uninitialized_copy(other.begin(), other.end(), _data);
				_capacity = _data + n;
			}
		}

/**	DESTRUCTOR: 	*/
//	(destructor)	Vector destructor
		virtual ~vector() {}

/**	OPERATOR:(=) 	*/
		vector& operator= (const vector& other) {
			if (this == &other) return *this;
			clear();
			assign(other.begin(), other.end());
			return *this;
		}

/**	ITERATORS: 	*/
		iterator begin(){ 											return _data; }

		const_iterator begin() const{						return _data; }

		iterator end(){													return _finish; }

		const_iterator end() const{							return _finish; }

		reverse_iterator rbegin(){							return reverse_iterator(end()); }

		const_reverse_iterator rbegin() const{ 	return const_reverse_iterator(end()); }

		reverse_iterator rend(){								return reverse_iterator(begin()); }

		const_reverse_iterator rend() const{		return const_reverse_iterator(begin()); }

/** CAPACITY: */
//	returns the n of elements
		size_type size() const {	return _finish - _data; }

//	returns the max possible n of elems 			
		size_type max_size() const {	return _allocator.max_size(); }

//	Change size
		void resize (size_type n, value_type val = value_type()) {
			if (n < size()) {
				for (size_type i = n; i < size(); ++i)
					_allocator.destroy(&_data[i]);
				_finish = _data + n;
			}
			else
				reserve(new_capacity(n));
			for (size_type i = size(); i != n; ++i)
				push_back(val);
			_finish = _data + n;
		}

//	returns n of elems that can be held in curr alloc storage		
		size_type capacity() const { return size_type(_capacity - _data); }

//	checks whether the container is empty
		bool empty() const {	return _finish == _data; }
		
		void reserve(size_type n) {	// reservers storage if capacity is less than new_cap
			if (n >= capacity()) {
				pointer start = _allocator.allocate(new_capacity(n)); 
				pointer finish = start;
		//	copy from start of old vec to position
				try {
					finish = uninitialized_copy(begin(), end(), start);	
				}
		//	If an error occurrs destroy the new allocated vector
				catch(...) {
					erase(start, finish);
					throw;
				}
		//	Destroy old vector data
				reallocate(start, finish, n);
			}
		}
		
/**	ELEMENT:ACCESS: */
		reference operator[](size_type n) { return *(begin() + n );}
		const_reference operator[](size_type n) const { return *(begin() + n );}
		reference at(size_type pos) {	
			if (!(pos < size()))
				throw std::out_of_range("vector::at: out of range");  
			return *(begin() + pos);
		}

		const_reference at(size_type pos) const {
			if (!(pos < size()))
				throw std::out_of_range("vector::at: out of range");  
			return *(begin() + pos);
		}

		reference front() {	return *(begin()); }

		const_reference front() const {	return *(begin()); }

		reference back() { return *(end() - 1); }

		const_reference back() const { return *(end() - 1); }

		value_type* data() { return begin(); }

		const value_type* data() const { begin(); }

/** MODIFIERS: */
/** @assign:	Assigns new contents to the vector replacing its current contents
 *						and modifying its size accordingly. */	
//	Replaces the contents with 'count' copies of value 'value'
		void assign( size_type count, const value_type& value) {
			while(!empty())
				pop_back();
			reserve(count);
 			while(count--)
				push_back(value);
		}

		template< class InputIterator > 
		void assign( InputIterator first, InputIterator last,
		typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL)
		{
			while(!empty())
				pop_back();
			reserve(ft::distance(first, last));
			for ( ; first != last; first++)
				push_back(*first);
		}
			
/**	@push_back: Add element at the end
 * 	If the storage capacity of the vector is not almost full 
 *	(-1 from full capacity) a new object (val) is constructed
 *	after the last element and the number of elements (size)
 *	is incremented by one.
 *	If the storage capacity of the vector is almost full its
 *	necessary to extend the vector. */
		void push_back(const value_type& val){
			size_type len = _finish - _data;
			if (empty()) reserve(1);
			else if (len >= capacity())
				reserve(len * 2);
			_allocator.construct(&_data[len], val);
			_finish++;
		}

		// pop_back:			Delete last element
		void pop_back() {
			_allocator.destroy(_data - 1);
			_finish--;
		}

//	single element
		iterator insert (iterator position, const value_type& val) {
			size_type n = position - begin();
			if (position == end()) push_back(val);
			else {
				size_type len = new_capacity(size());
				pointer start = _allocator.allocate(len);
				pointer finish = start;
				try {
					finish = uninitialized_copy(begin(), position, start); 
					_allocator.construct(finish++, val);
					finish = uninitialized_copy(position, end(), finish);	
				}
				catch(...) {
					erase(start, finish);
					throw;
				}
				reallocate(start, finish, len);
			}
			return begin() + n;
		}

/** @insert_fill: 	*/
		void insert (iterator position, size_type n, const value_type& val)
		{
			size_type len = size() + n;

			if (len <= capacity() && position == end())
				while (n--) insert(position, val);
			else {
				pointer start = _allocator.allocate(new_capacity(len));
				pointer finish = start;
//			If the allocation fails, the content allocated must be erased and a bad_alloc thrown 				
				try {
					finish = uninitialized_copy(begin(), position, start);
					while (n--)
						_allocator.construct(finish++, val); 												
					finish = uninitialized_copy(position, end(), finish);
				}
				catch(...) {
					erase(start, finish);
					throw;
				}
				reallocate(start, finish, len);
			}
		}

/** @insert_range:	 */
		template <class InputIterator>
		void insert (iterator position, InputIterator first, InputIterator last,
		typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL)
		{
			size_type len =	size() + ft::distance(first, last);
			if ((len < capacity()) && position == end()) {
				for (; first != last; first++, _finish++)
					insert(position, *first);
			}
			else {
				pointer start = _allocator.allocate(new_capacity(len)); 
				pointer finish = start;
				try {
					finish = uninitialized_copy(begin(), position, start);
					while (first != last)
						_allocator.construct(finish++, *first++);
					finish = uninitialized_copy(position, end(), finish);
				}
				catch(...) {
					erase(start, finish);
					throw;
				}
				reallocate(start, finish, len);
			}
		}
	
	/** @brief:
	 * If the position given is not the last element of the vector
	 * we copy all the elements from position to the last element
	 * The size (_finish iterator) is reduced and the last element is deleted
	 * Position is returned as the element after the one it was erased	*/
		iterator erase (iterator position) {
			uninitialized_copy(position + 1, end(), position);
			_finish--;
			return position;
		}

	/** @brief:
	 * The function recieves an iterator to the start and end
	 * of a range of elements to be erased copy all elements between 
	 * (range)last and the last element of the vector starting at 
	 * (range)first the _finish iterator is reduced by the length 
	 * of the range erased then the elements between the (range)first 
	 * and the last element are destroyed, since they were already copied
	 * The last element in the vector is returned	*/ 
		iterator erase (iterator first, iterator last) {
			iterator ret = first;
			if (last != end())
				uninitialized_copy(last, end(), first);
			while (first++ != last)
				_allocator.destroy(_finish--); 
			return ret;
		};

		void swap (vector& other) {
			pointer tmp = _data;
			_data = other._data;
			other._data = tmp;
			tmp = _finish;
			_finish = other._finish;
			other._finish = tmp;
			tmp = _capacity;
			_capacity = other._capacity;
			other._capacity = tmp;
		}

		void clear() {
			for (pointer i = _data; i < _finish; i++)
				_allocator.destroy(i);
			_finish = _data;
		}

/** ALLOCATOR: ***/
		allocator_type get_allocator() const { return _allocator; }


	private:

/** HELPERS: --*/
		size_type new_capacity(size_type len) {
			size_type cap = capacity();
			if (!len)	return cap = 1;
			while (len >= cap)
					cap = 2 * len;
			return cap;
		}

		void reallocate(pointer start, pointer finish, size_type len) {
			clear();			
			_allocator.deallocate(_data, capacity());
			_data = start;
			_finish = finish;
			_capacity = _data + len;
		}

		template<class InputIterator, class ForwardIterator>
		ForwardIterator uninitialized_copy( InputIterator first, InputIterator last,
																				ForwardIterator result )
		{
			for(; first != last; ++result, ++first)
				new (static_cast<void*>(&*result))
					typename iterator_traits<ForwardIterator>::value_type(*first);
			return result;
		}
	};

 	/*----------------------------------*/
 /**	NON:MEMBER:FUNCTION:OVERLOADS: */
/*----------------------------------*/
/**		RELATIONAL:OPERATORS:				 */

		template <class T, class Alloc> 
		bool operator == (const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs) {
			if (lhs.size() != rhs.size())
				return false;
			for(size_t i = 0; i < lhs.size(); i++) {
					if (lhs[i] != rhs[i])
						return false;
			}
			return true;
		}

		template <class T, class Alloc> 
		bool operator != (const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
			return !(lhs	==	rhs); }
		
		// lexicographical_compare compares the elements sequentially (checking both a<b and b<a)
		template <class T, class Alloc> 
		bool operator <	(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) { 
			return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()); }
	
		template <class T, class Alloc> 
		bool operator <=	(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) { 
			return !(lhs > rhs); }
	
		template <class T, class Alloc> 
		bool operator >	(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) { 
			return rhs < lhs; }
	
		template <class T, class Alloc> 
		bool operator >=	(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) { 
			return !(lhs < rhs); }
	
/**	@swap:				 */
		template< class T, class Alloc> 
		void swap ( ft::vector<T,Alloc>& lhs, ft::vector<T,Alloc>& rhs ){ lhs.swap(rhs); }

} //end namespaces

#endif