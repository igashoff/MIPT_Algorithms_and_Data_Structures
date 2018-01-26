//
//  big_int.h
//  jet_brains_1
//
//  Created by Igashov_Ilya on 26.05.16.
//  Copyright (c) 2016 Igashov_Ilya. All rights reserved.
//

#ifndef jet_brains_1_big_int_h
#define jet_brains_1_big_int_h

#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>

typedef unsigned long int int_;

class big_int
{
    int_ *value;
    size_t size;
    static const int_ radix = 10;
    static const size_t rank = 1;
    
    void normalize();
    //big_int multiplication(const big_int & right_operand);
public:
    big_int();
    big_int(int_ other);
    big_int(const std::string & str);
    big_int(const big_int & other);
    
    const big_int & operator =(int_ other);
    const big_int & operator =(const big_int & other);
    
    ~big_int();
    
    bool operator <(const big_int & right_operand) const;
    
    big_int operator +(const big_int & right_operand) const;
    big_int operator +(int_ right_operand) const;
    big_int operator -(const big_int & right_operand) const;
    big_int operator -(int_ right_operand) const;
    big_int operator *(const big_int & right_operand) const;
    big_int operator *(int_ right_operand) const;
    big_int operator /(const big_int & right_operand) const;
    big_int operator %(const big_int & right_operand) const;
    big_int operator /(const int_ & right_operand) const;
    int_ operator %(const int_ & right_operand) const;
    
    friend std::ostream & operator <<(std::ostream & os, const big_int & my_int)
    {
        os << my_int.value[my_int.size - 1];
        for (int i = (int)my_int.size - 2; i >= 0; --i)
        {
            for (int j = 0; j < rank; ++j)
                if (my_int.value[i] / (int)pow(10, j) == 0)
                {
                    for (int k = 0; k < rank - j; ++k)
                        os << 0;
                    break;
                }
            
            if (my_int.value[i]) os << my_int.value[i];
        }
        os << std::endl;
        return os;
    }
};


void big_int::normalize()
{
    if (size > 1)
    {
        for (size_t i = 0; i < size - 1; ++i)
        {
            if (value[i] >= radix)
            {
                value[i + 1] += value[i] / radix;
                value[i] = value[i] % radix;
                continue;
            }
            
            if (value[i] < 0)
            {
                value[i] += radix;
                --value[i + 1];
            }
        }
        
        while (true)
        {
            if (value[size - 1] >= radix)
            {
                big_int tmp(*this);
                delete [] value;
                ++size;
                value = new int_[size];
                for (size_t i = 0; i < size - 2; ++i)
                    value[i] = tmp.value[i];
                value[size - 2] = tmp.value[tmp.size - 1] % radix;
                value[size - 1] = tmp.value[tmp.size - 1] / radix;
            }
            else break;
        }
        
        while (true)
        {
            if (value[size - 1] == 0 && size > 1)
            {
                big_int copy = *this;
                delete value;
                --size;
                value = new int_[size];
                for (size_t i = 0; i < size; ++i)
                    value[i] = copy.value[i];
            }
            else break;
        }
    }
}

/*
 big_int big_int::multiplication(const big_int & right_operand)
 {
 //
 std::vector<big_int> addends(right_operand.size);
 for (size_t i = 0; i < right_operand.size; ++i)
 {
 addends[i].size = i + size;
 addends[i].value = new int_[addends[i].size];
 for (size_t k = 0; k < addends[i].size; ++k)
 {
 addends[i].value[k] = 0;
 }
 
 int_ multiplier = right_operand.value[i];
 
 big_int add;
 add.size = i + size + 1;
 add.value = new int_[add.size];
 for (size_t k = 0; k < add.size; ++k)
 {
 add.value[k] = 0;
 }
 
 for (size_t j = 0; j < size; ++j)
 {
 addends[i].value[i + j] = (value[j] * multiplier) % radix;
 add.value[i + j + 1] = ((value[j] * multiplier) / radix);
 }
 addends[i] = addends[i] + add;
 }
 
 big_int result(addends[0]);
 for (size_t i = 1; i < addends.size(); ++i)
 result = result + addends[i];
 //
 
 big_int result;
 result.size = size + right_operand.size;
 result.value = new int_[result.size];
 
 for (int i = 0; i < (int)result.size; ++i)
 result.value[i] = 0;
 
 for (size_t i = 0; i < size; ++i)
 for (size_t j = 0; j < right_operand.size; ++j)
 result.value[i + j] += value[i] * right_operand.value[j];
 
 result.normalize();
 return result;
 }
 */

big_int::big_int()
{
}

big_int::big_int(int_ other)
{
    int length;
    for (length = 1; other / (int)pow(10, length); ++length);
    
    size = length / rank + 1;
    
    value = new int_[size];
    for (size_t i = 0; i < size; ++i)
        value[i] = (other % (int)pow(10, i * rank + rank)) / (int)pow(10, i * rank);
}

big_int::big_int(const std::string & str)
{
    size = str.length() / rank + 1;
    value = new int_[size];
    for (size_t i = 0; i < size; ++i)
        value[i] = 0;
    for (size_t i = 0; i < str.length(); ++i)
    {
        value[i / rank] += (str[str.length() - i - 1] - '0') * (int)pow(10, i % rank);
    }
    
    (*this).normalize();
}

