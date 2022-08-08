#ifndef VECTOR_HPP  
# define VECTOR_HPP

# include <memory>
# include <iostream>
# include "utils/random_access_iterator.hpp"
# include "utils/reverse_iterators.hpp"
# include "utils/enable_if.hpp"
# include "utils/is_integral.hpp"
# include "utils/lexicographical_compare.hpp"

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
			typedef T												value_type;
			typedef Alloc											allocator_type;
			typedef std::size_t										size_type;
			typedef std::ptrdiff_t									difference_type;
			typedef value_type &									reference;
			typedef const value_type &								const_reference;
			typedef typename allocator_type::pointer				pointer;
			typedef typename allocator_type::const_pointer			const_pointer;
			typedef ft::random_access_iterator<value_type>			iterator;
			typedef	ft::random_access_iterator<const value_type>	const_iterator;
			typedef	ft::reverse_iterator<iterator>					reverse_iterator;
			typedef	ft::reverse_iterator<const_iterator>			const_reverse_iterator;

			explicit vector(const allocator_type& alloc = allocator_type()) {
				_alloc = alloc;
				_size = 0;
				_array = NULL;
				_array = _alloc.allocate(0);
				_capacity = 0;
			}

			explicit vector(size_type n, const value_type& val = value_type(),
				const allocator_type& alloc = allocator_type()) {
				_size = n;
				_alloc = alloc;
				_capacity = _size;
				_array = _alloc.allocate(_size);
				assign(n, val);
			}

			template <class InputIterator>
			vector(InputIterator first, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type last,
				const allocator_type& alloc = allocator_type()) {
				_size = static_cast<size_type>(ft::distance(first, last));
				_alloc = alloc;
				_capacity = _size;
				_array = _alloc.allocate(_size);
				assign(first, last);
			}

			~vector() {
				for (size_type i(0); i < _size; i++) {
					_alloc.destroy(&_array[i]);
				}
				_alloc.deallocate(_array, _capacity);
				_array = NULL;
			}

			vector(const vector<T>& src):  _size(src._size), _capacity(src._size) {
				_array = _alloc.allocate(_capacity);
				for (size_type i = 0; i < _size; i++)
				{
					_alloc.construct(_array + i, src[i]);
				}
			}
			vector& operator=(const vector<T>& rhs) {
				_alloc = rhs._alloc;
				_size = rhs._size;
				_capacity = rhs._capacity;
				_array = _alloc.allocate(_size);
				for (size_type i(0); i < _size; i++)
					_alloc.construct(&_array[i], rhs[i]);
				return *this;
			}

			allocator_type get_allocator(void) const {
				return Alloc();
			}

		private :
			T*              _array;
			allocator_type  _alloc;
			size_type       _size;
			size_type       _capacity;

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
				if (!(pos < _size))
					throw std::out_of_range("vector");
				return _array[pos];
			}

			const_reference   at(size_type pos) const {
				if (!(pos < _size))
					throw std::out_of_range("vector");
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

			reference   back() const {
				return _array[_size - 1];
			}

			
   /*
		ITERATORS
		begin 
		end 
		rbegin
		rend
	*/  
			iterator    begin() {
				return iterator(_array);
			}

			iterator    end() {
				return iterator(_array + _size);
			}
   
			reverse_iterator    rbegin() {
				return reverse_iterator(end());
			}

			reverse_iterator    rend() {
				return reverse_iterator(begin());
			}

			const_iterator    begin() const {
				return const_iterator(_array);
			}

			const_iterator    end() const {
				return const_iterator(_array + _size);
			}

			const_reverse_iterator	rbegin( void ) const
			{
				return const_reverse_iterator(end());
			}

			const_reverse_iterator	rend( void ) const
			{
				return const_reverse_iterator(begin());
			}
   
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
		assign *
		clear *
		insert *
		erase *
		push_back *
		pop_back *
		resize *
		swap *
	*/
			void    assign(size_type n, const value_type& val) {
				if (n == 0)
					return ;
				if (n > _capacity)
				{
					this->clear();
					_alloc.deallocate(_array, _capacity);
					_array = NULL;
					_capacity = 0;
					_size = n;
					_capacity = n;
					_array = _alloc.allocate(_capacity);
					for (size_type i = 0; i < n; i++)
						_alloc.construct(_array + i, val);
				}
				else
				{
					for (size_type i = 0; i < _size; i++)
						_alloc.destroy(_array + i);
					_size = n;
					for (size_type i = 0; i < _size; i++)
						_alloc.construct(_array + i, val);
				}
			}

			template    <class InputIterator>
			void    assign (InputIterator first, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type last) {
				this->clear();
				if (ft::distance(first, last) > static_cast<difference_type>(_capacity))
					this->reserve(ft::distance(first, last));
				for (InputIterator it = first; it != last; it++)
					push_back(*it);
			}

			void    clear() {
				for (size_type i(0); i < _size; i++) {
					_alloc.destroy(&_array[i]);
				}
				_size = 0;
			}

			iterator insert(iterator position, const value_type& val) {
				iterator            it = begin();
				ft::difference_type diff;
				size_type           tmp_pos;
				diff = ft::distance(it, position);
				if (_size == _capacity)
					reserve(_capacity *= 2);
				tmp_pos = _size;
				_alloc.construct(&_array[tmp_pos], _array[tmp_pos - 1]);
				diff = static_cast<ft::difference_type>(_size) - diff;
				it = end();
				while (diff) {
					diff--;
					tmp_pos--;
					it--;
					if (tmp_pos)
						_array[tmp_pos] = _array[tmp_pos - 1];
				}
				_array[tmp_pos] = val;
				_size++;
				return it;
			}

			void insert (iterator position, size_type n, const value_type& val) {
				iterator            it = begin();
				ft::difference_type diff;
				diff = ft::distance(it, position);
				if (_size + n >= _capacity)
					realloc(_size + n);
				size_type   tmp_pos;
				tmp_pos = _size;
				diff = static_cast<ft::difference_type>(_size) - diff;
				while (diff) {
					diff--;
					if (tmp_pos)
						_array[tmp_pos + n - 1] = _array[tmp_pos - 1];
					tmp_pos--;
				}
				for (size_type i = 0; i < n; i++) {
					_array[tmp_pos] = val;
					tmp_pos++;
				}
				_size += n;
			}

			template <class InputIterator>
			void insert (iterator position, InputIterator first, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type last) {
				iterator            it = begin();
				ft::difference_type diff;
				size_type           n;
				n = static_cast<size_type>(ft::distance(first, last));
				diff = ft::distance(it, position);
				if (_size + n >= _capacity)
					realloc(_size + n);
				size_type   tmp_pos;
				tmp_pos = _size;
				diff = static_cast<ft::difference_type>(_size) - diff;
				while (diff) {
					diff--;
					if (tmp_pos)
						_array[tmp_pos + n - 1] = _array[tmp_pos - 1];
					tmp_pos--;
				}
				for (size_type i = 0; i < n; i++) {
					_array[tmp_pos] = *first;
					first++;
					tmp_pos++;
				}
				_size += n;
			}

			iterator erase (iterator position) {
				return (erase(position, position + 1));
			}

			iterator erase (iterator first, iterator last) {
				size_type	len;
			
				len = ft::distance(first, last);
				if (last == end())
				{
					for (size_type i = 0; i < len; i++)
						pop_back();
					return end();
				}
				else
				{
					iterator	ret = first;
					while (last != end()) {
						*first = *last;
						first++;
						last++;
					}
					while (len > 0) {
						_size--;
						_alloc.destroy(&(_array[_size]));
						len--;
					}
					return ret;
				}
			}

			void    push_back (const value_type& val) {
				if (_size >= _capacity) {
					if (_capacity == 0)
						_capacity = 1;
					else
						_capacity *= 2;
					realloc (_capacity);
				}
				_size++;
				_array[_size - 1] = val;
			}

			void    pop_back() {
				if (_size == 0)
					return ;
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
   
			void    swap(vector &x) {
				value_type		*copy_array;
				size_type		copy_size;
				//size_type		copy_max_size;
				allocator_type	copy_alloc;
				size_type		copy_capacity;

				copy_array = _array;
				copy_size = _size;
				//copy_max_size = _max_size;
				copy_alloc = _alloc;
				copy_capacity = _capacity;

				_array = x._array;
				_size = x._size;
				//_max_size = other._max_size;
				_alloc = x._alloc;
				_capacity = x._capacity;

				x._array = copy_array;
				x._size = copy_size;
				//other._max_size = copy_max_size;
				x._alloc = copy_alloc;
				x._capacity = copy_capacity;
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

		std::swap *
	*/

	template <class T, class Alloc>
	bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		if (lhs.size() == rhs.size()) {
			for (size_t i = 0; i < lhs.size(); i++)
				if (lhs[i] != rhs[i])
					return false;
		}
		else
			return false;
		return true;
	}

	template <class T, class Alloc>
	bool operator< (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template <class T, class Alloc>
	bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		return !(lhs == rhs);
	}

	template <class T, class Alloc>
	bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		return !(rhs < lhs);
	}

	template <class T, class Alloc>
	bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		return (rhs < lhs);
	}

	template <class T, class Alloc>
	bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		return !(lhs < rhs);
	}

	template <class T, class Alloc>
	void swap (ft::vector<T,Alloc>& x, ft::vector<T,Alloc>& y) {
		x.swap(y);
	}
};

#endif