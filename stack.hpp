#ifndef stack_HPP  
# define stack_HPP

# include <memory>
# include <iostream>
# include "vector.hpp"
# include "utils/iterators.hpp"
# include "utils/reverse_iterators.hpp"
# include "utils/enable_if.hpp"
# include "utils/is_integral.hpp"
# include "utils/lexicographical_compare.hpp"

namespace ft
{
    template <class T, class Container = ft::vector<T> > class stack
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
            typedef Container                       container_type;
            typedef typename std::size_t            size_type;
        private:
            size_type   _size;
            Container   _underlying_container;
        public:
            explicit stack (const container_type& ctnr = container_type()) {
                _underlying_container = ctnr;
                _size = ctnr.size();
            }

   /*
        ELEMENT ACCESS
        empty
        top
        size
        push
        pop
    */
        bool empty() const {
            return _underlying_container.empty();
        }

        size_type size() const {
            return _underlying_container.size();
        }

        value_type& top() {
            return _underlying_container.back();
        }

        const value_type& top() const {
            return _underlying_container.back();
        }

        void push (const value_type& val) {
            _underlying_container.push_back(val);
        }

        void pop() {
            _underlying_container.pop_back();
        }
    };
    /*
        NON MEMBER FUNCTIONS
        operator== *
        operator!= *
        operator< *
        operator<= *
        operator>= *
        operator>= *
    */

    /*template <class T, class Container>
    bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
        return lhs._underlying_container == rhs._underlying_container;
    }

    template <class T, class Container>
    bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
        return !(lhs == rhs);
    }

    template <class T, class Container>
    bool operator<  (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
        return lhs._underlying_container < rhs._underlying_container;
    }

    template <class T, class Container>
    bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
        return !(rhs < lhs);
    }

    template <class T, class Container>
    bool operator>  (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
        return rhs < lhs;
    }

    template <class T, class Container>
    bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
        return !(lhs < rhs);
    }*/

};

#endif