big_int::big_int(const big_int & other)
{
    size = other.size;
    value = new int_[size];
    for (size_t i = 0; i < size; ++i)
        value[i] = other.value[i];
}

const big_int & big_int::operator =(int_ other)
{
    big_int other_(other);
    (*this) = other_;
    return *this;
}

const big_int & big_int::operator =(const big_int & other)
{
    size = other.size;
    delete [] value;
    value = new int_[size];
    for (size_t i = 0; i < size; ++i)
        value[i] = other.value[i];
    return *this;
}

big_int::~big_int()
{
    delete [] value;
}


bool big_int::operator <(const big_int & right_operand) const
{
    if (size > right_operand.size)
        return false;
    if (size < right_operand.size)
        return true;
    for (int i = (int)size - 1; i >= 0; --i)
    {
        if (value[i] > right_operand.value[i])
            return false;
        if (value[i] < right_operand.value[i])
            return true;
    }
    return false;
}



big_int big_int::operator +(const big_int & right_operand) const
{
    big_int result(*this);
    
    if (size >= right_operand.size)
    {
        for (size_t i = 0; i < result.size; ++i)
            result.value[i] += (i < right_operand.size) ? right_operand.value[i] : 0;
    }
    else
    {
        result = right_operand;
        for (size_t i = 0; i < result.size; ++i)
            result.value[i] += (i < size) ? value[i] : 0;
    }
    
    result.normalize();
    return result;
}

big_int big_int::operator +(int_ right_operand) const
{
    big_int tmp(right_operand);
    return (*this) + tmp;
}

big_int big_int::operator -(const big_int & right_operand) const
{
    big_int result(*this);
    for (size_t i = 0; i < result.size; ++i)
        result.value[i] -= (i < right_operand.size) ? right_operand.value[i] : 0;
    
    result.normalize();
    return result;
}

big_int big_int::operator -(int_ right_operand) const
{
    big_int tmp(right_operand);
    return (*this) - tmp;
}


big_int big_int::operator *(const big_int & right_operand) const
{
    big_int result;
    result.size = size + right_operand.size;
    result.value = new int_[result.size];
    
    for (int i = 0; i < (int)result.size; ++i)
        result.value[i] = 0;
    
    for (size_t i = 0; i < size; ++i)
        for (size_t j = 0; j < right_operand.size; ++j)
            result.value[i + j] += value[i] * right_operand.value[j];
    
    result.normalize();
    return result;
}

big_int big_int::operator *(int_ right_operand) const
{
    big_int tmp(right_operand);
    return (*this) * tmp;
}

big_int big_int::operator /(const int_ & right_operand) const
{
    big_int tmp_result;
    tmp_result.size = size;
    tmp_result.value = new int_[tmp_result.size];
    
    int_ carry = 0;
    int_ current;
    size_t j = 0;
    for (int i = (int)size - 1; i >= 0; --i)
    {
        current = value[i] + carry * radix;
        tmp_result.value[j] = current / right_operand;
        carry = current % right_operand;
        ++j;
    }
    
    big_int result;
    result.size = j;
    result.value = new int_[result.size];
    
    for (size_t i = 0; i < result.size; ++i)
        result.value[i] = tmp_result.value[j - i - 1];
    
    result.normalize();
    return result;
}

int_ big_int::operator %(const int_ & right_operand) const
{
    int_ carry = 0;
    int_ current;
    for (int i = (int)size - 1; i >= 0; --i)
    {
        current = value[i] + carry * radix;
        carry = current % right_operand;
    }
    
    return carry;
}

big_int big_int::operator /(const big_int & right_operand) const
{
    if((*this) < right_operand)
    {
        big_int result(0);
        return result;
    }
    
    big_int result;
    result.size = size;
    
    bool check = 0;
    
    for(int i = 1; i <= (int)right_operand.size; ++i)
    {
        if (value[size - i] > right_operand.value[right_operand.size - i])
        {
            result.size = size - right_operand.size + 1;
            check = 1;
            break;
        }
        
        else
            
            if (value[size - i] < right_operand.value[right_operand.size - i])
            {
                result.size = size - right_operand.size;
                check = 1;
                break;
            }
    }
    
    if (!check)
    {
        result.size = size - right_operand.size + 1;
    }
    
    result.value = new int_[result.size];
    for (int i = 0; i < result.size; ++i)
        result.value[i] = 0;
    
    for (int i = (int)result.size - 1; i >= 0; --i)
    {
        int_ bottom = 0;
        int_ top = radix - 1;
        int_ middle = (top + bottom) / 2;
        
        while (bottom < top - 1)
        {
            middle = (top + bottom) / 2;
            result.value[i] = middle;
            
            if ((*this) < (result * right_operand))
                top = middle;
            else bottom = middle;
        }
        
        result.value[i] = bottom + 1;
        
        if ((*this) < (result * right_operand))
            result.value[i] = bottom;
    }
    
    result.normalize();
    return result;
}

big_int big_int::operator %(const big_int & right_operand) const
{
    return ((*this) - right_operand * ((*this) / right_operand));
}

#endif
