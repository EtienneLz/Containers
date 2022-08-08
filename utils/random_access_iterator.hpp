#ifndef RANDOM_ACCESS_ITERATOR_HPP
# define RANDOM_ACCESS_ITERATOR_HPP

# include "iterator_traits.hpp"

namespace ft {
	template <class T>
	struct  random_access_iterator: iterator < random_access_iterator_tag, T > {
		public :
		typedef typename iterator<random_access_iterator_tag, T>::value_type										value_type;
		typedef ptrdiff_t                          	difference_type;
		typedef T*                                 	pointer;
		typedef T&                                 	reference;
		typedef typename iterator<random_access_iterator_tag, T>::iterator_category			iterator_category;

		private:
			pointer    _point;


		public:
		random_access_iterator(void): _point() {}

		random_access_iterator(pointer p) {
			_point = p;
		}

		~random_access_iterator() {}

		random_access_iterator(const random_access_iterator &src): _point(src._point) {}

		random_access_iterator& operator=(const random_access_iterator &rhs) {
			if (this != &rhs)
				_point = rhs._point;
			return *this;
		}

		operator random_access_iterator<const T> () const
		{
			return random_access_iterator<const T>(_point);
		}

		random_access_iterator&   operator++() {
			_point++;
			return *this;
		}

		random_access_iterator    operator++(int) {
			pointer tmp;
			tmp = _point;
			_point++;

			return tmp;
		}

		random_access_iterator&   operator--() {
			this->_point--;
			return *this;
		}

		random_access_iterator    operator--(int) {
			pointer tmp;
			tmp = _point;
			this->_point--;

			return tmp;
		}

		random_access_iterator&   operator+=(difference_type n) {
			_point += n;
			return *this;
		}

		random_access_iterator&   operator-=(difference_type n) {
			_point -= n;
			return *this;
		}

		random_access_iterator   operator+(difference_type n) const {
			random_access_iterator tmp(_point + n);
			return tmp;
		}

		random_access_iterator   operator-(difference_type n) const {
			random_access_iterator tmp(_point - n);
			return tmp;
		}

		reference   operator[](const int n) const {
			return _point[n];
		}

		pointer     operator->() const {
			return _point;
		}

		reference   operator*() const {
			return *_point;
		}

		T*			base( void ) const
		{
			return _point;
		}
	};
	
template<typename T>
bool				operator==( const random_access_iterator<T> & lhs, const random_access_iterator<T> & rhs )
{
	return (lhs.base() == rhs.base());
}

//POLYMORPHISM FRO ITERATOR VS CONST ITERATOR COMPARISONS
template<typename T_lhs, typename T_rhs>
bool				operator==( const random_access_iterator<T_lhs> & lhs, const random_access_iterator<T_rhs> & rhs )
{
	return (lhs.base() == rhs.base());
}

template<typename T>
bool				operator!=( const random_access_iterator<T> & lhs, const random_access_iterator<T> & rhs )
{
	return (lhs.base() != rhs.base());
}

template<typename T_lhs, typename T_rhs>
bool				operator!=( const random_access_iterator<T_lhs> & lhs, const random_access_iterator<T_rhs> & rhs )
{
	return (lhs.base() != rhs.base());
}

template<typename T>
bool				operator<( const random_access_iterator<T> & lhs, const random_access_iterator<T> & rhs ) 
{
	return (lhs.base() < rhs.base());
}

template<typename T_lhs, typename T_rhs>
bool				operator<( const random_access_iterator<T_lhs> & lhs, const random_access_iterator<T_rhs> & rhs )
{
	return (lhs.base() < rhs.base());
}

template<typename T>
bool				operator<=( const random_access_iterator<T> & lhs, const random_access_iterator<T> & rhs )
{
	return (lhs.base() <= rhs.base());
}

template<typename T_lhs, typename T_rhs>
bool				operator<=( const random_access_iterator<T_lhs> & lhs, const random_access_iterator<T_rhs> & rhs )
{
	return (lhs.base() <= rhs.base());
}

template<typename T>
bool				operator>( const random_access_iterator<T> & lhs, const random_access_iterator<T> & rhs )
{
	return (lhs.base() > rhs.base());
}

template<typename T_lhs, typename T_rhs>
bool				operator>( const random_access_iterator<T_lhs> & lhs, const random_access_iterator<T_rhs> & rhs )
{
	return (lhs.base() > rhs.base());
}

template<typename T>
bool				operator>=( const random_access_iterator<T> & lhs, const random_access_iterator<T> & rhs )
{
	return (lhs.base() >= rhs.base());
}

template<typename T_lhs, typename T_rhs>
bool				operator>=( const random_access_iterator<T_lhs> & lhs, const random_access_iterator<T_rhs> & rhs )
{
	return (lhs.base() >= rhs.base());
}

// Operation overloads for additions and substractions
template <typename T>
random_access_iterator<T>		operator+( typename random_access_iterator<T>::difference_type n, typename ft::random_access_iterator<T> & rhs )
{
	return (rhs + n);
}

template <typename T>
typename random_access_iterator<T>::difference_type		operator-( const random_access_iterator<T> lhs, const random_access_iterator<T> rhs )
{
	return (lhs.base() - rhs.base());
}

template <typename T_lhs, typename T_rhs>
typename random_access_iterator<T_lhs>::difference_type		operator-( const random_access_iterator<T_lhs> lhs, const random_access_iterator<T_rhs> rhs )
{
	return (lhs.base() - rhs.base());
}

	typedef ptrdiff_t   difference_type;

	template<typename InputIterator>
	difference_type distance(const InputIterator first, const InputIterator last) {
		difference_type i = 0;
		for (InputIterator it(first); it != last; it++) i++;
		return i;
	}

};
 
#endif