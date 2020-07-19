---
author: zc
avatar: null
categories:
- - "\u5237\u9898\u8BB0\u5F55"
commnet: 1
date: 2020-04-09 20:43
html: "<details><summary>\u67E5\u770B\u539F\u9898</summary><div id='from'></div><p><button\
  \ onclick=\"document.getElementById('from').innerHTML='<iframe src=&quot;https://www.luogu.com.cn/problem/SP16580&quot;\
  \ width=100% height=800px style=&quot;border: none;&quot;><iframe>'\" class='mdui-btn\
  \ mdui-btn-raised mdui-ripple'>\u70B9\u51FB\u52A0\u8F7D</button><a class='mdui-btn\
  \ mdui-btn-raised mdui-ripple' href=\"https://www.luogu.com.cn/problem/SP16580\"\
  \ target='_blank'>\u70B9\u51FB\u8DF3\u8F6C</a><p></details>"
permalink: LG SP16580 QTREE7 - Query on a tree VII
tags:
- lct
thumbnail: null
title: LG SP16580 QTREE7 - Query on a tree VII
top: 0
---
还是QTREE6的方法

从维护子树大小变成了维护子树最值
```cpp
#include<bits/stdc++.h>
#pragma GCC optimize(3)
#define il __inline__ __attribute__ ((always_inline))
namespace IO{const int str=1<<20;static char in_buf[str],*in_s,*in_t;bool __=0;il char gc(){return (in_s==in_t)&&(in_t=(in_s=in_buf)+fread(in_buf,1,str,stdin)),in_s==in_t?EOF:*in_s++;}il void in(char &ch){if(__)return;char c;while((c=gc())!=EOF&&isspace(c));if(c==EOF)__=1;else ch=c;}il void in(char *ch){*ch='\0';if(__)return;char c;while((c=gc())!=EOF&&isspace(c));if(c==EOF){__=1;return;}*ch=c;ch++;while((c=gc())!=EOF&&!isspace(c))*ch=c,ch++;if(c==EOF)__=1;*ch='\0';}template<typename T>il void in(T &x){if(__)return;char c=gc();bool f=0;while(c!=EOF&&(c<'0'||c>'9'))f^=(c=='-'),c=gc();if(c==EOF){__=1;return;}x=0;while(c!=EOF&&'0'<=c&&c<='9')x=x*10+c-48,c=gc();if(c==EOF)__=1;if(f)x=-x;}template<typename T,typename ... arr>il void in(T &x,arr & ... y){in(x),in(y...);}const char ln='\n';static char out_buf[str],*out_s=out_buf,*out_t=out_buf+str;il void flush(){fwrite(out_buf,1,out_s-out_buf,stdout);out_s=out_buf;}il void pt(char c){(out_s==out_t)?(fwrite(out_s=out_buf,1,str,stdout),*out_s++=c):(*out_s++=c);}il void out(const char* s){while(*s)pt(*s++);}il void out(char* s){while(*s)pt(*s++);}il void out(char c){pt(c);}template<typename T>il void out(T x){if(!x){pt('0');return;}if(x<0)pt('-'),x=-x;char a[50],t=0;while(x)a[t++]=x%10,x/= 10;while(t--)pt(a[t]+'0');}template<typename T,typename ... arr>il void out(T x,arr & ... y){out(x),out(y...);}}using namespace IO;
const int N=100011,inf=1000000000;
using std::multiset;
int n,q,cnt,head[N],fa[N],v[N];
bool col[N];
struct edge{int to,nxt;}e[N<<1];
il void add(int x,int y){e[++cnt].to=y;e[cnt].nxt=head[x];head[x]=cnt;}
struct LCT{
    LCT(){s[0]=-inf;}
    int s[N],c[2][N],f[N];
    multiset<int>s2[N];
    #define ls c[0][x]
    #define rs c[1][x]
    il int max(int x,int y){return x>y?x:y;}
    il void pu(int x){
        s[x]=max(max(s[ls],s[rs]),v[x]);
        if(!s2[x].empty())s[x]=max(s[x],*s2[x].rbegin());
    }
    il int g(int x){return c[1][f[x]]==x;}
    il int nrt(int x){return c[0][f[x]]==x||c[1][f[x]]==x;}
    il void rotate(int x){
        int y=f[x],z=f[y],l=g(x),r=!l,w=c[r][x];
        if(nrt(y))c[g(y)][z]=x;
        c[r][x]=y,c[l][y]=w;
        if(w)f[w]=y;
        f[x]=z,f[y]=x;
        pu(y),pu(x);
    }
    il void splay(int x){
        for(int y;nrt(x);rotate(x))if(nrt(y=f[x]))
            rotate(g(x)^g(y)?x:y);
        pu(x);
    }
    il void access(int x){
        for(int y=0;x;x=f[y=x]){
            splay(x);
            if(rs)s2[x].insert(s[rs]);
            if(rs=y)s2[x].erase(s2[x].find(s[y]));
            pu(x);
        }
    }
    il void brt(int x){access(x),splay(x);}
    il int frt(int x){
        for(brt(x);ls;x=ls);
        splay(x);return x;
    }
    il void link(int x){
        splay(x);
        int y=f[x]=fa[x];
        brt(y);
        c[1][y]=x,pu(y);
    }
    il void cut(int x){
        brt(x);
        ls=f[ls]=0;
        pu(x);
    }
    il int ask(int x){return s[c[1][frt(x)]];}
}T[2];
void dfs(int x){
    for(int i=head[x],to;to=e[i].to,i;i=e[i].nxt)
        if(to!=fa[x])fa[to]=x,dfs(to);
    T[col[x]].link(x);
}
int main(){
    in(n);
    int x,y;
    for(int i=1;i<n;++i)
        in(x,y),
        add(x,y),add(y,x);
    for(int i=1;i<=n;++i)in(col[i]);
    for(int i=1;i<=n;++i)in(v[i]);
    fa[1]=n+1;dfs(1);
    in(q);
    while(q--){
        in(y,x);
        if(y==0)out(T[col[x]].ask(x),ln);
        else if(y==1)T[col[x]].cut(x),T[col[x]^=1].link(x);
        else{
            T[0].brt(x),T[1].brt(x),
            in(v[x]),
            T[0].pu(x),T[1].pu(x);
        }
    }
    flush();
}
```
