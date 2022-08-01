#ifndef MAP_HPP
# define MAP_HPP
# include <memory>
# include <map>

# include "utils/red_black_tree.hpp"
# include "utils/bidirectional_iterator.hpp"

namespace ft
{

template <class Key,
			class T,
			class Compare = std::less<Key>,
			class Alloc = std::allocator<ft::pair<const Key, T> > >
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
		typedef typename allocator_type::difference_type    difference_type;
		typedef typename std::size_t                        size_type;

		typedef ft::bidirectional_iterator<value_type, ft::Node<Key, T> >		iterator;
		typedef ft::bidirectional_iterator<value_type, ft::Node<Key, T> >		const_iterator;
		//typedef std::map<Key, T>::container_type::reverse_iterator       	reverse_iterator;
		//typedef std::map<Key, T>::container_type::const_reverse_iterator	const_reverse_iterator;
	
	private:
		allocator_type                          _alloc;
		ft::RedBlackTree<key_type, mapped_type> _tree;

	public:
		/*
			MEMBER FUNCTIONS
			constructor
			destructor
			operator=
		*/
		explicit map (const key_compare& comp = key_compare(),
			  const allocator_type& alloc = allocator_type());

		template <class InputIterator>
			map (InputIterator first, InputIterator last,
			const key_compare& comp = key_compare(),
			const allocator_type& alloc = allocator_type());

		map (const map& x);

		~map();

		//map& operator= (const map& x);

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
			return iterator(_tree.maximum(_tree.getRoot()));
		}

		const_iterator end() const {
			return const_iterator(_tree.maximum(_tree.getRoot()));
		}

		//reverse_iterator rbegin();
		
		//const_reverse_iterator rbegin() const;

		//reverse_iterator rend();
		
		//const_reverse_iterator rend() const;

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
			MODIFIERS
			clear
			insert
			erase
			swap
		*/

		pair<iterator,bool> insert (const value_type& val) {
			return _tree.insert(val.first, val.second);
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
			_tree.deleteNode(position->first);
		}

		//void erase( iterator first, iterator last );

		//size_type erase (const key_type& k);

		//void erase (iterator first, iterator last);

		//void swap (map& x);
		
		void clear() {
			_tree.deleteAll();
		}
		/*
			LOOKUP
			count
			find
			equal_range
			lower_bound
			upper_bound
		*/

		size_type count( const Key& key ) const {
			if (_tree.searchTree(key) != NULL)
				return 1;
			return 0;
		}

		iterator find( const Key& key ) {
			return iterator(_tree.searchTree(key));
		}
	
		const_iterator find( const Key& key ) const {
			return const_iterator(_tree.searchTree(key));
		}

		/*
			OBSERVER FUNCTIONS
			key_comp
			value_compare
		*/

		key_compare key_comp() const {
			return key_compare();
		}

		/*value_compare value_comp() const {
			return value_compare(key_compare());
		}*/

		/*allocator_type get_allocator() const {
			return allocator_type;
		}*/
};

};

#endif