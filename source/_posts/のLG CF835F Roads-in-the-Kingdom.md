---
author: zc
avatar: null
categories:
- - 刷题记录
commnet: 1
date: 2019-12-21 19:47
html: '<details><summary>查看原题</summary><div id=''from''></div><p><button onclick="document.getElementById(''from'').innerHTML=''<iframe
  src=&quot;https://www.luogu.com.cn/problem/CF835F&quot; width=100% height=800px
  style=&quot;border: none;&quot;><iframe>''" class=''mdui-btn mdui-btn-raised mdui-ripple''>点击加载</button><a
  class=''mdui-btn mdui-btn-raised mdui-ripple'' href="https://www.luogu.com.cn/problem/CF835F"
  target=''_blank''>点击跳转</a><p></details>'
permalink: LG CF835F Roads-in-the-Kingdom
tags:
- 基环树
thumbnail: null
title: LG CF835F Roads-in-the-Kingdom
top: 0
---
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
#define N 400011
int n,cnt=0,head[N];
struct edge{
	int to,nxt,w;
}e[N*2];
void add(int x,int y,int w){
	e[++cnt].to=y;e[cnt].w=w;e[cnt].nxt=head[x];head[x]=cnt;
}
bool b[N];
int dfn[N],sz=0,pre[N];
int tt[N],tot=0;
void dfs(int x){
	dfn[x]=++sz;
	fl(i,x)
	if(to!=pre[x]){
		if(dfn[to]){
			if(dfn[to]<dfn[x])continue;
			tt[tot++]=x;b[x]=1;
			int y=to;
			for(;y!=x;y=pre[y])b[y]=1,tt[tot++]=y;
		}
		else pre[to]=x,dfs(to);
	}
}
ll f[N],d[N],sum[N],ans=0,tmp=0;
void dp(int x,int fa){
	fl(i,x)
	if(to!=fa&&!b[to]){
		dp(to,x);
		f[x]=MAX(f[x],MAX(f[to],d[x]+d[to]+e[i].w));
		d[x]=MAX(d[x],d[to]+e[i].w);
	}
}
typedef pair<ll,int>pli;
multiset<pli,greater<pli>>T1,T2;
int main(){
	in>>n;
	int x,y,w;
	Fur(i,1,n)in>>x>>y>>w,add(x,y,w),add(y,x,w);
	tot=0;
	int sl=0;
	dfs(1);
	tt[tot]=tt[0];
	sum[sl++]=0;
	Fur(i,0,tot-1)
		fl(j,tt[i])
			if(to==tt[i+1])sum[sl++]=e[j].w;
	Fur(i,1,tot)
		tt[i+tot]=tt[i],sum[i+tot]=sum[i];

	Fur(i,1,tot*2-1)sum[i]+=sum[i-1];
	Fur(i,0,tot-1)dp(tt[i],0),tmp=MAX(tmp,MAX(f[tt[i]],d[tt[i]]));

	ans=(1ll<<50);
	Fur(i,0,tot-1)
		T1.insert(make_pair(d[tt[i]]+sum[i],i)),
		T2.insert(make_pair(d[tt[i]]-sum[i],i));

	Fur(i,0,tot-1){
		ll t;
		if(T1.begin()->second==T2.begin()->second){
			multiset<pli,greater<pli>>::iterator ptr = T2.begin();
			++ptr;
			t=T1.begin()->first+ptr->first;
			ptr=T1.begin();
			++ptr;
			t=MAX(t,ptr->first+T2.begin()->first);
		}
		else
			t=T1.begin()->first+T2.begin()->first;
		
		ans=MIN(ans,t);
		T1.erase(make_pair(d[tt[i]]+sum[i],i)),
		T2.erase(make_pair(d[tt[i]]-sum[i],i));

		T1.insert(make_pair(d[tt[i+tot]]+sum[i+tot],i+tot)),
		T2.insert(make_pair(d[tt[i+tot]]-sum[i+tot],i+tot));
	}
	out<<MAX(ans,tmp)<<ln;
}
```
