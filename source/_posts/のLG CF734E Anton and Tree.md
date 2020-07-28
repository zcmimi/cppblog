---
author: zc
avatar: null
categories:
- - 刷题记录
commnet: 1
date: 2019-12-21 19:47
html: '<details><summary>查看原题</summary><div id=''from''></div><p><button onclick="document.getElementById(''from'').innerHTML=''<iframe
  src=&quot;https://www.luogu.com.cn/problem/CF734E&quot; width=100% height=800px
  style=&quot;border: none;&quot;><iframe>''" class=''mdui-btn mdui-btn-raised mdui-ripple''>点击加载</button><a
  class=''mdui-btn mdui-btn-raised mdui-ripple'' href="https://www.luogu.com.cn/problem/CF734E"
  target=''_blank''>点击跳转</a><p></details>'
permalink: LG CF734E Anton and Tree
tags:
- 并查集
- 树的直径
thumbnail: null
title: LG CF734E Anton and Tree
top: 0
---
先用并查集求出所有连通块(相邻且相同颜色的节点)

接着是相邻节点的颜色都不一样的一棵树

最少次数就是树的直径/2了

```cpp
#include<bits/stdc++.h>
using namespace std;
#define Fur(i,x,y) for(int i=x;i<=y;i++)
#define N 200011
int n,a[N],b[N];
struct edge{
	int to,nxt;
}e[N*2];
int head[N],cnt=1;
void add(int x,int y){
	e[++cnt].to=y;e[cnt].nxt=head[x];head[x]=cnt;
}
int mx=0,d[N];
void dfs(int x,int f){
	if(d[x]>d[mx])mx=x;
	for(int i=head[x],to;to=e[i].to,i;i=e[i].nxt)
		if(to!=f)d[to]=d[x]+1,dfs(to,x);
}
int f[N];
int gf(int x){
	return (x==f[x])?x:(f[x]=gf(f[x]));
}
int main(){
	scanf("%d",&n);
	Fur(i,1,n)scanf("%d",&a[i]),f[i]=i;
	int x,y,t;
	Fur(i,1,n-1)
		scanf("%d%d",&x,&y),
		add(x,y),add(y,x);
		
	Fur(i,2,cnt){
		x=e[i].to,y=e[i^1].to;
		if(a[x]==a[y]&&gf(x)!=gf(y))f[f[y]]=f[x];
		++i;
	}
	t=cnt;cnt=0;
	memset(head,0,sizeof(head));
	Fur(i,2,t){
		x=gf(e[i].to),y=gf(e[i^1].to);
		if(x!=y)add(x,y),add(y,x);
		++i;
	}
	dfs(f[1],0);
	memset(d,0,sizeof(d));
	dfs(mx,0);
	printf("%d\n",(d[mx]+1)/2);
}
```
