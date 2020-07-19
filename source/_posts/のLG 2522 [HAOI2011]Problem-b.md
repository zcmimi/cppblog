---
author: zc
avatar: null
categories:
- - "\u5237\u9898\u8BB0\u5F55"
commnet: 1
date: 2020-03-15 16:05
html: "<details><summary>\u67E5\u770B\u539F\u9898</summary><div id='from'></div><p><button\
  \ onclick=\"document.getElementById('from').innerHTML='<iframe src=&quot;https://www.luogu.com.cn/problem/P2522&quot;\
  \ width=100% height=800px style=&quot;border: none;&quot;><iframe>'\" class='mdui-btn\
  \ mdui-btn-raised mdui-ripple'>\u70B9\u51FB\u52A0\u8F7D</button><a class='mdui-btn\
  \ mdui-btn-raised mdui-ripple' href=\"https://www.luogu.com.cn/problem/P2522\" target='_blank'>\u70B9\
  \u51FB\u8DF3\u8F6C</a><p></details>"
permalink: LG 2522 [HAOI2011]Problem-b
tags:
- "\u6570\u8BBA"
- "\u6B27\u62C9\u51FD\u6570"
- "\u83AB\u6BD4\u4E4C\u65AF"
thumbnail: null
title: LG 2522 [HAOI2011]Problem-b
top: 0
---
把题目强行转换为[[POI2007]ZAP-Queries](https://www.luogu.org/problemnew/show/P3455)


$Ans((1,b),(1,d))-Ans((1,b),(1,c-1))-Ans((1,a-1),(1,d))+Ans((1,a-1),(1,c-1))$



$$
f=\sum_{i=1}^{a}\sum_{j=1}^{b}[gcd(i,j)=d] \\
f=\sum_{i=1}^{\left \lfloor \frac ad \right \rfloor} \sum_{j=1}^{\left \lfloor \frac bd \right \rfloor} [gcd(i,j)=1] \\
\because \sum_{x|n} \mu(x) = [n=1] \\
\therefore 
f= \sum_{i=1}^{\left \lfloor \frac ad \right \rfloor} \sum_{j=1}^{\left \lfloor \frac bd \right \rfloor}
\sum_{k|gcd(i,j)} \mu(k) \\
f=\sum_{k=1}^{\left \lfloor \frac ad \right \rfloor}\mu(k)\left \lfloor \frac a{dk} \right \rfloor \left \lfloor \frac b{dk} \right \rfloor
$$
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
#define N 50000
int t,d,mu[N+11],pri[N+11],tot=0;
bool f[N+11];
void sm(int n){
	f[1]=mu[1]=1;
	Fur(i,2,n){
		if(!f[i])pri[++tot]=i,mu[i]=-1;
		Fur(j,1,tot){
			if(pri[j]*i>n)break;
			f[i*pri[j]]=1;
			if(i%pri[j])mu[i*pri[j]]=-mu[i];
			else break;
		}
	}
	Fur(i,2,n)mu[i]+=mu[i-1];
}
int ask(int a,int b){
	int n=a/d,m=b/d,ans=0;
	if(n>m)SWAP(n,m);
	for(int l=1,r=0;l<=n;l=r+1){
		r=MIN(n/(n/l),m/(m/l));
		ans+=(n/l)*(m/l)*(mu[r]-mu[l-1]);
	}	
	return ans;
}
int main(){
	sm(N);
	in>>t;
	while(t--){
		int a,b,c,D;
		in>>a>>b>>c>>D>>d;
		out<<ask(b,D)-ask(b,c-1)-ask(a-1,D)+ask(a-1,c-1)<<ln;
	}
}
```
