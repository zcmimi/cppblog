---
author: zc
avatar: null
categories:
- - "\u5237\u9898\u8BB0\u5F55"
commnet: 1
date: 2020-04-03 01:53
html: "<details><summary>\u67E5\u770B\u539F\u9898</summary><div id='from'></div><p><button\
  \ onclick=\"document.getElementById('from').innerHTML='<iframe src=&quot;https://www.luogu.com.cn/problem/SP2939&quot;\
  \ width=100% height=800px style=&quot;border: none;&quot;><iframe>'\" class='mdui-btn\
  \ mdui-btn-raised mdui-ripple'>\u70B9\u51FB\u52A0\u8F7D</button><a class='mdui-btn\
  \ mdui-btn-raised mdui-ripple' href=\"https://www.luogu.com.cn/problem/SP2939\"\
  \ target='_blank'>\u70B9\u51FB\u8DF3\u8F6C</a><p></details>"
permalink: LG SP2939 QTREE5 - Query on a tree V
tags:
- lct
thumbnail: null
title: LG SP2939 QTREE5 - Query on a tree V
top: 0
---
根据套路,用`LCT`维护子树,信息为最值,每个节点都开一个`multiset`来记录虚子树信息

思考`LCT`的定义,每个`splay`维护的是一条深度单调递增的链(也可以说是实链)

我们定义`lm[x],rm[x]`分别为每条实链的上端和下端能够到达最近的白点的距离

这样就可以方便地更新信息了

每次求解可以`access(x),splay(x)`,然后$x$就是树根所在实链的下端,输出`rm[x]`就可以了

这样不需要换根什么的,也就不需要翻转操作,省去了复杂的pushdown过程
```cpp
#include<bits/stdc++.h>
#pragma GCC optimize(3)
#define il __inline__ __attribute__ ((always_inline))
namespace IO{const int str=1<<20;static char in_buf[str],*in_s,*in_t;bool __=0;il char gc(){return (in_s==in_t)&&(in_t=(in_s=in_buf)+fread(in_buf,1,str,stdin)),in_s==in_t?EOF:*in_s++;}il void in(char &ch){if(__)return;char c;while((c=gc())!=EOF&&isspace(c));if(c==EOF)__=1;else ch=c;}il void in(char *ch){*ch='\0';if(__)return;char c;while((c=gc())!=EOF&&isspace(c));if(c==EOF){__=1;return;}*ch=c;ch++;while((c=gc())!=EOF&&!isspace(c))*ch=c,ch++;if(c==EOF)__=1;*ch='\0';}template<typename T>il void in(T &x){if(__)return;char c=gc();bool f=0;while(c!=EOF&&(c<'0'||c>'9'))f^=(c=='-'),c=gc();if(c==EOF){__=1;return;}x=0;while(c!=EOF&&'0'<=c&&c<='9')x=x*10+c-48,c=gc();if(c==EOF)__=1;if(f)x=-x;}template<typename T,typename ... arr>il void in(T &x,arr & ... y){in(x),in(y...);}const char ln='\n';static char out_buf[str],*out_s=out_buf,*out_t=out_buf+str;il void flush(){fwrite(out_buf,1,out_s-out_buf,stdout);out_s=out_buf;}il void pt(char c){(out_s==out_t)?(fwrite(out_s=out_buf,1,str,stdout),*out_s++=c):(*out_s++=c);}il void out(const char* s){while(*s)pt(*s++);}il void out(char* s){while(*s)pt(*s++);}il void out(char c){pt(c);}template<typename T>il void out(T x){if(!x){pt('0');return;}if(x<0)pt('-'),x=-x;char a[50],t=0;while(x)a[t++]=x%10,x/= 10;while(t--)pt(a[t]+'0');}template<typename T,typename ... arr>il void out(T x,arr & ... y){out(x),out(y...);}}using namespace IO;
const int N=100011,inf=1000000000;
int n,q,siz[N],c[2][N],f[N],lm[N],rm[N];
bool rev[N],col[N];
using std::multiset;
multiset<int>s2[N];
#define ls(x) c[0][x]
#define rs(x) c[1][x]
il int min(int x,int y){return x<y?x:y;}
il void pu(int x){
    siz[x]=siz[ls(x)]+siz[rs(x)]+1;
    int t=s2[x].empty()?inf:*s2[x].begin();
    lm[x]=min(lm[ls(x)],siz[ls(x)]+min(col[x]?0:inf,min(t,lm[rs(x)]+1)));
    rm[x]=min(rm[rs(x)],siz[rs(x)]+min(col[x]?0:inf,min(t,rm[ls(x)]+1)));
}
il int g(int x){return rs(f[x])==x;}
il int nrt(int x){return ls(f[x])==x||rs(f[x])==x;}
il void rotate(int x){
    int y=f[x],z=f[y],l=g(x),r=!l,w=c[r][x];
    if(nrt(y))c[g(y)][z]=x;
    c[r][x]=y,c[l][y]=w;
    if(w)f[w]=y;
    f[y]=x,f[x]=z;
    pu(y),pu(x);
}
il void splay(int x){
    for(;nrt(x);rotate(x))if(nrt(f[x]))
        rotate(g(x)^g(f[x])?x:f[x]);
}
il void access(int x){
    for(int y=0;x;x=f[y=x]){
        splay(x);
        s2[x].insert(lm[rs(x)]+1);
        rs(x)=y;
        multiset<int>::iterator it=s2[x].lower_bound(lm[rs(x)]+1);
        if(it!=s2[x].end()&&(*it)==lm[rs(x)]+1)s2[x].erase(it);
        pu(x);
    }
}
struct edge{int to,nxt;}e[N<<1];
int cnt=0,head[N];
il void add(int x,int y){e[++cnt].to=y;e[cnt].nxt=head[x];head[x]=cnt;}
void dfs(int x,int fa){
    for(int i=head[x],to;to=e[i].to,i;i=e[i].nxt)
    if(to!=fa){
        f[to]=x;s2[x].insert(inf+1);pu(x);
        dfs(to,x);
    }
}
int main(){
    in(n);
    lm[0]=rm[0]=inf;
    int opt,x,y;
    for(int i=1;i<n;++i)in(x,y),add(x,y),add(y,x);
    dfs(1,0);
    in(q);
    while(q--){
        in(opt,x);
        access(x),splay(x);
        if(!opt)col[x]^=1,pu(x);
        else out(rm[x]>n?-1:rm[x],ln);
    }
    flush();
}
```
