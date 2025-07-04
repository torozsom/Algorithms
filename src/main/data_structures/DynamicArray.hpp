

#ifndef DYNAMICARRAY_HPP
#define DYNAMICARRAY_HPP


#include <iostream>


/**
 * @class DynamicArray
 *
 * A generic dynamic array class that provides functionalities for adding,
 * inserting, removing, and accessing elements. The internal storage is
 * dynamically resized as needed to accommodate changes in size.
 */
template<typename Type>
class DynamicArray {

private:
    Type* data_;
    unsigned int size_;
    unsigned int capacity_;
    static constexpr unsigned int DEFAULT_CAPACITY = 5;


    /**
     * Copies a specific number of elements from the source array to the destination array.
     *
     * @param source Pointer to the source array from which elements will be copied.
     * @param destination Pointer to the destination array where elements will be copied to.
     * @param count The number of elements to copy from the source to the destination.
     */
    void copyData(const Type* source, Type* destination, const unsigned int count) {
        for (unsigned int i = 0; i < count; ++i)
            destination[i] = source[i];
    }


    /**
     * Resizes the dynamic array to the specified capacity. If the new capacity is less than
     * the default capacity, it is set to the default capacity instead. Copies existing data
     * to the newly allocated memory and updates the capacity.
     *
     * @param new_capacity The new desired capacity for the dynamic array.
     */
    void resize(unsigned int new_capacity) {
        if (new_capacity < DEFAULT_CAPACITY)
            new_capacity = DEFAULT_CAPACITY;

        Type* new_data = nullptr;
        try {
            new_data = new Type[new_capacity];
            copyData(data_, new_data, size_);
        } catch (...) {
            delete[] new_data;
            throw;
        }

        delete[] data_;
        data_ = new_data;
        capacity_ = new_capacity;
    }



public:
    /// Default constructor
    DynamicArray() : data_(nullptr), size_(0), capacity_(DEFAULT_CAPACITY) {
        data_ = new Type[capacity_];
    }

    /// Constructor with initial size
    DynamicArray(const Type* initial_data, const unsigned int initial_size)
        : data_(new Type[initial_size]), size_(initial_size), capacity_(initial_size) {
        copyData(initial_data, data_, initial_size);
    }

    /// Copy constructor
    DynamicArray(const DynamicArray& other)
        : data_(new Type[other.capacity_]), size_(other.size_), capacity_(other.capacity_) {
        copyData(other.data_, data_, size_);
    }

    /// Move constructor
    DynamicArray(DynamicArray&& other) noexcept
        : data_(other.data_), size_(other.size_), capacity_(other.capacity_) {
        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }


    unsigned int getSize() const { return size_; }

    unsigned int getCapacity() const { return capacity_; }

    bool isEmpty() const { return size_ == 0; }


    /// Copy assignment operator
    DynamicArray& operator=(const DynamicArray& other) {
        if (this == &other)
            return *this;

        delete[] data_;
        data_ = new Type[other.capacity_];
        size_ = other.size_;
        capacity_ = other.capacity_;

        copyData(other.data_, data_, size_);
        return *this;
    }

    /// Move assignment operator
    DynamicArray& operator=(DynamicArray&& other) noexcept {
        if (this == &other)
            return *this;

        delete[] data_;
        data_ = other.data_;
        size_ = other.size_;
        capacity_ = other.capacity_;

        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;

        return *this;
    }


    /**
     * Adds an element to the end of the dynamic array. If the array is at full capacity,
     * it resizes to accommodate the new element.
     *
     * @param element The element to be added to the array.
     */
    void addLast(const Type& element) {
        insert(size_, element);
    }


    /**
     * Adds an element to the beginning of the dynamic array. All existing elements
     * are shifted one position to the right to make space for the new element.
     * If the array is at full capacity, it resizes to accommodate the new element.
     *
     * @param element The element to be added at the beginning of the array.
     */
    void addFirst(const Type& element) {
        insert(0, element);
    }


    /**
     * Inserts an element at the specified index in the dynamic array.
     * Shifts all subsequent elements one position to the right. If the array
     * is at full capacity, it resizes to accommodate the new element.
     *
     * @param idx The position at which the element is to be inserted. Must be within the range [0, size_].
     * @param element The element to be inserted into the array.
     * @throws std::out_of_range If the specified index is greater than the size of the array.
     */
    void insert(const unsigned int idx, const Type& element) {
        if (idx > size_)
            throw std::out_of_range("Index out of range");

        if (size_ == capacity_)
            resize(capacity_ * 2);

        for (unsigned int i = size_; i > idx; --i)
            data_[i] = data_[i - 1];

        data_[idx] = element;
        ++size_;
    }


    /**
     * Removes an element at the specified index from the dynamic array.
     * Shifts all subsequent elements one position to the left. Reduces the
     * size of the array. If the size falls below one-fourth of the capacity,
     * the array is resized to half of its current capacity.
     *
     * @param idx The position of the element to be removed. Must be within the range [0, size_ - 1].
     * @throws std::out_of_range If the specified index is greater than or equal to the size of the array.
     */
    void remove(const unsigned int idx) {
        if (idx >= size_)
            throw std::out_of_range("Index out of range");

        for (unsigned int i = idx; i < size_ - 1; ++i)
            data_[i] = data_[i + 1];

        --size_;

        if (size_ > 0 && size_ <= capacity_ / 4)
            resize(capacity_ / 2);
    }


    /**
     * Retrieves the element at the specified index in the dynamic array.
     *
     * @param idx The position of the element to retrieve. Must be within the range [0, size_ - 1].
     * @return A reference to the element at the specified index in the dynamic array.
     * @throws std::out_of_range If the specified index is greater than or equal to the size of the array.
     */
    Type& get(const unsigned int idx) {
        if (idx >= size_)
            throw std::out_of_range("Index out of range");

        return data_[idx];
    }


    /**
     * Retrieves the element at the specified index in the dynamic array.
     *
     * @param idx The position of the element to retrieve. Must be within the range [0, size_ - 1].
     * @return A reference to the element at the specified index in the dynamic array.
     * @throws std::out_of_range If the specified index is greater than or equal to the size of the array.
     */
    const Type& get(const unsigned int idx) const {
        if (idx >= size_)
            throw std::out_of_range("Index out of range");

        return data_[idx];
    }


    /**
     * Accesses the element at the specified index in the dynamic array.
     *
     * @param idx The position of the element to access. Must be within the range [0, size_ - 1].
     * @return A reference to the element at the specified index in the dynamic array.
     * @throws std::out_of_range If the specified index is greater than or equal to the size of the array.
     */
    Type& operator[](const unsigned int idx) {
        return get(idx);
    }


    /**
     * Provides read-only access to the element at the specified index in the dynamic array.
     *
     * @param idx The position of the element to access. Must be within the range [0, size_ - 1].
     * @return A constant reference to the element at the specified index in the dynamic array.
     * @throws std::out_of_range If the specified index is greater than or equal to the size of the array.
     */
    const Type& operator[](const unsigned int idx) const {
        return get(idx);
    }


    /**
     * Clears the contents of the dynamic array, deallocating the current memory.
     * Resets the array to its default capacity, size to zero, and reinitializes
     * the underlying data.
     */
    void clear() {
        delete[] data_;
        data_ = new Type[DEFAULT_CAPACITY];
        size_ = 0;
        capacity_ = DEFAULT_CAPACITY;
    }


    /// Destructor
    ~DynamicArray() { delete[] data_; }

};


#endif  // DYNAMICARRAY_HPP
