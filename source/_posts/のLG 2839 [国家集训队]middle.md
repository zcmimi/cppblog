---
author: zc
avatar: null
categories:
- - "\u5237\u9898\u8BB0\u5F55"
commnet: 1
date: 2019-12-31 11:31
html: "<details><summary>\u67E5\u770B\u539F\u9898</summary><div id='from'></div><p><button\
  \ onclick=\"document.getElementById('from').innerHTML='<iframe src=&quot;https://www.luogu.com.cn/problem/P2839&quot;\
  \ width=100% height=800px style=&quot;border: none;&quot;><iframe>'\" class='mdui-btn\
  \ mdui-btn-raised mdui-ripple'>\u70B9\u51FB\u52A0\u8F7D</button><a class='mdui-btn\
  \ mdui-btn-raised mdui-ripple' href=\"https://www.luogu.com.cn/problem/P2839\" target='_blank'>\u70B9\
  \u51FB\u8DF3\u8F6C</a><p></details>"
permalink: "LG 2839 [\u56FD\u5BB6\u96C6\u8BAD\u961F]middle"
tags:
- "\u4E8C\u5206"
- "\u4E3B\u5E2D\u6811"
thumbnail: null
title: "LG 2839 [\u56FD\u5BB6\u96C6\u8BAD\u961F]middle"
top: 0
---
可以先考虑离散化

离散话后是$1～n$

一般要求中位数可以:

二分中位数$x$

将区间中$<x$的赋值为$-1$,$\ge x$的赋值为$-1$

若区间和为$0$,那么$x$就是中位数

题目是要求左端点在$[a,b]$,右端点在$[c,d]$的序列的最大中位数

区间$[b+1,c-1]$是必选的

我们可以求$[a,b]$的最大后缀和$[c,d]$的最大前缀

如果这三个部分的和大于零,那么当前二分的值是合法的

~~这个一看就可以用线段树维护~~

---

我们再来考虑$x$变成$x+1$会有什么变化：

1. 原来$<x$的还是$-1$
2. 原来$>x$的还是$1$
3. 原来$=x$变成$-1$

所以我们只需修改值为$x$的位置(可以先用链表或$vector$存下所有值为$x$的位置)

其实从小到大排序后按顺序更改就完事了

数离散化后的大小不超过$n$

我们可以先预处理出所有$x$(中位数)对应的线段树

可是空间不够啊

这时候主席树就派上用场了

下面是简洁的代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 20011
int n,la=0;
struct node{
    int v,p;
    bool operator<(node x){return v<x.v;}
}b[N];
int ls[N*15],rs[N*15],rt[N],s[N*15],lm[N*15],rm[N*15],sz=0;
void pu(int x){
    s[x]=s[ls[x]]+s[rs[x]];
    lm[x]=max(lm[ls[x]],s[ls[x]]+lm[rs[x]]);
    rm[x]=max(rm[rs[x]],s[rs[x]]+rm[ls[x]]);
}
void build(int l,int r,int &x){
    x=++sz;
    if(l==r){
        s[x]=lm[x]=rm[x]=1;
        return;
    }
    int m=(l+r)>>1;
    build(l,m,ls[x]);build(m+1,r,rs[x]);
    pu(x);
}
void upd(int l,int r,int p,int &x,int pre){
    if(!x)x=++sz;
    if(l==r){
        s[x]=lm[x]=rm[x]=-1;
        return;
    }
    int m=(l+r)>>1;
    if(p<=m)upd(l,m,p,ls[x],ls[pre]),rs[x]=rs[pre];
    else upd(m+1,r,p,rs[x],rs[pre]),ls[x]=ls[pre];
    pu(x);
}
int qs(int L,int R,int l,int r,int x){
    if(L<=l&&r<=R)return s[x];
    int m=(l+r)>>1;
    if(L<=m&&R>m)return qs(L,R,l,m,ls[x])+qs(L,R,m+1,r,rs[x]);
    else if(L<=m)return qs(L,R,l,m,ls[x]);
    else return qs(L,R,m+1,r,rs[x]);
}
struct tr{int s,lm,rm;};
tr operator+(tr x,tr y){
    tr ans;
    ans.s=x.s+y.s;
    ans.lm=max(x.lm,x.s+y.lm);
    ans.rm=max(y.rm,y.s+x.rm);
    return ans;
}
tr qm(int L,int R,int l,int r,int x){
    if(L<=l&&r<=R)return tr{s[x],lm[x],rm[x]};
    int m=(l+r)>>1;
    if(L<=m&&R>m)return qm(L,R,l,m,ls[x])+qm(L,R,m+1,r,rs[x]);
    else if(L<=m)return qm(L,R,l,m,ls[x]);
    else return qm(L,R,m+1,r,rs[x]);
}
void work(){
    int A,B,C,D,q[4];
    scanf("%d%d%d%d",q+0,q+1,q+2,q+3);
    q[0]=(q[0]+la)%n+1;
    q[1]=(q[1]+la)%n+1;
    q[2]=(q[2]+la)%n+1;
    q[3]=(q[3]+la)%n+1;
    sort(q,q+4);
    A=q[0],B=q[1],C=q[2],D=q[3];
    int l=1,r=n,ans;
    while(l<=r){
        int m=(l+r)>>1,tot=0;
        if(B+1<=C-1)tot=qs(B+1,C-1,1,n,rt[m]);
        tot+=qm(A,B,1,n,rt[m]).rm+qm(C,D,1,n,rt[m]).lm;
        if(tot>=0)ans=m,l=m+1;
        else r=m-1;
    }
    printf("%d\n",la=b[ans].v);
}
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;++i)scanf("%d",&b[i]),b[i].p=i;
    sort(b+1,b+n+1);
    build(1,n,rt[1]);
    for(int i=2;i<=n;++i)
        upd(1,n,b[i-1].p,rt[i],rt[i-1]);
    int q;scanf("%d",&q);
    while(q--)work();
}
```
