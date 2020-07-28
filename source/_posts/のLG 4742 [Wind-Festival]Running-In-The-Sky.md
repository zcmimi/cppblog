---
author: zc
avatar: null
categories:
- - 刷题记录
commnet: 1
date: 2019-12-21 19:47
html: '<details><summary>查看原题</summary><div id=''from''></div><p><button onclick="document.getElementById(''from'').innerHTML=''<iframe
  src=&quot;https://www.luogu.com.cn/problem/P4742&quot; width=100% height=800px style=&quot;border:
  none;&quot;><iframe>''" class=''mdui-btn mdui-btn-raised mdui-ripple''>点击加载</button><a
  class=''mdui-btn mdui-btn-raised mdui-ripple'' href="https://www.luogu.com.cn/problem/P4742"
  target=''_blank''>点击跳转</a><p></details>'
permalink: LG 4742 [Wind-Festival]Running-In-The-Sky
tags:
- tarjan
thumbnail: null
title: LG 4742 [Wind-Festival]Running-In-The-Sky
top: 0
---
先缩点,然后跑最长路

然后更新的时候顺便记录最大亮度就可以了

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
#define N 2000011
int head[N],n,m,cnt=0,z[N],bl[N],dfn[N],low[N],c[N],tp=0,sz=0,mx[N];
int Head[N],Cnt=0,r[N],q[N],top=0,f[N],F[N];
bool v[N];
struct edge{
	int x,to,nxt;
}e[N*10],E[N*10];
void add(int x,int y){
	e[++cnt].to=y;e[cnt].x=x;e[cnt].nxt=head[x];head[x]=cnt;
}
void Add(int x,int y){
	E[++Cnt].to=y;E[Cnt].x=x;E[Cnt].nxt=Head[x];Head[x]=Cnt;
}
void tarjan(ll x){
	dfn[x]=low[x]=++sz;v[x]=1;z[++tp]=x;
	fl(i,x)
	if(!dfn[to]){
		tarjan(to);
		low[x]=min(low[x],low[to]);
	}
	else if(v[to])low[x]=min(low[x],dfn[to]);
	if(low[x]==dfn[x])
	while(ll k=z[tp--]){
		v[k]=0,bl[k]=x;
		if(k==x)break;
		c[x]+=c[k];
	}
}
int main(){
	in>>n>>m;
	Fur(i,1,n)in>>c[i],mx[i]=c[i];
	int x,y;
	Fur(i,1,m)in>>x>>y,add(x,y);
	Fur(i,1,n)if(!dfn[i])tarjan(i);
	Fur(i,1,m){
		x=bl[e[i].x];y=bl[e[i].to];
		if(x!=y)Add(x,y),r[y]++;
	}
	Fur(i,1,n)if(bl[i]==i&&!r[i])q[++top]=i,f[i]=c[i],F[i]=mx[i];
	while(top){
		x=q[top--];
		for(int i=Head[x],to;to=E[i].to,i;i=E[i].nxt){
			if(f[x]+c[to]==f[to])
				F[to]=MAX(F[to],MAX(F[x],mx[to]));
			
			if(f[x]+c[to]>f[to]){
				f[to]=f[x]+c[to];
				F[to]=MAX(F[x],mx[to]);
			}
			

			if(--r[to]==0)q[++top]=to;
		}
	}
	int ans=0,as=0;
	Fur(i,1,n){
		if(f[i]>ans)ans=f[i],as=F[i];
		else if(f[i]==ans)as=MAX(as,F[i]);
	}
	out<<ans<<" "<<as<<ln;
}
```
