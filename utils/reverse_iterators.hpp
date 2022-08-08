#ifndef REVERSE_ITERATORS_HPP
# define REVERSE_ITERATORS_HPP

# include "iterator_traits.hpp"

namespace ft
{
	template <class Iterator>
	class  reverse_iterator {
		public :
		typedef Iterator												iterator_type;
		typedef typename iterator_traits<Iterator>::difference_type		difference_type;
		typedef typename iterator_traits<Iterator>::pointer				point;
		typedef typename iterator_traits<Iterator>::reference			reference;

		protected:
			Iterator    _point;


		public:
		//CONSTRUCTORS
	reverse_iterator( void ): _point()
	{
		//nothing here
	}

	explicit reverse_iterator( iterator_type x ): _point(x)
	{
		//nothing here
	}

	template<class U>
	reverse_iterator( const reverse_iterator<U> & x ): _point(x.base())
	{
		//nothing here
	}

	//DESTRUCTORS
	~reverse_iterator( void )
	{
		//nothing here
	}

	//ASSIGNATION OPERATOR OVERLOAD
	// template<class Iter>
	// reverse_iterator	operator=( const reverse_iterator<Iter> & rhs )
	// {
	// 	if (reinterpret_cast< const void * >(this) != reinterpret_cast< const void * >(&rhs))
	// 	{
	// 		_point = rhs.base();
	// 	}
	// 	return *this;
	// }

	//DEREFERENCING AS AN RVALUE
	reference		operator*( void ) const
	{
		Iterator	temp = _point;
		return *--temp;
	}

	point			operator->( void ) const
	{
		return &(operator*());
	}

	//INCREMENTATION AND DECREMENTATION OPERATORS
	reverse_iterator &		operator++( void )
	{
		--_point;
		return *this;
	}

	reverse_iterator		operator++( int )
	{
		reverse_iterator	copy(*this);

		--_point;
		return (copy);
	}

	reverse_iterator &		operator--( void )
	{
		++_point;
		return *this;
	}

	reverse_iterator		operator--( int )
	{
		reverse_iterator	copy(*this);

		++_point;
		return (copy);
	}

	//ARITHMETIC OPERATORS
	reverse_iterator		operator+( difference_type n ) const
	{
		reverse_iterator	temp(_point - n);
		return (temp);
	}

	reverse_iterator &		operator+=( difference_type n )
	{
		_point -= n;
		return *this;
	}

	reverse_iterator		operator-( difference_type n ) const
	{
		reverse_iterator	temp(_point + n);
		return (temp);
	}

	reverse_iterator &		operator-=( difference_type n )
	{
		_point += n;
		return *this;
	}

	//OFFSET DEREFERENCE OFFSET OPERATOR
	reference				operator[]( difference_type n ) const
	{
		return *(*this + n);
	}

	//BASE FUNCTION FOR NON-MEMBER FUNCTIONS TO GET ACCESS TO _ptr
	Iterator				base( void ) const
	{
		return _point;
	}

	//ALLOWING COMPARISON BETWEEN CONST AND NON-CONST REVERSE_ITERATOR
	operator reverse_iterator<const Iterator> () const
	{
		return (reverse_iterator<const Iterator>(_point));
	}
};

// NON-MEMBER EQUALITY/INEQUALITY COMPARISONS AND FUNCTIONS FOR 2 REVERSE_ITERATORS
template<typename Iterator>
bool			operator==(const reverse_iterator<Iterator> & lhs, const reverse_iterator<Iterator> & rhs)
{
	return (lhs.base() == rhs.base());
}

template<typename Iterator>
bool			operator!=(const reverse_iterator<Iterator> & lhs, const reverse_iterator<Iterator> & rhs)
{
	return (lhs.base() != rhs.base());
}

template<typename Iterator>
bool			operator<(const reverse_iterator<Iterator> & lhs, const reverse_iterator<Iterator> & rhs)
{
	return (lhs.base() > rhs.base());
}

template<typename Iterator>
bool			operator<=(const reverse_iterator<Iterator> & lhs, const reverse_iterator<Iterator> & rhs)
{
	return (!(rhs < lhs));
}

template<typename Iterator>
bool			operator>(const reverse_iterator<Iterator> & lhs, const reverse_iterator<Iterator> & rhs)
{
	return (rhs < lhs);
}

template<typename Iterator>
bool			operator>=(const reverse_iterator<Iterator> & lhs, const reverse_iterator<Iterator> & rhs)
{
	return (!(lhs < rhs));
}

// NON-MEMBER EQUALITY/INEQUALITY COMPARISONS AND FUNCTIONS FOR A REVERSE_ITERATOR AND A CONST REVERSE ITERATOR
template<typename Iter_lhs, typename Iter_rhs>
bool			operator==(const reverse_iterator<Iter_lhs> & lhs, const reverse_iterator<Iter_rhs> & rhs)
{
	return (lhs.base() == rhs.base());
}

template<typename Iter_lhs, typename Iter_rhs>
bool			operator!=(const reverse_iterator<Iter_lhs> & lhs, const reverse_iterator<Iter_rhs> & rhs)
{
	return (lhs.base() != rhs.base());
}

template<typename Iter_lhs, typename Iter_rhs>
bool			operator<(const reverse_iterator<Iter_lhs> & lhs, const reverse_iterator<Iter_rhs> & rhs)
{
	return (lhs.base() > rhs.base());
}

template<typename Iter_lhs, typename Iter_rhs>
bool			operator<=(const reverse_iterator<Iter_lhs> & lhs, const reverse_iterator<Iter_rhs> & rhs)
{
	return (!(rhs < lhs));
}

template<typename Iter_lhs, typename Iter_rhs>
bool			operator>(const reverse_iterator<Iter_lhs> & lhs, const reverse_iterator<Iter_rhs> & rhs)
{
	return (rhs < lhs);
}

template<typename Iter_lhs, typename Iter_rhs>
bool			operator>=(const reverse_iterator<Iter_lhs> & lhs, const reverse_iterator<Iter_rhs> & rhs)
{
	return (!(lhs < rhs));
}

template<class Iterator>
reverse_iterator<Iterator>								operator+(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator> & x)
{
	return (reverse_iterator<Iterator>(x.base() - n));
}

template<typename Iterator>
typename reverse_iterator<Iterator>::difference_type	operator-(const reverse_iterator<Iterator> & x, const reverse_iterator<Iterator> & y)
{
	return (y.base() - x.base());
}

template<typename Iter_lhs, typename Iter_rhs>
typename reverse_iterator<Iter_lhs>::difference_type	operator-(const reverse_iterator<Iter_lhs> & x, const reverse_iterator<Iter_rhs> & y)
{
	return (y.base() - x.base());
}

}; // end of namespace ft

#endif