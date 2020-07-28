---
author: zc
avatar: null
categories:
- - 刷题记录
commnet: 1
date: 2020-04-26 16:20
html: '<details><summary>查看原题</summary><div id=''from''></div><p><button onclick="document.getElementById(''from'').innerHTML=''<iframe
  src=&quot;https://www.luogu.com.cn/problem/CF1324F&quot; width=100% height=800px
  style=&quot;border: none;&quot;><iframe>''" class=''mdui-btn mdui-btn-raised mdui-ripple''>点击加载</button><a
  class=''mdui-btn mdui-btn-raised mdui-ripple'' href="https://www.luogu.com.cn/problem/CF1324F"
  target=''_blank''>点击跳转</a><p></details>'
permalink: LG CF1324F Maximum White Subtree
tags:
- 树型dp
- dfs
thumbnail: null
title: LG CF1324F Maximum White Subtree
top: 0
---
两次dfs即可

第一次dfs: 

计算出每个点的子树,包含这个点,答案最大是多少

显然$S_x=v_x+\sum\limits_{y\in son_x} [S_y>0]S_y$

(若$x$为黑点$v_x=-1$,否则$v_x=1$)

第二次dfs:

通过$x$的父亲的答案来计算出$x$的答案

如果$x$目前的答案$>0$,则从$x$的答案减去$x$目前的答案

如果这个结果$>0$,那么$x$的答案加上这个结果

感觉直接看代码可能更直观
```cpp
#include<bits/stdc++.h>
#define gc getchar()
#define fur(i,x,y) for(int i=x;i<=y;++i)
void in(int &x){x=0;char c;bool f=0;for(c=gc;c<'0'||'9'<c;c=gc)f^=c=='-';for(x=c-48,c=gc;'0'<=c&&c<='9';x=x*10+c-48,c=gc);if(f)x=-x;}
const int N=200011;
int n,cnt,head[N],s[N];
struct edge{int to,nxt;}e[N<<1];
void add(int x,int y){e[++cnt].to=y,e[cnt].nxt=head[x];head[x]=cnt;}
void dfs(int x,int f){
    for(int i=head[x],to;to=e[i].to,i;i=e[i].nxt)
        if(to^f){dfs(to,x);if(s[to]>0)s[x]+=s[to];}
}
void up(int x,int f){
    int t=s[f];if(s[x]>0)t-=s[x];
    if(t>0)s[x]+=t;
    for(int i=head[x],to;to=e[i].to,i;i=e[i].nxt)
        if(to^f)up(to,x);
}
int main(){
    in(n);
    int x,y;
    fur(i,1,n)in(x),s[i]=x?1:-1;
    fur(i,1,n-1)in(x),in(y),add(x,y),add(y,x);
    dfs(1,0);up(1,0);
    fur(i,1,n)printf("%d ",s[i]);
}
```
