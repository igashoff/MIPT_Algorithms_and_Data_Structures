//
//  main.cpp
//  BigInt
//
//  Created by Igashov_Ilya on 21.03.16.
//  Copyright (c) 2016 Igashov_Ilya. All rights reserved.
//

#include <iostream>
#include <cmath>
#include <vector>

typedef unsigned long int int_;

class BigInt
{
    int_ *digits;
    size_t size;
    static const int_ radix = 10000000;
    static const int rank = 7;
    void delete_nulls();
public:
    BigInt();
    BigInt(const std::string & str);
    BigInt(int_ other);
    BigInt(const BigInt & other);
    ~BigInt();
    const BigInt & operator =(const BigInt & other);
    const BigInt & operator =(int_ other);
    
    BigInt & operator ++();
    BigInt & operator --();
    
    BigInt operator +(const BigInt & right_operand) const;
    BigInt operator -(const BigInt & right_operand) const;
    BigInt & operator +=(const BigInt & right_operand);
    BigInt & operator -=(const BigInt & right_operand);
    
    BigInt operator +(int_ right_operand) const;
    BigInt operator -(int_ right_operand) const;
    BigInt & operator +=(int_ right_operand);
    BigInt & operator -=(int_ right_operand);
    
    BigInt operator *(const BigInt & right_operand);
    BigInt & operator *=(const BigInt & right_operand);
    BigInt & operator /=(const BigInt & right_operand);
    
    
    friend std::ostream & operator <<(std::ostream & os, const BigInt & my_int)
    {
        os << my_int.digits[my_int.size - 1];
        for (int i = (int)my_int.size - 2; i >= 0; --i)
        {
            for (int j = 0; j < rank; ++j)
                if (my_int.digits[i] / (int)pow(10, j) == 0)
                {
                    for (int k = 0; k < rank - j; ++k)
                        os << 0;
                    break;
                }
            
            if (my_int.digits[i]) os << my_int.digits[i];
        }
        os << std::endl;
        return os;
    }
};

void BigInt::delete_nulls()
{
    size_t i;
    for (i = size - 1; digits[i] == 0; --i);
    BigInt copy(*this);
    size = i + 1;
    delete [] digits;
    digits = new int_[size];
    for (size_t j = 0; j < size; ++j) digits[j] = copy.digits[j];
}

BigInt::BigInt() {}

BigInt::BigInt(int_ other)
{
    int length;
    for (length = 1; other / (int)pow(10, length); ++length);
    size = length / rank + 1;
    digits = new int_[size];
    for (int i = 0; i < size; ++i)
    {
        digits[i] = (other % (int)pow(10, i * rank + rank)) / (int)pow(10, i * rank);
    }
}

BigInt::BigInt(const BigInt & other)
{
    size = other.size;
    digits = new int_[size];
    for (size_t i = 0; i < size; ++i)
        digits[i] = other.digits[i];
}

BigInt::~BigInt()
{
    delete [] digits;
}

const BigInt & BigInt::operator =(const BigInt & other)
{
    size = other.size;
    delete [] digits;
    digits = new int_[size];
    for (size_t i = 0; i < size; ++i)
        digits[i] = other.digits[i];
    return *this;
}

const BigInt & BigInt::operator =(int_ other)
{
    BigInt other_(other);
    (*this) = other_;
    return *this;
}

BigInt & BigInt::operator++()
{
    size_t i;
    for (i = 0; i < size; ++i)
    {
        if (++digits[i] / (int)pow(10, rank) == 0) break;
        digits[i] = 0;
    }
    if (i == size)
    {
        ++size;
        delete [] digits;
        digits = new int_[size];
        for (size_t i = 0; i < size - 1; ++i)
            digits[i] = 0;
        digits[size - 1] = 1;
    }
    return *this;
}

BigInt & BigInt::operator --()
{
    for (size_t i = 0; i < size; ++i)
    {
        if (digits[i]-- != 0) break;
        digits[i] = radix - 1;
    }
    return *this;
}

