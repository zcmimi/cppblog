---
author: zc
avatar: null
categories:
- - 刷题记录
commnet: 1
date: 2019-12-21 19:47
html: '<details><summary>查看原题</summary><div id=''from''></div><p><button onclick="document.getElementById(''from'').innerHTML=''<iframe
  src=&quot;https://www.luogu.com.cn/problem/CF52C&quot; width=100% height=800px style=&quot;border:
  none;&quot;><iframe>''" class=''mdui-btn mdui-btn-raised mdui-ripple''>点击加载</button><a
  class=''mdui-btn mdui-btn-raised mdui-ripple'' href="https://www.luogu.com.cn/problem/CF52C"
  target=''_blank''>点击跳转</a><p></details>'
permalink: LG CF52C Circular-RMQ
tags:
- 线段树
thumbnail: null
title: LG CF52C Circular-RMQ
top: 0
---
线段树裸题
```cpp
#include<bits/stdc++.h>
#define int ll
namespace ZDY{
    #pragma GCC optimize(3)
    #define il __inline__ __attribute__ ((always_inline))
    #define rg register
    #define ll long long
    #define ull unsigned long long
    #define db double
    #define sht short
    #define MB template <class T>il
    #define Fur(i,x,y) for(int i(x);i<=y;++i)
    #define Fdr(i,x,y) for(int i(x);i>=y;--i)
    #define fl(i,x) for(int i(head[x]),to;to=e[i].to,i;i=e[i].nxt)
    #define clr(x,y) memset(x,y,sizeof(x))
    #define cpy(x,y) memcpy(x,y,sizeof(x))
    #define fin(s) freopen(s".in","r",stdin)
    #define fout(s) freopen(s".out","w",stdout)
    #define fcin ios::sync_with_stdio(false)
    #define l2(n) ((int)(log2(n)))
    #define inf 2122219134
    MB T ABS(T x){return x>0?x:-x;}
    MB T MAX(T x,T y){return x>y?x:y;}
    MB T MIN(T x,T y){return x<y?x:y;}
    MB T GCD(T x,T y){return y?GCD(y,x%y):x;}
    MB void SWAP(T &x,T &y){T t=x;x=y;y=t;}
}using namespace ZDY;using namespace std;
namespace IO{
    const int str=1<<20;
    //in
    static char in_buf[str],*in_s,*in_t;
    bool __=0;
    il char gc(){return (in_s==in_t)&&(in_t=(in_s=in_buf)+fread(in_buf,1,str,stdin)),in_s==in_t?EOF:*in_s++;}
    template<typename T>
    il int in(T &x){
        if(__)return 0;
        rg char c=gc();
        bool f=0;
        while(c!=EOF&&(c<'0'||c>'9'))f^=(c=='-'),c=gc();
        if(c==EOF){__=1;return 0;}
        x=0;
        while(c!=EOF&&'0'<=c&&c<='9')x=x*10+c-48,c=gc();
        if(c==EOF)__=1;
        if(f)x=-x;
        if(c==' ')return 1;
        return 0;
    }
    template<typename T,typename ... arr>
    il void in(T &x,arr & ... y){in(x),in(y...);}

    //out
    const char ln='\n';
    static char out_buf[str],*out_s=out_buf,*out_t=out_buf+str;
    il void flush(){fwrite(out_buf,1,out_s-out_buf,stdout);out_s=out_buf;}
    il void pt(char c){(out_s==out_t)?(fwrite(out_s=out_buf,1,str,stdout),*out_s++=c):(*out_s++=c);}
    template<typename T>
    il void out(T x){
        if(!x){pt('0');return;}
        if(x<0)pt('-'),x=-x;
        char a[60],t=0;
        while(x)a[t++]=x%10,x/= 10;
        while(t--)pt(a[t]+'0');
    }
}using namespace IO;
#define N 200011
#define ls rt<<1
#define rs rt<<1|1
#define pu s[rt]=MIN(s[ls],s[rs]);
int n,s[N<<2],laz[N<<2];
void build(int l,int r,int rt){
    if(l==r){
        in(s[rt]);
        return;
    }
    int m=(l+r)>>1;
    build(l,m,ls);build(m+1,r,rs);
    pu;
}
il void pd(int rt){
    if(laz[rt]){
        laz[ls]+=laz[rt];laz[rs]+=laz[rt];
        s[ls]+=laz[rt];s[rs]+=laz[rt];
        laz[rt]=0;
    }
}
void upd(int L,int R,int v,int l,int r,int rt){
    if(L<=l&&r<=R){
        s[rt]+=v;
        laz[rt]+=v;
        return;
    }
    int m=(l+r)>>1;
    pd(rt);
    if(L<=m)upd(L,R,v,l,m,ls);
    if(R>m)upd(L,R,v,m+1,r,rs);
    pu;
}
int ask(int L,int R,int l,int r,int rt){
    if(L<=l&&r<=R)return s[rt];
    int m=(l+r)>>1,ans=inf;
    pd(rt);
    if(L<=m)ans=ask(L,R,l,m,ls);
    if(R>m)ans=MIN(ans,ask(L,R,m+1,r,rs));
    return ans;
}
signed main(){
    in(n);
    build(1,n,1);
    int q,l,r,v,ans;
    in(q);
    while(q--){
        in(l);
        bool ff=0;
        ff=in(r);
        ++l,++r;

        if(ff){
            in(v);
            if(l<=r)upd(l,r,v,1,n,1);
            else upd(l,n,v,1,n,1),upd(1,r,v,1,n,1);
        }
        else{
            if(l<=r)ans=ask(l,r,1,n,1);
            else ans=MIN(ask(l,n,1,n,1),ask(1,r,1,n,1));
            out(ans);pt('\n');
        }
    }
    flush();
}
```
