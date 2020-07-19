---
author: zc
avatar: null
categories:
- - "\u5237\u9898\u8BB0\u5F55"
commnet: 1
date: 2019-12-21 19:47
html: "<details><summary>\u67E5\u770B\u539F\u9898</summary><div id='from'></div><p><button\
  \ onclick=\"document.getElementById('from').innerHTML='<iframe src=&quot;https://www.luogu.com.cn/problem/P3067&quot;\
  \ width=100% height=800px style=&quot;border: none;&quot;><iframe>'\" class='mdui-btn\
  \ mdui-btn-raised mdui-ripple'>\u70B9\u51FB\u52A0\u8F7D</button><a class='mdui-btn\
  \ mdui-btn-raised mdui-ripple' href=\"https://www.luogu.com.cn/problem/P3067\" target='_blank'>\u70B9\
  \u51FB\u8DF3\u8F6C</a><p></details>"
permalink: "LG 3067 [USACO12OPEN]\u5E73\u8861\u7684\u5976\u725B\u7FA4Balanced-Cow"
tags:
- "\u6298\u534A\u641C\u7D22"
thumbnail: null
title: "LG 3067 [USACO12OPEN]\u5E73\u8861\u7684\u5976\u725B\u7FA4Balanced-Cow"
top: 0
---
一个数有三种情况：

1. 放左边
2. 放右边
3. 不选

折半搜索

还是一样的套路

分前部分和后部分搜索

但是有可能出现前后选的数出现重叠状况

我们可以用状压并开一个桶来记录是否重复出现过

最后答案记得-1,因为空集不算

```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 1000011
int n,v[40],ans=0;
struct node{
    int s,sta;    
}a[1<<22],b[1<<22];
bool cmp(node x,node y){
    return x.s<y.s;
}
bool CMP(node x,node y){
    return x.s>y.s;
}
int dep=0,ta=0,tb=0;
inline void dfs(int d,int s,int now,bool f){
    if(d==dep+1){
        if(f)a[++ta]=node{s,now};
        else b[++tb]=node{s,now};
        return;
    }
    dfs(d+1,s,now,f);
    dfs(d+1,s+v[d],(now+(1<<(d-1))),f);
    dfs(d+1,s-v[d],(now+(1<<(d-1))),f);
}
bool vis[1<<22];
int main(){
    cin>>n;
    for(int i=1;i<=n;++i)cin>>v[i];
    dep=n/2;
    dfs(1,0,0,1);
    dep=n;
    dfs(n/2+1,0,0,0);
    sort(a+1,a+ta+1,cmp);
    sort(b+1,b+tb+1,CMP);
    int p=1,q=1;
    while(p<=ta&&q<=tb){
        while(-a[p].s<b[q].s&&q<=tb)++q;
        int pos=q;
        while(q<=tb&&-a[p].s==b[q].s){
            if(!vis[a[p].sta|b[q].sta])
                vis[a[p].sta|b[q].sta]=1,++ans;
            ++q;
        }
        if(p<ta&&a[p].s==a[p+1].s)q=pos;
        ++p;
    }
    cout<<ans-1<<endl; 
}
```
