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
};

template < class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator < pair < const Key, T> > >
class RedBlackTree {

	public:

	typedef Key						key_type;
	typedef ft::pair<const Key, T>	value_type;
	typedef Node<value_type>		*NodePtr;
	typedef typename std::size_t    size_type;
	typedef T                       mapped_value;
	typedef	Compare					key_compare;
	typedef typename Alloc::template rebind<Node<value_type> >::other	node_allocator_type;
	typedef Alloc					allocator_type;

	typedef bidirectional_iterator<ft::pair<const Key, T>, Node<value_type> >		iterator;

	RedBlackTree(const allocator_type& alloc = allocator_type()): _alloc_two(alloc), root(NULL) {
		TNULL = _alloc_node.allocate(1);
		TNULL->color = 0;
		TNULL->left = NULL;
		TNULL->right = NULL;
		
		_size = 0;
		/*Node<Key, T> *nRoot = _alloc_node.allocate(1);
		_alloc_two.construct(nRoot, Node<Key, T>(Key(), T())); 
		nRoot->color = BLACK;
		nRoot->left = TNULL;
		nRoot->right = TNULL;
		nRoot->parent = NULL;
		root = nRoot;*/
		root = TNULL;
		TNULL->parent = root;
	}

	~RedBlackTree() {
		_alloc_node.deallocate(TNULL, 1);
		deleteAll(root);
	}

	void	deleteAll(NodePtr x) {
		if (x->left != TNULL)
			deleteAll(x->left);
		if (x->right != TNULL)
			deleteAll(x->right);
		_alloc_two.destroy(&(x->data));
		_alloc_node.deallocate(x, 1);
		_size = 0;

	}
	void preorder() {
		preOrderHelper(this->root);
	}

	void inorder() {
		inOrderHelper(this->root);
	}

	void postorder() {
		postOrderHelper(this->root);
	}

	NodePtr searchTree(Key k) {
		return searchTreeHelper(this->root, k);
	}

	NodePtr find_tree(Key k) {
		NodePtr	node;

		node = searchTreeHelper(this->root, k);
		if (node == TNULL)
			return NULL;
		return node;
	}

	NodePtr minimum(NodePtr node) {
		while (node->left != TNULL) {
			node = node->left;
		}
		return node;
	}

	NodePtr maximum(NodePtr node) {
		while (node->right != TNULL) {
			node = node->right;
		}
		return node;
	}

	NodePtr end() const {
		return TNULL;
	}

