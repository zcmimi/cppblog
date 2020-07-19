---
author: zc
avatar: null
categories:
- - "\u5237\u9898\u8BB0\u5F55"
commnet: 1
date: 2020-04-26 16:20
html: "<details><summary>\u67E5\u770B\u539F\u9898</summary><div id='from'></div><p><button\
  \ onclick=\"document.getElementById('from').innerHTML='<iframe src=&quot;https://www.luogu.com.cn/problem/CF1313D&quot;\
  \ width=100% height=800px style=&quot;border: none;&quot;><iframe>'\" class='mdui-btn\
  \ mdui-btn-raised mdui-ripple'>\u70B9\u51FB\u52A0\u8F7D</button><a class='mdui-btn\
  \ mdui-btn-raised mdui-ripple' href=\"https://www.luogu.com.cn/problem/CF1313D\"\
  \ target='_blank'>\u70B9\u51FB\u8DF3\u8F6C</a><p></details>"
permalink: LG CF1313D Happy New Year
tags:
- "\u72B6\u538Bdp"
- "\u52A8\u6001\u89C4\u5212"
thumbnail: null
title: LG CF1313D Happy New Year
top: 0
---
设$f_{i,j}$表示前$i$个点,第$i$个点的覆盖状态为$j$($j$为$8$位二进制数)


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
