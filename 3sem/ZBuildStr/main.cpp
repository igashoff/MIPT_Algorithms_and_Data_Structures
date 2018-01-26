//
//  main.cpp
//  ZBuildStr
//
//  Created by Igashov_Ilya on 25.11.16.
//  Copyright (c) 2016 Igashov_Ilya. All rights reserved.
//

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

//  Функция, которая строит префикс-функцию по известной z-функции pf O(n).
vector<int> ZToPrefix( const vector<int>& z );
//  Функция, которая строит лексикографически-минимальную строку по ее префикс-функции.
string ReversePrefixFunction( const vector<int>& prefix );

int main()
{
    ifstream fin( "input.txt" );
    vector<int> z;
    string s;
    getline( fin, s );
    int temp = 0;
    int prod = 1;
    char ch = ' ';
    for( auto c: s ) {
        ch = c;
        if( c >= 48 && c <= 57 ) {
            temp += prod * (c - 48);
            prod *= 10;
        } else {
            z.push_back( temp );
            temp = 0;
            prod = 1;
        }
    }
    if( ch >= 48 && ch <= 57 ) {
        z.push_back( temp );
    }
    fin.close();
    
    if( z.empty() ) {
        return 0;
    }
    
    vector<int> prefix = ZToPrefix( z );
    string str = ReversePrefixFunction( prefix );
    
    ofstream fout( "output.txt" );
    fout << str;
    fout.close();
    return 0;
}

//  Проходим по z-массиву и на i-позиции перебираем все позиции j префикса длины z[i] от z[i] - 1 до 0.
//  Для каждого j мы устанавливаем значение prefix[i + j].
//  Очевидно, что prefix[i + j] >= j + 1. Заметим, что если для некоторого i и j, лежащего от 0 до z[i] - 1,
//  мы уже установили какое-то значение prefix[i + j] = k, а теперь рассматриваем i' и j', такие что
//  i' > i и i + j == i' + j', то утсановленное значение k  больше значения k' = j' + 1:
//  k = j + 1 > j' + 1 = k'.
//  Следовательно, если для некоторых i и j prefix[i + j] != 0 (а значит и для всех остальных меньших j prefix[i + j] != 0),
//  то этот префикс мы изменять уже не будем.
vector<int> ZToPrefix( const vector<int>& z )
{
    vector<int> prefix( z.size(), 0 );
    for( int i = 1; i < prefix.size(); i++ ) {
        for( int j = z[i] - 1; j >= 0; j-- ) {
            if( prefix[i + j] != 0 ) {
                break;
            }
            else {
                prefix[i + j] = j + 1;
            }
        }
    }
    return prefix;
}

//  Если prefix[i] > 0, то s[i] = s[prefix[i] - 1].
//  Будем поддерживать индекс lastOne последней единицы в префикс-функции, а также массив Apos позиций символов 'a' в строке.
//  Если prefix[i] == 0, то с = следующий по величине символ после символа s[prefix[i - 1]]
//  (чтобы префикс не возрос по сравнению c предыдущим).
//  Далее возможен случай, когда префикс может стать все-таки не равным 0, но меньшим, чем prefix[i - 1], если
//  записать в s[i] символ c + 1. Нужно подобрать наименьший возможный c.
//  Для j от lastOne + 1 до i - 1 будем смотреть, s[j] == 'a'? Если да, то возможно возникновение префикса длины
//  len = i - j + 1. Следовательно, нужно заменить c на максимальный из c и s[len - 1].
//  Первый символ строки полагаем равным 'a'.
string ReversePrefixFunction( const vector<int>& prefix )
{
    string s;
    s += 'a';
    vector<int> Apos( 0 );
    int lastOne = 0;
    for( int i = 1; i < prefix.size(); ++i ) {
        if( prefix[i] == 0 ) {
            char c = s[prefix[i - 1]];
            for( int j = lastOne + 1; j < i; ++j ) {
                if( s[j] == 'a' ) {
                    int len = i - j + 1;
                    c = max( s[len - 1], c );
                }
            }
            s += c + 1;
        }
        else {
            s += s[prefix[i] - 1];
            if( prefix[i] == 1 ) {
                lastOne = i;
            }
            if( s[i] == 'a' ) {
                Apos.push_back( i );
            }
        }
    }
    return s;
}