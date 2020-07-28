---
author: zc
avatar: null
categories:
- - 刷题记录
commnet: 1
date: 2020-06-09 16:10
html: '<details><summary>查看原题</summary><div id=''from''></div><p><button onclick="document.getElementById(''from'').innerHTML=''<iframe
  src=&quot;https://www.luogu.com.cn/problem/AT5200&quot; width=100% height=800px
  style=&quot;border: none;&quot;><iframe>''" class=''mdui-btn mdui-btn-raised mdui-ripple''>点击加载</button><a
  class=''mdui-btn mdui-btn-raised mdui-ripple'' href="https://www.luogu.com.cn/problem/AT5200"
  target=''_blank''>点击跳转</a><p></details>'
permalink: LG AT5200 [AGC038C] LCMs
tags:
- 莫比乌斯
- 数论
thumbnail: null
title: LG AT5200 [AGC038C] LCMs
top: 0
---
设$a_i=\sum\limits_{j=1}^N[A_j=i],n=10^6$

$$
\sum_{i=1}^n\sum_{j=i+1}^n \operatorname{lcm}(A_i,A_j)\\
=\sum_{i=1}^n\sum_{j=i+1}^n a_ia_j\frac{ij}{\gcd(i,j)}\\
=\sum_{d=1}^n\frac 1d\sum_{i=1}^n\sum_{j=i+1}^n a_ia_j ij [\gcd(i,j)=d]\\
=\sum_{d=1}^n\frac 1d\sum_{i=1}^{n/d}\sum_{j=i+1}^{n/d} a_{id}a_{jd} idjd [\gcd(i,j)=1]\\
=\sum_{d=1}^n d \sum_{i=1}^{n/d}\sum_{j=i+1}^{n/d} a_{id}a_{jd} ij [\gcd(i,j)=1]\\
=\sum_{d=1}^n d \sum_{i=1}^{n/d}\sum_{j=i+1}^{n/d} a_{id}a_{jd} ij \sum_{x|i,x|j}\mu(x)\\
=\sum_{d=1}^n d \sum_{x=1}^n\mu(x)\sum_{i=1}^{n/dx}\sum_{j=i+1}^{n/dx} a_{idx}a_{jdx} ixjx\\
=\sum_{d=1}^n d \sum_{x=1}^n\mu(x)x^2 \sum_{i=1}^{n/dx}\sum_{j=i+1}^{n/dx} a_{idx}a_{jdx} ij\\
$$
设$T=dx$
$$
=\sum_{T=1}^n T \sum_{x|T}\mu(x)x \sum_{i=1}^{n/T}\sum_{j=i+1}^{n/T} a_{iT}a_{jT} ij
$$
```cpp
#include<bits/stdc++.h>
const int N=1000111,P=998244353;
int n,a[N],pri[N],mu[N];
bool v[N];
int f(int T){
	int k=n/T,sum=0,res=0;
	for(int i=1;i<=k;i++)
        (sum+=1ll*i*a[i*T]%P)%=P;
	for(int i=1;i<=k;i++)
		(sum+=P-1ll*i*a[i*T]%P)%=P,
		(res+=1ll*sum*i%P*a[i*T]%P)%=P;
	return res;
}
int main(){
    int t,x,ans=0;scanf("%d",&t);
    while(t--){
        scanf("%d",&x),++a[x];
        if(x>n)n=x;
    }
    mu[1]=1;
    for(int i=2,tt=0;i<=n;++i){
        if(!v[i])pri[++tt]=i,mu[i]=-1;
        for(int j=1;j<=tt&&i*pri[j]<=n;++j){
            v[i*pri[j]]=1;
            if(i%pri[j]==0)break;
            mu[i*pri[j]]=-mu[i];
        }
    }
    for(int i=1;i<=n;++i)
        mu[i]=(~mu[i])?(mu[i]*i):(mu[i]*i+P);
    for(int x=n;x;--x)
        for(int T=x+x;T<=n;T+=x)
            (mu[T]+=mu[x])%=P;
    for(int T=1;T<=n;++T)
        (ans+=1ll*a[T]*(a[T]-1)/2%P*T%P)%=P;
    for(int T=1;T<=n;++T)
        (ans+=1ll*T*mu[T]%P*f(T)%P)%=P;
    printf("%d\n",ans);
}
```
