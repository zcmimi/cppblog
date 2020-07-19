---
author: zc
avatar: null
categories:
- - "\u5237\u9898\u8BB0\u5F55"
commnet: 1
date: 2020-03-01 14:52
html: "<details><summary>\u67E5\u770B\u539F\u9898</summary><div id='from'></div><p><button\
  \ onclick=\"document.getElementById('from').innerHTML='<iframe src=&quot;https://www.luogu.com.cn/problem/P4556&quot;\
  \ width=100% height=800px style=&quot;border: none;&quot;><iframe>'\" class='mdui-btn\
  \ mdui-btn-raised mdui-ripple'>\u70B9\u51FB\u52A0\u8F7D</button><a class='mdui-btn\
  \ mdui-btn-raised mdui-ripple' href=\"https://www.luogu.com.cn/problem/P4556\" target='_blank'>\u70B9\
  \u51FB\u8DF3\u8F6C</a><p></details>"
permalink: "LG 4556 [Vani\u6709\u7EA6\u4F1A]\u96E8\u5929\u7684\u5C3E\u5DF4"
tags:
- "\u7EBF\u6BB5\u6811\u5408\u5E76"
- lca
- "\u5DEE\u5206"
thumbnail: null
title: "LG 4556 [Vani\u6709\u7EA6\u4F1A]\u96E8\u5929\u7684\u5C3E\u5DF4"
top: 0
---
树上差分,统计的时候每个节点都合并自身子节点的结果

每个点都维护一颗动态开点权值线段树

在$x\leftrightarrow y$区间加可以看成$x,y$的$w$位置$+1$,$lca(x,y),f_{lca(x,y)}$的$w$位置$-1$

统计的时候不断向上线段树合并

具体看代码
```cpp
#include<bits/stdc++.h>
#define il __inline__ __attribute__ ((always_inline))
#define Fur(i,x,y) for(int i(x);i<=y;++i)
#define fl(i,x) for(int i(head[x]),to;to=e[i].to,i;i=e[i].nxt)
const int str=1<<20;static char in_buf[str],*in_s,*in_t;bool __=0;il char gc(){return (in_s==in_t)&&(in_t=(in_s=in_buf)+fread(in_buf,1,str,stdin)),in_s==in_t?EOF:*in_s++;}template<typename T>il void in(T &x){if(__)return;char c=gc();bool f=0;while(c!=EOF&&(c<'0'||c>'9'))f^=(c=='-'),c=gc();if(c==EOF){__=1;return;}x=0;while(c!=EOF&&'0'<=c&&c<='9')x=x*10+c-48,c=gc();if(c==EOF)__=1;if(f)x=-x;}template<typename T,typename ... arr>il void in(T &x,arr & ... y){in(x),in(y...);}const char ln='\n';static char out_buf[str],*out_s=out_buf,*out_t=out_buf+str;il void flush(){fwrite(out_buf,1,out_s-out_buf,stdout);out_s=out_buf;}il void pt(char c){(out_s==out_t)?(fwrite(out_s=out_buf,1,str,stdout),*out_s++=c):(*out_s++=c);}template<typename T>il void out(T x){if(!x){pt('0');return;}if(x<0)pt('-'),x=-x;char a[50],t=0;while(x)a[t++]=x%10,x/= 10;while(t--)pt(a[t]+'0');}
const int N=100011;
int n,q,cnt=0,sz=0,head[N],s[N*60],S[N*60],ls[N*60],rs[N*60],RT[N],ans[N];
il void pu(int rt){s[ls[rt]]>=s[rs[rt]]?(s[rt]=s[ls[rt]],S[rt]=S[ls[rt]]):(s[rt]=s[rs[rt]],S[rt]=S[rs[rt]]);}
void upd(int &rt,int x,int v,int l=1,int r=100000){
    if(!rt)rt=++sz;
    if(l==r){s[rt]+=v;S[rt]=l;return;}
    int m=(l+r)>>1;
    if(x<=m)upd(ls[rt],x,v,l,m);
    else upd(rs[rt],x,v,m+1,r);
    pu(rt);
}
int mg(int x,int y,int l=1,int r=100000){
    if(!x||!y)return x|y;
    if(l==r)return s[x]+=s[y],S[x]=l,x;
    int m=(l+r)>>1;
    ls[x]=mg(ls[x],ls[y],l,m); 
    rs[x]=mg(rs[x],rs[y],m+1,r);
    pu(x);return x;
}
struct edge{int to,nxt;}e[N<<1];
il void add(int x,int y){e[++cnt].to=y;e[cnt].nxt=head[x];head[x]=cnt;}
int d[N],top[N],siz[N],f[N];
void dfs(int x){
    siz[x]=1;
    fl(i,x)if(to!=f[x]){
        f[to]=x;d[to]=d[x]+1;
        dfs(to);
        siz[x]+=siz[to];
    }
}
void bt(int x,int tp){
    top[x]=tp;int k=0;
    fl(i,x)if(to!=f[x]&&siz[to]>siz[k])k=to;
    if(k)bt(k,tp);
    fl(i,x)if(!top[to])bt(to,to);
}
il int lca(int x,int y){
    while(top[x]!=top[y])
        d[top[x]]>d[top[y]]?x=f[top[x]]:y=f[top[y]];
    return d[x]<d[y]?x:y;
}
void solve(int x){
    fl(i,x)if(to!=f[x])
        solve(to),
        RT[x]=mg(RT[x],RT[to]);
    if(s[RT[x]])ans[x]=S[RT[x]];
}
int main(){
    in(n,q);
    int x,y,w;
    Fur(i,2,n)in(x,y),add(x,y),add(y,x);
    dfs(1);bt(1,1);
    while(q--){
        in(x,y,w);
        int t=lca(x,y);
        upd(RT[x],w,1);upd(RT[y],w,1);
        upd(RT[t],w,-1);upd(RT[f[t]],w,-1);
    }
    solve(1);
    Fur(i,1,n)out(ans[i]),pt('\n');
    flush();
}
```
