---
author: zc
avatar: null
categories:
- - "\u5237\u9898\u8BB0\u5F55"
commnet: 1
date: 2020-03-01 00:37
html: "<details><summary>\u67E5\u770B\u539F\u9898</summary><div id='from'></div><p><button\
  \ onclick=\"document.getElementById('from').innerHTML='<iframe src=&quot;https://www.luogu.com.cn/problem/CF778C&quot;\
  \ width=100% height=800px style=&quot;border: none;&quot;><iframe>'\" class='mdui-btn\
  \ mdui-btn-raised mdui-ripple'>\u70B9\u51FB\u52A0\u8F7D</button><a class='mdui-btn\
  \ mdui-btn-raised mdui-ripple' href=\"https://www.luogu.com.cn/problem/CF778C\"\
  \ target='_blank'>\u70B9\u51FB\u8DF3\u8F6C</a><p></details>"
permalink: LG CF778C Peterson Polyglot
tags:
- trie
- "\u542F\u53D1\u5F0F\u5408\u5E76"
thumbnail: null
title: LG CF778C Peterson Polyglot
top: 0
---
题意: 

给一棵trie树,可以删掉某一层的所有边

求删掉哪一层边后合并出的trie树最小？

解法: 

trie的启发式合并

```cpp
int mg(int x,int y){
    if(!x||!y)return x+y;
    int now=++cnt;
    Fur(i,0,25)c[now][i]=mg(c[x][i],c[y][i]);
    return now;
}
```

这个合并的复杂度是$\Theta(\log n)$的

证明:

> 每次合并向下递归的时候规模$n$会变成原来的一半$\frac n2$
> 
> 所以最多需要合并$\log_2 n$次

代码: 
```cpp
#include<bits/stdc++.h>
#define il __inline__ __attribute__ ((always_inline))
#define Fur(i,x,y) for(int i(x);i<=y;++i)
namespace IO{const int str=1<<20;static char in_buf[str],*in_s,*in_t;bool __=0;il char gc(){return (in_s==in_t)&&(in_t=(in_s=in_buf)+fread(in_buf,1,str,stdin)),in_s==in_t?EOF:*in_s++;}template<typename T>il void in(T &x){if(__)return;char c=gc();bool f=0;while(c!=EOF&&(c<'0'||c>'9'))f^=(c=='-'),c=gc();if(c==EOF){__=1;return;}x=0;while(c!=EOF&&'0'<=c&&c<='9')x=x*10+c-48,c=gc();if(c==EOF)__=1;if(f)x=-x;}template<typename T,typename ... arr>il void in(T &x,arr & ... y){in(x),in(y...);}}using namespace IO;
const int N=600011;
int n,cnt,c[N][26],a[N];
int mg(int x,int y){
    if(!x||!y)return x+y;
    int now=++cnt;
    Fur(i,0,25)c[now][i]=mg(c[x][i],c[y][i]);
    return now;
}
void dfs(int x,int d){
    int now=n+1;cnt=n+1;
    Fur(i,0,25)if(c[x][i])
        now=mg(now,c[x][i]);
    a[d]+=cnt-n-1;
    Fur(i,0,25)if(c[x][i])
        dfs(c[x][i],d+1);
}
int main(){
    in(n);
    int x,y,ans=0,as=0;char w;
    Fur(i,2,n)in(x,y,w),c[x][w-'a']=y;
    dfs(1,1);
    Fur(i,1,n)if(a[i]>ans)as=i,ans=a[i];
    printf("%d\n%d\n",n-ans,as);
}
```
