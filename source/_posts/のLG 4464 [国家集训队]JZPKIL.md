---
author: zc
avatar: null
categories:
- - 刷题记录
commnet: 1
date: 2020-07-10 18:50
html: '<details><summary>查看原题</summary><div id=''from''></div><p><button onclick="document.getElementById(''from'').innerHTML=''<iframe
  src=&quot;https://www.luogu.com.cn/problem/P4464&quot; width=100% height=800px style=&quot;border:
  none;&quot;><iframe>''" class=''mdui-btn mdui-btn-raised mdui-ripple''>点击加载</button><a
  class=''mdui-btn mdui-btn-raised mdui-ripple'' href="https://www.luogu.com.cn/problem/P4464"
  target=''_blank''>点击跳转</a><p></details>'
permalink: LG 4464 [国家集训队]JZPKIL
tags:
- 莫比乌斯
- 数论
thumbnail: null
title: LG 4464 [国家集训队]JZPKIL
top: 0

---
$$
\begin{aligned}
&\quad\sum_{i=1}^n \gcd(i,n)^x lcm(i,n)^y
\\
&=\sum_{i=1}^n \frac{in}{lcm(i,n)}^x lcm(i,n)^y
\\
&=\sum_{i=1}^n (in)^x lcm(i,n)^{y-x}
\\
&=\sum_{i=1}^n (in)^x \frac{in}{\gcd(i,n)}^{y-x}\\
&=\sum_{i=1}^n (in)^y \gcd(i,n)^{x-y}
\\
&=n^y\sum_{d=1}^n d^{x-y}\sum_{i=1}^n i^y [\gcd(i,n)=d]
\\
&=n^y\sum_{d=1}^n d^{x-y}\sum_{i=1}^{n/d} (id)^y [\gcd(i,n)=1]
\\
&=n^y\sum_{d=1}^n d^{x-y}\sum_{i=1}^{n/d} (id)^y \sum_{k|i,k|n}\mu(k)
\\
&=n^y\sum_{d=1}^n d^{x-y}\sum_{k=1}^{n/d}\mu(k)\sum_{i=1}^{n/dk} (idk)^y
\end{aligned}
$$

设$T=dk$

$$
=n^y\sum_{T=1}^n\sum_{d|T}d^{x-y}\mu(\frac Td)\sum_{i=1}^{n/T} (iT)^y
$$
```cpp
#include<bits/stdc++.h>
#define fur(i,x,y) for(int i=x;i<=y;++i)
void cmin(int &x,int y){if(x>y)x=y;}
int rd(){int x=0;char c;bool f=0;for(c=getchar();c<'0'||'9'<c;c=getchar())f^=c=='-';for(x=c-48,c=getchar();'0'<=c&&c<='9';x=x*10+c-48,c=getchar());return f?-x:x;}
const int N=100011,inf=2122219134;
int main(){
    
}
```
