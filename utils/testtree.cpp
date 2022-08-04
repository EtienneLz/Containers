#include "red_black_tree.hpp"
#include "bidirectional_iterator.hpp"
#include "make_pair.hpp"

int main() {
	ft::RedBlackTree<int, int> bst;
	bst.insert(ft::make_pair(55, 1));
	bst.insert(ft::make_pair(40, 1));
	bst.insert(ft::make_pair(65, 1));
	bst.insert(ft::make_pair(60, 1));
	bst.insert(ft::make_pair(75, 1));
	bst.insert(ft::make_pair(57, 1));
	bst.insert(ft::make_pair(57, 1));
	bst.printTree();

	bst.deleteNode(60);
	bst.printTree();
	ft::RedBlackTree<int, int>::iterator it(bst.minimum(bst.getRoot()));
	it++;
	std::cout << it->first << std::endl;
	return 0;
}