#ifndef VECTOR_HPP  
# define VECTOR_HPP

#include <memory>
#include <iterator>

namespace ft
{
    template <class T, class Alloc = std::allocator<T> > class vector
    {        
    /*
        MEMBER FUNCTIONS
        constructor
        destructor
        operator=
        get_allocator
    */
        public:
            typedef T                               value_type;
            typedef Alloc                           allocator_type;
            typedef typename Alloc::reference       reference;
            typedef typename Alloc::const_reference const_reference;
            typedef typename Alloc::pointer         pointer;
            typedef typename Alloc::const_pointer   const_pointer;
            typedef typename std::size_t            size_type;

            explicit vector(const allocator_type& alloc = allocator_type()) {
                _alloc = alloc;
                _size = 0;
                _array = _alloc.allocate(0);
                _capacity = 0;
            }

            explicit vector(size_type n, const value_type& val = value_type(),
                const allocator_type& alloc = allocator_type()) {
                _alloc = alloc;
                _capacity = _size;
                _array = alloc.allocate(_size);
                assign(n, val);
            }

            /*template <class InputIterator>
            vector<T>(InputIterator first, InputIterator last,
                const allocator_type& alloc = allocator_type()) {
                
            }*/

            ~vector(void) {
                for (size_type i(0); i < _size; i++)
                    _alloc.destroy(&_array[i]);
                _alloc.deallocate(_array, _capacity);
            }

            vector(const vector<T>& src) {
                *this = src;
            }
            vector& operator=(const vector<T>& rhs) {
                _alloc = rhs._alloc;
                _size = rhs._size;
                _capacity = rhs._capacity;
                _array = _alloc.allocate(_size);
                for (size_type i(0); i < _size; i++)
                    _alloc.construct(&_array[i], rhs[i]);
            }

            allocator_type get_allocator(void) const {
                return Alloc();
            }
        private :
            T*          _array;
            Alloc       _alloc;
            size_type   _size;
            size_type   _capacity;

            void    realloc(size_type n) {
                T*          tmp;
                Alloc       tmp_alloc;
                _capacity = n;

                if (_size > _capacity)
                    _capacity = _size;
                tmp = tmp_alloc.allocate(_capacity);
                for (size_type i(0); i < _size; i++)
                    tmp_alloc.construct(&tmp[i], _array[i]);

                for (size_type i(0); i < _size; i++)
                    _alloc.destroy(&_array[i]);
                _alloc.deallocate(_array, _capacity);

                _array = tmp;
                _alloc = tmp_alloc;
            }

            void    assign(const size_type n, const T& val) {
                size_type i(0);
                while (i < n) {
                    _alloc.construct(&_array[i], val);
                }
                _size = n;
            }


   /*
        ELEMENT ACCESS
        at *
        operator[] * 
        front *
        back *
    */
        public:
            reference          operator[](size_type n) {
                return (_array[n]);
            }

            const_reference          operator[](size_type n) const {
                return _array[n];
            }

            reference   at(size_type pos) {
                return _array[pos];
            }

            const_reference   at(size_type pos) const {
                return _array[pos];
            }

            reference   front() {
                return _array[0];
            }

            const_reference   front() const {
                return _array[0];
            }

            reference   back() {
                return _array[_size - 1];
            }

            
   /*
        ITERATORS
        begin
        end
        rbegin
        rend
    */

   /*
        CAPACITY
        empty *
        size *
        max_size *
        reserve * 
        capacity *
    */
            bool    empty() const {
                if (_size == 0)
                    return true;
                else
                    return false;
            }

            size_type   size() const {
                return _size;
            }

            size_type   max_size() const {
                return _alloc.max_size();
            }

            void    reserve(size_type n) {
                realloc(n);
            }

            size_type   capacity() const {
                return _capacity;
            }

   /*
        MODIFIERS
        assign
        clear *
        insert
        erase
        push_back *
        pop_back *
        resize *
        swap
    */
            void    clear() {
                for (size_type i(0); i < _size; i++) {
                    _alloc.destroy(&_array[i]);
                }
                _size = 0;
            }

            void    push_back (const value_type& val) {
                if (_size >= _capacity) {
                    _capacity *= 2;
                    realloc (_capacity);
                }
                _size++;
                _array[_size - 1] = val;
            }

            void    pop_back() {
                _alloc.destroy(&_array[_size - 1]);
                _size--;
            }

            void    resize(size_type n, value_type val = value_type()) {
                if (n < _size) {
                    for (size_type i(n); i <= _size; i++)
                        _alloc.destroy(&_array[i]);
                    _size = n;
                }
                if (n > _size) {
                    if (n > _capacity) {
                        realloc(n * 2);
                        _capacity = n * 2;
                    }
                    for (size_type i(_size); i < n; i++) {
                        push_back(val);
                    }
                    _size = n;
                }
            }
   
            class	OutOfRange: public std::exception {
		        public:
			    virtual const char* what() const throw() {
				    return ("\033[0;35m>>>EXCEPTION:\033[0mVector: Out of range");
			    }
	        };
    };
    /*
        NON MEMBER FUNCTIONS
        operator==
        operator!=
        operator<
        operator<=
        operator>=
        operator>=

        std::swap
    */
};

#endif