#include "../vector.hpp"
#include <vector>
#include <iterator>
#include <iostream>
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <list>

#ifndef STD
# define NAMESPACE ft
#else
# define NAMESPACE std
#endif


using namespace NAMESPACE;

#define NB_OF_ELEMENTS 1000000
#define FALSE 0

unsigned long int	chrono_init(void)
{
	struct timeval		tv;
	unsigned long int	start_time;

	gettimeofday(&tv, NULL);
	start_time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (start_time);
}
 
unsigned long int	stamp_time(unsigned long int start_time)
{
	unsigned long int	actual_time;
	struct timeval		tv;

	gettimeofday(&tv, NULL);
	actual_time = (tv.tv_sec * 1000 + tv.tv_usec / 1000) - start_time;
	return (actual_time);
}

void constructor_bench()
{
    vector<std::string> *test;
    for (int i = 0; i < NB_OF_ELEMENTS; i++)
    {
        test = new vector<std::string>;
        delete test;
    }
    for (int i = 0; i < NB_OF_ELEMENTS; i++)
    {
        test = new vector<std::string>(10, "blop");
        delete test;
    }

    std::list<std::string> just_a_list(15, "youhoo");
    for (int i = 0; i < NB_OF_ELEMENTS; i++)
    {
        test = new vector<std::string>(just_a_list.begin(), just_a_list.end());
        delete test;
    }
    vector<std::string> little_things_in(15, "gift");
    for (int i = 0; i < NB_OF_ELEMENTS; i++)
    {
        test = new vector<std::string>(little_things_in);
        delete test;
    }
}

void operator_assign()
{
    vector<std::string> test;
    for (int i = 0; i < NB_OF_ELEMENTS; i++)
        test.push_back("miaou");
    vector<std::string> ditto;
    ditto = test;
}

void resize_bench()
{
    vector<std::string> test;
    for (int i = 0; i < NB_OF_ELEMENTS; i++)
        test.resize(i);
    for (int i = NB_OF_ELEMENTS; i >= 0; i--)
        test.resize(i);
}

void reserve_bench()
{
    vector<std::string> test;
    for (int i = 0; i < NB_OF_ELEMENTS; i++)
        test.reserve(i);
}

void crochet_bench()
{
    vector<std::string> test;
    for (int i = 0; i < NB_OF_ELEMENTS; i++)
        test.push_back("miaou");
    for (int i = 0; i < NB_OF_ELEMENTS; i++)
        test[i] = "waf";
}

void assign_bench()
{
    vector<std::string> test;

    test.assign(NB_OF_ELEMENTS,  "welcome");
    test.assign(NB_OF_ELEMENTS,  "welcome");
    vector<std::string> test2;
    for (int i = 0; i < 20;i++)
    {
        test2.assign(test.begin(),  test.end());
        test.assign(test2.begin(), test2.end());
    }
}

void push_pop_back_bench()
{
    vector<std::string> test;

    for (int i = 0; i < NB_OF_ELEMENTS * 2;i++)
        test.push_back("sameastheprevious");
    for (int i = 0; i < NB_OF_ELEMENTS;i++)
        test.pop_back();
}

void insert_bench()
{
    vector<std::string> test;

    for (int i = 0; i < 15000 ;i++)
        test.insert(test.begin() + i/2 , "sameastheprevious");
    test.clear();
    for (int i = 0; i < 5000 ;i++)
        test.insert(test.begin() + i/2 , 3 ,"sameastheprevious");
    vector<std::string> test2;
    for (int i = 0; i < 5000 ;i++)
        test2.insert(test2.begin() + i/2 , test.begin() , test.begin() + 3);
}

void swap_bench()
{
    vector<std::string> swap_a(100, "opop");
    vector<std::string> swap_b(100, "ploup");

    for (int i = 0; i < NB_OF_ELEMENTS ;i++)
        swap_a.swap(swap_b);
}
int main()
{
	size_t start = chrono_init();
    /*constructor_bench();
    operator_assign();*/
    //resize_bench();
    /*reserve_bench();
    crochet_bench();
    assign_bench();
    push_pop_back_bench();
    swap_bench();*/
    insert_bench();
	std::cout << stamp_time(start) <<  "ms" <<std::endl;
}
