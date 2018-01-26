//
//  main.cpp
//  informatics
//
//  Created by Igashov_Ilya on 16.05.16.
//  Copyright (c) 2016 Igashov_Ilya. All rights reserved.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <set>

using namespace std;
enum command {SOLVED, STUD_STAT, STUDS_BY_TASKS, STUDS_BY_BALLS, STUDS_MORE_TASKS, STUDS_MORE_BALLS, TASKS_BY_SOLUTIONS, EXIT, INVALID};

struct student
{
    string name;
    size_t solved = 0;
    size_t balls = 0;
};

struct task
{
    size_t number;
    size_t cost;
    size_t count_solvings = 0;
};

struct f_arg
{
    string name;
    size_t point;
    
    bool operator <(const f_arg & other)
    {
        if (point == other.point)
            return name < other.name;
        return point < other.point;
    }
};

void input(size_t & N, vector<task> & tasks);
void solved(map<command, map<f_arg, student>> & students, vector<task> & tasks);
void stud_stat(const map<command, map<f_arg, student>> & students);
void studs_by_tasks(const map<command, map<f_arg, student>> & students);
void studs_by_balls(const map<command, map<f_arg, student>> & students);
void studs_more_tasks(const map<command, map<f_arg, student>> & students);
void studs_more_balls(const map<command, map<f_arg, student>> & students);
void tasks_by_solutions(const vector<task> & tasks);


int main()
{
    size_t N;
    vector<task> tasks;
    input(N, tasks);
    
    
    //map<string, student> students;
    string ask;
    command command_;
    
    map<command, map<string, student>> students;
    students[STUDS_BY_TASKS];
    students[STUDS_BY_BALLS];
    students[STUD_STAT];
    
    
    
    while (true)
    {
        cin >> ask;
        if (ask == "SOLVED")
            command_ = SOLVED;
        else if (ask == "STUD_STAT")
            command_ = STUD_STAT;
        else if (ask == "STUDS_BY_TASKS")
            command_ = STUDS_BY_TASKS;
        else if (ask == "STUDS_BY_BALLS")
            command_ = STUDS_BY_BALLS;
        else if (ask == "STUDS_MORE_TASKS")
            command_ = STUDS_MORE_TASKS;
        else if (ask == "STUDS_MORE_BALLS")
            command_ = STUDS_MORE_BALLS;
        else if (ask == "TASKS_BY_SOLUTIONS")
            command_ = TASKS_BY_SOLUTIONS;
        else if (ask == "EXIT")
        {
            command_ = EXIT;
            break;
        }
        else command_ = INVALID;
        
        
        switch (command_)
        {
            case SOLVED:
                solved(students, tasks);
                break;
            case STUD_STAT:
                stud_stat(students);
                break;
            case STUDS_BY_TASKS:
                studs_by_tasks(students);
                break;
            case STUDS_BY_BALLS:
                studs_by_balls(students);
                break;
            case STUDS_MORE_TASKS:
                studs_more_tasks(students);
                break;
            case STUDS_MORE_BALLS:
                studs_more_balls(students);
                break;
            case TASKS_BY_SOLUTIONS:
                tasks_by_solutions(tasks);
                break;
            default:
                cout << "INVALID COMMAND. TRY AGAIN." << endl;
                break;
        }
    }
    
    return 0;
}

void input(size_t & N, vector<task> & tasks)
{
    cout << "Количество задач:\n";
    cin >> N;
    cout << "Баллы за каждую задачу:\n";
    tasks.resize(N);
    size_t count = 1;
    for (auto & i: tasks)
    {
        cin >> i.cost;
        i.number = count++;
    }
}

void solved(map<command, map<f_arg, student>> & students, vector<task> & tasks)
{
    string name_;
    size_t number;
    cin >> name_ >> number;
    
    f_arg tmp_stat;
    tmp_stat.name = name_;
    tmp_stat.point = 0;
    
    students[STUD_STAT].e
}

