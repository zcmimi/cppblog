---
author: zc
avatar: null
categories:
- - 刷题记录
commnet: 1
date: 2019-12-21 19:47
html: '<details><summary>查看原题</summary><div id=''from''></div><p><button onclick="document.getElementById(''from'').innerHTML=''<iframe
  src=&quot;https://www.luogu.com.cn/problem/CF401D&quot; width=100% height=800px
  style=&quot;border: none;&quot;><iframe>''" class=''mdui-btn mdui-btn-raised mdui-ripple''>点击加载</button><a
  class=''mdui-btn mdui-btn-raised mdui-ripple'' href="https://www.luogu.com.cn/problem/CF401D"
  target=''_blank''>点击跳转</a><p></details>'
permalink: LG CF401D Roman and Numbers
tags:
- 状压dp
thumbnail: null
title: LG CF401D Roman and Numbers
top: 0
---
```cpp
#include<iostream>
#include<cstring>
#define int long long
using namespace std;
const int maxs=(1<<18)+10,maxm=110;
int w[20],cnt=-1,m,n,f[maxs][maxm];
bool vis[10];
signed main()
{
    for(cin>>n>>m;n;n/=10)
        w[++cnt]=n%10;
    f[0][0]=1;
    for(int s=1;s<1<<cnt+1;s++)
    {
        memset(vis,0,sizeof(vis));
        for(int i=0;i<=cnt;i++)
        {
            if(s==(1<<i)&&!w[i])
                break;
            if(!(s&(1<<i))||vis[w[i]])
                continue;
            vis[w[i]]=1;
            for(int j=0;j<m;j++)
                f[s][(j*10+w[i])%m]=f[s][(j*10+w[i])%m]+f[s^(1<<i)][j];
        }
    }
    cout<<f[(1<<cnt+1)-1][0]<<endl;
    return 0;
}
```
