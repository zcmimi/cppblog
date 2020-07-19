---
author: zc
avatar: null
categories:
- - "\u5237\u9898\u8BB0\u5F55"
commnet: 1
date: 2020-01-22 17:05
html: "<details><summary>\u67E5\u770B\u539F\u9898</summary><div id='from'></div><p><button\
  \ onclick=\"document.getElementById('from').innerHTML='<iframe src=&quot;http://acm.hdu.edu.cn/showproblem.php?pid=1028&quot;\
  \ width=100% height=800px style=&quot;border: none;&quot;><iframe>'\" class='mdui-btn\
  \ mdui-btn-raised mdui-ripple'>\u70B9\u51FB\u52A0\u8F7D</button><a class='mdui-btn\
  \ mdui-btn-raised mdui-ripple' href=\"http://acm.hdu.edu.cn/showproblem.php?pid=1028\"\
  \ target='_blank'>\u70B9\u51FB\u8DF3\u8F6C</a><p></details>"
permalink: HDU 1028 Ignatius-and-the-Princess-III
tags:
- "\u751F\u6210\u51FD\u6570"
- "\u6570\u8BBA"
thumbnail: null
title: HDU 1028 Ignatius-and-the-Princess-III
top: 0
---
$g(x)=(1+x+x^2+x^3+...)(1+x^2+x^4+x^6+...)(1+x^3+x^6+x^9+...)...$

模拟一下

$\Theta(n^2)$
```cpp
#include<bits/stdc++.h>
#define Fur(i,x,y) for(int i=x;i<=y;++i)
const int N=121;
int n,a[2][N];
int main(){
    Fur(i,0,120)a[1][i]=1;
    Fur(i,2,120){
        memset(a[i&1],0,sizeof a[i&1]);
        int p=0;
        while(p<=120){
            Fur(j,0,120-p)a[i&1][p+j]+=a[!(i&1)][j];
            p+=i;
        }
    }
    while(~scanf("%d",&n))printf("%d\n",a[0][n]);
}
```
