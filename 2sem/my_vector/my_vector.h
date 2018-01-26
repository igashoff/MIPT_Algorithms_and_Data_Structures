//
//  header.h
//  Vector
//
//  Created by Igashov_Ilya on 14.03.16.
//  Copyright (c) 2016 Igashov_Ilya. All rights reserved.
//

#ifndef Vector_header_h
#define Vector_header_h

#include <iostream>
#include <cmath>

template <typename T>
class Vector
{
private:
    T *Arr;
    char *Ptr;
    size_t Size;
    size_t Capacity;
public:
    Vector(size_t size_);
    Vector(const Vector & other);
    ~Vector();
    const Vector & operator =(const Vector & other);
    const T & operator [](size_t index) const;
    T & operator [](size_t index);
    bool operator ==(const Vector & right_operand) const;
    bool operator <=(const Vector & right_operand) const;
    bool operator >=(const Vector & right_operand) const;
    bool operator <(const Vector & right_operand) const;
    bool operator >(const Vector & right_operand) const;
    void PushBack(const T & x);                                                                 //ref
    size_t GetSize() const;
    size_t GetCapacity() const;

    friend std::istream & operator >>(std::istream & is, Vector & vector_)
    {
        for (size_t i = 0; i < vector_.Size; i++)
            is >> vector_.Arr[i];
        return is;
    }
    
    friend std::ostream & operator <<(std::ostream & os, const Vector & vector_)
    {
        for (size_t i = 0; i < vector_.Size; i++)
            os << vector_.Arr[i] << std::endl;
        return os;
    }

    
    class iterator
    {
        ptrdiff_t index;
        Vector *vector;
    public:
        typedef T value_type;
        typedef T* pointer;
        typedef T& reference;
        typedef ptrdiff_t difference_type;
        typedef std::random_access_iterator_tag iterator_category;
        
        iterator(Vector *myvector, ptrdiff_t myvector_index);
        iterator & operator ++();
        iterator & operator --();
        bool operator ==(const iterator & right_operand) const;
        bool operator !=(const iterator & right_operand) const;
        bool operator <(const iterator & right_operand) const;
        bool operator >(const iterator & right_operand) const;
        bool operator <=(const iterator & right_operand) const;
        bool operator >=(const iterator & right_operand) const;
        iterator & operator +=(const ptrdiff_t & right_operand);
        iterator operator +(const ptrdiff_t & right_operand) const;
        iterator & operator -=(const ptrdiff_t & right_operand);
        iterator operator -(const ptrdiff_t & right_operand) const;
        ptrdiff_t operator -(const iterator & right_operand) const;
        T & operator *();
    };
    
    iterator begin();
    iterator end();
};


//VECTOR<T> METHODS


template <typename T>
Vector<T>::Vector(size_t size_)
{
    Ptr = new char[size_ * sizeof(T) / sizeof(char)];
    
    for (int i = 0; i < size_; ++i)
        new(Ptr + i * sizeof(T)) T();
    
    Arr =(T *)Ptr;
    
    Size = size_;
    Capacity = size_;
}

template <typename T>
Vector<T>::Vector(const Vector & other)
{
    Ptr = new char[other.Capacity * sizeof(T) / sizeof(char)];
    
    for (int i = 0; i < other.Size; ++i)
        new(Ptr + i * sizeof(T)) T();
    
    Arr =(T *)Ptr;

    for (int i = 0; i < other.Size; ++i)
    {
        Arr[i] = other.Arr[i];
    }
    
    Size = other.Size;
    Capacity = other.Capacity;
}

template <typename T>
Vector<T>::~Vector()
{
    for (int i = 0; i < Size; ++i) Arr[i].~T();
    delete [] Arr;                                                                      //ptr
}

