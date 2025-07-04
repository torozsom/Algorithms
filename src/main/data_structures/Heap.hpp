

#ifndef HEAP_HPP
#define HEAP_HPP


#include <bitset>

#include "BinaryTree.hpp"



/**
 * @class Heap: Abstract class
 *
 * A generic heap data structure that stores elements of a given type.
 * The heap is a binary tree structure that satisfies the heap property,
 * which depends on the type of heap (min-heap or max-heap).
 *
 * In a min-heap, the parent node is less than or equal to its children, while in a max-heap,
 * the parent node is greater than or equal to its children. The heap structure is commonly used to
 * implement priority queues and sorting algorithms. This class provides common
 * functionality for both min-heaps and max-heaps.
 *
 * @tparam Type The type of elements stored in the heap.
 */
template <typename Type>                    // Protected inheritance
class Heap : public BinaryTree<Type> {   // means that the public and protected members
                                            // in the parent are protected here
protected:

    virtual void heapifyUp(Node<Type>* node) = 0;
    virtual void heapifyDown(Node<Type>* node) = 0;


    /**
     * Finds and returns the rightmost (last) node in the binary tree.
     *
     * The method starts from the root node and repeatedly traverses to the right child
     * until it reaches a node with no right child. The node at this position is considered
     * the last node in the tree based on a binary structure where right children are considered
     * after left children.
     *
     * @return A pointer to the last node in the tree, or nullptr if the tree is empty.
     */
    Node<Type>* findLastNode() const {
        if (this->isEmpty())
            return nullptr;

        unsigned int n = this->size();
        std::bitset<32> binary(n);
        std::string path = binary.to_string();

        unsigned int index = path.find('1');
        path = path.substr(index + 1);

        Node<Type>* current = this->root_;
        for (char direction : path) {
            if (direction == '0')
                current = current->left;
            else
                current = current->right;

            if (current == nullptr)
                break;
        }

        return current;
    }



    /**
     * Swaps the data stored in two nodes of the binary tree.
     *
     * This method exchanges the `data` field of the two provided nodes. If either node
     * is null, the method does nothing.
     *
     * @param node1 Pointer to the first node involved in the swap operation.
     * @param node2 Pointer to the second node involved in the swap operation.
     */
    void swapData(Node<Type>* node1, Node<Type>* node2) {
        if (node1 == nullptr || node2 == nullptr)
            return;

        Type temp = node1->data;
        node1->data = node2->data;
        node2->data = temp;
    }



public:

    void insertLeft(const Type& element) = delete;
    void insertRight(const Type& element) = delete;

    virtual void insert(const Type& element) = 0;


    /**
     * Removes and returns the root element of the heap, maintaining the heap property.
     *
     * This method retrieves the value of the root node, then replaces the root with
     * the value of the last node in level-order. After removing the last node, the
     * heap property is restored by a downward adjustment from the root.
     * If the heap is empty, an exception is thrown.
     *
     * @return The value of the root element that was removed from the heap.
     * @throws std::out_of_range If the heap is empty.
     */
    Type extractRoot() {
        if (this->isEmpty())
            throw std::out_of_range("Heap is empty. Cannot extract root.");

        Type rootValue = this->root_->data;
        Node<Type>* lastNode = this->findLastNode();

        if (lastNode == this->root_) {
            delete this->root_;
            this->root_ = nullptr;
        } else {
            this->root_->data = lastNode->data;

            if (lastNode->parent->left == lastNode)
                lastNode->parent->left = nullptr;
            else
                lastNode->parent->right = nullptr;

            delete lastNode;
            heapifyDown(this->root_);
        }

        --this->size_;
        return rootValue;
    }


    /**
     * Retrieves and returns the value stored at the root of the heap.
     *
     * This method provides access to the root element of the heap without removing it.
     * If the heap is empty, an exception is thrown to indicate the error.
     *
     * @return The value stored at the root of the heap.
     * @throws std::out_of_range If the heap is empty.
     */
    Type peekRoot() const {
        if (this->isEmpty())
            throw std::out_of_range("Heap is empty");
        return this->root_->data;
    }


    /// Destructor
    ~Heap() override = default;

};

#endif //HEAP_HPP
