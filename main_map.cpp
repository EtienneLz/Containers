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
		map<int, int> c1;

    	c1.insert(map<int, int>::value_type(1, 1));
    	c1.insert(map<int, int>::value_type(2, 2));
    	c1.insert(map<int, int>::value_type(3, 3));
		c1.insert(map<int, int>::value_type(4, 3));
		c1.insert(map<int, int>::value_type(5, 3));
		c1.insert(map<int, int>::value_type(6, 3));
		c1.insert(map<int, int>::value_type(7, 3));

		map<int, int>::iterator it = c1.begin();

		for (int i = 0; i < 7; i++) {
			std::cout << it++->first << std::endl;
		}

		if (it == c1.end())
			std::cout << "True\n";
		else
			std::cout << "False\n";
		/*std::cout << c1.size() << std::endl << std::endl;

		std::cout << c1.end()->first << std::endl << std::endl;

		for (map<int, int>::iterator it = c1.begin(); it != c1.end(); it++) {
			std::cout << it->first << std::endl;
		}*/
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
	}
	{
  		map<char,int> mymap;
  		map<char,int>::iterator it;

  		// insert some values:
  		mymap['a']=10;
  		mymap['b']=20;
  		mymap['c']=30;
  		mymap['d']=40;
  		mymap['e']=50;
  		mymap['f']=60;

  		it=mymap.find('b');
  		//mymap.erase (it);                   // erasing by iterator

  		mymap.erase ('c');                  // erasing by key

  		//it=mymap.find ('e');
  		//mymap.erase ( it, mymap.end() );    // erasing by range

  		// show content:
  		for (it=mymap.begin(); it!=mymap.end(); ++it)
    		std::cout << it->first << " => " << it->second << '\n';
}
{
  		std::map<char,int> mymap;
  		std::map<char,int>::iterator itlow,itup;

  		mymap['a']=20;
  		mymap['b']=40;
  		mymap['c']=60;
  		mymap['d']=80;
  		mymap['e']=100;

  		itlow=mymap.lower_bound ('b');  // itlow points to b
  		itup=mymap.upper_bound ('d');   // itup points to e (not d!)

  		mymap.erase(itlow,itup);        // erases [itlow,itup)

  		// print content:
  		for (std::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
    		std::cout << it->first << " => " << it->second << '\n';
}*/
}