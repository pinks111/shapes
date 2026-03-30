#pragma once
#include <cstddef>
#include <iostream>
#include <string>

template<typename Item> class Storage {
    Item *array;
    size_t size;
    size_t capacity;
    
public:
    Storage() : array(nullptr), size(0), capacity(0) {}
    
    Storage(size_t start_capacity) : array(nullptr), size(0), capacity(start_capacity) {
        if (capacity > 0) {
            array = new Item[capacity];
        }
    }
    
    Storage(const Storage& other) : size(other.size), capacity(other.capacity) {
        array = new Item[capacity];
        for(size_t i = 0; i < size; ++i) {
            array[i] = other.array[i];
        }
    }
    
    Storage& operator=(const Storage& other) {
        if(this != &other) {
            delete[] array;
            size = other.size;
            capacity = other.capacity;
            array = new Item[capacity];
            for(size_t i = 0; i < size; ++i) {
                array[i] = other.array[i];
            }
        }
        return *this;
    }
    
    ~Storage() {
        delete[] array;
    }
    
    void addItem(const Item &item) {
        if (capacity == 0) {
            capacity = 10;
            array = new Item[capacity];
        }
        else if (size == capacity) {
            capacity *= 2;
            Item *new_array = new Item[capacity];
            for (size_t i = 0; i < size; ++i) {
                new_array[i] = array[i];
            }
            delete[] array;
            array = new_array;
        }
        array[size] = item;
        ++size;
    }
    
    Item& getItem(size_t index) {
        return array[index];
    }
    
    const Item& getItem(size_t index) const {
        return array[index];
    }
    
    size_t getSize() const {
        return size;
    }
    
    void print() const {
        if (size == 0) {
            std::cout << "  (empty)\n";
            return;
        }
        
        for (size_t i = 0; i < size; ++i) {
            std::cout << array[i] << "\n";
        }
    }
};