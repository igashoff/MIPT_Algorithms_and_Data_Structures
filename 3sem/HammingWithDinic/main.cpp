//
//  main.cpp
//  HammingWithDinic
//
//  Created by Igashov_Ilya on 15.11.16.
//  Copyright (c) 2016 Igashov_Ilya. All rights reserved.
//

//  Расстояние Хэмминга между двумя строками равной длины — это количество индексов, в которых символы этих строк не равны.
//  Определим расстояние от шаблона p до строки s как суммарное расстояние Хэмминга от p до всех подстрок s, имеющих длину
//  |p|. В строке и в шаблоне некоторые символы стёрты. Нужно восстановить стёртые символы так, чтобы расстояние от p до s
//  было минимально возможным.
//  Формат ввода:
//  В первой строке дана строка s, во второй — шаблон p. Обе строки непусты, имеют длину не более 1000 и состоят из символов
//  `0', `1' и `?'. `?' обозначает стёртые символы, которые нужно восстановить. Длина строки p не превосходит длины строки s.
//  Формат вывода:
//  В первой строке выведите минимальное расстояние от p до s после восстановления всех стёртых символов. Во второй и третьей
//  строках соответственно выведите s и p, в которых символы `?' заменены на `0' и `1'.

#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <limits.h>

struct CVertex
{
    // Тройка, обозначающая ребро.
    struct triple
    {
        CVertex* first;     // Указатель на вершину, в которую ведет это ребро.
        int second;         // Вес ребра (пропукная способность).
        int third;          // Поток через это ребро.
        
        triple() {}
        triple( CVertex* f, int s, int t = 0 ): first( f ), second( s ), third( t ) {}
    };
    
    int number;                             // Номер вершины.
    char value;                             // Символ, который обозначает эта вершина.
    std::map<int, triple> neighbours;       // Смежные вершины.
    
    // Для Диница
    int d;  // Расстояние до вершины от истока после Bfs.
    int p;  // Номер вершины, ребро до которой является первым необнуленным на пути из данной до стока.
    
    CVertex() {}
    CVertex( int _number, char _value ): number( _number ), value( _value ), d( 0 ), p( 0 ) {}
    
    // Сравнение для очереди в Bfs.
    bool operator<( const CVertex other ) const
    {
        return d > other.d;
    }
};

//  Конструирует тройку (как std::make_pair).
CVertex::triple make_triple( CVertex* f, int s, int t = 0 );

//  Проверяет, являются ли входные данные тривиальными: если один из символов '1' или '0' отсутствует во входных строках,
//  ответ можно дать сразу. Функция выводит ответ в этом случае.
bool Trivial( std::string s, std::string p );

//  Чтобы найти минимальное расстояние Хэмминга между строкой s и шаблоном p, на первом этапе нужно построить двудольный
//  граф, где каждая вершина обозначает каждый конкретный символ в строках, а ребра межу вершинами проводятся, если в случае
//  какого-либо наложения шаблона на строку позиции этих двух вершин (символов в строке и шаблоне) совпадают.
//  Дополнительно эта функция записывает в массив undefinedPositions номера вершин - символов '?' (вершины-символы нумеруются
//  по порядку от нуля до |s|+|p|-1 так, что первый символ в s имеет номер 0, а последний в p - номер |s|+|p|-1).
std::vector<CVertex> MakeGraph( const std::string& s, const std::string& p, std::vector<int>& undefinedPositions );

//  Следующий этап - объединить все '0'-вершины в одну и все '1'-вершины в одну. При этом если изначально все ребра в графе
//  были единичными, то теперь веса ребер складываются в соответствующих случаях. Дополнительно эта функция найдет и запишет
//  в vertex позицию истока или стока в зависимости от того, какие параметры она принимает.
void Union( std::vector<CVertex>& graph, char c, int& vertex );

//  Функция Bfs ищет кратчайшие пути из истока sourse до каждой вершины (эти пути записываются в поле d).
//  Возвращает true, если путь из истока в сток есть, и false иначе.
bool Bfs( std::vector<CVertex>& graph, int sourse, int target );

//  Функция Dfs пускает по какому-то пути из истока в сток блокирующий поток.
int Dfs( std::vector<CVertex>& graph, int sourse, int target, int u, int minC );

// Функция, реализующая алгоритм Диница поиска максимального потока в сети.
int Dinic( std::vector<CVertex>& graph, int sourse, int target );

// Функция, которая восстанавливает в строках s и p недостающие символы.
void CompleteStrings( std::string& s, std::string& p, const std::vector<CVertex>& graph, const std::vector<int>& undefinedPositions);



