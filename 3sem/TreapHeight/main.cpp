//
//  main.cpp
//  TreapHeight
//
//  Created by Igashov_Ilya on 12.12.16.
//  Copyright (c) 2016 Igashov_Ilya. All rights reserved.
//

//  Дано число N < 10^6 и последовательность пар целых чисел из [-231, 231] длиной N.
//  Построить декартово дерево из N узлов, характеризующихся парами чисел (Xi, Yi).
//  Каждая пара чисел (Xi, Yi) определяет ключ Xi и приоритет Yi в декартовом дереве.
//  Добавление узла в декартово дерево выполняйте второй версией алгоритма, рассказанного на лекции:
//  При добавлении узла (x, y) выполняйте спуск по ключу до узла P с меньшим приоритетом.
//  Затем разбейте найденное поддерево по ключу x так, чтобы в первом поддереве все ключи меньше x,
//  а во втором больше или равны x. Получившиеся два дерева сделайте дочерними для нового узла (x, y).
//  Новый узел вставьте на место узла P.

//  Построить также наивное дерево поиска по ключам Xi. Равные ключи добавляйте в правое поддерево.

//  Вычислить разницу глубин наивного дерева поиска и декартового дерева. Разница может быть отрицательна.


#include <iostream>
#include <vector>

using namespace std;

//  Структура узла декартова дерева: x - ключ, y - приоритет, left, right - указатели на потомков.
struct CNode
{
    int x;
    int y;
    CNode* left;
    CNode* right;
    
    CNode(): x( 0 ), y( 0 ), left( nullptr ), right( nullptr ) {}
    CNode( int _x, int _y ): x( _x ), y( _y ), left( nullptr ), right( nullptr ) {}
};

//  Функция разбиения декартова дерева treap на два дерева по ключу key.
pair<CNode*, CNode*> split( CNode* treap, int key );
//  Функция слияния двух декартовых деревьев treap1 и treap2 (все ключи в treap1 меньше ключей в treap2).
CNode* merge( CNode* treap1, CNode* treap2 );
//  Функция, которая вставляет в декартово дерево treap узел node.
void insertIntoTreap( CNode*& treap, CNode* node );
//  Функция, которая вставляет в наивное дерево binaryTree узел node.
void insertIntoBinaryTree( CNode*& binaryTree, CNode* node );
//  Функция, окторая считает высоту дерева tree.
int countHeight( CNode* tree );

int main()
{
    // Количество узлов дерева.
    int N = 0;
    cin >> N;
    
    // Вектор узлов дерева.
    vector<CNode> nodes( 0 );
    for( int i = 0; i < N; ++i ) {
        int x, y;
        cin >> x >> y;
        nodes.emplace_back( x, y );
    }
    
    // treap - указатель на корень декартова дерева. Изначально указывает на первый элемент вектора nodes,
    // но в процессе добавления элементов корень может поменяться. Поэтому в функцию insert указательна корень
    // передается по ссылке.
    CNode* treap = &nodes[0];
    // Добавляем все узлы в дерево.
    for( int i = 1; i < N; ++i ) {
        insertIntoTreap( treap, &nodes[i] );
    }
    
    // Считаем высоту декартова дерева.
    int treapHeight = countHeight( treap );
    
    // Обнуляем все указатели в узлах, чтобы построить на них наивное дерево поиска по ключу x.
    for( int i = 0; i < N; ++i ) {
        nodes[i].left = nullptr;
        nodes[i].right = nullptr;
    }
    // binaryTree - указатель на корень дерева. Изначально указывает на первый элемент вектора nodes, и меняться не будет.
    CNode* binaryTree = &nodes[0];
    // Добавляем все узлы в дерево.
    for( int i = 1; i < N; ++i ) {
        insertIntoBinaryTree( binaryTree, &nodes[i] );
    }
    
    // Считаем высоту дерева.
    int binaryTreeHeight = countHeight( binaryTree );
    
    // Выводим разность высот.
    cout << binaryTreeHeight - treapHeight;
    
    return 0;
}

