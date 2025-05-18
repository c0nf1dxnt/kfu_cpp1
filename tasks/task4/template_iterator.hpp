#pragma once

#include <iterator>

/**
 * @brief
 * Класс итератора, представлен для возможности использовать в векторе
 * обаладает стандартными операциями с итераторами
 * @tparam T 
 */
template <class T>
class Iterator : public std::iterator<std::random_access_iterator_tag, T>
{
public:
    using value_type = T;
    using reference = T&;
    using pointer = T*;
    using iterator = Iterator<T>;

    Iterator(pointer ptr) noexcept
        : ptr_(ptr)
    {}

    reference operator * () const noexcept {
        return *ptr_;
    }

    bool operator == (const iterator & other) const noexcept {
        return ptr_ == other.ptr_;
    }

    bool operator != (const iterator & other) const noexcept {
        return ptr_ != other.ptr_;
    }

    bool operator < (const iterator & other) const noexcept {
        return ptr_ < other.ptr_;
    }

    bool operator > (const iterator & other) const noexcept {
        return ptr_ > other.ptr_;
    }

    bool operator <= (const iterator & other) const noexcept {
        return ptr_ <= other.ptr_;
    }

    bool operator >= (const iterator & other) const noexcept {
        return ptr_ >= other.ptr_;
    }

    iterator operator + (int n) const noexcept {
        return iterator(ptr_ + n);
    }

    iterator & operator += (int n) noexcept {
        ptr_ += n;
        return *this;
    }

    iterator operator - (int n) const noexcept {
        return iterator(ptr_ - n);
    }

    iterator & operator -= (int n) noexcept {
        ptr_ -= n;
        return *this;
    }

    reference operator [] (int n) const noexcept {
        return *(ptr_ + n);
    }

    iterator & operator ++ () noexcept {
        ++ptr_;
        return *this;
    }

    iterator & operator -- () noexcept {
        --ptr_;
        return *this;
    }

    iterator operator ++ (int) noexcept {
        iterator tmp = *this;
        ++ptr_;
        return tmp;
    }

    iterator operator -- (int) noexcept {
        iterator tmp = *this;
        --ptr_;
        return tmp;
    }

    friend iterator operator + (int n, const iterator & it) noexcept {
        return iterator(it.ptr_ + n);
    }

    friend iterator operator - (int n, const iterator & it) noexcept {
        return iterator(it.ptr_ - n);
    }

    friend int operator - (const iterator & lhs, const iterator & rhs) noexcept {
        return lhs.ptr_ - rhs.ptr_;
    }
private:
    pointer ptr_;
};
