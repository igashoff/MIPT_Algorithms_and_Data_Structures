//
//  b-tree.h
//  B-tree
//
//  Created by Igashov_Ilya on 21.05.16.
//  Copyright (c) 2016 Igashov_Ilya. All rights reserved.
//

#ifndef B_tree_b_tree_h
#define B_tree_b_tree_h

#include <iostream>
#include <memory>

#include <iostream>
#include <vector>
#include <initializer_list>

using namespace std;

template <typename K, typename V>
struct key
{
    K k;
    V v;
    bool operator <(const key & other) const
    {
        return k < other.k;
    }
    
    bool operator <(const K & other) const
    {
        return k < other;
    }
};

key<int, int> make_key(int x, int y)
{
    key<int, int> tmp;
    tmp.k = x;
    tmp.v = y;
    return tmp;
}

template <typename K, typename V>
struct node
{
    bool leaf;
    int n;
    vector<key<K, V>> keys;
    vector<shared_ptr<node>> children;
};



template <typename K, typename V>
class btree
{
    typedef shared_ptr<node<K,V>> ptr;
    
    static const int t = 5;
    ptr root;
    int Size;
    
public:
    btree(): root(nullptr), Size(0) {}
    
    btree(initializer_list<key<K, V>> l): btree(), Size(l.size())
    {
        for (const auto &i : l)
            insert(i);
    }
    
    void split_child(const ptr & x, int i)
    {
        ++i;
        ptr z(new node<K, V>);                                          //новый узел на высоте полного
        ptr y = x->children[i - 1];                                     //полный узел, который мы разобьем
        z->leaf = y->leaf;                                              //они на одной высоте, значит они оба или листы, или нет
        z->n = t - 1;
        
        for (int j = 1; j <= t - 1; ++j)
            z->keys.push_back(y->keys[t + j - 1]);                      //покопировали вторую половину ключей из y в z
        for (int j = 1; j <= t - 1; ++j)
            y->keys.pop_back();
        
        if (!y->leaf)
        {
            for (int j = 1; j <= t; ++j)                                //если есть потомки, то и их покопировали
                z->children.push_back(y->children[t + j - 1]);
            for (int j = 1; j <= t; ++j)
                y->children.pop_back();
        }
        
        y->n = t - 1;                                                   //обновили кол-во ключей в у
        
        x->children.push_back(x->children[x->n]);                       //сместили вторую половину указателей на потомков в х
        for (int j = x->n; j >= i + 1; --j)
            x->children[j] = x->children[j - 1];
        
        x->children[i] = z;                                             //добавили в х указатель на нового потомка z
        
        ++x->n;
        if (!x->keys.empty())
        {
            x->keys.push_back(x->keys[x->n - 1]);                       //сместили вторую половину ключей
            for (int j = x->n - 1; j >= i; --j)
                x->keys[j] = x->keys[j - 1];
            
            x->keys[i - 1] = y->keys[t - 1];                            //добавили новый ключ, который до этого был медианой в y
        }
        else
            x->keys.push_back(y->keys[t - 1]);
        y->keys.pop_back();
    }
    
    void insert(const key<K, V> & k)
    {
        if (root == nullptr)
        {
            ptr tmp(new node<K, V>);
            root = tmp;
            root->keys.push_back(k);
            root->n = 1;
            root->leaf = true;
        }
        
        else
        {
            ptr r = root;
            if (r->n == 2 * t - 1)                                      //если корень полный
            {
                ptr s(new node<K, V>);                                        //тогда делаем новый корень (только так и увеличивается высота)
                root = s;
                s->leaf = false;
                s->n = 0;                                               //у нового корня ни одного ключа
                s->children.push_back(r);                               //зато у него есть потомок: старый корень
                split_child(s, 0);                                      //разделяем этот полный узел (бывший корень)
                insert_nonfull(s, k);                                   //вставляем элемент в дерево с гарантированно неполным корнем
            }
            
            else insert_nonfull(r, k);                                      //корень неполный => применяем функцию вставки в дерево с ним
        }
        
        ++Size;
    }
    
