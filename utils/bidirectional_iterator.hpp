#ifndef BIDIRECTIONAL_ITERATOR_HPP
# define BIDIRECTIONAL_ITERATOR_HPP

# include "iterator_traits.hpp"
# include "red_black_tree.hpp"

namespace ft {
	template <class Node, class Tree>
	struct  bidirectional_iterator {
		public :
		typedef Node								value_type;
		typedef ptrdiff_t                          	difference_type;
		typedef Node*                               pointer;
		typedef Node&                               reference;
		typedef bidirectional_iterator_tag			iterator_category;

		private:
			pointer		_point;
			Tree		*_tree;


		public:
		bidirectional_iterator(void) {
			_point = NULL;
		}

		bidirectional_iterator(pointer p, Tree *tree) {
			_point = p;
			_tree = tree;
		}

		~bidirectional_iterator() {}

		bidirectional_iterator(const bidirectional_iterator &src) {
			*this = src;
		}

		bidirectional_iterator& operator=(const bidirectional_iterator &rhs) {
			if (this != &rhs) {
				_point = rhs._point;
				_tree = rhs._tree;
			}
			return *this;
		}

		bidirectional_iterator&   operator++() {
			_point = _tree.successor(_point);
			return *this;
		}

		bidirectional_iterator    operator++(int) {
			pointer tmp;
			tmp = _point;
			_point = _tree.successor(_point);

			return tmp;
		}

		bidirectional_iterator&   operator--() {
			_point = _tree.predecessor(_point);
			return *this;
		}

		bidirectional_iterator    operator--(int) {
			pointer tmp;
			tmp = _point;
			_point = _tree.predecessor(_point);

			return tmp;
		}

		pointer     operator->() {
			return &_point->data;
		}

		const pointer     operator->() const {
			return &_point->data;
		}

		reference   operator*() {
			return _point->data;
		}

		friend bool        operator==(const bidirectional_iterator<T> &lhs, const bidirectional_iterator<T> &rhs) {
			return lhs._point == rhs._point;
		}

		friend bool        operator!=(const bidirectional_iterator<T> &lhs, const bidirectional_iterator<T> &rhs) {
			return lhs._point != rhs._point;
		}
	};

	template <class T>
	struct  const_bidirectional_iterator {
		public :
		typedef T                                  	value_type;
		typedef ptrdiff_t                          	difference_type;
		typedef T*                                 	pointer;
		typedef T&                                 	reference;
		typedef random_access_iterator_tag    		iterator_category;

		private:
			pointer    _point;


		public:
		const_bidirectional_iterator(void) {
			_point = NULL;
		}

		const_bidirectional_iterator(pointer p) {
			_point = p;
		}

		~const_bidirectional_iterator() {}

		const_bidirectional_iterator(const const_bidirectional_iterator<T> &src) {
			*this = src;
		}

		const_bidirectional_iterator& operator=(const const_bidirectional_iterator<T> &rhs) {
			if (this != &rhs) {
				_point = rhs._point;
				_tree = rhs._tree;
			}
			return *this;
		}

		const_bidirectional_iterator&   operator++() {
			_point = _tree.successor(_point);
			return *this;
		}

		const_bidirectional_iterator    operator++(int) {
			pointer tmp;
			tmp = _point;
			_point = _tree.successor(_point);

			return tmp;
		}

		const_bidirectional_iterator&   operator--() {
			_point = _tree.predecessor(_point);
			return *this;
		}

		const_bidirectional_iterator    operator--(int) {
			pointer tmp;
			tmp = _point;
			_point = _tree.predecessor(_point);

			return tmp;
		}

		pointer     operator->() {
			return &_point->data;
		}

		const pointer     operator->() const {
			return &_point->data;
		}

		reference   operator*() {
			return _point->data;
		}

		friend bool        operator==(const const_bidirectional_iterator<T> &lhs, const const_bidirectional_iterator<T> &rhs) {
			return lhs._point == rhs._point;
		}

		friend bool        operator!=(const const_bidirectional_iterator<T> &lhs, const const_bidirectional_iterator<T> &rhs) {
			return lhs._point != rhs._point;
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