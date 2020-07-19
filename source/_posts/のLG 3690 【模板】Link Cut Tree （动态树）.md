---
author: zc
avatar: null
categories:
- - "\u5237\u9898\u8BB0\u5F55"
commnet: 1
date: 2020-03-29 10:46
html: "<details><summary>\u67E5\u770B\u539F\u9898</summary><div id='from'></div><p><button\
  \ onclick=\"document.getElementById('from').innerHTML='<iframe src=&quot;https://www.luogu.com.cn/problem/P3690&quot;\
  \ width=100% height=800px style=&quot;border: none;&quot;><iframe>'\" class='mdui-btn\
  \ mdui-btn-raised mdui-ripple'>\u70B9\u51FB\u52A0\u8F7D</button><a class='mdui-btn\
  \ mdui-btn-raised mdui-ripple' href=\"https://www.luogu.com.cn/problem/P3690\" target='_blank'>\u70B9\
  \u51FB\u8DF3\u8F6C</a><p></details>"
permalink: "LG 3690 \u3010\u6A21\u677F\u3011Link Cut Tree \uFF08\u52A8\u6001\u6811\
  \uFF09"
tags:
- "\u6A21\u677F"
- lct
thumbnail: null
title: "LG 3690 \u3010\u6A21\u677F\u3011Link Cut Tree \uFF08\u52A8\u6001\u6811\uFF09"
top: 0
---
```cpp
#include<bits/stdc++.h>
#define il __inline__ __attribute__ ((always_inline))
namespace IN{const int str=1<<20;static char in_buf[str],*in_s,*in_t;bool __=0;inline char gc(){return (in_s==in_t)&&(in_t=(in_s=in_buf)+fread(in_buf,1,str,stdin)),in_s==in_t?EOF:*in_s++;}template<typename T>inline void in(T &x){if(__)return;char c=gc();bool f=0;while(c!=EOF&&(c<'0'||c>'9'))f^=(c=='-'),c=gc();if(c==EOF){__=1;return;}x=0;while(c!=EOF&&'0'<=c&&c<='9')x=x*10+c-48,c=gc();if(c==EOF)__=1;if(f)x=-x;}template<typename T,typename ... arr>inline void in(T &x,arr & ... y){in(x),in(y...);}}using namespace IN;
namespace OUT{const char ln='\n';const int str=1<<20;static char out_buf[str],*out_s=out_buf,*out_t=out_buf+str;inline void flush(){fwrite(out_buf,1,out_s-out_buf,stdout);out_s=out_buf;}inline void pt(char c){(out_s==out_t)?(fwrite(out_s=out_buf,1,str,stdout),*out_s++=c):(*out_s++=c);}inline void out(char c){pt(c);}template<typename T>inline void out(T x){if(!x){pt('0');return;}if(x<0)pt('-'),x=-x;char a[50],t=0;while(x)a[t++]=x%10,x/= 10;while(t--)pt(a[t]+'0');}template<typename T,typename ... arr>inline void out(T x,arr & ... y){out(x),out(y...);}}using namespace OUT;
const int N=100011;
int n,m,s[N],v[N],c[2][N],f[N],st[N];
bool rev[N];
#define ls(x) c[0][x]
#define rs(x) c[1][x]
il void pu(int x){s[x]=s[ls(x)]^s[rs(x)]^v[x];}
il void pr(int x){int t=ls(x);ls(x)=rs(x);rs(x)=t;rev[x]^=1;}
il void pd(int x){
    if(rev[x]){
        if(ls(x))pr(ls(x));
        if(rs(x))pr(rs(x));
        rev[x]=0;
    }
}
il int g(int x){return rs(f[x])==x;}
il int nrt(int x){return ls(f[x])==x||rs(f[x])==x;}
il void rotate(int x){
    int y=f[x],z=f[y],l=g(x),r=!l,w=c[r][x];
    if(nrt(y))c[g(y)][z]=x;
    c[r][x]=y,c[l][y]=w;
    if(w)f[w]=y;
    f[x]=z,f[y]=x;
    pu(y),pu(x);
}
il void splay(int x){
    int z=0,y=st[++z]=x;
    while(nrt(y))st[++z]=y=f[y];
    while(z)pd(st[z--]);
    for(;nrt(x);rotate(x))if(nrt(f[x]))
        rotate(g(x)^g(f[x])?x:f[x]);
}
il void access(int x){
    for(int y=0;x;x=f[y=x])
        splay(x),rs(x)=y,pu(x);
}
il void mrt(int x){access(x),splay(x),pr(x);}
il int frt(int x){
    for(access(x),splay(x);ls(x);pd(x),x=ls(x));
    splay(x);return x;
}
il void link(int x,int y){
    mrt(x);
    if(frt(y)^x)f[x]=y;
}
il void sl(int x,int y){mrt(x),access(y),splay(y);}
il void cut(int x,int y){
    mrt(x);
    if(frt(y)==x&&f[y]==x&&!ls(y))
        f[y]=rs(x)=0,pu(x);
}
int main(){
    in(n,m);
    for(int i=1;i<=n;++i)in(v[i]);
    int opt,x,y;
    while(m--){
        in(opt,x,y);
        if(opt==0)sl(x,y),out(s[y],ln);
        if(opt==1)link(x,y);
        if(opt==2)cut(x,y);
        if(opt==3)splay(x),v[x]=y;
    }
    flush();
}
```
