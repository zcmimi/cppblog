---
author: zc
avatar: null
categories:
- - "\u5237\u9898\u8BB0\u5F55"
commnet: 1
date: 2020-05-29 17:09
html: "<details><summary>\u67E5\u770B\u539F\u9898</summary><div id='from'></div><p><button\
  \ onclick=\"document.getElementById('from').innerHTML='<iframe src=&quot;https://www.luogu.com.cn/problem/P6569&quot;\
  \ width=100% height=800px style=&quot;border: none;&quot;><iframe>'\" class='mdui-btn\
  \ mdui-btn-raised mdui-ripple'>\u70B9\u51FB\u52A0\u8F7D</button><a class='mdui-btn\
  \ mdui-btn-raised mdui-ripple' href=\"https://www.luogu.com.cn/problem/P6569\" target='_blank'>\u70B9\
  \u51FB\u8DF3\u8F6C</a><p></details>"
permalink: "LG 6569 [NOI Online 3 \u63D0\u9AD8\u7EC4]\u9B54\u6CD5\u503C"
tags:
- "\u77E9\u9635"
- "\u500D\u589E"
- "\u4E8C\u8FDB\u5236"
thumbnail: null
title: "LG 6569 [NOI Online 3 \u63D0\u9AD8\u7EC4]\u9B54\u6CD5\u503C"
top: 0
---
矩阵乘法

这题倍增加速比快速幂快,可以节省很多多余的计算

二进制拆位后才能矩阵运算
```cpp
#include<bits/stdc++.h>
#define fur(i,x,y) for(int i=x;i<=y;++i)
typedef unsigned int ll;
ll rd(){ll x=0;char c;for(c=getchar();c<'0'||'9'<c;c=getchar());for(x=c-48,c=getchar();'0'<=c&&c<='9';x=x*10+c-48,c=getchar());return x;}
char cr[50];int tt;
void print(ll x){
    if(!x)putchar('0');
    while(x)cr[++tt]=x%10+'0',x/=10;
    while(tt)putchar(cr[tt--]);
    putchar('\n');
}
int n,m,q;ll f[101],g[101],t[101];
struct mat{bool a[101][101];}bs[32];
mat operator*(mat a,mat b){
    mat c;
    fur(i,1,n)fur(j,1,n){
        c.a[i][j]=0;
        fur(k,1,n)c.a[i][j]^=a.a[i][k]&b.a[k][j];
    }
    return c;
}
void mul(mat x){
    memset(t,0,n*4+4);
    fur(i,1,n)fur(j,1,n)
        if(x.a[i][j])t[i]^=g[j];
    fur(i,1,n)g[i]=t[i];
}
ll solve(ll v){
    fur(i,1,n)g[i]=f[i];
    fur(i,0,31)if((v>>i)&1)mul(bs[i]);
    return g[1];
}
int main(){
    n=rd(),m=rd(),q=rd();
    int x,y;;
    fur(i,1,n)f[i]=rd();
    fur(i,1,m)
        x=rd(),y=rd(),
        bs[0].a[x][y]=bs[0].a[y][x]=1;
    fur(i,1,31)bs[i]=bs[i-1]*bs[i-1];
    while(q--)print(solve(rd()));
}
```
