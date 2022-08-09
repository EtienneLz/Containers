#ifndef BIDIRECTIONAL_ITERATOR_HPP
# define BIDIRECTIONAL_ITERATOR_HPP

# include "iterator_traits.hpp"
# include "red_black_tree.hpp"

namespace ft {
	template <typename T, typename node>
	class  bidirectional_iterator: iterator <bidirectional_iterator_tag, T> {
		public :
		typedef typename iterator<bidirectional_iterator_tag, T>::value_type		value_type;
		typedef ptrdiff_t                          									difference_type;
		typedef value_type*                               							pointer;
		typedef value_type&                               							reference;
		typedef typename iterator<bidirectional_iterator_tag, T>::iterator_category	iterator_category;

		protected:
			node		*_point;

		public:
		bidirectional_iterator(void): _point() {}

		bidirectional_iterator(node *p) {
			_point = p;
		}

		~bidirectional_iterator() {}

		bidirectional_iterator(const bidirectional_iterator &src): _point(src._point) {}

		operator bidirectional_iterator<const T, node>() const {
			return (bidirectional_iterator<const T, node>(_point));
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
			bidirectional_iterator tmp(*this);
			_point = predecessor(_point);

			return tmp;
		}

		reference   operator*() const {
			return _point->data;
		}

		pointer     operator->() const {
			return &(this->operator*());
		}

		bool	operator==(const bidirectional_iterator & rhs) {
			return (_point == rhs._point);
		}

		bool	operator!=(const bidirectional_iterator & rhs) {
			return (_point != rhs._point);
		}

		pointer	base(void) const {
			return _point;
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