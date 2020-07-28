---
author: zc
avatar: null
categories:
- - 刷题记录
commnet: 1
date: 2020-01-04 20:29
html: '<details><summary>查看原题</summary><div id=''from''></div><p><button onclick="document.getElementById(''from'').innerHTML=''<iframe
  src=&quot;https://www.luogu.com.cn/problem/CF161D&quot; width=100% height=800px
  style=&quot;border: none;&quot;><iframe>''" class=''mdui-btn mdui-btn-raised mdui-ripple''>点击加载</button><a
  class=''mdui-btn mdui-btn-raised mdui-ripple'' href="https://www.luogu.com.cn/problem/CF161D"
  target=''_blank''>点击跳转</a><p></details>'
permalink: LG CF161D Distance-in-Tree
tags:
- 点分治
thumbnail: null
title: LG CF161D Distance-in-Tree
top: 0
---
点分治
```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 500011
#define inf 1000000000
#define ll long long
int n,k,cnt=0,SZ,rt,mxs,head[N],siz[N];
bool v[N];
struct edge{
    int to,nxt;
}e[N<<1];
void add(int x,int y){
    e[++cnt].to=y;e[cnt].nxt=head[x];head[x]=cnt;
}
#define fl(i,x) for(int i=head[x],to;to=e[i].to,i;i=e[i].nxt)
void frt(int x,int f){
    siz[x]=1;
    int res=0;
    fl(i,x)if(!v[to]&&to!=f){
        frt(to,x);
        siz[x]+=siz[to];
        res=max(res,siz[to]);
    }
    res=max(res,SZ-siz[x]);
    if(res<mxs)rt=x,mxs=res;
}
int b[N],tt;
ll ans=0;
void gd(int x,int d,int f){
    if(d>k)return;
    b[++tt]=d;
    fl(i,x)if(!v[to]&&to!=f)gd(to,d+1,x);
}
ll calc(int x,int d){
    tt=0;gd(x,d,0);
    sort(b+1,b+tt+1);
    int l=0,r=tt;
    ll res=0;
    while(l<r){
        ++l;
        while(b[l]+b[r]>k&&l<r)--r;
        if(b[l]+b[r]==k){
            int t1=1,t2=1;
            while(l<r&&b[l]==b[l+1])++l,++t1;
            while(l<r&&b[r]==b[r-1])--r,++t2;
            if(b[l]!=b[r])res+=1ll*t1*t2;
            else res+=1ll*(t1+t2)*(t1+t2-1)/2ll;
        }
    }
    return res;
}
void sol(int x){
    v[x]=1;ans+=calc(x,0);
    fl(i,x)if(!v[to]){
        ans-=calc(to,1);
        rt=0,mxs=inf;SZ=siz[to];
        frt(to,0);
        sol(rt);
    }
}
int main(){
    scanf("%d%d",&n,&k);
    int x,y;
    for(int i=1;i<=n-1;++i)
        scanf("%d%d",&x,&y),
        add(x,y),add(y,x);
    
    rt=0,mxs=inf,SZ=n;
    frt(1,0);
    sol(rt);
    printf("%lld\n",ans);
}
```
