#ifndef IS_INTEGRAL_HPP
# define IS_INTEGRAL_HPP

namespace ft {
template <class T, T v>
struct integral_constant
{
    static const bool           value = v;
    typedef T          value_type;
    typedef integral_constant<T, v>   type;
    bool operatorT() {return v;}
};

typedef integral_constant<bool, true> true_type;
typedef integral_constant<bool, false> false_type;

template <class T>
struct is_integral : public false_type{};

template<> struct is_integral<unsigned int> : public true_type{};
template<> struct is_integral<char> : public true_type{};
template<> struct is_integral<int> : public true_type{};
template<> struct is_integral<signed char> : public true_type{};
template<> struct is_integral<bool> : public true_type{};
template<> struct is_integral<long> : public true_type{};
template<> struct is_integral<long long> : public true_type{};
template<> struct is_integral<unsigned long> : public true_type{};
template<> struct is_integral<unsigned long long> : public true_type{};
template<> struct is_integral<short int> : public true_type{};
template<> struct is_integral<unsigned short int> : public true_type{};



};

#endif