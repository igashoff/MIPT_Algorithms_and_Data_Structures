//
//  main.cpp
//  socket
//
//  Created by Igashov_Ilya on 20.04.16.
//  Copyright (c) 2016 Igashov_Ilya. All rights reserved.
//

#include <iostream>
#include <vector>
#include <queue>

using namespace std;
enum node_color {white, grey, black};

struct socket
{
    size_t number;
    vector<size_t> adjacency_numbers;
    vector<socket *> adjacency_list;
    
    node_color color;
    socket * parent;
    int reached;
    
    bool operator <(const socket & other) const
    {
        return reached >= other.reached;
    }
};

void BFS(vector<socket> & list, size_t my_num);



int main()
{
    vector<socket> list;
    list.clear();
    
    size_t N, my_socket_num, dest_socket_num;
    cout << "КОЛИЧЕСТВО ТИПОВ РОЗЕТОК: ";
    cin >> N;
    getchar();
    
    cout << "ТИП РОЗЕТКИ В ВАШЕЙ СТРАНЕ И ВПУНКТЕ НАЗНАЧЕНИЯ: ";
    cin >> my_socket_num >> dest_socket_num;
    getchar();
    
    cout << "ПЕРЕХОДНИКИ:\n";
    for (size_t i = 1; i < N + 1; ++i)
    {
        socket tmp;
        tmp.adjacency_numbers.clear();
        tmp.adjacency_list.clear();
        tmp.color = white;
        tmp.parent = nullptr;
        tmp.number = i;
        tmp.reached = -1;
        
        string input;
        getline(cin, input);
        
        size_t pos;
        char * str_end;
        while(input.find(' ') != string::npos)
        {
            pos = input.find(' ');
            
            char * str;
            str = new char[pos];
            for (size_t j = 0; j < pos; ++j)
                str[j] = input[j];
            
            tmp.adjacency_numbers.push_back((size_t)atoi(str));
            input = input.substr(pos + 1);
            
            for (size_t j = 0; j < pos; ++j)
                str[j] = '\0';
            
            delete [] str;
        }
        
        str_end = new char[input.size()];
        for (size_t j = 0; j < input.size(); ++j)
            str_end[j] = input[j];
        tmp.adjacency_numbers.push_back((size_t)atoi(str_end));
        delete [] str_end;
        
        list.push_back(tmp);
    }
    
    for (size_t i = 0; i < list.size(); ++i)
        for (size_t k = 0; k < list[i].adjacency_numbers.size(); ++k)
            for (size_t j = 0; j < list.size(); ++j)
                if (list[j].number == list[i].adjacency_numbers[k])
                    list[i].adjacency_list.push_back(&list[j]);
    
    BFS(list, my_socket_num - 1);
    
    priority_queue<socket> my_list;
    socket tmp = list[dest_socket_num - 1];
    my_list.emplace(tmp);
    while (tmp.parent->number != my_socket_num)
    {
        my_list.emplace(*tmp.parent);
        tmp = *tmp.parent;
    }
    
    cout << "КОЛИЧЕСТВО ПЕРЕХОДНИКОВ: " << my_list.size() << endl;
    cout << "ПЕРЕХОДНИКИ:" << endl;
    while (!my_list.empty())
    {
        cout << my_list.top().parent->number << ' ' << my_list.top().number << endl;
        my_list.pop();
    }

    return 0;
}

void BFS(vector<socket> & list, size_t my_num)
{
    queue<socket *> Q;
    list[my_num].color = grey;
    list[my_num].reached = 0;
    Q.push(&list[my_num]);

    while (!Q.empty())
    {
        socket *u = Q.front();
        Q.pop();
        for (auto & v: u->adjacency_list)
        {
            if (v->color == white)
            {
                v->color = grey;
                v->reached = u->reached + 1;
                v->parent = u;
                Q.push(v);
            }
        }
        u->color = black;
    }
}
