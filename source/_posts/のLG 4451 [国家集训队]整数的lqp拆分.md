---
author: zc
avatar: null
categories:
- - 刷题记录
commnet: 1
date: 2020-07-10 18:50
html: '<details><summary>查看原题</summary><div id=''from''></div><p><button onclick="document.getElementById(''from'').innerHTML=''<iframe
  src=&quot;https://www.luogu.com.cn/problem/P4451&quot; width=100% height=800px style=&quot;border:
  none;&quot;><iframe>''" class=''mdui-btn mdui-btn-raised mdui-ripple''>点击加载</button><a
  class=''mdui-btn mdui-btn-raised mdui-ripple'' href="https://www.luogu.com.cn/problem/P4451"
  target=''_blank''>点击跳转</a><p></details>'
permalink: LG 4451 [国家集训队]整数的lqp拆分
tags:
- 生成函数
- 数论
- 斐波那契
- 二次剩余
thumbnail: null
title: LG 4451 [国家集训队]整数的lqp拆分
top: 0

---
拆分为$m$项时,生成函数为$F^m (x)$

那么答案的生成函数为$\displaystyle G(x)=\sum_{i=0}^{\infin} F^i(x)$

$F$为斐波那契数列生成函数,$\displaystyle F(x)=\frac x{1-x-x^2}$

$
\begin{aligned}
G(x)
&=\sum_{i=0}^{\infty} F^i(x)\\
&=\frac 1{1-F(x)}\\
&=\frac {1-x-x^2}{1-2x-x^2}\\
&=1+\frac x{1-2x-x^2}\\
&=1+\frac x{[1-(1+\sqrt 2)x][1-(1-\sqrt2)x]}\\
&=1+\frac 1{2\sqrt 2}\left( \frac 1{1-(1+\sqrt 2)x} - \frac 1{1-(1-\sqrt 2)x} \right)\\
&=1+\sum_{i=1}^{\infin} \frac{(1+\sqrt 2)^i-(1-\sqrt 2)^i}{2\sqrt 2} x^i
\end{aligned}
$

那么:

$\displaystyle
ans_n=\frac{(1+\sqrt 2)^n-(1-\sqrt 2)^n}{2\sqrt 2}
$

其中$\sqrt 2 \equiv 59713600 \pmod{10^9+7}$(二次剩余)

这样的话:

$\displaystyle
\begin{aligned}
ans_n
&=\frac {\sqrt 2}4\left[(1+\sqrt 2)^n-(1-\sqrt 2)^n\right]\\
&\equiv 59713600\times 250000002\times [(1+59713600)^n-(1-59713600)^n] \pmod{10^9+7}
\end{aligned}
$

使用快速幂复杂度$O(\log n)$

考虑费马小定理: $ans_n \equiv ans_{n \mod 10^9+6}$

这样就可以把$n$压到$10^9+6$以内了,再快速幂即可
```cpp
#include<cstdio>
const int P=1000000007;
int n;
void readn(){
    char c;int p=P-1;
    for(c=getchar();c<'0'||'9'<c;c=getchar());
    for(n=c-48,c=getchar();'0'<=c&&c<='9';n=(10ll*n+c-48)%p,c=getchar());
}
int pw(int x,int b){
    int res=1;
    while(b){
        if(b&1)res=1ll*res*x%P;
        b>>=1,x=1ll*x*x%P;
    }
    return res;
}
int main(){
    readn();
    int t=1ll*59713600*250000002%P,
        a=(pw(59713601,n)-pw(940286408,n)+P)%P;
    printf("%d\n",1ll*t*a%P);
}
```
