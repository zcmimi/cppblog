---
author: zc
avatar: null
categories:
- - "\u5237\u9898\u8BB0\u5F55"
commnet: 1
date: 2020-03-19 19:22
html: "<details><summary>\u67E5\u770B\u539F\u9898</summary><div id='from'></div><p><button\
  \ onclick=\"document.getElementById('from').innerHTML='<iframe src=&quot;https://www.luogu.com.cn/problem/P3935&quot;\
  \ width=100% height=800px style=&quot;border: none;&quot;><iframe>'\" class='mdui-btn\
  \ mdui-btn-raised mdui-ripple'>\u70B9\u51FB\u52A0\u8F7D</button><a class='mdui-btn\
  \ mdui-btn-raised mdui-ripple' href=\"https://www.luogu.com.cn/problem/P3935\" target='_blank'>\u70B9\
  \u51FB\u8DF3\u8F6C</a><p></details>"
permalink: LG 3935 Calculating
tags:
- "\u6570\u8BBA"
- "\u6570\u8BBA\u5206\u5757"
thumbnail: null
title: LG 3935 Calculating
top: 0
---
若$x$分解质因数结果为$x=p_1^{k_1}p_2^{k_2}\cdots p_n^{k_n}$

令$f(x)=(k_1+1)(k_2+1)\cdots (k_n+1)$

$f(x)$其实就是$d(x)$,$x$的约数个数

> $p_1^{k_1}$的约数有$1,p_1,p_1^2,\cdots,p_1^{k_1}$
> 
> $p_2^{k_2}$的约数有$1,p_2,p_2^2,\cdots,p_2^{k_2}$
> 
> $\cdots$
> 
> $p_n^{k_n}$的约数有$1,p_n,p_n^2,\cdots,p_n^{k_n}$
> 
> 根据乘法原理,$d(x)=(k_1+1)(k_2+1)\cdots (k_n+1)$

首先可以想到的是

$$
\sum_{i=l}^r f(i)=\sum_{i=1}^r f(i) - \sum_{i=1}^{l-1} f(i)
$$

那么

$$
\sum_{i=1}^n f(i)
\\
=\sum_{i=1}^n \sum_{j|i}1
$$

换个枚举顺序

$$
=\sum_{j=1}^n \sum_{j|i}1
\\
=\sum_{j=1}^n \left \lfloor \frac nj\right \rfloor
$$

最后数论分块就可以了

```cpp
#include<cstdio>
const int P=998244353;
typedef long long ll;
int calc(ll n){
    int res=0;
    for(ll l=1,r,i;l<=n;l=r+1){
        i=n/l;r=n/i;
        (res+=(r-l+1)*i%P)%=P;
    }
    return res;
}
int main(){
    ll l,r;scanf("%lld%lld",&l,&r);
    printf("%d\n",(calc(r)-calc(l-1)+P)%P);
}
```
