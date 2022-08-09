#ifndef RED_BLACK_TREE
# define RED_BLACK_TREE

# include "bidirectional_iterator.hpp"
# include "make_pair.hpp"
# include <iostream>

# define BLACK 0
# define RED 1

namespace ft
{
template < typename T > 
class Node
{
public:
	T		data;
	Node	*parent;
	Node	*left;
	Node	*right;
	int		color; 

	bool	operator==( const Node & rhs ) {
		return (this->data == rhs.data);
	}

	Node &	operator=( const Node & rhs ) {
		if (this != &rhs) {
			data = rhs.data;
			parent = rhs.parent;
			left = rhs.left;
			right = rhs.right;
			color = rhs.color;
		}
		return *this;
	}
};

template < class Arg1, class Arg2, class Result >
struct binary_function
{
	typedef Arg1		first_type;
	typedef Arg2		second_type;
	typedef Result		result_type;
};

template < class T >
struct less : binary_function<T, T, bool>
{
	bool		operator() ( const T & x, const T & y) const
	{
		return (x < y);
	}
}; 

template < class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator < pair < const Key, T > > >
class RedBlackTree
{
public:

	typedef Key												key_type;
	typedef T												mapped_type;
	typedef ft::pair<const Key, T>							value_type;
	typedef Compare											key_compare;
	typedef Node<value_type>								node;
	typedef Alloc											allocator_type;
	typedef bidirectional_iterator<value_type, node>		iterator;
	typedef size_t											size_type;
	typedef typename Alloc::template rebind<node>::other	node_allocator_type;
	typedef	node *											NodePtr;

	RedBlackTree( const allocator_type & alloc = allocator_type()): _alloc_two(alloc), _root(NULL), _size(0) {
		TNULL = _alloc_node.allocate(1);
		TNULL->right = NULL;
		TNULL->left = NULL;
		TNULL->color = BLACK;
		_root = TNULL;
		TNULL->parent = _root;
	}

	~RedBlackTree( void ) {
		deleteAll(_root);
		if (TNULL != NULL) {
			_alloc_node.deallocate(TNULL, 1);
			TNULL = NULL;
		}
	}

	void			initializeTNULL() {
		TNULL = _alloc_node.allocate(1);
		TNULL->right = NULL;
		TNULL->left = NULL;
		TNULL->color = BLACK;
		TNULL->parent = _root;
	}

	void			reassign_root() {
		_root = TNULL;
		TNULL->parent = _root;
	}

	RedBlackTree &		operator=(const RedBlackTree & rhs) {
		if (this != &rhs) {
			clear();
			_root = TNULL;
			TNULL->parent = _root;
			in_order_tree_fill(rhs.getRoot());
		}
		return *this;
	}

	void			clear() {
		deleteAll(_root);
		_size = 0;
		_root = TNULL;
	}

	void	deleteAll(NodePtr x) {
		if (x == TNULL)
			return ;
		deleteAll(x->left);
		deleteAll(x->right);
		_alloc_two.destroy(&(x->data));
		_alloc_node.deallocate(x, 1);
		_size--;
	}

	void	in_order_tree_fill(NodePtr n) {
		if (n == TNULL)
			return ;
		insert(n->data);
		in_order_tree_fill(n->left);
		in_order_tree_fill(n->right);
	}

	NodePtr		searchTree(key_type k) const {
		return search_tree_helper(this->_root, k);
	}

	NodePtr		lower_bound(key_type k) const {
		return lower_bound_helper(_root, k);
	}

	NodePtr		upper_bound(key_type k) const {
		return upper_bound_helper(_root, k);
	}

	NodePtr		end( void ) const {
		return TNULL;
	}

	NodePtr		minimum(NodePtr n) const {
		while (n->left != TNULL && n->left != NULL)
			n = n->left;
		return n;
	}


	NodePtr		maximum(NodePtr n) {
		while (n->right != TNULL)
			n = n->right;
		return n;
	}

