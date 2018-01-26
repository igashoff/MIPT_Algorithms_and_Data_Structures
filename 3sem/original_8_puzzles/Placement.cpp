//
//  Placement.cpp
//  original_8_puzzles
//
//  Created by Igashov_Ilya on 10.10.16.
//  Copyright (c) 2016 Igashov_Ilya. All rights reserved.
//

#include "Placement.h"
#include <math.h>
#include <assert.h>

//---------------------------------------------------public---------------------------------------------------

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


//---------------------------------------------------private---------------------------------------------------


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