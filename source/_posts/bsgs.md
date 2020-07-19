---
date: 2020-02-19
tags:
- 数论
- 算法

categories:
  - [算法,数论]
  - [note]
---

求解关于$x$的方程: 

$$y^x \equiv z \pmod p$$

## bsgs

当$\gcd(y,p)=1$时

解法: 

设$x=am-b$

那么$y^{am} \equiv z\cdot a^b \pmod p$

右边: 

枚举$b$的取值$[0,m-1]$,计算右边的值,存入哈希表

左边:

枚举可能的$a$,也就是$[1,m]$,若左边的值在哈希表中出现过,那么当前$a$合法

不难证明当$m=\sqrt p$的时候复杂度最优,$\Theta(\sqrt p)$

关键代码:

```cpp
a%=p;
if(!a){
    if(!b)out("1\n");
    else out("Orz, I cannot find x!\n");
    continue;
}
int m=sqrt(p)+1,x=b%p,t=pw(a,m);
S.clear();
S.ins(x,0);
Fur(i,1,m)x=1ll*x*a%p,S.ins(x,i);
x=1;
bool ff=1;
Fur(i,1,m){
    x=1ll*x*t%p;
    int k=S[x];
    if(~k){
        ff=0;
        out(((i*m-k)%p+p)%p,ln);
        break;
    }
}
if(ff)out("Orz, I cannot find x!\n");
```

## ex bsgs

当$\gcd(y,p)\not =1$时

$$
y^x+kp=z
$$

令$d=\gcd(y,p)$

可以发现当$d|z$时才有解

除去$d$

$$
\frac ydy^{x-1}+k\frac pd=\frac zd
$$

就这样一直递归,除去$d$,直到$d=1$

假设递归了$c$次,所有$d$乘积为$g$,那么

$$
\frac {y^c}g y^{x-c}+k\frac pg=\frac zg
$$
也就是
$$
y^{x-c} \frac {y^c}g \equiv \frac zg \pmod{\frac pg}
$$
于是可以bsgs求解

关键代码: 

```cpp
void exbsgs(int y,int z,int p){
    if(z==1)return void(out("0\n"));
    int k=0,a=1;
    while(1){
        int d=GCD(y,p);
        if(d==1)break;
        if(z%d)return void(out("No Solution\n"));
        z/=d;p/=d;
        ++k;
        a=1ll*a*y/d%p;
        if(z==a)return void(out(k,ln));
    }
    S.clear();
    int m=sqrt(p)+1,x=z,f=pw(y,m,p);
    Fur(i,0,m-1)S.ins(x,i),x=1ll*x*y%p;
    x=1ll*a*f%p;
    Fur(i,1,m){
        int b=S[x];
        if(~b)return void(out(i*m-b+k,ln));
        x=1ll*x*f%p;
    }
    out("No Solution\n");
}
```

## 例题

[LG 4884 多少个1?](https://www.luogu.com.cn/problem/P4884)

$$
\overbrace{111\dots111}^{\text{N个1}} \equiv k \pmod m
\\
\frac{10^N-1}9\equiv k \pmod m
\\
10^N\equiv 9k+1 \pmod m
$$

顺利地推出是bsgs,($m$是质数,也就不用exbsgs了)