	NodePtr		successor(NodePtr x) const {
		if (x->right != TNULL)
			return minimum(x->right);
		NodePtr	 y = x->parent;
		while (y != TNULL && x == y->right) {
			x = y;
			y = y->parent;
		}
		return y;
	}

	NodePtr		predecessor(NodePtr x) const {
		if (x->left != TNULL)
			return maximum(x->left);
		NodePtr y = x->parent;
		while (y != TNULL && x == y->left) {
			x = y;
			y = y->parent;
		}
		return y;
	}

	void	left_rotate(NodePtr x) {
		NodePtr		y = x->right;
		x->right = y->left;
		if (y->left != TNULL)
			y->left->parent = x;
		y->parent = x->parent;
		if (x->parent == TNULL)
			this->_root = y;
		else if (x == x->parent->left)
			x->parent->left = y;
		else
			x->parent->right = y;
		y->left = x;
		x->parent = y;
	}

	void	right_rotate(NodePtr x) {
		NodePtr		y = x->left;
		x->left = y->right;
		if (y->right != TNULL)
			y->right->parent = x;
		y->parent = x->parent;
		if (x->parent == TNULL)
			this->_root = y;
		else if (x == x->parent->right)
			x->parent->right = y;
		else
			x->parent->left = y;
		y->right = x;
		x->parent = y;
	}


	pair<iterator, bool>	insert(value_type d) {
		NodePtr					new_node;
		pair<iterator, bool>	ret;
		
		new_node = _alloc_node.allocate(1);
		_alloc_two.construct(&(new_node->data), d);
		new_node->parent = NULL;
		new_node->left = TNULL;
		new_node->right = TNULL;
		new_node->color = RED;

		NodePtr 	y = NULL;
		NodePtr 	x = this->_root;

		while (x != TNULL)
		{
			y = x;
			if (key_compare() (new_node->data.first, x->data.first))
				x = x->left;
			else if (key_compare() (x->data.first, new_node->data.first))
				x = x->right;
			else {
				_alloc_two.destroy(&(new_node->data));
				_alloc_node.deallocate(new_node, 1);
				ret.first = iterator(x);
				ret.second = false;
				return ret;
			}
		}

		new_node->parent = y;
		if (y == NULL) {
			new_node->parent = TNULL;
			this->_root = new_node;
		}
		else if (key_compare() (new_node->data.first, y->data.first))
			y->left = new_node;
		else
			y->right = new_node;
		_size++;
		ret.first = iterator(new_node);
		ret.second = true;
		if (new_node->parent == TNULL) {
			new_node->color = BLACK;
			TNULL->parent = _root;
			return ret;
		}
		if (new_node->parent->parent == TNULL)
			return ret;
		fix_insert(new_node);
		TNULL->parent = _root;
		return ret;
	}

	bool		erase( key_type k) {
		bool	ret;
		if (_root == TNULL)
			return false;
		ret = delete_node_helper(this->_root, k);
		TNULL->parent = _root;
		return ret;
	}


	NodePtr		getRoot( void ) const {
		return this->_root;
	}

	size_t	get_size( void ) const {
		return this->_size;
	}

	size_t	maxSize( void ) const {
		return _alloc_node.max_size();
	}

	NodePtr		getTNULL( void ) const {
		return TNULL;
	}

	allocator_type	get_allocator( void ) const	{
		return _alloc_two;
	}

	void		delete_node(value_type d) {
		delete_node_helper(this->_root, d);
	}

	void		print_tree() {
		if (_root != TNULL) {
			std::cout << "Tree contains " << _size << " nodes :" << std::endl;
			print_helper(this->_root, "", true);
		}
	}

	void		nb_black_nodes_all_leaves_paths() {
		int		nb_black_nodes;

		nb_black_nodes = 0;
		count_black_nodes(nb_black_nodes, _root);
	}

