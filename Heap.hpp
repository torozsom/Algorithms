//
// Created by toron on 2024. 12. 26..
//

#ifndef HEAP_HPP
#define HEAP_HPP


#include "BinaryTree.hpp"


template <typename Type>
struct HeapNode : Node<Type> {
    HeapNode* parent;
    explicit HeapNode(const Type& data) : Node<Type>(data), parent(nullptr) {}
};


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
class Heap : protected BinaryTree<Type> {   // means that the public and protected members
                                            // in the parent are protected here

    using HeapNode = HeapNode<Type>;

protected:

    virtual void heapifyUp(HeapNode* node) = 0;
    virtual void heapifyDown(HeapNode* node) = 0;


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
    HeapNode* findLastNode() const {
        if (this->root_ == nullptr)
            return nullptr;

        Node<Type>* current = this->root_;
        while (current->right != nullptr)
            current = current->right;
        return static_cast<HeapNode*>(current);
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
    void swapData(HeapNode* node1, HeapNode* node2) {
        if (node1 == nullptr || node2 == nullptr)
            return;

        Type temp = node1->data;
        node1->data = node2->data;
        node2->data = temp;
    }



public:
    Heap() = default;


    void insertLeft(const Type& element) = delete;
    void insertRight(const Type& element) = delete;


    virtual void insert(const Type& element) = 0;
    virtual void remove(const Type& element) = 0;
    virtual Type extractRoot() = 0;


    bool isEmpty() const { return this->root_ == nullptr; }

    unsigned int size() const { return this->size_; }


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
        if (this->root_ == nullptr)
            throw std::out_of_range("Heap is empty");
        return this->root_->data;
    }


    /**
     * Clears all elements from the heap, removing nodes and resetting the size.
     *
     * This method overrides the `clear` method of the BinaryTree class to ensure
     * proper cleanup specific to the heap structure. It removes all nodes in the heap
     * and sets the size of the heap to zero. This process does not assume any specific
     * heap configuration after the method is executed.
     */
    void clear() override {
        BinaryTree<Type>::clear();
    }


    /// Destructor
    ~Heap() override { Heap::clear(); }

};

#endif //HEAP_HPP
