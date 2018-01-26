//
//  Placement.h
//  original_15_puzzles
//
//  Created by Igashov_Ilya on 12.10.16.
//  Copyright (c) 2016 Igashov_Ilya. All rights reserved.
//

#pragma once

#include <iostream>
#include <vector>

const int N = 16;
const int n = 4;
const std::vector<int> finalPlacement = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0};

class CPlacement
{
public:
    CPlacement() {}
    CPlacement( const std::vector<int>& _placement );
    
    int GetF() const { return f; }
    int GetG() const { return g; }
    int GetH() const { return h; }
    const CPlacement* GetParent() const { return parent; }
    int GetBlankPosition() const { return blankPosition; }
    const std::vector<int>& GetPlacement() const { return placement; }
    
    // Имеет смысл использовать Set_F() только после вызова метода SetG, поскольку в противном случае ничего не изменится.
    void SetF() { f = g + h; }
    void SetG( int _g ) { g = _g; }
    void SetParent( const CPlacement* _parent ) { parent = _parent; }
    
    std::vector<CPlacement> FindNeighbours() const;
    bool IsSolution() const;
    
    bool operator<( const CPlacement & other ) const;
    bool operator==( const CPlacement & other ) const;
    
private:
    std::vector<int> placement; // Одномерный массив, в котором записано расположение клеток на доске (можно было бы использовать и двумерный, но не обязательно)
    int f; // Значение функции f = g + h.
    int g; // Длина пути от стартовой вершины до данной (будет обновляться в процессе работы A*).
    int h; // Эвристическая функция.
    const CPlacement* parent; // Родитель вершины в графе ходов.
    int blankPosition; // Положение пустой клетки на доске (номер соответствующей ячейки массива placement).
    
    int countH() const; // Считает эвристику.
    int countPermutations() const; // Считает, сколько клеток стоят не на своих местах.
    int findBlankPosition() const; // Находит пустую клетку.
    void normalize(); // Используется в конструкторе копирования и в методе поиска соседей.
};
