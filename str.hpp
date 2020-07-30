#ifndef STR_H
#define STR_H

#include<bits/stdc++.h>
using std::string;
struct str_node{
    char c;
    str_node*nxt;
    str_node(){nxt=NULL;}
    str_node(const char cc){c=cc;nxt=NULL;}
    bool operator==(const char cc)const{return c==cc;}
};
struct STR{
    str_node*bg,*ed;
    int len;
    STR(){len=0;bg=ed=NULL;}
    STR(const char c){bg=new str_node(c),ed=NULL,len=1;}
    STR(const char*s,int l=-1){
        if(l==-1)l=strlen(s);
        len=l;
        if(!l){bg=ed=NULL;return;}

        bg=new str_node(s[0]),ed=bg->nxt=new str_node();
        for(int i=1;i<l;++i)
            ed->c=s[i],ed=ed->nxt=new str_node();
    }
    void push_back(const char&c){
        if(bg==NULL)bg=new str_node(c),ed=bg->nxt=new str_node(),len=1;
        else ed->c=c,ed=ed->nxt=new str_node(),++len;
    }
    void push_back(const char*s){
        int l=strlen(s);if(!l)return;
        push_back(s[0]);
        for(int i=1;i<l;++i)
            ed->c=s[i],ed=ed->nxt=new str_node();
    }
    void push_back_(STR s){
        if(bg==NULL)bg=s.bg,ed=s.ed;
        else ed=s.bg,ed=s.ed;
    }
    void push_back(const STR&s){
        for(str_node*node=s.bg;node!=s.ed;node=node->nxt)
            push_back(node->c);
    }
    void push_front(const char&c){
        str_node*node=new str_node(c);
        if(bg==NULL)bg=node,ed=bg->nxt=new str_node(),len=1;
        else node->nxt=bg,bg=node,++len;
    }
    void push_front(const char*s){for(int i=0,l=strlen(s);i<l;++i)push_back(s[i]);}
    void op(FILE*fp)const{
        for(str_node*node=bg;node!=ed;node=node->nxt)
            fputc(node->c,fp);
    }
    string str(int l=-1){
        if(l==-1||l>len)l=len;
        string res;
        str_node*node=bg;
        while(l--)
            res+=node->c,
            node=node->nxt;
        return res;
    }
    const char* c_str(int l=-1)const{
        if(l==-1||l>len)l=len;
        char*res=(char *)malloc(l+1),*p=res;
        str_node*node=bg;
        while(l--)
            *p++=node->c,
            node=node->nxt;
        *p='\0';
        return (const char*)res;
    }
    bool empty(){return !len;}

    bool operator<(const STR&s)const{
        int n=len<s.len?len:s.len;
        str_node*x=bg,*y=s.bg;
        while(n--){
            if(x->c!=y->c)return x->c<y->c;
            x=x->nxt,y=y->nxt;
        }
        return len<s.len;
    }
    bool operator>(const STR&s)const{
        int n=len<s.len?len:s.len;
        str_node*x=bg,*y=s.bg;
        while(n--){
            if(x->c!=y->c)return x->c>y->c;
            x=x->nxt,y=y->nxt;
        }
        return len>s.len;
    }
    bool operator==(const STR&s)const{
        if(len!=s.len)return 0;
        str_node*x=bg,*y=s.bg;
        for(int i=0;i<len;++i){
            if(x->c!=y->c)return 0;
            x=x->nxt,y=y->nxt;
        }
        return 1;
    }
    bool operator==(const char*s)const{
        int l=strlen(s);
        if(len!=l)return 0;
        str_node*x=bg;
        for(int i=0;i<l;++i){
            if(x->c!=s[i])return 0;
            x=x->nxt;
        }
        return 1;
    }

    struct iterator{
        str_node*node;
        iterator(){node=NULL;}
        iterator(str_node*p){node=p;}
        bool operator!=(const iterator&p){return node!=p.node;}
        void operator++(){node=node->nxt;}
        str_node operator*(){return *node;}
        const str_node operator*()const{return *node;}
    };

    iterator begin(){return bg;}
    iterator end(){return ed;}

    void operator+=(const char c){push_back(c);}
    void operator+=(const char*s){push_back(s);}
    void operator+=(STR s){push_back_(s);}
    // void operator+=(const STR&s){push_back(s);}
};
STR mg(STR x,STR y){
    x.push_back(y);
    return x;
}
STR operator+(STR x,STR y){return mg(x,y);}

STR to_STR(int val){
    if(val==0)return STR('0');
    STR res;
    if(val<0)val=-val,res.push_front('-');
    while(val)res.push_front(val%10),val/=10;
    return res;
}
#endif