    void insert_nonfull(const ptr & x, const key<K, V> & k)
    {
        if (x->leaf)                                                    //если х - лист, то мы просто добавляем в него еще один ключ
        {
            x->keys.push_back(x->keys[x->n - 1]);
            ++x->n;
            int i = x->n - 1;
            for (; i >= 1 && k < x->keys[i - 1]; --i)
                x->keys[i] = x->keys[i - 1];
            x->keys[i] = k;
        }
        
        else                                                            //иначе ищем потомка, к которому нужно перейти для добавления k
        {
            int i = x->n;
            for (; i >= 1 && k < x->keys[i - 1]; --i);
            ++i;
            if (x->children[i - 1]->n == 2 * t - 1)                     //если этот потомок заполнен
            {
                split_child(x, i - 1);                                  //то разделяем его
                if (x->keys[i - 1] < k)                                 //проверяем, что мы идем все еще по правильному пути
                    ++i;                                                //если что, корректируем путь
            }
            
            insert_nonfull(x->children[i - 1], k);                      //рекурсивно вызываемся от нужного потомка
        }
    }
    
    void inorder_walk(const ptr & x) const
    {
        if (!x->leaf)
        {
            for (int i = 0; i < x->n; ++i)
            {
                inorder_walk(x->children[i]);
                cout << x->keys[i].k << '(' << x->keys[i].v << ')' << ' ';
            }
            inorder_walk(x->children[x->n]);
        }
        
        else
            for (int i = 0; i < x->n; ++i)
                cout << x->keys[i].k << '(' << x->keys[i].v << ')' << ' ';
    }
    
    const ptr & get_root() const
    {
        return root;
    }
    
    key<K,V> * search(const ptr & root_, const K & key) const
    {
        shared_ptr<key<K,V>> temp;                                          //!!!!!ЗДЕСЬ!!!!!!
        if (root_->leaf)                                                    //если этот узел - лист, то рекурсивно вызываться некуда
        {
            for (int i = 0; i < root_->n; ++i)                              //проходим по всем ключам этого узла
                if (root_->keys[i].k == key)                                //если нашли, то возвращаем указатель (не знаю, как вернуть shared_ptr)
                    return &root_->keys[i];
            return nullptr;
        }
        else                                                                //если узел не лист, то делаем то же самое
        {
            //shared_ptr<key<typename K, typename V>> pt;
            int i;
            for (i = 0; i < root_->n && root->keys[i] < key; ++i);
            if (i == root_->n)
                return search(root_->children[i], key);                     //но если не находим, то вызываемся рекурсивно от нужного потомка
            else
            {
                if (root_->keys[i].k == key)
                    return &root_->keys[i];
                return search(root_->children[i], key);
            }
        }
    }
    
    key<K,V> *  min(const ptr & root_) const
    {
        auto ptr = root_;
        while (!ptr->leaf)
            ptr = ptr->children[0];
        return &ptr->keys[0];
    }
    
    key<K,V> * max(const ptr & root_) const
    {
        auto ptr = root_;
        while (!ptr->leaf)
            ptr = ptr->children[ptr->n];
        return &ptr->keys[ptr->n - 1];
    }
    
    key<K,V> * predcessor(const ptr & root_, const K & key) const
    {
        if (!root_->leaf)
        {
            int i;
            for (i = 0; i < root_->n && root_->keys[i].k < key; ++i);

            if (root_->children[i]->keys[0].k >= key)
                return &root_->keys[i - 1];
            else return predcessor(root_->children[i], key);
        }
        
        else
        {
            int i;
            for (i = 0; i < root_->n && root_->keys[i].k < key; ++i);
            return (i == 0)? &root_->keys[i] : &root_->keys[i - 1];
        }
    }
    
    key<K,V> * successor(const ptr & root_, const K & key) const
    {
        if (!root_->leaf)
        {
            int i;
            for (i = 0; i < root_->n && root_->keys[i].k <= key; ++i);
            
            if (root_->children[i]->keys[root_->children[i]->n - 1].k <= key)
                return &root_->keys[i];
            else return successor(root_->children[i], key);
        }
        
        else
        {
            int i;
            for (i = 0; i < root_->n && root_->keys[i].k <= key; ++i);
            return (i == root_->n)? &root->keys[i - 1]: &root_->keys[i];
        }
    }
};


template <typename K, typename V>
class bmap
{
protected:
    
    btree<K, V> tree;
    int Size;
    
public:
    
    bmap();
    
    bool empty() const;
    int size() const;
    
    V & operator [](const K & key);
    V & at(const K & key);
    const V & at(const K & key) const;
    
    class iterator
    {
        key<K, V> * obj;
        bmap my_map;
    public:
        typedef key<K, V> value_type;
        typedef key<K, V> * pointer;
        typedef key<K, V>& reference;
        typedef bidirectional_iterator_tag iterator_category;
        
