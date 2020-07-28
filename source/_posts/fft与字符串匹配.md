---
title: fft与字符串匹配
date: 2020-07-22 19:57
tags: 
 - 字符串
 - 数论

categories:
 - [note]
 - [算法,字符串]

top: 0 
html:
---

## 普通的单模式串匹配

> 给定模式串$A(|A|=m)$、文本串$B(|B|=n)$，需要求出所有位置$p$,满足$B$串从第$p$个字符开始的连续$m$个字符，与$A$串完全相同

定义匹配函数$C(x,y)=[A(x)-B(y)]^2$,若$A$的第$x$个字符与$B$的第$y$个字符匹配,那么$C(x,y)=0$

再定义完全匹配函数$\displaystyle P(x)=\sum_{i=0}^{m-1}[A(i)-B(x-m+i+1)]^2$,若$P(x)=0$,则称$B$以第$x$位结束的连续$m$位,与$A$完全匹配  

咋一看似乎没有什么优化方法  

我们翻转$A$串得到$S$串  

那么  

$\displaystyle
\begin{aligned}
P(x)
&=\sum_{i=0}^{m-1}[A(i)-B(x-m+i+1)]^2\\
&=\sum_{i=0}^{m-1}[S(m-i+1)-B(x-m+i+1)]^2\\
&=\sum_{i=0}^{m-1}[S(m-i+1)^2+B(x-m+i+1)^2-2S(m-i+1)B(x-m+i+1)]\\
&=\sum_{i=0}^{m-1}S(m-i+1)^2+\sum_{i=0}^{m-1}B(x-m+i+1)^2-\sum_{i=0}^{m-1}2S(m-i+1)B(x-m+i+1)]
\end{aligned}$

第一项是定值,第二项可以预处理前缀和解决,第三项可以卷积
 
$\displaystyle  \sum_{i=0}^{m-1}2S(m-i+1)B(x-m+i+1)]=\sum_{i+j=x}2S(i)B(j)$

设$T=\sum_{i=0}^{m-1} S(i)^2,f(x)=\sum_{i=0}^x B(i)^2,g(x)=\sum_{i+j=x}2S(i)B(j)$

那么$P(x)=T+f(x)-f(x-m)-2g(x)$  

这样可以$O(n)$得到所有$P(x)$的值  

## 带通配符的单模式串匹配  

设通配符的数值为$0$,定义匹配函数$C(x,y)=[A(x)-B(y)]^2A(x)B(y)$,那么$\displaystyle P(x)=\sum_{i=0}^{m-1}[A(i)-B(x-m+i+1)]^2A(i)B(x-m+i+1)$

按照套路,翻转$A$串得到$S$串:

$\displaystyle
\begin{aligned}
P(x)
&=\sum_{i=0}^{m-1}[A(i)-B(x-m+i+1)]^2A(i)B(x-m+i+1)\\
&=\sum_{i=0}^{m-1}[S(m-i+1)-B(x-m+i+1)]^2S(m-i+1)B(x-m+i+1)\\
&=\sum_{i=0}^{m-1}S(m-i+1)^3B(x-m+i+1)+\\
&\quad\sum_{i=0}^{m-1}B(x-m+i+1)^3S(m-i+1)-\\
&\quad2\sum_{i=0}^{m-1}S(m-i+1)^2B(x-m+i+1)^2
\end{aligned}$

写为卷积形式:

$\displaystyle P(x)=\sum_{i+j=x}S(i)^3B(j)+S(i)B(j)^3-2S(i)^2B(j)^2$