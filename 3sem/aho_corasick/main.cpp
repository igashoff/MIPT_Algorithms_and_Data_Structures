//
//  main.cpp
//  AhoCorasick
//
//  Created by Igashov_Ilya on 02.12.16.
//  Copyright (c) 2016 Igashov_Ilya. All rights reserved.
//

//  Шаблон поиска задан строкой длины m, в которой кроме обычных символов могут встречаться символы “?”.
//  Найти позиции всех вхождений шаблона в тексте длины n. Каждое вхождение шаблона предполагает, что все обычные
//  символы совпадают с соответствующими из текста, а вместо символа “?” в тексте встречается произвольный символ.
//  Время работы - O(n + m + Z), где Z - общее число вхождений подстрок шаблона “между вопросиками” в исходном тексте.
//  (Ахо-Корасик)

//  m ≤ 5000, n ≤ 2000000. Время: 10с, память 32Mb.

//  Формат входного файла:
//  Шаблон, символ перевода строки, строка.
//  Формат выходного файла:
//  Позиции вхождения шаблона в строке.

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

//  Структура, реализующая узел в боре.
struct Node
{
    vector<int> children;   // Номера узлов, в которые ведут ребра, соотв. символам от a до z (0..25).
    vector<int> go;         // Номера узлов, куда ведет функция перехода по соотв. символу.
    int parent;             // Номер родителя данного узла.
    int suffixLink;         // Суффиксная ссылка.
    int terminateLink;      // Сжатая суффиксная ссылка (номер первой терминальной вершины на пути суффиксных ссылок).
    int charToParent;       // Символ ребра, которое ведет из родителя в данную вершиу.
    bool leaf;              // Индикатор терминальной вершины.
    vector<int> pos;        // Если у нас подшаблоны повторяются, то мы делаем вектор, где каждому подшаблону данной
                            // вершины соответствует число, равное
                            // "номер первого символа данного подшаблона в шаблоне с маской" + "длина подшаблона" - 1.
    
    // При создании вершины все ссылки, функции перехода, а также номера вершин, в которые ведут ребра-символы, ставим -1.
    Node(): parent( -1 ), suffixLink( -1 ), terminateLink( -1 ), charToParent( -1 ), leaf( false )
    {
        children.resize( 26, -1 );
        go.resize( 26, -1 );
        pos.resize( 0 );

    }
    
    Node( int par, int chToPar ): parent( par ), suffixLink( -1 ), terminateLink( -1 ), charToParent( chToPar ), leaf( false )
    {
        children.resize( 26, -1 );
        go.resize( 26, -1 );
        pos.resize( 0 );

    }
    
};

//  Функция, создающая бор. Принимает на вход вектор подшаблонов, по которым и будет строиться бор, а также
//  вектор номеров первых символов каждого подшаблона в шаблоне с маской (нужно для заполнения pos).
vector<Node> MakeTrie( const vector<string>& splitPattern, const vector<int>& startPositions );
//  Функция, возвращающая суффиксную ссылку вершины node в боре trie.
int GetSuffixLink( vector<Node>& trie, int node );
//  Функция, возвращающая функцию перехода вершины node в боре trie по символу _char.
int GetLink( vector<Node>& trie, int node, int _char );
//  Функция, возвращающая сжатую суффиксную ссылку вершины node в боре trie.
int GetTerminateLink( vector<Node>& trie, int node );
//  Функция, которая ищет все вхождения шабона с маской pattern в строку text.
vector<int> FindPositions( vector<Node>& trie, const string& text, const string& pattern, const vector<string>& splitPattern );

int main()
{
    ifstream fin( "input.txt" );
    string pattern;
    string text;
    fin >> pattern >> text;
    // Если длина шаблона больше длины строки, то автоматически завершаем программу, т.к. нет корректны вхождений
    // шаблона в строку.
    if( pattern.size() > text.size() ) {
        return 0;
    }
    
    // Разбиваем шаблон на строки, в которых нет символов '?'.
    vector<string> splitPattern( 0 );               // Вектор подшаблонов.
    vector<int> startPositions( 0 );                // Вектор позиций первых символов каждого подшаблона в шаблоне.
    string s;                                       // Буфер для построения подшаблона.
    int i = 0;
    for( i = 0; i < pattern.length(); ++i ) {
        if( pattern[i] != '?' ) {
            s += pattern[i];
        }
        else {
            if( s.length() > 0 ) {
                splitPattern.push_back( s );
                startPositions.push_back( static_cast<int>( i - s.length() ) );
                s.clear();
            }
        }
    }
    // В случае, если строка закончилась, а последний символ не был равен "?",
    // нужно не забыть про последний подшаблон s.
    if( s.length() > 0 ) {
        splitPattern.push_back( s );
        startPositions.push_back( static_cast<int>( i - s.length() ) );
    }
    
    // Создаем бор.
    vector<Node> trie = MakeTrie( splitPattern, startPositions );
    
    // Ищем все вхождения шаблона в строку.
    vector<int> positions = FindPositions( trie, text, pattern, splitPattern );
    ofstream fout( "output.txt" );
    for( auto x: positions ) {
        fout << x << ' ';
    }
    
    return 0;
}

