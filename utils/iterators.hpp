#ifndef ITERATOR_HPP
# define ITERATOR_HPP

#include <cstddef>

namespace ft {
    template <class T>
    class  iterator {
        public :
        typedef T                                  value_type;
        typedef ptrdiff_t                          difference_type;
        typedef T*                                 pointer;
        typedef T&                                 reference;
        typedef std::random_access_iterator_tag    iterator_category;

        private:
            pointer    _point;


        public:
        iterator(void) {
            _point = NULL;
        }

        iterator(pointer p) {
            _point = p;
        }

        ~iterator() {}

        iterator(const iterator &src) {
            *this = src;
        }

        iterator& operator=(const iterator &rhs) {
            if (this != &rhs)
                _point = rhs._point;
            return *this;
        }

        iterator&   operator++() {
            _point++;
            return *this;
        }

        iterator    operator++(int) {
            pointer tmp;
            tmp = _point;
            _point++;

            return tmp;
        }

        iterator&   operator--() {
            _point--;
            return *this;
        }

        iterator    operator--(int) {
            pointer tmp;
            tmp = _point;
            _point--;

            return tmp;
        }

        iterator&   operator+=(int n) {
            _point + n;
            return *this;
        }

        iterator&   operator-=(int n) {
            _point - n;
            return *this;
        }

        iterator   operator+(difference_type n) const {
            return iterator(_point + n);
        }

        iterator   operator-(int n) {
            return iterator(_point - n);
        }

        reference   operator[](const int n) const {
            return _point[n];
        }

        pointer     operator->() {
            return _point;
        }

        reference   operator*() {
            return *_point;
        }

        friend bool        operator==(const iterator<T> &lhs, const iterator<T> &rhs) {
            return lhs._point == rhs._point;
        }

        friend bool        operator!=(const iterator<T> &lhs, const iterator<T> &rhs) {
            return lhs._point != rhs._point;
        }

        friend bool        operator>(const iterator<T> &lhs, const iterator<T> &rhs) {
            return lhs._point > rhs._point;
        }

        friend bool        operator>=(const iterator<T> &lhs, const iterator<T> &rhs) {
            return lhs._point >= rhs._point;
        }

        friend bool        operator<(const iterator<T> &lhs, const iterator<T> &rhs) {
            return lhs._point < rhs._point;
        }

        friend bool        operator<=(const iterator<T> &lhs, const iterator<T> &rhs) {
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