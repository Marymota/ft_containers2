#ifndef _PAIR_HPP_
#define _PAIR_HPP_

namespace ft {


  /*-----------*/
 /**	PAIR:		*/
/*-----------*/

template <class T1, class T2> 
struct pair {

	// Member types
	typedef T1	first_type;			//	type of the first template parameter
	typedef T2	second_type;		//	type of the second template parameter

	// Public member variables
	first_type	first;					// first value in pair
	second_type second;					// second value in pair



		 /*------------------*/ 
		/** CONSTRUCT:PAIR: */
	 /*------------------*/ 
	/** @info: Constructs a pair object:
 	*					 Way to store two heterogeneus
 *					 objects as a single unit. 
*/

	// default constructor
	pair() : first(first_type()), second(second_type()) {}

	// copy / move constructor (and implicit conversion)
	template<class U, class V>
	pair (const pair<U,V>& pr) : first(pr.first), second(pr.second) {}

	// initialization constructor
	pair( const first_type& first, const second_type& second) : first(first), second(second) {}
	
	// Assign Contents
	pair& operator= (const pair& pr) { 
		if (*this == pr) { return *this; }
		first = pr.first;
		second = pr.second;
		return *this;
	}
};


	 	 /*---------------------------------*/
	  /** NON:MEMBER:FUNCTION:OVERLOADS: */
	 /*---------------------------------*/
	/**  relational operators (pair)   */

	// Compare two pair objects: True only if both first and second parameters are equal
	template <class T1, class T2>
	bool operator== (	const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{	return lhs.first == rhs.first && lhs.second == rhs.second; }

	template <class T1, class T2>
	bool operator!= (	const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{	return !(lhs == rhs);	}

	template <class T1, class T2>
	bool operator<  (	const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
		return lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second); }

	template <class T1, class T2>
	bool operator<= (	const pair<T1,T2>& lhs, const pair<T1,T2>& rhs){ 
		return !(rhs < lhs);	}

	template <class T1, class T2>
	bool operator>  (	const pair<T1,T2>& lhs, const pair<T1,T2>& rhs){ 
		return rhs < lhs; }

	template <class T1, class T2>
	bool operator>= (	const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
	{ return !(lhs < rhs);  }


		 /**--------------*/
		/**	MAKE:PAIR: 	 */
	 /*---------------*/
	/** @info: Constructs a pair object:
  *					The template types can be implicitly deduced
 * 				  from the arguments passed to make_pair
*/
	template <class T1, class T2>
	pair<T1,T2> make_pair (T1 x, T2 y) { return pair<T1,T2>(x, y); }

}
#endif