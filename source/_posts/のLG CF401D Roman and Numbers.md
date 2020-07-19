---
author: zc
avatar: null
categories:
- - "\u5237\u9898\u8BB0\u5F55"
commnet: 1
date: 2019-12-21 19:47
html: "<details><summary>\u67E5\u770B\u539F\u9898</summary><div id='from'></div><p><button\
  \ onclick=\"document.getElementById('from').innerHTML='<iframe src=&quot;https://www.luogu.com.cn/problem/CF401D&quot;\
  \ width=100% height=800px style=&quot;border: none;&quot;><iframe>'\" class='mdui-btn\
  \ mdui-btn-raised mdui-ripple'>\u70B9\u51FB\u52A0\u8F7D</button><a class='mdui-btn\
  \ mdui-btn-raised mdui-ripple' href=\"https://www.luogu.com.cn/problem/CF401D\"\
  \ target='_blank'>\u70B9\u51FB\u8DF3\u8F6C</a><p></details>"
permalink: LG CF401D Roman and Numbers
tags:
- "\u72B6\u538Bdp"
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
