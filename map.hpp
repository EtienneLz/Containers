#ifndef MAP_HPP
# define MAP_HPP
# include <memory>

# include "utils/lexicographical_compare.hpp"
# include "utils/red_black_tree.hpp"
# include "utils/bidirectional_iterator.hpp"
# include "utils/equal.hpp"
# include "utils/reverse_iterators.hpp"
# include "utils/equal.hpp"
# include "utils/lexicographical_compare.hpp"

namespace ft
{

template <typename Key, typename T, typename Compare = less<Key>, typename Alloc = std::allocator<ft::pair<const Key, T> > >
class map
{
	public:
		typedef Key                                         key_type;
		typedef T                                           mapped_type;
		typedef ft::pair<const key_type, mapped_type>       value_type;
		typedef Compare                                     key_compare;
		typedef Alloc                                       allocator_type;
		typedef typename allocator_type::reference          reference;
		typedef typename allocator_type::const_reference    const_reference;
		typedef typename allocator_type::pointer            pointer;
		typedef typename allocator_type::const_pointer      const_pointer;
		typedef	std::ptrdiff_t								difference_type;
		typedef typename std::size_t                        size_type;

		typedef ft::bidirectional_iterator<value_type, ft::Node<value_type> >		iterator;
		typedef ft::bidirectional_iterator<const value_type, ft::Node<value_type> >	const_iterator;
		typedef ft::reverse_iterator<iterator>              						reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>        						const_reverse_iterator;
	
	private:
		allocator_type                          _alloc;
		ft::RedBlackTree<key_type, mapped_type, Compare, Alloc> _tree;
		key_compare								_comp;

	public:

		class value_compare: public binary_function<value_type, value_type, bool>
		{
			friend class map;

			protected:
			key_compare			_comp;
		
			value_compare(key_compare c): _comp(c) {}

			public:

			typedef bool			result_type;
			typedef value_type		first_type;
			typedef	value_type		second_type;

			bool		operator() (const value_type & x, const value_type & y) const
			{
				return _comp(x.first, y.first);
			}
		}; 
		/*
			MEMBER FUNCTIONS
			constructor
			destructor
			operator=
		*/
		explicit map (const key_compare& comp = key_compare(),
			  const allocator_type& alloc = allocator_type()) 
		{
			_comp = comp;
			_alloc = alloc;
		}

		template <class InputIterator>
			map (InputIterator first, InputIterator last,
			const key_compare& comp = key_compare(),
			const allocator_type& alloc = allocator_type());

		map (const map& x): _comp(x._comp), _alloc(x._alloc)
		{
			insert(x.begin(), x.end());
		}

		~map() {}

		map &	operator=(const map & rhs)
		{
			if (rhs.empty())
				this->clear();
			else if (this != &rhs)
			{
				this->clear();
				_tree.reassign_root();
				insert(rhs.begin(), rhs.end());
			}
			return *this;
		}

		/*
			ITERATORS
			begin
			end
			rbegin
			rend
		*/
		iterator begin() {
			return iterator(_tree.minimum(_tree.getRoot()));
		}
		
		const_iterator begin() const {
			return const_iterator(_tree.minimum(_tree.getRoot()));
		}

		iterator end() {
			return iterator(_tree.end());
		}

		const_iterator end() const {
			return const_iterator(_tree.end());
		}

		reverse_iterator rbegin() {
			return reverse_iterator(_tree.end());
		}
		
		const_reverse_iterator rbegin() const {
			return const_reverse_iterator(_tree.end());
		}

		reverse_iterator rend() {
			return reverse_iterator(_tree.minimum(_tree.getRoot()));
		}
		
		const_reverse_iterator rend() const {
			return const_reverse_iterator(_tree.minimum(_tree.getRoot()));
		}

		/*
			CAPACITY
			empty
			size
			max_size
		*/

		bool empty() const {
			if (_tree.get_size() == 0)
				return true;
			return false;
		}

		size_type size() const {
			return _tree.get_size();
		}

		size_type max_size() const {
			return _alloc.max_size();
		}
		/*
			ELEMENT ACCESS
			operator[]
		*/