template <typename T>
const Vector<T> & Vector<T>::operator =(const Vector & other)
{
    if (this != & other)
    {
        for (int i = 0; i < Size; ++i) Arr[i].~T();
        delete [] Arr;
        
        Size = other.Size;
        Capacity = other.Capacity;
        
        Ptr = new char[other.Capacity * sizeof(T) / sizeof(char)];
        
        for (int i = 0; i < other.Size; ++i)
        {
            new(Ptr + i * sizeof(T)) T();
        }
        
        Arr = (T *)Ptr;
        
        for (int i = 0; i < other.Size; ++i)
        {
            Arr[i] = other.Arr[i];
        }

    }
    return *this;
}

template <typename T>
const T & Vector<T>::operator [](size_t index) const
{
    return Arr[index];
}

template <typename T>
T & Vector<T>::operator [](size_t index)
{
    return Arr[index];
}

template <typename T>
bool Vector<T>::operator ==(const Vector & right_operand) const
{
    int i = 0;
    if (Size == right_operand.Size)
    {
        while (Arr[i] == right_operand.Arr[i] && i < Size)
        {
            ++i;
        }
        if (i == Size) return true;
        else return false;
    }
    else return false;
}

template <typename T>
bool Vector<T>::operator <=(const Vector & right_operand) const
{
    int i = 0;
    while (Arr[i] == right_operand.Arr[i] && i < Size && i < right_operand.Size)
    {
        ++i;
    }
    if (i == Size && i == right_operand.Size)
    {
        return true;
    }
    if (i == Size)
    {
        return true;
    } else {
        if (i == right_operand.Size)
        {
            return false;
        } else {
            if (Arr[i] <= right_operand.Arr[i])
            {
                return true;
            } else {
                return false;
            }
        }
    }
}

template <typename T>
bool Vector<T>::operator >=(const Vector & right_operand) const
{
    int i = 0;
    while (Arr[i] == right_operand.Arr[i] && i < Size && i < right_operand.Size)
    {
        ++i;
    }
    if (i == Size && i == right_operand.Size)
    {
        return true;
    }
    if (i == Size)
    {
        return false;
    } else {
        if (i == right_operand.Size)
        {
            return true;
        } else {
            if (Arr[i] >= right_operand.Arr[i])
            {
                return true;
            } else {
                return false;
            }
        }
    }
}

template <typename T>
bool Vector<T>::operator <(const Vector & right_operand) const
{
    int i = 0;
    while (Arr[i] == right_operand.Arr[i] && i < Size && i < right_operand.Size)
    {
        ++i;
    }
    if (i == Size && i == right_operand.Size)
    {
        return false;
    }
    if (i == Size)
    {
        return true;
    } else {
        if (i == right_operand.Size)
        {
            return false;
        } else {
            if (Arr[i] < right_operand.Arr[i])
            {
                return true;
            } else {
                return false;
            }
        }
    }
}

template <typename T>
bool Vector<T>::operator >(const Vector & right_operand) const
{
    int i = 0;
    while (Arr[i] == right_operand.Arr[i] && i < Size && i < right_operand.Size)
    {
        ++i;
    }
    if (i == Size && i == right_operand.Size)
    {
        return false;
    }
    if (i == Size)
    {
        return false;
    } else {
        if (i == right_operand.Size)
        {
            return true;
        } else {
            if (Arr[i] > right_operand.Arr[i])
            {
                return true;
            } else {
                return false;
            }
        }
    }
}

template <typename T>
void Vector<T>::PushBack(const T & x)
{
    if (Size == Capacity)
    {
        Capacity *= 2;
        char *CopyPtr = new char[Capacity * sizeof(T) / sizeof(char)];
        
        for (int i = 0; i < Size + 1; ++i)
        {
            new(CopyPtr + i * sizeof(T)) T();
        }
        
        T *CopyArr = (T *)CopyPtr;
        
        for (int i = 0; i < Size; ++i)
        {
            CopyArr[i] = Arr[i];
        }
        
        for (int i = 0; i < Size; ++i)
        {
            Arr[i].~T();
        }
        delete [] Arr;
        
        Arr = CopyArr;
        Ptr = CopyPtr;
    }
    Arr[++Size - 1] = x;
}

