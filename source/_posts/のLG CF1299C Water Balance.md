---
author: zc
avatar: null
categories:
- - 刷题记录
commnet: 1
date: 2020-05-03 21:39
html: '<details><summary>查看原题</summary><div id=''from''></div><p><button onclick="document.getElementById(''from'').innerHTML=''<iframe
  src=&quot;https://www.luogu.com.cn/problem/CF1299C&quot; width=100% height=800px
  style=&quot;border: none;&quot;><iframe>''" class=''mdui-btn mdui-btn-raised mdui-ripple''>点击加载</button><a
  class=''mdui-btn mdui-btn-raised mdui-ripple'' href="https://www.luogu.com.cn/problem/CF1299C"
  target=''_blank''>点击跳转</a><p></details>'
permalink: LG CF1299C Water Balance
tags:
- 后缀和
- 字典序
- 单调栈
thumbnail: null
title: LG CF1299C Water Balance
top: 0
---
可以发现如果要字典序最小,那么就需要让靠前的数字变小

那么最终形成的平均数是递增的

可以用单调栈维护平均数递增
```cpp
#include<bits/stdc++.h>
#define gc getchar()
#define fur(i,x,y) for(int i=x;i<=y;++i)
#define fdr(i,x,y) for(int i=x;i>=y;--i)
void in(int &x){x=0;char c;bool f=0;for(c=gc;c<'0'||'9'<c;c=gc)f^=c=='-';for(x=c-48,c=gc;'0'<=c&&c<='9';x=x*10+c-48,c=gc);if(f)x=-x;}
const int N=1000011;
int n,a[N],t[N],tp,tot;
long long s[N],sum;
int main(){
    in(n);
    fur(i,1,n)in(a[i]);
    s[tp=1]=a[n],t[1]=1;
    fdr(i,n-1,1){
        tot=1,sum=a[i];
        while(tp&&sum*t[tp]>=tot*s[tp])
            sum+=s[tp],tot+=t[tp],--tp;
        s[++tp]=sum,t[tp]=tot;
    }
    fdr(i,tp,1){
        double k=1.0*s[i]/(double)t[i];
        fur(j,1,t[i])printf("%.9f\n",k);
    }
}
```
