//
//  main.cpp
//  B-tree
//
//  Created by Igashov_Ilya on 21.05.16.
//  Copyright (c) 2016 Igashov_Ilya. All rights reserved.
//

#include "b-tree.h"


int main()
{
    /*
    btree<int, int> x;
    for (int i = 0; i < 20; i += 1)
        x.insert(make_key(i, i));
    key<int, int> * tmp = x.min(x.get_root());
    while (tmp != x.max(x.get_root()))
    {
        cout << tmp->v << ' ';
        tmp = x.successor(x.get_root(), tmp->k);
    }
    
    
     *//*
    auto ptr = x.search(x.get_root(), 19);
    if (ptr)
        cout << ptr->k << ' ' << ptr->v << endl;
    x.inorder_walk(x.get_root());
    cout << endl;
    ptr = x.successor(x.get_root(), 233);
    cout << ptr->k << ' ' << ptr->v;
    */
    
    bmap<int, int> x;
    for (int i = 0; i < 20; ++i)
        x[i] = i;
    for (int i = 0; i < 20; ++i)
        cout << x.at(i) << ' ';
    x[0] = 100;
    x.at(1) = 101;
    x.insert(make_key(-1, 1000));
    try
    {
        x.at(500) = 12;
    }
    catch (out_of_range)
    {
        cout << endl << "catched" << endl;
    }
    
    for (auto i = x.begin(); i != x.end(); ++i)
        cout << (*i).v << ' ';
    
    return 0;
}
