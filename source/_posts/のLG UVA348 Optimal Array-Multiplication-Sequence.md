---
author: zc
avatar: null
categories:
- - "\u5237\u9898\u8BB0\u5F55"
commnet: 1
date: 2019-12-21 19:47
html: "<details><summary>\u67E5\u770B\u539F\u9898</summary><div id='from'></div><p><button\
  \ onclick=\"document.getElementById('from').innerHTML='<iframe src=&quot;https://www.luogu.com.cn/problem/UVA348&quot;\
  \ width=100% height=800px style=&quot;border: none;&quot;><iframe>'\" class='mdui-btn\
  \ mdui-btn-raised mdui-ripple'>\u70B9\u51FB\u52A0\u8F7D</button><a class='mdui-btn\
  \ mdui-btn-raised mdui-ripple' href=\"https://www.luogu.com.cn/problem/UVA348\"\
  \ target='_blank'>\u70B9\u51FB\u8DF3\u8F6C</a><p></details>"
permalink: LG UVA348 Optimal Array-Multiplication-Sequence
tags:
- dfs
thumbnail: null
title: LG UVA348 Optimal Array-Multiplication-Sequence
top: 0
---
记忆化搜索
```cpp
#include<bits/stdc++.h>
#define N 15
int n,f[N][N],g[N][N],cnt;
struct node{
    int al,ar,yk,zk;
}a[N];
void init(){
    memset(a,0,sizeof(a));
    memset(g,0,sizeof(g));
    memset(f,0x3f,sizeof(f));
    for(int i=1;i<=n;++i)scanf("%d %d",&a[i].al,&a[i].ar);
}
int solve(int l,int r){
    if(f[l][r]!=0x3f3f3f3f)return f[l][r];
    if(l>=r)return f[l][r]=0;
    int pos=0;
    for(int k=l;k<r;++k){
        int temp=solve(l,k)+solve(k+1,r)+a[l].al*a[k].ar*a[r].ar;
        if(temp<f[l][r])pos=k,f[l][r]=temp;
    }
    g[l][r]=pos;
    return f[l][r];
}
void dfs(int l,int r){
    if(l==r)return ;
    a[l].zk++,a[r].yk++;
    dfs(l,g[l][r]),dfs(g[l][r]+1,r);
}
void out(){
    printf("Case %d: ",++cnt);
    for(int i=1;i<=n;++i){
        if(i!=1)printf(" x ");
        while(a[i].zk)putchar('('),a[i].zk--;
        printf("A%d",i);
        while(a[i].yk)putchar(')'),a[i].yk--;
    }
    putchar('\n');
}
int main(){
    while(scanf("%d",&n)&&n){
        init();
        solve(1,n);
        dfs(1,n);
        out();
    }
}
```
