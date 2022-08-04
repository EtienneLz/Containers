#ifndef BIDIRECTIONAL_ITERATOR_HPP
# define BIDIRECTIONAL_ITERATOR_HPP

# include "iterator_traits.hpp"
# include "red_black_tree.hpp"

namespace ft {
	
	/*template <class Key, class T>
	struct Node;
	template <class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator< Node<const Key, T> > >
	class RedBlackTree;*/

	template <typename T, typename node>
	class  bidirectional_iterator: iterator <bidirectional_iterator_tag, T> {
		public :
		typedef typename iterator<bidirectional_iterator_tag, T>::value_type		value_type;
		typedef ptrdiff_t                          									difference_type;
		typedef value_type*                               							pointer;
		typedef value_type&                               							reference;
		typedef typename iterator<bidirectional_iterator_tag, T>::iterator_category	iterator_category;

		private:
			node		*_point;

		public:
		bidirectional_iterator(void) {
			_point = NULL;
		}

		bidirectional_iterator(node *p) {
			_point = p;
		}

		~bidirectional_iterator() {}

		bidirectional_iterator(const bidirectional_iterator &src) {
			*this = src;
		}

		bidirectional_iterator& operator=(const bidirectional_iterator &rhs) {
			if (this != &rhs) {
				_point = rhs._point;
			}
			return *this;
		}

		bidirectional_iterator&   operator++() {
			_point = successor(_point);
			
			return *this;
		}

		bidirectional_iterator    operator++(int) {
			bidirectional_iterator tmp;
			tmp._point = _point;
			_point = successor(_point);
			return tmp;
		}

		bidirectional_iterator&   operator--() {
			_point = predecessor(_point);
			return *this;
		}

		bidirectional_iterator    operator--(int) {
			bidirectional_iterator tmp;
			tmp._point = _point;
			_point = predecessor(_point);

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

		friend bool        operator==(const bidirectional_iterator<T, node> &lhs, const bidirectional_iterator<T, node> &rhs) {
			return lhs._point == rhs._point;
		}

		friend bool        operator!=(const bidirectional_iterator<T, node> &lhs, const bidirectional_iterator<T, node> &rhs) {
			return lhs._point != rhs._point;
		}
	};

	template <typename T>
	class  const_bidirectional_iterator {
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
			}
			return *this;
		}

		const_bidirectional_iterator&   operator++() {
			if (_point->right == NULL && _point->left == NULL)
				return NULL;
			_point = successor(_point);
			return *this;
		}

		const_bidirectional_iterator    operator++(int) {
			pointer tmp;
			tmp = _point;
			_point = successor(_point);

			return tmp;
		}

		const_bidirectional_iterator&   operator--() {
			_point = predecessor(_point);
			return *this;
		}

		const_bidirectional_iterator    operator--(int) {
			pointer tmp;
			tmp = _point;
			_point = predecessor(_point);

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