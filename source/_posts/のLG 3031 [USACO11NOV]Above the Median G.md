---
author: zc
avatar: null
categories:
- - "\u5237\u9898\u8BB0\u5F55"
commnet: 1
date: 2020-03-23 16:44
html: "<details><summary>\u67E5\u770B\u539F\u9898</summary><div id='from'></div><p><button\
  \ onclick=\"document.getElementById('from').innerHTML='<iframe src=&quot;https://www.luogu.com.cn/problem/P3031&quot;\
  \ width=100% height=800px style=&quot;border: none;&quot;><iframe>'\" class='mdui-btn\
  \ mdui-btn-raised mdui-ripple'>\u70B9\u51FB\u52A0\u8F7D</button><a class='mdui-btn\
  \ mdui-btn-raised mdui-ripple' href=\"https://www.luogu.com.cn/problem/P3031\" target='_blank'>\u70B9\
  \u51FB\u8DF3\u8F6C</a><p></details>"
permalink: LG 3031 [USACO11NOV]Above the Median G
tags:
- "\u524D\u7F00\u548C"
- "\u601D\u7EF4"
thumbnail: null
title: LG 3031 [USACO11NOV]Above the Median G
top: 0
---
很妙的一道题

对每位置$i$分别统计$[l,i],l\in [1,i]$的方案数

设$S_i$表示$\sum_{j=1}^i [H_i \ge X]$,$pre$为位置$i-1$的方案数,$now$为位置$i$的方案数

若$H_i\ge x$,$now=pre+\sum_{j=1}^i [S_j=S_i]$,这些位置是位置$i-1$不能满足而位置$i$可以满足的

若$H_i\le x$,$now=pre-\sum_{j=1}^i [S_j=S_{i-1}]$,这些位置是位置$i$不能满足而位置$i-1$可以满足的

这样就可以$\Theta(n)$解决了呢

记得开`long long`,$S_0$先赋值为$n$,防止负数re
```cpp
#include<bits/stdc++.h>
namespace IN{const int str=1<<20;static char in_buf[str],*in_s,*in_t;bool __=0;inline char gc(){return (in_s==in_t)&&(in_t=(in_s=in_buf)+fread(in_buf,1,str,stdin)),in_s==in_t?EOF:*in_s++;}template<typename T>inline void in(T &x){if(__)return;char c=gc();bool f=0;while(c!=EOF&&(c<'0'||c>'9'))f^=(c=='-'),c=gc();if(c==EOF){__=1;return;}x=0;while(c!=EOF&&'0'<=c&&c<='9')x=x*10+c-48,c=gc();if(c==EOF)__=1;if(f)x=-x;}template<typename T,typename ... arr>inline void in(T &x,arr & ... y){in(x),in(y...);}}using namespace IN;
const int N=100011;
int n,k,b[N<<1];
int main(){
    in(n,k);
    int x,pre=0,s=n;
    long long ans=0;
    b[s]=1;
    for(int i=1;i<=n;++i){
        in(x);
        if(x>=k)pre+=b[++s]+1;
        else pre-=b[s--]-1;
        ++b[s];
        ans+=pre;
    }
    printf("%lld\n",ans);
}
```
