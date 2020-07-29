#include<bits/stdc++.h>

#ifndef STR_H
#define STR_H

struct str_node{
    char c;
    str_node*nxt;
    str_node();
    str_node(const char cc);
    bool operator==(const char cc)const;
};
struct STR{
    str_node*bg,*ed;
    int len;
    STR();
    STR(const char*s,int l=-1);
    void push_back(const char c);
    void push_back(const char*s);
    void push_back(STR&s);
    void push_back(const STR&s);
    void push_front(const char c);
    void push_front(const char*s);
    void op(FILE*fp);
    const char* c_str(int l=-1)const;
    bool empty();

    bool operator<(const STR&s)const;
    bool operator>(const STR&s)const;
    bool operator==(const STR&s)const;
    bool operator==(const char*s)const;

    struct iterator{
        str_node*node;
        iterator();
        iterator(str_node*p);
        bool operator!=(const iterator&p);
        void operator++();
        str_node operator*();
        const str_node operator*()const;
    };

    iterator begin();
    iterator end();

    void operator+=(const char c);
    void operator+=(const char*s);
    void operator+=(const STR&s);

    friend STR operator+(const STR&s,const char c);
    friend STR operator+(const STR&t,const char*s);
};
STR operator+(const char c,const STR&s);
STR operator+(const char*s,const STR&t);
STR operator+(STR x,const STR y);
STR to_STR(int val);

#endif