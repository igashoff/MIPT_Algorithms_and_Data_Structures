//
//  main.cpp
//  students_exam
//
//  Created by Igashov_Ilya on 17.04.16.
//  Copyright (c) 2016 Igashov_Ilya. All rights reserved.
//

#include <iostream>
#include <vector>
#include <map>
#include <set>

class student
{
    std::string fname;
    std::string lname;
    std::map <std::string, size_t> exams;
    
public:
    
    student(std::string name)
    {
        size_t space = name.find(' ');
        fname = name.substr(0, space);
        lname = name.substr(space + 1);
    }
    
    void add_subject(std::string subject, size_t mark)
    {
        exams[subject] = mark;
    }
    
    size_t mark(std::string subject) const
    {
        if (exams.find(subject) == exams.end())
            return 0;
        return exams.at(subject);
    }
    
    size_t well_done() const
    {
        size_t count = 0;
        
        for (auto i: exams)
            if (i.second > 2)
                ++count;
        return count;
    }
    
    size_t flunked() const
    {
        size_t count = 0;
        
        for (auto i: exams)
            if (i.second < 3)
                ++count;
        return count;
    }

    
    std::string get_lname() const
    {
        return lname;
    }
    
    bool operator <(const student & other) const
    {
        return lname < other.lname;
    }
};

class group
{
    std::set<student> my_group;
    const size_t limit;
    
public:
    
    group(size_t limit_ = 1): limit(limit_) {}
    
    void add_student(const student & new_student)
    {
        my_group.insert(new_student);
    }
    
    
    std::vector<std::string> retake(std::string subject)
    {
        std::vector<std::string> students;
        
        for (auto i: my_group)
            if (i.mark(subject) < 3)
                students.push_back(i.get_lname());
        
        return students;
    }
    
    void kick_out()
    {
        std::vector<student> tmp;
        
        for (const auto& i: my_group)
            if (i.flunked() > limit)
                tmp.push_back(i);
        
        for (const auto& i: tmp)
            my_group.erase(my_group.find(i));
    }
    
    void show() const
    {
        std::cout << "MY GROUP:\n";
        for (auto i: my_group)
            std::cout << i.get_lname() << std::endl;
    }
    
    
};




int main()
{
    student ilya("Ilya Igashov");
    ilya.add_subject("Biology", 7);
    ilya.add_subject("Math", 2);
    ilya.add_subject("Literature", 10);
    
    student anna("Anna Pyshkova");
    anna.add_subject("Math", 1);
    anna.add_subject("Literature", 8);
    anna.add_subject("Biology", 10);
    
    student nikita("Nikita Baskakov");
    nikita.add_subject("Literature", 1);
    nikita.add_subject("Biology", 2);
    
    student vlad("Vladislav Arzhanov");
    vlad.add_subject("Literature", 2);
    vlad.add_subject("Math", 5);
    
    group g;
    g.add_student(ilya);
    g.add_student(anna);
    g.add_student(nikita);
    g.add_student(vlad);
    
    
    std::vector<std::string> v = g.retake("Literature");
    
    for (auto i: v)
        std::cout << i << std::endl;
    g.show();
    
    g.kick_out();
    g.show();
    
    std::cout << vlad.flunked();
    
    return 0;
}