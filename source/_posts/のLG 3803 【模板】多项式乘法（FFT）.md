---
author: zc
avatar: null
categories:
- - 刷题记录
commnet: 1
date: 2020-02-05 12:21
html: '<details><summary>查看原题</summary><div id=''from''></div><p><button onclick="document.getElementById(''from'').innerHTML=''<iframe
  src=&quot;https://www.luogu.com.cn/problem/P3803&quot; width=100% height=800px style=&quot;border:
  none;&quot;><iframe>''" class=''mdui-btn mdui-btn-raised mdui-ripple''>点击加载</button><a
  class=''mdui-btn mdui-btn-raised mdui-ripple'' href="https://www.luogu.com.cn/problem/P3803"
  target=''_blank''>点击跳转</a><p></details>'
permalink: LG 3803 【模板】多项式乘法（FFT）
tags:
- 模板
- 数论
- 多项式
- fft
thumbnail: null
title: LG 3803 【模板】多项式乘法（FFT）
top: 0
---
## FFT 

~~fst fst tle~~

> DFT: 离散傅里叶变换
> 
> IDFT: 离散傅里叶逆变换
> 
> FFT: 快速傅里叶变换
> 
> FNTT/NTT: 快速傅里叶变换的优化版
> 
> FWT: 快速沃尔什变换,利用类似FFT的东西解决一类卷积问题
> 
> MTT: 毛爷爷的FFT,非常nb/任意模数
> 
> FMT: 快速莫比乌斯变化
> 
> (摘自https://www.cnblogs.com/zwfymqz/p/8244902.html)

为什么要用到FFT呢?

以高精度乘法举个例子: 

你现在要计算$a\times b,a,b>10^{1000000}$

设$len_a=n,len_b=m$

如果用普通的高精度乘法$\mathcal{O(nm)}$,直接tle

但是FFT可以做到$\mathcal{O((n+m) \log (n+m))}$

原理: 先把多项式转化为用点值表示$\mathcal{O(n \log n)}$

然后再用点值相乘来计算$\mathcal{O(n)}$

然后再通过点值还原多项式

---

下面是前置知识: 

## 多项式

### 系数表示法

形式: $f(x)=\sum_{i=0}^{n-1} a_ix^i$

比如$123456$也可以看做一个多项式: 

$f(10)=6+5\cdot10+4\cdot10^2+3\cdot10^3+2\cdot 10^4+1\cdot 10^5$

### 点值表示法

取$n$个点$x_1,x_2, \dots ,x_n$

代入$f(x)$会得到$n$个不同的$y_i$

$f(x)$被$(x_1,y_1),(x_2,y_2),\dots (x_n,y_n)$唯一确定

定理:

> 一个 $n-1$ 次多项式在 $n$ 个不同点的取值唯一确定了该多项式。

证明: (反证法)

> 假设命题不成立,那么存在两个不同的$n-1$次多项式$A(x),B(x)$满足: $\forall i\in[1,n], A(x_i)=B(x_i)$
> 
> 令$C(x)=A(x)-B(x)$,那么$C(x)$也是一个$n-1$次多项式,且$\forall i\in[1,n], C(x_i)=0$
> 
> 这样的话$C(x)$有$n$个根,与代数基本定理($n$次多项式有且仅有$n$个根)不符,所以$C(x)$不是$n-1$次多项式
>
> 所以原命题成立
> 
> (摘自https://zhuanlan.zhihu.com/p/31584464)

## 复数

复数由实部(real)和虚部(image)组成,形如$a+bi$

$i$是虚树单位,$i^2=-1,i=\sqrt{-1}$

### 复数运算法则:

$(a+bi)+(c+di)=(a+c)+(b+d)i$

$(a+bi)-(c+di)=(a-c)+(b-d)i$

$(a+bi)\cdot(c+di)=(ac-bd)+(ad+bc)i$

复数$z=a+bi$在复平面中对应坐标为$(a,b)$

复平面中$x$轴又称实轴,$y$轴又称虚轴

### 共轭复数

复数$z=a+bi$的共轭复数$z'=a-bi$,$z'$称为$z$的复共轭

性质: 

$z\cdot z' = a^2 + b^2$

$|z|=|z'|$(模长相等,到原点的距离相等)


## 单位根

若$\omega^n=1$则$\omega$为$n$次单位根

在复平面上,以原点为圆心,$1$为半径作圆,所得的圆叫单位圆。

以圆心为起点,圆的$n$等分点为终点,做$n$个向量。

其中幅角为正且最小的向量称为$n$次单位向量,记为$\omega_n^1$

根据复数乘法的运算法则,其余$n−1$个复数为$\omega_n^2,\omega_n^3,\dots,\omega_n^n$

$\omega_n^0=\omega_n^n=1$,在复平面上对应的点为$(1,0)$

<html>
<svg version="1.1" xmlns="http://www.w3.org/2000/svg" xmlns:xlink="http://www.w3.org/1999/xlink" width="584" height="294"><defs><clipPath id="HfoVspciGtkQ"><path fill="none" stroke="none" d=" M 0 0 L 584 0 L 584 294 L 0 294 L 0 0 Z"/></clipPath></defs><g transform="scale(1,1)" clip-path="url(#HfoVspciGtkQ)"><g><rect fill="rgb(255,255,255)" stroke="none" x="0" y="0" width="584" height="294" fill-opacity="1"/><path fill="none" stroke="rgb(192,192,192)" paint-order="fill stroke markers" d=" M 34.5 0.5 L 34.5 294.5 M 34.5 0.5 L 34.5 294.5 M 100.5 0.5 L 100.5 294.5 M 167.5 0.5 L 167.5 294.5 M 300.5 0.5 L 300.5 294.5 M 367.5 0.5 L 367.5 294.5 M 433.5 0.5 L 433.5 294.5 M 500.5 0.5 L 500.5 294.5 M 567.5 0.5 L 567.5 294.5" stroke-opacity="1" stroke-linecap="round" stroke-linejoin="round" stroke-miterlimit="10"/><path fill="none" stroke="rgb(192,192,192)" paint-order="fill stroke markers" d=" M 7.5 0.5 L 7.5 294.5 M 20.5 0.5 L 20.5 294.5 M 47.5 0.5 L 47.5 294.5 M 60.5 0.5 L 60.5 294.5 M 74.5 0.5 L 74.5 294.5 M 87.5 0.5 L 87.5 294.5 M 114.5 0.5 L 114.5 294.5 M 127.5 0.5 L 127.5 294.5 M 140.5 0.5 L 140.5 294.5 M 154.5 0.5 L 154.5 294.5 M 180.5 0.5 L 180.5 294.5 M 194.5 0.5 L 194.5 294.5 M 207.5 0.5 L 207.5 294.5 M 220.5 0.5 L 220.5 294.5 M 247.5 0.5 L 247.5 294.5 M 260.5 0.5 L 260.5 294.5 M 273.5 0.5 L 273.5 294.5 M 287.5 0.5 L 287.5 294.5 M 313.5 0.5 L 313.5 294.5 M 327.5 0.5 L 327.5 294.5 M 340.5 0.5 L 340.5 294.5 M 353.5 0.5 L 353.5 294.5 M 380.5 0.5 L 380.5 294.5 M 393.5 0.5 L 393.5 294.5 M 407.5 0.5 L 407.5 294.5 M 420.5 0.5 L 420.5 294.5 M 447.5 0.5 L 447.5 294.5 M 460.5 0.5 L 460.5 294.5 M 473.5 0.5 L 473.5 294.5 M 487.5 0.5 L 487.5 294.5 M 513.5 0.5 L 513.5 294.5 M 527.5 0.5 L 527.5 294.5 M 540.5 0.5 L 540.5 294.5 M 553.5 0.5 L 553.5 294.5 M 580.5 0.5 L 580.5 294.5" stroke-opacity="0.23529411764705882" stroke-linecap="round" stroke-linejoin="round" stroke-miterlimit="10"/><path fill="none" stroke="rgb(192,192,192)" paint-order="fill stroke markers" d=" M 0.5 16.5 L 584.5 16.5 M 0.5 16.5 L 584.5 16.5 M 0.5 82.5 L 584.5 82.5 M 0.5 216.5 L 584.5 216.5 M 0.5 282.5 L 584.5 282.5" stroke-opacity="1" stroke-linecap="round" stroke-linejoin="round" stroke-miterlimit="10"/><path fill="none" stroke="rgb(192,192,192)" paint-order="fill stroke markers" d=" M 0.5 2.5 L 584.5 2.5 M 0.5 2.5 L 584.5 2.5 M 0.5 29.5 L 584.5 29.5 M 0.5 42.5 L 584.5 42.5 M 0.5 56.5 L 584.5 56.5 M 0.5 69.5 L 584.5 69.5 M 0.5 96.5 L 584.5 96.5 M 0.5 109.5 L 584.5 109.5 M 0.5 122.5 L 584.5 122.5 M 0.5 136.5 L 584.5 136.5 M 0.5 162.5 L 584.5 162.5 M 0.5 176.5 L 584.5 176.5 M 0.5 189.5 L 584.5 189.5 M 0.5 202.5 L 584.5 202.5 M 0.5 229.5 L 584.5 229.5 M 0.5 242.5 L 584.5 242.5 M 0.5 256.5 L 584.5 256.5 M 0.5 269.5 L 584.5 269.5" stroke-opacity="0.23529411764705882" stroke-linecap="round" stroke-linejoin="round" stroke-miterlimit="10"/><path fill="none" stroke="rgb(0,0,0)" paint-order="fill stroke markers" d=" M 233.5 2.5 L 233.5 294.5" stroke-opacity="1" stroke-miterlimit="10"/><path fill="none" stroke="rgb(0,0,0)" paint-order="fill stroke markers" d=" M 233.5 1.5 L 229.5 5.5" stroke-opacity="1" stroke-miterlimit="10"/><path fill="none" stroke="rgb(0,0,0)" paint-order="fill stroke markers" d=" M 233.5 1.5 L 237.5 5.5" stroke-opacity="1" stroke-miterlimit="10"/><path fill="none" stroke="rgb(0,0,0)" paint-order="fill stroke markers" d=" M 0.5 149.5 L 582.5 149.5" stroke-opacity="1" stroke-miterlimit="10"/><path fill="none" stroke="rgb(0,0,0)" paint-order="fill stroke markers" d=" M 583.5 149.5 L 579.5 145.5" stroke-opacity="1" stroke-miterlimit="10"/><path fill="none" stroke="rgb(0,0,0)" paint-order="fill stroke markers" d=" M 583.5 149.5 L 579.5 153.5" stroke-opacity="1" stroke-miterlimit="10"/><text fill="rgb(0,0,0)" stroke="none" font-family="geogebra-sans-serif, sans-serif" font-size="12px" font-style="normal" font-weight="normal" text-decoration="normal" x="23" y="165" text-anchor="start" dominant-baseline="alphabetic" fill-opacity="1">–1.5</text><text fill="none" stroke="rgb(255,255,255)" font-family="geogebra-sans-serif, sans-serif" font-size="12px" font-style="normal" font-weight="normal" text-decoration="normal" x="23" y="165" text-anchor="start" dominant-baseline="alphabetic" stroke-opacity="1" stroke-linejoin="bevel" stroke-miterlimit="10" stroke-width="3">–1.5</text><text fill="rgb(0,0,0)" stroke="none" font-family="geogebra-sans-serif, sans-serif" font-size="12px" font-style="normal" font-weight="normal" text-decoration="normal" x="23" y="165" text-anchor="start" dominant-baseline="alphabetic" fill-opacity="1">–1.5</text><text fill="rgb(0,0,0)" stroke="none" font-family="geogebra-sans-serif, sans-serif" font-size="12px" font-style="normal" font-weight="normal" text-decoration="normal" x="95" y="165" text-anchor="start" dominant-baseline="alphabetic" fill-opacity="1">–1</text><text fill="none" stroke="rgb(255,255,255)" font-family="geogebra-sans-serif, sans-serif" font-size="12px" font-style="normal" font-weight="normal" text-decoration="normal" x="95" y="165" text-anchor="start" dominant-baseline="alphabetic" stroke-opacity="1" stroke-linejoin="bevel" stroke-miterlimit="10" stroke-width="3">–1</text><text fill="rgb(0,0,0)" stroke="none" font-family="geogebra-sans-serif, sans-serif" font-size="12px" font-style="normal" font-weight="normal" text-decoration="normal" x="95" y="165" text-anchor="start" dominant-baseline="alphabetic" fill-opacity="1">–1</text><text fill="rgb(0,0,0)" stroke="none" font-family="geogebra-sans-serif, sans-serif" font-size="12px" font-style="normal" font-weight="normal" text-decoration="normal" x="156" y="165" text-anchor="start" dominant-baseline="alphabetic" fill-opacity="1">–0.5</text><text fill="none" stroke="rgb(255,255,255)" font-family="geogebra-sans-serif, sans-serif" font-size="12px" font-style="normal" font-weight="normal" text-decoration="normal" x="156" y="165" text-anchor="start" dominant-baseline="alphabetic" stroke-opacity="1" stroke-linejoin="bevel" stroke-miterlimit="10" stroke-width="3">–0.5</text><text fill="rgb(0,0,0)" stroke="none" font-family="geogebra-sans-serif, sans-serif" font-size="12px" font-style="normal" font-weight="normal" text-decoration="normal" x="156" y="165" text-anchor="start" dominant-baseline="alphabetic" fill-opacity="1">–0.5</text><text fill="rgb(0,0,0)" stroke="none" font-family="geogebra-sans-serif, sans-serif" font-size="12px" font-style="normal" font-weight="normal" text-decoration="normal" x="292" y="165" text-anchor="start" dominant-baseline="alphabetic" fill-opacity="1">0.5</text><text fill="none" stroke="rgb(255,255,255)" font-family="geogebra-sans-serif, sans-serif" font-size="12px" font-style="normal" font-weight="normal" text-decoration="normal" x="292" y="165" text-anchor="start" dominant-baseline="alphabetic" stroke-opacity="1" stroke-linejoin="bevel" stroke-miterlimit="10" stroke-width="3">0.5</text><text fill="rgb(0,0,0)" stroke="none" font-family="geogebra-sans-serif, sans-serif" font-size="12px" font-style="normal" font-weight="normal" text-decoration="normal" x="292" y="165" text-anchor="start" dominant-baseline="alphabetic" fill-opacity="1">0.5</text><text fill="rgb(0,0,0)" stroke="none" font-family="geogebra-sans-serif, sans-serif" font-size="12px" font-style="normal" font-weight="normal" text-decoration="normal" x="365" y="165" text-anchor="start" dominant-baseline="alphabetic" fill-opacity="1">1</text><text fill="none" stroke="rgb(255,255,255)" font-family="geogebra-sans-serif, sans-serif" font-size="12px" font-style="normal" font-weight="normal" text-decoration="normal" x="365" y="165" text-anchor="start" dominant-baseline="alphabetic" stroke-opacity="1" stroke-linejoin="bevel" stroke-miterlimit="10" stroke-width="3">1</text><text fill="rgb(0,0,0)" stroke="none" font-family="geogebra-sans-serif, sans-serif" font-size="12px" font-style="normal" font-weight="normal" text-decoration="normal" x="365" y="165" text-anchor="start" dominant-baseline="alphabetic" fill-opacity="1">1</text><text fill="rgb(0,0,0)" stroke="none" font-family="geogebra-sans-serif, sans-serif" font-size="12px" font-style="normal" font-weight="normal" text-decoration="normal" x="425" y="165" text-anchor="start" dominant-baseline="alphabetic" fill-opacity="1">1.5</text><text fill="none" stroke="rgb(255,255,255)" font-family="geogebra-sans-serif, sans-serif" font-size="12px" font-style="normal" font-weight="normal" text-decoration="normal" x="425" y="165" text-anchor="start" dominant-baseline="alphabetic" stroke-opacity="1" stroke-linejoin="bevel" stroke-miterlimit="10" stroke-width="3">1.5</text><text fill="rgb(0,0,0)" stroke="none" font-family="geogebra-sans-serif, sans-serif" font-size="12px" font-style="normal" font-weight="normal" text-decoration="normal" x="425" y="165" text-anchor="start" dominant-baseline="alphabetic" fill-opacity="1">1.5</text><text fill="rgb(0,0,0)" stroke="none" font-family="geogebra-sans-serif, sans-serif" font-size="12px" font-style="normal" font-weight="normal" text-decoration="normal" x="498" y="165" text-anchor="start" dominant-baseline="alphabetic" fill-opacity="1">2</text><text fill="none" stroke="rgb(255,255,255)" font-family="geogebra-sans-serif, sans-serif" font-size="12px" font-style="normal" font-weight="normal" text-decoration="normal" x="498" y="165" text-anchor="start" dominant-baseline="alphabetic" stroke-opacity="1" stroke-linejoin="bevel" stroke-miterlimit="10" stroke-width="3">2</text><text fill="rgb(0,0,0)" stroke="none" font-family="geogebra-sans-serif, sans-serif" font-size="12px" font-style="normal" font-weight="normal" text-decoration="normal" x="498" y="165" text-anchor="start" dominant-baseline="alphabetic" fill-opacity="1">2</text><text fill="rgb(0,0,0)" stroke="none" font-family="geogebra-sans-serif, sans-serif" font-size="12px" font-style="normal" font-weight="normal" text-decoration="normal" x="559" y="165" text-anchor="start" dominant-baseline="alphabetic" fill-opacity="1">2.5</text><text fill="none" stroke="rgb(255,255,255)" font-family="geogebra-sans-serif, sans-serif" font-size="12px" font-style="normal" font-weight="normal" text-decoration="normal" x="559" y="165" text-anchor="start" dominant-baseline="alphabetic" stroke-opacity="1" stroke-linejoin="bevel" stroke-miterlimit="10" stroke-width="3">2.5</text><text fill="rgb(0,0,0)" stroke="none" font-family="geogebra-sans-serif, sans-serif" font-size="12px" font-style="normal" font-weight="normal" text-decoration="normal" x="559" y="165" text-anchor="start" dominant-baseline="alphabetic" fill-opacity="1">2.5</text><text fill="rgb(0,0,0)" stroke="none" font-family="geogebra-sans-serif, sans-serif" font-size="12px" font-style="normal" font-weight="normal" text-decoration="normal" x="212" y="287" text-anchor="start" dominant-baseline="alphabetic" fill-opacity="1">–1</text><text fill="none" stroke="rgb(255,255,255)" font-family="geogebra-sans-serif, sans-serif" font-size="12px" font-style="normal" font-weight="normal" text-decoration="normal" x="212" y="287" text-anchor="start" dominant-baseline="alphabetic" stroke-opacity="1" stroke-linejoin="bevel" stroke-miterlimit="10" stroke-width="3">–1</text><text fill="rgb(0,0,0)" stroke="none" font-family="geogebra-sans-serif, sans-serif" font-size="12px" font-style="normal" font-weight="normal" text-decoration="normal" x="212" y="287" text-anchor="start" dominant-baseline="alphabetic" fill-opacity="1">–1</text><text fill="rgb(0,0,0)" stroke="none" font-family="geogebra-sans-serif, sans-serif" font-size="12px" font-style="normal" font-weight="normal" text-decoration="normal" x="197" y="221" text-anchor="start" dominant-baseline="alphabetic" fill-opacity="1">–0.5</text><text fill="none" stroke="rgb(255,255,255)" font-family="geogebra-sans-serif, sans-serif" font-size="12px" font-style="normal" font-weight="normal" text-decoration="normal" x="197" y="221" text-anchor="start" dominant-baseline="alphabetic" stroke-opacity="1" stroke-linejoin="bevel" stroke-miterlimit="10" stroke-width="3">–0.5</text><text fill="rgb(0,0,0)" stroke="none" font-family="geogebra-sans-serif, sans-serif" font-size="12px" font-style="normal" font-weight="normal" text-decoration="normal" x="197" y="221" text-anchor="start" dominant-baseline="alphabetic" fill-opacity="1">–0.5</text><text fill="rgb(0,0,0)" stroke="none" font-family="geogebra-sans-serif, sans-serif" font-size="12px" font-style="normal" font-weight="normal" text-decoration="normal" x="204" y="87" text-anchor="start" dominant-baseline="alphabetic" fill-opacity="1">0.5</text><text fill="none" stroke="rgb(255,255,255)" font-family="geogebra-sans-serif, sans-serif" font-size="12px" font-style="normal" font-weight="normal" text-decoration="normal" x="204" y="87" text-anchor="start" dominant-baseline="alphabetic" stroke-opacity="1" stroke-linejoin="bevel" stroke-miterlimit="10" stroke-width="3">0.5</text><text fill="rgb(0,0,0)" stroke="none" font-family="geogebra-sans-serif, sans-serif" font-size="12px" font-style="normal" font-weight="normal" text-decoration="normal" x="204" y="87" text-anchor="start" dominant-baseline="alphabetic" fill-opacity="1">0.5</text><text fill="rgb(0,0,0)" stroke="none" font-family="geogebra-sans-serif, sans-serif" font-size="12px" font-style="normal" font-weight="normal" text-decoration="normal" x="219" y="21" text-anchor="start" dominant-baseline="alphabetic" fill-opacity="1">1</text><text fill="none" stroke="rgb(255,255,255)" font-family="geogebra-sans-serif, sans-serif" font-size="12px" font-style="normal" font-weight="normal" text-decoration="normal" x="219" y="21" text-anchor="start" dominant-baseline="alphabetic" stroke-opacity="1" stroke-linejoin="bevel" stroke-miterlimit="10" stroke-width="3">1</text><text fill="rgb(0,0,0)" stroke="none" font-family="geogebra-sans-serif, sans-serif" font-size="12px" font-style="normal" font-weight="normal" text-decoration="normal" x="219" y="21" text-anchor="start" dominant-baseline="alphabetic" fill-opacity="1">1</text><text fill="rgb(0,0,0)" stroke="none" font-family="geogebra-sans-serif, sans-serif" font-size="12px" font-style="normal" font-weight="normal" text-decoration="normal" x="219" y="165" text-anchor="start" dominant-baseline="alphabetic" fill-opacity="1">0</text><text fill="none" stroke="rgb(255,255,255)" font-family="geogebra-sans-serif, sans-serif" font-size="12px" font-style="normal" font-weight="normal" text-decoration="normal" x="219" y="165" text-anchor="start" dominant-baseline="alphabetic" stroke-opacity="1" stroke-linejoin="bevel" stroke-miterlimit="10" stroke-width="3">0</text><text fill="rgb(0,0,0)" stroke="none" font-family="geogebra-sans-serif, sans-serif" font-size="12px" font-style="normal" font-weight="normal" text-decoration="normal" x="219" y="165" text-anchor="start" dominant-baseline="alphabetic" fill-opacity="1">0</text><path fill="none" stroke="rgb(97,97,97)" paint-order="fill stroke markers" d=" M 367.23252568911755 149.44244871325463 C 367.23252568911755 223.03584163929233 307.5732931378362 282.695074190574 233.97990021179882 282.695074190574 C 160.38650728576147 282.695074190574 100.72727473448012 223.03584163929233 100.72727473448012 149.44244871325463 C 100.72727473448012 75.84905578721691 160.38650728576147 16.18982323593528 233.97990021179882 16.18982323593528 C 307.5732931378362 16.18982323593528 367.23252568911755 75.84905578721691 367.23252568911755 149.44244871325463 Z" stroke-opacity="0.8" stroke-linecap="round" stroke-linejoin="round" stroke-miterlimit="10" stroke-width="2.5"/><path fill="rgb(0,0,0)" stroke="none" paint-order="stroke fill markers" d=" M 263.97990021179885 149.44244871325463 C 263.97990021179885 141.48595401806827 260.8191950008363 133.8553366310992 255.19310364739525 128.2292452776581 L 233.97990021179882 149.44244871325463 Z" fill-opacity="0.09803921568627451"/><path fill="none" stroke="rgb(0,0,0)" paint-order="fill stroke markers" d=" M 263.97990021179885 149.44244871325463 C 263.97990021179885 141.48595401806827 260.8191950008363 133.8553366310992 255.19310364739525 128.2292452776581 L 233.97990021179882 149.44244871325463 Z" stroke-opacity="0.6" stroke-linecap="round" stroke-linejoin="round" stroke-miterlimit="10" stroke-width="2"/><text fill="rgb(0,0,0)" stroke="none" font-family="geogebra-sans-serif, sans-serif" font-size="16px" font-style="normal" font-weight="normal" text-decoration="normal" x="247" y="147" text-anchor="start" dominant-baseline="alphabetic" fill-opacity="1">θ</text><text fill="none" stroke="rgb(255,255,255)" font-family="geogebra-sans-serif, sans-serif" font-size="16px" font-style="normal" font-weight="normal" text-decoration="normal" x="247" y="147" text-anchor="start" dominant-baseline="alphabetic" stroke-opacity="1" stroke-linejoin="bevel" stroke-miterlimit="10" stroke-width="3">θ</text><text fill="rgb(0,0,0)" stroke="none" font-family="geogebra-sans-serif, sans-serif" font-size="16px" font-style="normal" font-weight="normal" text-decoration="normal" x="247" y="147" text-anchor="start" dominant-baseline="alphabetic" fill-opacity="1">θ</text><path fill="none" stroke="rgb(97,97,97)" paint-order="fill stroke markers" d=" M 233.97990021179882 149.44244871325463 L 316.1829200175509 67.23942890750214" stroke-opacity="0.8" stroke-linecap="round" stroke-linejoin="round" stroke-miterlimit="10" stroke-width="2.5"/><path fill="rgb(97,97,97)" stroke="none" paint-order="stroke fill markers" fill-rule="evenodd" d=" M 328.2037352977222 55.21861362733081 L 319.1881238375937 70.24463272754497 L 313.17771619750806 64.23422508745932 Z" fill-opacity="0.8"/><path fill="none" stroke="rgb(97,97,97)" paint-order="fill stroke markers" d=" M 233.97990021179882 149.44244871325463 L 151.77688040604676 231.64546851900712" stroke-opacity="0.8" stroke-linecap="round" stroke-linejoin="round" stroke-miterlimit="10" stroke-width="2.5"/><path fill="rgb(97,97,97)" stroke="none" paint-order="stroke fill markers" fill-rule="evenodd" d=" M 139.75606512587547 243.66628379917847 L 148.77167658600393 228.6402646989643 L 154.78208422608958 234.65067233904995 Z" fill-opacity="0.8"/><path fill="none" stroke="rgb(97,97,97)" paint-order="fill stroke markers" d=" M 233.97990021179882 149.44244871325463 L 151.77688040604676 67.23942890750214" stroke-opacity="0.8" stroke-linecap="round" stroke-linejoin="round" stroke-miterlimit="10" stroke-width="2.5"/><path fill="rgb(97,97,97)" stroke="none" paint-order="stroke fill markers" fill-rule="evenodd" d=" M 139.75606512587547 55.21861362733081 L 154.78208422608958 64.23422508745932 L 148.77167658600393 70.24463272754497 Z" fill-opacity="0.8"/><path fill="none" stroke="rgb(97,97,97)" paint-order="fill stroke markers" d=" M 233.97990021179882 149.44244871325463 L 316.1829200175509 231.64546851900712" stroke-opacity="0.8" stroke-linecap="round" stroke-linejoin="round" stroke-miterlimit="10" stroke-width="2.5"/><path fill="rgb(97,97,97)" stroke="none" paint-order="stroke fill markers" fill-rule="evenodd" d=" M 328.2037352977222 243.66628379917847 L 313.17771619750806 234.65067233904995 L 319.1881238375937 228.6402646989643 Z" fill-opacity="0.8"/><path fill="none" stroke="rgb(97,97,97)" paint-order="fill stroke markers" d=" M 233.97990021179882 149.44244871325463 L 350.23252568911755 149.44244871325463" stroke-opacity="0.8" stroke-linecap="round" stroke-linejoin="round" stroke-miterlimit="10" stroke-width="2.5"/><path fill="rgb(97,97,97)" stroke="none" paint-order="stroke fill markers" fill-rule="evenodd" d=" M 367.23252568911755 149.44244871325463 L 350.23252568911755 153.69244871325463 L 350.23252568911755 145.19244871325463 Z" fill-opacity="0.8"/><path fill="none" stroke="rgb(97,97,97)" paint-order="fill stroke markers" d=" M 233.97990021179882 149.44244871325463 L 117.72727473448012 149.44244871325463" stroke-opacity="0.8" stroke-linecap="round" stroke-linejoin="round" stroke-miterlimit="10" stroke-width="2.5"/><path fill="rgb(97,97,97)" stroke="none" paint-order="stroke fill markers" fill-rule="evenodd" d=" M 100.72727473448012 149.44244871325463 L 117.72727473448012 145.19244871325463 L 117.72727473448012 153.69244871325463 Z" fill-opacity="0.8"/><path fill="none" stroke="rgb(97,97,97)" paint-order="fill stroke markers" d=" M 233.97990021179882 149.44244871325463 L 233.97990021179882 265.695074190574" stroke-opacity="0.8" stroke-linecap="round" stroke-linejoin="round" stroke-miterlimit="10" stroke-width="2.5"/><path fill="rgb(97,97,97)" stroke="none" paint-order="stroke fill markers" fill-rule="evenodd" d=" M 233.97990021179882 282.695074190574 L 229.72990021179882 265.695074190574 L 238.22990021179882 265.695074190574 Z" fill-opacity="0.8"/><path fill="none" stroke="rgb(97,97,97)" paint-order="fill stroke markers" d=" M 233.97990021179882 149.44244871325463 L 233.97990021179882 33.18982323593528" stroke-opacity="0.8" stroke-linecap="round" stroke-linejoin="round" stroke-miterlimit="10" stroke-width="2.5"/><path fill="rgb(97,97,97)" stroke="none" paint-order="stroke fill markers" fill-rule="evenodd" d=" M 233.97990021179882 16.18982323593528 L 238.22990021179882 33.18982323593528 L 229.72990021179882 33.18982323593528 Z" fill-opacity="0.8"/><path fill="rgb(97,97,97)" stroke="none" paint-order="stroke fill markers" d=" M 237.97990021179882 149.44244871325463 C 237.97990021179882 151.6515877125778 236.189039211122 153.44244871325463 233.97990021179882 153.44244871325463 C 231.77076121247563 153.44244871325463 229.97990021179882 151.6515877125778 229.97990021179882 149.44244871325463 C 229.97990021179882 147.23330971393145 231.77076121247563 145.44244871325463 233.97990021179882 145.44244871325463 C 236.189039211122 145.44244871325463 237.97990021179882 147.23330971393145 237.97990021179882 149.44244871325463 Z" fill-opacity="1"/><path fill="none" stroke="rgb(0,0,0)" paint-order="fill stroke markers" d=" M 237.97990021179882 149.44244871325463 C 237.97990021179882 151.6515877125778 236.189039211122 153.44244871325463 233.97990021179882 153.44244871325463 C 231.77076121247563 153.44244871325463 229.97990021179882 151.6515877125778 229.97990021179882 149.44244871325463 C 229.97990021179882 147.23330971393145 231.77076121247563 145.44244871325463 233.97990021179882 145.44244871325463 C 236.189039211122 145.44244871325463 237.97990021179882 147.23330971393145 237.97990021179882 149.44244871325463 Z" stroke-opacity="1" stroke-linecap="round" stroke-linejoin="round" stroke-miterlimit="10"/><text fill="rgb(97,97,97)" stroke="none" font-family="geogebra-sans-serif, sans-serif" font-size="16px" font-style="normal" font-weight="normal" text-decoration="normal" x="238" y="141" text-anchor="start" dominant-baseline="alphabetic" fill-opacity="1">O</text><text fill="none" stroke="rgb(255,255,255)" font-family="geogebra-sans-serif, sans-serif" font-size="16px" font-style="normal" font-weight="normal" text-decoration="normal" x="238" y="141" text-anchor="start" dominant-baseline="alphabetic" stroke-opacity="1" stroke-linejoin="bevel" stroke-miterlimit="10" stroke-width="3">O</text><text fill="rgb(97,97,97)" stroke="none" font-family="geogebra-sans-serif, sans-serif" font-size="16px" font-style="normal" font-weight="normal" text-decoration="normal" x="238" y="141" text-anchor="start" dominant-baseline="alphabetic" fill-opacity="1">O</text><path fill="rgb(21,101,192)" stroke="none" paint-order="stroke fill markers" d=" M 372.23252568911755 149.44244871325463 C 372.23252568911755 152.2038724624086 369.9939494382715 154.44244871325463 367.23252568911755 154.44244871325463 C 364.4711019399636 154.44244871325463 362.23252568911755 152.2038724624086 362.23252568911755 149.44244871325463 C 362.23252568911755 146.68102496410066 364.4711019399636 144.44244871325463 367.23252568911755 144.44244871325463 C 369.9939494382715 144.44244871325463 372.23252568911755 146.68102496410066 372.23252568911755 149.44244871325463 Z" fill-opacity="1"/><path fill="none" stroke="rgb(0,0,0)" paint-order="fill stroke markers" d=" M 372.23252568911755 149.44244871325463 C 372.23252568911755 152.2038724624086 369.9939494382715 154.44244871325463 367.23252568911755 154.44244871325463 C 364.4711019399636 154.44244871325463 362.23252568911755 152.2038724624086 362.23252568911755 149.44244871325463 C 362.23252568911755 146.68102496410066 364.4711019399636 144.44244871325463 367.23252568911755 144.44244871325463 C 369.9939494382715 144.44244871325463 372.23252568911755 146.68102496410066 372.23252568911755 149.44244871325463 Z" stroke-opacity="1" stroke-linecap="round" stroke-linejoin="round" stroke-miterlimit="10"/><path fill="rgb(21,101,192)" stroke="none" paint-order="stroke fill markers" d=" M 333.2037352977222 55.21861362733081 C 333.2037352977222 57.98003737648477 330.9651590468761 60.21861362733081 328.2037352977222 60.21861362733081 C 325.4423115485682 60.21861362733081 323.2037352977222 57.98003737648477 323.2037352977222 55.21861362733081 C 323.2037352977222 52.45718987817684 325.4423115485682 50.21861362733081 328.2037352977222 50.21861362733081 C 330.9651590468761 50.21861362733081 333.2037352977222 52.45718987817684 333.2037352977222 55.21861362733081 Z" fill-opacity="1"/><path fill="none" stroke="rgb(0,0,0)" paint-order="fill stroke markers" d=" M 333.2037352977222 55.21861362733081 C 333.2037352977222 57.98003737648477 330.9651590468761 60.21861362733081 328.2037352977222 60.21861362733081 C 325.4423115485682 60.21861362733081 323.2037352977222 57.98003737648477 323.2037352977222 55.21861362733081 C 323.2037352977222 52.45718987817684 325.4423115485682 50.21861362733081 328.2037352977222 50.21861362733081 C 330.9651590468761 50.21861362733081 333.2037352977222 52.45718987817684 333.2037352977222 55.21861362733081 Z" stroke-opacity="1" stroke-linecap="round" stroke-linejoin="round" stroke-miterlimit="10"/><text fill="rgb(21,101,192)" stroke="none" font-family="geogebra-sans-serif, sans-serif" font-size="16px" font-style="normal" font-weight="normal" text-decoration="normal" x="332" y="45" text-anchor="start" dominant-baseline="alphabetic" fill-opacity="1">ω</text><text fill="none" stroke="rgb(255,255,255)" font-family="geogebra-sans-serif, sans-serif" font-size="16px" font-style="normal" font-weight="normal" text-decoration="normal" x="332" y="45" text-anchor="start" dominant-baseline="alphabetic" stroke-opacity="1" stroke-linejoin="bevel" stroke-miterlimit="10" stroke-width="3">ω</text><text fill="rgb(21,101,192)" stroke="none" font-family="geogebra-sans-serif, sans-serif" font-size="16px" font-style="normal" font-weight="normal" text-decoration="normal" x="332" y="45" text-anchor="start" dominant-baseline="alphabetic" fill-opacity="1">ω</text><text fill="rgb(21,101,192)" stroke="none" font-family="geogebra-sans-serif, sans-serif" font-size="14px" font-style="normal" font-weight="normal" text-decoration="normal" x="346" y="52" text-anchor="start" dominant-baseline="alphabetic" fill-opacity="1">8</text><text fill="none" stroke="rgb(255,255,255)" font-family="geogebra-sans-serif, sans-serif" font-size="14px" font-style="normal" font-weight="normal" text-decoration="normal" x="346" y="52" text-anchor="start" dominant-baseline="alphabetic" stroke-opacity="1" stroke-linejoin="bevel" stroke-miterlimit="10" stroke-width="3">8</text><text fill="rgb(21,101,192)" stroke="none" font-family="geogebra-sans-serif, sans-serif" font-size="14px" font-style="normal" font-weight="normal" text-decoration="normal" x="346" y="52" text-anchor="start" dominant-baseline="alphabetic" fill-opacity="1">8</text><text fill="rgb(21,101,192)" stroke="none" font-family="geogebra-sans-serif, sans-serif" font-size="16px" font-style="normal" font-weight="normal" text-decoration="normal" x="354" y="45" text-anchor="start" dominant-baseline="alphabetic" fill-opacity="1">(cos θ, i sin θ)</text><text fill="none" stroke="rgb(255,255,255)" font-family="geogebra-sans-serif, sans-serif" font-size="16px" font-style="normal" font-weight="normal" text-decoration="normal" x="354" y="45" text-anchor="start" dominant-baseline="alphabetic" stroke-opacity="1" stroke-linejoin="bevel" stroke-miterlimit="10" stroke-width="3">(cos θ, i sin θ)</text><text fill="rgb(21,101,192)" stroke="none" font-family="geogebra-sans-serif, sans-serif" font-size="16px" font-style="normal" font-weight="normal" text-decoration="normal" x="354" y="45" text-anchor="start" dominant-baseline="alphabetic" fill-opacity="1">(cos θ, sin θ)</text><path fill="rgb(97,97,97)" stroke="none" paint-order="stroke fill markers" d=" M 143.75606512587547 243.66628379917847 C 143.75606512587547 245.87542279850163 141.96520412519862 247.66628379917847 139.75606512587547 247.66628379917847 C 137.54692612655228 247.66628379917847 135.75606512587547 245.87542279850163 135.75606512587547 243.66628379917847 C 135.75606512587547 241.45714479985529 137.54692612655228 239.66628379917847 139.75606512587547 239.66628379917847 C 141.96520412519862 239.66628379917847 143.75606512587547 241.45714479985529 143.75606512587547 243.66628379917847 Z" fill-opacity="1"/><path fill="none" stroke="rgb(0,0,0)" paint-order="fill stroke markers" d=" M 143.75606512587547 243.66628379917847 C 143.75606512587547 245.87542279850163 141.96520412519862 247.66628379917847 139.75606512587547 247.66628379917847 C 137.54692612655228 247.66628379917847 135.75606512587547 245.87542279850163 135.75606512587547 243.66628379917847 C 135.75606512587547 241.45714479985529 137.54692612655228 239.66628379917847 139.75606512587547 239.66628379917847 C 141.96520412519862 239.66628379917847 143.75606512587547 241.45714479985529 143.75606512587547 243.66628379917847 Z" stroke-opacity="1" stroke-linecap="round" stroke-linejoin="round" stroke-miterlimit="10"/><text fill="rgb(97,97,97)" stroke="none" font-family="geogebra-sans-serif, sans-serif" font-size="16px" font-style="normal" font-weight="normal" text-decoration="normal" x="144" y="236" text-anchor="start" dominant-baseline="alphabetic" fill-opacity="1">C</text><text fill="none" stroke="rgb(255,255,255)" font-family="geogebra-sans-serif, sans-serif" font-size="16px" font-style="normal" font-weight="normal" text-decoration="normal" x="144" y="236" text-anchor="start" dominant-baseline="alphabetic" stroke-opacity="1" stroke-linejoin="bevel" stroke-miterlimit="10" stroke-width="3">C</text><text fill="rgb(97,97,97)" stroke="none" font-family="geogebra-sans-serif, sans-serif" font-size="16px" font-style="normal" font-weight="normal" text-decoration="normal" x="144" y="236" text-anchor="start" dominant-baseline="alphabetic" fill-opacity="1">C</text><path fill="rgb(97,97,97)" stroke="none" paint-order="stroke fill markers" d=" M 143.75606512587547 55.21861362733081 C 143.75606512587547 57.427752626653984 141.96520412519862 59.21861362733081 139.75606512587547 59.21861362733081 C 137.54692612655228 59.21861362733081 135.75606512587547 57.427752626653984 135.75606512587547 55.21861362733081 C 135.75606512587547 53.00947462800764 137.54692612655228 51.21861362733081 139.75606512587547 51.21861362733081 C 141.96520412519862 51.21861362733081 143.75606512587547 53.00947462800764 143.75606512587547 55.21861362733081 Z" fill-opacity="1"/><path fill="none" stroke="rgb(0,0,0)" paint-order="fill stroke markers" d=" M 143.75606512587547 55.21861362733081 C 143.75606512587547 57.427752626653984 141.96520412519862 59.21861362733081 139.75606512587547 59.21861362733081 C 137.54692612655228 59.21861362733081 135.75606512587547 57.427752626653984 135.75606512587547 55.21861362733081 C 135.75606512587547 53.00947462800764 137.54692612655228 51.21861362733081 139.75606512587547 51.21861362733081 C 141.96520412519862 51.21861362733081 143.75606512587547 53.00947462800764 143.75606512587547 55.21861362733081 Z" stroke-opacity="1" stroke-linecap="round" stroke-linejoin="round" stroke-miterlimit="10"/><text fill="rgb(97,97,97)" stroke="none" font-family="geogebra-sans-serif, sans-serif" font-size="16px" font-style="normal" font-weight="normal" text-decoration="normal" x="144" y="47" text-anchor="start" dominant-baseline="alphabetic" fill-opacity="1">B</text><text fill="none" stroke="rgb(255,255,255)" font-family="geogebra-sans-serif, sans-serif" font-size="16px" font-style="normal" font-weight="normal" text-decoration="normal" x="144" y="47" text-anchor="start" dominant-baseline="alphabetic" stroke-opacity="1" stroke-linejoin="bevel" stroke-miterlimit="10" stroke-width="3">B</text><text fill="rgb(97,97,97)" stroke="none" font-family="geogebra-sans-serif, sans-serif" font-size="16px" font-style="normal" font-weight="normal" text-decoration="normal" x="144" y="47" text-anchor="start" dominant-baseline="alphabetic" fill-opacity="1">B</text><path fill="rgb(97,97,97)" stroke="none" paint-order="stroke fill markers" d=" M 332.2037352977222 243.66628379917847 C 332.2037352977222 245.87542279850163 330.41287429704533 247.66628379917847 328.2037352977222 247.66628379917847 C 325.994596298399 247.66628379917847 324.2037352977222 245.87542279850163 324.2037352977222 243.66628379917847 C 324.2037352977222 241.45714479985529 325.994596298399 239.66628379917847 328.2037352977222 239.66628379917847 C 330.41287429704533 239.66628379917847 332.2037352977222 241.45714479985529 332.2037352977222 243.66628379917847 Z" fill-opacity="1"/><path fill="none" stroke="rgb(0,0,0)" paint-order="fill stroke markers" d=" M 332.2037352977222 243.66628379917847 C 332.2037352977222 245.87542279850163 330.41287429704533 247.66628379917847 328.2037352977222 247.66628379917847 C 325.994596298399 247.66628379917847 324.2037352977222 245.87542279850163 324.2037352977222 243.66628379917847 C 324.2037352977222 241.45714479985529 325.994596298399 239.66628379917847 328.2037352977222 239.66628379917847 C 330.41287429704533 239.66628379917847 332.2037352977222 241.45714479985529 332.2037352977222 243.66628379917847 Z" stroke-opacity="1" stroke-linecap="round" stroke-linejoin="round" stroke-miterlimit="10"/><text fill="rgb(97,97,97)" stroke="none" font-family="geogebra-sans-serif, sans-serif" font-size="16px" font-style="normal" font-weight="normal" text-decoration="normal" x="332" y="236" text-anchor="start" dominant-baseline="alphabetic" fill-opacity="1">D</text><text fill="none" stroke="rgb(255,255,255)" font-family="geogebra-sans-serif, sans-serif" font-size="16px" font-style="normal" font-weight="normal" text-decoration="normal" x="332" y="236" text-anchor="start" dominant-baseline="alphabetic" stroke-opacity="1" stroke-linejoin="bevel" stroke-miterlimit="10" stroke-width="3">D</text><text fill="rgb(97,97,97)" stroke="none" font-family="geogebra-sans-serif, sans-serif" font-size="16px" font-style="normal" font-weight="normal" text-decoration="normal" x="332" y="236" text-anchor="start" dominant-baseline="alphabetic" fill-opacity="1">D</text><path fill="rgb(97,97,97)" stroke="none" paint-order="stroke fill markers" d=" M 104.72727473448012 149.44244871325463 C 104.72727473448012 151.6515877125778 102.93641373380329 153.44244871325463 100.72727473448012 153.44244871325463 C 98.51813573515695 153.44244871325463 96.72727473448012 151.6515877125778 96.72727473448012 149.44244871325463 C 96.72727473448012 147.23330971393145 98.51813573515695 145.44244871325463 100.72727473448012 145.44244871325463 C 102.93641373380329 145.44244871325463 104.72727473448012 147.23330971393145 104.72727473448012 149.44244871325463 Z" fill-opacity="1"/><path fill="none" stroke="rgb(0,0,0)" paint-order="fill stroke markers" d=" M 104.72727473448012 149.44244871325463 C 104.72727473448012 151.6515877125778 102.93641373380329 153.44244871325463 100.72727473448012 153.44244871325463 C 98.51813573515695 153.44244871325463 96.72727473448012 151.6515877125778 96.72727473448012 149.44244871325463 C 96.72727473448012 147.23330971393145 98.51813573515695 145.44244871325463 100.72727473448012 145.44244871325463 C 102.93641373380329 145.44244871325463 104.72727473448012 147.23330971393145 104.72727473448012 149.44244871325463 Z" stroke-opacity="1" stroke-linecap="round" stroke-linejoin="round" stroke-miterlimit="10"/><text fill="rgb(97,97,97)" stroke="none" font-family="geogebra-sans-serif, sans-serif" font-size="16px" font-style="normal" font-weight="normal" text-decoration="normal" x="105" y="141" text-anchor="start" dominant-baseline="alphabetic" fill-opacity="1">E</text><text fill="none" stroke="rgb(255,255,255)" font-family="geogebra-sans-serif, sans-serif" font-size="16px" font-style="normal" font-weight="normal" text-decoration="normal" x="105" y="141" text-anchor="start" dominant-baseline="alphabetic" stroke-opacity="1" stroke-linejoin="bevel" stroke-miterlimit="10" stroke-width="3">E</text><text fill="rgb(97,97,97)" stroke="none" font-family="geogebra-sans-serif, sans-serif" font-size="16px" font-style="normal" font-weight="normal" text-decoration="normal" x="105" y="141" text-anchor="start" dominant-baseline="alphabetic" fill-opacity="1">E</text><path fill="rgb(97,97,97)" stroke="none" paint-order="stroke fill markers" d=" M 237.97990021179882 282.695074190574 C 237.97990021179882 284.9042131898972 236.189039211122 286.695074190574 233.97990021179882 286.695074190574 C 231.77076121247563 286.695074190574 229.97990021179882 284.9042131898972 229.97990021179882 282.695074190574 C 229.97990021179882 280.48593519125086 231.77076121247563 278.695074190574 233.97990021179882 278.695074190574 C 236.189039211122 278.695074190574 237.97990021179882 280.48593519125086 237.97990021179882 282.695074190574 Z" fill-opacity="1"/><path fill="none" stroke="rgb(0,0,0)" paint-order="fill stroke markers" d=" M 237.97990021179882 282.695074190574 C 237.97990021179882 284.9042131898972 236.189039211122 286.695074190574 233.97990021179882 286.695074190574 C 231.77076121247563 286.695074190574 229.97990021179882 284.9042131898972 229.97990021179882 282.695074190574 C 229.97990021179882 280.48593519125086 231.77076121247563 278.695074190574 233.97990021179882 278.695074190574 C 236.189039211122 278.695074190574 237.97990021179882 280.48593519125086 237.97990021179882 282.695074190574 Z" stroke-opacity="1" stroke-linecap="round" stroke-linejoin="round" stroke-miterlimit="10"/><text fill="rgb(97,97,97)" stroke="none" font-family="geogebra-sans-serif, sans-serif" font-size="16px" font-style="normal" font-weight="normal" text-decoration="normal" x="238" y="275" text-anchor="start" dominant-baseline="alphabetic" fill-opacity="1">F</text><text fill="none" stroke="rgb(255,255,255)" font-family="geogebra-sans-serif, sans-serif" font-size="16px" font-style="normal" font-weight="normal" text-decoration="normal" x="238" y="275" text-anchor="start" dominant-baseline="alphabetic" stroke-opacity="1" stroke-linejoin="bevel" stroke-miterlimit="10" stroke-width="3">F</text><text fill="rgb(97,97,97)" stroke="none" font-family="geogebra-sans-serif, sans-serif" font-size="16px" font-style="normal" font-weight="normal" text-decoration="normal" x="238" y="275" text-anchor="start" dominant-baseline="alphabetic" fill-opacity="1">F</text><path fill="rgb(97,97,97)" stroke="none" paint-order="stroke fill markers" d=" M 237.97990021179882 16.18982323593528 C 237.97990021179882 18.398962235258452 236.189039211122 20.18982323593528 233.97990021179882 20.18982323593528 C 231.77076121247563 20.18982323593528 229.97990021179882 18.398962235258452 229.97990021179882 16.18982323593528 C 229.97990021179882 13.980684236612106 231.77076121247563 12.189823235935279 233.97990021179882 12.189823235935279 C 236.189039211122 12.189823235935279 237.97990021179882 13.980684236612106 237.97990021179882 16.18982323593528 Z" fill-opacity="1"/><path fill="none" stroke="rgb(0,0,0)" paint-order="fill stroke markers" d=" M 237.97990021179882 16.18982323593528 C 237.97990021179882 18.398962235258452 236.189039211122 20.18982323593528 233.97990021179882 20.18982323593528 C 231.77076121247563 20.18982323593528 229.97990021179882 18.398962235258452 229.97990021179882 16.18982323593528 C 229.97990021179882 13.980684236612106 231.77076121247563 12.189823235935279 233.97990021179882 12.189823235935279 C 236.189039211122 12.189823235935279 237.97990021179882 13.980684236612106 237.97990021179882 16.18982323593528 Z" stroke-opacity="1" stroke-linecap="round" stroke-linejoin="round" stroke-miterlimit="10"/><text fill="rgb(97,97,97)" stroke="none" font-family="geogebra-sans-serif, sans-serif" font-size="16px" font-style="normal" font-weight="normal" text-decoration="normal" x="238" y="16" text-anchor="start" dominant-baseline="alphabetic" fill-opacity="1">G</text><text fill="none" stroke="rgb(255,255,255)" font-family="geogebra-sans-serif, sans-serif" font-size="16px" font-style="normal" font-weight="normal" text-decoration="normal" x="238" y="16" text-anchor="start" dominant-baseline="alphabetic" stroke-opacity="1" stroke-linejoin="bevel" stroke-miterlimit="10" stroke-width="3">G</text><text fill="rgb(97,97,97)" stroke="none" font-family="geogebra-sans-serif, sans-serif" font-size="16px" font-style="normal" font-weight="normal" text-decoration="normal" x="238" y="16" text-anchor="start" dominant-baseline="alphabetic" fill-opacity="1">G</text></g></g></svg>
</html>

向量$\overrightarrow{O\omega_8}$表示的复数就是$8$次单位根,$\omega_8^1$

> 拓展: 
> 
> 欧拉公式: $e^{i\theta}=\cos\theta + i \sin \theta$(在复平面内坐标为$(\cos \theta, \sin \theta)$)
> 
> $\omega_n^k=e^{i 2\pi \frac kn}$
> (可以理解为从$\omega_n^0(1,0)$开始走长度为$2\pi \frac kn$的圆弧后到达的位置)
> 
> 欧拉公式: $e^{i\pi}=-1$(复平面中的$(-1,0)$)
> 
> 关于证明和理解,可以参考下面两个视频: 
> 
> https://www.bilibili.com/video/av63666593
> 
> https://www.bilibili.com/video/av79134103

性质:

$\omega_n^k= \cos 2\pi\frac kn+ i \sin 2\pi \frac kn$

$\omega_{2n}^{2k}=\omega_n^k$

> $\omega_{2n}^{2k}=\cos 2\pi\frac {2k}{2n}+ i \sin 2\pi \frac {2k}{2n}=\cos 2\pi\frac kn+ i \sin 2\pi \frac kn=\omega_n^k$

$\omega_n^0=\omega_n^n=1$

$\omega_n^{k+\frac n2}=-\omega_n^k$

> $\omega _{n}^{\frac{n}{2}}=\cos\frac{n}{2}\cdot\frac{2\pi}{n}+i\sin\frac{n}{2}\cdot\frac{2\pi}{n}=-1$
> (也就是上面说的$e^{i\pi}$)

---

正题开始: 

## DFT 

将多项式从系数表示法转换为点值表示法

如果暴力代入$n$个点,复杂度还是$\mathcal{O(n^2)}$的

我们可以利用单位根的性质

假设设$n$为偶数

对于$A(x)=a_0+a_1x+a_2x^2+a_3x^3+\dots+a_{n-1}x^{n-1}$

$A(x)=(a_0+a_2x^2+a_4x^4+\dots+a_{n-2}x^{n-2})+x(a_1+a_3x^2+a_5x^4+...+a_{n-1}x^{n-1})$

设$A_1(x)=a_0+a_2x+a_4x^2+\dots+a_{n-2}x^\frac{n-2}2,A_2(x)=a_1+a_3x+a_5x^2+...+a_{n-1}x^\frac{n-2}2$

那么$A(x)=A_1(x^2)+xA_2(x^2)$

设$0 \le k \le \frac{n}{2}-1,k\in Z$

$A(\omega_n^k)=A_1(\omega_\frac n2 ^k)+\omega_n^k\cdot A_2(\omega_\frac n2 ^k)$

对于$\frac n2 \le k+\frac n2 \le n-1$

$A(\omega_n^{k+\frac n2})=A_1(\omega_n^{2k+n})+\omega_n^{k+\frac n2}\cdot A_2(\omega_n^{2k+n})$

$\because \omega_n^{k+\frac n2}=-\omega_n^k,\omega_n^{2k+n}=\omega_\frac n2^k$

$\therefore A(\omega_n^{k+\frac n2})=A_1(\omega_\frac n2^k)-\omega_n^k\cdot A_2(\omega_\frac n2^k)$

如果已经知道$A_1,A_2$分别在$\omega_\frac n2 ^{0,1,2,...,\frac n2 -1}$的取值,那么就可以在$\mathcal{O(n)}$的时间内计算出$A(x)$,而$A_1(x),A_2(x)$的规模都是$A(x)$的一半

复杂度$\mathcal{T(n)=2T(\frac n2)+O(n) = O(n \log n)}$

## IDFT

使用快速傅里叶变换将点值表示的多项式转化为系数表示,这个过程叫做离散傅里叶逆变换

即由$n$维点值向量$(A(x_0),A(x_1),\dots,A(x_{n-1}))$推出$n$维系数向量$(a_0,a_1,\dots,a_{n-1})$。

设$y_0,y_1,y_2,...,y_{n-1}$是多项式$A(x)$变换后的点值

设$(d_0,d_1,\dots,d_{n-1})$为$(a_0,a_1,\dots,a_{n-1})$离散傅里叶变换后的结果

构造$F(x)=d_0+d_1x+d_2x^2+\dots+d_{n-1}x^{n-1}$

设向量$(c_0,c_1,\dots,c_{n-1})$中

$c_k$为$F(x)$在$x=\omega_n^{-k}$时的点值表示

$$

c_k=\sum_{i=0}^{n-1}d_i\cdot(\omega_n^{-k})^i
\\
=\sum_{i=0}^{n-1}[\sum_{j=0}^{n-1}a_j(\omega_n^i)^j]\cdot(\omega_n^{-k})^i
\\
=\sum_{j=0}^{n-1}a_j\sum_{i=0}^{n-1}(\omega_n^i)^j\cdot(\omega_n^{-k})^i
\\
=\sum_{j=0}^{n-1}a_j\sum_{i=0}^{n-1}(\omega_n^i)^{j-k}
$$

观察$\sum_{i=0}^{n-1}(\omega_n^i)^{j-k}$

当$j=k$时$\sum_{i=0}^{n-1}(\omega_n^i)^{j-k}=\sum_{i=0}^{n-1}1=n$

当$j\not = k$时

$\sum_{i=0}^{n-1}(\omega_n^i)^{j-k}=$

$\sum_{i=0}^{\frac{n-1}2}(\omega_n^i)^{j-k}+(\omega_n^{i+\frac{n-1}2})^{j-k}=0$

也就是$n$次单位根会互相抵消

$\therefore \sum_{i=0}^{n-1}(\omega_n^i)^{j-k}=[j=k]\cdot n$

$\therefore c_k=\sum_{j=0}^{n-1}a_j\sum_{i=0}^{n-1}(\omega_n^i)^{j-k}=\sum_{j=0}^{n-1}a_j [j=k]\cdot n=na_k$

$\therefore a_k=\frac{c_k}n$

那么我们要将点值表示的多项式转化为系数表示:

1. 将$(\omega_n^0,\omega_n^{-1},\omega_n^{-2},\dots,w_n^{-(n-1)})$作为差值节点,将点值再做一次DFT
   
   得到$(c_0,c_1,c_2,\dots,c_{n-1})$

2. $(\frac{c_0}n,\frac{c_1}n,\frac{c_2}n,\dots,\frac{c_{n-1}}n)$就是原来的$(a_0,a_1,a_2,\dots,a_{n-1})$

---

到这里我们就已经大致懂得FFT的原理了,那要怎么实现呢?

## 实现

[LG 3803 【模板】多项式乘法（FFT）](https://www.luogu.com.cn/problem/P3803)

### 普通的递归写法

~~Fst_Fst_**TLE**~~

不断对下标进行奇偶分类,分成两个子序列之后再不断合并

需要辅助数组,容易**TLE,MLE**

### 迭代实现

![](https://pic1.zhimg.com/80/v2-953d1cd6c91a84197775d504defe302c_hd.jpg)

可以发现在不断进行奇偶分类之后,原数在数组中的位置下标最终变成了**下标的二进制反转**

我们可以直接通过枚举来代替递归

从最底层开始向上合并,那么怎么合并呢？

#### 蝴蝶操作

设该层一共有$n$项需要处理

设$A_1(\omega_{\frac n2}^k)$和$A_2(\omega_{\frac n2}^k)$分别存放在$a_k$和$a_{k+\frac n2}$

$A_1(\omega_n^k)$和$A_2(\omega_n^k)$要存放在$buf(k)$和$buf(k+\frac n2)$

我们只需设中间变量$t=\omega_n^k\cdot a(k+\frac n2)$

$buf(k+\frac n2)= a(k) - t$

$buf(k) = a(k)+t$

我们可以发现我们不需要辅助存放的数组$buf$了,直接在原序列操作即可

代码: 

```cpp
#include<bits/stdc++.h>
#define db double
#define For(i,x,y) for(int i=x;i<=y;++i)
const int N=4000011;
const db Pi=acos(-1.0);
int n,m,limit=1,l=0,r[N];
struct cp{db r,i;cp(db R=0,db I=0){r=R,i=I;}}a[N],b[N];
cp operator + (cp a,cp b){return cp(a.r+b.r,a.i+b.i);}
cp operator - (cp a,cp b){return cp(a.r-b.r,a.i-b.i);}
cp operator * (cp a,cp b){return cp(a.r*b.r-a.i*b.i,a.r*b.i+a.i*b.r);}
void fft(cp *A,int typ){
    For(i,0,limit-1)
        if(i<r[i])std::swap(A[i],A[r[i]]);
    for(int len=1;len<limit;len<<=1){//已处理好的长度块,也就是n/2
        cp Wn(cos(Pi/len),typ*sin(Pi/len));//单位根
        for(int i=0;i<limit;i+=(len<<1)){
            cp w(1,0);//w_n^0
            For(k,0,len-1){//蝴蝶操作
                cp t=w*A[i+k+len];
                A[i+k+len]=A[i+k]-t;
                A[i+k]=A[i+k]+t;
                w=w*Wn;
            }
        }
    }
}
int main(){
    scanf("%d%d",&n,&m);
    For(i,0,n)scanf("%lf",&a[i].r);
    For(i,0,m)scanf("%lf",&b[i].r);
    
    while(limit<=n+m)limit<<=1,++l;
    For(i,0,limit-1)//预处理出不断奇偶分类后的最终位置
        r[i]=(r[i>>1]>>1)|((i&1)<<(l-1));

    fft(a,1);fft(b,1);//DFT
    For(i,0,limit)a[i]=a[i]*b[i];//点值相乘
    fft(a,-1);//IDFT
    For(i,0,n+m)printf("%d ",int(a[i].r/limit+0.5));
}
```

---

本文部分内容摘自:(参考资料)

https://zhuanlan.zhihu.com/p/31584464

https://www.cnblogs.com/zwfymqz/p/8244902.html
```cpp
#include<bits/stdc++.h>
#define db double
#define For(i,x,y) for(int i=x;i<=y;++i)
const int N=4000011;
const db Pi=acos(-1.0);
int n,m,limit=1,l=0,r[N];
struct cp{db r,i;cp(db R=0,db I=0){r=R,i=I;}}a[N],b[N];
cp operator + (cp a,cp b){return cp(a.r+b.r,a.i+b.i);}
cp operator - (cp a,cp b){return cp(a.r-b.r,a.i-b.i);}
cp operator * (cp a,cp b){return cp(a.r*b.r-a.i*b.i,a.r*b.i+a.i*b.r);}
void fft(cp *A,int typ){
    For(i,0,limit-1)
        if(i<r[i])std::swap(A[i],A[r[i]]);
    for(int len=1;len<limit;len<<=1){
        cp Wn(cos(Pi/len),typ*sin(Pi/len));
        for(int i=0;i<limit;i+=(len<<1)){
            cp w(1,0);
            For(k,0,len-1){
                cp t=w*A[i+k+len];
                A[i+k+len]=A[i+k]-t;
                A[i+k]=A[i+k]+t;
                w=w*Wn;
            }
        }
    }
}
int main(){
    scanf("%d%d",&n,&m);
    For(i,0,n)scanf("%lf",&a[i].r);
    For(i,0,m)scanf("%lf",&b[i].r);
    
    while(limit<=n+m)limit<<=1,++l;
    For(i,0,limit-1)
        r[i]=(r[i>>1]>>1)|((i&1)<<(l-1));

    fft(a,1);fft(b,1);
    For(i,0,limit)a[i]=a[i]*b[i];
    fft(a,-1);
    For(i,0,n+m)printf("%d ",int(a[i].r/limit+0.5));
}
```
