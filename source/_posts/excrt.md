---
title: excrt
date: 2020-03-07 15:50
author:
avatar:
tags:
 - 算法
 - 数论
categories:
  - [算法,数论]
  - [note]
thumbnail:
top: 0
comment: 1
---

# 扩展中国剩余定理

给定方程组:

$$
\begin{cases}
x \equiv a_1\ ({\rm mod}\ m_1)
\\
x\equiv a_2\ ({\rm mod}\ m_2)
\\
...
\\
x \equiv a_n\ ({\rm mod}\ m_n)
\end{cases}
$$

求最小的非负整数$x$

假设我们求出了前$i-1$组的解$x_{i-1}$

设$M=\operatorname{lcm}(m_1,m_2,\cdots,m_{i-1})$

则$x_{i-1}+\lambda M \equiv a_{i-1} \pmod{m_{i-1}}(\lambda \in \Z)$

那么我们需要求出最小的非负整数$t$使:

$x_{i-1}+tM\equiv a_i \pmod{m_i}$

也就是$Mt\equiv a_i-x_{i-1} \pmod{m_i}$

可以使用Exgcd求解$t$ ($ax\equiv c \pmod b$)

如果无解,则整个方程误解

若有解,$x_i=x_{i-1}+tM$

[LG P4777 【模板】扩展中国剩余定理（EXcrt）](https://www.luogu.com.cn/problem/P4777)

代码:

```cpp
const int N=100011;
int n;ll m[N],a[N];
ll exgcd(ll a,ll b,ll &x,ll &y){
    if(!b){x=1,y=0;return a;}
    ll gcd=exgcd(b,a%b,x,y),t=x;
    x=y;y=t-a/b*y;
    return gcd;
}
ll mul(ll x,ll b,ll p){
    ll ans=0;
    while(b){
        if(b&1)ans=(ans+x)%p;
        b>>=1;x=(x+x)%p;
    }
    return ans;
}
ll excrt(){
    ll ans=a[1],M=m[1],t,y;
    Fur(i,2,n){
        ll b=m[i],c=(a[i]-ans%b+b)%b,
            gcd=exgcd(M,b,t,y);
        if(c%gcd)return -1;
        t=mul(t,c/gcd,b/gcd);
        ans+=t*M;
        M*=b/gcd;
        ans=(ans%M+M)%M;
    }
    return ans;
}
int main(){
    in(n);
    Fur(i,1,n)in(m[i],a[i]);
    printf("%lld\n",excrt());
}
```