template <typename T>
size_t Vector<T>::GetSize() const
{
    return Size;
}

template <typename T>
size_t Vector<T>::GetCapacity() const
{
    return Capacity;
}


//VECTOR<T> ITERATOR METHODS


template <typename T>
Vector<T>::iterator::iterator(Vector *myvector, ptrdiff_t myvector_index)
{
    vector = myvector;
    index = myvector_index;
}

template <typename T>
typename Vector<T>::iterator & Vector<T>::iterator::operator ++()
{
    ++index;
    return *this;
}

template <typename T>
typename Vector<T>::iterator & Vector<T>::iterator::operator --()
{
    --index;
    return *this;
}

template <typename T>
bool Vector<T>::iterator::operator ==(const Vector::iterator & right_operand) const
{
    if (vector == right_operand.vector && index == right_operand.index) return true;
    else return false;
}

template <typename T>
bool Vector<T>::iterator::operator !=(const Vector::iterator & right_operand) const
{
    if (vector != right_operand.vector || index != right_operand.index) return true;
    else return false;
}

template <typename T>
bool Vector<T>::iterator::operator <(const Vector::iterator & right_operand) const
{
    if (index < right_operand.index) return true;
    else return false;
}

template <typename T>
bool Vector<T>::iterator::operator >(const Vector::iterator & right_operand) const
{
    if (index >right_operand.index) return true;
    else return false;
}

template <typename T>
bool Vector<T>::iterator::operator <=(const Vector::iterator & right_operand) const
{
    if (index <= right_operand.index) return true;
    else return false;
}

template <typename T>
bool Vector<T>::iterator::operator >=(const Vector::iterator & right_operand) const
{
    if (index >= right_operand.index)
    return true;
    else return false;
}

template <typename T>
typename Vector<T>::iterator & Vector<T>::iterator::operator +=(const ptrdiff_t & right_operand)
{
    ptrdiff_t n = right_operand;
    if (n >= 0)
    {
        while (n--) ++index;
    } else {
        while (n++) --index;
    }
    return *this;
}

template <typename T>
typename Vector<T>::iterator Vector<T>::iterator::operator +(const ptrdiff_t & right_operand) const
{
    Vector::iterator tmp = *this;
    return tmp += right_operand;
}

template <typename T>
typename Vector<T>::iterator & Vector<T>::iterator::operator -=(const ptrdiff_t & right_operand)
{
    return *this += -right_operand;
}

template <typename T>
typename Vector<T>::iterator Vector<T>::iterator::operator -(const ptrdiff_t & right_operand) const
{
    Vector::iterator tmp = *this;
    return tmp -= right_operand;
}

template <typename T>
ptrdiff_t Vector<T>::iterator::operator -(const Vector::iterator & right_operand) const
{
    return index - right_operand.index;
}

template <typename T>
T & Vector<T>::iterator::operator *()
{
    return (*vector)[index];
}


//END WITH VECTOR<T> ITERATOR METHODS


template <typename T>
typename Vector<T>::iterator Vector<T>::begin()
{
    Vector::iterator myiterator(this, 0);
    return myiterator;
}

template <typename T>
typename Vector<T>::iterator Vector<T>::end()             
{
    Vector::iterator myiterator(this, GetSize());
    return myiterator;
}

//END WITH VECTOR<T> METHODS

template<>
class Vector<bool>
{
private:
    char *Arr;
    size_t Length;
    size_t Size;
    size_t Capacity;
    
public:
    Vector (size_t size_);
    Vector(const Vector<bool> & other);
    ~Vector();
    const Vector<bool> & operator =(const Vector<bool> & other);
    
    class Element
    {
        friend class Vector<bool>;
        
    private:
        char *array;
        size_t index;
        bool value;
        void ChangeValue();
        
