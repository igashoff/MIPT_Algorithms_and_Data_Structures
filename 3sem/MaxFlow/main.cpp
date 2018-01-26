//
//  main.cpp
//  MaxFlow
//
//  Created by Igashov_Ilya on 06.11.16.
//  Copyright (c) 2016 Igashov_Ilya. All rights reserved.
//

#include <iostream>
#include <limits.h>
#include <vector>
#include <queue>

enum Color {white, grey, black};

struct CVertex
{
    int number;
    int height;
    Color color;
    
    CVertex() {}
    CVertex( int n, int h, Color c ): number( n ), height( h ), color( c ) {}
    bool operator<( const CVertex& other ) const
    {
        return height < other.height;
    }
};

CVertex makeVertex( int n, int h, Color c )
{
    return CVertex( n, h, c );
}

bool Bfs( const std::vector<std::vector<int>>& matrix, std::vector<std::vector<int>>& layeredNetwork, int s, int t );
int Dfs( std::vector<std::vector<int>>& matrix, const std::vector<std::vector<int>>& layeredNetwork, int s, int t, int flow );

int main()
{
    int n, s, t, c;
    std::cin >> n >> s >> t >> c;
    std::vector<std::vector<int>> matrix( n );
    std::vector<std::vector<int>> layeredNetwork( n );
    for( int i = 0; i < n; ++i ) {
        matrix[i].resize( n, 0 );
        layeredNetwork[i].resize( n, 0 );
    }
    
    for( int i = 0; i < c; ++i ) {
        int a, b, w;
        std::cin >> a >> b >> w;
        matrix[a - 1][b - 1] = w;
        matrix[b - 1][a - 1] = w;
    }
    
    int flow = 0;
    while( Bfs( matrix, layeredNetwork, s, t ) ) {
        flow += Dfs( matrix, layeredNetwork, s, t, INT_MAX );
        for( int i = 0; i < n; ++i ) {
            layeredNetwork[i].resize( n, 0 );
        }
    }
    std::cout << flow;
    
    return 0;
}

bool Bfs( const std::vector<std::vector<int>>& matrix, std::vector<std::vector<int>>& layeredNetwork, int s, int t )
{
    std::vector<CVertex> heights;
    for( int i = 0; i < matrix.size(); ++i ) {
        heights.push_back( makeVertex( i + 1, -1, white ) );
    }
    
    std::queue<CVertex *> Q;
    heights[s - 1].height = 0;
    heights[s - 1].color = grey;
    Q.push(&heights[s - 1]);
    
    while (!Q.empty())
    {
        CVertex* u = Q.front();
        Q.pop();
        int i = 0;
        for ( auto & e: matrix[u->number - 1] )
        {
            if ( e != 0 && heights[i].color == white )
            {
                heights[i].color = grey;
                heights[i].height = u->height + 1;
                Q.push(&heights[i]);
                layeredNetwork[u->number - 1][i] = matrix[u->number - 1][i];
            }
            ++i;
        }
        u->color = black;
    }
    
    return heights[t - 1].height != -1;
}

int Dfs (std::vector<std::vector<int>>& matrix, const std::vector<std::vector<int>>& layeredNetwork, int v, int t, int flow)
{
    if( !flow )  return 0;
    if( v == t )  return flow;
    for( int i = 0; i < layeredNetwork.size(); ++i ) {
        if( layeredNetwork[v][i] == 0 )  continue;
        int pushed = Dfs( matrix, layeredNetwork, i, t, std::min( flow, layeredNetwork[v][i] ) );
        if (pushed) {
            matrix[i][v] += pushed;
            matrix[v][i] -= pushed;
            return pushed;
        }
    }
    return 0;
}
