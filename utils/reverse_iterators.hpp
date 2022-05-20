#ifndef REVERSE_ITERATORS_HPP
# define REVERSE_ITERATORS_HPP

namespace ft
{
    template <class T>
    class  reverse_iterator {
        public :
        typedef T                                  value_type;
        typedef ptrdiff_t                          difference_type;
        typedef T*                                 pointer;
        typedef T&                                 reference;
        typedef std::random_access_iterator_tag    iterator_category;

        private:
            pointer    _point;


        public:
        reverse_iterator(void) {
            _point = NULL;
        }

        reverse_iterator(pointer p) {
            _point = p;
        }

        ~reverse_iterator() {}

        reverse_iterator(const reverse_iterator &src) {
            *this = src;
        }

        reverse_iterator operator=(const reverse_iterator &rhs) {
            if (this != &rhs)
                _point = rhs._point;
            return *this;
        }

        reverse_iterator&   operator++() {
            _point--;
            return *this;
        }

        reverse_iterator    operator++(int) {
            pointer tmp;
            tmp = _point;
            _point--;

            return tmp;
        }

        reverse_iterator&   operator--() {
            _point++;
            return *this;
        }

        reverse_iterator    operator--(int) {
            pointer tmp;
            tmp = _point;
            _point++;

            return tmp;
        }

        reverse_iterator&   operator+=(difference_type n) {
            _point + n;
            return *this;
        }

        reverse_iterator&   operator-=(difference_type n) {
            _point - n;
            return *this;
        }

        reverse_iterator   operator+(difference_type n) {
            return reverse_iterator(_point + n);
        }

        reverse_iterator   operator-(difference_type n) {
            return reverse_iterator(_point - n);
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

        bool        operator==(const reverse_iterator<T> rhs) {
            return _point == rhs._point;
        }

        bool        operator!=(const reverse_iterator<T> rhs) {
            return _point != rhs._point;
        }

        bool        operator>(const reverse_iterator<T> rhs) {
            return _point > rhs._point;
        }

        bool        operator>=(const reverse_iterator<T> rhs) {
            return _point >= rhs._point;
        }

        bool        operator<(const reverse_iterator<T> rhs) {
            return _point < rhs._point;
        }

        bool        operator<=(const reverse_iterator<T> rhs) {
            return _point <= rhs._point;
        }
    };
};

#endif