        iterator(bmap<K, V> & my_map_, key<K, V> * obj_);
        iterator & operator ++();
        iterator & operator --();
        iterator & operator ++(int);
        iterator & operator --(int);
        bool operator ==(const iterator & right_operand) const;
        bool operator !=(const iterator & right_operand) const;
        value_type & operator *();
    };
    
    iterator begin();
    iterator end();
    iterator insert(const key<K, V> & k);
};

template <typename K, typename V>
bmap<K, V>::bmap(): Size(0) {}

template <typename K, typename V>
bool bmap<K, V>::empty() const
{
    return Size == 0;
}

template <typename K, typename V>
int bmap<K, V>::size() const
{
    return Size;
}

template <typename K, typename V>
V & bmap<K, V>::operator [](const K & key)
{
    if (Size == 0)
    {
        ++Size;
        V val;
        tree.insert(make_key(key, val));
        return tree.search(tree.get_root(), key)->v;
    }
    
    auto ptr = tree.search(tree.get_root(), key);
    if (ptr != nullptr)
    {
        return ptr->v;
    }
    else
    {
        ++Size;
        V val;
        tree.insert(make_key(key, val));
        return tree.search(tree.get_root(), key)->v;
    }
}

template <typename K, typename V>
V & bmap<K, V>::at(const K & key)
{
    auto ptr = tree.search(tree.get_root(), key);
    if (ptr != nullptr)
    {
        return ptr->v;
    }
    else
    {
        throw out_of_range("No such element");
    }
}

template <typename K, typename V>
const V & bmap<K, V>::at(const K & key) const
{
    auto ptr = tree.search(tree.get_root(), key);
    if (ptr != nullptr)
    {
        return ptr->v;
    }
    else
    {
        throw out_of_range("No such element");
    }
}

template <typename K, typename V>
bmap<K,V>::iterator::iterator(bmap & my_map_, key<K, V> * obj_): my_map(my_map_), obj(obj_) {}

template <typename K, typename V>
typename bmap<K,V>::iterator & bmap<K,V>::iterator::operator ++()
{
    obj = my_map.tree.successor(my_map.tree.get_root(), obj->k);
    return *this;
}

template <typename K, typename V>
typename bmap<K,V>::iterator & bmap<K, V>::iterator::operator --()
{
    obj = my_map.tree.predcessor(my_map.tree.get_root(), obj->k);
    return *this;
}

template <typename K, typename V>
typename bmap<K,V>::iterator & bmap<K,V>::iterator::operator ++(int)
{
    obj = my_map.tree.successor(my_map.tree.get_root(), obj->k);
    return *this;
}

template <typename K, typename V>
typename bmap<K,V>::iterator & bmap<K, V>::iterator::operator --(int)
{
    obj = my_map.tree.predcessor(my_map.tree.get_root(), obj->k);
    return *this;
}


template <typename K, typename V>
bool bmap<K,V>::iterator::operator ==(const bmap::iterator & right_operand) const
{
    if (&my_map == &right_operand.my_map && obj == right_operand.obj) return true;
    else return false;
}

template <typename K, typename V>
bool bmap<K,V>::iterator::operator !=(const bmap::iterator & right_operand) const
{
    if (&my_map != &right_operand.my_map || obj != right_operand.obj) return true;
    else return false;
}

template <typename K, typename V>
typename bmap<K,V>::iterator::value_type & bmap<K,V>::iterator::operator *()
{
    return *obj;
}

template <typename K, typename V>
typename bmap<K,V>::iterator bmap<K,V>::begin()
{
    //shared_ptr<bmap<K,V>> tmp(this);
    bmap::iterator myiterator(*this, tree.min(tree.get_root()));
    return myiterator;
}

template <typename K, typename V>
typename bmap<K,V>::iterator bmap<K,V>::end()
{
    //shared_ptr<bmap<K,V>> tmp(this);
    //bmap::iterator myiterator(*this, nullptr);  //что сюда положить???
    //return myiterator;
    bmap::iterator myiterator(*this, tree.max(tree.get_root()));
    return ++myiterator;
}

template <typename K, typename V>
typename bmap<K,V>::iterator bmap<K,V>::insert(const key<K, V> & k)
{
    ++Size;
    tree.insert(k);
    //shared_ptr<bmap<K,V>> tmp(this);
    iterator myiterator(*this, tree.search(tree.get_root(), k.k));
    return myiterator;
}



#endif
