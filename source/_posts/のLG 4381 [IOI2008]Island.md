---
author: zc
avatar: null
categories:
- - 刷题记录
commnet: 1
date: 2020-01-24 00:21
html: '<details><summary>查看原题</summary><div id=''from''></div><p><button onclick="document.getElementById(''from'').innerHTML=''<iframe
  src=&quot;https://www.luogu.com.cn/problem/P4381&quot; width=100% height=800px style=&quot;border:
  none;&quot;><iframe>''" class=''mdui-btn mdui-btn-raised mdui-ripple''>点击加载</button><a
  class=''mdui-btn mdui-btn-raised mdui-ripple'' href="https://www.luogu.com.cn/problem/P4381"
  target=''_blank''>点击跳转</a><p></details>'
permalink: LG 4381 [IOI2008]Island
tags:
- 基环树
thumbnail: null
title: LG 4381 [IOI2008]Island
top: 0
---
求基环树直径

先找出环,把环当根节点,找出每棵子树的直径和最大深度$d_x$

接着就要在环上找到两点$x,y$使$d_x+dis(x,y)+d_y$最大

可以破环后用单调队列$\mathcal O(n)$处理
```cpp
#include<cstdio>
const int N=1000011;
#define ll long long
#define fl(i,x) for(int i=head[x],to;to=e[i].to,i;i=e[i].nxt)
inline ll max(ll x,ll y){return x>y?x:y;}
int n,cnt=0,head[N],dfn[N],sz=0,pre[N],tt[N],tot=0,q[N];
bool b[N];
struct edge{
    int to,nxt,w;
}e[N<<1];
void add(int x,int y,int w){
    e[++cnt].to=y;e[cnt].nxt=head[x];head[x]=cnt;e[cnt].w=w;
}
void dfs(int x){
    dfn[x]=++sz;
    fl(i,x)if(to!=pre[x]){
        if(dfn[to]){
            if(dfn[to]<dfn[x])continue;
            b[tt[++tot]=x]=1;
            for(int y=to;y!=x;y=pre[y])b[tt[++tot]=y]=1;
        }
        else pre[to]=x,dfs(to);
    }
}
ll f[N],d[N],s[N],ans=0;
void dp(int x,int fa){
    fl(i,x)if(to!=fa&&!b[to]){
        dp(to,x);
        f[x]=max(f[x],max(f[to],d[x]+d[to]+e[i].w));
        d[x]=max(d[x],d[to]+e[i].w);
    }
}
void work(int x){
    ll tmp=0;
    tot=0;
    dfs(x);
    tt[tot+1]=tt[1];
    int p=0;
    for(int i=1;i<=tot;++i)
        fl(j,tt[i])if(to==tt[i+1])
            s[++p]=e[j].w;
    for(int i=1;i<=tot+1;++i)
        tt[i+tot]=tt[i],s[i+tot]=s[i];
    for(int i=2;i<=tot*2;++i)s[i]+=s[i-1];
    for(int i=1;i<=tot;++i)dp(tt[i],0),tmp=max(tmp,max(f[tt[i]],d[tt[i]]));
    int h=1,t=0;
    for(int i=1;i<=tot*2;++i){
        while(h<=t&&i-q[h]>=tot)++h;
        if(h<=t)tmp=max(tmp,d[tt[i]]+d[tt[q[h]]]+s[i-1]-s[q[h]-1]);
        while(h<=t&&d[tt[i]]-s[i-1]>=d[tt[q[t]]]-s[q[t]-1])--t;
        q[++t]=i;
    }
    ans+=tmp;
}
int main(){
    scanf("%d",&n);
    int y,w;
    for(int i=1;i<=n;++i)
        scanf("%d%d",&y,&w),
        add(i,y,w),add(y,i,w);
    for(int i=1;i<=n;++i)if(!dfn[i])work(i);
    printf("%lld\n",ans);
}
```
