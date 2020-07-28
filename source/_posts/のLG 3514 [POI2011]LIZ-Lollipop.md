---
author: zc
avatar: null
categories:
- - 刷题记录
commnet: 1
date: 2020-06-13 11:22
html: '<details><summary>查看原题</summary><div id=''from''></div><p><button onclick="document.getElementById(''from'').innerHTML=''<iframe
  src=&quot;https://www.luogu.com.cn/problem/P3514&quot; width=100% height=800px style=&quot;border:
  none;&quot;><iframe>''" class=''mdui-btn mdui-btn-raised mdui-ripple''>点击加载</button><a
  class=''mdui-btn mdui-btn-raised mdui-ripple'' href="https://www.luogu.com.cn/problem/P3514"
  target=''_blank''>点击跳转</a><p></details>'
permalink: LG 3514 [POI2011]LIZ-Lollipop
tags:
- 前缀和
- 思维
thumbnail: null
title: LG 3514 [POI2011]LIZ-Lollipop
top: 0
---
逆推

若当前区间$[l,r]$和为$x$,考虑如何得到和为$x-2$的区间:

1. $a_l=2 \rightarrow [l+1,r]$
2. $a_r=2 \rightarrow [l,r-1]$
3. $a_l=a_r=1 \rightarrow [l+1,r-1]$

这样我们求出区间 最大奇数和 与 最大偶数和,就可以预处理出所有$x$的答案了
```cpp
#include<bits/stdc++.h>
const int N=1000001;
int n,q,a[N],s[N],L[N*2],R[N*2];
char c[N];
void solve(int v){
    while(v>2){
        L[v-2]=L[v]+1,R[v-2]=R[v]-1;
        if(a[L[v]]==2)R[v-2]=R[v];
        else if(a[R[v]]==2)L[v-2]=L[v];
        v-=2;
    }
}
int main(){
    int t1=0,t2=0,v;
    scanf("%d%d%s",&n,&q,c+1);
    for(int i=1;i<=n;++i)
        a[i]=1+(c[i]=='T'),
        s[i]=s[i-1]+a[i];
    v=s[n],L[v]=1,R[v]=n,solve(v);
    for(int i=1;i<=n;++i)if(a[i]==1){t1=i+1;break;}
    for(int i=n;i;--i)if(a[i]==1){t2=i-1;break;}
    if((!t1&&t2)||s[t2]>s[n]-s[t1-1])
        v=s[t2],L[v]=1,R[v]=t2;
    else if(t1)
        v=s[n]-s[t1-1],L[v]=t1,R[v]=n;
    solve(v);
    while(q--){
        int x;scanf("%d",&x);
        if(!L[x])printf("NIE\n");
        else printf("%d %d\n",L[x],R[x]);
    }
}
```
