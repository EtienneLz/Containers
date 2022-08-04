#ifndef RANDOM_ACCESS_ITERATOR_HPP
# define RANDOM_ACCESS_ITERATOR_HPP

# include "iterator_traits.hpp"

namespace ft {
	template <class T>
	struct  random_access_iterator {
		public :
		typedef T									value_type;
		typedef ptrdiff_t                          	difference_type;
		typedef T*                                 	pointer;
		typedef T&                                 	reference;
		typedef random_access_iterator_tag			iterator_category;

		private:
			pointer    _point;


		public:
		random_access_iterator(void) {
			_point = NULL;
		}

		random_access_iterator(pointer p) {
			_point = p;
		}

		~random_access_iterator() {}

		random_access_iterator(const random_access_iterator &src) {
			*this = src;
		}

		random_access_iterator& operator=(const random_access_iterator &rhs) {
			if (this != &rhs)
				_point = rhs._point;
			return *this;
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
			_point--;
			return *this;
		}

		random_access_iterator    operator--(int) {
			pointer tmp;
			tmp = _point;
			_point--;

			return tmp;
		}

		random_access_iterator&   operator+=(int n) {
			_point + n;
			return *this;
		}

		random_access_iterator&   operator-=(int n) {
			_point - n;
			return *this;
		}

		random_access_iterator   operator+(difference_type n) const {
			return random_access_iterator(_point + n);
		}

		random_access_iterator   operator-(int n) {
			return random_access_iterator(_point - n);
		}

		reference   operator[](const int n) const {
			return _point[n];
		}

		pointer     operator->() {
			return _point;
		}

		const pointer     operator->() const {
			return _point;
		}

		reference   operator*() {
			return *_point;
		}

		friend bool        operator==(const random_access_iterator<T> &lhs, const random_access_iterator<T> &rhs) {
			return lhs._point == rhs._point;
		}

		friend bool        operator!=(const random_access_iterator<T> &lhs, const random_access_iterator<T> &rhs) {
			return lhs._point != rhs._point;
		}

		friend bool        operator>(const random_access_iterator<T> &lhs, const random_access_iterator<T> &rhs) {
			return lhs._point > rhs._point;
		}

		friend bool        operator>=(const random_access_iterator<T> &lhs, const random_access_iterator<T> &rhs) {
			return lhs._point >= rhs._point;
		}

		friend bool        operator<(const random_access_iterator<T> &lhs, const random_access_iterator<T> &rhs) {
			return lhs._point < rhs._point;
		}

		friend bool        operator<=(const random_access_iterator<T> &lhs, const random_access_iterator<T> &rhs) {
			return lhs._point <= rhs._point;
		}
	};

	template <class T>
	struct  const_random_access_iterator {
		public :
		typedef T                                  	value_type;
		typedef ptrdiff_t                          	difference_type;
		typedef T*                                 	pointer;
		typedef T&                                 	reference;
		typedef random_access_iterator_tag    		iterator_category;

		private:
			pointer    _point;


		public:
		const_random_access_iterator(void) {
			_point = NULL;
		}

		const_random_access_iterator(pointer p) {
			_point = p;
		}

		~const_random_access_iterator() {}

		const_random_access_iterator(const const_random_access_iterator<T> &src) {
			*this = src;
		}

		const_random_access_iterator& operator=(const const_random_access_iterator<T> &rhs) {
			if (this != &rhs)
				_point = rhs._point;
			return *this;
		}

		const_random_access_iterator&   operator++() {
			_point++;
			return *this;
		}

		const_random_access_iterator    operator++(int) {
			pointer tmp;
			tmp = _point;
			_point++;

			return tmp;
		}

		const_random_access_iterator&   operator--() {
			_point--;
			return *this;
		}

		const_random_access_iterator    operator--(int) {
			pointer tmp;
			tmp = _point;
			_point--;

			return tmp;
		}

		const_random_access_iterator&   operator+=(int n) {
			_point + n;
			return *this;
		}

		const_random_access_iterator&   operator-=(int n) {
			_point - n;
			return *this;
		}

		const_random_access_iterator   operator+(difference_type n) const {
			return const_random_access_iterator(_point + n);
		}

		const_random_access_iterator   operator-(int n) {
			return const_random_access_iterator(_point - n);
		}

		reference   operator[](const int n) const {
			return _point[n];
		}

		pointer     operator->() {
			return _point;
		}

		const pointer     operator->() const {
			return _point;
		}

		reference   operator*() {
			return *_point;
		}

		friend bool        operator==(const const_random_access_iterator<T> &lhs, const const_random_access_iterator<T> &rhs) {
			return lhs._point == rhs._point;
		}

		friend bool        operator!=(const const_random_access_iterator<T> &lhs, const const_random_access_iterator<T> &rhs) {
			return lhs._point != rhs._point;
		}

		friend bool        operator>(const const_random_access_iterator<T> &lhs, const const_random_access_iterator<T> &rhs) {
			return lhs._point > rhs._point;
		}

		friend bool        operator>=(const const_random_access_iterator<T> &lhs, const const_random_access_iterator<T> &rhs) {
			return lhs._point >= rhs._point;
		}

		friend bool        operator<(const const_random_access_iterator<T> &lhs, const const_random_access_iterator<T> &rhs) {
			return lhs._point < rhs._point;
		}

		friend bool        operator<=(const const_random_access_iterator<T> &lhs, const const_random_access_iterator<T> &rhs) {
			return lhs._point <= rhs._point;
		}
	};

	
	typedef ptrdiff_t   difference_type;

	template<typename InputIterator>
	difference_type distance(const InputIterator first, const InputIterator last) {
		difference_type i = 0;
		for (InputIterator it(first); it != last; it++) i++;
		return i;
	}

};
 
#endif