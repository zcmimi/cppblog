---
author: zc
avatar: null
categories:
- - "\u5237\u9898\u8BB0\u5F55"
commnet: 1
date: 2020-04-26 21:16
html: "<details><summary>\u67E5\u770B\u539F\u9898</summary><div id='from'></div><p><button\
  \ onclick=\"document.getElementById('from').innerHTML='<iframe src=&quot;https://www.luogu.com.cn/problem/CF1325E&quot;\
  \ width=100% height=800px style=&quot;border: none;&quot;><iframe>'\" class='mdui-btn\
  \ mdui-btn-raised mdui-ripple'>\u70B9\u51FB\u52A0\u8F7D</button><a class='mdui-btn\
  \ mdui-btn-raised mdui-ripple' href=\"https://www.luogu.com.cn/problem/CF1325E\"\
  \ target='_blank'>\u70B9\u51FB\u8DF3\u8F6C</a><p></details>"
permalink: LG CF1325E Ehab's REAL Number Theory Problem
tags:
- "\u6570\u8BBA"
- "\u56FE\u8BBA"
- "\u6700\u5C0F\u73AF"
thumbnail: null
title: LG CF1325E Ehab's REAL Number Theory Problem
top: 0
---
首先我们可以只保留每个数奇数次幂的因子

第二,根据约数个数定理,因为每个数的约数不超过7,所以最多只有两个质因子

可以把选择一个数看成在这两个质因子之间的连边

如果只有一个,那么把$1$作为另一个质因子

于是我们得到一张图

乘积为完全平方,也就是每个质因子都是偶数次幂,那么再最终的图中它的入度为偶数

那就是说我们要找这个无向图中的最小环




```cpp
#include<bits/stdc++.h>
#define gc getchar()
#define fur(i,x,y) for(int i=x;i<=y;++i)
void cmin(int &x,int y){if(x>y)x=y;}
void in(int &x){x=0;char c;bool f=0;for(c=gc;c<'0'||'9'<c;c=gc)f^=c=='-';for(x=c-48,c=gc;'0'<=c&&c<='9';x=x*10+c-48,c=gc);if(f)x=-x;}
const int N=1000011,inf=2122219134;
bool f[N];
int cnt,pri[N],id[N],head[N],tt=1,S;
void ol(int n){
    pri[cnt=1]=id[1]=S=1;
    fur(i,2,n){
        if(!f[i])pri[++cnt]=i,id[i]=cnt,S+=(i<=999);
        for(int j=2;j<=cnt&&i*pri[j]<=n;++j){
            f[i*pri[j]]=1;
            // if(i%pri[j]==0)break;
        }
    }
}
struct edge{int to,nxt;}e[N];
void add(int x,int y){
    e[++tt].to=y,e[tt].nxt=head[x],head[x]=tt;
    e[++tt].to=x,e[tt].nxt=head[y],head[y]=tt;
}
int q[N],p[N],d[N];
int bfs(int x){
    fur(i,1,78500)d[i]=inf;
    int h=0,t=1,pre,sz=inf;
    q[0]=x;d[x]=0;
    while(h<t){
        x=q[h],pre=p[h++];
        for(int i=head[x],to;to=e[i].to,i&&i!=pre;i=e[i].nxt)
        if(d[to]==inf){
            d[to]=d[x]+1;
            q[t]=to,p[t++]=i^1;
        }
        else cmin(sz,d[x]+d[to]+1);
    }
    return sz;
}
int main(){
    int n;in(n);
    ol(1000000);
    int x,a[2];
    fur(i,1,n){
        in(x);
        int tot=0;
        for(int j=2,t;j<=cnt&&(t=pri[j]*pri[j])<=x;++j)
        if(x%pri[j]==0){
            while(x%t==0)x/=t;
            if(x%pri[j]==0)a[tot++]=j,x/=pri[j];
        }
        if(x>1)a[tot++]=id[x],x=1;
        if(!tot)return printf("1\n"),0;
        else if(tot==1)add(1,a[0]);
        else add(a[0],a[1]);
    }
    int ans=inf;
    fur(i,1,S)cmin(ans,bfs(i));
    if(ans==inf)ans=-1;
    printf("%d\n",ans);
}
```
