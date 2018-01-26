//
//  main.cpp
//  Vector
//
//  Created by Igashov_Ilya on 14.03.16.
//  Copyright (c) 2016 Igashov_Ilya. All rights reserved.
//

#include <iostream>
#include <algorithm>
#include <vector>
#include "my_vector.h"

int main()
{
    double arr[] = {15.2, 3.5, 21.5, 1.1, 6.3, 5.2};
    Vector<double>  vector_1(6);
    
    for (int i = 0; i < 6; ++i)
    {
        vector_1[i] = arr[i];
    }
    
    std::cout << "size: " << vector_1.GetSize() << " capacity: " << vector_1.GetCapacity() << '\n';
    vector_1.PushBack(1.009);
    
    std::sort(vector_1.begin(), vector_1.end());
    
    for (double j: vector_1)
    {
        std::cout << j << '\n';
    }
    
    std::cout << "size: " << vector_1.GetSize() << " capacity: " << vector_1.GetCapacity() << '\n';
    
    Vector<bool> vector_2(4);
    
    //std::sort(BoolVector.begin(), BoolVector.end());
    vector_2.PushBack(true);
    std::cout << vector_2 << "size: " << vector_2.GetSize() << " capacity: " << vector_2.GetCapacity();
    
    return 0;
}

