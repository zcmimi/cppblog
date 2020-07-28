---
author: zc
avatar: null
categories:
- - 刷题记录
commnet: 1
date: 2020-04-26 01:05
html: '<details><summary>查看原题</summary><div id=''from''></div><p><button onclick="document.getElementById(''from'').innerHTML=''<iframe
  src=&quot;https://www.luogu.com.cn/problem/CF1312D&quot; width=100% height=800px
  style=&quot;border: none;&quot;><iframe>''" class=''mdui-btn mdui-btn-raised mdui-ripple''>点击加载</button><a
  class=''mdui-btn mdui-btn-raised mdui-ripple'' href="https://www.luogu.com.cn/problem/CF1312D"
  target=''_blank''>点击跳转</a><p></details>'
permalink: LG CF1312D Count the Arrays
tags:
- 数论
- 组合数
thumbnail: null
title: LG CF1312D Count the Arrays
top: 0
---
首先,确定最大值和唯一一对的相同的元素

这对元素分别放在最大值的左边和右边

剩下的$n-3$个元素,有两种选择:

1. 放在最大值左边
2. 放在最大值右边

那么就有$2^{n-3}$种方案

从$[1,m]$中选取$n-1$个不相同的元素,有$m \choose {n-1}$种方案

接着在这$n-1$个元素中选取一个非最大值的元素作为唯一相同那一对,有$n-2$种方案

那么最终答案就是$2^{n-3} \times {m \choose{n-1}} \times (n-2)$

```cpp
#include<bits/stdc++.h>
const int P=998244353;
int pw(int x,int b){
    int res=1;
    while(b){
        if(b&1)res=1ll*res*x%P;
        b>>=1,x=1ll*x*x%P;
    }
    return res;
}
int fac(int x){
    int ans=1;
    for(int i=2;i<=x;++i)ans=1ll*ans*i%P;
    return ans;
}
int C(int n,int m){
    if(n<m)return 0;
    return 1ll*fac(n)*pw(fac(m),P-2)%P*pw(fac(n-m),P-2)%P;
}
int main(){
    int n,m;
    scanf("%d%d",&n,&m);
    if(n<=2){printf("0\n");return 0;}
    printf("%d\n",1ll*pw(2,n-3)*C(m,n-1)%P*(n-2)%P);
}
```
