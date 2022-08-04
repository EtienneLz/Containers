#include "red_black_tree.hpp"
#include "bidirectional_iterator.hpp"
#include "make_pair.hpp"

int main() {
	ft::RedBlackTree<int, int> bst;
	bst.insert(ft::make_pair(1, 1));
	bst.insert(ft::make_pair(2, 1));
	bst.insert(ft::make_pair(3, 1));
	bst.insert(ft::make_pair(4, 1));
	bst.insert(ft::make_pair(5, 1));
	bst.insert(ft::make_pair(6, 1));
	bst.insert(ft::make_pair(7, 1));
	bst.printTree();

	ft::RedBlackTree<int, int>::iterator it(bst.minimum(bst.getRoot()));
	it++;
	std::cout << it->first << std::endl;
	return 0;
}