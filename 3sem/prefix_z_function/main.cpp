//
//  main.cpp
//  task_B
//
//  Created by Igashov_Ilya on 15.12.16.
//  Copyright (c) 2016 Igashov_Ilya. All rights reserved.
//

//  Реализован процесс: строка -> z-функция -> префикс-функция -> строка.
//  С помощью этого можно выразить любое из шести преобразований, описанных в задаче.

#include <iostream>
#include <string>
#include <vector>

using namespace std;
//  Функция, строящая z-функцию.
vector<int> ZFunction( string & s );
//  Функция, которая переводит z-функцию в префикс-функцию.
vector<int> ZToPrefix( const vector<int>& z );
//  Функция, которая восстанавливает лексикографически-минимальную строку по префикс-функции.
string ReversePrefixFunction( const vector<int>& prefix );


int main()
{
    string s;
    cin >> s;
    vector<int> z = ZFunction( s );
    vector<int>prefix = ZToPrefix( z );
    string str = ReversePrefixFunction( prefix );
    cout << str;
    return 0;
}

vector<int> ZFunction( string & s )
{
    vector<int> z( s.length(), 0 );
    int l = 0;
    int r = 0;
    for( int i = 1; i < s.length(); ++i ) {
        if( i <= r ) {
            z[i] = min( z[i - l], r - i + 1 );
        }
        while( i + z[i] < s.length() && s[i + z[i]] == s[z[i]] ) {
            ++z[i];
        }
        if( i + z[i] - 1 > r ) {
            l = i; r = i + z[i] - 1;
        }
    }
    
    return z;
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
