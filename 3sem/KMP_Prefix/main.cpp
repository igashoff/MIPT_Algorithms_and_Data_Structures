//
//  main.cpp
//  KMP_Prefix
//
//  Created by Igashov_Ilya on 24.11.16.
//  Copyright (c) 2016 Igashov_Ilya. All rights reserved.
//

//  Найдите все вхождения шаблона в строку. Длина шаблона – p, длина строки ­– n. Время O(n + p), доп. память – O(p).
//  Вариант 1. С помощью префикс-функции;
//  Формат входного файла:
//  Шаблон, символ перевода строки, строка.
//  Формат выходного файла:
//  Позиции вхождения шаблона в строке.

#include <iostream>
#include <string>
#include <vector>

//  Функция, реализующая алгоритм Кнута-Морриса-Пратта построения префикс-функции за O(n).
//  В качестве аргумента функция принимает строку, по которой будет строиться префикс-функция.
std::vector<int> PrefixFunction( const std::string& s );
//  Функция, возвращающая массив позиций, с которых начинается шаблон pattern в строке text.
//  Функция принимает на вход шаблон pattern и строку text.
std::vector<int> FindPositions( std::string& pattern, const std::string& text );


int main()
{
    std::string pattern;
    std::string text;
    std::cin >> pattern >> text;
    std::vector<int> positions = FindPositions( pattern, text );
    for( auto x: positions ) {
        std::cout << x << ' ';
    }
    return 0;
}

//  Пусть найдено значение p[i]. Тогда если s[i + 1] == s[p[i]], то p[i + 1] = p[i] + 1.
//  Иначе p[i] <= p[i + 1]. Будем записывать в переменную k гипотетическое значение p[i].
//  Изначально оно равно p[i - 1]. Далее пока k > 0 и пока последующие символы s[k] и s[i] не совпадают,
//  будем уменьшать величину k: делать ее равной p[k - 1].
//  Когда мы вышли из цикла while, надо сравнить s[k] и s[i] (k >= 0). В случае совпадения p[i] = k + 1, иначе p[i] = k.
std::vector<int> PrefixFunction( const std::string& s )
{
    std::vector<int> p( s.length(), 0 );
    for( int i = 1; i < s.length(); ++i ) {
        int k = p[i - 1];
        while( k > 0 && s[i] != s[k] ) {
            k = p[k - 1];
        }
        if( s[i] == s[k] ) {
            ++k;
        }
        p[i] = k;
    }
    return p;
}

//  Посчитаем префикс-функцию для строки pattern$.
//  Дальше как бы берем строку pattern$text и считаем префкс-функцию для оставшихся символов.
//  Поскольку значение префикс-функции для любого символа строки text не может превышать длины
//  шаблона (в силу добавления символа '$'), то нам достаточно хранить только префикс-функию для
//  строки pattern$ и текущее значение префикс-функции. Таким образом дополнительная память составляет O(|pattern|).
//  Если на каком-то символе значение функциии достигло длины шаблона, то значит, что в этом месте заканчивается
//  вхождение шаблона в строку text.
std::vector<int> FindPositions( std::string& pattern, const std::string& text )
{
    pattern += '\0';
    std::vector<int> p = PrefixFunction( pattern );
    
    std::vector<int> positions;
    int currentPrefix = 0;
    int cnt = 0;
    char c;
    do {
        c = text[cnt];
        int k = currentPrefix;
        while( k > 0 && c != pattern[k] ) {
            k = p[k - 1];
        }
        if( c == pattern[k] ) {
            ++k;
        }
        currentPrefix = k;
        if( currentPrefix == pattern.length() - 1 ) {
            positions.push_back( static_cast<int>( cnt -  pattern.length() + 2 ) );
        }
        ++cnt;
        
    } while ( cnt < text.length() );
    return positions;
}

