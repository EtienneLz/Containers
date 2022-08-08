#ifndef RED_BLACK_TREE
# define RED_BLACK_TREE

# include "bidirectional_iterator.hpp"
# include "make_pair.hpp"
# include <iostream>

# define BLACK 0
# define RED 1

namespace ft
{
template <typename T>
struct Node {
public:
	T					  	data;
	Node                    *parent;
	Node                    *left;
	Node                    *right;
	int                     color;


	bool operator==(const Node &rhs) {
		if (parent == rhs.parent && left == rhs.left && right == rhs.right && color == rhs.color)
			return true;
		return false;
	}

	bool operator!=(const Node &rhs) {
		return !(this == rhs);
	}

	Node &	operator=( const Node & rhs )
	{
		if (this != &rhs)
		{
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
}; // binary function structure to include in the comparison structure

template < class T >
struct less : binary_function<T, T, bool>
{
	bool		operator() ( const T & x, const T & y) const
	{
		return (x < y);
	}
}; // less compare structure


// RedBlackTree IMPLEMENTATION//
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
	// the rebind<type> of std::allocator gives us access to its member type "other" which serves as allocator for elements of type <type>


	//CONSTRUCTOR//
	RedBlackTree( const allocator_type & alloc = allocator_type()): _pair_alloc(alloc), _root(NULL), _size(0)
	{
		TNULL = _node_alloc.allocate(1);
		TNULL->right = NULL;
		TNULL->left = NULL;
		TNULL->color = 0;
		_root = TNULL;
		TNULL->parent = _root;
	}

	~RedBlackTree( void )
	{
		delete_all_nodes(_root);
		if (TNULL != NULL)
		{
			_node_alloc.deallocate(TNULL, 1);
			TNULL = NULL;
		}
	}

	void			initializeTNULL( void )
	{
		TNULL = _node_alloc.allocate(1);
		TNULL->right = NULL;
		TNULL->left = NULL;
		TNULL->color = 0;
		TNULL->parent = _root;
	}

	void			reassign_root( void )
	{
		_root = TNULL;
		TNULL->parent = _root;
	}

	RedBlackTree &		operator=( const RedBlackTree & rhs )
	{
		if (this != &rhs)
		{
			clear();
			_root = TNULL;
			TNULL->parent = _root;
			in_order_tree_fill(rhs.get_Root());
		}
		return *this;
	}

	void			clear( void )
	{
		delete_all_nodes(_root);
		_size = 0;
		_root = TNULL;
	}

	void	delete_all_nodes( NodePtr x )
	{
		if (x == TNULL)
			return ;
		delete_all_nodes(x->left);
		delete_all_nodes(x->right);
		_pair_alloc.destroy(&(x->data));
		_node_alloc.deallocate(x, 1);
		_size--;
	}

	void	in_order_tree_fill(NodePtr n)
	{
		if (n == TNULL)
		{
			return ;
		}
		insert(n->data);
		in_order_tree_fill(n->left);
		in_order_tree_fill(n->right);
	}


	// searching the tree for k key and returning the corresponding node
	NodePtr		searchTree(key_type k) const
	{
		return searchTree_helper(this->_root, k);
	}

	NodePtr		lower_bound(key_type k) const
	{
		return lower_bound_helper(_root, k);
	}

	NodePtr		upper_bound(key_type k) const
	{
		return upper_bound_helper(_root, k);
	}

	NodePtr		begin( void ) const
	{
		return this->minimum(_root);
	}

	NodePtr		end( void ) const
	{
		return TNULL;
	}


	// finding node with minimum key
	NodePtr		minimum(NodePtr n) const
	{
		while (n->left != TNULL && n->left != NULL)
			n = n->left;
		return n;
	}


	NodePtr		maximum(NodePtr n)
	{
		while (n->right != TNULL)
			n = n->right;
		return n;
	}


	// find the successor of a given node
	NodePtr		successor(NodePtr x) const
	{
		// if the right sub-tree is not null, the successor is the leftmost node in the right sub-tree
		if (x->right != TNULL)
		{
			return minimum(x->right);
		}
		//else it is the lowest ancestor of x whose left child is also an ancestor of x
		NodePtr	 y = x->parent;
		while (y != TNULL && x == y->right)
		{
			x = y;
			y = y->parent;
		}
		return y;
	}


	//find the predecessor of a given node
	NodePtr		predecessor(NodePtr x) const
	{
		// if the left tree is not null, the predecessor is the right most node in the left sub-tree
		if (x->left != TNULL)
			return maximum(x->left);
		//else it is the highest ancestor of x whose right child is also an ancestor of x
		NodePtr y = x->parent;
		while (y != TNULL && x == y->left)
		{
			x = y;
			y = y->parent;
		}
		return y;
	}


	//rotate left at Node x
	void	left_rotate(NodePtr x)
	{
		NodePtr		y = x->right;
		x->right = y->left;
		if (y->left != TNULL)
		{
			y->left->parent = x;
		}
		y->parent = x->parent;
		if (x->parent == TNULL)
		{
			this->_root = y;
		}
		else if (x == x->parent->left)
		{
			x->parent->left = y;
		}
		else
		{
			x->parent->right = y;
		}
		y->left = x;
		x->parent = y;
	}


	//rotate right at Node x
	void	right_rotate(NodePtr x)
	{
		NodePtr		y = x->left;
		x->left = y->right;
		if (y->right != TNULL)
		{
			y->right->parent = x;
		}
		y->parent = x->parent;
		if (x->parent == TNULL)
		{
			this->_root = y;
		}
		else if (x == x->parent->right)
		{
			x->parent->right = y;
		}
		else
		{
			x->parent->left = y;
		}
		y->right = x;
		x->parent = y;
	}


	pair<iterator, bool>	insert(value_type d)
	{
		NodePtr					new_node;
		pair<iterator, bool>	ret;
		
		new_node = _node_alloc.allocate(1);
		_pair_alloc.construct(&(new_node->data), d);
		new_node->parent = NULL;
		new_node->left = TNULL;
		new_node->right = TNULL;
		new_node->color = 1; // new node must be red

		NodePtr 	y = NULL;
		NodePtr 	x = this->_root;

		while (x != TNULL)
		{
			y = x;
			if (key_compare() (new_node->data.first, x->data.first)) // we go down the tree to place the new_node by comparing its data value with existing nodes.
			{
				x = x->left;
			}
			else if (key_compare() (x->data.first, new_node->data.first))
			{
				x = x->right;
			}
			else
			{
				_pair_alloc.destroy(&(new_node->data));
				_node_alloc.deallocate(new_node, 1);
				ret.first = iterator(x);
				ret.second = false;
				return ret;
			}
		}

		// so we have x at the bottom of the tree ( as TNULL ) and y as its parent
		// so we know we can place the new_node  with y as its parent
		new_node->parent = y;
		if (y == NULL) // in case the tree is empty
		{
			new_node->parent = TNULL;
			this->_root = new_node;
		}
		else if (key_compare() (new_node->data.first, y->data.first)) // we check by comparing data values wether new_node goes to the left or right of its parent
		{
			y->left = new_node;
		}
		else
		{
			y->right = new_node;
		}

		_size++;
		ret.first = iterator(new_node);
		ret.second = true;

		//if the new_node has become root, we simply return
		if (new_node->parent == TNULL)
		{
			new_node->color = 0;
			TNULL->parent = _root;
			return ret;
		}

		// if the grandparent is null, we simply return ( new_node is a child of _root )
		if (new_node->parent->parent == TNULL)
		{
			return ret;
		}

		// AND NOW LET'S FIX THE TREE
		fix_insert(new_node);
		TNULL->parent = _root;
		return ret;
	}

	bool		erase( key_type k)
	{
		bool	ret;
		if (_root == TNULL)
			return false;
		ret = delete_node_helper(this->_root, k);
		TNULL->parent = _root;
		return ret;
	}


	NodePtr		getRoot( void ) const
	{
		return this->_root;
	}

	size_t	get_size( void ) const
	{
		return this->_size;
	}

	size_t	get_Max_Size( void ) const
	{
		return _node_alloc.max_size();
	}

	NodePtr		getTNULL( void ) const
	{
		return TNULL;
	}

	allocator_type	get_allocator( void ) const
	{
		return _pair_alloc;
	}

	void		delete_node(value_type d)
	{
		delete_node_helper(this->_root, d);
	}


	// CA C'EST POUR FAIRE JOLI, ON VERRA POUR L'ENLEVER PLUS TARD
	void		print_tree( void )
	{
		if (_root != TNULL)
		{
			std::cout << "Tree contains " << _size << " nodes :" << std::endl;
			print_helper(this->_root, "", true);
		}
	}

	void		nb_black_nodes_all_leaves_paths( void )
	{
		int		nb_black_nodes;

		nb_black_nodes = 0;
		count_black_nodes(nb_black_nodes, _root);
	}

	void		count_black_nodes( int nb_black_nodes, NodePtr n)
	{
		if (n->color == 0)
			nb_black_nodes++;
		if (n->left == TNULL && n->right == TNULL)
		{
			std::cout << "Path to leaf [ " << n->data << " ] contains " << nb_black_nodes << " black nodes." << std::endl;
			return ;
		}
		if (n->left != TNULL)
		{
			count_black_nodes(nb_black_nodes, n->left);
		}
		if (n->right != TNULL)
		{
			count_black_nodes(nb_black_nodes, n->right);
		}
	}

	void		swap( RedBlackTree & rhs)
	{
		allocator_type			temp_pair_alloc = rhs.get_allocator();
		node_allocator_type		temp_node_alloc = rhs._node_alloc;
		node *					temp_root = rhs.get_Root();
		node *					tempTNULL = rhs.getTNULL();
		size_t					temp_size = rhs.get_size();

		rhs._pair_alloc = this->get_allocator();
		rhs._node_alloc = _node_alloc;
		rhs._root = this->get_Root();
		rhs.TNULL = this->getTNULL();
		rhs._size = this->get_size();

		_pair_alloc = temp_pair_alloc;
		_node_alloc = temp_node_alloc;
		_root = temp_root;
		TNULL = tempTNULL;
		_size = temp_size;
	}


private:
	allocator_type			_pair_alloc;
	node_allocator_type		_node_alloc;
	node *					_root;
	node *					TNULL;
	size_t					_size;

	// Pour l'instant pas besoin
	// void initializeNULLNode(NodePtr node, NodePtr parent) {}

	NodePtr		searchTree_helper(NodePtr n, key_type k) const
	{
		if (n == TNULL) // if current node is empty or k is equal to current node data we return root
		{
			return n;
		}
		if (key_compare() (k, n->data.first)) // we progress throught he tree by comparing data values, in case the data is a pair, the pair operator overloads compare key first
		{
			return searchTree_helper(n->left, k);
		}
		else if (key_compare() (n->data.first, k))
		{
			return searchTree_helper(n->right, k);
		}
		else
		{
			return n;
		}
	}

	NodePtr		lower_bound_helper(NodePtr x, key_type k) const
	{
		NodePtr		y = _root;

		while (x != TNULL)
		{
			if (!(key_compare() (x->data.first, k)))
			{
				y = x;
				x = x->left;
			}
			else
			{
				x = x->right;
			}
		}
		if (key_compare() (y->data.first, k) && x == TNULL)
			return TNULL;
		return y;
	}

	NodePtr		upper_bound_helper(NodePtr x, key_type k) const
	{
		NodePtr		y = _root;

		while (x != TNULL)
		{
			if (key_compare() (k, x->data.first))
			{
				y = x;
				x = x->left;
			}
			else
			{
				x = x->right;
			}
		}
		if (key_compare() (y->data.first, k) && x == TNULL)
			return TNULL;
		return y;
	}

	void		fix_delete(NodePtr x)
	{
		NodePtr		s;

		// THIS GIANT LOOP IS CASE 3 : X is a black node
		// Deleting a black node violates property number 5 (All paths must have the same number of black nodes)
		// So we add an extra black node to the deleted node to make a "double black node" and try to convert this back to a single node
		// There are 8 cases for this (4 cases and there mirrors): 3.1, 3.2, 3.3 and 3.4
		while (x != _root && x->color == 0)
		{
			if (x == x->parent->left) // if() brackets that encapsulate cases 3.1, 3.2, 3.3 and 3.4 in the case where x is a LEFT child
			{
				s = x->parent->right; // We make S the right neighbor of X
				if (s->color == 1) // CASE 3.1 DELETION : X's sibling S is red
				{
					s->color = 0;// We switch colors between S and X's parent
					x->parent->color = 1;
					left_rotate(x->parent); // And then perform a left rotation on X's parent
					s = x->parent->right; // the right sibling of S's new position becomes S
				} // This reduces case 3.1 to cases 3.2, 3.3 or 3.4.
				if (s->left->color == 0 && s->right->color == 0) // CASE 3.2 DELETION : X's sibling S is black and both S's children are black
				{
					s->color = 1; // We change S's color to red
					x = x->parent; // and we make X's parent the new X and this leads us to case 3.1
				}
				else
				{
					if (s->right->color == 0) // CASE 3.3 DELETION: S is black, S's left child is black and S's right child is black
					{
						s->left->color = 0; // Switching color between S and S's left child
						s->color = 1;
						right_rotate(s); // performing a right rotation on S
						s = x->parent->right; // S becomes X's right sibling to prepare for next case
					}// We end up with a 3.4 case
					// CASE 3.4 DELETION : X's sibling S is black and S's right child is red (terminal case)
					s->color = x->parent->color; // S takes on X's parent color so that we can change the parent to black
					x->parent->color = 0; // We change X's parent to black
					s->right->color = 0; // We change S's right child to black
					left_rotate(x->parent); // And then we perform a left rotation on X's parent to reequilibrate the tree.
					x = _root; // this causes the new x value to become the root of the tree;
				}
			}
			else //cases 3.1, 3.2, 3.3 and 3.4 in the case where x is a RIGHT child (same as above but right and left are inverted)
			{
				s = x->parent->left;
				if (s->color == 1) // CASE 3.1 DELETION
				{
					s->color = 0;
					x->parent->color = 1;
					right_rotate(x->parent);
					s = x->parent->left;
				}
				if (s->right->color == 0 && s->right->color == 0) // CASE 3.2 DELETION
				{
					s->color = 1;
					x = x->parent;
				}
				else
				{
					if (s->left->color == 0) // CASE 3.3 DELETION
					{
						s->right->color = 0;
						s->color = 1;
						left_rotate(s);
						s = x->parent->left;
					}
					//CASE 3.4 DELETION
					s->color = x->parent->color;
					x->parent->color = 0;
					s->left->color = 0;
					right_rotate(x->parent);
					x = _root;
				}
			}
		}
		x->color = 0;
	}

	void	rb_transplant(NodePtr u, NodePtr v)
	{
		if (u->parent == TNULL) // Case where u is _root
		{
			_root = v; // We make v the root
		}
		else if (u == u->parent->left) // case where u is a left_child
		{
			u->parent->left = v; // we replace u with v as left_child of its parent
		}
		else // case where u is a right_child
		{
			u->parent->right = v; // we replace u with v as right_child of its parent
		}
		v->parent = u->parent;
	}

	bool		delete_node_helper(NodePtr n, key_type k)
	{
		// first we try to find the node corresponding to the pair k
		NodePtr		z = TNULL;
		NodePtr		x;
		NodePtr		y;

		while (n != TNULL) // while loop where we search for value_type k
		{
			if ((!(key_compare() (n->data.first, k))) && (!(key_compare() (k, n->data.first))))
			{
				z = n;
				break ;
			}
			else if (key_compare() (n->data.first, k))
			{
				n = n->right;
			}
			else
			{
				n = n->left;
			}
		}

		if (z == TNULL)
		{
			return false;
		}

		y = z;
		int		y_original_color = y->color;
		if (z->left == TNULL)
		{
			x = z->right;
			rb_transplant(z, z->right);
		}
		else if (z->right == TNULL)
		{
			x = z->left;
			rb_transplant(z, z->left);
		}
		else
		{
			y = minimum(z->right);
			y_original_color = y->color;
			x = y->right;
			if (y->parent == z)
			{
				x->parent = y;
			}
			else
			{
				rb_transplant(y, y->right);
				y->right = z->right;
				y->right->parent = y;
			}
			rb_transplant(z, y);
			y->left = z->left;
			y->left->parent = y;
			y->color = z->color;
		}
		_pair_alloc.destroy(&(z->data));
		_node_alloc.deallocate(z, 1);
		if (y_original_color == 0)
			fix_delete(x);
		_size--;
		return true;
	}

	//fixing the red black tree after insertion of new node
	void		fix_insert(NodePtr k)
	{
		NodePtr		u;

		//All following cases are sub-cases of case 3 where P (parent) of the inserted node is red
		// We will refer to the subtree nodes with the letters S (sibling), P (parent), U (uncle) and G (grandparent)
		while (k->parent->color == 1)
		{
			if (k->parent == k->parent->parent->right)
			{
				u = k->parent->parent->left; //uncle
				if (u->color == 1) // CASE 3.1 INSERTION: P is red and U is red too
				{
					u->color = 0;
					k->parent->color = 0;
					k->parent->parent->color = 1;
					k = k->parent->parent;
				}
				else // case 3.2.1 and case 3.2.2 following from case 3.2 where P is red and U is black (or NULL)
				{
					if (k == k->parent->left) // CASE 3.2.2: triangle case where P is right child of G and K is left child of P
					{
						k = k->parent;
						right_rotate(k);
					}
					//CASE 3.2.1 : line situation between G, P and the new node
					k->parent->color = 0;
					k->parent->parent->color = 1;
					left_rotate(k->parent->parent);
				}
			}
			else // And here we solve mirror case 3.1 and mirror cases of 3.2.1, 3.2.2 (these are 3.2.3 and 3.2.4) 
			{
				u = k->parent->parent->right; // uncle
				if (u->color == 1) //Mirror CASE of 3.1
				{
					u->color = 0;
					k->parent->color = 0;
					k ->parent->parent->color = 1;
					k = k->parent->parent;
				}
				else
				{
					if (k == k->parent->right) //Mirror case of 3.2.2 (CASE 3.2.4)
					{
						k = k->parent;
						left_rotate(k);
					}
					//Mirror CASE of 3.2.1 (Case 3.2.3)
					k->parent->color = 0;
					k->parent->parent->color = 1;
					right_rotate(k->parent->parent);
				}
			}
			if (k == _root)
			{
				break;
			}
		}
		_root->color = 0;
	}

	void		print_helper(NodePtr root, std::string indent, bool last)
	{
		// displaying the tree structure on the screen
		if (root != TNULL)
		{
			std::cout << indent;
			if (last)
			{
				std::cout << "R---------";
				indent += "          ";
			}
			else
			{
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

//find the sucessor of a given node
template<typename T>
Node<T> *		successor(Node<T> * x)
{
	if (x->left == NULL)
		return x;
	// if the right sub-tree is not null, the successor is the leftmost node in the right sub-tree
	if (x->right->right != NULL)
	{
		Node<T> *	 y = x->right;
		while (y->left->left != NULL)
			y = y->left;
		return y;
	}
	//else it is the lowest ancestor of x whose left child is also an ancestor of x
	Node<T> *	 y = x->parent;
	while (y->left != NULL && x == y->right)
	{
		x = y;
		y = y->parent;
	}
	return y;
}


//find the predecessor of a given node
template<typename T>
Node<T> *		predecessor(Node<T> * x)
{
	if (x->left == NULL)
	{
		Node<T> *	y = x->parent;
		while (y->right->right != NULL)
		{
			y = y->right;
		}
		return y;
	}
	// if the left tree is not null, the predecessor is the right most node in the left sub-tree
	if (x->left->left != NULL)
	{
		Node<T> *	 y = x->left;
		while (y->right->right != NULL)
			y = y->right;
		return y;
	}
	//else it is the highest ancestor of x whose right child is also an ancestor of x
	Node<T> * y = x->parent;
	while (y->right != NULL && x == y->left)
	{
		x = y;
		y = y->parent;
	}
	return y;
}

template<typename T>
Node<T> *	returnRoot(Node<T> * r) {
		Node<T> * val;

		val = r;
		while (val->parent)
			val = val->parent;
		return val;
}

template<typename T>
Node<T> *		minimum(Node<T> * n)
{
	while (n->left->left != NULL)
 		n = n->left;
 	return n;
}

template<typename T>
Node<T> *		maximum(Node<T> * n)
{
 	while (n->right->right != NULL)
		n = n->right;
 	return n;
}
};
#endif