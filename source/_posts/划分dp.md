---
date: 2019-12-01
tags:
- 动态规划
- 计数

categories:
  - [算法,动态规划]
  - [算法,树论]
  - [note]
---
# 划分dp

## 题意

每组输入是两个整数$n$和$k$($1\le n \le 50, 1 \le k \le n)$

输出

对于输入的$n,k$;

第一行： 将$n$划分成若干正整数之和的方案数。

第二行： 将$n$划分成$k$个正整数之和的方案数。

第三行： 将$n$划分成最大数不超过$k$的方案数。

第四行： 将$n$划分成若干个奇正整数之和的方案数。

第五行： 将$n$划分成若干不同整数之和的方案数。

第六行： 打印一个空行

## Sol.：

### 划分的多个正整数可以相同

设$f[i][j]$表示将$i$划分成不大于$j$的整数的方案数

1. 当$i<j$时,$i$不能划分为大于$i$的数,所以$f[i][j]=f[i][i]$
2. 当$i>j$时,分为两种情况
   - 划分中后的数含有$j$

     方案数：$f[i-j][j](i<j)$

   - 划分中不含$j$

     相当于把$i$划分成不大于$j-1$的数
     方案数：$f[i][j-1]$

   所以$f[i][j]=f[i-j][j]+f[i-1][j-1](i>j)$

3. 当$i=j$时,两种情况：

   - 划分后的数只含有$j$,那么只有一种情况
   - 相当于把$i$划分成不大于$j-1$的数
   方案数：$f[i][j-1]$

   所以$f[i][j]=1+f[i][j-1]$

$f[n][n]$:将$n$划分为若干正整数之和的划分数

$f[n][k]$:将$n$划分成最大数不超过$k$的划分数。

### 划分的正整数必须不同

设$f[i][j]$表示将$i$划分成不大于$j$的不同整数的方案数

1. 当$i<j$时,$i$不能划分为大于$i$的数,所以$f[i][j]=f[i][i]$
2. 当$i>j$时,分为两种情况
   - 划分后的数中含有$j$

     其余的不能含有$j$

     方案数：$f[i-j][j-1](i<j)$

   - 划分中不含$j$

     相当于把$i$划分成不大于$j-1$的数

     方案数：$f[i][j-1]$

   所以$f[i][j]=f[i-j][j-1]+f[i-1][j-1](i>j)$

3. 当$i=j$时,两种情况：

   - 划分后的数只含有$j$,那么只有一种情况
   - 相当于把$i$划分成不大于$j-1$的数
   方案数：$f[i][j-1]$

   $f[i][j]=1+f[i][j-1]$

$f[n][n]$:将$n$划分为不同正整数之和的划分数

### 将n划分为k个正整数的划分数

设$f[i][j]$为将$i$划分为$j$个正整数的方案数

1. $i<j$,不可能出现,$f[i][j]=0(i<j)$
2. $i=j$, 只有一种情况：划分成$i$个$1$
3. $i>j$,两种情况：
   - 划分后的数中含有$1$

     可以使用“截边法”将划分出的$j$个数分别减去$1$,把问题转化为将$i-j$划分成$j-1$个数,方案数：$f[i-j][j-1]$

   - 划分后的数中不含$1$

     使用“截边法”将划分出的$j$个数分别减去$1$,将为题转化为求$i-j$的$j$个划分数,为$f[i-j][j]$

    所以$f[i][j]=f[i-j][j-1]+f[i-j][j]$

$f[n][k]$表示将$n$划分为$k$个正整数的方案数

### 将n划分为若干正奇数之和的划分数

设$f[i][j]$为将$i$划分为$j$个奇数之和的划分数,

$g[i][j]$为将$i$划分为$j$个偶数之和的划分数

使用截边法,将$g[i][j]$的$j$个划分都减去$1$,可以得到$f[i-j][j]$,所以

$g[i][j] = f[i-j][j]$

对于$f[i][j]$

1. 划分后的数中包含$1$
   
   可以将划分出的$1$除去,转化为“将$i-1$划分为$j-1$个奇数之和的划分数

   即$f[i-1][j-1]$

2. 划分后的数中不含$1$
   
   使用截边法将划分出的$j$个数每一个都减去$1$
   
   转化为“将$i-j$划分为$j$个偶数之和的划分数”,
   
   即$g[i-j][j]$

所以$f[i][j]=f[i-1][j-1]+g[i-j][j]$。

$\sum_{i=0}^nf[n][i]$表示将$n$划分为若干奇数的方案数