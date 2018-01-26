//This file was created with Single-C-File
//Single-C-File was developed by Adrian Dawid.
#include <iostream>
#include <vector>
#include <math.h>
#include <deque>
#include <map>
const int N = 9;
const int n = 3;
const std::vector<int> finalPlacement = {1,2,3,4,5,6,7,8,0};
class CPlacement
{
public:
    CPlacement() {}
    CPlacement( const std::vector<int>& _placement );
    
    int GetF() const { return f; }
    int GetG() const { return g; }
    int GetH() const { return h; }
    const CPlacement* GetParent() const { return parent; }
    int GetBlankPosition() const { return blankPosition; }
    const std::vector<int>& GetPlacement() const { return placement; }
    
    // Имеет смысл использовать Set_F() только после вызова метода SetG, поскольку в противном случае ничего не изменится.
    void SetF() { f = g + h; }
    void SetG( int _g ) { g = _g; }
    void SetParent( const CPlacement* _parent ) { parent = _parent; }
    
    std::vector<CPlacement> FindNeighbours() const;
    bool IsSolution() const;
    
    bool operator<( const CPlacement & other ) const;
    bool operator==( const CPlacement & other ) const;
    
private:
    std::vector<int> placement; // Одномерный массив, в котором записано расположение клеток на доске (можно было бы использовать и двумерный, но не обязательно)
    int f; // Значение функции f = g + h.
    int g; // Длина пути от стартовой вершины до данной (будет обновляться в процессе работы A*).
    int h; // Эвристическая функция.
    const CPlacement* parent; // Родитель вершины в графе ходов.
    int blankPosition; // Положение пустой клетки на доске (номер соответствующей ячейки массива placement).
    
    int countH() const; // Считает эвристику.
    int countPermutations() const; // Считает, сколько клеток стоят не на своих местах.
    int findBlankPosition() const; // Находит пустую клетку.
    void normalize(); // Используется в конструкторе копирования и в методе поиска соседей.
};
#include <cassert>
CPlacement::CPlacement( const std::vector<int>& _placement ) :
placement( _placement ),
g( 0 ),
parent( nullptr )
{
    normalize();
}
std::vector<CPlacement> CPlacement::FindNeighbours() const
{
    std::vector<CPlacement> nbours( 0 );
    
    // Максимум может быть 4 варианта, куда переместится пустая клетка
    CPlacement rightNeighbour( *this );
    CPlacement leftNeighbour( *this );
    CPlacement downNeighbour( *this );
    CPlacement upNeighbour( *this );
    
    // Для каждого из 4 соседей сначала проверяем, есть ли он. Если есть, то добавляем его в массив соседей
    if( blankPosition % n + 1 < n ) {
        std::swap( rightNeighbour.placement[blankPosition], rightNeighbour.placement[blankPosition + 1] );
        rightNeighbour.normalize();
        nbours.push_back( rightNeighbour );
    }
    
    if ( blankPosition % n - 1 >= 0 ) {
        std::swap( leftNeighbour.placement[blankPosition], leftNeighbour.placement[blankPosition - 1] );
        leftNeighbour.normalize();
        nbours.push_back( leftNeighbour );
    }
    
    if ( blankPosition + n < N ) {
        std::swap( downNeighbour.placement[blankPosition], downNeighbour.placement[blankPosition + n] );
        downNeighbour.normalize();
        nbours.push_back( downNeighbour );
    }
    
    if ( blankPosition - n >= 0 ) {
        std::swap( upNeighbour.placement[blankPosition], upNeighbour.placement[blankPosition - n] );
        upNeighbour.normalize();
        nbours.push_back( upNeighbour );
    }
    
    return nbours;
}
bool CPlacement::IsSolution() const
{
    // Четность/нечетность количества перестановок - инвариант, который не меняется на протяжении всей игры.
    return !(countPermutations() % 2);
}
bool CPlacement::operator<( const CPlacement& other ) const
{
    return f >= other.f;
}
bool CPlacement::operator==( const CPlacement& other ) const
{
    return placement == other.placement;
}
int CPlacement::countH() const
{
    int count = 0;
    
    // Считается манхэттенское расстояние каждой клетки до своей позиции
    // Результат - сумма расстояний всех клеток
    for( int i = 0; i < N; ++i ) {
        if( placement[i] != 0 ) {
            count += fabs( static_cast<double>( i / n - (placement[i] - 1) / n ) ) +
            fabs( static_cast<double>( i % n - (placement[i] - 1) % n ) );
        }
    }
    
    // Другая эвристика: количество клеток, стоящих не на своих местах.
    // for (int i = 0; i < N; ++i)
    // if (placement[i] != 0 && i != placement[i] - 1)
    // ++count
    
    return count;
}
int CPlacement::countPermutations() const
{
    int count = 0;
    
    for( int i = 0; i < N - 1; ++i ) {
        for( int j = i + 1; j < N; ++j ) {
            if( placement[i] > placement[j] && placement[i] != 0 && placement[j] != 0 ) {
                ++count;
            }
        }
    }
    
    return count;
}
int CPlacement::findBlankPosition() const
{
    for( int i = 0; i < N; ++i ) {
        if( placement[i] == 0 ) {
            return i;
        }
    }
    assert( false );
    return 0;
}
void CPlacement::normalize()
{
    blankPosition = findBlankPosition();
    h = countH();
    f = g + h;
}
#include <queue>
#include <set>
#include <stack>
#include <algorithm>
class Compare
{
public:
    bool operator()( const CPlacement& a, const CPlacement& b )
    {
        return a.GetPlacement() < b.GetPlacement();
    }
};
CPlacement Astar( const CPlacement& start, const CPlacement& finish, std::set<CPlacement, Compare>& U );
void PrintPath( CPlacement& finish, FILE* f );
int main()
{
    std::vector<int> startPlacement( N ); // Начальное расположение клеток на доске.
    
    FILE* f = fopen( "puzzle.in", "r" );
    for( int i = 0; i < N; ++i ) {
        fscanf( f, "%d", &startPlacement[i] );
    }
    fclose( f );
    
    std::set<CPlacement, Compare> U; // Массив "рассмотренных" вершин графа ходов.
    std::map<std::vector<int>, CPlacement> vertices; // Map всех вершин, с которыми мы работаем или работали
    CPlacement start( startPlacement );
    CPlacement finish( finalPlacement );
    
    f = fopen( "puzzle.out", "w" );
    
    // Проверка на существование пути.
    if( !start.IsSolution() ) {
        fprintf( f, "%d", -1 );
    } else {
        // Поиск пути и вывод результата.
        finish = Astar( start, finish, U );
        PrintPath( finish , f );
    }
    
    fclose( f );
    return 0;
}
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
            auto par = &*U.find( current );
            if( (tentativeScore < v.GetG()) || it == U.end() ) {
                v.SetParent( par );
                v.SetG( tentativeScore );
                v.SetF();
                Q.push( v );
            }
        }
    }
    
    assert( false );
    return CPlacement();                                                                                            //(*)
}
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
    //std::cout << path.size() << std::endl;
    
    while( !path.empty() ) {
        fprintf( f, "%c", path.top() );
        //std::cout << path.top();
        path.pop();
    }
}
