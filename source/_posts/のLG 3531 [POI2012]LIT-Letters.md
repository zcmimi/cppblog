---
author: zc
avatar: null
categories:
- - 刷题记录
commnet: 1
date: 2020-01-18 22:40
html: '<details><summary>查看原题</summary><div id=''from''></div><p><button onclick="document.getElementById(''from'').innerHTML=''<iframe
  src=&quot;https://www.luogu.com.cn/problem/P3531&quot; width=100% height=800px style=&quot;border:
  none;&quot;><iframe>''" class=''mdui-btn mdui-btn-raised mdui-ripple''>点击加载</button><a
  class=''mdui-btn mdui-btn-raised mdui-ripple'' href="https://www.luogu.com.cn/problem/P3531"
  target=''_blank''>点击跳转</a><p></details>'
permalink: LG 3531 [POI2012]LIT-Letters
tags:
- 树状数组
- 逆序对
thumbnail: null
title: LG 3531 [POI2012]LIT-Letters
top: 0
---
看到交换相邻字母,就想到逆序对

考虑一下,一定是将A的每个字母移动到离它最近的B中相同字母的位置

我们可以用讲位置存起来然后处理一下

之后数组变成了A中每个位置最后在B中的位置

这个数组中逆序对的数目就是答案


```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 1000011
int n,cnt[30],s[N];
char a[N],b[N];
vector<int>p[30];
void add(int x){
    for(int i=x;i<=n;i+=i&-i)
        ++s[i];
}
int get(int x){
    int ans=0;
    for(int i=x;i;i-=i&-i)
        ans+=s[i];
    return ans;
}
struct node{
    int v,p;
    bool operator<(node x)const{
        return v>x.v;
    }
}c[N];
int main(){
    scanf("%d%s%s",&n,a+1,b+1);
    for(int i=1;i<=n;++i)p[b[i]-'A'].push_back(i);
    for(int i=1;i<=n;++i)c[i]={p[a[i]-'A'][cnt[a[i]-'A']++],i};
    sort(c+1,c+n+1);
    long long ans=0;
    for(int i=1;i<=n;++i){
        ans+=get(c[i].p-1);
        add(c[i].p);
    }
    printf("%lld\n",ans);
}
```
