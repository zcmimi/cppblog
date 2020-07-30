#ifndef FASTIO_H
#define FASTIO_H

#include<bits/stdc++.h>
using std::string;

char* read(const string&file){
    FILE*fp=fopen(file.c_str(),"r");
    fseek(fp,0,SEEK_END);
    int len=ftell(fp);
    char*res=(char*)malloc(len+1);
    rewind(fp);
    fread(res,1,len,fp);
    res[len]='\0';
    return res;
}

void out(const string&str,FILE*fp){fputs(str.c_str(),fp);}
void out(const char*str,FILE*fp){fputs(str,fp);}
void out(const char&c,FILE*fp){fputc(c,fp);}
void out(int val,FILE*fp){fprintf(fp,"%d",val);}


const int SIZ=1<<20;
struct OUT{
    char out_buf[SIZ],*out_s,*out_t;
    FILE*fp;
    OUT(){}
    OUT(FILE*file){fp=file,out_s=out_buf,out_t=out_buf+SIZ;}
    void flush(){fwrite(out_buf,1,out_s-out_buf,fp);out_s=out_buf;}
    void pt(const char&c){(out_s==out_t)?(fwrite(out_s=out_buf,1,SIZ,fp),*out_s++=c):(*out_s++=c);}
    void out(const char*s){while(*s)pt(*s++);}
    void out(const char&c){pt(c);}
    void out(const string&s){for(auto&i:s)pt(i);}
    template<typename T>
    void out(T x){
        if(!x){pt('0');return;}
        if(x<0)pt('-'),x=-x;
        char a[50],t=0;
        while(x)a[t++]=x%10,x/= 10;
        while(t--)pt(a[t]+'0');
    }
    template<typename T,typename ... arr>
    void out(T x,arr & ... y){out(x),out(y...);}
};

#endif