//
//  main.cpp
//  dota_clone
//
//  Created by Igashov_Ilya on 22.02.16.
//  Copyright (c) 2016 Igashov_Ilya. All rights reserved.
//

#include <iostream>
#include "header.h"

void interface(World *world, GameObject **objects);

int main()
{
    World *world;
    GameObject **objects;
    
    interface(world, objects);
    return 0;
}
