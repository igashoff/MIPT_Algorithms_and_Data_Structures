//
//  main.cpp
//  shared_ptr
//
//  Created by Igashov_Ilya on 02.05.16.
//  Copyright (c) 2016 Igashov_Ilya. All rights reserved.
//

#include <iostream>
#include <cassert>

template <typename T>
void default_delete(T * ptr)
{
    delete ptr;
}

template <class T>
void default_array_delete(T *p)
{
    delete [] p;
}

template <typename T>
class shared_ptr
{
    T *pointer;
    size_t *counter;
    void (*del) (T *);
    
public:
    
    shared_ptr();
    shared_ptr(T * ptr);
    shared_ptr(T * ptr, void (*delete_fn) (T *));
    
    shared_ptr(const shared_ptr & other);
    shared_ptr(shared_ptr && other);
    
    shared_ptr & operator =(const shared_ptr & other);
    shared_ptr & operator =(shared_ptr && other);
    
    ~shared_ptr();
    
    void swap(shared_ptr & other);
    void reset();
    void reset(T * other);
    void reset(T * other, void (*delete_fn)(T * ));
    
    T * get() const;
    T * operator ->() const;
    T & operator *() const;
    size_t use_count() const;
    bool unique() const;
    operator bool() const;
};

template <typename T>
shared_ptr<T>::shared_ptr(): pointer(nullptr), counter(nullptr), del(default_delete<T>) {}

template <typename T>
shared_ptr<T>::shared_ptr(T * ptr): pointer(ptr), counter(new size_t(1)), del(default_delete<T>) {}


template <typename T>
shared_ptr<T>::shared_ptr(T * ptr, void (*delete_fn) (T *)): pointer(ptr), counter(new size_t(1)), del(delete_fn) {}

template <typename T>
shared_ptr<T>::shared_ptr(const shared_ptr & other): shared_ptr(other.pointer, other.del)
{
    counter = other.counter;
    ++*counter;
}

template <typename T>
shared_ptr<T>::shared_ptr(shared_ptr && other): pointer(std::move(other.pointer)), counter(std::move(other.counter)),
        del(std::move(other.del))
{
    other.pointer = nullptr;
    other.counter = nullptr;
}

template <typename T>
shared_ptr<T> & shared_ptr<T>::operator =(const shared_ptr & other)
{
    if (this != &other)
    {
        this->reset();
        pointer = other.pointer;
        counter = other.counter;
        del = other.del;
        ++*counter;
    }
    return *this;
}

template <typename T>
shared_ptr<T> & shared_ptr<T>::operator =(shared_ptr && other)
{
    shared_ptr::swap(other);
    return *this;
}

template <typename T>
shared_ptr<T>::~shared_ptr<T>()
{
    if (counter != nullptr && --*counter == 0)
    {
        del(pointer);
        delete(counter);
    }
}

template <typename T>
void shared_ptr<T>::swap(shared_ptr & other)
{
    std::swap(pointer, other.pointer);
    std::swap(counter, other.counter);
    std::swap(del, other.del);
}

template <typename T>
void shared_ptr<T>::reset()
{
    this->~shared_ptr();
    pointer = nullptr;
    counter = nullptr;
}

template <typename T>
void shared_ptr<T>::reset(T * other)
{
    reset();
    pointer = other;
    counter = new size_t(1);
}

template <typename T>
void shared_ptr<T>::reset(T * other, void(*delete_fn)(T *))
{
    reset();
    pointer = other;
    counter = new size_t(1);
    del = delete_fn;
}


template <typename T>
T * shared_ptr<T>::get() const
{
    return pointer;
}

template <typename T>
T * shared_ptr<T>::operator ->() const
{
    return pointer;
}

template <typename T>
T & shared_ptr<T>::operator *() const
{
    return *pointer;
}

template <typename T>
size_t shared_ptr<T>::use_count() const
{
    return (counter == nullptr)? 0 : *counter;
}

template <typename T>
bool shared_ptr<T>::unique() const
{
    return use_count() == 1;
}

template <typename T>
shared_ptr<T>::operator bool() const
{
    return pointer != nullptr;
}

int main()
{
    shared_ptr<int> foo;
    shared_ptr<int> bar (new int(10));
    
    foo = bar;
    
    std::cout << bar.use_count() << std::endl;
    
    int * ptr = new int(20);
    bar = ptr;
    
    bar.reset();
    assert(!bar);
    
    foo.reset(new int(30), default_delete);
    std::cout << *foo << std::endl;
    bar = foo;
    std::cout << bar.use_count() << std::endl;
    return 0;
}
