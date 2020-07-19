---
author: zc
avatar: null
categories:
- - "\u5237\u9898\u8BB0\u5F55"
commnet: 1
date: 2020-01-18 22:40
html: "<details><summary>\u67E5\u770B\u539F\u9898</summary><div id='from'></div><p><button\
  \ onclick=\"document.getElementById('from').innerHTML='<iframe src=&quot;https://www.luogu.com.cn/problem/SP10628&quot;\
  \ width=100% height=800px style=&quot;border: none;&quot;><iframe>'\" class='mdui-btn\
  \ mdui-btn-raised mdui-ripple'>\u70B9\u51FB\u52A0\u8F7D</button><a class='mdui-btn\
  \ mdui-btn-raised mdui-ripple' href=\"https://www.luogu.com.cn/problem/SP10628\"\
  \ target='_blank'>\u70B9\u51FB\u8DF3\u8F6C</a><p></details>"
permalink: LG SP10628 COT Count-on-a-tree
tags:
- "\u6811\u94FE\u5256\u5206"
- "\u4E3B\u5E2D\u6811"
thumbnail: null
title: LG SP10628 COT Count-on-a-tree
top: 0
---
模板
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
namespace IO{const int str=1<<20;static char in_buf[str],*in_s,*in_t;bool __=0;il char gc(){return (in_s==in_t)&&(in_t=(in_s=in_buf)+fread(in_buf,1,str,stdin)),in_s==in_t?EOF:*in_s++;}il void in(string &ch){ch.clear();if(__)return;char c;while((c=gc())!=EOF&&isspace(c));if(c==EOF){__=1;return;}ch+=c;while((c=gc())!=EOF&&!isspace(c))ch+=c;if(c==EOF)__=1;}il void in(char &ch){if(__)return;char c;while((c=gc())!=EOF&&isspace(c));if(c==EOF)__=1;else ch=c;}il void in(char *ch){*ch='\0';if(__)return;char c;while((c=gc())!=EOF&&isspace(c));if(c==EOF){__=1;return;}*ch=c;ch++;while((c=gc())!=EOF&&!isspace(c))*ch=c,ch++;if(c==EOF)__=1;*ch='\0';}template<typename T>il void in(T &x){if(__)return;char c=gc();bool f=0;while(c!=EOF&&(c<'0'||c>'9'))f^=(c=='-'),c=gc();if(c==EOF){__=1;return;}x=0;while(c!=EOF&&'0'<=c&&c<='9')x=x*10+c-48,c=gc();if(c==EOF)__=1;if(f)x=-x;}template<typename T,typename ... arr>il void in(T &x,arr & ... y){in(x),in(y...);}const char ln='\n';static char out_buf[str],*out_s=out_buf,*out_t=out_buf+str;il void flush(){fwrite(out_buf,1,out_s-out_buf,stdout);out_s=out_buf;}il void pt(char c){(out_s==out_t)?(fwrite(out_s=out_buf,1,str,stdout),*out_s++=c):(*out_s++=c);}il void out(const char* s){while(*s)pt(*s++);}il void out(char* s){while(*s)pt(*s++);}il void out(char c){pt(c);}il void out(string s){for(int i=0;s[i];i++)pt(s[i]);}template<typename T>il void out(T x){if(!x){pt('0');return;}if(x<0)pt('-'),x=-x;char a[50],t=0;while(x)a[t++]=x%10,x/= 10;while(t--)pt(a[t]+'0');}template<typename T,typename ... arr>il void out(T x,arr & ... y){out(x),out(y...);}}using namespace IO;
#define N 100011
int n,cnt=0,head[N],val[N];
struct edge{
    int to,nxt;
}e[N<<1];
il void add(int x,int y){
    e[++cnt].to=y;e[cnt].nxt=head[x];head[x]=cnt;
}
int RT[N*20],s[N*20],sz=0,ls[N*20],rs[N*20];
void ins(int l,int r,int p,int &x,int pre){
    s[x=++sz]=s[pre]+1;
    if(l==r)return;
    ls[x]=ls[pre];
    rs[x]=rs[pre];
    int m=(l+r)>>1;
    if(p<=m)ins(l,m,p,ls[x],ls[pre]);
    else ins(m+1,r,p,rs[x],rs[pre]);
}
int ask(int k,int l,int r,int x,int y,int lca,int ff){
    if(l==r)return l;
    int m=(l+r)>>1,sum=s[ls[x]]+s[ls[y]]-s[ls[lca]]-s[ls[ff]];
    if(sum>=k)return ask(k,l,m,ls[x],ls[y],ls[lca],ls[ff]);
    else return ask(k-sum,m+1,r,rs[x],rs[y],rs[lca],rs[ff]);
}
int top[N],f[N],d[N],siz[N];
void dfs(int x){
    siz[x]=1;
    fl(i,x)if(to!=f[x]){
        d[to]=d[x]+1;
        f[to]=x;
        dfs(to);
        siz[x]+=siz[to];
    }
}
void bt(int x,int tp){
    top[x]=tp;ins(1,n,val[x],RT[x],RT[f[x]]);
    int k=0;
    fl(i,x)if(to!=f[x]&&siz[to]>siz[k])k=to;
    if(!k)return;bt(k,tp);
    fl(i,x)if(!top[to])bt(to,to);
}
int glca(int x,int y){
    while(top[x]!=top[y]){
        if(d[top[x]]<d[top[y]])SWAP(x,y);
        x=f[top[x]];
    }
    return d[x]<d[y]?x:y;
}
struct node{
    int v,p;
    bool operator<(node x)const{
        return v<x.v;
    }
}a[N];
int old[N];
int main(){
    int x,y,k,q;
    in(n,q);
    Fur(i,1,n)in(a[i].v),a[i].p=i;
    sort(a+1,a+n+1);
    int tt=0;
    Fur(i,1,n)old[val[a[i].p]=(tt+=a[i].v!=a[i-1].v)]=a[i].v;
    Fur(i,1,n-1)in(x,y),add(x,y),add(y,x);
    dfs(1);bt(1,1);
    while(q--){
        in(x,y,k);
        int lca=glca(x,y);
        out(old[ask(k,1,n,RT[x],RT[y],RT[lca],RT[f[lca]])],ln);
    }
    flush();
}
```
