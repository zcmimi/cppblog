---
author: zc
avatar: null
categories:
- - "\u5237\u9898\u8BB0\u5F55"
commnet: 1
date: 2020-04-26 14:01
html: "<details><summary>\u67E5\u770B\u539F\u9898</summary><div id='from'></div><p><button\
  \ onclick=\"document.getElementById('from').innerHTML='<iframe src=&quot;https://www.luogu.com.cn/problem/CF1324D&quot;\
  \ width=100% height=800px style=&quot;border: none;&quot;><iframe>'\" class='mdui-btn\
  \ mdui-btn-raised mdui-ripple'>\u70B9\u51FB\u52A0\u8F7D</button><a class='mdui-btn\
  \ mdui-btn-raised mdui-ripple' href=\"https://www.luogu.com.cn/problem/CF1324D\"\
  \ target='_blank'>\u70B9\u51FB\u8DF3\u8F6C</a><p></details>"
permalink: LG CF1324D Pair of Topics
tags:
- "\u6392\u5E8F"
- "\u53CC\u6307\u9488"
thumbnail: null
title: LG CF1324D Pair of Topics
top: 0
---
建立新数$c$,使$c_i=a_i-b_i$

那么就是要找多少对$i<j$且$c_i>c_j$

将$c$排序,然后双指针统计一下就可以了
```cpp
#include<bits/stdc++.h>
int n,a[200001];
int main(){
    scanf("%d",&n);
    int x;long long ans=0;
    for(int i=1;i<=n;++i)scanf("%d",a+i);
    for(int i=1;i<=n;++i)scanf("%d",&x),a[i]-=x;
    std::sort(a+1,a+n+1,std::greater<int>());
    x=n;
    for(int i=1;i<=n;++i){
        while(a[x]+a[i]<=0&&x>i)--x;
        if(a[x]+a[i]>0)ans+=x-i;
        else break;
    }
    printf("%lld\n",ans);
}
```