	NodePtr		lower_bound(key_type k) const
	{
		NodePtr	x = root;
		NodePtr	y = root;

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

	NodePtr		upper_bound(key_type k) const
	{
		NodePtr	x = root;
		NodePtr	y = root;

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

	NodePtr successor(NodePtr x) {
		if (x->right != TNULL) {
			return minimum(x->right);
		}

		NodePtr y = x->parent;
		while (y != TNULL && x == y->right) {
			x = y;
			y = y->parent;
		}
		return y;
	}

	NodePtr predecessor(NodePtr x) {
		if (x->left != TNULL) {
			return maximum(x->left);
		}

		NodePtr y = x->parent;
		while (y != TNULL && x == y->left) {
			x = y;
			y = y->parent;
		}

		return y;
	}

	void leftRotate(NodePtr x) {
		NodePtr y = x->right;
		x->right = y->left;
		if (y->left != TNULL) {
			y->left->parent = x;
		}
		y->parent = x->parent;
		if (x->parent == NULL) {
			this->root = y;
		} else if (x == x->parent->left) {
			x->parent->left = y;
		} else {
			x->parent->right = y;
		}
		y->left = x;
		x->parent = y;
	}

	void rightRotate(NodePtr x) {
		NodePtr y = x->left;
		x->left = y->right;
		if (y->right != TNULL) {
			y->right->parent = x;
		}
		y->parent = x->parent;
		if (x->parent == NULL)
			this->root = y;
		else if (x == x->parent->right)
			x->parent->right = y;
		else
			x->parent->left = y;
		y->right = x;
		x->parent = y;
	}

	// Inserting a node
	pair<iterator, bool> insert(value_type val) {
		pair<iterator, bool>	ret;

		if (searchTree(val.first) != TNULL) {
			ret.first = iterator(searchTree(val.first));
			ret.second = false;
			return ret;
		}
		NodePtr node;
		node = _alloc_node.allocate(1);
		_alloc_two.construct(&(node->data), val);
		node->parent = NULL;
		node->left = TNULL;
		node->right = TNULL;
		node->color = RED;

		NodePtr y = NULL;
		NodePtr x = this->root;

		while (x != TNULL) {
			y = x;
			if (key_compare() (node->data.first, x->data.first))
				x = x->left;
			else
				x = x->right;
		}
		node->parent = y;
		if (y == NULL)
			root = node;
		else if (key_compare() (node->data.first, y->data.first))
			y->left = node;
		else
			y->right = node;

		if (node->parent == NULL) {
			node->color = BLACK;
			ret.first = iterator(node);
			ret.second = true;
			_size++;
			return ret;
		}

		if (node->parent->parent == NULL) {
			ret.first = iterator(node);
			ret.second = true;
			_size++;
			return ret;
		}
		_size++;
		insertFix(node);
		//TNULL->parent = root;
		ret.first = iterator(node);
		ret.second = true;
		return ret;
	}

	NodePtr getRoot() {
		return this->root;
	}

	void deleteNode(Key data) {
		deleteNodeHelper(this->root, data);
	}

	bool erase(Key data) {
		if (searchTree(data) != TNULL)
			return false;
		deleteNode(data);
		return true;
	}

	void printTree() {
		if (root) {
			printHelper(this->root, "", true);
		}
	}

	size_t	get_size() const {
		return _size;
	}

	private:
		node_allocator_type	_alloc_node;
		Alloc				_alloc_two;
		NodePtr         	root;
		NodePtr         	TNULL;
		size_t          	_size;
		NodePtr         	_array;

	void initNode(NodePtr node) {
		node->parent = NULL;
		node->left = NULL;
		node->right = NULL;
	}

	// Preorder
	void preOrderHelper(NodePtr node) {
		if (node != TNULL) {
			std::cout << node->data.first << " ";
			preOrderHelper(node->left);
			preOrderHelper(node->right);
		}
	}

	// Inorder
	void inOrderHelper(NodePtr node) {
		if (node != TNULL) {
			inOrderHelper(node->left);
			std::cout << node->data.first << " ";
			inOrderHelper(node->right);
		}
	}

	// Post order
	void postOrderHelper(NodePtr node) {
		if (node != TNULL) {
			postOrderHelper(node->left);
			postOrderHelper(node->right);
			std::cout << node->data.first << " ";
		}
	}

	NodePtr searchTreeHelper(NodePtr node, int key) {
		if (node == TNULL || key == node->data.first) {
			return node;
		}

		if (key_compare() (key, node->data.first)) {
			return searchTreeHelper(node->left, key);
		}
		return searchTreeHelper(node->right, key);
	}

	// For balancing the tree after deletion
	void deleteFix(NodePtr x) {
		NodePtr s;
		while (x != root && x->color == BLACK) {
			if (x == x->parent->left) {
				s = x->parent->right;
				if (s->color == RED) {
					s->color = BLACK;
					x->parent->color = RED;
					leftRotate(x->parent);
					s = x->parent->right;
				}

				if (s->left->color == BLACK && s->right->color == BLACK) {
					s->color = RED;
					x = x->parent;
				} else {
					if (s->right->color == BLACK) {
						s->left->color = BLACK;
						s->color = 1;
						rightRotate(s);
						s = x->parent->right;
					}

					s->color = x->parent->color;
					x->parent->color = BLACK;
					s->right->color = BLACK;
					leftRotate(x->parent);
					x = root;
				}
			} else {
				s = x->parent->left;
				if (s->color == RED) {
					s->color = BLACK;
					x->parent->color = RED;
					rightRotate(x->parent);
					s = x->parent->left;
				}

				if (s->right->color == BLACK && s->right->color == BLACK) {
					s->color = RED;
					x = x->parent;
				} else {
					if (s->left->color == BLACK) {
						s->right->color = BLACK;
						s->color = RED;
						leftRotate(s);
						s = x->parent->left;
					}

					s->color = x->parent->color;
					x->parent->color = BLACK;
					s->left->color = BLACK;
					rightRotate(x->parent);
					x = root;
				}
			}
		}
		x->color = BLACK;
	}

	void rbTransplant(NodePtr u, NodePtr v) {
		if (u->parent == NULL) {
			root = v;
		} else if (u == u->parent->left) {
			u->parent->left = v;
		} else {
			u->parent->right = v;
		}
		v->parent = u->parent;
	}

	void deleteNodeHelper(NodePtr node, int key) {
		NodePtr z = TNULL;
		NodePtr x, y;
		while (node != TNULL) {
			if (node->data.first == key)
				z = node;
			if (key_compare() (node->data.first, key))
				node = node->right;
			else
				node = node->left;
		}

		if (z == TNULL) {
			std::cout << "Key not found" << std::endl;
			return;
		}

		y = z;
		int y_original_color = y->color;
		if (z->left == TNULL) {
			x = z->right;
			rbTransplant(z, z->right);
		} else if (z->right == TNULL) {
			x = z->left;
			rbTransplant(z, z->left);
		} else {
			y = minimum(z->right);
			y_original_color = y->color;
			x = y->right;
			if (y->parent == z) {
				x->parent = y;
			} else {
				rbTransplant(y, y->right);
				y->right = z->right;
				y->right->parent = y;
			}

			rbTransplant(z, y);
			y->left = z->left;
			y->left->parent = y;
			y->color = z->color;
		}
		_alloc_node.destroy(z);
		_alloc_node.deallocate(z, 1);
		_size--;
		if (y_original_color == BLACK) {
			deleteFix(x);
		}
	}

	// Balance the tree after an insertion
	void insertFix(NodePtr k) {
		NodePtr u;
		while (k->parent->color == RED) {
			if (k->parent == k->parent->parent->right) {
				u = k->parent->parent->left;
				if (u->color == RED) {
					u->color = BLACK;
					k->parent->color = BLACK;
					k->parent->parent->color = RED;
					k = k->parent->parent;
				} else {
					if (k == k->parent->left) {
						k = k->parent;
						rightRotate(k);
					}
					k->parent->color = BLACK;
					k->parent->parent->color = RED;
					leftRotate(k->parent->parent);
				}
			} else {
				u = k->parent->parent->right;

				if (u->color == RED) {
					u->color = BLACK;
					k->parent->color = BLACK;
					k->parent->parent->color = RED;
					k = k->parent->parent;
				} else {
					if (k == k->parent->right) {
						k = k->parent;
						leftRotate(k);
					}
					k->parent->color = BLACK;
					k->parent->parent->color = RED;
					rightRotate(k->parent->parent);
				}
			}
			if (k == root) {
				break;
			}
		}
		root->color = BLACK;
	}

	void printHelper(NodePtr root, std::string indent, bool last) {
		if (root != TNULL) {
			std::cout << indent;
			if (last) {
				std::cout << "R----";
				indent += "   ";
			} else {
				std::cout << "L----";
				indent += "|  ";
			}

			std::string sColor = root->color ? "RED" : "BLACK";
			std::cout << root->data.first << "|" << root->data.second << " (" << sColor << ")";
			if (root->left == TNULL)
				std::cout << "LNULL ";
			if (root->right == TNULL)
				std::cout << "RNULL ";
			if (root->parent == NULL)
				std::cout << "PNULL ";
			std::cout << std::endl;
			printHelper(root->left, indent, false);
			printHelper(root->right, indent, true);
		}
	}

};
template<typename T>
Node<T> *		successor(Node<T> * x)
{
	if (x->right == NULL)
		return x;
	if (x->left == NULL)
		return x;
	if (x->right->right != NULL)
	{
		Node<T> *	 y = x->right;
		while (y->left->left != NULL)
			y = y->left;
		return y;
	} 
	Node<T> *	 y = x->parent;
	while (y->left != NULL && x == y->right)
	{
		//std::cout << y->data.first << std::endl;
		x = y;
		y = y->parent;
	}
	return y;
}

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
	if (x->left->left != NULL)
	{
		Node<T> *	 y = x->left;
		while (y->right->right != NULL)
			y = y->right;
		return y;
	}
	Node<T> * y = x->parent;
	while (y->right != NULL && x == y->left)
	{
		x = y;
		y = y->parent;
	}
	return y;
}
};
#endif