    public:
        Element(const Vector<bool> & vector_, size_t index_);
        const bool & operator =(const bool & other);
        const bool & operator =(const Element & other);
        
        friend std::istream & operator >>(std::istream & is, Element & element)
        {
            is >> element.value;
            element.ChangeValue();
            return is;
        }
        
        friend std::ostream & operator <<(std::ostream & os, const Element & element)
        {
            os << element.value;
            return os;
        }

    };
    
    Element operator [](size_t index);
    const Element operator [](size_t index) const;
    bool operator ==(const Vector<bool> & right_operand) const;
    bool operator <=(const Vector<bool> & right_operand) const;
    bool operator >=(const Vector & right_operand) const;
    bool operator <(const Vector & right_operand) const;
    bool operator >(const Vector & right_operand) const;
    void PushBack(bool x);
    size_t GetSize() const;
    size_t GetCapacity() const;
    
    friend std::istream & operator >>(std::istream & is, Vector<bool> & vector_)
    {
        for (size_t i = 0; i < vector_.Size; i++)
        {
            Element element(vector_, i);
            is >> element;
        }
        return is;
    }
    
    friend std::ostream & operator <<(std::ostream & os, const Vector<bool> & vector_)
    {
        for (size_t i = 0; i < vector_.Size; i++)
            os << vector_[i] << std::endl;
        return os;
    }
    
    class iterator
    {
        ptrdiff_t index;
        Vector<bool> *vector;
    public:
        typedef Element value_type;
        typedef Element* pointer;
        typedef Element & reference;
        typedef ptrdiff_t difference_type;
        typedef std::random_access_iterator_tag iterator_category;
        
        iterator(Vector<bool> *myvector, ptrdiff_t myvector_index);
        iterator & operator ++();
        iterator & operator --();
        bool operator ==(const iterator & right_operand) const;
        bool operator !=(const iterator & right_operand) const;
        bool operator <(const iterator & right_operand) const;
        bool operator >(const iterator & right_operand) const;
        bool operator <=(const iterator & right_operand) const;
        bool operator >=(const iterator & right_operand) const;
        iterator & operator +=(const ptrdiff_t & right_operand);
        iterator operator +(const ptrdiff_t & right_operand) const;
        iterator & operator -=(const ptrdiff_t & right_operand);
        iterator operator -(const ptrdiff_t & right_operand) const;
        ptrdiff_t operator -(const iterator & right_operand) const;
        Element operator *();
    };
    
    iterator begin();
    iterator end();

};


//VECTOR<BOOL> METHODS


Vector<bool>::Vector(size_t size_)
{
    Length = ceil(size_ / sizeof(char));
    Arr = new char[Length];
    
    for (size_t i = 0; i < Length; ++i)
        Arr[i] = 0;
    
    Size = size_;
    Capacity = Length * sizeof(char);
}

Vector<bool>::Vector(const Vector<bool> & other)
{
    Arr = new char[other.Length];
    
    for (size_t i = 0; i < Length; ++i)
        Arr[i] = 0;
    
    Size = other.Size;
    Capacity = other.Capacity;
    Length = other.Length;
    
    for (size_t i = 0; i < Length; ++i)
    {
        for (size_t j = 0; j < sizeof(char); ++j)
        {
            if ((other.Arr[i] & (1 << j)) != 0)
                Arr[i] = Arr[i] | (1 << j);
        }
    }
}

Vector<bool>::~Vector()
{
    delete [] Arr;
}

const Vector<bool> & Vector<bool>::operator =(const Vector<bool> & other)
{
    if (this != &other)
    {
        delete [] Arr;
        
        Arr = new char[other.Length];
        
        Size = other.Size;
        Capacity = other.Capacity;
        Length = other.Length;
        
        for (size_t i = 0; i < Length; ++i)
        {
            for (size_t j = 0; j < sizeof(char); ++j)
            {
                if ((other.Arr[i] & (1 << j)) != 0)
                    Arr[i] = Arr[i] | (1 << j);
            }
        }
    }
    return *this;
}

