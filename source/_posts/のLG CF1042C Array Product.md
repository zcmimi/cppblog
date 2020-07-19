---
author: zc
avatar: null
categories:
- - "\u5237\u9898\u8BB0\u5F55"
commnet: 1
date: 2019-12-21 19:47
html: "<details><summary>\u67E5\u770B\u539F\u9898</summary><div id='from'></div><p><button\
  \ onclick=\"document.getElementById('from').innerHTML='<iframe src=&quot;https://www.luogu.com.cn/problem/CF1042C&quot;\
  \ width=100% height=800px style=&quot;border: none;&quot;><iframe>'\" class='mdui-btn\
  \ mdui-btn-raised mdui-ripple'>\u70B9\u51FB\u52A0\u8F7D</button><a class='mdui-btn\
  \ mdui-btn-raised mdui-ripple' href=\"https://www.luogu.com.cn/problem/CF1042C\"\
  \ target='_blank'>\u70B9\u51FB\u8DF3\u8F6C</a><p></details>"
permalink: LG CF1042C Array Product
tags:
- "\u8D2A\u5FC3"
- "\u6392\u5E8F"
thumbnail: null
title: LG CF1042C Array Product
top: 0
---
先把所有0合成1个,所有正数合成一个,把负数(除了最大的那个负数之外的(如果负数个数为奇数)))合成一个

1.如果全是0

2.没有0

3.没有负数

4.没有正数
```cpp
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
using namespace std;
int cnt,cnt1,cnt2,n,x;
struct ahah
{
    int x,pos;
} a[200006],b[200006],c[200006];
bool cmp(ahah a,ahah b){ return abs(a.x)<abs(b.x); }
int main()
{
    scanf("%d",&n);
    for(int i=1; i<=n; i++)
    {
        scanf("%d",&x);
        if(x==0)c[++cnt].pos=i;
        if(x<0)a[++cnt1].x=x,a[cnt1].pos=i;
        if(x>0)b[++cnt2].x=x,b[cnt2].pos=i;
    }
    sort(a+1,a+1+cnt1,cmp);
    sort(b+1,b+1+cnt2,cmp);
    int v=-1;
    if(cnt!=0)
    {
        v=c[1].pos;
        for(int i=2; i<=cnt; i++)
        {
            printf("1 %d %d\n",v,c[i].pos);
            v=c[i].pos;
        }
    }
    if(cnt==n)return 0;
    if(cnt1%2==0)
    {
        if(v!=-1)printf("2 %d\n",v),v=-1;
        if(cnt1!=0)
        {
            if(v==-1)v=a[1].pos;
            else printf("1 %d %d\n",v,a[1].pos),v=a[1].pos;
            for(int i=2; i<=cnt1; i++)
            {
                printf("1 %d %d\n",v,a[i].pos);
                v=a[i].pos;
            }
        }
        if(cnt2!=0)
        {
            if(v==-1)v=b[1].pos;
            else printf("1 %d %d\n",v,b[1].pos),v=b[1].pos;
            for(int i=2; i<=cnt2; i++)
            {
                printf("1 %d %d\n",v,b[i].pos);
                v=b[i].pos;
            }
        }
    }
    else
    {
        if(v==-1)v=a[1].pos;
        else printf("1 %d %d\n",v,a[1].pos),v=a[1].pos;
        if(cnt+1!=n)printf("2 %d\n",v),v=-1;
        else return 0;
        if(cnt1>1)
        {
            v=a[2].pos;
            for(int i=3; i<=cnt1; i++)
            {
                printf("1 %d %d\n",v,a[i].pos);
                v=a[i].pos;
            }
        }
        if(cnt2>0)
        {
            if(v==-1)v=b[1].pos;
            else printf("1 %d %d\n",v,b[1].pos),v=b[1].pos;
            for(int i=2; i<=cnt2; i++)
            {
                printf("1 %d %d\n",v,b[i].pos);
                v=b[i].pos;
            }
        }
    }
}
```
