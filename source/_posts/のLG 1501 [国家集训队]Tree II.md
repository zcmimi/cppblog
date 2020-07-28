---
author: zc
avatar: null
categories:
- - 刷题记录
commnet: 1
date: 2020-03-31 22:37
html: '<details><summary>查看原题</summary><div id=''from''></div><p><button onclick="document.getElementById(''from'').innerHTML=''<iframe
  src=&quot;https://www.luogu.com.cn/problem/P1501&quot; width=100% height=800px style=&quot;border:
  none;&quot;><iframe>''" class=''mdui-btn mdui-btn-raised mdui-ripple''>点击加载</button><a
  class=''mdui-btn mdui-btn-raised mdui-ripple'' href="https://www.luogu.com.cn/problem/P1501"
  target=''_blank''>点击跳转</a><p></details>'
permalink: LG 1501 [国家集训队]Tree II
tags:
- lct
thumbnail: null
title: LG 1501 [国家集训队]Tree II
top: 0
---
```cpp
#include<bits/stdc++.h>
#define il __inline__ __attribute__ ((always_inline))
namespace IO{const int str=1<<20;static char in_buf[str],*in_s,*in_t;bool __=0;il char gc(){return (in_s==in_t)&&(in_t=(in_s=in_buf)+fread(in_buf,1,str,stdin)),in_s==in_t?EOF:*in_s++;}il void in(char &ch){if(__)return;char c;while((c=gc())!=EOF&&isspace(c));if(c==EOF)__=1;else ch=c;}il void in(char *ch){*ch='\0';if(__)return;char c;while((c=gc())!=EOF&&isspace(c));if(c==EOF){__=1;return;}*ch=c;ch++;while((c=gc())!=EOF&&!isspace(c))*ch=c,ch++;if(c==EOF)__=1;*ch='\0';}template<typename T>il void in(T &x){if(__)return;char c=gc();bool f=0;while(c!=EOF&&(c<'0'||c>'9'))f^=(c=='-'),c=gc();if(c==EOF){__=1;return;}x=0;while(c!=EOF&&'0'<=c&&c<='9')x=x*10+c-48,c=gc();if(c==EOF)__=1;if(f)x=-x;}template<typename T,typename ... arr>il void in(T &x,arr & ... y){in(x),in(y...);}const char ln='\n';static char out_buf[str],*out_s=out_buf,*out_t=out_buf+str;il void flush(){fwrite(out_buf,1,out_s-out_buf,stdout);out_s=out_buf;}il void pt(char c){(out_s==out_t)?(fwrite(out_s=out_buf,1,str,stdout),*out_s++=c):(*out_s++=c);}il void out(const char* s){while(*s)pt(*s++);}il void out(char* s){while(*s)pt(*s++);}il void out(char c){pt(c);}template<typename T>il void out(T x){if(!x){pt('0');return;}if(x<0)pt('-'),x=-x;char a[50],t=0;while(x)a[t++]=x%10,x/= 10;while(t--)pt(a[t]+'0');}template<typename T,typename ... arr>il void out(T x,arr & ... y){out(x),out(y...);}}using namespace IO;
const int N=100011,P=51061;
#define int long long
int n,q,s[N],siz[N],v[N],c[2][N],f[N],st[N],add[N],mul[N];
bool rev[N];
#define ls(x) c[0][x]
#define rs(x) c[1][x]
il void pu(int x){
    s[x]=(s[ls(x)]+s[rs(x)]+v[x])%P;
    siz[x]=siz[ls(x)]+siz[rs(x)]+1;
}
il void pr(int x){int t=ls(x);ls(x)=rs(x);rs(x)=t;rev[x]^=1;}
il void pd(int x){
    if(rev[x]){
        if(ls(x))pr(ls(x));
        if(rs(x))pr(rs(x));
        rev[x]=0;
    }
    if(mul[x]^1){
        if(ls(x)){
            mul[ls(x)]=mul[ls(x)]*mul[x]%P;
            add[ls(x)]=add[ls(x)]*mul[x]%P;
            s[ls(x)]=s[ls(x)]*mul[x]%P;
            v[ls(x)]=v[ls(x)]*mul[x]%P;
        }
        if(rs(x)){
            mul[rs(x)]=mul[rs(x)]*mul[x]%P;
            add[rs(x)]=add[rs(x)]*mul[x]%P;
            s[rs(x)]=s[rs(x)]*mul[x]%P;
            v[rs(x)]=v[rs(x)]*mul[x]%P;
        }
        mul[x]=1;
    }
    if(add[x]){
        if(ls(x)){
            add[ls(x)]=(add[ls(x)]+add[x])%P;
            s[ls(x)]=(s[ls(x)]+add[x]*siz[ls(x)]%P)%P;
            v[ls(x)]=(v[ls(x)]+add[x])%P;
        }
        if(rs(x)){
            add[rs(x)]=(add[rs(x)]+add[x])%P;
            s[rs(x)]=(s[rs(x)]+add[x]*siz[rs(x)]%P)%P;
            v[rs(x)]=(v[rs(x)]+add[x])%P;
        }
        add[x]=0;
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
        rotate(g(f[x])^g(x)?x:f[x]);
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
    if(frt(y)==x&f[y]==x&&!ls(y))
        f[y]=rs(x)=0,pu(x);
}
signed main(){
    in(n,q);
    int x,y,c;char opt;
    for(int i=1;i<=n;++i)mul[i]=1,siz[i]=1,v[i]=1;
    for(int i=2;i<=n;++i)in(x,y),link(x,y);
    while(q--){
        in(opt,x,y);
        if(opt=='+')
            in(c),sl(x,y),
            s[y]=(s[y]+c*siz[y]%P)%P,v[y]=(v[y]+c)%P,
            add[y]=(add[y]+c)%P;
        if(opt=='-')cut(x,y),in(x,y),link(x,y);
        if(opt=='*'){
            in(c),sl(x,y),
            s[y]=s[y]*c%P,v[y]=v[y]*c%P;
            add[y]=add[y]*c%P,
            mul[y]=mul[y]*c%P;
        }
        if(opt=='/')sl(x,y),out(s[y],ln);
    }
    flush();
}
```
