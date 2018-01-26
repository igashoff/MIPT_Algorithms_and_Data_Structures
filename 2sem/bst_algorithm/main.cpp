//
//  main.cpp
//  bst_algorithm
//
//  Created by Igashov_Ilya on 15.05.16.
//  Copyright (c) 2016 Igashov_Ilya. All rights reserved.
//

#include <iostream>
using namespace std;

template <typename T> class tree;

template <typename T>
class node
{
    friend tree<T>;
    T data;
    shared_ptr<node> left;
    shared_ptr<node> right;
    shared_ptr<node> parent;
    
public:
    
    node(): left(nullptr), right(nullptr), parent(nullptr) {}
    
    node(const T & data_): data(data_), left(nullptr), right(nullptr), parent(nullptr) {}
    
    const T & get_data() const
    {
        return data;
    }

};

template <typename T>
class tree
{
    shared_ptr<node<T>> root;
    
public:
    tree();
    shared_ptr<node<T>> find(const shared_ptr<node<T>> & root_, const T & node_) const;
    T get_max(const shared_ptr<node<T>> & root_) const;
    T get_min(const shared_ptr<node<T>> & root_) const;
    T predcessor(const shared_ptr<node<T>> & root_, const shared_ptr<node<T>> & x) const;
    T successor(const shared_ptr<node<T>> & root_, const shared_ptr<node<T>> & x) const;
    
    void insert_node(const T & new_node);
    void delete_node(shared_ptr<node<T>> & del_node);
    void inorder_walk(shared_ptr<node<T>> & root_) const;
    shared_ptr<node<T>> & get_root();
    
};

template <typename T>
tree<T>::tree(): root(nullptr) {}

template <typename T>
shared_ptr<node<T>> tree<T>::find(const shared_ptr<node<T>> & root_, const T & node_) const
{
    auto result = root_;
    while (result != nullptr && node_ != result->data)
    {
        result = (node_ < result->data) ? result->left: result->right;
    }
    return result;
}

template <typename T>
T tree<T>::get_max(const shared_ptr<node<T>> & root_) const
{
    auto ptr = root_;
    while (ptr->right != nullptr)
        ptr = ptr->right;
    return ptr->data;
}

template <typename T>
T tree<T>::get_min(const shared_ptr<node<T>> & root_) const
{
    auto ptr = root_;
    while (ptr->left != nullptr)
        ptr = ptr->left;
    return ptr->data;
}


template <typename T>
void tree<T>::insert_node(const T & new_node)
{
    shared_ptr<node<T>> n(new node<T>);
    n->data = new_node;
    shared_ptr<node<T>> ptr1 = root;
    shared_ptr<node<T>> ptr2 = nullptr;
    
    while (ptr1)
    {
        ptr2 = ptr1;
        ptr1 = (new_node < ptr1->data) ? ptr1->left : ptr1->right;
    }
    
    if (!ptr2)
        root = n;
    else
    {
        n->parent = ptr2;
        if (n->data < n->parent->data)
            n->parent->left = n;
        else
            n->parent->right = n;
    }
}

template <typename T>
void tree<T>::inorder_walk(shared_ptr<node<T>> & root_) const
{
    if (root_ != nullptr)
    {
        inorder_walk(root_->left);
        cout << root_->data << ' ';
        inorder_walk(root_->right);
    }
}

template <typename T>
shared_ptr<node<T>> & tree<T>::get_root()
{
    return root;
}

template <typename T>
T tree<T>::predcessor(const shared_ptr<node<T>> & root_, const shared_ptr<node<T>> & x) const
{
    auto x_ptr = x;
    if (x_ptr != nullptr)
    {
        if (x_ptr->left != nullptr)
            return get_max(x_ptr->left);
        auto y = x_ptr->parent;
        while (y != nullptr && x_ptr == y->left)
        {
            x_ptr = y;
            y = y->parent;
        }
        if (y != nullptr)
            return y->data;
        else return get_max(root);
    }
    else return get_max(root);
}


template <typename T>
T tree<T>::successor(const shared_ptr<node<T>> & root_, const shared_ptr<node<T>> & x) const
{
    auto x_ptr = x;
    if (x_ptr != nullptr)
    {
        if (x_ptr->right != nullptr)
            return get_min(x_ptr->right);
        auto y = x_ptr->parent;
        while (y != nullptr && x_ptr == y->right)
        {
            x_ptr = y;
            y = y->parent;
        }
        return y->data;
    }
    else return get_min(root);
}

int main()
{
    tree<int> t;
    t.insert_node(8);
    t.insert_node(3);
    t.insert_node(10);
    t.insert_node(1);
    t.insert_node(6);
    t.insert_node(4);
    t.insert_node(7);
    t.insert_node(14);
    t.insert_node(13);
    t.inorder_walk(t.get_root());
    cout << endl;
    cout << t.predcessor(t.get_root(), t.find(t.get_root(), 4)) << endl << t.get_max(t.get_root()) << endl << t.get_min(t.get_root()) ;
    return 0;
}


