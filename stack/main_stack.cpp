
#include <stack>

#include "../stack.hpp"

#ifndef STD
# define NAMESPACE ft
#else
# define NAMESPACE std
#endif

using namespace NAMESPACE;

int main(void) {
std::cout << std::endl << "=====STACK TEST=====" << std::endl;
	{
  		stack<int> mystack;
  		int sum (0);

  		for (int i=1;i<=10;i++) mystack.push(i);

  		while (!mystack.empty())
  		{
     		sum += mystack.top();
    		mystack.pop();
  		}

  		std::cout << "total: " << sum << '\n';
	}
	std::cout << std::endl;
	{
  		stack<int> myints;
  		std::cout << "0. size: " << myints.size() << '\n';

  		for (int i=0; i<5; i++) myints.push(i);
  		std::cout << "1. size: " << myints.size() << '\n';

  		myints.pop();
  		std::cout << "2. size: " << myints.size() << '\n';
	}
	std::cout << std::endl;
	{
  		stack<int> mystack;

  		mystack.push(10);
  		mystack.push(20);

  		mystack.top() -= 5;

  		std::cout << "mystack.top() is now " << mystack.top() << '\n';
}
	std::cout << std::endl;
	{
  		stack<int> mystack;

  		for (int i=0; i<5; ++i) mystack.push(i);

  		std::cout << "Popping out elements...";
  		while (!mystack.empty())
  		{
     		std::cout << ' ' << mystack.top();
     		mystack.pop();
  		}
  		std::cout << '\n';
	}
	std::cout << std::endl;
	{
  		stack<int> foo;   // three ints with a value of 100
  		stack<int> bar;   // two ints with a value of 200

		foo.push(1);
		foo.push(2);
		foo.push(3);
		bar.push(4);
		bar.push(5);
		bar.push(6);

  		if (foo==bar) std::cout << "foo and bar are equal\n";
  		if (foo!=bar) std::cout << "foo and bar are not equal\n";
  		if (foo< bar) std::cout << "foo is less than bar\n";
  		if (foo> bar) std::cout << "foo is greater than bar\n";
  		if (foo<=bar) std::cout << "foo is less than or equal to bar\n";
  		if (foo>=bar) std::cout << "foo is greater than or equal to bar\n";
		
		std::cout << std::endl;
		stack<int> foo2;   // three ints with a value of 100
  		stack<int> bar2;   // two ints with a value of 200

		foo2.push(1);
		foo2.push(2);
		foo2.push(3);
		bar2.push(1);
		bar2.push(2);
		bar2.push(3);

  		if (foo2==bar2) std::cout << "foo2 and bar2 are equal\n";
  		if (foo2!=bar2) std::cout << "foo2 and bar2 are not equal\n";
  		if (foo2< bar2) std::cout << "foo2 is less than bar2\n";
  		if (foo2> bar2) std::cout << "foo2 is greater than bar2\n";
  		if (foo2<=bar2) std::cout << "foo2 is less than or equal to bar2\n";
  		if (foo2>=bar2) std::cout << "foo2 is greater than or equal to bar2\n";
	}
	std::cout << std::endl;
}