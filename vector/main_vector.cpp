#include <iostream>


#include "../vector.hpp"
#include "../utils/make_pair.hpp"


#include <vector>

#ifndef STD
# define NAMESPACE ft
#else
# define NAMESPACE std
#endif

using namespace NAMESPACE;

int	main(void) {
	{
  		// constructors used in the same order as described above:
  		vector<int> first;                                // empty vector of ints
  		vector<int> second (4,100);                       // four ints with value 100
  		vector<int> third (second.begin(),second.end());  // iterating through second
  		vector<int> fourth (third);                       // a copy of third

  		// the iterator constructor can also be used to construct from arrays:
  		int myints[] = {16,2,77,29};
  		vector<int> fifth (myints, myints + sizeof(myints) / sizeof(int) );

  		std::cout << "The contents of fifth are:";
  		for (vector<int>::iterator it = fifth.begin(); it != fifth.end(); ++it)
    		std::cout << ' ' << *it;
  		std::cout << '\n';
	}
	std::cout << std::endl;
	{
		vector<int> vec;

		std::cout << "Size: " << vec.size() << std::endl << std::endl;

		vec.push_back(1);
		vec.push_back(2);
		vec.push_back(3);
		vec.push_back(4);
		vec.push_back(5);
		vec.push_back(6);
		vec.push_back(7);
		vec.push_back(8);
		vec.push_back(9);

		for (int i(0); i < 9; i++) {
			std::cout << vec[i] << std::endl;
		}

		std::cout << "Size: " << vec.size() << std::endl;

		vec.pop_back();
		vec.pop_back();

		std::cout << std::endl;

		std::cout << "Is empty: " << vec.empty() << std::endl;

		for (int i(0); i < 9; i++) {
			std::cout << vec[i] << std::endl;
		}

		std::cout << "Size: " << vec.size() << std::endl;

		vec.pop_back();
		vec.pop_back();
		vec.pop_back();
		vec.pop_back();
		vec.pop_back();
		vec.pop_back();
		vec.pop_back();

		std::cout << "Is empty: " << vec.empty() << std::endl << std::endl;
	}
	std::cout << std::endl;
	{
  		vector<int> myvector;
  		int * p;
  		unsigned int i;

  		// allocate an array with space for 5 elements using vector's allocator:
  		p = myvector.get_allocator().allocate(5);

  		// construct values in-place on the array:
  		for (i=0; i<5; i++) myvector.get_allocator().construct(&p[i],i);

  		std::cout << "The allocated array contains:";
  		for (i=0; i<5; i++) std::cout << ' ' << p[i];
  		std::cout << '\n';

  		// destroy and deallocate:
  		for (i=0; i<5; i++) myvector.get_allocator().destroy(&p[i]);
  		myvector.get_allocator().deallocate(p,5);
	}
	std::cout << std::endl;
	{
  		vector<int> myvector;
  		int sum (0);
  		myvector.push_back (100);
  		myvector.push_back (200);
  		myvector.push_back (300);

  		while (!myvector.empty())
  		{
    		sum+=myvector.back();
    		myvector.pop_back();
  		}
  		std::cout << "The elements of myvector add up to " << sum << '\n';
	}
	std::cout << std::endl;
	{
		vector<int> myvector;

		myvector.push_back(78);
		myvector.push_back(16);

		// now front equals 78, and back 16

		std::cout << "myvector.front() is equal to " << myvector.front() << '\n';

		myvector.front() -= myvector.back();

		std::cout << "myvector.front() is now " << myvector.front() << '\n';
	}
	std::cout << std::endl;
	{
		vector<int> myints;
		std::cout << "0. size: " << myints.size() << '\n';

		for (int i=0; i<10; i++) myints.push_back(i);
		std::cout << "1. size: " << myints.size() << '\n';

		myints.insert (myints.end(),10,100);
		std::cout << "2. size: " << myints.size() << '\n';

		myints.pop_back();
		std::cout << "3. size: " << myints.size() << '\n';
	}
	std::cout << std::endl;
	{
  		vector<int> myvector;

  		// set some content in the vector:
  		for (int i=0; i<100; i++)
			myvector.push_back(i);

  		std::cout << "size: " << myvector.size() << "\n";
  		std::cout << "capacity: " << myvector.capacity() << "\n";
  		std::cout << "max_size: " << myvector.max_size() << "\n";
	}
	std::cout << std::endl;
	{
  		vector<int> myvector;

  		// set some initial content:
  		for (unsigned int i = 1; i < 10; i++) myvector.push_back(i);

  		myvector.resize(5);
  		myvector.resize(8,100);
  		myvector.resize(12);

  		std::cout << "myvector contains:";
  		for (unsigned int i = 0; i < myvector.size(); i++)
  			std::cout << ' ' << myvector[i];
  		std::cout << '\n';
	}
	std::cout << std::endl;
	{
  		vector<int> myvector (10);   // 10 zero-initialized ints

  		// assign some values:
  		for (unsigned i = 0; i < myvector.size(); i++)
    		myvector.at(i) = i;

  		std::cout << "myvector contains:";
  		for (unsigned i = 0; i < myvector.size(); i++)
    		std::cout << ' ' << myvector.at(i);
  		std::cout << '\n';
	}
	std::cout << std::endl;
	{
  		vector<int> myvector;
  		for (int i=1; i<=5; i++) myvector.push_back(i);

  		std::cout << "myvector contains:";
  		for (vector<int>::iterator it = myvector.begin() ; it != myvector.end(); ++it)
    		std::cout << ' ' << *it;
  		std::cout << '\n';
	}
	std::cout << std::endl;
	{
  		vector<int> myvector (5);  // 5 default-constructed ints

  		int i=0;

  		vector<int>::reverse_iterator rit = myvector.rbegin();
  		for (; rit!= myvector.rend(); ++rit)
    		*rit = ++i;

  		std::cout << "myvector contains:";
  		for (vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it)
    		std::cout << ' ' << *it;
  		std::cout << '\n';
	}
	std::cout << std::endl;
	{
  		vector<int> first;
  		vector<int> second;
  		vector<int> third;

  		first.assign (7,100);             // 7 ints with a value of 100

  		vector<int>::iterator it;
  		it=first.begin();

  		second.assign (it,first.end()-1); // the 5 central values of first

  		int myints[] = {1776,7,4};
  		third.assign (myints,myints+3);   // assigning from array.

  		std::cout << "Size of first: " << int (first.size()) << '\n';
  		std::cout << "Size of second: " << int (second.size()) << '\n';
  		std::cout << "Size of third: " << int (third.size()) << '\n';
	}
	std::cout << std::endl;
	{
  		vector<int> foo (3,100);   // three ints with a value of 100
  		vector<int> bar (5,200);   // five ints with a value of 200

		std::cout << "foo contains:";
  		for (unsigned i=0; i<foo.size(); i++)
    		std::cout << ' ' << foo[i];
  		std::cout << '\n';

  		std::cout << "bar contains:";
  		for (unsigned i=0; i<bar.size(); i++)
    		std::cout << ' ' << bar[i];

		std::cout << std::endl << "Swapping" << std::endl;
  		foo.swap(bar);

  		std::cout << "foo contains:";
  		for (unsigned i=0; i<foo.size(); i++)
    		std::cout << ' ' << foo[i];
  		std::cout << '\n';

  		std::cout << "bar contains:";
  		for (unsigned i=0; i<bar.size(); i++)
    		std::cout << ' ' << bar[i];
  		std::cout << '\n';

		swap(foo, bar);

		std::cout << std::endl << "Swapping" << std::endl;

  		std::cout << "foo contains:";
  		for (unsigned i=0; i<foo.size(); i++)
    		std::cout << ' ' << foo[i];
  		std::cout << '\n';

  		std::cout << "bar contains:";
  		for (unsigned i=0; i<bar.size(); i++)
    		std::cout << ' ' << bar[i];
  		std::cout << '\n';
	}
	std::cout << std::endl;
	{
		vector<int> myvector (3,100);
  		vector<int>::iterator it;

  		it = myvector.begin();
  		it = myvector.insert ( it , 200 );

		it = myvector.begin();
		myvector.insert (it , 20 );
		std::cout << "myvector contains:";
  		for (it=myvector.begin(); it<myvector.end(); it++)
    		std::cout << ' ' << *it;
  		std::cout << '\n';
		it = myvector.begin();
  		myvector.insert (it,2,300);
		it = myvector.begin()+7;
		myvector.insert (it,2,44);
  		it = myvector.begin();

		std::cout << "myvector contains:";
  		for (it=myvector.begin(); it<myvector.end(); it++)
    		std::cout << ' ' << *it;
  		std::cout << '\n';
		it = myvector.begin();

  		vector<int> anothervector (2,400);
  		myvector.insert (it+2,anothervector.begin(),anothervector.end());

  		int myarray [] = { 501,502,503 };
  		myvector.insert (myvector.begin(), myarray, myarray+3);

  		std::cout << "myvector contains:";
  		for (it=myvector.begin(); it<myvector.end(); it++)
    		std::cout << ' ' << *it;
  		std::cout << '\n';
		  std::cout << myvector.size() << std::endl;
	}
	std::cout << std::endl;
	{
  		vector<int> myvector;

  		// set some values (from 1 to 10)
  		for (int i=1; i<=10; i++) myvector.push_back(i);

  		// erase the 6th element
  		myvector.erase (myvector.begin()+5);

		std::cout << "myvector contains:";
  		for (unsigned i=0; i<myvector.size(); ++i)
    		std::cout << ' ' << myvector[i];
  		std::cout << '\n';

  		// erase the first 3 elements:
  		myvector.erase (myvector.begin()+3,myvector.begin()+6);

  		std::cout << "myvector contains:";
  		for (unsigned i=0; i<myvector.size(); ++i)
    		std::cout << ' ' << myvector[i];
  		std::cout << '\n';
	}
	std::cout << std::endl;
	{
		vector<int> myvector1;

  		// set some values (from 1 to 10)
  		for (int i=1; i<=10; i++) myvector1.push_back(i);
		vector<int> myvector2;

  		// set some values (from 1 to 10)
  		for (int i=1; i<=10; i++) myvector2.push_back(i);
		vector<vector<int> > myvector;
		myvector.push_back(myvector1);
		myvector.push_back(myvector2);
	}
	std::cout << std::endl;
	{
  		vector<int> foo (3,100);   // three ints with a value of 100
  		vector<int> bar (2,200);   // two ints with a value of 200

  		if (foo==bar) std::cout << "foo and bar are equal\n";
  		if (foo!=bar) std::cout << "foo and bar are not equal\n";
  		if (foo< bar) std::cout << "foo is less than bar\n";
  		if (foo> bar) std::cout << "foo is greater than bar\n";
  		if (foo<=bar) std::cout << "foo is less than or equal to bar\n";
  		if (foo>=bar) std::cout << "foo is greater than or equal to bar\n";
		
		std::cout << std::endl;
		vector<int> foo2 (2,200);   // three ints with a value of 100
  		vector<int> bar2 (2,200);   // two ints with a value of 200

  		if (foo2==bar2) std::cout << "foo2 and bar2 are equal\n";
  		if (foo2!=bar2) std::cout << "foo2 and bar2 are not equal\n";
  		if (foo2< bar2) std::cout << "foo2 is less than bar2\n";
  		if (foo2> bar2) std::cout << "foo2 is greater than bar2\n";
  		if (foo2<=bar2) std::cout << "foo2 is less than or equal to bar2\n";
  		if (foo2>=bar2) std::cout << "foo2 is greater than or equal to bar2\n";
	}
}
	