---
author: zc
avatar: null
categories:
- - 刷题记录
commnet: 1
date: 2019-12-21 19:47
html: '<details><summary>查看原题</summary><div id=''from''></div><p><button onclick="document.getElementById(''from'').innerHTML=''<iframe
  src=&quot;https://www.luogu.com.cn/problem/CF767C&quot; width=100% height=800px
  style=&quot;border: none;&quot;><iframe>''" class=''mdui-btn mdui-btn-raised mdui-ripple''>点击加载</button><a
  class=''mdui-btn mdui-btn-raised mdui-ripple'' href="https://www.luogu.com.cn/problem/CF767C"
  target=''_blank''>点击跳转</a><p></details>'
permalink: LG CF767C Garland
tags:
- 树形dp
- 动态规划
thumbnail: null
title: LG CF767C Garland
top: 0
---
```cpp
#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<cmath>
using namespace std;
const int maxn=1000010;
int n,t[maxn],root,cnt,sum,ans[5];
int ver[2*maxn],head[maxn*2],nxt[maxn*2],tem[maxn],tot;
void add(int x,int y){
    tot++;
    ver[tot]=y;
    nxt[tot]=head[x];
    head[x]=tot;
}
void dfs(int x,int y){
    tem[x]=t[x];
    for(int i=head[x];i;i=nxt[i]){
        int v=ver[i];
        if(v!=y){
            dfs(v,x);
            tem[x]+=tem[v];
        }
    }
    if(tem[x]==sum) ans[++cnt]=x,tem[x]=0;
}
int main(){
    int a;
    scanf("%d",&n);
    for(int i=1;i<=n;i++) {
        scanf("%d %d",&a,&t[i]);
        if(a) add(a,i),add(i,a);
        else root=i;
        sum+=t[i];
    }
    if(sum%3){
        puts("-1");
        return 0;
    }
    sum/=3;
    dfs(root,0);
    if(cnt<=2) puts("-1");
    else printf("%d %d\n",ans[1],ans[2]);
    return 0;
}
```