	void		count_black_nodes( int nb_black_nodes, NodePtr n) {
		if (n->color == BLACK)
			nb_black_nodes++;
		if (n->left == TNULL && n->right == TNULL) {
			std::cout << "Path to leaf [ " << n->data << " ] contains " << nb_black_nodes << " black nodes." << std::endl;
			return ;
		}
		if (n->left != TNULL)
			count_black_nodes(nb_black_nodes, n->left);
		if (n->right != TNULL)
			count_black_nodes(nb_black_nodes, n->right);
	}

	void		swap( RedBlackTree & rhs) {
		allocator_type			temp_alloc_two = rhs.get_allocator();
		node_allocator_type		temp_alloc_node = rhs._alloc_node;
		node *					temp_root = rhs.getRoot();
		node *					tempTNULL = rhs.getTNULL();
		size_t					temp_size = rhs.get_size();

		rhs._alloc_two = this->get_allocator();
		rhs._alloc_node = _alloc_node;
		rhs._root = this->getRoot();
		rhs.TNULL = this->getTNULL();
		rhs._size = this->get_size();

		_alloc_two = temp_alloc_two;
		_alloc_node = temp_alloc_node;
		_root = temp_root;
		TNULL = tempTNULL;
		_size = temp_size;
	}


private:
	allocator_type			_alloc_two;
	node_allocator_type		_alloc_node;
	node *					_root;
	node *					TNULL;
	size_t					_size;

	NodePtr		search_tree_helper(NodePtr n, key_type k) const	{
		if (n == TNULL) {
			return n;
		}
		if (key_compare() (k, n->data.first)) {
			return search_tree_helper(n->left, k);
		}
		else if (key_compare() (n->data.first, k)) {
			return search_tree_helper(n->right, k);
		}
		else {
			return n;
		}
	}

	NodePtr		lower_bound_helper(NodePtr x, key_type k) const	{
		NodePtr		y = _root;

		while (x != TNULL) {
			if (!(key_compare() (x->data.first, k))) {
				y = x;
				x = x->left;
			}
			else
				x = x->right;
		}
		if (key_compare() (y->data.first, k) && x == TNULL)
			return TNULL;
		return y;
	}

	NodePtr		upper_bound_helper(NodePtr x, key_type k) const	{
		NodePtr		y = _root;

		while (x != TNULL) {
			if (key_compare() (k, x->data.first)) {
				y = x;
				x = x->left;
			}
			else
				x = x->right;
		}
		if (key_compare() (y->data.first, k) && x == TNULL)
			return TNULL;
		return y;
	}

	void		fix_delete(NodePtr x) {
		NodePtr		s;

		while (x != _root && x->color == BLACK)
		{
			if (x == x->parent->left) {
				s = x->parent->right;
				if (s->color == RED) {
					s->color = BLACK;
					x->parent->color = RED;
					left_rotate(x->parent);
					s = x->parent->right;
				}
				if (s->left->color == BLACK && s->right->color == BLACK) {
					s->color = RED; 
					x = x->parent; 
				}
				else {
					if (s->right->color == BLACK) {
						s->left->color = BLACK; 
						s->color = RED;
						right_rotate(s); 
						s = x->parent->right;
					}
					s->color = x->parent->color;
					x->parent->color = BLACK;
					s->right->color = BLACK;
					left_rotate(x->parent); 
					x = _root;
				}
			}
			else {
				s = x->parent->left;
				if (s->color == RED) {
					s->color = BLACK;
					x->parent->color = RED;
					right_rotate(x->parent);
					s = x->parent->left;
				}
				if (s->right->color == BLACK && s->right->color == BLACK) {
					s->color = RED;
					x = x->parent;
				}
				else {
					if (s->left->color == BLACK) {
						s->right->color = BLACK;
						s->color = RED;
						left_rotate(s);
						s = x->parent->left;
					}
					s->color = x->parent->color;
					x->parent->color = BLACK;
					s->left->color = BLACK;
					right_rotate(x->parent);
					x = _root;
				}
			}
		}
		x->color = BLACK;
	}

	void	rb_transplant(NodePtr u, NodePtr v) {
		if (u->parent == TNULL)
			_root = v;
		else if (u == u->parent->left)
			u->parent->left = v;
		else
			u->parent->right = v;
		v->parent = u->parent;
	}

