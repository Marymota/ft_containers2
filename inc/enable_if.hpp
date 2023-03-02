#ifndef _ENABLE_IF_HPP_
#define _ENABLE_IF_HPP_

 /** @brief type_traits (Header)
  * This Header defines a series of classes to obtain type information on compile-time.
  * Vector range constructor requires the std::is_integral type_trait and std::enable_if
  * so that it will call the fill constructor instead of the range constructor
  * when integers are given as arguments
  */ 

namespace ft {

 /**If B is true, enable_if has a public member typedef type, equal to T;
  * otherwise, there is no member typedef.
  * 
  * This metafunction is a conveninet way to leverage
  * SFINAE ("Substitution Failure is Not An Error")
  * prior to C++20's concepts, in particular for conditionally
  * removing functions from the candidate set based on type traits.
  */ 

 // ENABLE_IF: Enable type if condition is met (possible implementation)
		template <bool B, class T = void> struct enable_if {};
		template<class T>	struct enable_if<true, T> { typedef T type; }; // If true define the T type value



/** @brief type_traits (Header)
 * This Header defines a series of classes to obtain type information on compile-time.
 * Vector range constructor requires the std::is_integral type_trait and std::enable_if
 * so that it will call the fill constructor instead of the range constructor
 * when integers are given as arguments
 */ 

/**	If B is true, enable_if has a public member typedef type, equal to T;
 * otherwise, there is no member typedef.
 * 
 * This metafunction is a conveninet way to leverage
 * SFINAE ("Substitution Failure is Not An Error")
 * prior to C++20's concepts, in particular for conditionally
 * removing functions from the candidate set based on type traits.
 */ 

/** @integral_constant: Template designed to provide compile-time constants as types*/
		template <class T, T v>
		struct integral_constant {
			static const T value = v;
			typedef T value_type;
			typedef integral_constant<T,v> type;
			operator T() { return v; }
		};

		// Instantiation of integral_constant to represent the bool value true
		typedef integral_constant<bool,true> true_type;
		// Instantiation of integral_constant to represent the bool value false
		typedef integral_constant<bool,false> false_type;

		// Trait class that identifies whether T is an integral type.
		template<typename>
		struct is_integral_type : public false_type {};

		template<>	struct is_integral_type<bool>									 	: public true_type {};
		template<>	struct is_integral_type<char>									 	: public true_type {};
		template<>	struct is_integral_type<wchar_t>									: public true_type {};
		template<>	struct is_integral_type<signed char>							: public true_type {};
		template<>	struct is_integral_type<short int>								: public true_type {};
		template<>	struct is_integral_type<int>											: public true_type {};
		template<>	struct is_integral_type<long int>							 	: public true_type {};
		template<>	struct is_integral_type<long long int>						: public true_type {};
		template<>	struct is_integral_type<unsigned char>						: public true_type {};
		template<>	struct is_integral_type<unsigned short int> 			: public true_type {};
		template<>	struct is_integral_type<unsigned int> 						: public true_type {};
		template<>	struct is_integral_type<unsigned long int> 		 	: public true_type {};
		template<>	struct is_integral_type<unsigned long long int> 	: public true_type {};

		template<typename T> struct is_integral : is_integral_type<T> {};
	}


#endif

/** Resources:
 * 	stackoverflow.com/questions/40439909/c98-03-stdis-constructible-implementation
 * 	
*/