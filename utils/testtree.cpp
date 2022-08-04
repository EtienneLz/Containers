#include "red_black_tree.hpp"
#include "bidirectional_iterator.hpp"

int main() {
	ft::RedBlackTree<int, int> bst;
	bst.insert(55, 1);
	bst.insert(40, 1);
	bst.insert(65, 1);
	bst.insert(60, 1);
	bst.insert(75, 1);
	bst.insert(57, 1);
	bst.insert(57, 1);
	bst.printTree();

	bst.deleteNode(60);
	bst.printTree();
	ft::RedBlackTree<int, int>::iterator it(bst.minimum(bst.getRoot()));
	it++;
	std::cout << it->first << std::endl;
	return 0;
}