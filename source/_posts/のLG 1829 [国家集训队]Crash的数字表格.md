---
author: zc
avatar: null
categories:
- - 刷题记录
commnet: 1
date: 2020-03-14 03:42
html: '<details><summary>查看原题</summary><div id=''from''></div><p><button onclick="document.getElementById(''from'').innerHTML=''<iframe
  src=&quot;https://www.luogu.com.cn/problem/P1829&quot; width=100% height=800px style=&quot;border:
  none;&quot;><iframe>''" class=''mdui-btn mdui-btn-raised mdui-ripple''>点击加载</button><a
  class=''mdui-btn mdui-btn-raised mdui-ripple'' href="https://www.luogu.com.cn/problem/P1829"
  target=''_blank''>点击跳转</a><p></details>'
permalink: LG 1829 [国家集训队]Crash的数字表格
tags:
- 数论
- 莫比乌斯
- 数论分块
thumbnail: null
title: LG 1829 [国家集训队]Crash的数字表格
top: 0
---
求:
$$\sum_{i=1}^n\sum_{j=1}^mlcm(i,j)$$

设$n<m$
$$
\sum_{i=1}^n\sum_{j=1}^mlcm(i,j)
\\
=\sum_{i=1}^n\sum_{j=1}^m \frac{ij}{\gcd(i,j)}
\\
=\sum_{d=1}^n\sum_{i=1}^n\sum_{j=1}^m \frac {ij}d[\gcd(i,j)=d]
$$

设$i'=\left \lfloor \frac id \right \rfloor,j'=\left \lfloor \frac jd \right \rfloor$

$$
\\
=\sum_{d=1}^n\sum_{i=1}^{\left \lfloor \frac nd \right \rfloor}\sum_{j=1}^{\left \lfloor \frac md \right \rfloor} ijd[\gcd(i,j)=1]
$$

把$\sum\limits_{i=1}^{\left \lfloor \frac nd \right \rfloor}\sum\limits_{j=1}^{\left \lfloor \frac md \right \rfloor} ij[\gcd(i,j)=1]$拆出来,

设$sum(n,m)=$

$$
\sum_{i=1}^n\sum_{j=1}^n ij[\gcd(i,j)=1]
\\
=\sum_{i=1}^n\sum_{j=1}^m\sum_{d|gcd(i,j)} ij\mu(d)
\\
=\sum_{d=1}^n\sum_{d|i}\sum_{d|j} ij\mu(d)
$$

设$i'=\left \lfloor \frac id \right \rfloor,j'=\left \lfloor \frac jd \right \rfloor$

$$
=\sum_{d=1}^n\mu(d)d^2\sum_{i=1}^{\left \lfloor \frac nd\right \rfloor}\sum_{j=1}^{\left \lfloor \frac md\right \rfloor} ij
$$

设$g(n,m)=\sum\limits_{i=1}^n\sum\limits_{j=1}^mij$

$$
g(n,m)=\frac{n(n+1)}2\cdot \frac{m(n+1)}2
$$

最后

$$
ans=\sum_{d=1}^n d\cdot sum(\left\lfloor \frac nd \right\rfloor,\left\lfloor \frac md \right\rfloor)
\\
sum(n,m)=\sum_{d=1}^n\mu(d)d^2 g(\left\lfloor \frac nd \right\rfloor,\left\lfloor \frac md \right\rfloor)
$$
```cpp
#include<cstdio>
int min(int x,int y){return x<y?x:y;}
const int N=10000001,P=20101009;
int mu[N],pri[664580],cnt=0,s[N];
bool f[N];
int g(int n,int m){return 1ll*(1ll*n*(n+1)/2%P)*(1ll*m*(m+1)/2%P)%P;}
int sum(int n,int m){
    if(n>m)n^=m,m^=n,n^=m;
    int ans=0;
    for(int l=1,r;l<=n;l=r+1){
        r=min(n/(n/l),m/(m/l));
        ans+=1ll*((s[r]-s[l-1]+P)%P)*g(n/l,m/l)%P;
        ans%=P;
    }
    return ans;
}
int main(){
    int n,m,k,ans=0;
    scanf("%d%d",&n,&m);
    if(n>m)n^=m,m^=n,n^=m;
    mu[1]=1;
    for(int i=2;i<=n;++i){
        if(!f[i])pri[++cnt]=i,mu[i]=-1;
        for(int j=1;j<=cnt&&pri[j]*i<=n;++j){
            f[i*pri[j]]=1;
            if(i%pri[j])mu[i*pri[j]]=-mu[i];
            else break;
        }
    }
    for(int i=1;i<=n;++i)s[i]=(s[i-1]+1ll*mu[i]*i*i%P+P)%P;
    for(int l=1,r;l<=n;l=r+1){
        r=min(n/(n/l),m/(m/l));
        ans=(ans+1ll*(r-l+1)*(r+l)/2%P*sum(n/l,m/l)%P)%P;
    }
    printf("%d\n",ans);
}
```
