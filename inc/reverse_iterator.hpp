#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP
# include "iterator_traits.hpp"

namespace ft {
							/*--------------------*/
						 /** REVERSE:ITERATOR: */
						/*--------------------*/
template <typename iterator_type>
class	reverse_iterator: public iterator_traits<iterator_type> {

	public:

/** MEMBER:TYPES: */
/**	Corresponding specialization of iterator_types class template definition */
		typedef typename iterator_traits<iterator_type>::iterator_category	iterator_category;
		typedef typename iterator_traits<iterator_type>::value_type					value_type;
		typedef typename iterator_traits<iterator_type>::difference_type		difference_type;
		typedef typename iterator_traits<iterator_type>::pointer						pointer;
		typedef typename iterator_traits<iterator_type>::reference					reference;
	
	protected:
		iterator_type	_rev_it;

	public:

/** MEMBER:FUNCTIONS: */
//	Default constructor
		reverse_iterator() : _rev_it(iterator_type()) {}

//	Initialization constructor
		reverse_iterator(iterator_type it) : _rev_it(it) {}

//	Copy / type-cast constructor
		template <class Iter>
		reverse_iterator(const reverse_iterator<Iter>& rev_it) : _rev_it(rev_it.base()) {}

//	Assignment constructor
		reverse_iterator& operator= (const reverse_iterator& rev_it) {
			if (this == &rev_it) return *this;
			_rev_it = rev_it._rev_it;
			return *this;
		}

		~reverse_iterator() {}


//	Returns a copy of the base iterator '_rev_it' used for underlying work
		iterator_type	base() const { return _rev_it; }

/**	Deference iterator
 * 	Returns a reference to the element pointed to by the iterator 
 * 	Internally, the function decreases a copy of its base iterator
 *	and returns the result of deferencing it;
*/	reference	operator* () const { iterator_type	it = _rev_it; return *--it; }

//	Addition operator
		reverse_iterator	operator+ (difference_type n) const {  return reverse_iterator(_rev_it - n);	}

//	Increment iterator position (pre-increment)
		reverse_iterator&	operator++ () {_rev_it--; return *this; }

//	Increment iterator position (post-increment)
		reverse_iterator	operator++ (int) { reverse_iterator tmp = *this; _rev_it--; return tmp; }

//	Advance iterator
		reverse_iterator&	operator+= (difference_type n) { _rev_it -= n; return *this; }

//	Subtraction operator
		reverse_iterator	operator- (difference_type n) const { return reverse_iterator(_rev_it + n);	}

//	Decrement iterator position (pre-increment)
		reverse_iterator&	operator-- (void) { _rev_it++; return *this; }

//	Decrement iterator position (post-increment)
		reverse_iterator	operator-- (int) { reverse_iterator tmp = *this; _rev_it++; return tmp; }
		
//	Retrocede iterator
		reverse_iterator&	operator-= (difference_type n) { _rev_it += n; return *this; }

//	Deference iterator - Returns a pointer to the element pointed to by the iterator
		pointer	operator->() const { return &(operator*()); }
		
/**	Deference iterator with offset
 * 	Accesses the element located n positions away from the element currently pointed to.
 */	reference	operator[](difference_type n) const { return _rev_it[-n - 1]; }

};

/** NON:MEMBER:FUNCTION:OVERLOADS: */

		template <class Iterator1, class Iterator2>
		bool			operator==	(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs) { return lhs.base() == rhs.base(); }
		
		template <class Iterator1, class Iterator2>
		bool			operator!=	(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs) { return lhs.base() != rhs.base(); }
	
		template <class Iterator1, class Iterator2>
		bool			operator<		(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs) { return lhs.base() > rhs.base(); }
		
		template <class Iterator1, class Iterator2>
		bool			operator>		(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs) { return lhs.base() < rhs.base(); }
	
		template <class Iterator1, class Iterator2>
		bool			operator<=	(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs) { return lhs.base() >= rhs.base(); }
	
		template <class Iterator1, class Iterator2>
		bool			operator>=	(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs) { return lhs.base() <= rhs.base(); }


//	Addition operator overload
//	Overloads the member function operator+, with the left-hand and right-hamd types inverted, but with same behaviour.
		template <class T>
		reverse_iterator<T>	operator+ (	typename reverse_iterator<T>::difference_type n,
																		const reverse_iterator<T>& m_it) {
			return m_it.base() - n; }

		template <class Iterator1, class Iterator2>
		typename reverse_iterator<Iterator1>::difference_type operator-
		(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs) {
			return  rhs.base() - lhs.base();
		}

		template <class Iterator>
		typename reverse_iterator<Iterator>::difference_type operator-
		(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
			return  rhs.base() - lhs.base();
		}
}

#endif

/** Resources:
 * cplusplus -> iterator/reverse_iterator/reverse_iterator/ 
 * 
 */