	bool		delete_node_helper(NodePtr n, key_type k) {
		NodePtr		z = TNULL;
		NodePtr		x;
		NodePtr		y;

		while (n != TNULL) {
			if ((!(key_compare() (n->data.first, k))) && (!(key_compare() (k, n->data.first))))	{
				z = n;
				break ;
			}
			else if (key_compare() (n->data.first, k))
				n = n->right;
			else
				n = n->left;
		}
		if (z == TNULL)
			return false;
		y = z;
		int		y_original_color = y->color;
		if (z->left == TNULL) {
			x = z->right;
			rb_transplant(z, z->right);
		}
		else if (z->right == TNULL)	{
			x = z->left;
			rb_transplant(z, z->left);
		}
		else {
			y = minimum(z->right);
			y_original_color = y->color;
			x = y->right;
			if (y->parent == z)
				x->parent = y;
			else {
				rb_transplant(y, y->right);
				y->right = z->right;
				y->right->parent = y;
			}
			rb_transplant(z, y);
			y->left = z->left;
			y->left->parent = y;
			y->color = z->color;
		}
		_alloc_two.destroy(&(z->data));
		_alloc_node.deallocate(z, 1);
		if (y_original_color == BLACK)
			fix_delete(x);
		_size--;
		return true;
	}

	void		fix_insert(NodePtr k) {
		NodePtr		u;

		while (k->parent->color == RED)
		{
			if (k->parent == k->parent->parent->right) {
				u = k->parent->parent->left;
				if (u->color == RED) {
					u->color = BLACK;
					k->parent->color = BLACK;
					k->parent->parent->color = RED;
					k = k->parent->parent;
				}
				else {
					if (k == k->parent->left) {
						k = k->parent;
						right_rotate(k);
					}
					k->parent->color = BLACK;
					k->parent->parent->color = RED;
					left_rotate(k->parent->parent);
				}
			}
			else {
				u = k->parent->parent->right;
				if (u->color == RED) {
					u->color = BLACK;
					k->parent->color = BLACK;
					k ->parent->parent->color = RED;
					k = k->parent->parent;
				}
				else {
					if (k == k->parent->right) {
						k = k->parent;
						left_rotate(k);
					}
					k->parent->color = BLACK;
					k->parent->parent->color = RED;
					right_rotate(k->parent->parent);
				}
			}
			if (k == _root)
				break;
		}
		_root->color = BLACK;
	}

	void		print_helper(NodePtr root, std::string indent, bool last) {
		if (root != TNULL) {
			std::cout << indent;
			if (last) {
				std::cout << "R---------";
				indent += "          ";
			}
			else {
				std::cout << "L---------";
				indent += "|         ";
			}
			std::string	sColor = root->color?"\033[1;31mRED\033[0m":"\033[1;37mBLACK\033[0m";
			std::cout << root->data << "(" << sColor << ")" << std::endl;
			print_helper(root->left, indent, false);
			print_helper(root->right, indent, true);
		}
	}

};

template<typename T>
Node<T> *		successor(Node<T> * x)
{
	if (x->left == NULL)
		return x;
	if (x->right->right != NULL) {
		Node<T> *	 y = x->right;
		while (y->left->left != NULL)
			y = y->left;
		return y;
	}
	Node<T> *	 y = x->parent;
	while (y->left != NULL && x == y->right) {
		x = y;
		y = y->parent;
	}
	return y;
}


template<typename T>
Node<T> *		predecessor(Node<T> * x) {
	if (x->left == NULL)
	{
		Node<T> *	y = x->parent;
		while (y->right->right != NULL)
			y = y->right;
		return y;
	}
	if (x->left->left != NULL)
	{
		Node<T> *	 y = x->left;
		while (y->right->right != NULL)
			y = y->right;
		return y;
	}
	Node<T> * y = x->parent;
	while (y->right != NULL && x == y->left) {
		x = y;
		y = y->parent;
	}
	return y;
}

};

#endif