		mapped_type& operator[] (const key_type& k) {
			return this->insert(value_type(k, mapped_type())).first->second;
		}

		/*
			MODIFIERS
			clear
			insert
			erase
			swap
		*/

		pair<iterator,bool> insert (const value_type& val) {
			return _tree.insert(val);
		}

		iterator insert (iterator position, const value_type& val) {
			(void)position;
			return _tree.insert(val).first;
		}

		template <class InputIteratorMap>
		void insert (InputIteratorMap first, InputIteratorMap last) {
			for (InputIteratorMap it = first; it != last; it++)
				_tree.insert(*it);
		}

		void erase (iterator position) {
			_tree.erase(position->first);
		}

		void erase( iterator first, iterator last ) {
			while (first != last) {
				first = find(first->first);
				erase(first++);
			}
		}

		size_type erase (const key_type& k) {
			if (_tree.erase(k))
				return 1;
			return 0;
		}

		void swap (map& x) {
			this->_tree.swap(x._tree);
		}
		
		void clear() {
			_tree.clear();
		}
		/*
			LOOKUP
			count
			find
			equal_range
			lower_bound
			upper_bound
		*/

		iterator find( const Key& key ) {
			return iterator(_tree.searchTree(key));
		}
	
		const_iterator find( const Key& key ) const {
			return const_iterator(_tree.searchTree(key));
		}

		size_type count( const Key& key ) const {
			if (find(key) == this->end())
				return 0;
		 return 1;
		}

		iterator lower_bound (const key_type& k) {
			return iterator(_tree.lower_bound(k));
		}

		const_iterator lower_bound (const key_type& k) const {
			return const_iterator(_tree.lower_bound(k));
		}

		iterator upper_bound (const key_type& k) {
			return iterator(_tree.upper_bound(k));
		}

		const_iterator upper_bound (const key_type& k) const {
			return const_iterator(_tree.upper_bound(k));
		}

		pair<iterator,iterator>             equal_range (const key_type& k) {
			pair<iterator, iterator>	ret;

		 	ret.first = lower_bound(k);
		 	ret.second = upper_bound(k);
		 	return ret;
		}

		pair<const_iterator,const_iterator> equal_range (const key_type& k) const {
			pair<const_iterator, const_iterator>	ret;

		 	ret.first = lower_bound(k);
		 	ret.second = upper_bound(k);
		 	return ret;
		}

		/*
			OBSERVER FUNCTIONS
			key_comp
			value_compare
		*/

		key_compare key_comp() const {
			return key_compare();
		}

		value_compare value_comp() const {
			return value_compare(key_compare());
		}

		allocator_type get_allocator() const {
			return _alloc;
		}
};

template < class Key, class T, class Compare, class Alloc>
bool		operator==( const map<Key, T, Compare, Alloc> & lhs, const map<Key, T, Compare, Alloc> & rhs)
{
	if (lhs.size() != rhs.size())
	{
		return false;
	}
	return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
}

template < class Key, class T, class Compare, class Alloc>
bool		operator!=( const map<Key, T, Compare, Alloc> & lhs, const map<Key, T, Compare, Alloc> & rhs)
{
	return (!(lhs == rhs));
}

template < class Key, class T, class Compare, class Alloc>
bool		operator<( const map<Key, T, Compare, Alloc> & lhs, const map<Key, T, Compare, Alloc> & rhs)
{
	return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
}

template < class Key, class T, class Compare, class Alloc>
bool		operator<=( const map<Key, T, Compare, Alloc> & lhs, const map<Key, T, Compare, Alloc> & rhs)
{
	return (!(rhs < lhs));
}

template < class Key, class T, class Compare, class Alloc>
bool		operator>( const map<Key, T, Compare, Alloc> & lhs, const map<Key, T, Compare, Alloc> & rhs)
{
	return (rhs < lhs);
}

template < class Key, class T, class Compare, class Alloc>
bool		operator>=( const map<Key, T, Compare, Alloc> & lhs, const map<Key, T, Compare, Alloc> & rhs)
{
	return (!(lhs < rhs));
}

};

#endif