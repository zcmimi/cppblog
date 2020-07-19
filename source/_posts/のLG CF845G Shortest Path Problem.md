---
author: zc
avatar: null
categories:
- - "\u5237\u9898\u8BB0\u5F55"
commnet: 1
date: 2020-06-04 12:21
html: "<details><summary>\u67E5\u770B\u539F\u9898</summary><div id='from'></div><p><button\
  \ onclick=\"document.getElementById('from').innerHTML='<iframe src=&quot;https://www.luogu.com.cn/problem/CF845G&quot;\
  \ width=100% height=800px style=&quot;border: none;&quot;><iframe>'\" class='mdui-btn\
  \ mdui-btn-raised mdui-ripple'>\u70B9\u51FB\u52A0\u8F7D</button><a class='mdui-btn\
  \ mdui-btn-raised mdui-ripple' href=\"https://www.luogu.com.cn/problem/CF845G\"\
  \ target='_blank'>\u70B9\u51FB\u8DF3\u8F6C</a><p></details>"
permalink: LG CF845G Shortest Path Problem
tags:
- "\u7EBF\u6027\u57FA"
- "\u56FE\u8BBA"
- dfs
thumbnail: null
title: LG CF845G Shortest Path Problem
top: 0
---
同[\[WC2011\]最大XOR和路径](https://www.luogu.com.cn/problem/P4151)
```cpp
#include<bits/stdc++.h>
int rd(){int x=0;char c;bool f=0;for(c=getchar();c<'0'||'9'<c;c=getchar())f^=c=='-';for(x=c-48,c=getchar();'0'<=c&&c<='9';x=x*10+c-48,c=getchar());return f?-x:x;}
const int N=100011;
int n,m,cnt,head[N],d[N],p[30];
struct edge{int to,nxt,w;}e[N<<1];
void add(int x,int y,int w){e[++cnt].to=y,e[cnt].nxt=head[x],head[x]=cnt,e[cnt].w=w;}
void ins(int x){
    for(int i=27;x,~i;--i)if(x>>i){
        if(!p[i]){p[i]=x;return;}
        x^=p[i];
    }
}
bool v[N];
void dfs(int x){
    v[x]=1;
    for(int i=head[x],to;to=e[i].to,i;i=e[i].nxt)
        if(!v[to])d[to]=d[x]^e[i].w,dfs(to);
        else ins(d[x]^d[to]^e[i].w);
}
int main(){
    n=rd(),m=rd();
    int x,y,w;
    while(m--)
        x=rd(),y=rd(),w=rd(),
        add(x,y,w),add(y,x,w);
    dfs(1);x=d[n];
    for(int i=27;~i;--i)
        if((x^p[i])<x)x^=p[i];
    printf("%d\n",x);
}
```
