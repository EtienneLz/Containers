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
	reverse_iterator( void ): _point() {}

	explicit reverse_iterator( iterator_type x ): _point(x) {}

	template<class U>
	reverse_iterator( const reverse_iterator<U> & x ): _point(x.base()) {}

	~reverse_iterator( void ) {}

	reference		operator*( void ) const
	{
		Iterator	temp = _point;
		return *--temp;
	}

	point			operator->( void ) const
	{
		return &(operator*());
	}

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

	reference				operator[]( difference_type n ) const
	{
		return *(*this + n);
	}

	Iterator				base( void ) const
	{
		return _point;
	}

	operator reverse_iterator<const Iterator> () const
	{
		return (reverse_iterator<const Iterator>(_point));
	}
};

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

};

#endif