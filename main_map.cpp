#include "utils/make_pair.hpp"
#include <iostream>


#include "map.hpp"
#include <map>

#ifndef STD
# define NAMESPACE ft
#else
# define NAMESPACE std
#endif

using namespace NAMESPACE;

int main(void) {
	{
		map<const int, int> c1;

    	/*c1.insert(map<int, int>::value_type('a', 1));
    	c1.insert(map<int, int>::value_type('b', 2));
    	c1.insert(map<int, int>::value_type('c', 3));
		c1.insert(map<int, int>::value_type('d', 3));
		c1.insert(map<int, int>::value_type('e', 3));
		c1.insert(map<int, int>::value_type('f', 3));

		std::cout << c1.size() << std::endl << std::endl;

		std::cout << c1.end()->second << std::endl << std::endl;*/

		//for (map<int, int>::iterator it = c1.begin(); it != c1.end(); it++) {
		//	std::cout << it->first << std::endl;
		//}
	// find and show elements
    	//std::cout << "c1.at('a') == " << c1.at('a') << std::endl;
    	//std::cout << "c1.at('b') == " << c1.at('b') << std::endl;
    	//std::cout << "c1.at('c') == " << c1.at('c') << std::endl;
	}
	/*{
  		map<char,int> mymap;

  		// first insert function version (single parameter):
  		mymap.insert ( pair<char,int>('a',100) );
  		mymap.insert ( pair<char,int>('z',200) );

  		pair<map<char,int>::iterator,bool> ret;
  		ret = mymap.insert (pair<char,int>('z',500) );
  		if (ret.second==false) {
   		std::cout << "element 'z' already existed";
  		std::cout << " with a value of " << ret.first->second << '\n';
  		}
  		// second insert function version (with hint position):
  		map<char,int>::iterator it = mymap.begin();
  		mymap.insert (it, pair<char,int>('b',300));  // max efficiency inserting
  		mymap.insert (it, pair<char,int>('c',400));  // no max efficiency inserting

  		// third insert function version (range insertion):
  		map<char,int> anothermap;
  		anothermap.insert(mymap.begin(),mymap.find('c'));

  		// showing contents:
  		std::cout << "mymap contains:\n";
  		for (it=mymap.begin(); it!=mymap.end(); ++it)
    	std::cout << it->first << " => " << it->second << '\n';

  		std::cout << "anothermap contains:\n";
  		for (it=anothermap.begin(); it!=anothermap.end(); ++it)
    	std::cout << it->first << " => " << it->second << '\n';
	}*/
}