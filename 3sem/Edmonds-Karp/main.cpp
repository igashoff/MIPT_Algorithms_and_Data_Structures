//
//  main.cpp
//  Edmonds-Karp
//
//  Created by Igashov_Ilya on 08.11.16.
//  Copyright (c) 2016 Igashov_Ilya. All rights reserved.
//
//  Найдите величину максимального потока в заданном неориентированном графе.
//  Формат входного файла:
//  Во входном файле заданы один или несколько тестов. Каждый тест начинается строкой, в которой содержится
//  число n (2 ≤ n ≤ 100) — количество вершин графа. В следующей строке записаны три числа s, t и c — номер истока, номер
//  стока и количество ребер, соответственно. Далее следуют c строк, в каждой из которых содержатся три числа: номера
//  соединенных ребром вершин и его пропускная способность — целое неотрицательное число, не превосходящее 1 000. Между двумя
//  парами вершин может быть более одного ребра, однако петли не допускаются.
//  Входной файл завершается фиктивным тестом, состоящим из одного числа 0, который обрабатывать не нужно.
//  Формат выходного файла:
//  Для каждого из тестов выведите величину максимального потока.

#include <iostream>
#include <vector>
#include <queue>
#include <deque>

enum Color {white, grey, black};

//  Вершина ребра. Содержит номер, d - кратчайший путь из s в данной остаточной сети, color -  цвет для BFS,
//  parent - номер предшествующей ей вершины на пути из s.
struct CVertex
{
    int number;
    int d;
    Color color;
    int parent;
    
    CVertex() {}
    CVertex( int n, int _d, Color c ): number( n ), d( _d ), color( c ), parent( -1 ) {}
    bool operator<( const CVertex& other ) const
    {
        return d < other.d;
    }
};

CVertex makeVertex( int n, int _d, Color c )
{
    return CVertex( n, _d, c );
}

//  Алгоритм поиска в ширину. Возвращает вектор номеров вершин, через которые идет кратчайший путь из s в t,
//  включая эти вершины.
std::deque<int> Bfs( const std::vector<std::vector<int>>& matrix, int s, int t );
//  Функция, которая находит поток в остаточной сети и изменяет остаточную сеть, учитывая найденный поток.
//  Возвращает значение потока.
int AddFlow( std::vector<std::vector<int>>& matrix, const std::deque<int>& path, int s, int t );

int main()
{
    int n = 1;
    
    while( true ) {
        // Ввод данных.
        std::cin >> n;
        if( n == 0 ) {
            break;
        }
        
        int s, t, c;
        std::cin >> s >> t >> c;
        --s;
        --t;
        
        // Строим матрицу смежности.
        std::vector<std::vector<int>> matrix( n );
        for( int i = 0; i < n; ++i ) {
            matrix[i].resize( n, 0 );
        }
        for( int i = 0; i < c; ++i ) {
            int a, b, w;
            std::cin >> a >> b >> w;
            --a;
            --b;
            matrix[a][b] += w;
            matrix[b][a] += w;
        }
        
        int flow = 0;
        auto path = Bfs( matrix, s, t );
        
        // Пока в остаточной сети есть путь из s в t, пускаем поток через этот путь, обновляем сеть и ищем новый путь в ней.
        while( path.size() > 1 ) {
            flow += AddFlow( matrix, path, s, t );
            path = Bfs( matrix, s, t );
        }
        
        std::cout << flow << std::endl;
    }
    
    return 0;
}

std::deque<int> Bfs( const std::vector<std::vector<int>>& matrix, int s, int t )
{
    std::vector<CVertex> vertices;
    for( int i = 0; i < matrix.size(); ++i ) {
        vertices.push_back( makeVertex( i, -1, white ) );
    }
    
    std::queue<CVertex *> Q;
    vertices[s].d = 0;
    vertices[s].color = grey;
    Q.push(&vertices[s]);
    
    while (!Q.empty())
    {
        CVertex* u = Q.front();
        Q.pop();
        int i = 0;
        for ( int e: matrix[u->number] )
        {
            if ( e > 0 && vertices[i].color == white )
            {
                vertices[i].color = grey;
                vertices[i].d = u->d + 1;
                vertices[i].parent = u->number;
                Q.push(&vertices[i]);
            }
            ++i;
        }
        u->color = black;
    }
    
    std::deque<int> result;
    int p = vertices[t].parent;
    result.push_front( t );
    while( p != -1 ) {
        result.push_front( p );
        p = vertices[p].parent;
    }
    
    return result;
}

int AddFlow( std::vector<std::vector<int>>& matrix, const std::deque<int>& path, int s, int t )
{
    // В этом цикле вычисляется, какой поток мы пустим по найденному в Bfs пути из s в t.
    // Этот поток соответствует минимальному значению пропускной способности ребер из этого пути.
    int u = path[0];
    int v = path[1];
    int flow = matrix[u][v];
    for( int i = 1; i < path.size() - 1; ++i ) {
        u = path[i];
        v = path[i + 1];
        flow = std::min( matrix[u][v], flow );
    }
    
    // Обновляем остаточную сеть, вычитая из прямых ребер пути значение пущенного потока и прибавляя это значение
    // к обратным ребрам.
    u = path[0];
    v = path[1];
    for( int i = 0; i < path.size() - 1; ++i ) {
        u = path[i];
        v = path[i + 1];
        matrix[u][v] -= flow;
        matrix[v][u] += flow;
    }
    
    return flow;
}