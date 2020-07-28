---
author: zc
avatar: null
categories:
- - 刷题记录
commnet: 1
date: 2019-12-21 19:47
html: '<details><summary>查看原题</summary><div id=''from''></div><p><button onclick="document.getElementById(''from'').innerHTML=''<iframe
  src=&quot;https://www.luogu.com.cn/problem/P5664&quot; width=100% height=800px style=&quot;border:
  none;&quot;><iframe>''" class=''mdui-btn mdui-btn-raised mdui-ripple''>点击加载</button><a
  class=''mdui-btn mdui-btn-raised mdui-ripple'' href="https://www.luogu.com.cn/problem/P5664"
  target=''_blank''>点击跳转</a><p></details>'
permalink: LG 5664 Emiya-家今天的饭
tags:
- 容斥
- 动态规划
thumbnail: null
title: LG 5664 Emiya-家今天的饭
top: 0
---
## 题意：

给出一个矩阵,要求每行只能选一个节点,每列选的节点不能超过所有选的节点的一半,不能不选,
给出每个节点的选择方案数,求总方案数

## 解法

考虑到限制是每列选择的不能超过一半,我们可以想到不合法的最多只有一列 

我们可以用总方案数减去不符合的

$s_i=\sum_{j=1}^m a_{ij}$

总方案数：$\prod_{i=1}^n (s_i+1) - 1$

$\because k=\frac {tot}2$

所以我们有一个很妙的方法:

设选中目标行之外的权值+1,不选+0,选中目标行权值位+2

最后只要权值$> n$,那么目标行一定被选了超过$\frac n2$次

设$f(i,k)$表示总共选了$i$次(也就是选到第$i$行)权值为$k$的方案数 


$f(i,k) += f(i-1,k)*(s_i-a_{ij})$(当前行不选目标列

$f(i,k+1) += f(i-1,k)$(当前行完全不选

$f(i,k+2) += f(i-1,k)\times a_{ij}$(当前行选中目标列

$ans = \prod_{i=1}^n (s_i+1) - 1 - \sum_{i=n+1}^{2n} f(n,i)$
```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 111
typedef long long ll;
const int mod=998244353;
int a[N][2011],n,m;
ll f[N][2011],s[N];
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
			scanf("%d",&a[i][j]),
            s[i]=(s[i]+a[i][j])%mod;
			
	ll ans=1; 
	for(int i=1;i<=n;++i)
		ans=(ans*(s[i]+1))%mod;
	
    --ans;
	for(int j=1;j<=m;++j){
        memset(f,0,sizeof f);
        f[0][0]=1;
        for(int i=1;i<=n;++i)
            for(int k=0;k<=n*2;++k){
                f[i][k]=(f[i][k]+f[i-1][k]*(s[i]-a[i][j]))%mod;
                f[i][k+1]=(f[i][k+1]+f[i-1][k])%mod;
                f[i][k+2]=(f[i][k+2]+f[i-1][k]*a[i][j])%mod;
            }
        for(int i=n+1;i<=n*2;++i)
            ans=(ans-f[n][i])%mod;
    }
    printf("%lld\n",(ans+mod)%mod);
}
```
