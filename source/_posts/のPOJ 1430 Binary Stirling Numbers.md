---
author: zc
avatar: null
categories:
- - 刷题记录
commnet: 1
date: 2020-07-10 18:50
html: '<details><summary>查看原题</summary><div id=''from''></div><p><button onclick="document.getElementById(''from'').innerHTML=''<iframe
  src=&quot;&quot; width=100% height=800px style=&quot;border: none;&quot;><iframe>''"
  class=''mdui-btn mdui-btn-raised mdui-ripple''>点击加载</button><a class=''mdui-btn
  mdui-btn-raised mdui-ripple'' href="" target=''_blank''>点击跳转</a><p></details>'
permalink: POJ 1430 Binary Stirling Numbers
tags:
- 第二类斯特林数
- 组合数
- 数论
- lucas
thumbnail: null
title: POJ 1430 Binary Stirling Numbers
top: 0

---
此题要求的是$S(n,m) \mod 2$(第二类斯特林数)

1. 当$m$为偶数,$S(n,m) \equiv S(n-1,m-1)$

2. 当$m$为奇数,$S(n,m) \equiv S(n-1,m-1)+s(n-1,m)$

这样的话,相当于:

1. 当$(x,y)$中$y$为奇数时,可以走到$(x+1,y+1)$(a变换)

2. 否则可以走到$(x+1,y+1)$(a变换),或$(x+1,y)$(b变换)

求从$(0,0)$走到$(n,m)$的方案数$\pmod 2$

这个过程必然走了$m$次$a$变换,走了$n-m$次$b$变换

而$b$变换只能在偶数位置出现,那么变换的序列必然是如下形式:

$a,b\times ?,a,a,b\times ?,a,a,...,a$

也就是在$\frac {m+1}2$个间隔中插入$n-m$个$b$,即隔板法

方案数:$C(n-m+\frac{m+1}2-1,\frac{m+1}2 -1) \mod 2$

还有一个结论:仅当$n\&m=m$时,$C(n,m) \equiv 1 \bmod 2$(lucas定理代入即可推出)
```cpp
#include<cstdio>
bool C(int n,int m){
    return (n&m)==m;
}
int main(){
    int T;scanf("%d",&T);
    while(T--){
        int n,m;
        scanf("%d%d",&n,&m);
        if(!n&&!m)puts("1");
        else if(!n||!m||n<0)puts("0");
        else{
            int b=n-m,a=(m+1)>>1;
            puts(C(b+a-1,a-1)?"1":"0");
        }
    }
}
```
