//
//  main.cpp
//  telephone_number
//
//  Created by Igashov_Ilya on 23.04.16.
//  Copyright (c) 2016 Igashov_Ilya. All rights reserved.
//

#include <iostream>
#include <map>
#include <vector>

using namespace std;

size_t count(map<size_t, vector<size_t>> &, size_t , size_t);

int main()
{
    size_t N;
    cin >> N;
    
    map<size_t, vector<size_t>> psbl;
    psbl[0] = {4, 6};
    psbl[1] = {6, 8};
    psbl[2] = {7, 9};
    psbl[3] = {4, 8};
    psbl[4] = {0, 3, 9};
    psbl[5] = {};
    psbl[6] = {0, 1, 7};
    psbl[7] = {2, 6};
    psbl[8] = {1, 3};
    psbl[9] = {2, 4};
    
    size_t num = 0;
    for (size_t i = 1; i < 8; ++i)
        num += count(psbl, i, N);
    
    num += count(psbl, 9, N);
    
    cout << num;
    return 0;
}

size_t count(map<size_t, vector<size_t>> & p, size_t j, size_t n)
{
    if (n == 1)
    {
        return 1;
    }
    
    size_t num = 0;
    for (auto k: p[j])
        num += count(p, k, n - 1);
    return num;
}