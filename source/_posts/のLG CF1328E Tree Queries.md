---
author: zc
avatar: null
categories:
- - 刷题记录
commnet: 1
date: 2020-04-27 17:49
html: '<details><summary>查看原题</summary><div id=''from''></div><p><button onclick="document.getElementById(''from'').innerHTML=''<iframe
  src=&quot;https://www.luogu.com.cn/problem/CF1328E&quot; width=100% height=800px
  style=&quot;border: none;&quot;><iframe>''" class=''mdui-btn mdui-btn-raised mdui-ripple''>点击加载</button><a
  class=''mdui-btn mdui-btn-raised mdui-ripple'' href="https://www.luogu.com.cn/problem/CF1328E"
  target=''_blank''>点击跳转</a><p></details>'
permalink: LG CF1328E Tree Queries
tags:
- 树
thumbnail: null
title: LG CF1328E Tree Queries
top: 0
---
可以发现,这条链必然经过每个给定点的父亲

把每个给定点都变成它的父亲

按深度排序

依次判断接下来的节点是否在上一个的子树中即可
```cpp
#include<bits/stdc++.h>
#define gc getchar()
#define fur(i,x,y) for(int i=x;i<=y;++i)
void in(int &x){x=0;char c;bool f=0;for(c=gc;c<'0'||'9'<c;c=gc)f^=c=='-';for(x=c-48,c=gc;'0'<=c&&c<='9';x=x*10+c-48,c=gc);if(f)x=-x;}
const int N=200011;
int n,q,cnt,head[N],a[N],f[N],d[N],L[N],R[N],dfn;
bool cmp(int x,int y){return d[x]<d[y];}
struct edge{int to,nxt;}e[N<<1];
void add(int x,int y){e[++cnt].to=y;e[cnt].nxt=head[x];head[x]=cnt;}
void dfs(int x){
    L[x]=++dfn,d[x]=d[f[x]]+1;
    for(int i=head[x],to;to=e[i].to,i;i=e[i].nxt)
        if(to^f[x])f[to]=x,dfs(to);
    R[x]=dfn;
}
bool chk(int x,int y){return L[x]<=L[y]&&L[y]<=R[x];}
int main(){
    in(n),in(q);
    int x,y,ff;
    fur(i,2,n)in(x),in(y),add(x,y),add(y,x);
    f[1]=1,dfs(1);
    while(q--){
        in(y);
        fur(i,1,y)in(x),a[i]=f[x];
        std::sort(a+1,a+y+1,cmp);
        ff=1;
        fur(i,1,y-1)if(!chk(a[i],a[i+1])){ff=0;break;}
        puts(ff?"YES":"NO");
    }
}
```
