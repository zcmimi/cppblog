---
author: zc
avatar: null
categories:
- - 刷题记录
commnet: 1
date: 2020-04-05 22:51
html: '<details><summary>查看原题</summary><div id=''from''></div><p><button onclick="document.getElementById(''from'').innerHTML=''<iframe
  src=&quot;http://www.lydsy.com/JudgeOnline/problem.php?id=3626&quot; width=100%
  height=800px style=&quot;border: none;&quot;><iframe>''" class=''mdui-btn mdui-btn-raised
  mdui-ripple''>点击加载</button><a class=''mdui-btn mdui-btn-raised mdui-ripple'' href="http://www.lydsy.com/JudgeOnline/problem.php?id=3626"
  target=''_blank''>点击跳转</a><p></details>'
permalink: BZ 3626 LNOI2014 LCA
tags:
- lct
- 树链剖分
- 离线
- 树状数组
thumbnail: null
title: BZ 3626 LNOI2014 LCA
top: 0
---
求$\sum_{i=l}^r deep[LCA(i,z)]$

首先,可以把询问拆成两个部分相减$\sum_{i=1}^r deep[LCA(i,z)]-\sum_{i=1}^{l-1} deep[LCA(i,z)]$

考虑一种暴力解法: 把$1-r$到根的路径全部+1,再查询$z$到根的路径和就是答案

可以发现问题的答案是可以叠加求出的

容易想到排序后离线处理

用树剖或`LCT`求解都可以

这里采用树剖+树状数组
```cpp
#include<bits/stdc++.h>
#define fl(i,x) for(int i=head[x],to;to=e[i].to,i;i=e[i].nxt)
#define il __inline__ __attribute__ ((always_inline))
namespace IN{const int str=1<<20;static char in_buf[str],*in_s,*in_t;bool __=0;inline char gc(){return (in_s==in_t)&&(in_t=(in_s=in_buf)+fread(in_buf,1,str,stdin)),in_s==in_t?EOF:*in_s++;}template<typename T>inline void in(T &x){if(__)return;char c=gc();bool f=0;while(c!=EOF&&(c<'0'||c>'9'))f^=(c=='-'),c=gc();if(c==EOF){__=1;return;}x=0;while(c!=EOF&&'0'<=c&&c<='9')x=x*10+c-48,c=gc();if(c==EOF)__=1;if(f)x=-x;}template<typename T,typename ... arr>inline void in(T &x,arr & ... y){in(x),in(y...);}}using namespace IN;
namespace OUT{const char ln='\n';const int str=1<<20;static char out_buf[str],*out_s=out_buf,*out_t=out_buf+str;inline void flush(){fwrite(out_buf,1,out_s-out_buf,stdout);out_s=out_buf;}inline void pt(char c){(out_s==out_t)?(fwrite(out_s=out_buf,1,str,stdout),*out_s++=c):(*out_s++=c);}inline void out(char c){pt(c);}template<typename T>inline void out(T x){if(!x){pt('0');return;}if(x<0)pt('-'),x=-x;char a[50],t=0;while(x)a[t++]=x%10,x/= 10;while(t--)pt(a[t]+'0');}template<typename T,typename ... arr>inline void out(T x,arr & ... y){out(x),out(y...);}}using namespace OUT;
const int N=50011,P=201314;
int n,q,cnt=0,head[N];
struct edge{int to,nxt;}e[N<<1];
il void add(int x,int y){e[++cnt].to=y;e[cnt].nxt=head[x];head[x]=cnt;}
int f[N],top[N],siz[N],id[N],sz;
void dfs(int x){
    siz[x]=1;
    fl(i,x)dfs(to),siz[x]+=siz[to];
}
void bt(int x,int tp){
    top[x]=tp;id[x]=++sz;int k=n;
    fl(i,x)if(siz[to]>siz[k])k=to;
    if(k==n)return;bt(k,tp);
    fl(i,x)if(to!=k)bt(to,to);
}
int s[N],S[N];
il void mod(int &x){while(x>=P)x-=P;}
il int mo(int x){return x>=P?x%P:x;}
il void upd(int x,int v){
    for(int i=x--;i<=n;i+=i&-i)
        s[i]+=v,mod(S[i]+=x*v);
}
il int ask(int x){
    int res=0,RES=0;
    for(int i=x;i;i-=i&-i)
        mod(res+=s[i]),mod(RES+=S[i]);
    return mo(1ll*x*res%P-RES+P);
}
il void upd(int l,int r,int v){upd(l,v),upd(r+1,-v);}
il int ask(int l,int r){return mo(ask(r)-ask(l-1)+P);}
il int ASK(int x){
    int res=0;
    while(top[x])mod(res+=ask(id[top[x]],id[x])),x=f[top[x]];
    return mo(res+ask(id[x]));
}
int ans[N];
struct que{int x,z,v,id;bool operator<(que t)const{return x<t.x;}}Q[N<<1];
il void u(int x){
    while(top[x])upd(id[top[x]],id[x],1),x=f[top[x]];
    upd(id[0],id[x],1);
}
int main(){
    in(n,q);
    for(int i=1;i<n;++i)in(f[i]),add(f[i],i);
    dfs(0);bt(0,0);
    int l,r,z;
    for(int i=0;i<q;++i){
        in(l,r,z);
        Q[i<<1]={l-1,z,-1,i};
        Q[i<<1|1]={r,z,1,i};
    }
    std::sort(Q,Q+(q<<1));
    for(int i=0,j=-1;i<(q<<1);++i){
        while(j<Q[i].x)u(++j);
        mod(ans[Q[i].id]+=Q[i].v*ASK(Q[i].z));
    }
    for(int i=0;i<q;++i)out(mo(ans[i]+P),ln);
    flush();
}
```
