//
//  main.cpp
//  Salesman
//
//  Created by Igashov_Ilya on 11.11.16.
//  Copyright (c) 2016 Igashov_Ilya. All rights reserved.
//
#include <iostream>
#include <vector>
#include <set>
#include <climits>
#include <cmath>
#include <ctime>

int time_ = 0;
typedef std::pair<double, double> Point;
const double EPS = 0.0001;
const double RAND_MAX_D = static_cast<double> (RAND_MAX);
enum Color {white, grey, black};

Point BoxMuller (const Point& center, double sigma)
{
    double x, y, s;
    do
    {
        x = 2.0 * (static_cast<double> (rand ()) / RAND_MAX_D) - 1.0;
        y = 2.0 * (static_cast<double> (rand ()) / RAND_MAX_D) - 1.0;
        s = x * x + y * y;
    } while ((s >= 1.0) || (s <= EPS));
    
    double lns = log (s);
    double z0 = x * sqrt (-2.0 * lns / s),
    z1 = y * sqrt (-2.0 * lns / s);
    return std::make_pair (center.first + sigma * z0, center.second + sigma * z1);
}


//  Структура вершины рафа. Содержит свой номер, ключ - вес инцидентного ей и "ведущего к ней" единственного ребра
//  в текущем остовном дереве и список смежных ей вершин.
struct CVertex
{
    int number;
    double key;
    std::vector<std::pair<CVertex*, double>> neighbours;
    CVertex* parent;
    Color color = white;
    
    CVertex(): number( 0 ), key( MAXFLOAT ), parent( nullptr ) {}
    CVertex( int _number ): number( _number ), key( MAXFLOAT ), parent( nullptr ) {}
    
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
std::vector<std::vector<int>> Prim( std::vector<CVertex>& vertices );
float DFS( std::vector<std::vector<int>>& mst, std::vector<CVertex>& vertices );


int main()
{
    srand( static_cast<unsigned int>( time( 0 ) ) );
    int N = 0;
    std::cin >> N;
    
    double sigma = 1;
    Point center = std::make_pair( 0, 0 );
    std::vector<Point> points( N );
    for( int i = 0; i < N; ++i ) {
        points[i] = BoxMuller( center, sigma ) ;
    }
    
    std::vector<CVertex> vertices;
    for( int i = 0; i < N; ++i ) {
        CVertex temp( i );
        vertices.push_back( temp );
    }
    for( int i = 0; i < N; ++i ) {
        for( int j = 0; j < N; ++j ) {
            if( j != i ) {
                CVertex temp( i );
                vertices[i].neighbours.push_back( std::make_pair( &vertices[j], sqrt( pow( points[i].first - points[j].first, 2 ) + pow( points[i].second - points[j].second, 2 ) ) ) );
            }
        }
    }
    
    std::vector<std::vector<int>> mst = Prim( vertices );
    float res = DFS( mst, vertices );
    std::cout << std::endl << res;
    
    
    return 0;
}

std::vector<std::vector<int>> Prim( std::vector<CVertex>& vertices )
{
    std::vector<std::vector<int>> mst( vertices.size() );
    for( int i = 0; i < vertices.size(); ++i ) {
        mst[i].resize( vertices.size(), 0 );
    }

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
                v->parent = &vertices[u.number];
                
                std::cout << v->number << ' ' << v->parent->number << ' ' << v->key << std::endl;
                mst[v->number][v->parent->number] = v->key;
                mst[v->parent->number][v->number] = v->key;
                
                queue.insert( *v );
                numbers.insert( *v );
            }
        }
    }
    
    return mst;
}

float DFS( std::vector<std::vector<int>>& mst, std::vector<CVertex>& vertices )
{
    float cnt = 0;
    
        
    return cnt;
}