BigInt BigInt::operator +(const BigInt & right_operand) const
{
    BigInt tmp;
    BigInt result;
    
    if (right_operand.size >= size)
    {
        tmp.size = right_operand.size;                                      //tmp instead of this, e.g. tmp + right.operand
        tmp.digits = new int_[tmp.size];
        for (size_t i = 0; i < tmp.size; ++i)
        {
            if (i < size) tmp.digits[i] = digits[i];
            else tmp.digits[i] = 0;
        }
        
        result.size = tmp.size + 1;
        result.digits = new int_[result.size];
        for (size_t i = 0; i < result.size; ++i) result.digits[i] = 0;
        
        int_ add = 0;
        for (size_t i = 0; i < tmp.size; ++i)
        {
            BigInt added;
            added.size = tmp.size - i;
            added.digits = new int_[added.size];
            for (size_t j = 0; j < added.size; ++j)
            {
                added.digits[j] = tmp.digits[i + j];
            }
            for (int j = 0; j < add; ++j) ++added;
            for (size_t j = 0; j < added.size; ++j) tmp.digits[i + j] = added.digits[j];
            
            result.digits[i] = (tmp.digits[i] + right_operand.digits[i]) % (int)pow(10, rank);
            add = (tmp.digits[i] + right_operand.digits[i]) / (int)pow(10, rank);
        }
    }
    
    else
    {
        tmp.size = size;                                                      //tmp instead of right_operand, e.g. tmp + this
        tmp.digits = new int_[tmp.size];
        for (size_t i = 0; i < tmp.size; ++i)
        {
            if (i < right_operand.size) tmp.digits[i] = right_operand.digits[i];
            else tmp.digits[i] = 0;
        }
        
        result.size = tmp.size + 1;
        result.digits = new int_[result.size];
        for (size_t i = 0; i < result.size; ++i) result.digits[i] = 0;
        
        int_ add = 0;
        for (size_t i = 0; i < tmp.size; ++i)
        {
            BigInt added;
            added.size = tmp.size - i;
            added.digits = new int_[added.size];
            
            for (size_t j = 0; j < added.size; ++j)
            {
                added.digits[j] = tmp.digits[i + j];
            }
            for (int j = 0; j < add; ++j) ++added;
            for (size_t j = 0; j < added.size; ++j) tmp.digits[i + j] = added.digits[j];
            
            result.digits[i] = (tmp.digits[i] + digits[i]) % (int)pow(10, rank);
            add = (tmp.digits[i] + digits[i]) / (int)pow(10, rank);
        }
        
    }
    return result;
}


BigInt BigInt::operator -(const BigInt & right_operand) const
{
    BigInt tmp(*this);
    
    for (size_t i = 0; i < right_operand.size; ++i)
    {
        if (tmp.digits[i] >= right_operand.digits[i])
        {
            tmp.digits[i] = tmp.digits[i] - right_operand.digits[i];
            continue;
        }
        
        BigInt minused;
        minused.size = size - i - 1;
        minused.digits = new int_[minused.size];
        
        for (size_t j = 0; j < minused.size; ++j)
        {
            minused.digits[j] = tmp.digits[i + 1 + j];
        }
        
        --minused;
        
        for (size_t j = 0; j < minused.size; ++j) tmp.digits[i + 1 + j] = minused.digits[j];
        
        tmp.digits[i] = tmp.digits[i] + radix - right_operand.digits[i];
    }
    return tmp;
}

BigInt & BigInt::operator +=(const BigInt & right_operand)
{
    (*this) = (*this) + right_operand;
    return *this;
}

BigInt & BigInt::operator -=(const BigInt & right_operand)
{
    (*this) = (*this) - right_operand;
    return *this;
}

/*BigInt & BigInt::operator +=(const BigInt & right_operand)
 {
 for (size_t i = 0; i < right_operand.size; ++i)
 {
 for (size_t j = 0; j < right_operand.digits[i] * (int)pow(10, rank * i); ++j)
 ++(*this);
 }
 return *this;
 }*/

BigInt BigInt::operator +(int_ right_operand) const
{
    BigInt tmp(right_operand);
    return (*this) + tmp;
}

BigInt BigInt::operator -(int_ right_operand) const
{
    BigInt tmp(right_operand);
    return (*this) - tmp;
}

BigInt & BigInt::operator +=(int_ right_operand)
{
    BigInt tmp(right_operand);
    return (*this)+=tmp;
}

BigInt & BigInt::operator -=(int_ right_operand)
{
    BigInt tmp(right_operand);
    return (*this)-=tmp;
}

BigInt BigInt::operator *(const BigInt & right_operand)
{
    std::vector<BigInt> addends(right_operand.size);
    
    for (size_t i = 0; i < right_operand.size; ++i)
    {
        addends[i].size = i + size;
        addends[i].digits = new int_[addends[i].size];
        for (size_t k = 0; k < addends[i].size; ++k)
        {
            addends[i].digits[k] = 0;
        }
        
        int_ multiplier = right_operand.digits[i];
        
        BigInt add;
        add.size = i + size + 1;
        add.digits = new int_[add.size];
        for (size_t k = 0; k < add.size; ++k)
        {
            add.digits[k] = 0;
        }
        
        for (size_t j = 0; j < size; ++j)
        {
            addends[i].digits[i + j] = (digits[j] * multiplier) % radix;
            add.digits[i + j + 1] = ((digits[j] * multiplier) / radix);
        }
        addends[i] += add;
    }
    
    BigInt result = addends[0];
    for (size_t i = 1; i < addends.size(); ++i)
        result += addends[i];
    
    return result;
}



int main()
{
    
    return 0;
}


