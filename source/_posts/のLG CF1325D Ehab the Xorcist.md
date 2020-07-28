---
author: zc
avatar: null
categories:
- - 刷题记录
commnet: 1
date: 2020-04-27 12:37
html: '<details><summary>查看原题</summary><div id=''from''></div><p><button onclick="document.getElementById(''from'').innerHTML=''<iframe
  src=&quot;https://www.luogu.com.cn/problem/CF1325D&quot; width=100% height=800px
  style=&quot;border: none;&quot;><iframe>''" class=''mdui-btn mdui-btn-raised mdui-ripple''>点击加载</button><a
  class=''mdui-btn mdui-btn-raised mdui-ripple'' href="https://www.luogu.com.cn/problem/CF1325D"
  target=''_blank''>点击跳转</a><p></details>'
permalink: LG CF1325D Ehab the Xorcist
tags:
- 异或
- 位运算
- 构造
thumbnail: null
title: LG CF1325D Ehab the Xorcist
top: 0
---
很妙的构造题

首先,可以发现异或和明显不大于总和

第二,如果异或和与总和的奇偶不同,那么无解(二进制下最低位不同,没法用进位来填充)

剩下的就都可以构造了

当$u=v$的时候,输出$u$就可以了,当$u=0$的时候记得特判

设$x=\frac{u+v}2$

那么$\left\{x,x,u\right\}$就一定可以满足

如果$x \And u=0$的时候$\left\{x,u\right\}$等价于$\left\{x+u\right\}$

那么$\left\{x,x+u\right\}$可以满足
```cpp
#include<bits/stdc++.h>
int main(){
    long long a,b,x;scanf("%lld%lld",&a,&b);
    if(a>b||(a&1)!=(b&1))return printf("-1\n"),0;
    if(a==b){
        if(!a)printf("0\n");
        else printf("1\n%lld\n",a);
    }
    else{
        x=b-a>>1;
        if(x&a)printf("3\n%lld %lld %lld\n",x,x,a);
        else printf("2\n%lld %lld\n",x,a|x);
    }
}
```