//VECTOR<BOOL> ELEMENT METHODS

void Vector<bool>::Element::ChangeValue()
{
    if (value != 0)
    {
        array[index / sizeof(char)] = array[index / sizeof(char)] | (1 << (index % sizeof(char)));
    } else {
        array[index / sizeof(char)] = array[index / sizeof(char)] & (255 - (1 << (index % sizeof(char))));
    }
}

Vector<bool>::Element::Element(const Vector<bool> & vector_, size_t index_)
{
    array = vector_.Arr;
    index = index_;
    if ((vector_.Arr[index_ / sizeof(char)] & (1 << (index_ % sizeof(char)))) != 0)
        value = 1;
    else value = 0;
}

const bool & Vector<bool>::Element::operator =(const bool & other)
{
    value = other;
    ChangeValue();
    return (*this).value;
}

const bool & Vector<bool>::Element::operator =(const Element & other)
{
    value = other.value;
    ChangeValue();
    return (*this).value;
}



//END WITH ELEMENT METHODS


Vector<bool>::Element Vector<bool>::operator [](size_t index)
{
    Element element(*this, index);
    return element;
}

const Vector<bool>::Element Vector<bool>::operator [](size_t index) const
{
    Element element(*this, index);
    return element;
}

bool Vector<bool>::operator ==(const Vector<bool> & right_operand) const
{
        int i = 0;
        if (Size == right_operand.Size)
        {
            while ((*this)[i].value == right_operand[i].value && i < Size)
            {
                ++i;
            }
            if (i == Size) return true;
            else return false;
        }
        else return false;
}

bool Vector<bool>::operator <=(const Vector<bool> & right_operand) const
{
    int i = 0;
    while ((*this)[i].value == right_operand[i].value && i < Size && i < right_operand.Size)
    {
        ++i;
    }
    if (i == Size && i == right_operand.Size)
    {
        return true;
    }
    if (i == Size)
    {
        return true;
    } else {
        if (i == right_operand.Size)
        {
            return false;
        } else {
            if ((*this)[i].value <= right_operand[i].value)
            {
                return true;
            } else {
                return false;
            }
        }
    }
}

bool Vector<bool>::operator >=(const Vector<bool> & right_operand) const
{
    int i = 0;
    while ((*this)[i].value == right_operand[i].value && i < Size && i < right_operand.Size)
    {
        ++i;
    }
    if (i == Size && i == right_operand.Size)
    {
        return true;
    }
    if (i == Size)
    {
        return false;
    } else {
        if (i == right_operand.Size)
        {
            return true;
        } else {
            if ((*this)[i].value >= right_operand[i].value)
            {
                return true;
            } else {
                return false;
            }
        }
    }
}

bool Vector<bool>::operator <(const Vector<bool> & right_operand) const
{
    int i = 0;
    while ((*this)[i].value == right_operand[i].value && i < Size && i < right_operand.Size)
    {
        ++i;
    }
    if (i == Size && i == right_operand.Size)
    {
        return false;
    }
    if (i == Size)
    {
        return true;
    } else {
        if (i == right_operand.Size)
        {
            return false;
        } else {
            if ((*this)[i].value < right_operand[i].value)
            {
                return true;
            } else {
                return false;
            }
        }
    }
}

bool Vector<bool>::operator >(const Vector<bool> & right_operand) const
{
    int i = 0;
    while ((*this)[i].value == right_operand[i].value && i < Size && i < right_operand.Size)
    {
        ++i;
    }
    if (i == Size && i == right_operand.Size)
    {
        return false;
    }
    if (i == Size)
    {
        return false;
    } else {
        if (i == right_operand.Size)
        {
            return true;
        } else {
            if ((*this)[i].value > right_operand[i].value)
            {
                return true;
            } else {
                return false;
            }
        }
    }
}

