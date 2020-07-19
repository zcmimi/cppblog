---
author: zc
avatar: null
categories:
- - "\u5237\u9898\u8BB0\u5F55"
commnet: 1
date: 2019-12-21 19:47
html: "<details><summary>\u67E5\u770B\u539F\u9898</summary><div id='from'></div><p><button\
  \ onclick=\"document.getElementById('from').innerHTML='<iframe src=&quot;https://www.luogu.com.cn/problem/CF208E&quot;\
  \ width=100% height=800px style=&quot;border: none;&quot;><iframe>'\" class='mdui-btn\
  \ mdui-btn-raised mdui-ripple'>\u70B9\u51FB\u52A0\u8F7D</button><a class='mdui-btn\
  \ mdui-btn-raised mdui-ripple' href=\"https://www.luogu.com.cn/problem/CF208E\"\
  \ target='_blank'>\u70B9\u51FB\u8DF3\u8F6C</a><p></details>"
permalink: LG CF208E Blood Cousins
tags:
- "\u9759\u6001\u94FE\u5206\u6CBB"
thumbnail: null
title: LG CF208E Blood Cousins
top: 0
---
倍增找$k$级祖先+~~dsu on tree~~静态链分治

设当前节点为$x$

如果$d_x < k$,那么答案当然为$0$
可以找到第$k$级祖先,然后在$k$级祖先上添加一组询问(求它子树中深度为$d_x$的节点数)

因为这个还算上了$x$本身,所以把结果-1就是答案了

统计区间中各个深度的点有多少个就直接$tot[d_x]+=(1\text{或}-1)$就可以了


上代码：
```cpp
#include<bits/stdc++.h>
#pragma GCC optimize(3)
#define il inline
#define rg register
#define Fur(i,x,y) for(register int i=x;i<=y;++i)
#define fl(i,x) for(register int i=head[x],to;to=e[i].to,i;i=e[i].nxt)
#define clr(x,y) memset(x,y,sizeof(x))
#define fin(s) freopen(s".in","r",stdin)
#define l2(n) ((int)(log2(n)))
namespace IO{const char* ln="\n";const int str=1<<20;struct IN{char buf[str],*s,*t;bool _;IN():s(buf),t(buf),_(0){}il char gc(){return s==t&&((t=(s=buf)+fread(buf,1,str,stdin))==s)?EOF:(*s++);}template<typename T>IN&operator>>(T&x){if(_)return *this;char c=gc();bool ff=0;while(c!=EOF&&(c<'0'||c>'9'))ff^=(c=='-'),c=gc();if(c==EOF){_=1;return *this;}x=0;while(c!=EOF&&'0'<=c&&c<='9')x=(x<<3)+(x<<1)+c-48,c=gc();if(c==EOF)_=1;if(ff)x=-x;return *this;}}in;struct OUT{char buf[str],*s,*t;OUT():s(buf),t(buf+str){}~OUT(){fwrite(buf,1,s-buf,stdout);}void pt(char c){(s==t)?(fwrite(s=buf,1,str,stdout),*s++=c):(*s++=c);}OUT&operator<<(const char*s){while(*s)pt(*s++);return *this;}template<typename T>OUT&operator<<(T x){if(!x)return pt('0'),*this;if(x<0)pt('-'),x=-x;char a[30],t=0;while(x)a[t++]=x%10,x/=10;while(t--)pt(a[t]+'0');return *this;}}out;}using namespace IO;
#define N 100011
int n,m,cnt=0,head[N],CNT=0,HEAD[N],tt=0,RT[N];
struct edge{
    int to,nxt;
}e[N],E[N];
il void add(int x,int y){
    e[++cnt].to=y;e[cnt].nxt=head[x];head[x]=cnt;
}
il void pb(int x,int y){
    E[++CNT].to=y;E[CNT].nxt=HEAD[x];HEAD[x]=CNT;
}
int f[17][N],d[N],siz[N],son[N],T[N],L[N],R[N],dfn=0;
il void dfs(int x){
    siz[x]=1;T[L[x]=++dfn]=x;
    fl(i,x){
        f[0][to]=x;d[to]=d[x]+1;
        dfs(to);siz[x]+=siz[to];
        if(siz[to]>siz[son[x]])son[x]=to;
    }
    R[x]=dfn;
}
il void st(){
    int k=l2(n);
    Fur(j,1,k)
        Fur(i,1,n)
        if(~f[j-1][i])f[j][i]=f[j-1][f[j-1][i]];
}
il int get(int x,int k){
    int t=0;
    while(k){
        if(k&1){
            x=f[t][x];
            if(!(~x))return -1;
        }
        k>>=1;++t;
    }
    return x;
}
struct que{int d,id;}q[N];
int ANS[N];
int tot[N];
il void Add(int x,int v){
    tot[d[x]]+=v;
}
il void upd(int x,int v){
    Fur(i,L[x],R[x])Add(T[i],v);
}
il void sol(int x){
    fl(i,x)if(to!=son[x]){
        sol(to);
        upd(to,-1);
    }
    if(son[x])sol(son[x]);
    Add(x,1);
    fl(i,x)if(to!=son[x])upd(to,1);
    for(register int i=HEAD[x],to;to=E[i].to,i;i=E[i].nxt)ANS[q[to].id]=tot[q[to].d]-1;
}
int main(){
    in>>n;
    register int x,k;
    Fur(i,1,n){
        in>>x;
        if(!x)RT[++RT[0]]=i;
        else add(x,i);
    }
    clr(f,-1);
    Fur(i,1,RT[0])dfs(RT[i]);
    st();
    in>>m;
    Fur(i,1,m){
        in>>x>>k;
        if(d[x]>=k)q[++tt]=que{d[x],i},pb(get(x,k),tt);
        else ANS[i]=0;
    }
    Fur(i,1,RT[0])sol(RT[i]),upd(RT[i],-1);
    Fur(i,1,m)out<<ANS[i]<<" ";
}
```
