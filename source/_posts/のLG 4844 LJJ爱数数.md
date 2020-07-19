---
author: zc
avatar: null
categories:
- - "\u5237\u9898\u8BB0\u5F55"
commnet: 1
date: 2020-03-19 23:44
html: "<details><summary>\u67E5\u770B\u539F\u9898</summary><div id='from'></div><p><button\
  \ onclick=\"document.getElementById('from').innerHTML='<iframe src=&quot;https://www.luogu.com.cn/problem/P4844&quot;\
  \ width=100% height=800px style=&quot;border: none;&quot;><iframe>'\" class='mdui-btn\
  \ mdui-btn-raised mdui-ripple'>\u70B9\u51FB\u52A0\u8F7D</button><a class='mdui-btn\
  \ mdui-btn-raised mdui-ripple' href=\"https://www.luogu.com.cn/problem/P4844\" target='_blank'>\u70B9\
  \u51FB\u8DF3\u8F6C</a><p></details>"
permalink: "LG 4844 LJJ\u7231\u6570\u6570"
tags:
- "\u6570\u8BBA"
- "\u83AB\u6BD4\u4E4C\u65AF"
thumbnail: null
title: "LG 4844 LJJ\u7231\u6570\u6570"
top: 0
---
经过一番化简后变成了:

$$
\sum_{i=1}^{\sqrt{2n}} \sum_{x=L}^{R} [\gcd(i,x)=1]  
\\
L=Max(1,i-\lfloor {n\over i}\rfloor)
\\
R=Min(i-1,\lfloor {n\over i }\rfloor)
$$

莫比乌斯反演

$$
\sum_{i=1}^{\sqrt{2n}} \sum_{j=l}^{R} [\gcd(i,j)=1]
\\
=\sum_{i=1}^{\sqrt{2n}} \sum_{j=l}^{R} \sum_{k|i,k|j} \mu(k)
\\
=\sum_{i=1}^{\sqrt{2n}}\sum_{k|j,k\in[L,R]} \mu(k)
$$

```cpp
#include<bits/stdc++.h>
typedef long long ll;
const int N=1500011;
inline int min(int x,int y){return x<y?x:y;}
inline int max(int x,int y){return x>y?x:y;}
inline int abs(int x){return x>0?x:-x;}
ll n;
int m,mu[N],pri[N],cnt=0,head[N];
bool b[N];
struct edge{int to,nxt;}e[N<<4];
inline void add(int x,int y){e[++cnt].to=y;e[cnt].nxt=head[x];head[x]=cnt;}
inline ll calc(int x,int k){
    ll res=0;
    for(int i=head[x];i&&abs(e[i].to)<=k;i=e[i].nxt)
        res+=k/e[i].to;
    return res;
}
int main(){
    scanf("%lld",&n);
    m=sqrt((n<<1));
    mu[1]=1;
    for(int i=2;i<=m;++i){
        if(!b[i])pri[++cnt]=i,mu[i]=-1;
        for(int j=1;j<=cnt&&i*pri[j]<=m;++j){
            b[i*pri[j]]=1;
            if(i%pri[j])mu[i*pri[j]]=-mu[i];
            else break;
        }
    }
    cnt=0;
    for(int i=1;i<=m;++i)
        for(int j=1;i*j<=m;++j)
        if(mu[j])add(i*j,mu[j]*j);
    ll ans=0;
    for(int i=1;i<=m;++i)
        ans+=calc(i,min(i-1,n/i))-calc(i,max(1,i-(n/i))-1);
    printf("%lld\n",ans);
}
```
