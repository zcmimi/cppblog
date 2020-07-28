---
author: zc
avatar: null
categories:
- - 刷题记录
commnet: 1
date: 2019-12-31 11:31
html: '<details><summary>查看原题</summary><div id=''from''></div><p><button onclick="document.getElementById(''from'').innerHTML=''<iframe
  src=&quot;http://www.lydsy.com/JudgeOnline/problem.php?id=3732&quot; width=100%
  height=800px style=&quot;border: none;&quot;><iframe>''" class=''mdui-btn mdui-btn-raised
  mdui-ripple''>点击加载</button><a class=''mdui-btn mdui-btn-raised mdui-ripple'' href="http://www.lydsy.com/JudgeOnline/problem.php?id=3732"
  target=''_blank''>点击跳转</a><p></details>'
permalink: BZ 3732 Network
tags:
- kruskal重构树
- rmq
- lca
thumbnail: null
title: BZ 3732 Network
top: 0
---
kruskal重构树模板
```cpp
#include<bits/stdc++.h>
namespace ZDY{
    #pragma GCC optimize(3)
    #define il __inline__ __attribute__ ((always_inline))
    #define register
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
    il void in(T &x){
        if(__)return;
        char c=gc();
        bool f=0;
        while(c!=EOF&&(c<'0'||c>'9'))f^=(c=='-'),c=gc();
        if(c==EOF){__=1;return;}
        x=0;
        while(c!=EOF&&'0'<=c&&c<='9')x=x*10+c-48,c=gc();
        if(c==EOF)__=1;
        if(f)x=-x;
    }

    //out
    const char ln='\n';
    static char out_buf[str],*out_s=out_buf,*out_t=out_buf+str;
    il void flush(){fwrite(out_buf,1,out_s-out_buf,stdout);out_s=out_buf;}
    il void pt(char c){(out_s==out_t)?(fwrite(out_s=out_buf,1,str,stdout),*out_s++=c):(*out_s++=c);}
    template<typename T>
    il void out(T x){
        if(!x){pt('0');return;}
        if(x<0)pt('-'),x=-x;
        char a[50],t=0;
        while(x)a[t++]=x%10,x/= 10;
        while(t--)pt(a[t]+'0');
    }
}using namespace IO;
#define N 30011
int n,m,q,cnt=0,head[N],f[N],ne[N];
struct edge{
    int to,nxt;
}e[N*2];
il void add(int x,int y){e[++cnt].to=y;e[cnt].nxt=head[x];head[x]=cnt;}
struct link{
    int x,y,w;
    il bool operator<(link x){return w<x.w;}
}E[N];
int gf(int x){return (x==f[x])?x:(f[x]=gf(f[x]));}
int s[16][N];
il void st(){
    int sz=l2(n<<1);
    Fur(k,1,sz)
        Fur(i,1,(n<<1)-(1<<k)+1)
        s[k][i]=MAX(s[k-1][i],s[k-1][i+(1<<(k-1))]);
}
il int ask(int l,int r){
    int k=l2(r-l+1);
    return MAX(s[k][l],s[k][r-(1<<k)+1]);
}
int top[N],d[N],siz[N],id[N],sz=0;
void dfs(int x){
    siz[x]=1;
    fl(i,x){
        d[to]=d[x]+1;
        f[to]=x;
        dfs(to);
        siz[x]+=siz[to];
    }
}
void bt(int x,int tp){
    top[x]=tp;id[x]=++sz;
    s[0][sz]=ne[x];
    int k=0;
    fl(i,x)if(siz[to]>siz[k])k=to;
    if(!k)return;bt(k,tp);
    fl(i,x)if(to!=k)bt(to,to);
}
il int fh(int x,int y){
    int ans=0;
    while(top[x]!=top[y]){
        if(d[top[x]]<d[top[y]])SWAP(x,y);
        ans=MAX(ans,ask(id[top[x]],id[x]));x=f[top[x]];
    }
    if(id[x]>id[y])SWAP(x,y);
    return MAX(ans,ask(id[x],id[y]));
}
int main(){
    in(n),in(m),in(q);
    int x,y,w,t=n;
    Fur(i,1,m)in(E[i].x),in(E[i].y),in(E[i].w);
    sort(E+1,E+m+1);
    Fur(i,1,n)f[i]=i;
    Fur(i,1,m){
        x=gf(E[i].x),y=gf(E[i].y);
        if(x==y)continue;
        ne[++t]=E[i].w;
        f[x]=f[y]=f[t]=t;
        add(t,x),add(t,y);
    }
    dfs(t);
    bt(t,t);
    st();
    while(q--)
        in(x),in(y),
        out(fh(x,y)),pt(ln);
    flush();
}
```
