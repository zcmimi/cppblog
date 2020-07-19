---
author: zc
avatar: null
categories:
- - "\u5237\u9898\u8BB0\u5F55"
commnet: 1
date: 2020-01-23 12:40
html: "<details><summary>\u67E5\u770B\u539F\u9898</summary><div id='from'></div><p><button\
  \ onclick=\"document.getElementById('from').innerHTML='<iframe src=&quot;https://www.luogu.com.cn/problem/P2889&quot;\
  \ width=100% height=800px style=&quot;border: none;&quot;><iframe>'\" class='mdui-btn\
  \ mdui-btn-raised mdui-ripple'>\u70B9\u51FB\u52A0\u8F7D</button><a class='mdui-btn\
  \ mdui-btn-raised mdui-ripple' href=\"https://www.luogu.com.cn/problem/P2889\" target='_blank'>\u70B9\
  \u51FB\u8DF3\u8F6C</a><p></details>"
permalink: "LG 2889 [USACO07NOV]\u6324\u5976\u7684\u65F6\u95F4Milking-Time"
tags:
- "\u52A8\u6001\u89C4\u5212"
thumbnail: null
title: "LG 2889 [USACO07NOV]\u6324\u5976\u7684\u65F6\u95F4Milking-Time"
top: 0
---
$f[i]=\max{f[t-r]+p}$
```cpp
#include<bits/stdc++.h>
const int N=1000011;
struct node{int st,ed,p,next;}a[N];
int f[N],head[N];
inline int max(int x,int y){return x>y?x:y;}
int main(){
    int n,m,r;
    scanf("%d%d%d",&n,&m,&r);
    for(int i=1;i<=m;++i){
        scanf("%d%d%d",&a[i].st,&a[i].ed,&a[i].p);
        a[i].next=head[a[i].ed];
        head[a[i].ed]=i;
    }
    for(int j=1;j<=n;++j){
        f[j]=f[j-1];
        for(int i=head[j];i;i=a[i].next)
            f[j]=max(f[j],f[max(0,a[i].st-r)]+a[i].p);
    }
    printf("%d\n",f[n]);
}
```
