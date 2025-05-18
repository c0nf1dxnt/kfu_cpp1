#pragma once
#include "template_iterator.hpp"

#include <stdexcept>
#include <utility>

template <class T>
class Vector
{
public: 
    static const size_t reserve_miltiply_ = 2;
    static const size_t empty_vector_size_ = 8;
public:
    using iterator = Iterator<T>;
    using value_type = T;
    using pointer = T*;
    using reference = T&;
    using const_reference = const T&;
    using size_type = size_t;

    Vector()
        : data_(new T[empty_vector_size_])
        , size_(0)
        , capacity_(empty_vector_size_)
    {
    }

    ~Vector()
    {
        delete[] data_;
    }

    reference operator[] (size_type n) {
        if (n >= size_) {
            throw std::out_of_range("out of range");
        }
        return data_[n];
    }

    const_reference operator[] (size_type n) const {
        if (n >= size_) {
            throw std::out_of_range("out of range");
        }
        return data_[n];
    }

    void push_back(const T & value) {
        if (size_ == capacity_) {
            reserve(capacity_ * reserve_miltiply_);
        }
        data_[size_++] = value;
    }

    void push_back(T && value) {
        if (size_ == capacity_) {
            reserve(capacity_ * reserve_miltiply_);
        }
        data_[size_++] = std::move(value);
    }

    void pop_back() {
        if (size_ == 0) {
            throw std::out_of_range("empty vector");
        }
        --size_;
        data_[size_] = T();
    }

    void clear() {
        for (size_type i = 0; i < size_; ++i) {
            data_[i] = T();
        }
        size_ = 0;
    }

    void reserve(size_type new_size) {
        if (new_size <= capacity_) {
            return;
        }
        
        pointer new_data = new T[new_size];
        for (size_type i = 0; i < size_; ++i) {
            new_data[i] = std::move(data_[i]);
        }
        
        delete[] data_;
        data_ = new_data;
        capacity_ = new_size;
    }

    void resize(size_type new_size) {
        if (new_size > capacity_) {
            reserve(new_size);
        }
        
        if (new_size > size_) {
            for (size_type i = size_; i < new_size; ++i) {
                data_[i] = T();
            }
        } else if (new_size < size_) {
            for (size_type i = new_size; i < size_; ++i) {
                data_[i] = T();
            }
        }
        
        size_ = new_size;
    }

    iterator begin() const noexcept {
        return iterator(data_);
    }

    iterator end() const noexcept {
        return iterator(data_ + size_);
    }

    size_type size() const noexcept {
        return size_;
    }

    size_type capacity() const noexcept {
        return capacity_;
    }

    bool empty() const noexcept {
        return size_ == 0;
    }

private:
    pointer data_;
    size_type size_;
    size_type capacity_;
};
