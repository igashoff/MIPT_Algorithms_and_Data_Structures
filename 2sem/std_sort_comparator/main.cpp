//
//  main.cpp
//  std_sort_comparator
//
//  Created by Igashov_Ilya on 14.03.16.
//  Copyright (c) 2016 Igashov_Ilya. All rights reserved.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>

template <typename T>
class TLessCmp {
public:
    static int count;
    bool operator ()(const T& a, const T& b)
    {
        ++count;
        if (a < b)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    int getcount() const
    {
        return count;
    }
};

template <typename T>
int TLessCmp<T>::count = 0;

int main()
{
    srand((unsigned)time(0));
    int a[2000];
    for (int i = 0; i< 2000; ++i)
    {
        a[i] = rand()%100;
    }
    std::vector<int> v(a, a+sizeof(a)/sizeof(int));
    TLessCmp<int> cmp;
    std::sort(v.begin(), v.end(), cmp);
    for (int i : v) {
        std::cout << i << '\n';
    }
    
    std::cout << cmp.getcount();
    return 0;
}
