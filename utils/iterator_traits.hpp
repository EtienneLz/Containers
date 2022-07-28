#ifndef ITERATOR_TRAITS_HPP
# define ITERATOR_TRAITS_HPP

#include <cstddef> 

namespace ft
{

template < class Category, class T, class Distance = std::ptrdiff_t, class Pointer = T*, class Reference = T& >
struct iterator
{
	typedef Category	iterator_category;
	typedef T			value_type;
	typedef Distance	difference_type;
	typedef Pointer		pointer;
	typedef Reference	reference;
};

struct	input_iterator_tag {};
struct	output_iterator_tag {};
struct	forward_iterator_tag : public input_iterator_tag {};
struct	bidirectional_iterator_tag : public forward_iterator_tag {};
struct	random_access_iterator_tag : public bidirectional_iterator_tag {};

template < class iterator >
struct iterator_traits
{
	typedef typename iterator::difference_type			difference_type;
	typedef typename iterator::value_type				value_type;
	typedef typename iterator::pointer					pointer;
	typedef typename iterator::reference				reference;
	typedef typename iterator::iterator_category		iterator_category;
};

template < class T >
struct iterator_traits< T* >
{
	typedef std::ptrdiff_t					difference_type;
	typedef T								value_type;
	typedef T*								pointer;
	typedef T&								reference;
	typedef random_access_iterator_tag		iterator_category;
};

template < class T >
struct iterator_traits < const T* >
{
	typedef std::ptrdiff_t					difference_type;
	typedef T								value_type;
	typedef const T*						pointer;
	typedef const T&						reference;
	typedef random_access_iterator_tag		iterator_category;
};
}

#endif


// needed for ptrdif_t type definition

namespace ft
{



}