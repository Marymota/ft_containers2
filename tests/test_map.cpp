#include <map>
#include <iostream>

#include "../containers/map.hpp"
#include "../inc/bidirectional_iterator.hpp"

bool fncomp (char lhs, char rhs) { return lhs < rhs; }

struct classcomp {
	bool operator() (const char& lhs, const char& rhs) const
	{ return lhs < rhs; }
};

void map_construct() {
	std::map<char,int> first;

	first['a']=10;
	first['b']=30;
	first['c']=50;
	first['d']=70;

	std::map<char,int> second (first.begin(),first.end());
	std::map<char,int> third 	(second);
	std::map<char,int,classcomp> fourth;

	bool(*fn_pt)(char,char) = fncomp;
	std::map<char,int,bool(*)(char,char)> fifth (fn_pt);

	std::map<char,int>::iterator it = first.begin();
	for (; it != first.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
	std::cout << "size: " << first.size() << std::endl;

	std::cout << std::endl;
	for (it = second.begin(); it != second.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
	std::cout << "size: " << second.size() << std::endl;

	std::cout << std::endl;
	for (it = third.begin(); it != third.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
	std::cout << "size: " << third.size() << std::endl;

	std::cout << std::endl;
	for (it = fourth.begin(); it != fourth.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
	std::cout << "size: " << fourth.size() << std::endl;

}

void ft_map_construct() {

/** Create a map "first" that recieves pair elements composed
	*	of a key and a value; both can have any type given; */
	ft::map<char,int> first;

/** Add elements to the map using the [] operator */
	first['a']=10;
	first['b']=30;
	first['c']=50;
	first['d']=70;

	ft::map<char,int> second (first.begin(),first.end());
	ft::map<char,int> third (second);
	ft::map<char,int,classcomp> fourth; // ??

	bool(*fn_pt)(char,char) = fncomp;
	ft::map<char,int,bool(*)(char,char)> fifth (fn_pt);

	ft::map<char,int>::iterator it = first.begin();
	for (; it != first.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
	std::cout << "size: " << first.size() << std::endl;

	std::cout << std::endl;
	for (it = second.begin(); it != second.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
	std::cout << "size: " << second.size() << std::endl;

	std::cout << std::endl;
	for (it = third.begin(); it != third.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
	std::cout << "size: " << third.size() << std::endl;

	std::cout << std::endl;
	for (it = fourth.begin(); it != fourth.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
	std::cout << "size: " << fourth.size() << std::endl;
}

//----------------------------------------------------------

void assignment() {
	std::map<char,int> first;
	std::map<char,int> second;

	first['x']=8;
	first['y']=16;
	first['z']=32;

	second=first;
	first=std::map<char,int>();

	std::cout << "Size of first: " << first.size() << '\n';
	std::cout << "size of second: " << second.size() << '\n';
}

void ft_assignment() {
	ft::map<char,int> first;
	ft::map<char,int> second;

	first['x']=8;
	first['y']=16;
	first['z']=32;

	second=first;
	first = ft::map<char,int>();

	std::cout << "Size of first: " << first.size() << '\n';
	std::cout << "size of second: " << second.size() << '\n';
}
//----------------------------------------------------------

void begin_end() {

  std::map<char,int> mymap;

  mymap['b'] = 100;
  mymap['a'] = 200;
  mymap['c'] = 300;

  // show content:
  for (std::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
    std::cout << it->first << " => " << it->second << '\n';

	std::map<char,int> rmap;

	rmap['x'] = 100;
	rmap['y'] = 200;
	rmap['z'] = 300;

	std::map<char,int>::reverse_iterator rit;
	for(rit=rmap.rbegin(); rit!=rmap.rend(); ++rit)
		std::cout << rit->first << " => " << rit->second << '\n';

}

void ft_begin_end() {

  ft::map<char,int> mymap;

  mymap['b'] = 100;
  mymap['a'] = 200;
  mymap['c'] = 300;

  // show content:
  for (ft::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
    std::cout << it->first << " => " << it->second << '\n';

	ft::map<char,int> rmap;

	rmap['x'] = 100;
	rmap['y'] = 200;
	rmap['z'] = 300;

	ft::map<char,int>::reverse_iterator rit;
	for(rit=rmap.rbegin(); rit!=rmap.rend(); ++rit)
		std::cout << rit->first << " => " << rit->second << '\n';

}

//----------------------------------------------------------


void ft_test_map_lower_upper_bound() {
  ft::map<char,int> mymap;
  ft::map<char,int>::iterator itlow,itup;

  mymap['a']=20;
  mymap['b']=40;
  mymap['c']=60;
  mymap['d']=80;
  mymap['e']=100;

 	itlow=mymap.lower_bound ('b');  // itlow points to b
 	std::cout << itlow->first << '\n';
 	itup=mymap.upper_bound ('d');   // itup points to e (not d!)
	std::cout << itup->first << '\n';
	mymap.erase(itlow,itup);        // erases [itlow,itup)

  // print content:
  for (ft::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
    std::cout << it->first << " => " << it->second << '\n';
}

void test_map_lower_upper_bound() {
  std::map<char,int> mymap;
  std::map<char,int>::iterator itlow,itup;

  mymap['a']=20;
  mymap['b']=40;
  mymap['c']=60;
  mymap['d']=80;
  mymap['e']=100;

  itlow=mymap.lower_bound ('b');  // itlow points to b
	std::cout << itlow->first << '\n';

  itup=mymap.upper_bound ('d');   // itup points to e (not d!)
  std::cout << itup->first << '\n';
  mymap.erase(itlow,itup);        // erases [itlow,itup)

  // print content:
  for (std::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
    std::cout << it->first << " => " << it->second << '\n';
}

void ft_map_begin() {
	ft::map<char,int> mymap;
	mymap['b'] = 100;
	mymap['a'] = 200;
	mymap['c'] = 300;

	for (ft::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
}

void map_begin() {
	std::map<char,int> mymap;
	mymap['b'] = 100;
	mymap['a'] = 200;
	mymap['c'] = 300;

	for (std::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
}

void erase_map() {
	std::map<char,int> mymap;
	std::map<char,int>::iterator it;

	mymap['f']=10;
	mymap['e']=20;
	mymap['d']=30;
	mymap['c']=40;
	mymap['b']=50;
	mymap['a']=60;
	mymap['g']=10;
	mymap['h']=20;
	mymap['i']=30;
	mymap['j']=40;
	mymap['k']=50;
	mymap['l']=60;

	it=mymap.find('e');
	mymap.erase(it);
	it=mymap.find('h');
	mymap.erase(it);
	it=mymap.find('l');
	mymap.erase(it);


	for(it=mymap.begin(); it!=mymap.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
}

void ft_erase_map() {
	ft::map<char,int> mymap;
	ft::map<char,int>::iterator it;

	mymap['f']=10;
	mymap['e']=20;
	mymap['d']=30;
	mymap['c']=40;
	mymap['b']=50;
	mymap['a']=60;
	mymap['g']=10;
	mymap['h']=20;
	mymap['i']=30;
	mymap['j']=40;
	mymap['k']=50;
	mymap['l']=60;

	it=mymap.find('e');
	mymap.erase(it);
	it=mymap.find('h');
	mymap.erase(it);
	it=mymap.find('l');
	mymap.erase(it);

	for(it=mymap.begin(); it!=mymap.end(); ++it) {
		std::cout << it->first << " => " << it->second << '\n';
	}

//	mymap.tree_print();
}