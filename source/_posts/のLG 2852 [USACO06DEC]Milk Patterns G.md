---
author: zc
avatar: null
categories:
- - "\u5237\u9898\u8BB0\u5F55"
commnet: 1
date: 2020-05-16 14:13
html: "<details><summary>\u67E5\u770B\u539F\u9898</summary><div id='from'></div><p><button\
  \ onclick=\"document.getElementById('from').innerHTML='<iframe src=&quot;https://www.luogu.com.cn/problem/P2852&quot;\
  \ width=100% height=800px style=&quot;border: none;&quot;><iframe>'\" class='mdui-btn\
  \ mdui-btn-raised mdui-ripple'>\u70B9\u51FB\u52A0\u8F7D</button><a class='mdui-btn\
  \ mdui-btn-raised mdui-ripple' href=\"https://www.luogu.com.cn/problem/P2852\" target='_blank'>\u70B9\
  \u51FB\u8DF3\u8F6C</a><p></details>"
permalink: LG 2852 [USACO06DEC]Milk Patterns G
tags:
- "\u540E\u7F00\u6570\u7EC4"
- "\u5355\u8C03\u961F\u5217"
thumbnail: null
title: LG 2852 [USACO06DEC]Milk Patterns G
top: 0
---
首先用后缀数组求出height数组

可以发现,重复出现的子串在sa数组中一定是连续的

那么在height中也是连续的

那么我们只需要求出 height数组中 连续$k-1$个数中 最小的数 最大可以是多少 即可

单调队列就可以解决
```cpp
#include<bits/stdc++.h>
#define gc getchar()
int rd(){int x=0;char c;bool f=0;for(c=gc;c<'0'||'9'<c;c=gc)f^=c=='-';for(x=c-48,c=gc;'0'<=c&&c<='9';x=x*10+c-48,c=gc);return f?-x:x;}
const int N=1000011;
int n,m,k,s[N],rnk[N],sa[N],tp[N],tax[N],height[N],q[N];
void qsort(){
    for(int i=0;i<=m;++i)tax[i]=0;
    for(int i=1;i<=n;++i)++tax[rnk[i]];
    for(int i=1;i<=m;++i)tax[i]+=tax[i-1];
    for(int i=n;i;--i)sa[tax[rnk[tp[i]]]--]=tp[i];
}
int main(){
    n=rd(),k=rd();
    for(int i=1;i<=n;++i)rnk[i]=s[i]=rd(),tp[i]=i;
    m=1000000;
    qsort();
    for(int w=1,p=0;p<n;m=p,w<<=1){
        p=0;
        for(int i=1;i<=w;++i)tp[++p]=n-w+i;
        for(int i=1;i<=n;++i)if(sa[i]>w)tp[++p]=sa[i]-w;
        qsort();
        std::swap(tp,rnk);
        rnk[sa[1]]=p=1;
        for(int i=2;i<=n;++i)
            rnk[sa[i]]=p+=tp[sa[i]]^tp[sa[i-1]]||tp[sa[i]+w]^tp[sa[i-1]+w];
    }
    for(int i=1,k=0;i<=n;++i){
        if(k)--k;
        int j=sa[rnk[i]-1];
        while(s[i+k]==s[j+k]&&i+k<=n&&j+k<=n)++k;
        height[rnk[i]]=k;
    }
    int h=1,t=0,ans=0;
    for(int i=2;i<=n;++i){
        while(h<=t&&height[q[t]]>=height[i])--t;
        q[++t]=i;
        if(i<k)continue;
        while(i-q[h]+1>=k)++h;
        if(ans<height[q[h]])ans=height[q[h]];
    }
    printf("%d\n",ans);
}
```
