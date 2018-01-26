//
//  header.h
//  dota_clone
//
//  Created by Igashov_Ilya on 22.02.16.
//  Copyright (c) 2016 Igashov_Ilya. All rights reserved.
//

#ifndef dota_clone_header_h
#define dota_clone_header_h

#include <iostream>
#include <string>

class GameObject
{
    int x, y;
    int size;
    
public:
    GameObject(int x_, int y_, int size_)
    {
        x = x_;
        y = y_;
        size = size_;
    }
    
    void move(int new_x, int new_y)
    {
        x = new_x;
        y = new_y;
    }
    
    int get_x() const
    {
        return x;
    }
    
    int get_y() const
    {
        return y;
    }
    
    int get_size() const
    {
        return size;
    }
    
    virtual void print() const
    {
        std::cout << "Object: " << "position " << x << ' ' << y << " size " << size << '\n';
    }
    
    virtual char symbol() const
    {
        return '?';
    }
};

class Creature: public GameObject
{
    int hp;
    
public:
    Creature(int x_, int y_, int size_, int hp_): GameObject(x_, y_, size_)
    {
        hp = hp_;
    }
    
    int get_hp() const
    {
        return hp;
    }
    
    virtual void print() const
    {
        std::cout << "Creature: " << "position " << get_x() << ' ' << get_y() << " hp " << hp << '\n';
    }
    
    virtual char symbol() const
    {
        return '?';
    }

};

class Hero: public Creature
{
    std::string name;
    
public:
    Hero(int x_, int y_, int size_, int hp_, std::string name_): Creature(x_, y_, size_, hp_)
    {
        name = name_;
    }
    
    virtual void print() const
    {
        std::cout << "Hero: " << name << " position " << get_x() << ' ' << get_y() << ", hp " << get_hp() << '\n';
    }
    
    virtual char symbol() const
    {
        return name[0];
    }
    
};

class Monster: public Creature
{
public:
    Monster(int x_, int y_, int size_, int hp_) : Creature(x_, y_, size_, hp_)
    {
    }
    
    
    virtual void print() const
    {
        std::cout << "Monster: " << "position " << get_x() << ' ' << get_y() << ", hp " << get_hp() << '\n';
    }
    
    virtual char symbol() const
    {
        return 'M';
    }
};

class Terrain: public GameObject
{
public:
    Terrain(int x_, int y_, int size_) : GameObject(x_, y_, size_)
    {
    }
    
    virtual void print() const
    {
        std::cout << "Terrain: " << "position " << get_x() << ' ' << get_y() << ", size " << get_size() << '\n';
    }
    
    virtual char symbol() const
    {
        return '?';
    }
};

class Lake: public Terrain
{
private:
    int depth;
public:
    Lake(int x_, int y_, int size_, int depth_) : Terrain(x_, y_, size_)
    {
        depth = depth_;
    }
    
    virtual void print() const
    {
        std::cout << "Lake: " << "position " << get_x() << ' ' << get_y() << ", size " << get_size() << ", depth " << depth << '\n';
    }
    
    virtual char symbol() const
    {
        return 'o';
    }
};

class Mountain: public Terrain
{
private:
    int height;
public:
    Mountain(int x_, int y_, int size_, int height_) : Terrain(x_, y_, size_)
    {
        height = height_;
    }
    
    virtual void print() const
    {
        std::cout << "Mountain: " << "position " << get_x() << ' ' << get_y() << ", size " << get_size() << ", height " << height << '\n';
    }
    
    virtual char symbol() const
    {
        return '^';
    }
};

class Forest: public Terrain
{
public:
    Forest(int x_, int y_, int size_) : Terrain(x_, y_, size_)
    {
    }

    virtual void print() const
    {
        std::cout << "Forest: " << "position " << get_x() << ' ' << get_y() << ", size " << get_size() << '\n';
    }
    
    virtual char symbol() const
    {
        return 'F';
    }
    
};

class World
{
private:
    int height;                                                         //map height
    int width;                                                          //map width
    GameObject **objects;                                               //list of objects
    int objects_count;
    char **map;
    void render(int object_index)                                       //puts the object[object_index] on map
    {
        GameObject *new_object = objects[object_index];
        int x_ = new_object -> get_x() - 1;
        int y_ = new_object -> get_y() - 1;
        int size_ = new_object -> get_size();
        char symbol_ = new_object -> symbol();
        for (int i = 0; i < size_; ++i)
        {
            for (int j = 0; j < size_; ++j)
            {
                map[y_ + i][x_ + j] = symbol_;
            }
        }
    }
    
    void clear(int object_index)                                        //clears the previous object's place on map
    {                                                                   //while moving the object[object_index]
        int x_ = objects[object_index] -> get_x() - 1;
        int y_ = objects[object_index] -> get_y() - 1;
        int size_ = objects[object_index] -> get_size();
        for (int i = 0; i < size_; ++i)
        {
            for (int j = 0; j < size_; ++j)
            {
                map[y_ + i][x_ + j] = '.';
            }
        }

    }
    
    World(const World &);
    void operator = (const World &);
    
    public:
    World(int height_, int width_)                                      //constructor creates a map and a list of objects
    {
        height = height_;
        width = width_;
        objects_count = 0;
        objects = new GameObject*[width * height];
        map = new char*[height];
        for (int i = 0; i < height; ++i)
        {
            map[i] = new char[width];
            for (int j = 0; j < width; ++j)
            {
                map[i][j] = '.';
            }
        }
    }
    
    ~World()
    {
        for (int i = 0; i < objects_count; ++i)
        {
            delete(objects[i]);
        }
        delete(objects);
        for (int i = 0; i < height; ++i)
        {
            delete map[i];
        }
        delete(map);
    }
    
    void show() const                                                   //outputs the map
    {
        for(int i = 0; i < height; ++i)
        {
            for (int j = 0; j < width; ++j)
            {
                std::cout << map[i][j];
            }
            std::cout << '\n';
        }
    }
    
    void add_object(GameObject * new_object)                            //creates a new object and puts it on map
    {
        objects[objects_count] = new_object;
        render(objects_count);
        ++objects_count;
    }
    
    void move_object(int object_index, int new_x, int new_y)            //moves the object[object_index]:
    {
        clear(object_index);                                            //1.clears the previous position
        objects[object_index] -> move(new_x, new_y);                    //2.changes object[object_index]'s coordinates
        render(object_index);                                           //3.puts the object[object_index] in the new place
    }                                                                   //  on the map
    
    bool occupied(int x_, int y_, int size_) const                      //checks if this position exists and is not occupied
    {
        --x_;
        --y_;
        for (int i = 0; i < size_; ++i)
        {
            for (int j = 0; j < size_; ++j)
            {
                if ((y_ + i >= height) || (x_ + j >= width) || (y_ + i < 0) || (x_ + i < 0) || (map[y_ + i][x_ + j] != '.')) return true;
            }
        }
        return false;
    }
    
};

#endif
