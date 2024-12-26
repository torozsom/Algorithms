

#ifndef BINARYTREE_HPP
#define BINARYTREE_HPP


#include <iostream>


/**
 * Represents a node in a binary tree structure.
 *
 * @tparam Type The data type stored in the node.
 */
template<typename Type>
struct Node {
    Type data;
    Node* left;
    Node* right;
    explicit Node(const Type& data) : data(data), left(nullptr), right(nullptr) {}
};


/**
 * @class BinaryTree
 * A binary tree data structure that stores elements of a given type.
 *
 * The binary tree is a tree data structure in which each node has at most two children,
 * referred to as the left child and the right child. The tree is defined recursively,
 * with each child node being the root of its own subtree.
 *
 * @tparam Type The type of elements stored in the binary tree.
 */
template<typename Type>
class BinaryTree {

protected:
    Node<Type>* root;


private:

    /**
     * Creates a new copy of a binary tree node and all its child nodes recursively.
     *
     * @param otherNode A pointer to the node to be copied. If nullptr, returns nullptr.
     * @return A pointer to the newly created node, which is a copy of the input node along with its subtree.
     */
    Node<Type>* copyNode(Node<Type>* otherNode) {
        if (otherNode == nullptr)
            return nullptr;

        Node<Type>* newNode = new Node(otherNode->data);
        newNode->left = copyNode(otherNode->left);
        newNode->right = copyNode(otherNode->right);
        return newNode;
    }


    /**
     * Recursively copies all elements from another binary tree into the current tree.
     *
     * @param other The binary tree whose elements are to be copied into the current tree.
     */
    void recursiveCopy(const BinaryTree& other) {
        root = copyNode(other.root);
    }



protected:

    /**
     * Recursively calculates the height of the binary tree.
     *
     * @param node Pointer to the current node being visited in the recursive process.
     * @return The height of the binary tree.
     */
    unsigned recursiveHeight(Node<Type>* node) const {
        if (node == nullptr)
            return 0;

        unsigned leftHeight = recursiveHeight(node->left);
        unsigned rightHeight = recursiveHeight(node->right);
        return 1 + std::max(leftHeight, rightHeight);
    }


    /**
     * Performs an in-order traversal of the binary tree recursively and outputs the data of each node.
     *
     * @param node Pointer to the current node being visited during the in-order traversal.
     */
    void recursiveInOrder(Node<Type>* node) const {
        if (node == nullptr)
            return;

        recursiveInOrder(node->left);
        std::cout << node->data << " ";
        recursiveInOrder(node->right);
    }


    /**
     * Performs a pre-order traversal of the binary tree recursively, visiting nodes in the order:
     * root, left subtree, right subtree.
     *
     * @param node The current node in the binary tree being visited during the traversal.
     */
    void recursivePreOrder(Node<Type>* node) const {
        if (node == nullptr)
            return;

        std::cout << node->data << " ";
        recursivePreOrder(node->left);
        recursivePreOrder(node->right);
    }


    /**
     * Performs a recursive post-order traversal of the binary tree and processes each node.
     * The traversal visits the left subtree, then the right subtree, and finally the current node.
     *
     * @param node Pointer to the current node being visited in the traversal process.
     */
    void recursivePostOrder(Node<Type>* node) const {
        if (node == nullptr)
            return;

        recursivePostOrder(node->left);
        recursivePostOrder(node->right);
        std::cout << node->data << " ";
    }


    /**
     * Recursively clears the binary tree by deallocating memory occupied by all nodes.
     *
     * @param node Pointer to the current node in the binary tree that is being cleared.
     */
    void recursiveClear(Node<Type>* node) {
        if (node == nullptr)
            return;

        recursiveClear(node->left);
        recursiveClear(node->right);
        delete node;
    }



public:
    /// Default constructor
    BinaryTree() : root(nullptr) {}

    /// Copy constructor
    BinaryTree(const BinaryTree& other) : root(nullptr) {
        recursiveCopy(other);
    }

    /// Move constructor
    BinaryTree(BinaryTree&& other) noexcept : root(other.root) {
        other.root = nullptr;
    }


    /// Assignment operator
    BinaryTree& operator=(const BinaryTree& other) {
        if (this == &other)
            return *this;

        clear();
        recursiveCopy(other);
        return *this;
    }


    /// Move assignment operator
    BinaryTree& operator=(BinaryTree&& other) noexcept {
        if (this == &other)
            return *this;

        clear();
        root = other.root;
        other.root = nullptr;
        return *this;
    }


    Node<Type>* getRoot() const { return root; }

    unsigned int getHeight() const { return recursiveHeight(root); }


    /**
     * Inserts an element as the rightmost node of the binary tree.
     *
     * @param element The element to be inserted into the rightmost position.
     */
    void insertRight(const Type& element) {
        if (root == nullptr) {
            root = new Node(element);
            return;
        }

        Node<Type>* current = root;
        while (current->right != nullptr)
            current = current->right;
        current->right = new Node(element);
    }


    /**
     * Inserts an element as the leftmost child of the binary tree.
     *
     * @param element The element to be inserted at the leftmost position of the binary tree.
     */
    void insertLeft(const Type& element) {
        if (root == nullptr) {
            root = new Node(element);
            return;
        }

        Node<Type>* current = root;
        while (current->left != nullptr)
            current = current->left;
        current->left = new Node(element);
    }


    /// Prints the elements of the binary tree in in-order traversal.
    void printInOrder() const {
        recursiveInOrder(root);
    }


    /// Prints the elements of the binary tree in pre-order traversal.
    void printPreOrder() const {
        recursivePreOrder(root);
    }


    /// Prints the elements of the binary tree in post-order traversal.
    void printPostOrder() const {
        recursivePostOrder(root);
    }


    /**
     * Clears the binary tree by deallocating all nodes and resetting the tree to an empty state.
     *
     * This method ensures that all allocated memory for the tree nodes is released,
     * leaving the root pointer as nullptr.
     */
    void clear() {
        recursiveClear(root);
        root = nullptr;
    }


    /// Destructor
    ~BinaryTree() { clear(); }

};

#endif //BINARYTREE_HPP