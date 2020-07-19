---
title: exgcd
copyright: true
date: 2019-01-21 11:31:55
tags:
- exgcd
- 数论
- 算法
- 逆元
categories:
  - [算法,数论]
  - [note]
permalink:
top:
password:
thumbnail:
---



转自https://www.cnblogs.com/hadilo/p/5914302.html

## 欧几里得

### 定义:

$gcd(a,b)$为整数$a$与$b$的最大公约数

### 引理：

$gcd(a,b)=gcd(b,a \bmod b)$

### 证明：

设$r=a \bmod b , c=gcd(a,b)$

则$a=xc,b=yc$, 其中$x,y$互质

$r=a \bmod b=a-pb=xc-pyc=(x-py)c$

而$b=yc$

可知：$y$与 $x-py$互质

#### 证明：

假设$y$与$x-py$不互质

设$y=nk,x-py=mk$, 且$k>1$（因为互质）

将$y$带入可得

$x-pnk=mk$

$x=(pn+m)k$

则$a=xc=(pn+m)kc,b=yc=nkc$

那么此时$a$与$b$的最大公约数为$kc$不为$k$

与原命题矛盾,则$y$与$x-py$互质

因为$y$与$x-py$互质,所以$r$与$b$的最大公约数为$c$

即$gcd(b,r)=c=gcd(a,b)$

得证

当$a\mod b=0$时,$gcd(a,b)=b$

这样我们可以写成递归形式

### 实现：

```cpp
int gcd(int a,int b){
    return b?gcd(b,a%b):a;
}
```

## 扩展欧几里得

### 引理：

存在$x,y$ 使得$gcd(a,b)=ax+by$

### 证明：

当 $b=0$ 时,$gcd(a,b)=a,此时 x=1 , y=0$
当 $b \neq  0$ 时,设

$ax+by=gcd(a,b)=gcd(b,a \bmod b)=b{x}'+(a \bmod b){y}'$

$\because a \bmod b = a-a/b*b$

$\therefore ax+by=b{x}'+(a-a/b*b){y}'$

$\therefore ax+by=b{x}'+a{y}'-b*a/b*{y}'$

$\therefore ax+by=a{y}'+b{x}'-b*a/b*{y}'$

$\therefore ax+by=a{y}'+b({x}'-a/b*{y}')$

$解得 x={y}' , y={x}'-a/b*{y}'$

当$b=0$时存在$x,y$为最后一组解

### 实现：

递归进入下一层,当$b=0$时就返回$x=1,y=0$

再根据$x=y' , y={x}'-a/b*y'$得出当前所在层的解

回到第一层的时候得到答案。

```cpp
int x,y;
void exgcd(int a,int b){
    if(!b){x=1,y=0;return;}
    exgcd(b,a%b);
    int t=x;x=y;y=t-a/b*y;
}
```
## LG 1082 同余方程

> 求关于$x$的同余方程$ax \equiv 1 \pmod b$的最小正整数解。

$ax \equiv 1 \pmod b$可以转化为$ax+by=1$

方程$ax + by = m$有解的必要条件是$m \mod \gcd(a,b) = 0$。

$\therefore \gcd(a,b) = 1$,即$a,b$互质

用扩展欧几里得求$ax+by=\gcd(a,b)$的解即可

我们求出来的$x$必然满足方程,但是不一定是最小正整数解

> $ax+by=1$
> 
> $ax+by+k\times ba-k\times ba=1$
> 
> $a(x+kb)+(y-ka)b=1$

所以$x+=b$或$x-=b$不会使$x$错过任何解

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll x,y;
void exgcd(ll a,ll b){
    if(!b){
        x=1,y=0;
        return;
    }
    exgcd(b,a%b);
    int t=x;
    x=y;
    y=t-a/b*y;
}
int main(){
    ll a,b;
    cin>>a>>b;
    exgcd(a,b);
    while(x<0)x+=b;
    x%=b;
    cout<<x<<endl;
}
```
