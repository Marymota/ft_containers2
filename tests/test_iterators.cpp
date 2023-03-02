#include <map>
#include "../containers/map.hpp"
#include "../inc/bidirectional_iterator.hpp"
#include "../containers/vector.hpp"
#include <string>       // std::string
#include <iostream>     // std::cout
#include <typeinfo>

void iterator_traits() {
	std::cout << "------ iterator_traits ------" << std::endl;
	typedef std::iterator_traits<int*> traits;
	if (typeid(traits::iterator_category)==typeid(std::random_access_iterator_tag))
		std::cout << "int* ia a random-access iterator";
	std::cout << std::endl;
}

void ft_iterator_traits() {
	std::cout << "------ ft iterator_traits ------" << std::endl;
	typedef ft::iterator_traits<int*> traits;
	if (typeid(traits::iterator_category)==typeid(std::random_access_iterator_tag))
		std::cout << "ft int* ia a random-access iterator";
	std::cout << std::endl;
}

void reverse_iterator() {
  ft::vector<int> myvector;
  for (int i=0; i<10; i++) myvector.push_back(i);

  typedef ft::vector<int>::iterator iter_type;
                                                         // ? 9 8 7 6 5 4 3 2 1 0 ?
  iter_type from (myvector.begin());                     //   ^
                                                         //         ------>
  iter_type until (myvector.end());                      //                       ^
                                                         //
  std::reverse_iterator<iter_type> rev_until (from);     // ^
                                                         //         <------
  std::reverse_iterator<iter_type> rev_from (until);     //                     ^

  std::cout << "myvector:";
  while (rev_from != rev_until)
    std::cout << ' ' << *rev_from++;
  std::cout << '\n';

}