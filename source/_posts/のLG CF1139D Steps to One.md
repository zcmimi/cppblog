---
author: zc
avatar: null
categories:
- - 刷题记录
commnet: 1
date: 2020-06-11 16:49
html: '<details><summary>查看原题</summary><div id=''from''></div><p><button onclick="document.getElementById(''from'').innerHTML=''<iframe
  src=&quot;https://www.luogu.com.cn/problem/CF1139D&quot; width=100% height=800px
  style=&quot;border: none;&quot;><iframe>''" class=''mdui-btn mdui-btn-raised mdui-ripple''>点击加载</button><a
  class=''mdui-btn mdui-btn-raised mdui-ripple'' href="https://www.luogu.com.cn/problem/CF1139D"
  target=''_blank''>点击跳转</a><p></details>'
permalink: LG CF1139D Steps to One
tags:
- 莫比乌斯
- 数论
- 期望
- 思维
thumbnail: null
title: LG CF1139D Steps to One
top: 0
---
设$f_i$表示所有数$\gcd$为$i$还要加入的数的期望数量

$$ans=1+\frac{\sum_{i=1}^mf_i}m$$

可以知道$f_1=0$

$$f_i=1+\frac{\sum_{j=1}^m f_{\gcd(i,j)}}m(i>1)$$

继续推式子:

$$
\begin{aligned}
f_i
&=1+\frac{\sum_{j=1}^m f_{\gcd(i,j)}}m\\
&=1+\frac{\sum_{d|i} f_d\sum_{j=1}^m [\gcd(i,j)=d]}m
\end{aligned}
$$

把分子拿出来

$$
\begin{aligned}
&\quad\sum_{d|i} f_d\sum_{j=1}^m [\gcd(i,j)=d]\\
&=\sum_{d|i} f_d\sum_{j=1}^{m/d} [\gcd(\frac id,j)=1]\\
&=\sum_{d|i} f_d\sum_{j=1}^{m/d} \sum_{x|\frac id,x|j}\mu(x)\\
&=\sum_{d|i} f_d \sum_{x|\frac id}\sum_{j=1}^{m/dx}\mu(x)\\
&=\sum_{d|i} f_d \sum_{x|\frac id}\mu(x)\left \lfloor \frac m{dx}\right\rfloor\\
\end{aligned}\\
$$

设$T=dx$

$$
=\sum_{T|i}\sum_{d|T} f_d \mu(\frac Td)\left \lfloor \frac mT\right\rfloor
$$

带入原来的式子

$$
f_i=1+\frac{\sum_{T|i}\left \lfloor \frac mT\right\rfloor\sum_{d|T} f_d \mu(\frac Td)}m
$$

设$F_T=\sum_{d|T} f_d \mu(\frac Td)$

当$d\not = i$时可以每算出一个$f_i$就更新所有$F_x(i|x)$

当$d=i$时没法直接更新,这时$T=d=i,\mu(\frac Td)=\mu(1)=1$

$$
f_i=1+\frac{\sum_{T|i}\left \lfloor \frac mT\right\rfloor\sum_{d|T} f_d \mu(\frac Td)[d\not=i]}m+\frac{f_i\left\lfloor \frac mi \right\rfloor}m
\\
f_i-\frac{f_i\left\lfloor \frac mi \right\rfloor}m=\frac{m+\sum_{T|i}\left \lfloor \frac mT\right\rfloor\sum_{d|T} f_d \mu(\frac Td)[d\not=i]}m
\\
f_i\frac{m-\left\lfloor\frac mi \right\rfloor}m=\frac{m+\sum_{T|i}\left \lfloor \frac mT\right\rfloor\sum_{d|T} f_d \mu(\frac Td)[d\not=i]}m
\\
f_i=\frac{m+\sum_{T|i}\left \lfloor \frac mT\right\rfloor\sum_{d|T} f_d \mu(\frac Td)[d\not=i]}{m-\left\lfloor\frac mi \right\rfloor}
$$

这样就可以先算$f_i$,再算$F_i$了

$[d\not=i]$这个条件只在$T=i$的时候才有限制

枚举到$T=i$,计算$f_i$时,$F_x(x<i)$都已经计算好了

$F_i$还少了$f[i] \times \mu(1)$

这正好是要剪掉的部分

```cpp
#include<bits/stdc++.h>
using std::list;
const int N=100011,P=1000000007;
int n,F[N],pri[N],mu[N],tt,inv[N],ans=1;
bool v[N];
list<int>d[N];
int m(int x){return x>=P?x-P:(x<0?x+P:x);}
int main(){
    scanf("%d",&n);
    mu[1]=1;
    for(int i=2;i<=n;++i){
        if(!v[i])pri[++tt]=i,mu[i]=-1;
        for(int j=1;j<=tt&&i*pri[j]<=n;++j){
            v[i*pri[j]]=1;
            if(i%pri[j]==0)break;
            mu[i*pri[j]]=-mu[i];
        }        
    }
    for(int i=1;i<=n;++i)
        for(int j=i;j<=n;j+=i)
            d[j].push_back(i);
    inv[1]=1;
    for(int i=2;i<=n;++i)
		inv[i]=1ll*(P-P/i)*inv[P%i]%P;
    
    for(int i=2;i<=n;++i){
        int f=n;
        for(auto T:d[i])
            f=(f+1ll*n/T*F[T])%P;
        f=1ll*f*inv[n-n/i]%P;
        ans=m(ans+f+1);
        for(int j=1,k=i;k<=n;++j,k+=i)
            F[k]=m(F[k]+f*mu[j]);
    }
    printf("%d\n",1ll*ans*inv[n]%P);
}
```
