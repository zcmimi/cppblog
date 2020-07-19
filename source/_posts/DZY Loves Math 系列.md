---
title: DZY Loves Math 系列 
date: 2020-06-09 16:22
tags: 
- 数论
- 数论分块
- 莫比乌斯

categories:
- [刷题记录]

top: 0 
html:
---

## DZY Loves Math

题意:

对于正整数$n$,定义$f(n)$为$n$所含质因子的最大幂指数

例如$f(1960)=f(2^3\cdot 5^1\cdot 7^2)=3,f(10007)=1,f(1)=0$

给定正整数$a,b$,求$\sum\limits_{i=1}^a\sum\limits_{j=1}^b f(\gcd(i,j))$

假设$a<b$

$$
\sum_{i=1}^a\sum_{j=1}^b f(\gcd(i,j))\\
=\sum_{d=1}^a f(d)\sum_{i=1}^a\sum_{j=1}^b[\gcd(i,j)=d]\\
=\sum_{d=1}^a f(d)\sum_{i=1}^{a/d}\sum_{j=1}^{b/d}[\gcd(i,j)=1]\\
=\sum_{d=1}^a f(d)\sum_{i=1}^{a/d}\sum_{j=1}^{b/d}\sum_{x|a,x|b}\mu(x)\\
=\sum_{d=1}^a f(d) \sum_{x=1}^a\mu(x)\sum_{i=1}^{a/dx}\sum_{j=1}^{b/dx}\\
=\sum_{d=1}^a f(d) \sum_{x=1}^a\mu(x)\left\lfloor\frac a{dx}\right\rfloor \left\lfloor\frac b{dx}\right\rfloor
$$

设$T=dx$

$$
=\sum_{T=1}^a \left\lfloor\frac a{T}\right\rfloor \left\lfloor\frac b{T}\right\rfloor \sum_{x|T} f(x)\mu(\frac Tx)
$$

前面可以数论分块,主要问题在于求$,\sum\limits_{x|T} f(x)\mu(\frac Tx)$

设$g(T)=,\sum\limits_{x|T} f(x)\mu(\frac Tx)$

可以发现当$\mu(x)$为$0$时没有贡献

设$T=p_1^{a_1}p_2^{a_2}\dots p_k^{a_k}$

当$a_1=a_2=\dots=a_k$时,
$g(T)=(-1)^{k+1}$。

否则$g(T)=0$

证明:

1. $a_1,a_2,\dots,a_k$不全相等时,$g(T)=0$
   
   如果所有质因子的次数不全相等,那么考虑次数最小的那个质因子,它无论是否选择都不会影响$f(\frac Tx)$的值,只是差在$μ(x)$的正负。这样选它和不选它,产生的贡献正好正负抵消,因此$g(T)$一定是$0$

2. $a_1=a_2=...=a_k$
   
   当且仅当每个质因子都选择时,$f(\frac Tx)$等于$a−1$,否则等于$a$。那么如果把$a−1$的那次贡献看作$a$,那么答案应该是0。所以只需要考虑把$a−1$看成$a$的变化。显然当$k$为奇数时$μ(x)$为负,$a−1$的贡献为负,因此答案为$1$；否则$a−1$的贡献为正,答案为$−1$

```cpp
#include<cstdio>
const int N=10000001;
int pri[N],mi[N],cnt[N],b[N];
long long g[N],res;
bool v[N];
void init(){
	for(int i=2,tt=0;i<N;++i){
		if(!v[i])pri[++tt]=i,cnt[i]=mi[i]=1;
		for(int j=1;j<=tt&&i*pri[j]<N;++j){
			v[i*pri[j]]=1;
			if(i%pri[j]==0){
				cnt[i*pri[j]]=cnt[i];//质因子个数
				mi[i*pri[j]]=mi[i]+1;//当前质因子幂次
                b[i*pri[j]]=b[i];//除当期质因子外最高幂次
				break;
			}
			else{
				if(!b[i]||b[i]==mi[i])b[i*pri[j]]=mi[i];
                else b[i*pri[j]]=-1;
                mi[i*pri[j]]=1,cnt[i*pri[j]]=cnt[i]+1;
			}
		}
        g[i]=g[i-1];
        if(!b[i]||b[i]==mi[i])g[i]+=(cnt[i]&1)?1:-1;
	}
}
int min(int x,int y){return x<y?x:y;}
void solve(){
	int a,b;res=0;
	scanf("%d%d",&a,&b);
	if(a>b)a^=b,b^=a,a^=b;
	for(int l=1,r;l<=a;l=r+1){
		r=min(a/(a/l),b/(b/l));
		res+=1ll*(a/l)*(b/l)*(g[r]-g[l-1]);
	}
	printf("%lld\n",res);
}
int main(){
    init();
	int T;scanf("%d",&T);
	while(T--)solve();
}
```