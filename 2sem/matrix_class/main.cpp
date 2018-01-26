//
//  main.cpp
//  matrix
//
//  Created by Igashov_Ilya on 16.04.16.
//  Copyright (c) 2016 Igashov_Ilya. All rights reserved.
//

#include <iostream>
#include "header.h"
#include <initializer_list>


int main()
{
    matrix<int> mat_1(4, 2, 1);
    matrix<int> mat_2(4, 2, 5);
    matrix<int> mat {{1, 2, 3}, {4, 5, 6}};
    std::cout << mat;
    
    std::cout << "mat_1 size:\n" << mat_1.size().first << " x " << mat_1.size().second << std::endl;
    std::cout << "mat_1 + mat_2:\n" << mat_1 + mat_2;
    
    matrix<int> mat_3(3, 2, {1, 2, 3, 4, 5, 6});
    std::cout << "mat_3:\n" << mat_3 << "transponated:\n" << mat_3.transponate();
    
    matrix<double> mat_4 (3, 3, {2, 5, 7, 6, 3, 4, 5, -2, -3});
    std::cout << "mat_4:\n" << mat_4 << "det(mat_4) = " << mat_4.determinate() << std::endl;
    std::cout << "inversed mat_4:\n" << mat_4.inverse();

    return 0;
}