int main()
{
    std::string s, p;
    std::cin >> s >> p;
    if( Trivial( s, p ) ) {
        return 0;
    }
    
    std::vector<int> undefinedPositions;
    std::vector<CVertex> graph = MakeGraph( s, p, undefinedPositions );
    
    int source = 0; int target = 0;
    Union( graph, '0', source );
    Union( graph, '1', target );
    
    int maxFlow = Dinic( graph, source, target );
    
    CompleteStrings( s, p, graph, undefinedPositions);
    std::cout << maxFlow << std::endl << s << std::endl << p;
    
    return 0;
}

CVertex::triple make_triple( CVertex* f, int s, int t )
{
    return CVertex::triple( f, s, t );
}


bool Trivial( std::string s, std::string p )
{
    // Проверяем отсутствие '1' в строках s и p.
    if( s.find( '1' ) == std::string::npos && p.find( '1' ) == std::string::npos) {
        for( int i = 0; i < s.length(); ++i ) {
            if( s[i] == '?' ) {
                s[i] = '0';
            }
        }
        for( int i = 0; i < p.length(); ++i ) {
            if( p[i] == '?' ) {
                p[i] = '0';
            }
        }
        std::cout << 0 << std::endl << s << std::endl << p;
        return true;
    }
    // Проверяем отсутствие '0' в строках s и p.
    if( s.find( '0' ) == std::string::npos && p.find( '0' ) == std::string::npos) {
        for( int i = 0; i < s.length(); ++i ) {
            if( s[i] == '?' ) {
                s[i] = '1';
            }
        }
        for( int i = 0; i < p.length(); ++i ) {
            if( p[i] == '?' ) {
                p[i] = '1';
            }
        }
        std::cout << 0 << std::endl << s << std::endl << p;
        return true;
    }
    
    return false;
}

std::vector<CVertex> MakeGraph( const std::string& s, const std::string& p, std::vector<int>& undefinedPositions )
{
    std::vector<CVertex> graph;
    int i = 0;
    // Проходим по строке s.
    for( auto c: s ) {
        // Создаем и добавляем i-ю символ-вершину в граф.
        CVertex temp( i, c );
        graph.push_back( temp );
        // Если символ является '?', то добавляем в undefinedPositions номер позиции этой вершины в графе graph.
        if( c == '?' ) {
            undefinedPositions.push_back( i );
        }
        ++i;
    }
    // Номер вершины, соответствующей первому символу в шаблоне.
    int firstInP = i;
    // Делаем все то же самое с шаблоном p.
    for( auto c: p ) {
        CVertex temp( i, c );
        graph.push_back( temp );
        if( c == '?' ) {
            undefinedPositions.push_back( i );
        }
        ++i;
    }
    
    // Строим ребра в графе graph.
    for( int i = 0; i < 2 * firstInP - graph.size() + 1; ++i ) {
        for( int j = 0; j < graph.size() - firstInP; ++j ) {
            graph[i + j].neighbours[firstInP + j] = make_triple( &graph[firstInP + j], 1 );
            graph[firstInP + j].neighbours[i + j] = make_triple( &graph[i + j], 1 );
        }
    }
    
    return graph;
}

void Union( std::vector<CVertex>& graph, char c, int& vertex )
{
    // Задача: для всех не 'c' вершин изменить их списки смежности и построить список для объединенной 'c'-вершины.
    // Первый элемент в graph, который является 'c'-вершиной, станет объединенной вершиной. Все остальные 'c'-вершины
    // останутся в массиве graph, но они превратятся в 'x'-вершины и в итоге к ним не будут вести никакие ребра из
    // оставшихся нормальных вершин. Дальше эти вершины не будут учитываться и использоваться.
    
    // Найдем номер n первой 'c'-вершины. Это и будет позицией истока или стока.
    int n = 0;
    for( n = 0; n < graph.size(); ++n ) {
        if( graph[n].value == c ) {
            break;
        }
    }
    
    // В edgeCapacities будут записываться веса новых ребер, которые будут идти от объединенной 'c'-вершины к остальным
    // (индексы соответствуют номерам вершин, к которым идут ребра).
    // Пройдемся по graph и на каждой 'c'-вершине мы будем прибавлять к соответствующим элементам edgeCapacities веса
    // ребер, ведущих из этой 'c'-вершины
    std::vector<int> edgeCapacities( graph.size(), 0 );
    
    for( int i = 0; i < graph.size(); ++i ) {
        if( graph[i].value == c ) {
            for( const auto& v: graph[i].neighbours ) {
                // Инкрементируем элемент с индексом вершины v, в которую ведет ребро из данной, если эта вершина v не 'c'.
                edgeCapacities[v.second.first->number] += ( v.second.first->value != c && v.second.first->value != 'x' ) ? v.second.second : 0;
            }
            // Если это не первая 'c' - вершина, то превращаем ее в 'x'-вершину.
            if ( i != n ) {
                graph[i].value = 'x';
            }
        }
        // Если это не 'c'-вершина, то поменяем ее список смежности: ребра, ведущие из нее к не'c'- и не'x'- вершинам
        // остаются такими же, а все ребра, ведущие к 'c'- и 'x'- вершинам складываются в одно ребро.
        else {
            // Подсчет количества ребер из этой вершины в 'c'- и 'x'-вершины.
            int cnt = 0;
            // Копируем сюда только ребра, ведущие в не'c'- и не'x'-вершины.
            std::map<int, CVertex::triple> newNeighbours;
            for( const auto& v: graph[i].neighbours ) {
                if( v.second.first->value == c || v.second.first->value == 'x' ) {
                    cnt += v.second.second;
                } else {
                    newNeighbours.insert( v );
                }
            }
            // Наконец, добавляем новое ребро, имеющее, возможно, вес больше 1, ведущее в объединенную 'c'-вершину.
            if( cnt > 0 ) {
                newNeighbours[n] = make_triple( &graph[n], cnt );
            }
            
            // И мы построили новый список смежности для не'c' - вершины.
            graph[i].neighbours = newNeighbours;
        }
    }
    
    // Теперь построим новый список для объединенной вершины.
    std::map<int, CVertex::triple> newNeighbours;
    for( int i = 0; i < edgeCapacities.size(); ++i ) {
        if( edgeCapacities[i] > 0 ) {
            newNeighbours[i] = make_triple( &graph[i], edgeCapacities[i] );
        }
    }
    graph[n].neighbours = newNeighbours;
    
    // Записываем в vertex номер объединенной вершины (это или сток, или исток).
    vertex = n;
}

