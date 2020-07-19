---
author: zc
avatar: null
categories:
- - "\u5237\u9898\u8BB0\u5F55"
commnet: 1
date: 2020-03-17 17:16
html: "<details><summary>\u67E5\u770B\u539F\u9898</summary><div id='from'></div><p><button\
  \ onclick=\"document.getElementById('from').innerHTML='<iframe src=&quot;https://www.luogu.com.cn/problem/P4213&quot;\
  \ width=100% height=800px style=&quot;border: none;&quot;><iframe>'\" class='mdui-btn\
  \ mdui-btn-raised mdui-ripple'>\u70B9\u51FB\u52A0\u8F7D</button><a class='mdui-btn\
  \ mdui-btn-raised mdui-ripple' href=\"https://www.luogu.com.cn/problem/P4213\" target='_blank'>\u70B9\
  \u51FB\u8DF3\u8F6C</a><p></details>"
permalink: "LG 4213 \u3010\u6A21\u677F\u3011\u675C\u6559\u7B5B\uFF08Sum\uFF09"
tags:
- "\u675C\u6559\u7B5B"
- "\u83AB\u6BD4\u4E4C\u65AF"
- "\u6B27\u62C9\u51FD\u6570"
- "\u6570\u8BBA"
thumbnail: null
title: "LG 4213 \u3010\u6A21\u677F\u3011\u675C\u6559\u7B5B\uFF08Sum\uFF09"
top: 0
---
```cpp
#include<bits/stdc++.h>
typedef long long ll;
#pragma GCC optimize(3)
#define il __inline__ __attribute__ ((always_inline))
const int N=5000000;
int mu[N+11],pri[N+1];
ll phi[N+11];
bool b[N+11];
il void init(){
    mu[1]=phi[1]=1;
    int cnt=0;
    for(int i=2;i<=N;++i){
        if(!b[i])pri[++cnt]=i,mu[i]=-1,phi[i]=i-1;
        for(int j=1;j<=cnt&&i*pri[j]<=N;++j){
            b[i*pri[j]]=1;
            if(i%pri[j])mu[i*pri[j]]=-mu[i],phi[i*pri[j]]=phi[i]*(pri[j]-1);
            else{phi[i*pri[j]]=phi[i]*pri[j];break;}
        }
    }
    for(int i=2;i<=N;++i)mu[i]+=mu[i-1],phi[i]+=phi[i-1];
}
const int P=1000007;
struct hash{
    int cnt=0,head[P];
    struct edge{int to,nxt;ll w;}e[P];
    il void add(int x,int y,ll w){e[++cnt].to=y;e[cnt].nxt=head[x];head[x]=cnt;e[cnt].w=w;}
    il void ins(int x,ll v){add(x%P,x,v);}
    il ll ask(int x){for(int i=head[x%P];i;i=e[i].nxt)if(e[i].to==x)return e[i].w;return 1ll<<63;}
}SP,SM;
ll PHI(int n){
    if(n<=N)return phi[n];
    ll t=SP.ask(n);if(t!=(1ll<<63))return t;
    ll res=1ll*n*(n+1)/2;
    for(ll l=2,r;l<=n;l=r+1){
        r=n/(n/l);
        res-=PHI(n/l)*(r-l+1);
    }
    SP.ins(n,res);
    return res;
}
ll MU(int n){
    if(n<=N)return mu[n];
    ll t=SM.ask(n);if(t!=(1ll<<63))return t;
    ll res=1;
    for(ll l=2,r;l<=n;l=r+1){
        r=n/(n/l);
        res-=MU(n/l)*(r-l+1);
    }
    SM.ins(n,res);
    return res;
}
int main(){
    init();
    int T,n;scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        printf("%lld %lld\n",PHI(n),MU(n));
    }
}
```
