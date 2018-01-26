//
//  main.cpp
//  Prim_Algorithm
//
//  Created by Igashov_Ilya on 01.11.16.
//  Copyright (c) 2016 Igashov_Ilya. All rights reserved.
//

//  Первая строка входного файла содержит два натуральных числа n и m — количество вершин
//  и ребер графа соответственно (1 <= 𝑛 <= 20000, 0 <= 𝑚 <= 100000). Следующие 𝑚 строк содержат
//  описание ребер по одному на строке. Ребро номер i описывается тремя натуральными числами
//  b𝑖, e𝑖 и w𝑖 — номера концов ребра и его вес соответственно (1 <= b𝑖, e𝑖 <= n, 0 <= w𝑖 <= 100000).
//  Граф является связным.
//  Формат выходного файла:
//  Выведите единственное целое число - вес минимального остовного дерева

#include <fstream>
#include <vector>
#include <set>
#include <limits.h>

//  Структура вершины рафа. Содержит свой номер, ключ - вес инцидентного ей и "ведущего к ней" единственного ребра
//  в текущем остовном дереве и список смежных ей вершин.
struct CVertex
{
    int number;
    int key;
    std::vector<std::pair<CVertex*, int>> neighbours;
    
    CVertex(): number( 0 ), key( INT_MAX )  {}
    CVertex( int _number ): number( _number ), key( INT_MAX ) {}
    
    // Сравнение для очереди с приоритетом, функции которой выполняет set<CVertex> queue.
    bool operator<( const CVertex& other ) const
    {
        if( key == other.key ) {
            return number < other.number;
        } else {
            return key < other.key;
        }
    }
};

//  Сравнение для set<Cvertex> numbers
struct Comp
{
    bool operator()( CVertex a, CVertex b )
    {
        return a.number < b.number;
    }
};

//  Функция, реализующая алгоритм Прима поиска минимального остовного дерева в заданном графе, который
//  передается в качестве параметра как вектор вершин.
int Prim( std::vector<CVertex>& vertices );

int main()
{
    int n,m;
    std::ifstream fin( "kruskal.in" );
    fin >> n >> m;
    // Вектор вершин графа.
    std::vector<CVertex> vertices;
    for( int i = 0; i < n; ++i ) {
        CVertex temp( i + 1 );
        vertices.push_back( temp );
    }
    
    int a, b, w;
    for( int i = 0; i < m; ++i ) {
        fin >> a >> b >> w;
        // Заполняем списки смежности вершин.
        vertices[a - 1].neighbours.push_back( std::make_pair( &vertices[b - 1], w ) );
        vertices[b - 1].neighbours.push_back( std::make_pair( &vertices[a - 1], w ) );
    }
    fin.close();
    
    std::ofstream fout( "kruskal.out" );
    fout << Prim( vertices );
    fout.close();
    return 0;
}

int Prim( std::vector<CVertex>& vertices )
{
    // Сет, выполняющий роль очереди с приоритеом.
    std::set<CVertex> queue;
    // Сет, который позволяет быстро проверять, лежит ли данная вершина в очереди queue (сравнение элементов с помощью Comp).
    std::set<CVertex, Comp> numbers;
    // Ставим для первой вершины ключ минимальным и заполняем очередь и сет вершинами.
    vertices[0].key = 0;
    for( int i = 0; i < vertices.size(); ++i ) {
        queue.insert( vertices[i] );
        numbers.insert( vertices[i] );
    }
    // Пока очередь не станет пустой, извлекаем из нее вершину с наименьшим ключом и релаксируем
    // каждое инцидентное ей ребро, если оно ведет к вершине, все еще лежащей в очереди.
    while( !queue.empty() ) {
        CVertex u = *queue.begin();
        queue.erase( u );
        numbers.erase( u );
        for( auto edge: u.neighbours ) {
            if( numbers.find( *edge.first ) != numbers.end() && edge.first->key > edge.second ) {
                CVertex* v = edge.first;
                queue.erase( *v );
                numbers.erase( *v );
                v->key = edge.second;
                queue.insert( *v );
                numbers.insert( *v );
            }
        }
    }
    
    // Суммируем ключи всех вершин - это и есть вес построенного MST.
    int cnt = 0;
    for( int i = 0; i < vertices.size(); ++i ) {
        cnt += vertices[i].key;
    }
    
    return cnt;
    
}




