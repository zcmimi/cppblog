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

void out(const string&str,FILE*fp){
    
}

#endif