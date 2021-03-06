//
//  main.cpp
//  original_15_puzzles
//
//  Created by Igashov_Ilya on 12.10.16.
//  Copyright (c) 2016 Igashov_Ilya. All rights reserved.
//

#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <stack>
#include <algorithm>
#include <assert.h>
#include "Placement.h"

// Компаратор для элементов в set U.
class Compare
{
public:
    bool operator()( const CPlacement& a, const CPlacement& b )
    {
        return a.GetPlacement() < b.GetPlacement();
    }
};


// Функция, реализующая алгоритм А*. Параметрами являются: начальное расположение клеток на доске,
// конечное и массив "закрытых" вершин графа ходов.
// Массив передается по ссылке, поскольку все новые расположения являются локальными объектами функции Astar,
// но после выхода из функции мы должны использовать указатели на эти вершины для восстановления пути.
// Функция возвращает вершину, являющуюся конечной с известным родителем (это позволит восстановить путь к ней).
CPlacement Astar( const CPlacement& start, const CPlacement& finish, std::set<CPlacement, Compare>& U );

// Функция, восстанавливающая путь до искомой вершины после работы алгоритма A*.
// Принимает конечную вершину finish, у которой известен родитель, и указаель на файл, куда записывать решение.
void PrintPath( CPlacement& finish, FILE* f );


int main()
{
    std::vector<int> startPlacement( N ); // Начальное расположение клеток на доске.
    
    FILE* f = fopen( "input.txt", "r" );
    for( int i = 0; i < N; ++i ) {
        fscanf( f, "%d", &startPlacement[i] );
    }
    fclose( f );
    
    std::set<CPlacement, Compare> U; // Массив "рассмотренных" вершин графа ходов.
    CPlacement start( startPlacement );
    CPlacement finish( finalPlacement );
    
    f = fopen( "output.txt", "w" );
    
    // Проверка на существование пути.
    if( !start.IsSolution() ) {
        fprintf( f, "%d", -1 );
        std::cout << "-1" << std::endl;
    } else {
        // Поиск пути и вывод результата.
        finish = Astar( start, finish, U );
        PrintPath( finish , f );
    }
    
    fclose( f );
    return 0;
}

// В очередь с приоритетом Q будем записывать все новые вершины.
// Пока очередь Q не опустеет или пока мы не вытащим из нее конечное искомое расположение finish,
// будем доставать из нее вершину с наименьшим значением f = g + h (переменная current) и рассматривать всех ее соседей:
// если очередной соседv v еще не попал в число рассмотренных вершин, т.е. в массив U, или расстояние от start до v (число g)
// оказалось больше обновленного расстояния tentativeScore от start до v (tentativeScore = current.g + 1), то:
// current становится родителем вершины v, расстояние от start до v меняется на tentativeScore, и
// добавляем v в Q независимо от того, была ли v уже добавлена в Q (можем так сделать, поскольку у вновь добавленной v
// значение f меньше значения f  вершины v, добавленной раньше, а значит из очереди раньше извлечется обновленная v).
// Фактически, проверка на наличие решения проводится вне функции Astar. А это гарантирует, что функция вернет конечную вершину
// finish и решение будет найдено. Поэтому (*) никогда не выполнятся в данной задаче.
CPlacement Astar( const CPlacement& start, const CPlacement& finish, std::set<CPlacement, Compare>& U )
{
    std::priority_queue<CPlacement> Q;
    Q.push( start );
    
    while( !Q.empty() ) {
        CPlacement current = Q.top();
        
        if( current == finish ) {
            return current;
        }
        
        Q.pop();
        U.insert( current );
        
        for( auto v: current.FindNeighbours() ) {
            int tentativeScore = current.GetG() + 1;
            
            auto it = U.find( v );
            auto parent = &*U.find( current );
            if( (tentativeScore < v.GetG()) || it == U.end() ) {
                v.SetParent( parent );
                v.SetG( tentativeScore );
                v.SetF();
                Q.push( v );
            }
        }
    }
    
    assert( false );
    return CPlacement();                                                                                            //(*)
}

// В зависимости от взаимного расположения пустых клеток на "родительской" и "дочерней" досках
// в стек ходов path записывается один из четырех симоовлов R, L, U и D.
// Стек удобен, поскольку мы начинаем узнавать ходы с конца, а, следовательно, извлечение из стека будет происходить
// в нужном порядке.
// Ходы записываются до момента, пока у очередной вершины не окажется родителя (parent == nullptr).
// Это значит, что мы достигли стартовой вершины.
void PrintPath( CPlacement& finish, FILE* f )
{
    std::stack<char> path;
    int tempEnd = finish.GetBlankPosition();
    int tempBegin = 0;
    const CPlacement* ptr = finish.GetParent();
    
    while( ptr != nullptr ) {
        tempBegin = ptr->GetBlankPosition();
        
        if( tempBegin < tempEnd ) {
            if( tempEnd - tempBegin > 1 ) {
                path.push( 'D' );
            } else {
                path.push( 'R' );
            }
        } else {
            if( tempBegin - tempEnd > 1 ) {
                path.push( 'U' );
            } else {
                path.push( 'L' );
            }
        }
        
        tempEnd = tempBegin;
        ptr = ptr->GetParent();
    }
    
    fprintf( f, "%lu\n", path.size() );
    std::cout << path.size() << std::endl;
    
    while( !path.empty() ) {
        fprintf( f, "%c", path.top() );
        std::cout << path.top();
        path.pop();
    }
}
