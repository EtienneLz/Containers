#ifndef RED_BLACK_TREE
# define RED_BLACK_TREE

# include "make_pair.hpp"
# include <iostream>

# define BLACK 0
# define RED 1

namespace ft
{
/*
template <class Key, class T>
struct Node {
		Node*                   _left;
		Node*                   _right;
		Node*                   _parent;
		ft::pair<const Key, T>  _data;
		int                     _color;

		Node(Key key, T t) {
				_data(key, t);
		}
};

template <class Key,
						class T,
						class Compare = std::less<Key>,
						class Alloc = std::allocator<ft::pair<const Key, T> > >
class   RB_Tree
{
		private:
				Alloc           _n_alloc;
				Node<Key, T>    *_root;
                Node<Key, T>    *null_node;
				size_t          _size;
		
		public:
			RB_Tree() {
				_size = 0;
				_n_alloc.allocate(1);
				_n_alloc.construct(&_root, Node<Key, T>(Key(), T()));

				_root._left = NULL;
				_root._right = NULL;
				_root._parent = NULL;
				_root._color = BLACK;
			}

			Node<Key, T> new_node(Key key, T t) {
    			Node<Key, T>	*newNode;

			    _n_alloc.allocate(1);
			    _n_alloc.construct(newNode, Node<Key, T>(key, t));
			    newNode._parent = NULL;
		    	newNode._left = _null_node;
	    		newNode._right = _null_node;
    			newNode._color = BLACK;
    		}

			void insert(Key key, T t) {
				Node<Key, T>	*newNode = new_node(key, t);
                Node<Key, T>    *point_a;
                Node<Key, T>    *point_b;
                point_a = _root;
                point_b = NULL;
                
                while (point_a._left != NULL && point_a._right != NULL) {
                    point_b = point_a;
                    if (newNode._data < point_a._data)
                        point_a = point_a._left;
                    else
                        point_a = point_a._right;
                }
                newNode._parent = point_b;
                if (newNode._parent._parent == NULL)
                    _root = newNode;
                else if (newNode.data < point_b._data)
                    point_b._left = newNode;
                else
                    point_b._right = newNode;
			}
		

};
};
*/


/*struct Node {
		Node*                   _left;
		Node*                   _right;
		Node*                   _parent;
		ft::pair<const Key, T>  _data;
		int                     _color;

		Node(Key key, T t) {
				_data(key, t);
		}
};*/
template <class Key, class T>
struct Node {
	ft::pair<const Key, T>  data;
	Node                    *parent;
	Node                    *left;
	Node                    *right;
	int                     color;

    Node(Key key, T t): data(key, t) {}
};

typedef Node<class Key, class T> *NodePtr;

template <class Key,
						class T,
						class Compare = std::less<Key>,
						class Alloc = std::allocator<ft::pair<const Key, T> > >
class RedBlackTree {
	private:
	    NodePtr         root;
	    NodePtr         TNULL;
        size_t          _size;
        NodePtr         _array;
        Alloc           _alloc_node;

	// Preorder
	void preOrderHelper(NodePtr node) {
		if (node != TNULL) {
			std::cout << node->data << " ";
			preOrderHelper(node->left);
			preOrderHelper(node->right);
		}
	}

	// Inorder
	void inOrderHelper(NodePtr node) {
		if (node != TNULL) {
			inOrderHelper(node->left);
			std::cout << node->data << " ";
			inOrderHelper(node->right);
		}
	}

	// Post order
	void postOrderHelper(NodePtr node) {
		if (node != TNULL) {
			postOrderHelper(node->left);
			postOrderHelper(node->right);
			std::cout << node->data << " ";
		}
	}

	NodePtr searchTreeHelper(NodePtr node, int key) {
		if (node == TNULL || key == node->data) {
			return node;
		}

		if (key < node->data) {
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
		if (u->parent == nullptr) {
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
			if (node->data == key) {
				z = node;
			}

			if (node->data <= key) {
				node = node->right;
			} else {
				node = node->left;
			}
		}

		if (z == TNULL) {
			std::cout << "Key not found in the tree" << std::endl;
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
		if (y_original_color == BLACK) {
			deleteFix(x);
		}
	}

	// For balancing the tree after insertion
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
			std::cout << root->data << "(" << sColor << ")" << std::endl;
			printHelper(root->left, indent, false);
			printHelper(root->right, indent, true);
		}
	}

	public:

    typedef typename std::size_t    size_type;
    typedef T                       mapped_value;

	RedBlackTree() {
        _size = 0;
        Node<Key, T> nRoot = _alloc_node.allocate(1);
        _alloc_node.construct(nRoot, Node<Key, T>(Key(), T())); 
		nRoot->color = BLACK;
		nRoot->left = nullptr;
		nRoot->right = nullptr;
		root = nRoot;
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

	NodePtr searchTree(int k) {
		return searchTreeHelper(this->root, k);
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
		if (x->parent == nullptr) {
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
		if (x->parent == nullptr)
			this->root = y;
        else if (x == x->parent->right)
			x->parent->right = y;
        else
			x->parent->left = y;
		y->right = x;
		x->parent = y;
	}

	// Inserting a node
	void insert(int key) {
		NodePtr node = _alloc_node.allocate(1);
        _alloc_node.construct(node, Node<Key, T>(Key(), T()));
		node->parent = nullptr;
		node->data = key;
		node->left = TNULL;
		node->right = TNULL;
		node->color = RED;

		NodePtr y = nullptr;
		NodePtr x = this->root;

		while (x != TNULL) {
			y = x;
			if (node->data < x->data) {
				x = x->left;
			} else {
				x = x->right;
			}
		}

		node->parent = y;
		if (y == nullptr) {
			root = node;
		} else if (node->data < y->data) {
			y->left = node;
		} else {
			y->right = node;
		}

		if (node->parent == nullptr) {
			node->color = BLACK;
			return;
		}

		if (node->parent->parent == nullptr) {
			return;
		}

		insertFix(node);
	}

	NodePtr getRoot() {
		return this->root;
	}

	void deleteNode(int data) {
		deleteNodeHelper(this->root, data);
	}

	void printTree() {
		if (root) {
			printHelper(this->root, "", true);
		}
	}
};
};
#endif