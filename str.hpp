#include<bits/stdc++.h>
using std::string,std::wstring;
struct STR{
    char *str;
    size_t len;
    STR(){len=0;}
    STR(string s){str=(char *)s.c_str();len=s.length();}
    STR(const char*s){str=(char *)s;len=strlen(s);}
    STR(const char*s,size_t l){str=(char *)s;len=l;}

    char&operator[](const size_t p){return str[p];}
    bool operator<(const STR&t){
        int n=len<t.len?len:t.len;
        for(int i=0;i<n;++i)
            if(str[i]<t.str[i])return 1;
        return len<t.len;
    }
    bool operator==(const STR&t){
        if(len!=t.len)return 0;
        for(int i=0;i<len;++i)if(str[i]!=t.str[i])return 0;
        return 1;
    }
    bool operator==(const char*s){
        if(len!=strlen(s))return 0;
        for(int i=0;i<len;++i)if(str[i]!=s[i])return 0;
        return 1;
    }
    STR operator+(const char*s){
        size_t l=strlen(s);
        char *res=(char *)malloc(len+l+1);
        sprintf(res,"%.*s%.*s",len,str,l,s);
        str=res;len+=l;
    }
    STR operator+(const STR&t){
        char *res=(char *)malloc(len+t.len+1);
        sprintf(res,"%.*s%.*s",len,str,t.len,t.str);
        return STR(res,len+t.len);
    }
    void operator+=(const char&c){str[len++]=c;}
    void operator+=(const char*s){
        for(int i=0,l=strlen(s);i<l;++i)
            str[len++]=s[i];
    }
};