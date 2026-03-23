#pragma once
#include <cstddef>

template<typename Item> class Storage
{
    Item *array_;
    size_t size_;
    size_t maxSize_;
public:
    Storage(size_t size) : maxSize_(size);
    ~Storage();
    size_t addItem(const Item& newOne);
    Item& getItem(size_t index) const;
    void deleteItem(size_t index);
    size_t getSize() const;
};
