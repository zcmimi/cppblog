---
title: Lucas
date: 2020-03-02
tags: 
- 数论
- 组合数
- 算法
- 二进制

categories:
  - [算法,数论]
  - [note]
---

## Lucas定理

$$C_n^m\pmod p\equiv C_{n\mod p}^{m\mod p} \cdot C_{\lfloor n/p\rfloor}^{\lfloor m/p\rfloor}\pmod p$$

就是一个组合数可以拆成P进制下的乘积

这个算法可以处理当m,n非常大而$p$较小的时候的取模

```cpp
int C(int n,int m){
    if(n<m)return 0;
    return 1ll*fac[n]*inv(fac[m])%p*inv(fac[n-m])%p;
}
int lucas(int n,int m){
    if(n<m)return 0;
    if(!n)return 1;
    return 1ll*lucas(n/p,m/p)*C(n%p,m%p)%p;
}
```

扩展：仅当$(n\&m)=m$时,$C(n,m) \equiv 1 \bmod 2$

## 扩展lucas

当模数$p$过大或者$p$不是质数的时候就不能直接用lucas了

似乎扩展lucas和lucas没太大关系,会`exgcd`和`crt`就可以了

设$p=p_1^{k_1}p_2^{k_2}\dots p_n^{k_n}$

求出每个${n\choose m} \equiv a_i \pmod {p_i^{k_i}}$

得到同余方程组

$$
\begin{cases}
{n\choose m} \equiv a_1 \pmod {p_1^{k_1}}
\\
{n\choose m} \equiv a_2 \pmod {p_1^{k_2}}
\\
\vdots
\\
{n\choose m} \equiv a_n \pmod {p_n^{k_n}}
\end{cases}
$$

使用`crt`即可求出$n\choose m$的值

$p^t$不是质数,那么如何求${n\choose m} \mod p^t$呢?

可以计算${n\choose m}=\frac{n!}{m!(n-m)!}$,分别计算出$n!,m!,(n-m)!$在模$p^t$意义下的值

假设$p=3,t=2,n=19$,

$$
n!=1\cdot 2\cdot 3\cdots 19
\\
=(1\cdot 2\cdot 4\cdot 5\cdot 7\cdot 8\cdot 10\cdot 11\cdot 13\cdot 14\cdot 16\cdot 17\cdot 19)\cdot (3\cdot 6\cdot 9\cdot 12\cdot 15\cdot 18)
\\ 
=(1\cdot 2\cdot 4\cdot 5\cdot 7\cdot 8\cdot 10\cdot 11\cdot 13\cdot 14\cdot 16\cdot 17\cdot 19)\cdot 3^6\cdot(1\cdot2\cdot3\cdot4\cdot5\cdot6)
$$

可以发现后面的部分相当于$\left\lfloor \frac np \right\rfloor!$,递归计算即可

前半部分以$p^t$为周期,即

$1\cdot 2\cdot 4\cdot 5\cdot 7\cdot 8 \equiv 10\cdot 11\cdot 13\cdot 14\cdot 16\cdot 17 \pmod {3^2}$

只需要计算不满足周期的数$19$就可以了