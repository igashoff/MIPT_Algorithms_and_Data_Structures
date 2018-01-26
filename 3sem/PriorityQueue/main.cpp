//
//  main.cpp
//  PriorityQueue
//
//  Created by Igashov_Ilya on 12.10.16.
//  Copyright (c) 2016 Igashov_Ilya. All rights reserved.
//

#include <iostream>
#include <deque>
#include <set>
#include <assert.h>
#include <initializer_list>

template <typename U, typename V>
struct pair
{
    U first;
    V second;
    
    bool operator==( const pair& other ) const
    {
        return first == other.first;
    }
    
    bool operator<( const pair& other ) const
    {
        return first < other.first;
    }
};

template <typename U, typename V>
pair<U, V> make_pair( const U& fst, const V& snd )
{
    pair<U, V> temp;
    temp.first = fst;
    temp.second = snd;
    return temp;
}

template <typename T>
class CPriorityQueue
{
public:
    CPriorityQueue() {}
    
    CPriorityQueue( const std::initializer_list<T>& list )
    {
        for( const auto& obj: list ) {
            Push( obj );
        }
    }
    
    const T& Top() const
    {
        return priorityQueue[0]->first;
    }
    
    void Pop()
    {
        std::swap( priorityQueue[0], priorityQueue[priorityQueue.size() - 1] );
        change( priorityQueue[0]->first, make_pair( priorityQueue[0]->first, 0 ) );
        priorityQueue.pop_back();
        siftDown( 0 );
    }
    
    void Push( const T& object )
    {
        objects.insert( make_pair<T, int>( object, static_cast<int>( priorityQueue.size() ) ) );
        priorityQueue.push_back( &*objects.find( make_pair<T, int>( object, 0 ) ) );
        siftUp( static_cast<int>( priorityQueue.size() - 1 ) );
    }
    
    bool Empty() const
    {
        return priorityQueue.size() == 0;
    }
    
    int Find( const T& object ) const
    {
        if( objects.find( make_pair<T, int>( object, 0 ) ) != objects.end() ) {
            return objects.find( make_pair<T, int>( object, 0 ) )->second;
        } else {
            return -1;
        }
        
    }
    
    void Erase( const T& object )
    {
        int pos = Find( object );
        assert( pos != -1 );
        
        std::swap( priorityQueue[pos], priorityQueue[priorityQueue.size() - 1] );
        change( priorityQueue[pos]->first, make_pair( priorityQueue[pos]->first, pos ) );
        priorityQueue.pop_back();
        siftDown( pos );
    }
    
private:
    std::deque<const pair<T, int>*> priorityQueue;
    std::set<pair<T, int>> objects;
    
    void change( const T& old, const pair<T, int>& newOne )
    {
        objects.erase( make_pair<T, int>( old, 0 ) );
        objects.insert( newOne );
    }
    
    int parent( int pos ) const { return (pos - 1) / 2; }
    int left( int pos ) const { return 2 * pos + 1; }
    int right( int pos ) const { return 2 * pos + 2; }

    
    void siftUp( int pos )
    {
        while( pos > 0 && priorityQueue[parent( pos )]->first < priorityQueue[pos]->first ) {
            change( priorityQueue[pos]->first, make_pair<T, int>( priorityQueue[pos]->first, parent( pos ) ) );
            change( priorityQueue[parent( pos )]->first, make_pair<T, int>( priorityQueue[parent( pos )]->first, pos ) );
            std::swap( priorityQueue[pos], priorityQueue[parent( pos )] );
            pos = parent( pos );
        }
    }
    
    void siftDown( int pos )
    {
        int l = left( pos );
        int r = right( pos );
        int largest;
        if( l < priorityQueue.size() ) {
            largest = l;
        } else {
            largest = pos;
        }
        if( r < priorityQueue.size() && priorityQueue[largest]->first < priorityQueue[r]->first ) {
            largest = r;
        }
        if( largest != pos ) {
            if( largest == r ) {
                change( priorityQueue[r]->first, make_pair<T, int>( priorityQueue[r]->first, pos ) );
                change( priorityQueue[pos]->first, make_pair<T, int>( priorityQueue[pos]->first, r ) );
                std::swap( priorityQueue[r], priorityQueue[pos] );
            } else if( largest == l ) {
                change( priorityQueue[l]->first, make_pair<T, int>( priorityQueue[l]->first, pos ) );
                change( priorityQueue[pos]->first, make_pair<T, int>( priorityQueue[pos]->first, l ) );
                std::swap( priorityQueue[l], priorityQueue[pos] );
            }
            siftDown( largest );
        }
    }
};


int main()
{
    CPriorityQueue<int> q = {1, 1, 1, 1, 1};
    q.Erase( 1 );
    while( !q.Empty() ) {
        int temp = q.Top();
        std::cout << q.Top() << ' ';
        
        q.Pop();
    }
    return 0;
}