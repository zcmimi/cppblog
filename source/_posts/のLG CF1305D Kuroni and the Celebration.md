---
author: zc
avatar: null
categories:
- - "\u5237\u9898\u8BB0\u5F55"
commnet: 1
date: 2020-05-03 11:51
html: "<details><summary>\u67E5\u770B\u539F\u9898</summary><div id='from'></div><p><button\
  \ onclick=\"document.getElementById('from').innerHTML='<iframe src=&quot;https://www.luogu.com.cn/problem/CF1305D&quot;\
  \ width=100% height=800px style=&quot;border: none;&quot;><iframe>'\" class='mdui-btn\
  \ mdui-btn-raised mdui-ripple'>\u70B9\u51FB\u52A0\u8F7D</button><a class='mdui-btn\
  \ mdui-btn-raised mdui-ripple' href=\"https://www.luogu.com.cn/problem/CF1305D\"\
  \ target='_blank'>\u70B9\u51FB\u8DF3\u8F6C</a><p></details>"
permalink: LG CF1305D Kuroni and the Celebration
tags:
- "\u4EA4\u4E92"
- lca
- "\u6811"
thumbnail: null
title: LG CF1305D Kuroni and the Celebration
top: 0
---
交互题

我们从叶子节点开始搜索,把所有叶子节点添加到队列中

每次从队列中弹出两个叶子节点,

如果`lca`为其中一个,那么这个`lca`就是树根

否则删除这两个节点,可能会形成新的叶子节点,加入队列

因为最坏情况下每次都会删掉两个节点,那么重复$\frac n2$次后,也就只剩下根节点了
```cpp
#include<bits/stdc++.h>
#define gc getchar()
#define fur(i,x,y) for(int i=x;i<=y;++i)
void cmin(int &x,int y){if(x>y)x=y;}void cmax(int &x,int y){if(x<y)x=y;}
void in(int &x){x=0;char c;bool f=0;for(c=gc;c<'0'||'9'<c;c=gc)f^=c=='-';for(x=c-48,c=gc;'0'<=c&&c<='9';x=x*10+c-48,c=gc);if(f)x=-x;}
const int N=100011,inf=2122219134;
using std::list;
int n,d[N],q[N],h,t;
list<int>e[N];
bool v[N];
int main(){
    in(n);
    int x,y,z;
    fur(i,2,n)
        in(x),in(y),
        e[x].push_back(y),
        e[y].push_back(x),
        ++d[x],++d[y];
    fur(i,1,n)if(d[i]==1)q[t++]=i;
    fur(i,1,n>>1){
        x=q[h++],y=q[h++];
        printf("? %d %d\n",x,y),fflush(stdout);
        in(z);
        if(z==x||z==y)return printf("! %d\n",z),0;
        for(int z:e[x])
            if(!v[z]&&--d[z]==1)q[t++]=z;
        for(int z:e[y])
            if(!v[z]&&--d[z]==1)q[t++]=z;
        v[x]=v[y]=1;
    }
    fur(i,1,n)if(!v[i])printf("! %d\n",i);
}
```