// Нулевой элемент в боре - это корень.
// Теперь для кадого подшаблона мы будем добавлять ребра посимвольно, если такого ребра еще не было.
// Если ребро из текущей вершины с этим символом уже есть, то мы просто переходим по нему.
vector<Node> MakeTrie( const vector<string>& splitPattern, const vector<int>& startPositions )
{
    vector<Node> trie;
    
    // Добавили корень.
    Node root( 0, -1 );
    trie.push_back( root );
    
    // Для каждого подшаблона:
    for( int i = 0; i < splitPattern.size(); ++i ) {
        int current = 0; // Текущая вершина (изначально это корень).
        // Для каждого символа в подшаблоне добавляем новое ребро, соотв. этому символу, если его не было.
        for( auto c: splitPattern[i] ) {
            if( trie[current].children[c - 97] == -1 ) {
                Node temp( current, c - 97 );
                trie.push_back( temp );
                int number = static_cast<int>( trie.size() - 1 );
                trie[current].children[c - 97] = number;
            }
            // Переходим по ребру.
            current = trie[current].children[c - 97];
        }
        // Когда все символа подшаблона обработаны, нужно пометить вершину, в которой мы оказались, как терминальную.
        // Запишем в нее также информацию о данном подшаблоне - вектор pos.
        // (Это понадобится на последнем этапе для оптимизации).
        trie[current].leaf = true;
        trie[current].pos.push_back( static_cast<int>( startPositions[i] + splitPattern[i].length() - 1 ) );
    }
    return trie;
}

int GetSuffixLink( vector<Node>& trie, int node )
{
    // Если мы еще не заполнили ссылку, то есть два варианта:
    if( trie[node].suffixLink == -1 ) {
        // Первый вариант: это корень или ребенок корня.
        // В любом случае наибольший собственный суффикс строки, полученной проходом из корня до node, равен 0,
        // то есть суффиксную ссылку для node устанавливаем на корень.
        if( node == 0 || trie[node].parent == 0 ) {
            trie[node].suffixLink = 0;
        }
        // Второй вариант: node не является ни корнем, ни ребенком корня.
        // В таком случае в боре может существовать ненулевой собственный суффикс для строки,
        // полученной проходом из корня до node. Найдем этот суффикс. Построим суффиксную ссылку рекурсивно.
        // Для этого рассмотрим собственный суффикс родителя вершины node и попробуем перейти вершины,
        // на которую указывает суффиксная ссылка родителя по ребру с символом 'c', таким, что из родителя node к node
        // ведет именно ребро с символом 'c'. Суффиксная ссылка для node должна как раз указывать на вершину, к которой мы
        // в итоге рекурсивно придем.
        else {
            trie[node].suffixLink = GetLink( trie, GetSuffixLink( trie, trie[node].parent ), trie[node].charToParent );
        }
    }
    return trie[node].suffixLink;
}

int GetLink( vector<Node>& trie, int node, int _char )
{
    if( trie[node].go[_char] == -1 ) {
        // Если из node выходит ребро c символом _char к ребенку v, то ссылка перехода для node равна v.
        if( trie[node].children[_char] != -1 ) {
            trie[node].go[_char] = trie[node].children[_char];
        } else {
            // Если из node не выходит ребро с символом _char и node - корень, то его ссылка перехода - корень.
            if( node ==  0 ) {
                trie[node].go[_char] = 0;
              // Иначе ссылка перехода для node - это вершина, на которую указывает ссылка перехода вершины u по _char,
              // где u - суффиксная ссылка вершины node.
            } else {
                trie[node].go[_char] = GetLink( trie, GetSuffixLink( trie, node ), _char );
            }
        }
    }
    return trie[node].go[_char];
}

int GetTerminateLink( vector<Node>& trie, int node )
{
    if( trie[node].terminateLink == -1 ) {
        // Вычисляем суффиксную ссылку v для node.
        int v = GetSuffixLink( trie, node );
        // Если v - лист, значит в v закончился какой-то шаблон, следовательно v и будет функцией выхода для node.
        if( trie[v].leaf == true ) {
            trie[node].terminateLink = v;
        } else {
            // Если v - корень, то v будет функцией выхода для node
            if( v == 0 ) {
                trie[node].terminateLink = 0;
              // Иначе мы рекурсивно переходим к рассмотрению функции выхода для вершины,
              // на которую указывает суффиксная ссылка v вершины node.
            } else {
                trie[node].terminateLink = GetTerminateLink( trie, v );
            }
        }
    }
    return trie[node].terminateLink;
}

//  Посимвольно считываем строку text. На каждом символе мы переходим в новое состояние по автомату trie.
//  Если состояние терминальное, то на данном символе заканчиваетя вхождение в text подшаблона, соотв. данному состоянию.
//  Далее нужно вернуться в корень, проходя по сжатым суффиксным ссылкам, чтобы учесть все подшаблоны, которые
//  могут заканчиваться на данном символе.
//  Создадим вектор C, j-й элемент которого показывает, сколько на данный момент подшаблонов совпадает с соотв. частями
//  строки text, если начало шаблона поместить в позицию j в строке text.
//  Если в какой-то момент C[j] = |splitPattern|, то на j-й позиции начинается вхождение шаблона в строку.
//  (|splitPattern| = #подшаблонов)
//  На i-й итерации легко найти нужный индекс j для массива C, используя вектор pos соотв. терминальной вершины.
vector<int> FindPositions( vector<Node>& trie, const string& text, const string& pattern, const vector<string>& splitPattern )
{
    vector<int> result( 0 );
    vector<int> C( text.length() - pattern.length() + 1, 0 );
    int current = 0;
    for( int i = 0; i < text.size(); ++i ) {
        int c = text[i] - 97;
        current = GetLink( trie, current, c );
        int tmp = current;
        while( tmp > 0 ) {
            if( trie[tmp].leaf == true ) {
                for( int p: trie[tmp].pos ) {
                    if( i - p >= 0 && i - p < C.size() ) {
                        ++C[i - p];
                        if( C[i - p] == splitPattern.size() ) {
                            result.push_back( i - p );
                            break;
                        }
                    }
                }

            }
            tmp = GetTerminateLink( trie, tmp );
        }
    }
    return result;
}