//  Если дерево пусто, то резудьтатом будет пара пустых деревьев.
//  Рекурсиво выполняем следующее:
//  если ключ key больше ключа корня текущего поддерева t, то разбиваем правое поддерево этого поддерева по ключу
//  и правым поддеревом поддерева t становится первое дерево из результата разбиения правого поддерева дерева t.
//  Иначе выполняем симметричные операции с левым поддеревом.
pair<CNode*, CNode*> split( CNode* treap, int key )
{
    if( treap == nullptr ) {
        return make_pair( nullptr, nullptr );
    }
    
    if( key > treap->x ) {
        pair<CNode*, CNode*> splittedSubTreap = split( treap->right, key );
        treap->right = splittedSubTreap.first;
        return make_pair( treap, splittedSubTreap.second );
    }
    else {
        pair<CNode*, CNode*> splittedSubTreap = split( treap->left, key );
        treap->left = splittedSubTreap.second;
        return make_pair( splittedSubTreap.first, treap );
    }
}

//  Если какое-то из деревьев пусто, то возвращаем другое.
//  Если оба непусты, то надо решить, что будет корнем. Из корней деревьев treap1 и treap2 выбираем больши по приоритету:
//  он станет корнем нашего дерева. Если у treap1 корень больше, то левым поддеревом нашего дерева станет
//  левое поддерево treap1, а правым - слитые правое поддерево treap1 и дерево treap2.
//  Иначе выполняем симметричные операции с левым поддеревом.
CNode* merge( CNode* treap1, CNode* treap2 )
{
    if( treap2 == nullptr ) {
        return treap1;
    }
    if( treap1 == nullptr ) {
        return treap2;
    }
    
    if( treap1->y > treap2->y ) {
        treap1->right = merge( treap1->right, treap2 );
        return treap1;
    }
    else {
        treap2->left = merge( treap1, treap2->left );
        return treap2;
    }
}

//  При добавлении узла (x, y) выполняем спуск по ключу до узла P с меньшим приоритетом.
//  Затем разбиваем найденное поддерево по ключу x так, чтобы в первом поддереве все ключи меньше x,
//  а во втором больше или равны x. Получившиеся два дерева сделаем дочерними для нового узла (x, y).
//  Новый узел вставляем на место узла P.
//  Указательна корень передается по ссылке, поттому что корень может измениться.
void insertIntoTreap( CNode*& treap, CNode* node )
{
    CNode* parent = nullptr;
    CNode* current = treap;
    while( current != nullptr && current->y >= node->y ) {
        if( node->x < current->x ) {
            parent = current;
            current = current->left;
        }
        else {
            parent = current;
            current = current->right;
        }
    }
    pair<CNode*, CNode*> splittedSubTreap = split( current, node->x );
    node->left = splittedSubTreap.first;
    node->right = splittedSubTreap.second;
    if( parent != nullptr ) {
        if( node->x < parent->x ) {
            parent->left = node;
        }
        else {
            parent->right = node;
        }
    } else {
        treap = node;
    }
}

//  Вставка в наивное дерево поиска.
//  Спускаемся по дереву по ключу node->x до самого низа и вставляем туда узел.
void insertIntoBinaryTree( CNode*& binaryTree, CNode* node )
{
    CNode* parent = nullptr;
    CNode* current = binaryTree;
    while( current != nullptr ) {
        if( node->x < current->x ) {
            parent = current;
            current = current->left;
        }
        else {
            parent = current;
            current = current->right;
        }
    }
    if( node->x < parent->x ) {
        parent->left = node;
    }
    else {
        parent->right = node;
    }
}

//  Будем поддерживать вектор указателей ptrs.
//  Пусть мы находимся на i-м уровне и текущая высота равна i. Тогда ptrs будет содержать ненулевые указатели на все узлы,
//  которые находятся на уровне i + 1. Будем так спускаться, пока вектор ptrs не станет пустым.
//  По ходу спуска увеличиваем высоту height.
int countHeight( CNode* tree )
{
    if( tree == nullptr ) {
        return 0;
    }
    
    int height = 1;
    vector<CNode*> ptrs( 0 );
    if( tree->left != nullptr ) {
        ptrs.push_back( tree->left );
    }
    if( tree->right != nullptr ) {
        ptrs.push_back( tree->right );
    }
    while( !ptrs.empty() ) {
        ++height;
        vector<CNode*> temp( 0 );
        for( CNode* ptr: ptrs ) {
            if( ptr->left != nullptr ) {
                temp.push_back( ptr->left );
            }
            if( ptr->right != nullptr ) {
                temp.push_back( ptr->right );
            }
        }
        ptrs = temp;
    }
    return height;
}

