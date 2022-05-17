#ifndef VECTOR_HPP  
# define VECTOR_HPP

#include <memory>

namespace ft
{
    template <class T, class Alloc = std::allocator<T>> class vector
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

            explicit vector<T>(const allocator_type& alloc = allocator_type()) {
                _alloc = alloc;
                _size = 0;
                _array = _alloc.allocate(0);
                _capacity = 0;
            }

            explicit vector<T>(size_type n, const value_type& val = value_type(),
                const allocator_type& alloc = allocator_type()) {
                _alloc = alloc;
                _capacity = _size;
                _array = alloc.allocate(_size);
                assign(n, val);
            }

            template <class InputIterator>
            vector<T>(InputIterator first, InputIterator last,
                const allocator_type& alloc = allocator_type()) {
                
            }

            ~vector<T>(void) {
                for (size_type i(0); i < _size; i++)
                    _alloc.destroy(_array[i]);
                _alloc.deallocate(_array, _capacity);
            }

            vector<T>(const vector<T>& src) {
                *this = src;
            }
            vector<T>& operator=(const vector<T>& rhs) {
                _alloc = rhs._alloc;
                _size = rhs._size;
                _capacity = rhs._capacity;
                _array = _alloc.allocate(_size);
                for (size_type i(0); i < _size; i++)
                    _alloc.construct(&_array, rhs[i]);
            }

            allocator_type get_allocator(void) const {
                return Alloc();
            }
        private :
            T*          _array;
            Alloc       _alloc;
            size_type   _size;
            size_type   _capacity;

            assign(const size_type n, const T& val) {
                size_type i(0);
                while (i < n) {
                    _alloc.construct(&_array, val);
                }
                _size = n;
            }


   /*
        ELEMENT ACCESS
        at
        operator[]
        front
        back
        data
    */
        public:
            reference   at(size_type pos) {
                if (pos >= _size)
                    throw ::OutOfRange();
                return _array[pos];
            }

            const_reference   at(size_type pos) const {
        
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
        empty
        size *
        max_size *
        reserve
        capacity *
    */


            size_type   size() const {
                return _size;
            }

            size_type   max_size() const {
                return _alloc.max_size();
            }

            size_type   capacity() const {
                return _capacity;
            }

   /*
        MODIFIERS
        clear
        insert
        erase
        push_back
        pop_back
        resize
        swap
    */

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
            class	OutOfRange: public std::exception {
		        public:
			    virtual const char* what() const throw() {
				    return ("\033[0;35m>>>EXCEPTION:\033[0mVector: Out of range");
			    }
	        };
    };
    
};

#endif