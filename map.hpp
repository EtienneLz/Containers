#ifndef MAP_HPP
# define MAP_HPP
# include <memory>
# include <map>
# include "utils/red_black_tree.hpp"

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
		typedef std::map<Key, T>::container_type::iterator       iterator;
		typedef std::map<Key, T>::container_type::const_iterator       const_iterator;
		typedef std::map<Key, T>::container_type::reverse_iterator       reverse_iterator;
		typedef std::map<Key, T>::container_type::const_reverse_iterator       const_reverse_iterator;
		typedef typename allocator_type::difference_type    difference_type;
		typedef typename std::size_t                        size_type;
	
	private:
		allocator_type                          _alloc;
		ft::RedBlackTree<key_type, mapped_type> _tree;

	public:
		explicit map (const key_compare& comp = key_compare(),
			  const allocator_type& alloc = allocator_type());

		template <class InputIterator>
			map (InputIterator first, InputIterator last,
			const key_compare& comp = key_compare(),
			const allocator_type& alloc = allocator_type());

		map (const map& x);

		~map();

		//map& operator= (const map& x);

		//iterator begin();
		
		//const_iterator begin() const;

		//iterator end();

		//const_iterator end() const;

		//reverse_iterator rbegin();
		
		//const_reverse_iterator rbegin() const;

		//reverse_iterator rend();
		
		//const_reverse_iterator rend() const;

		bool empty() const {
			if (_tree.get_size() == 0)
				return true;
			return false;
		}

		size_type size() const {
			return _tree.get_size();
		}

		size_type max_size() const {
			return alloc.max_size();
		}

		//mapped_type& operator[] (const key_type& k);

		//pair<iterator,bool> insert (const value_type& val);

		//iterator insert (iterator position, const value_type& val);

		//template <class InputIterator>
		//void insert (InputIterator first, InputIterator last);

		//void erase (iterator position);

		//size_type erase (const key_type& k);

		//void erase (iterator first, iterator last);

		//void swap (map& x);
		
		void clear() {
			_tree.deleteAll();
		}

		key_compare key_comp() const;

		value_compare value_comp() const;

		iterator find (const key_type& k);

		const_iterator find (const key_type& k) const;

		size_type count (const key_type& k) const;

		iterator lower_bound (const key_type& k);

		const_iterator lower_bound (const key_type& k) const;

		iterator upper_bound (const key_type& k);

		const_iterator upper_bound (const key_type& k) const;

		pair<const_iterator,const_iterator> equal_range (const key_type& k) const;

		pair<iterator,iterator>             equal_range (const key_type& k);

		allocator_type get_allocator() const {
			return allocator_type;
		}
};

};

#endif