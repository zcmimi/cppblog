---
author: zc
avatar: null
categories:
- - 刷题记录
commnet: 1
date: 2020-07-22 19:27
html: '<details><summary>查看原题</summary><div id=''from''></div><p><button onclick="document.getElementById(''from'').innerHTML=''<iframe
  src=&quot;https://loj.ac/problem/6187&quot; width=100% height=800px style=&quot;border:
  none;&quot;><iframe>''" class=''mdui-btn mdui-btn-raised mdui-ripple''>点击加载</button><a
  class=''mdui-btn mdui-btn-raised mdui-ripple'' href="https://loj.ac/problem/6187"
  target=''_blank''>点击跳转</a><p></details>'
permalink: LOJ 6187 Odd
tags:
- hash
- 分块
- 随机
thumbnail: null
title: LOJ 6187 Odd
top: 0
---
异或一个数两次,可以抵消

我们可以给区间中所有相同的数都赋一个新的随机数值,防止异或时出现干扰

设$pre_i$为$i$位置的数上一次出现的数,$v_i$为位置$i$新赋值的数,$S_i$为异或前缀和

若区间$[l,r]$中所有数出现的数出现的次数是奇数,那么$S_r\oplus S_{l-1}$等于$\{v_i|pre_i<x,i\in [l,r]\}$的异或和

枚举$r$,设$p_x$为$\{v_i|pre_i<x,i\in [x,r]\}$异或和

那么相当于求满足$S_r\oplus S_{x-1}\oplus p_x=0$

当$r$变为$r+1$,$\{p_i|i\in [pre_{r+1}+1,r]\}$异或上$v_{r+1}$

问题也就转化为了: 区间异或,区间查询某个数出现次数

使用分块+hash解决
```cpp
#include<bits/stdc++.h>
namespace IO{
	char buf[1<<20|5];
	const char *ed=buf+(1<<20);
	char *st=buf+(1<<20);
	#define gc() (((st==ed)?(fread(buf,1,1<<20,stdin),st=buf):0),*st++)
	template<class T>inline void rd(T &x){
    	char ch;x=0;
    	do ch = gc();while(ch<'0' or ch>'9');
    	while(ch>='0' and ch<= '9')x=x*10+(ch&15),ch=gc();
    }
    #undef gc
};
typedef unsigned long long ll;
const int N=200011,P=10007;
struct hash{
	int head[P+1],cnt;
	struct edge{int nxt;ll to,w;}e[20000];
	hash(){cnt=0;}
	ll&operator()(ll n,bool t=1){
		int x=n%P+1;
		for(int i=head[x];i;i=e[i].nxt)
			if(e[i].to==n)return e[i].w;
		if(t){
			e[++cnt].to=n,e[cnt].nxt=head[x],head[x]=cnt;
			return e[cnt].w=0;
		}
		else return e[0].w;
	}
	void init(){while(cnt)head[e[cnt--].to%P+1]=0;}
}T[450];
int n,blk,pre[N],b[1000001],bl[N],L[450],R[450];
ll a[N],s[N],laz[450],p[N],rnd[1000001];
void build(int k){
	T[k].init();
	for(int i=L[k];i<=R[k];++i)++T[k](p[i]);
}
void add(int l,int r,ll v){
	if(bl[l]==bl[r]){
		for(int i=l;i<=r;++i)p[i]^=v;
		build(bl[l]);
		return;
	}
	for(int i=l;bl[i]==bl[l];++i)p[i]^=v;
	for(int i=bl[l]+1;i<bl[r];++i)laz[i]^=v;
	for(int i=r;bl[i]==bl[r];--i)p[i]^=v;
	build(bl[l]),build(bl[r]);
}
int ask(int r){
	int res=0;ll v=s[r];
	for(int i=1;i<bl[r];++i)
		res+=T[i](v^laz[i],0);
	v^=laz[bl[r]];
	for(int i=r;bl[i]==bl[r];--i)
		if(v==p[i])++res;
	return res;
}
int main(){
	ll ans=0;
	IO::rd(n);blk=sqrt(n);
	rnd[0]=233;
	for(int i=1;i<=1000000;++i)rnd[i]=rnd[i-1]*482711ll;
	for(int i=1;i<=n;++i){
		ll x;IO::rd(x);
		pre[i]=b[x],b[x]=i;
		s[i]=s[i-1]^(a[i]=rnd[x]);
		bl[i]=(i-1)/blk+1;
		++T[bl[i]](p[i]=s[i-1]);
	}
	for(int i=1;i<=bl[n];++i)
		L[i]=R[i-1]+1,R[i]=R[i-1]+blk;
	R[bl[n]]=n;
	
	for(int i=1;i<=n;++i)
		add(pre[i]+1,i,a[i]),
		ans+=ask(i);
		
	printf("%lld\n",ans);
}
```
