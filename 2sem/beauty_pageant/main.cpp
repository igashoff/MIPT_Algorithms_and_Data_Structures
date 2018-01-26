//
//  main.cpp
//  beauty_pageant
//
//  Created by Igashov_Ilya on 10.05.16.
//  Copyright (c) 2016 Igashov_Ilya. All rights reserved.
//

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

struct key
{
    size_t k;
    string name;
    key(size_t key_, const string & name_): k(key_), name(name_) {};
    bool operator <(const key & other) const
    {
        if (k == other.k)
            return name < other.name;
        return k >= other.k;
    }
};

struct voter
{
    string number;
    size_t limit;
    size_t votes;
};

struct member
{
    string name;
    size_t votes;
    
    bool operator <(const member & other) const
    {
        if (votes != other.votes)
            return votes < other.votes;
        else
            return name >= other.name;
    }
};

enum command {REGISTER, VIP, VOTE, KICK, TOP, EXIT, INVALID};

void register_please(map<string, member> & members, multimap<key, member> & members_by_votes);
void vip(map<string, voter> & voters);
void vote(map<string, voter> & voters, map<string, member> & members, multimap<key, member> & members_by_votes);
void kick(map<string, member> & members, multimap<key, member> & members_by_votes);
void top(const multimap<key, member> & members_by_votes);

int main()
{
    map<string, voter> voters;
    map<string, member> members;
    multimap<key, member> members_by_votes;
    
    string ask;
    command command_;
    
    while (true)
    {
        cin >> ask;
        if (ask == "REGISTER")
            command_ = REGISTER;
        else if (ask == "VIP")
            command_ = VIP;
        else if (ask == "VOTE")
            command_ = VOTE;
        else if (ask == "KICK")
            command_ = KICK;
        else if (ask == "TOP")
            command_ = TOP;
        else if (ask == "EXIT")
        {
            command_ = EXIT;
            cout << "OK" << endl;
            break;
        }
        else command_ = INVALID;
        
        
        switch (command_)
        {
            case REGISTER:
                register_please(members, members_by_votes);
                break;
            case VIP:
                vip(voters);
                break;
            case VOTE:
                vote(voters, members, members_by_votes);
                break;
            case KICK:
                kick(members, members_by_votes);
                break;
            case TOP:
                top(members_by_votes);
                break;
            default:
                cout << "INVALID COMMAND" << endl;
                break;
        }
    }
    
    return 0;
}

void register_please(map<string, member> & members, multimap<key, member> & members_by_votes)
{
    string name_;
    cin >> name_;
    try
    {
        members.at(name_);
        cout << "ALREADY REGISTERED" << endl;
    }
    catch (out_of_range)
    {
        members[name_].name = name_;
        members[name_].votes = 0;
        cout << "OK" << endl;
        
        key tmp(0, name_);
        members_by_votes.emplace(make_pair(tmp, members[name_]));
    }
}

void vip(map<string, voter> & voters)
{
    string number_;
    cin >> number_;
    try
    {
        if (voters.at(number_).limit == 1)
        {
            voters.at(number_).limit = 3;
            cout << "OK" << endl;
        }
        else
            cout << "ALREADY VIP" << endl;
    }
    catch (out_of_range)
    {
        voters[number_].number = number_;
        voters[number_].limit = 3;
        voters[number_].votes = 0;
        cout << "OK" << endl;
    }
}

