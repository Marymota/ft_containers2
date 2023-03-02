#ifndef ITERATOR_TRAITS_HPP
#define ITERATOR_TRAITS_HPP

#include <cstddef>

namespace ft
{
/**	Iterator_traits:
 *	Defines the properties of iterators;
 *	For every iterator type, a corresponding specialization
 *	of iterator_types class template shall be defined
*/
	template <class Iterator>
	class iterator_traits {

		public:
//																									Member:								 Description:
			typedef typename Iterator::difference_type		difference_type;		// Subtraction of one iterator from another
			typedef typename Iterator::value_type					value_type;					// Type of element
			typedef typename Iterator::pointer						pointer;						// Type of pointer to element
			typedef typename Iterator::reference					reference;					// Type of reference to an element
			typedef typename Iterator::iterator_category	iterator_category;	// Iterator category
		};

// 	Partial specialization for pointer types
	template <class T>
	class iterator_traits<T*> {

		public:
//						T* specialization:							 			generic definition:
			typedef ptrdiff_t															difference_type;
			typedef T																			value_type;
			typedef T*																		pointer;
			typedef T&																		reference;
			typedef std::random_access_iterator_tag				iterator_category;
		};

// 	Partial specialization for const pointer types
	template <class T>
	class iterator_traits<const T*> {

		public:
//		const T* specialization:							 	 			generic definition:
			typedef ptrdiff_t												 			difference_type;
			typedef T																 			value_type;
			typedef const T*												 			pointer;
			typedef const T&												 			reference;
			typedef std::random_access_iterator_tag	 			iterator_category;
		};

} // end_namespace

#endif

/** References: 
 *	libstdc++ -> stl_iterator_base_types.h
 *	cplusplus -> iterator_traits
*/
