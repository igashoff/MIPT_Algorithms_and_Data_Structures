
//
//  header.h
//  matrix
//
//  Created by Igashov_Ilya on 16.04.16.
//  Copyright (c) 2016 Igashov_Ilya. All rights reserved.
//

#ifndef matrix_header_h
#define matrix_header_h

#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <initializer_list>
#include <exception>

template <typename T>
class matrix
{
    size_t rows;
    size_t columns;
    std::vector<std::vector<T>> mat;
    
public:
    
    matrix();
    matrix(std::initializer_list<std::initializer_list<T>> l);
    matrix(size_t columns_, size_t rows_);
    matrix(size_t columns_, size_t rows_, const T & value);
    matrix(size_t columns_, size_t rows_, const std::vector<T> & mat_);
    
    template <typename ptr_type, typename ret_type>
    class line
    {
        ptr_type my_mat;
        size_t row;
        
    public:
        
        line(ptr_type my_mat_, size_t row_): my_mat(my_mat_), row(row_) {};
        ret_type operator [](size_t index)
        {
            return my_mat->mat[row][index];
        }
    };

    template<>
    class line<const matrix<T> &, const T &>
    {
        const matrix<T> & my_mat;
        size_t row;
        
    public:
        line(const matrix<T> & my_mat_, size_t row_): my_mat(my_mat_), row(row_) {};
        const T & operator [](size_t index) const
        {
            return my_mat->mat[row][index];
        }

    };
    
    line<matrix<T> &, T &> operator [](size_t index);
    const line<const matrix<T> &, const T &> operator [](size_t index) const;
    
    matrix operator +(const matrix & right_operand) const;
    matrix operator -(const matrix & right_operand) const;
    matrix operator *(const matrix & right_operand) const;
    matrix operator *(const T & right_operand) const;
    matrix operator /(const T & right_operand) const;
    
    matrix transponate() const;
    T trunc() const;
    T determinate() const;
    matrix inverse() const;
    
    std::pair<size_t, size_t> size() const;
    size_t height() const;
    size_t width() const;
    
    friend std::ostream & operator <<(std::ostream & os, const matrix & matrix_)
    {
        for (size_t i = 0; i < matrix_.rows; i++)
        {
            os << '|';
            for (size_t j = 0; j < matrix_.columns; ++j)
                os << matrix_.mat[i][j] << ' ';
            os << '|' << std::endl;
        }
        return os;
    }
    
    size_t & foo()
    {
        return rows;
    }

};


/*
 template <typename ptr_type, typename ret_type>
 class element
 {
 ptr_type my_mat;
 size_t row;
 
 private:
 element(ptr_type my_mat_, size_t row_): my_mat(&my_mat_), row(row_) {};
 ret_type operator [](size_t index)
 {
 return my_mat -> mat[row][index];
 };
 
 };
 */


//MATRIX<T> METHODS

template <typename T>
matrix<T>::matrix() {}

template <typename T>
matrix<T>::matrix(std::initializer_list<std::initializer_list<T>> l)
{
    mat.resize(l.size());
    for (auto & i: mat)
        i.resize(l.begin()->size());
    
    size_t i = 0;
    size_t j = 0;
    for (auto & line: l)
    {
        j = 0;
        for (auto & element: line)
        {
            mat[i][j] = element;
            ++j;
        }
        ++i;
    }
    
    rows = mat.size();
    columns = mat[0].size();
}

template <typename T>
matrix<T>::matrix(size_t columns_, size_t rows_): rows(rows_), columns(columns_)
{
    mat.resize(rows);
    for (size_t i = 0; i < mat.size(); ++i)
        mat[i].resize(columns);
}

template <typename T>
matrix<T>::matrix(size_t columns_, size_t rows_, const T & value): rows(rows_), columns(columns_)
{
    mat.resize(rows);
    for (size_t i = 0; i < mat.size(); ++i)
        mat[i].resize(columns, value);
}

template <typename T>
matrix<T>::matrix(size_t columns_, size_t rows_, const std::vector<T> & mat_): rows(rows_), columns(columns_)
{
    mat.resize(rows);
    for (size_t i = 0; i < mat.size(); ++i)
    {
        mat[i].resize(columns);
        for (size_t j = 0; j < mat[i].size(); ++j)
            mat[i][j] = mat_[i * columns + j];
    }
}

//ELEMENT METHODS

/*
template <typename T>
matrix<T>::element::element(matrix<T> & my_mat_, size_t row_): allocated(false), my_mat(&my_mat_), row(row_) {};

template <typename T>
matrix<T>::element::element(const matrix<T> & my_mat_, size_t row_): allocated(true), row(row_) // в шаблоне!!
{
    my_mat = new matrix<T>();
    *my_mat = my_mat_;
};

template <typename T>
matrix<T>::element::~element()
{
    if (allocated)
        delete my_mat;
}

template <typename T>
T & matrix<T>::element::operator [](size_t index)
{
    return my_mat -> mat[row][index];
}

template <typename T>
const T & matrix<T>::element::operator [](size_t index) const
{
    return my_mat -> mat[row][index];
}
*/
//END WITH ELEMENT METHODS

