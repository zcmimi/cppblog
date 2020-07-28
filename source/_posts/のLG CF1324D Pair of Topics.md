---
author: zc
avatar: null
categories:
- - 刷题记录
commnet: 1
date: 2020-04-26 14:01
html: '<details><summary>查看原题</summary><div id=''from''></div><p><button onclick="document.getElementById(''from'').innerHTML=''<iframe
  src=&quot;https://www.luogu.com.cn/problem/CF1324D&quot; width=100% height=800px
  style=&quot;border: none;&quot;><iframe>''" class=''mdui-btn mdui-btn-raised mdui-ripple''>点击加载</button><a
  class=''mdui-btn mdui-btn-raised mdui-ripple'' href="https://www.luogu.com.cn/problem/CF1324D"
  target=''_blank''>点击跳转</a><p></details>'
permalink: LG CF1324D Pair of Topics
tags:
- 排序
- 双指针
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
