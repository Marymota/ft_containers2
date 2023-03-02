#ifndef RANDOM_ACCESS_ITERATOR_HPP
#define RANDOM_ACCESS_ITERATOR_HPP

#include "iterator_traits.hpp"

namespace ft
{
							/*--------------------------*/
						 /** RANDOM:ACCESS:ITERATOR: */
						/*--------------------------*/
template <class T>
class random_access_iterator: public iterator_traits<T> { 

	public:

/** MEMBER:TYPES: */
/**	Corresponding specialization of iterator_types class template definition */
		typedef typename iterator_traits<T>::difference_type		difference_type;
		typedef typename iterator_traits<T>::value_type					value_type;
		typedef typename iterator_traits<T>::pointer						pointer;
		typedef typename iterator_traits<T>::reference					reference;
		typedef typename iterator_traits<T>::iterator_category	iterator_category;

	private:
		pointer     _iterator;

	public:

/** MEMBER:FUNCTIONS: */
//	Default constructor
		random_access_iterator() : _iterator(NULL) {}
		
//	Initialization constructor
		random_access_iterator(pointer it) : _iterator(it) {}

//	Copy / type-cast constructor
		template <class Iter>
		random_access_iterator(const random_access_iterator<Iter>& it) : _iterator(it.base()) {}

//	Assignment constructor
		random_access_iterator& operator= (const random_access_iterator& it) {
			if (this == &it) return *this;
			_iterator = it._iterator;
			return *this;
		}

		~random_access_iterator() {}

//	Returns a copy of the base iterator '_iterator' used for underlying work
		pointer	base() const {	return _iterator; }

//	Deference iterator:	Returns a reference to the element pointed to by the iterator 
		reference	operator* () const {	return *(_iterator); }

//	Addition operator
		random_access_iterator	operator+ (difference_type n) const { return random_access_iterator(_iterator + n); }

//	Increment iterator position (pre-increment)
		random_access_iterator&	operator++ () { _iterator++; return *this; }

//	Increment iterator position (post-increment)
		random_access_iterator	operator++ (int) { random_access_iterator tmp(*this); _iterator++; return tmp; }

//	Advance iterator
		random_access_iterator&	operator+= (difference_type n) { _iterator += n; return *this; }

//	Subtraction operator
		random_access_iterator	operator- (difference_type n) const { return random_access_iterator(_iterator - n); }

//	Returns the number of elements between two vector iterators (only in random access iterators)
		difference_type	operator- (const random_access_iterator& it) const { return _iterator - it._iterator; }

//	Decrement iterator position (pre-increment)
		random_access_iterator&	operator-- () { _iterator--; return *this; } 

//	Decrement iterator position (post-increment)
		random_access_iterator	operator-- (int) { random_access_iterator tmp(*this); _iterator--; return tmp; }

//	Retrocede iterator
		random_access_iterator&	operator-= (difference_type n) { _iterator -= n; return *this; }

//	Deference iterator - Returns a pointer to the element pointed to by the iterator		
		pointer	operator-> () const { return _iterator; }

//	Deference iterator with offset: 	Access the element located n positions away from the current element.		
		reference	operator[] (difference_type n) const { return _iterator[n]; }
};


/** NON:MEMBER:FUNCTION:OVERLOADS: */

		template <class Iterator1, class Iterator2>
		bool	operator==	(const random_access_iterator<Iterator1>& lhs, const random_access_iterator<Iterator2>& rhs) { return lhs.base() ==	rhs.base(); }
	
		template <class Iterator1, class Iterator2>
		bool	operator!=	(const random_access_iterator<Iterator1>&	lhs, const random_access_iterator<Iterator2>& rhs) { return lhs.base() !=	rhs.base(); }
	
		template <class Iterator1, class Iterator2>
		bool	operator<		(const random_access_iterator<Iterator1>& lhs, const random_access_iterator<Iterator2>& rhs) { return lhs.base() <	rhs.base(); }
	
		template <class Iterator1, class Iterator2>
		bool	operator>		(const random_access_iterator<Iterator1>& lhs, const random_access_iterator<Iterator2>& rhs) { return lhs.base() >	rhs.base(); }
	
		template <class Iterator1, class Iterator2>
		bool	operator<=	(const random_access_iterator<Iterator1>& lhs, const random_access_iterator<Iterator2>& rhs) { return lhs.base() <=	rhs.base(); }
	
		template <class Iterator1, class Iterator2>
		bool	operator>=	(const random_access_iterator<Iterator1>& lhs, const random_access_iterator<Iterator2>& rhs) { return lhs.base() >=	rhs.base(); }


//	Addition operator
		template <class T>
		random_access_iterator<T>	operator+ (	typename random_access_iterator<T>::difference_type n,
																					const random_access_iterator<T>& m_it) {
			return m_it.base() + n; }

		template <class Iterator1, class Iterator2>
		typename random_access_iterator<Iterator1>::difference_type operator-
		(const random_access_iterator<Iterator1>& lhs, const random_access_iterator<Iterator2>& rhs) {
			return  lhs.base() - rhs.base();
		}
}

#endif

/** Resources:
 *	https://learn.microsoft.com/en-us/cpp/cppcx/platform-collections-vectoriterator-class?view=msvc-170
*/