---
author: zc
avatar: null
categories:
- - "\u5237\u9898\u8BB0\u5F55"
commnet: 1
date: 2019-12-21 19:47
html: "<details><summary>\u67E5\u770B\u539F\u9898</summary><div id='from'></div><p><button\
  \ onclick=\"document.getElementById('from').innerHTML='<iframe src=&quot;https://www.luogu.com.cn/problem/UVA10308&quot;\
  \ width=100% height=800px style=&quot;border: none;&quot;><iframe>'\" class='mdui-btn\
  \ mdui-btn-raised mdui-ripple'>\u70B9\u51FB\u52A0\u8F7D</button><a class='mdui-btn\
  \ mdui-btn-raised mdui-ripple' href=\"https://www.luogu.com.cn/problem/UVA10308\"\
  \ target='_blank'>\u70B9\u51FB\u8DF3\u8F6C</a><p></details>"
permalink: LG UVA10308 Roads-in-the-North
tags:
- "\u6811\u7684\u76F4\u5F84"
thumbnail: null
title: LG UVA10308 Roads-in-the-North
top: 0
---
求树的直径

读入毒瘤

自己探索吧(不怀好意

(tips:getline,ssstream)

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
#define N 20000011
struct edge{
	int nxt,to,w;
}e[N*2];
int d[N],head[N],q[N],f[N],n,k=0,cnt=0;
void add(int x,int y,int w){
	e[++cnt].to=y;e[cnt].w=w;e[cnt].nxt=head[x];head[x]=cnt;
}
void bfs(int x){
	int h=0,t=1;
	q[h]=x;
	clr(d,0);clr(f,0);
	while(h<t){
		int x=q[h++];
		if(d[k]<d[x])k=x;
		fl(i,x)if(to!=f[x]){
			f[to]=x;d[to]=d[x]+e[i].w;
			q[t++]=to;
		}
	}
}
int main(){
	int x,y,w;
	fcin;
	string s;
	stringstream ss;
	while(getline(cin,s)){
		cnt=0;clr(head,0);
		ss.clear();
		ss.str(s);
		while(ss>>x>>y>>w){
			add(x,y,w);add(y,x,w);
			getline(cin,s);
			ss.clear();
			ss.str(s);
		}
		bfs(1);
		bfs(k);
		cout<<d[k]<<endl;
	}
}
```
