---
author: zc
avatar: null
categories:
- - 刷题记录
commnet: 1
date: 2020-05-03 11:09
html: '<details><summary>查看原题</summary><div id=''from''></div><p><button onclick="document.getElementById(''from'').innerHTML=''<iframe
  src=&quot;https://www.luogu.com.cn/problem/CF1304E&quot; width=100% height=800px
  style=&quot;border: none;&quot;><iframe>''" class=''mdui-btn mdui-btn-raised mdui-ripple''>点击加载</button><a
  class=''mdui-btn mdui-btn-raised mdui-ripple'' href="https://www.luogu.com.cn/problem/CF1304E"
  target=''_blank''>点击跳转</a><p></details>'
permalink: LG CF1304E 1-Trees and Queries
tags:
- 树
- lca
thumbnail: null
title: LG CF1304E 1-Trees and Queries
top: 0
---
可以发现有三种路径:

1. $a \leftrightarrow b$
   
2. $a \leftrightarrow x \leftrightarrow y \leftrightarrow b$

3. $a \leftrightarrow y \leftrightarrow x \leftrightarrow b$

只需要判断这三条路径是否满足就可以了

可以发现只要$dis\le k$而且和$k$同奇偶就是符合的

(比如$x\leftrightarrow y$可以一直循环,变成$x\leftrightarrow y \leftrightarrow x \leftrightarrow y \dots$,每次长度$+2$)


```cpp
#include<bits/stdc++.h>
#define gc getchar()
#define fur(i,x,y) for(int i=x;i<=y;++i)
void in(int &x){x=0;char c;bool f=0;for(c=gc;c<'0'||'9'<c;c=gc)f^=c=='-';for(x=c-48,c=gc;'0'<=c&&c<='9';x=x*10+c-48,c=gc);if(f)x=-x;}
const int N=100011;
int n,k,cnt,head[N],d[N],f[N],siz[N],top[N];
struct edge{int to,nxt;}e[N<<1];
void add(int x,int y){e[++cnt].to=y;e[cnt].nxt=head[x];head[x]=cnt;}
#define fl(i,x) for(int i=head[x],to;to=e[i].to,i;i=e[i].nxt)
void dfs(int x){
    siz[x]=1;
    fl(i,x)if(to!=f[x]){
        f[to]=x;d[to]=d[x]+1;
        dfs(to);siz[x]+=siz[to];
    }
}
void bt(int x,int tp){
    top[x]=tp;int k=0;
    fl(i,x)if(to!=f[x]&&siz[to]>siz[k])k=to;
    if(!k)return;bt(k,tp);
    fl(i,x)if(!top[to])bt(to,to);
}
int lca(int x,int y){
    while(top[x]!=top[y])(d[top[x]]>d[top[y]])?(x=f[top[x]]):(y=f[top[y]]);
    return d[x]<d[y]?x:y;
}
int dis(int x,int y){return d[x]+d[y]-2*d[lca(x,y)];}
bool chk(int x){return x<=k&&(x&1)==(k&1);}
int main(){
    in(n);
    int x,y,a,b,q;
    fur(i,2,n)in(x),in(y),add(x,y),add(y,x);
    dfs(1),bt(1,1);
    in(q);
    while(q--){
        in(x),in(y),in(a),in(b),in(k);
        if(chk(dis(a,b))||chk(dis(a,x)+1+dis(y,b))||chk(dis(a,y)+1+dis(x,b)))puts("YES");
        else puts("NO");
    }
}
```
