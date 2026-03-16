#pragma once
#include <cstddef>

template<typename Item> class Storage
{
    Item *array_;
    size_t size_;
    size_t maxSize_;
public:
    Storage(size_t size): maxSize_(size)
    {
        Item *array_ = new Item[maxSize_];
    }
    ~Storage()
    {
        delete[] array_;
    }
    size_t addItem(const Item &newOne)
    {
        array_[size_] = newOne;
        size_++;
        return size_-1;
    }
    Item &getItem(size_t index) const
    {
        return array_[index];
    }
    void deleteItem(size_t index)
    {
        for (size_t i=index; i<size_-1; i++)
        {
            array_[i] = array_[i+1];
        }
        size_--;
    }
    size_t getSize() const
    {
        return size_;
    }
};
