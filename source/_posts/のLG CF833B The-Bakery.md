---
author: zc
avatar: null
categories:
- - 刷题记录
commnet: 1
date: 2019-12-21 19:47
html: '<details><summary>查看原题</summary><div id=''from''></div><p><button onclick="document.getElementById(''from'').innerHTML=''<iframe
  src=&quot;https://www.luogu.com.cn/problem/CF833B&quot; width=100% height=800px
  style=&quot;border: none;&quot;><iframe>''" class=''mdui-btn mdui-btn-raised mdui-ripple''>点击加载</button><a
  class=''mdui-btn mdui-btn-raised mdui-ripple'' href="https://www.luogu.com.cn/problem/CF833B"
  target=''_blank''>点击跳转</a><p></details>'
permalink: LG CF833B The-Bakery
tags:
- 动态规划
- 线段树
thumbnail: null
title: LG CF833B The-Bakery
top: 0
---
设$f[i][k]$为第$i$位,分成$k$段

$f[i][k] = MAX(f[j][k-1] + cnt[j+1][i])$

这样的话肯定复杂度爆炸

既然看到$MAX$,那是不是可以用线段树优化呢？

记录每个点贡献的范围,更新时把这个范围的点++就可以了。

相信看代码可以看懂

~~其实我还加了滚动数组OwO~~
```cpp
#include<bits/stdc++.h>
namespace ZDY{
	#pragma GCC optimize(3)
	#define il __inline__ __attribute__ ((always_inline))
	#define rg register
	#define ll long long
	#define ull unsigned long long
	#define db double
	#define sht short
	#define MB template <class T>il
	#define Fur(i,x,y) for(int i=x;i<=y;i++)
	#define Fdr(i,x,y) for(int i=x;i>=y;i--)
	#define fl(i,x) for(int i=head[x],to;to=e[i].to,i;i=e[i].nxt)
	#define clr(x,y) memset(x,y,sizeof(x))
	#define cpy(x,y) memcpy(x,y,sizeof(x))
	#define fin(s) freopen(s".in","r",stdin)
	#define fout(s) freopen(s".out","w",stdout)
	#define fcin ios::sync_with_stdio(false)
	#define l2(n) (int(log2(n)))
	#define inf 0x3f3f3f3f
	MB T ABS(T x){return x>0?x:-x;}
	MB T MAX(T x,T y){return x>y?x:y;}
	MB T MIN(T x,T y){return x<y?x:y;}
	MB T GCD(T x,T y){return y?GCD(y,x%y):x;}
	MB void SWAP(T &x,T &y){T t=x;x=y;y=t;}
}using namespace ZDY;using namespace std;
namespace IO{const char* ln="\n";const int str=1<<20;struct IN{char buf[str],*s,*t;bool _;IN():s(buf),t(buf),_(0){}il char gc(){return s==t&&((t=(s=buf)+fread(buf,1,str,stdin))==s)?EOF:(*s++);}IN&operator>>(char&ch){if(_)return *this;char c;while((c=gc())!=EOF&&isspace(c));if(c==EOF)_=1;else ch=c;return *this;}IN& operator>>(char* ch){if(_)return *this;char c;while((c=gc())!=EOF&&isspace(c));if(c==EOF)return _=1,*this;*ch=c;ch++;while((c=gc())!=EOF&&!isspace(c))*ch=c,ch++;if(c==EOF)_=1;return *this;}IN& operator>>(string& ch){if(_)return *this;char c;while((c=gc())!=EOF&&isspace(c));if(c==EOF)return _=1,*this;ch+=c;while((c=gc())!=EOF&&!isspace(c))ch+=c;if(c==EOF)_=1;return *this;}template<typename T>IN&operator>>(T&x){if(_)return *this;char c=gc();bool ff=0;while(c!=EOF&&(c<'0'||c>'9'))ff^=(c=='-'),c=gc();if(c==EOF){_=1;return *this;}x=0;while(c!=EOF&&'0'<=c&&c<='9')x=(x<<3)+(x<<1)+c-48,c=gc();if(c==EOF)_=1;if(ff)x=-x;return *this;}}in;struct OUT{char buf[str],*s,*t;OUT():s(buf),t(buf+str){}~OUT(){fwrite(buf,1,s-buf,stdout);}void pt(char c){(s==t)?(fwrite(s=buf,1,str,stdout),*s++=c):(*s++=c);}OUT&operator<<(const char*s){while(*s)pt(*s++);return *this;}OUT&operator<<(char*s){while(*s)pt(*s++);return *this;}OUT&operator<<(string s){for(int i=0;s[i];i++)pt(s[i]);return *this;}template<typename T>OUT&operator<<(T x){if(!x)return pt('0'),*this;if(x<0)pt('-'),x=-x;char a[30],t=0;while(x)a[t++]=x%10,x/=10;while(t--)pt(a[t]+'0');return *this;}}out;}using namespace IO;
#define N 35011
int pre[N],p[N],n,k,s[N<<2],laz[N<<2],f[N];
#define ls rt<<1
#define rs rt<<1|1
#define pu s[rt]=MAX(s[ls],s[rs]);
void build(int l,int r,int rt){
	if(l==r){
		s[rt]=f[l-1];laz[rt]=0;
		return;
	}
	int m=(l+r)>>1;
	build(l,m,ls);build(m+1,r,rs);
	pu;
}
void pd(int rt){
	if(laz[rt]){
		laz[ls]+=laz[rt];laz[rs]+=laz[rt];
		s[ls]+=laz[rt];s[rs]+=laz[rt];
		laz[rt]=0;
	}
}
void upd(int L,int R,int l,int r,int rt){
	if(L<=l&&r<=R){
		s[rt]++;
		laz[rt]++;
		return;
	}
	int m=(l+r)>>1;
	pd(rt);
	if(L<=m)upd(L,R,l,m,ls);
	if(R>m)upd(L,R,m+1,r,rs);
	pu;
}
int ask(int L,int R,int l,int r,int rt){
	if(L<=l&&r<=R)return s[rt];
	int m=(l+r)>>1,ans=0;
	pd(rt);
	if(L<=m)ans=ask(L,R,l,m,ls);
	if(R>m)ans=MAX(ans,ask(L,R,m+1,r,rs));
	return ans;
}
int main(){
	in>>n>>k;
	int x;
	Fur(i,1,n)
		in>>x,
		pre[i]=p[x]+1,
		p[x]=i;
		
	Fur(i,1,k){
		clr(laz,0);clr(s,0);
		build(1,n,1);
		Fur(j,1,n)
			upd(pre[j],j,1,n,1),
			f[j]=ask(1,j,1,n,1);
	}
	out<<f[n]<<ln;
}
```
