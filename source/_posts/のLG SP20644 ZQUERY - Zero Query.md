---
author: zc
avatar: null
categories:
- - 刷题记录
commnet: 1
date: 2020-07-15 19:12
html: '<details><summary>查看原题</summary><div id=''from''></div><p><button onclick="document.getElementById(''from'').innerHTML=''<iframe
  src=&quot;https://www.luogu.com.cn/problem/SP20644&quot; width=100% height=800px
  style=&quot;border: none;&quot;><iframe>''" class=''mdui-btn mdui-btn-raised mdui-ripple''>点击加载</button><a
  class=''mdui-btn mdui-btn-raised mdui-ripple'' href="https://www.luogu.com.cn/problem/SP20644"
  target=''_blank''>点击跳转</a><p></details>'
permalink: LG SP20644 ZQUERY - Zero Query
tags:
- 莫队
- 回滚莫队
thumbnail: null
title: LG SP20644 ZQUERY - Zero Query
top: 0

---
这题可以算是回滚莫队板子题

设$S$为前缀和

假设区间$[l,r]$区间和为$0$,那么$S_r-S_{1-1}=0$

如果使用莫队算法的话,容易想到:

用桶记录某个前缀和出现的最大/最小位置,加点操作就很容易维护答案

但这样的话删点操作就有点难实现了

可以使用回滚莫队

回滚莫队是一种只添加不删除的莫队,实现如下:

首先对原序列进行分块,并对询问按照如下的方式排序:以左端点所在的块升序为第一关键字,以右端点升序为第二关键字

枚举当前要处理的块,处理所有左端点在该块内的询问,

设当前块右端为$R$,左指针移动到$R+1$,右指针移动到$R$.

若询问两端在同一块内,那么暴力枚举统计即可

1. 由于左端点在同一块内,右端点单调递增

   不断右移右指针到当前询问右端点,并加点更新总答案

   (每个块右端点总位移不超过$n$)

2. 不断左移左指针到当前询问左端点,并加点更新当前询问答案
   
   然后将左端点回滚到$R+1$,撤销加点操作对桶的影响

   (每次回滚左端点位移不超过$\sqrt n$)

继续处理下一个询问

总复杂度$O(n\sqrt n)$,实测跑的飞快

请配合代码理解,**注意细节**
```cpp
#include<bits/stdc++.h>
const int N=50011;
int n,m,blk,s[N],p[N*2],mi[N*2],ma[N*2],ans[N],clr[N];
struct que{
    int l,r,id,pl,pr;
    bool operator<(que t){return pl!=t.pl?l<t.l:r<t.r;}
}q[N];
void cmax(int&x,int y){if(y>x)x=y;}
int main(){
    scanf("%d%d",&n,&m);blk=sqrt(n);
    s[0]=n;
    for(int i=1;i<=n;++i)
        scanf("%d",s+i),s[i]+=s[i-1];
    int l,r,mx,tt;
    for(int i=1;i<=m;++i)
        scanf("%d%d",&l,&r),
        q[i]=(que){l,r,i,(l-1)/blk+1,(r-1)/blk+1};
    std::sort(q+1,q+m+1);
    memset(mi,126,sizeof mi),memset(p,126,sizeof p);
    int tot=(n-1)/blk+1;
    for(int now=1,i=1,R=blk;now<=tot;R+=blk,++now){
        if(R>n)R=n;
        l=R+1,r=R,mx=0,tt=0;
        for(;q[i].pl==now;++i){
            if(q[i].pr==now){
                p[s[q[i].l-1]]=q[i].l-1;
                for(int j=q[i].l;j<=q[i].r;++j)
                    if(p[s[j]]<j)cmax(ans[q[i].id],j-p[s[j]]);
                    else p[s[j]]=j;
                p[s[q[i].l-1]]=n;
                for(int j=q[i].l;j<=q[i].r;++j)p[s[j]]=n;
                continue;
            }
            while(r<q[i].r){
                ++r,ma[s[r]]=r;
                if(mi[s[r]]>n)mi[s[r]]=r,clr[tt++]=s[r];
                else cmax(mx,r-mi[s[r]]);
            }
            ans[q[i].id]=mx;
            while(l>=q[i].l){
                --l;
                if(ma[s[l]])cmax(ans[q[i].id],ma[s[l]]-l);
                else ma[s[l]]=l;
            }
            for(;l<=R;++l)if(ma[s[l]]==l)ma[s[l]]=0;
        }
        while(tt--)mi[clr[tt]]=n,ma[clr[tt]]=0;
    }
    for(int i=1;i<=m;++i)printf("%d\n",ans[i]);
}
```
