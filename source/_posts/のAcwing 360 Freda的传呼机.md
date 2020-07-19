---
author: zc
avatar: null
categories:
- - "\u5237\u9898\u8BB0\u5F55"
commnet: 1
date: 2020-01-25 20:19
html: "<details><summary>\u67E5\u770B\u539F\u9898</summary><div id='from'></div><p><button\
  \ onclick=\"document.getElementById('from').innerHTML='<iframe src=&quot;&quot;\
  \ width=100% height=800px style=&quot;border: none;&quot;><iframe>'\" class='mdui-btn\
  \ mdui-btn-raised mdui-ripple'>\u70B9\u51FB\u52A0\u8F7D</button><a class='mdui-btn\
  \ mdui-btn-raised mdui-ripple' href=\"\" target='_blank'>\u70B9\u51FB\u8DF3\u8F6C\
  </a><p></details>"
permalink: "Acwing 360 Freda\u7684\u4F20\u547C\u673A"
tags:
- "\u57FA\u73AF\u6811"
- lca
- "\u4ED9\u4EBA\u638C"
thumbnail: null
title: "Acwing 360 Freda\u7684\u4F20\u547C\u673A"
top: 0
---
```cpp
#include<cstdio>
#pragma GCC optimize(3)
#define il __inline__ __attribute__ ((always_inline))
#define Fur(i,x,y) for(int i(x);i<=y;++i)
#define Fdr(i,x,y) for(int i(x);i>=y;--i)
il void swap(int &x,int &y){int t=x;x=y;y=t;}
il int min(int x,int y){return x<y?x:y;}
il int abs(int x){return x>0?x:-x;}
namespace IO{const int str=1<<20;static char in_buf[str],*in_s,*in_t;bool __=0;il char gc(){return (in_s==in_t)&&(in_t=(in_s=in_buf)+fread(in_buf,1,str,stdin)),in_s==in_t?__=1,EOF:*in_s++;}template<typename T>il void in(T &x){if(__)return;char c=gc();bool f=0;while(c!=EOF&&(c<'0'||c>'9'))f^=(c=='-'),c=gc();if(c==EOF){__=1;return;}x=0;while(c!=EOF&&'0'<=c&&c<='9')x=x*10+c-48,c=gc();if(c==EOF)__=1;if(f)x=-x;}template<typename T,typename ... arr>il void in(T &x,arr & ... y){in(x),in(y...);}const char ln='\n';static char out_buf[str],*out_s=out_buf,*out_t=out_buf+str;il void flush(){fwrite(out_buf,1,out_s-out_buf,stdout);out_s=out_buf;}il void pt(char c){(out_s==out_t)?(fwrite(out_s=out_buf,1,str,stdout),*out_s++=c):(*out_s++=c);}il void out(const char* s){while(*s)pt(*s++);}il void out(char* s){while(*s)pt(*s++);}il void out(char c){pt(c);}template<typename T>il void out(T x){if(!x){pt('0');return;}if(x<0)pt('-'),x=-x;char a[50],t=0;while(x)a[t++]=x%10,x/= 10;while(t--)pt(a[t]+'0');}template<typename T,typename ... arr>il void out(T x,arr & ... y){out(x),out(y...);}}using namespace IO;
const int N=20011;
int n,m,q,cnt=0,head[N],HEAD[N];
struct edge{
    int to,nxt,w;
}e[N<<2];
#define fl(i,x) for(int i(head[x]),to;to=e[i].to,i;i=e[i].nxt)
#define FL(i,x) for(int i(HEAD[x]),to;to=e[i].to,i;i=e[i].nxt)
il void add(int x,int y,int w){
    e[++cnt].to=y;e[cnt].nxt=head[x];head[x]=cnt;e[cnt].w=w;
    e[++cnt].to=x;e[cnt].nxt=head[y];head[y]=cnt;e[cnt].w=w;
}
il void ADD(int x,int y,int w){
    e[++cnt].to=y;e[cnt].nxt=HEAD[x];HEAD[x]=cnt;e[cnt].w=w;
    e[++cnt].to=x;e[cnt].nxt=HEAD[y];HEAD[y]=cnt;e[cnt].w=w;
}
int dfn[N],low[N],sz=0,fa[N],tot,b[N],id[N],s[N];
void solve(int x,int y,int w){
    ++tot;
    int t=w,tt=0;
    for(int i=y;i!=fa[x];i=fa[i]){
        s[i]=t;
        t+=b[i];
        id[i]=tt++;
    }
    s[tot]=s[x];s[x]=0;
    for(int i=y;i!=fa[x];i=fa[i])
        ADD(tot,i,min(s[i],s[tot]-s[i]));
}
void tarjan(int x){
    dfn[x]=low[x]=++sz;
    fl(i,x)if(to!=fa[x]){
        if(!dfn[to]){
            fa[to]=x;b[to]=e[i].w;
            tarjan(to);
            low[x]=min(low[x],low[to]);
        }
        else low[x]=min(low[x],dfn[to]);
        if(low[to]>dfn[x])ADD(x,to,e[i].w);
    }
    fl(i,x)if(fa[to]!=x&&dfn[to]>dfn[x])
        solve(x,to,e[i].w);
}
int f[N],d[N],dep[N],siz[N],top[N],A,B,st[N],ed[N],df=0;
void dfs(int x){
    st[x]=++df;
    siz[x]=1;
    FL(i,x)if(to!=f[x]){
        f[to]=x;
        d[to]=d[x]+1;
        dep[to]=dep[x]+e[i].w;
        dfs(to);
        siz[x]+=siz[to];
    }
    ed[x]=df;
}
void bt(int x,int tp){
    top[x]=tp;int k=0;
    FL(i,x)if(to!=f[x]&&siz[to]>siz[k])k=to;
    if(!k)return;bt(k,tp);
    FL(i,x)if(!top[to])bt(to,to);
}
il int lca(int x,int y){
    int ox=x,oy=y;
    while(top[x]!=top[y]){
        if(d[top[x]]<d[top[y]])swap(x,y);
        x=f[top[x]];
    }
    if(d[x]>d[y])swap(x,y);
    FL(i,x)if(to!=f[x]){
        if(st[to]<=st[ox]&&ed[ox]<=ed[to])A=to;
        if(st[to]<=st[oy]&&ed[oy]<=ed[to])B=to;
    }
    return x;
}
int main(){
    in(n,m,q);tot=n;
    int x,y,w;
    Fur(i,1,m)in(x,y,w),add(x,y,w);
    tarjan(1);
    dfs(1);bt(1,1);
    while(q--){
        in(x,y);
        w=lca(x,y);
        if(w<=n)out(dep[x]+dep[y]-2*dep[w],ln);
        else out(dep[x]+dep[y]-dep[A]-dep[B]+min(s[w]-abs(s[B]-s[A]),abs(s[A]-s[B])),ln);
    }
    flush();
}
```