void vote(map<string, voter> & voters, map<string, member> & members, multimap<key, member> & members_by_votes)
{
    string name_;
    string number_;
    cin >> name_ >> number_;
    
    try
    {
        if (voters.at(number_).votes < voters.at(number_).limit)
        {
            try
            {
                members.at(name_).votes += 1;
                voters.at(number_).votes += 1;
                cout << members.at(name_).votes << endl;
                
                /*members_by_votes.erase(find_if(members_by_votes.begin(), members_by_votes.end(), [&](member x)
                                               { return x.name == name_; }));*/
                //bool check = false;
                auto x = members_by_votes.begin();
                for (auto & i: members_by_votes)
                {
                    if (i.second.name == name_)
                    {
                        members_by_votes.erase(x);
                        break;
                    }
                    ++x;
                }
                
                key tmp(members.at(name_).votes, name_);
                members_by_votes.emplace(make_pair(tmp, members.at(name_)));
            }
            catch (out_of_range)
            {
                cout << "NOT REGISTERED" << endl;
            }
        }
        else
            cout << "NO MORE VOTES" << endl;
    }
    catch (out_of_range)
    {
        voters[number_].number = number_;
        voters[number_].limit = 1;
        voters[number_].votes = 0;
        
        try
        {
            members.at(name_).votes += 1;
            voters.at(number_).votes += 1;
            cout << members.at(name_).votes << endl;
            
            auto x = members_by_votes.begin();
            for (auto & i: members_by_votes)
            {
                if (i.second.name == name_)
                {
                    members_by_votes.erase(x);
                    break;
                }
                ++x;
            }
            
            key tmp(members.at(name_).votes, name_);
            members_by_votes.emplace(make_pair(tmp, members.at(name_)));
        }
        catch (out_of_range)
        {
            cout << "NOT REGISTERED" << endl;
        }
    }
}

void kick(map<string, member> & members, multimap<key, member> & members_by_votes)
{
    string name_;
    cin >> name_;
    
    if (members.erase(name_) > 0)
    {
        /*members_by_votes.erase(find_if(members_by_votes.begin(), members_by_votes.end(), [&](member x)
                                       { return x.name == name_; }));*/
        auto x = members_by_votes.begin();
        for (auto & i: members_by_votes)
        {
            if (i.second.name == name_)
            {
                members_by_votes.erase(x);
                break;
            }
            ++x;
        }
        
        cout << "OK" << endl;
    }
    else
        cout << "NOT REGISTERED" << endl;
}

/*
void top(const map<string, member> & members)
{
    size_t N;
    cin >> N;
    vector<member> mem;
    for (const auto & m: members)
        mem.push_back(m.second);
    sort(mem.rbegin(), mem.rend());
    for (const auto & m: mem)
    {
        cout << m.name << ' ' << m.votes << endl;
        --N;
        if (N == 0)
            break;
    }
}
*/
void top(const multimap<key, member> & members_by_votes)
{
    size_t N;
    cin >> N;
    for (auto & i: members_by_votes)
    {
        cout << i.second.name << ' ' << i.first.k << endl;
        if (--N == 0)
            break;
    }
}


/*
 Пример 1.
 
 Вход:
 REGISTER MARY
 REGISTER JANE
 TOP 10
 VOTE MARY +79161234567
 TOP 10
 EXIT
 
 Выход:
 OK
 OK
 JANE 0
 MARY 0
 1
 MARY 1
 JANE 0
 OK
 
 Пример 2.
 
 Вход:
 TOP 10
 VOTE SALLY +79161234567
 KICK SALLY
 REGISTER SALLY
 REGISTER SALLY
 VOTE SALLY +79161234567
 VOTE SALLY +79161234567
 VIP +79161234567
 VOTE SALLY +79161234567
 VOTE SALLY +79161234567
 VOTE SALLY +79161234567
 VOTE SALLY +79161234567
 VIP +79161234567
 VOTE ALICE +79161234567
 EXIT
 
 Выход:
 NOT REGISTERED
 NOT REGISTERED
 OK
 ALREADY REGISTERED
 1
 NO MORE VOTES
 OK
 2
 3
 4
 NO MORE VOTES
 ALREADY VIP
 NOT REGISTERED
 OK
 
 Пример 3.
 
 Вход:
 REGISTER SALLY
 VOTE SALLY +79161234567
 KICK SALLY
 VOTE SALLY +79031111111
 REGISTER SALLY
 VOTE SALLY +79031111111
 EXIT
 
 Выход:
 OK
 1
 OK
 NOT REGISTERED
 OK
 1
 OK
*/