bool Bfs( std::vector<CVertex>& graph, int source, int target )
{
    // Изначально расстояние до всех вершин равны ∞, а номера первых неудаленных ребер - 0.
    for( int i = 0; i < graph.size(); ++i ) {
        graph[i].d = INT_MAX;
        graph[i].p = 0;
    }
    
    std::queue<CVertex *> Q;
    // Расстояние до истока ставим равным нулю и добавляем исток в очередь Q.
    graph[source].d = 0;
    Q.push(&graph[source]);
    
    // Пока очередь не опустеет, достаем из нее первую вершину (с минимальным d) и работаем с ее соседями.
    while( !Q.empty() ) {
        CVertex* u = Q.front();
        Q.pop();
        for( auto& e: graph[u->number].neighbours ) {
            // Если такое ребро еще есть в остаточной сети и вершина, в которую оно ведет, еще не просмотрена, то
            // меняем расстояние d до нее.
            if( e.second.third < e.second.second && e.second.first->d == INT_MAX ) {
                e.second.first->d = u->d + 1;
                Q.push( e.second.first );
            }
        }
    }
    
    return graph[target].d != INT_MAX;
}

int Dfs( std::vector<CVertex>& graph, int source, int target, int u, int minC )
{
    if( u == target || minC == 0 ) {
        return minC;
    }
    for( int v = graph[u].p;  v < graph.size(); ++v ) {
        if( graph[v].d == graph[u].d + 1 ) {
            if( graph[u].neighbours.find( v ) != graph[u].neighbours.end() ) {
                CVertex::triple* edge = &graph[u].neighbours.find( v )->second;
                int delta = Dfs( graph, source, target, v, std::min( minC, edge->second - edge->third ) );
                if( delta != 0 ) {
                    edge->third += delta;
                    CVertex::triple* reverseEdge = &graph[v].neighbours.find( u )->second;
                    reverseEdge->third -= delta;
                    return delta;
                }
            }
        }
        ++graph[u].p;
    }
    return 0;
}

int Dinic( std::vector<CVertex>& graph, int source, int target )
{
    int maxFlow = 0;
    while( Bfs( graph, source, target ) ) {
        int flow = Dfs( graph, source, target, source, INT_MAX );
        while( flow != 0 ) {
            maxFlow += flow;
            flow = Dfs( graph, source, target, source, INT_MAX );
        }
    }
    return maxFlow;
}

void CompleteStrings( std::string& s, std::string& p, const std::vector<CVertex>& graph, const std::vector<int>& undefinedPositions)
{
    std::vector<char> symbols;
    for( int pos: undefinedPositions ) {
        if( graph[pos].d != INT_MAX ) {
            symbols.push_back( '0' );
        } else {
            symbols.push_back( '1' );
        }
    }
    
    int cnt = 0;
    for( char& c: s ) {
        if( c == '?' ) {
            c = symbols[cnt];
            ++cnt;
        }
    }
    for( char& c: p ) {
        if( c == '?' ) {
            c = symbols[cnt];
            ++cnt;
        }
    }
}

