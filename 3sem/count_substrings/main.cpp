//
//  main.cpp
//  CountSubstrings
//
//  Created by Igashov_Ilya on 25.11.16.
//  Copyright (c) 2016 Igashov_Ilya. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

const int alphabet = 27;

//  Функция, создающая суффиксный массив строки str и заполняющая массив обратного преобразования pos.
//  На вход подается строка str и ссылка на массив обратного преобразования pos, который заполнится в этой функции.
vector<int> MakeSA( string& str, vector<int>& pos );
vector<int> CountLCP( const string& str, const vector<int>& SA, const vector<int>& pos );

int main()
{
    string str;
    cin >> str;
    str += '`';
    
    vector<int> pos( str.length() );
    vector<int> suffixArray = MakeSA( str, pos );
    vector<int> lcp = CountLCP( str, suffixArray, pos );
    
    int cnt = 0;
    for( int i = 0; i < str.length(); ++i ) {
        cnt += str.length() - suffixArray[i] - 1 - lcp[i];
    }
    
    cout << cnt - 1;
    return 0;
}

//  Будем сортировать подстроки строки str различных длин (1, 2, 4, ..., log[n]).
//  На первом шаге остортируем символы строки подсчетом:
//  В permutations запишем перестановку символов в порядке возрастания, а в classes - классы эквивалентности символов
//  (classes[i] - класс эквивалентности i-го символа строки str. Например, "`" имеет класс 0, след. по возрастанию
//  символ - клас 1, и тд).
//  Дальше в цикле по len от 2 до log[n]: пусть подстроки длины len/2 остортиррованы.
//  В pn записываем позиции начала подстрок длины len, упорядоченных по их вторым частям;
//  сортируем подсчетом эти подстроки длины len по классам эквивалентности их первых частей;
//  обновляем классы эквивалентностей для подстрок длины len.
//  После каждой итерации в permutations записаны позиции отсортированных подстрок длины len.
vector<int> MakeSA( string& str, vector<int>& pos )
{
    vector<int> permutation( str.length(), 0 );
    vector<int> classes( str.length(), 0 );
    vector<int> cnt( alphabet, 0 );
    
    for( int i = 0; i < str.length(); ++i ) {
        ++cnt[str[i] - 96];
    }
    for( int i = 1; i < alphabet; ++i ) {
        cnt[i] += cnt[i - 1];
    }
    for( int i = 0; i < str.length(); ++i ) {
        permutation[--cnt[str[i] - 96]] = i;
    }
    
    int cls = 1;
    classes[permutation[0]] = 0;
    for( int i = 1; i < permutation.size(); ++i ) {
        if( str[permutation[i - 1]] != str[permutation[i]] ) {
            ++cls;
        }
        classes[permutation[i]] = cls - 1;
    }
    
    vector<int> pn( str.length(), 0 );
    vector<int> cn( str.length(), 0 );
    for( int k = 0; (1<<k) < str.length(); ++k ) {
        for( int i = 0; i < permutation.size(); ++i ) {
            pn[i] = permutation[i] - (1<<k);
            if( pn[i] < 0 ) {
                pn[i] += permutation.size();
            }
        }
        vector<int> counter( cls, 0 );
        for( int i = 0; i < pn.size(); ++i ) {
            ++counter[classes[pn[i]]];
        }
        for( int i = 1; i < counter.size(); ++i ) {
            counter[i] += counter[i - 1];
        }
        for( int i = static_cast<int>( pn.size() - 1 ); i >= 0; --i ) {
            permutation[--counter[classes[pn[i]]]] = pn[i];
        }
        
        cls = 1;
        cn[permutation[0]] = 0;
        for( int i = 1; i < permutation.size(); ++i ) {
            int temp1 = (permutation[i] + (1<<k)) % permutation.size();
            int temp2 = (permutation[i - 1] + (1<<k)) % permutation.size();
            if( classes[permutation[i]] != classes[permutation[i-1]] || classes[temp1] != classes[temp2] ) {
                ++cls;
            }
            cn[permutation[i]] = cls - 1;
        }
        
        for( int i = 0; i < classes.size(); ++i ) {
            classes[i] = cn[i];
        }
    }
    
    vector<int> suffixArray( permutation.size() );
    for( int i = 0; i < permutation.size(); ++i ) {
        suffixArray[i] = permutation[i];
        pos[suffixArray[i]] = i;
    }
    
    return suffixArray;
}

vector<int> CountLCP( const string& str, const vector<int>& SA, const vector<int>& pos )
{
    vector<int> lcp( str.length() );
    int k = 0;
    for( int i = 0; i < str.length() - 1; ++i ) {
        if( k > 0 ) {
            --k;
        }
        if( pos[i] == str.length() - 1 ) {
            lcp[str.length() - 1] = -1;
            k = 0;
        }
        else {
            int j = SA[pos[i] + 1];
            while( max(i + k, j + k) < str.length() && str[i + k] == str[j + k] ) {
                ++k;
            }
            lcp[pos[i]] = k;
        }
    }
    return lcp;
}