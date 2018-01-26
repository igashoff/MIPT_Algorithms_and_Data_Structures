//
//  main.cpp
//  Trade Arbitrage
//
//  Created by Igashov_Ilya on 09.09.16.
//  Copyright (c) 2016 Igashov_Ilya. All rights reserved.
//


// «Trade Arbitrage» Необходимо написать торгового советника для поиска арбитража.
// Определение
// Арбитраж - это торговля по цепочке различных валют в надежде заработать на небольших различиях в коэффициентах.
// Например, есть следующие курсы валют (на 03.05.2015):
// GBP/USD: 0.67
// RUB/GBP: 78.66
// USD/RUB: 0.02
// Имея 1$ и совершив цикл USD->GBP->RUB->USD, получим 1.054$. Таким образом заработав 5.4%.
// Формат входных данных.
// Первая строка содержит число N – количество возможных валют (размер таблицы котировок)
// Далее следует построчное представление таблицы. Диагональные элементы (i, i) пропущены
// (подразумевается, что курс валюты к себе же 1.0).
// В элементе таблицы (i, j) содержится обменный курс i->j.
// Если обмен в данном направлении не производится, то -1.
// Формат выходных данных.
// Выводим Yes, если арбитраж есть, и No, иначе.


#include <iostream>
#include <vector>
#include <math.h>
#include <limits.h>
#include <assert.h>

using namespace std;

// Функция, реализующая алгоритм Беллмана-Форда (ищет положительные циклы в шрафе, заданном матрицей смежности matrix)
bool BellmanFord( const vector<vector<double>>& matrix );

int main()
{
    // Количество возможных валют
    int N = 0;
    cin >> N;
    assert( N != 0 );
    
    // Таблица курсов валют в логарифмическом представлении
    // (логарифмы нужны для привычной реализации алгоритма Беллмана-Форда)
    vector<vector<double>> matrix( N );
    
    for( int i = 0; i < N; ++i ) {
        for( int j = 0; j < N; ++j ) {
            // Диагональные элементы автоматически заполняются нулями
            if( i == j ) {
                matrix[i].push_back( 0 );
                continue;
            }
            
            // Считываем очередной курс
            double quotation = 0;
            cin >> quotation;
            
            // Если обмена нет, то автоматически заполняется минимальная котировка (такой вариант подходит для наших целей),
            // а если обмен существует, то заполняем обычно
            if( quotation == -1 ) {
                matrix[i].push_back( LLONG_MIN );
            } else {
                matrix[i].push_back( log( quotation ) );
            }
        }
    }
    
    // Ищем положительный цикл
    if( BellmanFord( matrix ) == true ) {
        cout << "NO" << endl;
    } else {
        cout << "YES" << endl;
    }
    
    return 0;
}

bool BellmanFord( const vector<vector<double>>& matrix )
{
    // Вектор "расстояний" от начальной вершины до всех остальных
    // В начале все расстояния равны -∞, для начальной вершины расстояние равно 0
    vector<double> distance( matrix.size(), LLONG_MIN );
    distance[0] = 0;
    
    // Итерируемся N-1 = |V|-1 раз
    for( int i = 0; i < matrix.size() - 1; ++i ) {
        bool relaxed = false;
        
        // Внутри каждой итерации релаксируем все ребра графа
        for( int j = 0; j < matrix.size(); ++j ) {
            for( int k = 0; k < matrix.size(); ++k ) {
                if( distance[k] < distance[j] + matrix[j][k] ) {
                    distance[k] = distance[j] + matrix[j][k];
                    relaxed = true;
                }
            }
        }
        
        // Если на очередном шаге не релаксировалось ни одного ребра, алгоритм заканчивает работу:
        // положительных циклов нет
        if( !relaxed ) {
            break;
        }
    }
    
    // Проверка на наличие неотрелаксированных ребер
    // Если такие есть после всех N-1 итераций, значит в графе есть положительный цикл
    for( int j = 0; j < matrix.size(); ++j ) {
        for( int k = 0; k < matrix.size(); ++k ) {
            if( distance[k] < distance[j] + matrix[j][k] ) {
                return false;
            }
        }
    }
    
    return true;
}

// Пример:
// 4
// 32.1  1.50 78.66
// 0.03        0.04  2.43
// 0.67 21.22       51.89
// 0.01    -1  0.02

// -YES
