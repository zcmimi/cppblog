#include<bits/stdc++.h>
#include"str.h"
using std::string,std::wstring;
struct str_node{
    char c;
    str_node*nxt;
    str_node(){c=NULL,nxt=NULL;}
    str_node(const char cc){c=cc;nxt=NULL;}
    bool operator==(const char cc)const{return c==cc;}
};
struct STR{
    str_node*bg,*ed;
    int len;
    STR(){len=0;bg=ed=NULL;}
    STR(const char*s,int l=-1){
        if(l==-1)l=strlen(s);
        len=l;
        if(!l){bg=ed=NULL;return;}

        bg=new str_node(s[0]),ed=bg->nxt=new str_node();
        for(int i=1;i<l;++i)
            ed->c=s[i],ed=ed->nxt=new str_node();
    }
    void push_back(const char c){
        if(bg==NULL)bg=new str_node(c),ed=bg->nxt=new str_node(),len=1;
        else ed->c=c,ed=ed->nxt=new str_node(),++len;
    }
    void push_back(const char*s){for(int i=0,l=strlen(s);i<l;++i)push_back(s[i]);}
    void push_back(STR&s){
        if(bg==NULL)bg=s.bg,ed=s.ed;
        else ed=s.bg,ed=s.ed;
    }
    void push_back(const STR&s){
        str_node*node=s.bg;
        while(node!=s.ed)push_back(node->c),node=node->nxt;
    }    
    void push_front(const char c){
        str_node*node=new str_node(c);
        if(bg==NULL)bg=node,ed=bg->nxt=new str_node(),len=1;
        else node->nxt=bg,bg=node,++len;
    }
    void push_front(const char*s){for(int i=0,l=strlen(s);i<l;++i)push_back(s[i]);}
    void op(FILE*fp)const{
        str_node*node=bg;
        while(node!=ed)
            fputc(node->c,fp),node=node->nxt;
    }
    const char* c_str(int l=-1)const{
        if(l==-1)l=len;
        char*res=(char *)malloc(len+1),*p=res;
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
    void operator+=(const STR&s){push_back(s);}

    friend STR operator+(const STR&s,const char c){
        STR res=s;
        res.push_back(c);
        return res;
    }
    friend STR operator+(const STR&t,const char*s){
        STR res=t;
        res.push_back(s);
        return res;
    }
};
STR operator+(const char c,const STR&s){
    STR res=s;
    res.push_front(c);
    return res;
}
STR operator+(const char*s,const STR&t){
    STR res=t;
    res.push_front(s);
    return res;
}
STR operator+(STR x,const STR y){
    x.push_back(y);
    return x;
}
STR to_STR(int val){return STR(std::to_string(val).c_str());}