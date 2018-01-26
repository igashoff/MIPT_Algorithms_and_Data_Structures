//
//  main.cpp
//  todo_list
//
//  Created by Igashov_Ilya on 17.04.16.
//  Copyright (c) 2016 Igashov_Ilya. All rights reserved.
//

#include <iostream>
#include <vector>
#include <queue>
#include <set>

using namespace std;
static size_t time_;
enum Color {white, grey, black};

struct task
{
    size_t number;
    string description;
    vector<size_t> adjacency_numbers;                       //Номера задач, которые нужно выполнить до текущей
                                                            //Поля для DFS
    vector<task *> adjacency_list;
    Color color;
    task *parent;
    size_t begin;
    size_t end;
    
    priority_queue<task> *list;
    
    bool operator <(const task & other) const
    {
        return end >= other.end;
    }
    
    void execute()
    {
        if (list->top().description == description)
            list->pop();
        else
            cout << "You have to execute some other tasks before" << endl;
        
    }
    
    vector<task> dependancies()
    {
        priority_queue<task> tmp(*list);
        vector<task> temp;
        for (int i = 0; i < tmp.size(); ++i)
        {
            temp.push_back(tmp.top());
            tmp.pop();
        }
        
        int count = 0;
        for (const auto & i: temp)
        {
            if (i.description == description)
                break;
            ++count;
        }
        
        vector<task> result;
        copy(temp.begin(), temp.begin() + count, back_inserter(result));
        
        return result;
    }
};

void DFS(vector<task> & list);
void DFS_VISIT(vector<task> & list, task & u);

int main()
{
    vector<task> list;
    list.clear();
    
    size_t N;                                               //На вход подается число задач
    cout << "КОЛИЧЕСТВО ЗАДАЧ: ";
    cin >> N;
    getchar();
    
    cout << "ЗАДАЧИ:\n";                                    //В каждой следующей строчке - новая задача
    for (size_t i = 1; i < N + 1; ++i)                      //Вводится в формате: описание и номера задач, от которых она
    {                                                       //Зависит
        task tmp;
        tmp.adjacency_numbers.clear();
        tmp.adjacency_list.clear();                         //Устанавливаем дефолтные значения полей.
        tmp.color = white;
        tmp.parent = nullptr;
        tmp.number = i;
        
        cin >> tmp.description;                             //Вводим описание.
        
        string input;
        getline(cin, input);
        
        size_t pos;                                         //Поскольку мы не знаем, сколько пользователь введет номеров,
        char * str_end;                                     //будем считывать их как единую строку, а потом парсить.
        while(input.find(' ') != string::npos)              //Пока пробелы в нашей строке еще есть,
        {
            pos = input.find(' ');                          //находим ближайший пробел,
            
            char * str;
            str = new char[pos];                            //заводим С-строку и копируем в нее символы из input до пробела,
            for (size_t j = 0; j < pos; ++j)
                str[j] = input[j];
                                                            //записываем в список смежности номер задачи, который получился из С-строки путем преобразования в число,
            tmp.adjacency_numbers.push_back((size_t)atoi(str));
            input = input.substr(pos + 1);                  //отрезаем от input все до первого пробела,
            
            for (size_t j = 0; j < pos; ++j)                //затираем С-строку,
                str[j] = '\0';
            
            delete [] str;                                  //удаляем ее.
        }
        
        str_end = new char[input.size()];                   //Когда пробелов не осталось, нужно считать последний номер
        for (size_t j = 0; j < input.size(); ++j)           //Аналогично
            str_end[j] = input[j];
        tmp.adjacency_numbers.push_back((size_t)atoi(str_end));
        delete [] str_end;
        
        tmp.adjacency_numbers.erase(tmp.adjacency_numbers.begin());
        list.push_back(tmp);
    }
    
    for (size_t i = 0; i < list.size(); ++i)                //Преобразуем список смежности номеров в список смежности
        for (size_t k = 0; k < list[i].adjacency_numbers.size(); ++k)           //указателей
            for (size_t j = 0; j < list.size(); ++j)
                if (list[j].number == list[i].adjacency_numbers[k])
                    list[i].adjacency_list.push_back(&list[j]);
    
    DFS(list);                                              //Выполняем поиск в глубину в дереве задач
    
    priority_queue<task> my_list;                           //Создаем очередь с приоритетом из задач
    for (auto i: list)                                      //(сравниваем поля end - время окончания работы
    {
        i.list = &my_list;
        my_list.emplace(i);                                 // с этим листом в DFS)
    }
    
    while (!my_list.empty())                                //Выводим все задачи в порядке выполнения
    {
        cout << my_list.top().description << endl;
        my_list.pop();
    }
    
    return 0;

}

void DFS(vector<task> & list)
{
    time_ = 0;
    for (size_t i = 0; i < list.size(); ++i)
        if (list[i].color == white)
            DFS_VISIT(list, list[i]);
}

void DFS_VISIT(vector<task> & list, task & u)
{
    ++time_;
    u.begin = time_;
    u.color = grey;
    for (size_t i = 0; i < u.adjacency_list.size(); ++i)
        if (u.adjacency_list[i]->color == white)
        {
            u.adjacency_list[i]->parent = &u;
            DFS_VISIT(list, *u.adjacency_list[i]);
        }
    u.color = black;
    ++time_;
    u.end = time_;
}
