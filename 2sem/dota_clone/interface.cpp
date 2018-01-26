//
//  interface.cpp
//  dota_clone
//
//  Created by Igashov_Ilya on 02.03.16.
//  Copyright (c) 2016 Igashov_Ilya. All rights reserved.
//

#include <stdio.h>
#include "header.h"

void interface(World *world, GameObject **objects)

{
    int code;
    std::string answer;
    int current_object_index = -1;
    
    
    while (true)
    {
        std::cout << "> ";
        std::cin >> answer;
        std::cout << '\n';
        
        if (answer == "map")
        {
            code = 1;
        } else {
            if (answer == "show")
            {
                code = 2;
            } else {
                if (answer == "create")
                {
                    code = 3;
                } else {
                    if (answer == "dump")
                    {
                        code = 4;
                    } else {
                        if (answer == "move")
                        {
                            code = 5;
                        } else {
                            if (answer == "help")
                            {
                                code = 6;
                            } else {
                                if (answer == "quit")
                                {
                                    code = 7;
                                } else {
                                    code = 8;
                                }
                            }
                        }
                    }
                }
            }
        }
        switch (code)
        {
            case 1:
            {
                int width_;
                int height_;
                std::cin >> width_ >> height_;
                objects = new GameObject*[width_ * height_];
                world = new World(height_, width_);
                break;
            }
            case 2:
            {
                world -> show();
                break;
            }
            case 3:
            {
                std::string answer_3;
                int code_3;
                std::cin >> answer_3;
                
                if (answer_3 == "monster")
                {
                    code_3 = 1;
                } else {
                    if (answer_3 == "hero")
                    {
                        code_3 = 2;
                    } else {
                        if (answer_3 == "lake")
                        {
                            code_3 = 3;
                        } else {
                            if (answer_3 == "mountain")
                            {
                                code_3 = 4;
                            } else {
                                if (answer_3 == "forest")
                                {
                                    code_3 = 5;
                                } else {
                                    code_3 = 6;
                                }
                            }
                        }
                    }
                }
                
                std::string not_usable, name_;
                int x_, y_, hp_, size_, depth_, height_;

                
                switch (code_3)
                {
                    case 1:
                    {
                        std::cin >> not_usable >> x_ >> y_ >> not_usable >> hp_;
                        if (world -> occupied(x_, y_, 1) == true) {
                            std::cout << "Sorry, you can't create an object at this place. Try again with new position.\n";
                            break;
                        }
                        objects[++current_object_index] = new  Monster(x_, y_, 1, hp_);
                        world -> add_object(objects[current_object_index]);
                        break;
                    }
                    case 2:
                    {
                        std::cin >> name_ >> not_usable >> x_ >> y_ >> not_usable >> hp_;
                        if (world -> occupied(x_, y_, 1) == true) {
                            std::cout << "Sorry, you can't create an object at this place. Try again with new position.\n";
                            break;
                        }
                        objects[++current_object_index] = new Hero(x_, y_, 1, hp_, name_);
                        world -> add_object (objects[current_object_index]);
                        break;
                    }
                    case 3:
                    {
                        std::cin >> not_usable >> depth_ >> not_usable >> x_ >> y_ >> not_usable >> size_;
                        if (world -> occupied(x_, y_, size_) == true) {
                            std::cout << "Sorry, you can't create an object at this place. Try again with new position.\n";
                            break;
                        }
                        objects[++current_object_index] = new Lake(x_, y_, size_, depth_);
                        world -> add_object (objects[current_object_index]);
                        break;
                    }
                    case 4:
                    {
                        std::cin >> not_usable >> height_ >> not_usable >> x_ >> y_ >> not_usable >> size_;
                        if (world -> occupied(x_, y_, size_) == true) {
                            std::cout << "Sorry, you can't create an object at this place. Try again with new position.\n";
                            break;
                        }
                        objects[++current_object_index] = new Mountain(x_, y_, size_, height_);
                        world -> add_object (objects[current_object_index]);
                        break;
                    }
                    case 5:
                    {
                        std::cin >> not_usable >> x_ >> y_ >> not_usable >> size_;
                        if (world -> occupied(x_, y_, size_) == true) {
                            std::cout << "Sorry, you can't create an object at this place. Try again with new position.\n";
                            break;
                        }
                        objects[++current_object_index] = new Forest(x_, y_, size_);
                        world -> add_object (objects[current_object_index]);
                        break;
                    }
                    default:
                    {
                        break;
                    }
                }
                break;
            }
            case 4:
            {
                std::cout << "Dumping " << current_object_index + 1 << " objects\n";
                if (current_object_index > -1)
                {
                    for (int i = 0; i <= current_object_index; ++i)
                    {
                        std::cout << i + 1 << ". ";
                        objects[i] -> print();
                    }
                }
                break;
            }
            case 5:
            {
                int new_x, new_y, object_index;
                std::cin >> object_index >> new_x >> new_y;
                if (world -> occupied(new_x, new_y, objects[object_index - 1] -> get_size()) == true) {
                    std::cout << "Sorry, you can't move the object at this place. Try again with new position.\n";
                    break;
                }
                world -> move_object(object_index - 1, new_x, new_y);
                break;
            }
            case 6:
            {
                std::cout << "Instructions: here I'll write some words...\n";
                break;
            }
            case 7:
            {
                for (int i = 0; i <= current_object_index; ++i )
                {
                    delete(objects[i]);
                }
                delete(objects);
                delete(world);
                return;
                break;
            }
            default:
            {
                std::cout << "invalid command\n";
                break;
            }
        }
    }
}











