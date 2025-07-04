
#include "Tests.h"


void testBinarySearchTree() {

    std::cout << "\n\n==== Testing Binary Search Tree ====" << std::endl;

    // **Insert Elements**
    int array[7] = {50, 30, 70, 20, 40, 60, 80};
    BinarySearchTree bst(array, 7);

    // **Traversals**
    std::cout << "\nIn-Order Traversal (Should be sorted): ";
    bst.printInOrder();

    std::cout << "\nPre-Order Traversal: ";
    bst.printPreOrder();

    std::cout << "\nPost-Order Traversal: ";
    bst.printPostOrder();

    std::cout << "\nTree Height: " << bst.getHeight() << "\n";

    // **Remove Elements**
    std::cout << "\n-- Removing Leaf Node (20) --" << std::endl;
    bst.remove(20);
    bst.printInOrder();

    std::cout << "\n-- Removing Node with One Child (30) --" << std::endl;
    bst.remove(30);
    bst.printInOrder();

    std::cout << "\n-- Removing Node with Two Children (50) --" << std::endl;
    bst.remove(50);
    bst.printInOrder();

    std::cout << "\nTree Height after deletions: " << bst.getHeight() << "\n";

    // **Clear Tree**
    std::cout << "\n-- Clearing the Tree --" << std::endl;
    bst.clear();
    std::cout << "Tree cleared. Is empty? " << (bst.getHeight() == 0 ? "Yes" : "No") << "\n";
}