void stud_stat(const map<string, student> & students)
{
    string name_;
    cin >> name_;
    try
    {
        cout << students.at(name_).solved << " " << students.at(name_).balls << endl;
    }
    catch (std::out_of_range)
    {
        cout << "SUCH STUDENT DOES NOT EXIST" << endl;
    }
}

void studs_by_tasks(const map<string, student> & students)
{
    if (!students.empty())
    {
        vector<student> st;
        for (const auto & i: students)
            *(back_inserter(st)) = i.second;
        
        sort(st.begin(), st.end(),
             [](const student & a, const student & b)
             {
                 if (a.solved < b.solved)
                     return true;
                 else if (a.solved > b.solved)
                     return false;
                 else return a.name < b.name;
             });
        
        for (const auto & i: st)
            cout << i.name << ' ' << i.solved << endl;
    }
}

void studs_by_balls(const map<string, student> & students)
{
    if (!students.empty())
    {
        vector<student> st;
        for (const auto & i: students)
            *(back_inserter(st)) = i.second;
        
        sort(st.begin(), st.end(),
             [](const student & a, const student & b)
             {
                 if (a.balls < b.balls)
                     return true;
                 else if (a.balls > b.balls)
                     return false;
                 else return a.name < b.name;
             });
        
        for (const auto & i: st)
            cout << i.name << ' ' << i.balls << endl;
    }
}

void studs_more_tasks(const map<string, student> & students)
{
    size_t n;
    cin >> n;
    
    vector<student> st;
    for (const auto & i: students)
        if (i.second.solved >= n)
            *(back_inserter(st)) = i.second;
    
    if (!st.empty())
    {
        sort(st.begin(), st.end(),
             [](const student & a, const student & b)
             {
                 if (a.solved < b.solved)
                     return true;
                 else if (a.solved > b.solved)
                     return false;
                 else return a.name < b.name;
             });
        
        for (const auto & i: st)
            cout << i.name << ' ' << i.solved << endl;
    }
}

void studs_more_balls(const map<string, student> & students)
{
    size_t n;
    cin >> n;
    
    vector<student> st;
    for (const auto & i: students)
        if (i.second.balls >= n)
            *(back_inserter(st)) = i.second;
    
    if (!st.empty())
    {
        sort(st.begin(), st.end(),
             [](const student & a, const student & b)
             {
                 if (a.balls < b.balls)
                     return true;
                 else if (a.balls > b.balls)
                     return false;
                 else return a.name < b.name;
             });
        
        for (const auto & i: st)
            cout << i.name << ' ' << i.balls << endl;
    }
}

void tasks_by_solutions(const vector<task> & tasks)
{
    vector<task> copy_;
    copy(tasks.begin(), tasks.end(), back_inserter(copy_));
    sort(copy_.begin(), copy_.end(),
         [](const task & a, const task & b)
         {
             if (a.count_solvings < b.count_solvings)
                 return true;
             else if (a.count_solvings > b.count_solvings)
                 return false;
             else return a.number < b.number;
         });
    
    for (const auto & i: copy_)
        cout << i.number << ' ' << i.count_solvings << endl;
}




/*
 
 input:
 
 4
 20 4 6 8
 SOLVED ivanov 3
 SOLVED sidorov 1
 SOLVED petrov 4
 SOLVED ivanov 4
 STUDS_BY_BALLS
 STUD_STAT ivanov
 STUD_STAT petrov
 SOLVED petrov 2
 STUDS_MORE_TASKS 2
 SOLVED ivanov 1
 SOLVED sidorov 2
 SOLVED petrov 1
 TASKS_BY_SOLUTIONS
 STUDS_BY_TASKS
 STUDS_MORE_BALLS 33
 EXIT
 
 output:
 
 petrov 8
 ivanov 14
 sidorov 20
 2 14
 1 8
 ivanov 2
 petrov 2
 3 1
 2 2
 4 2
 1 3
 sidorov 2
 ivanov 3
 petrov 3
 ivanov 34
 
 */
