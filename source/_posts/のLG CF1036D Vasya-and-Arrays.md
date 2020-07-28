---
author: zc
avatar: null
categories:
- - 刷题记录
commnet: 1
date: 2020-01-20 22:35
html: '<details><summary>查看原题</summary><div id=''from''></div><p><button onclick="document.getElementById(''from'').innerHTML=''<iframe
  src=&quot;https://www.luogu.com.cn/problem/CF1036D&quot; width=100% height=800px
  style=&quot;border: none;&quot;><iframe>''" class=''mdui-btn mdui-btn-raised mdui-ripple''>点击加载</button><a
  class=''mdui-btn mdui-btn-raised mdui-ripple'' href="https://www.luogu.com.cn/problem/CF1036D"
  target=''_blank''>点击跳转</a><p></details>'
permalink: LG CF1036D Vasya-and-Arrays
tags:
- 双指针
- 贪心
thumbnail: null
title: LG CF1036D Vasya-and-Arrays
top: 0
---
若$A,B$总和不相同,显然是-1

由于元素都大于0,可以使用类似双指针的方法

两个指针在$A,B$数组中移动,若找到$A,B$中和相同的两端,答案就+1


```cpp
#include<cstdio>
#pragma GCC optimize(3)
#define ll long long
#define Fur(i,x,y) for(int i(x);i<=y;++i)
const int N=300011;
inline char gc(){static const int IN_LEN=N*10;static char buf[IN_LEN],*s,*t;return (s==t)&&(t=(s=buf)+fread(buf,1,IN_LEN,stdin)),s==t?-1:*s++;}
inline void in(int &x){x=0;char c;bool f=0;while((c=gc())<'0'||'9'<c)f^=(c=='-');while('0'<=c&&c<='9')x=x*10+c-48,c=gc();if(f)x=-x;}
int n,m,a[N],b[N];
int main(){
    in(n);
    Fur(i,1,n)in(a[i]);
    in(m);
    Fur(i,1,m)in(b[i]);
    int ans=0,j=1;
    ll s=0;
    Fur(i,1,n){
        s+=a[i];
        while(s>=b[j]&&j<=m)s-=b[j++];
        if(!s)++ans;
    }
    if(s!=0||j!=m+1)printf("-1\n");
    else printf("%d\n",ans);
}
```
