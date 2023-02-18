
#pragma once

#include <algorithm>
#include <cassert>
#include <functional>
#include <iostream>

template <class T> class CyclicQueue
{
  public:
    CyclicQueue(){};
    CyclicQueue(size_t n);
    CyclicQueue(const CyclicQueue& other);
    CyclicQueue(CyclicQueue&& other) noexcept;
    auto operator=(const CyclicQueue& other);
    auto operator=(CyclicQueue&& other) noexcept;
    ~CyclicQueue();

    T& operator[](size_t index);
    const T& operator[](size_t index) const;

    void resize(size_t n);
    void insert(const T& inp);
    void insert(T&& inp);
    void insert_on_top(const T& inp);
    void insert_on_top(T&& inp);
    T dequeue();
    const T& front() const;
    const T& back() const;
    void traverseQueue(auto func);
    void clear() noexcept;

    size_t size() const noexcept
    {
        return totalSize_;
    };
    size_t nInserted() const noexcept
    {
        return nInserted_;
    };
    size_t frontIndex() const noexcept
    {
        return front_;
    };

  private:
    size_t totalSize_ = 0;
    size_t nInserted_ = 0;
    size_t front_ = 0;
    T* data_ = nullptr;
};

template <class T> void CyclicQueue<T>::insert(const T& inp)
{
    if (totalSize_ == 0 or data_ == nullptr)
        throw std::runtime_error(
            "CyclicQueue was never allocated. Please call resize or pass the size in the constructor");
    (*this)[nInserted_] = inp;
    if (nInserted_ < totalSize_)
    {
        nInserted_++;
    }
    else if (nInserted_ == totalSize_)
    {
        front_++;
    }
}

template <class T> void CyclicQueue<T>::insert_on_top(const T& inp)
{
    if (totalSize_ == 0 or data_ == nullptr)
        throw std::runtime_error(
            "CyclicQueue was never allocated. Please call resize or pass the size in the constructor");
    if (front_ != 0)
    {
        front_--;
    }
    else
    {
        front_ = totalSize_ - 1;
    }
    if (nInserted_ < totalSize_)
    {
        nInserted_++;
    }
    (*this)[0] = inp;
}

template <class T> void CyclicQueue<T>::insert(T&& inp)
{
    if (totalSize_ == 0 or data_ == nullptr)
        throw std::runtime_error(
            "CyclicQueue was never allocated. Please call resize or pass the size in the constructor");
    (*this)[nInserted_] = std::move(inp);
    if (nInserted_ < totalSize_)
    {
        nInserted_++;
    }
    else if (nInserted_ == totalSize_)
    {
        front_++;
    }
}

template <class T> void CyclicQueue<T>::insert_on_top(T&& inp)
{
    if (totalSize_ == 0 or data_ == nullptr)
        throw std::runtime_error(
            "CyclicQueue was never allocated. Please call resize or pass the size in the constructor");
    if (front_ != 0)
    {
        front_--;
    }
    else
    {
        front_ = totalSize_ - 1;
    }
    if (nInserted_ < totalSize_)
    {
        nInserted_++;
    }
    (*this)[0] = std::move(inp);
}

template <class T> T CyclicQueue<T>::dequeue()
{
    if (nInserted_ == 0)
        throw std::runtime_error("Cannot dequeue empty queue");
    T ref = (*this)[0];
    nInserted_--;
    front_++;
    return ref;
}

template <class T> T& CyclicQueue<T>::operator[](size_t index)
{
    assert((((front_ + index) % totalSize_) < totalSize_));
    assert((data_ != nullptr));
    return data_[(front_ + index) % totalSize_];
};

template <class T> const T& CyclicQueue<T>::operator[](size_t index) const
{
    assert((((front_ + index) % totalSize_) < totalSize_));
    assert((data_ != nullptr));
    return data_[(front_ + index) % totalSize_];
};

template <class T> const T& CyclicQueue<T>::front() const
{
    return (*this)[0];
}

template <class T> const T& CyclicQueue<T>::back() const
{
    return (*this)[nInserted_ - 1];
}

template <class T> void CyclicQueue<T>::traverseQueue(auto func)
{
    for (size_t i = 0; i < nInserted_; ++i)
    {
        func((*this)[i]);
    }
}

template <class T> void CyclicQueue<T>::resize(size_t n)
{
    if (n == 0)
    {
        if (data_ != nullptr)
            delete[] data_;
        data_ = nullptr;
        front_ = 0;
        nInserted_ = 0;
        totalSize_ = 0;
    }
    else
    {
        T* newData = new T[n];
        size_t disp = nInserted_ <= n ? 0 : nInserted_ - n;
        nInserted_ = nInserted_ <= n ? nInserted_ : n;
        for (size_t i = 0; i < nInserted_; ++i)
        {
            newData[i] = (*this)[i + disp];
        }
        totalSize_ = n;
        front_ = 0;
        delete[] data_;
        data_ = newData;
    }
}

template <class T> void CyclicQueue<T>::clear() noexcept
{
    nInserted_ = 0;
    front_ = 0;
}

template <class T> CyclicQueue<T>::CyclicQueue(size_t n)
{
    totalSize_ = n;
    data_ = new T[n];
};

template <class T> CyclicQueue<T>::~CyclicQueue()
{
    if (data_ != nullptr)
    {
        delete[] data_;
    }
}

template <class T> CyclicQueue<T>::CyclicQueue(const CyclicQueue<T>& other)
{
    totalSize_ = other.size();
    nInserted_ = other.nInserted();
    front_ = other.frontIndex();
    delete[] data_;
    data_ = new T[totalSize_];
    std::copy_n(other.data_, totalSize_, data_);
}

template <class T> auto CyclicQueue<T>::operator=(const CyclicQueue<T>& other)
{
    totalSize_ = other.size();
    nInserted_ = other.nInserted();
    front_ = other.frontIndex();
    delete[] data_;
    data_ = new T[totalSize_];
    std::copy_n(other.data_, totalSize_, data_);
}

template <class T> CyclicQueue<T>::CyclicQueue(CyclicQueue<T>&& other) noexcept
{
    totalSize_ = other.size();
    nInserted_ = other.nInserted();
    front_ = other.frontIndex();
    data_ = other.data_;
    other.data_ = nullptr;
    other.resize(0);
}

template <class T> auto CyclicQueue<T>::operator=(CyclicQueue<T>&& other) noexcept
{
    totalSize_ = other.size();
    nInserted_ = other.nInserted();
    front_ = other.frontIndex();
    data_ = other.data_;
    other.data_ = nullptr;
    other.resize(0);
}

template <class T> std::ostream& operator<<(std::ostream& out, const CyclicQueue<T>& inp)
{
    out << "Cyclic Queue Metadata:\n";
    out << "   Total Size  = " << inp.size() << "\n";
    out << "   Front Index = " << inp.frontIndex() << "\n";
    out << "   Number of Items in Queue = " << inp.nInserted() << "\n";
    out << "Cyclic Queue Entries:\n";
    for (size_t i = 0; i < inp.nInserted(); i++)
    {
        out << "   " << inp[i] << "\n";
    }
    out << "\n";
    return out;
}