/*
template <typename T> template <typename ptr_type, typename ret_type>
typename line<ptr_type, ret_type>::line<matrix<T> &, T &> matrix<T>::operator [](size_t index)
{
    line tmp((*this), index);
    return tmp;
}


template <typename T>
const typename matrix<T>::element matrix<T>::operator [](size_t index) const
{
    element tmp((*this), index);
    return tmp;
}
*/

template <typename T>
matrix<T>::line<matrix<T> &, T &> matrix<T>::operator [](size_t index)
{
    line<matrix<T> &, T &> tmp((*this), index);
    return tmp;
}

template <typename T>
const matrix<T>::line<const matrix<T> &, const T &> matrix<T>::operator [](size_t index) const
{
    line<const matrix<T> &, const T &> tmp((*this), index);
    return tmp;
}

template <typename T>
matrix<T> matrix<T>::operator +(const matrix & right_operand) const
{
    matrix<T> result(columns, rows);
    for (size_t i = 0; i < rows; ++i)
        for (size_t j = 0; j < columns; ++j)
            result[i][j] = (*this)[i][j] + right_operand[i][j];
    return result;
}

template <typename T>
matrix<T> matrix<T>::operator -(const matrix & right_operand) const
{
    matrix<T> result(columns, rows);
    for (size_t i = 0; i < rows; ++i)
        for (size_t j = 0; j < columns; ++j)
            result[i][j] = (*this)[i][j] - right_operand[i][j];
    return result;
}

template <typename T>
matrix<T> matrix<T>::operator *(const matrix & right_operand) const
{
    matrix<T> result(rows, right_operand.columns);
    for (size_t i = 0; i < result.rows; ++i)
        for (size_t j = 0; j < result.columns; ++j)
            for (size_t k = 0; k < columns; ++k)
                result[i][j] += (*this)[i][k] * right_operand[k][j];
    return result;
}

template <typename T>
matrix<T> matrix<T>::operator *(const T & right_operand) const
{
    matrix<T> result(rows, columns);
    for (size_t i = 0; i < rows; ++i)
        for (size_t j = 0; j < columns; ++j)
            result[i][j] = (*this)[i][j] * right_operand;
    return result;
}

template <typename T>
matrix<T> matrix<T>::operator /(const T & right_operand) const
{
    matrix<T> result(rows, columns);
    for (size_t i = 0; i < rows; ++i)
        for (size_t j = 0; j < columns; ++j)
            result[i][j] = (*this)[i][j] / right_operand;
    return result;
}


template <typename T>
matrix<T> matrix<T>::transponate() const
{
    matrix<T> result(rows, columns);
    for (size_t i = 0; i < rows; ++i)
        for (size_t j = 0; j < columns; ++j)
            result[j][i] = (*this)[i][j];
    return result;
}

template <typename T>
T matrix<T>::trunc() const
{
    T trunc = (*this)[0][0];
    for (int i = 1; i < rows; ++i)
        trunc += (*this)[i][i];
    return trunc;
}

template <typename T>
T matrix<T>::determinate() const
{
    if (rows == 1)
        return (*this)[0][0];
    
    matrix<T> minor(*this);
    for (size_t i = 0; i < rows; ++i)
        minor.mat[i].erase(minor.mat[i].begin());
    minor.mat.erase(minor.mat.begin());
    --minor.rows;
    --minor.columns;
    
    T determinate = (*this)[0][0] * minor.determinate();
    
    for (size_t j = 1; j < columns; ++j)
    {
        matrix<T> minor(*this);
        for (size_t i = 0; i < rows; ++i)
            minor.mat[i].erase(minor.mat[i].begin() + j);
        minor.mat.erase(minor.mat.begin());
        --minor.rows;
        --minor.columns;
        if (j % 2)
            determinate += (-1) * (*this)[0][j] * minor.determinate();
        else
            determinate += (*this)[0][j] * minor.determinate();
    }
    
    return determinate;
}

template <typename T>
std::pair<size_t, size_t> matrix<T>::size() const
{
    std::pair<size_t, size_t> size_;
    size_.first = columns;
    size_.second = rows;
    return size_;
}

template <typename T>
size_t matrix<T>::height() const
{
    return rows;
}

template <typename T>
size_t matrix<T>::width() const
{
    return columns;
}


template <typename T>
matrix<T> matrix<T>::inverse() const
{
    matrix<T> result(columns, rows);
    
    for (size_t i = 0; i < rows; ++i)
        for (size_t j = 0; j < columns; ++j)
        {
            matrix<T> minor(*this);
            
            for (size_t k = 0; k < rows; ++k)
                minor.mat[k].erase(minor.mat[k].begin() + j);
            
            minor.mat.erase(minor.mat.begin() + i);
            --minor.rows;
            --minor.columns;
            
            result[i][j] = minor.determinate();
            if ((i + j) % 2)
                result[i][j] *= (-1);
        }
    
    result = result.transponate();
    result = result / (*this).determinate();
    return result;
}

#endif