void Vector<bool>::PushBack(bool x)
{
    if (Size == Capacity)
    {
        Capacity *= 2;
        Length = Capacity / sizeof(char);
        char *Copy = new char[Length];
        
        for (size_t i = 0; i < Length; ++i)
            Copy[i] = Arr[i];
        
        delete [] Arr;
        
        Arr = Copy;
    }
    
    if (x != 0)
    {
        Arr[Size / sizeof(char)] = Arr[Size / sizeof(char)] | (1 << (Size % sizeof(char)));
    } else {
        Arr[Size / sizeof(char)] = Arr[Size / sizeof(char)] & (255 - (1 << (Size % sizeof(char))));
    }
    ++Size;
}

size_t Vector<bool>::GetSize() const
{
    return Size;
}

size_t Vector<bool>::GetCapacity() const
{
    return Capacity;
}

//VECTOR<T> ITERATOR METHODS


Vector<bool>::iterator::iterator(Vector<bool> *myvector, ptrdiff_t myvector_index)
{
    vector = myvector;
    index = myvector_index;
}

typename Vector<bool>::iterator & Vector<bool>::iterator::operator ++()
{
    ++index;
    return *this;
}

typename Vector<bool>::iterator & Vector<bool>::iterator::operator --()
{
    --index;
    return *this;
}

bool Vector<bool>::iterator::operator ==(const Vector<bool>::iterator & right_operand) const
{
    if (vector == right_operand.vector && index == right_operand.index) return true;
    else return false;
}

bool Vector<bool>::iterator::operator !=(const Vector<bool>::iterator & right_operand) const
{
    if (vector != right_operand.vector || index != right_operand.index) return true;
    else return false;
}

bool Vector<bool>::iterator::operator <(const Vector<bool>::iterator & right_operand) const
{
    if (index < right_operand.index) return true;
    else return false;
}

bool Vector<bool>::iterator::operator >(const Vector<bool>::iterator & right_operand) const
{
    if (index >right_operand.index) return true;
    else return false;
}

bool Vector<bool>::iterator::operator <=(const Vector<bool>::iterator & right_operand) const
{
    if (index <= right_operand.index)
    return true;
    else return false;
}

bool Vector<bool>::iterator::operator >=(const Vector<bool>::iterator & right_operand) const
{
    if (index >= right_operand.index) return true;
    else return false;
}

typename Vector<bool>::iterator & Vector<bool>::iterator::operator +=(const ptrdiff_t & right_operand)
{
    ptrdiff_t n = right_operand;
    if (n >= 0)
    {
        while (n--) ++index;
    } else {
        while (n++) --index;
    }
    return *this;
}

typename Vector<bool>::iterator Vector<bool>::iterator::operator +(const ptrdiff_t & right_operand) const
{
    Vector<bool>::iterator tmp = *this;
    return tmp += right_operand;
}

typename Vector<bool>::iterator & Vector<bool>::iterator::operator -=(const ptrdiff_t & right_operand)
{
    return *this += -right_operand;
}

typename Vector<bool>::iterator Vector<bool>::iterator::operator -(const ptrdiff_t & right_operand) const
{
    Vector::iterator tmp = *this;
    return tmp -= right_operand;
}

ptrdiff_t Vector<bool>::iterator::operator -(const Vector<bool>::iterator & right_operand) const
{
    return index - right_operand.index;
}

Vector<bool>::Element Vector<bool>::iterator::operator *()
{
    return (*vector)[index];
}

//END WITH VECTOR<T> ITERATOR METHODS

typename Vector<bool>::iterator Vector<bool>::begin()
{
    Vector<bool>::iterator myiterator(this, 0);
    return myiterator;
}

typename Vector<bool>::iterator Vector<bool>::end()
{
    Vector<bool>::iterator myiterator(this, GetSize());
    return myiterator;
}

//END WITH VECTOR<T> METHODS


#endif
