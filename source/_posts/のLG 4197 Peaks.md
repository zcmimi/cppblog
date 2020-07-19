---
author: zc
avatar: null
categories:
- - "\u5237\u9898\u8BB0\u5F55"
commnet: 1
date: 2019-12-31 11:31
html: "<details><summary>\u67E5\u770B\u539F\u9898</summary><div id='from'></div><p><button\
  \ onclick=\"document.getElementById('from').innerHTML='<iframe src=&quot;https://www.luogu.com.cn/problem/P4197&quot;\
  \ width=100% height=800px style=&quot;border: none;&quot;><iframe>'\" class='mdui-btn\
  \ mdui-btn-raised mdui-ripple'>\u70B9\u51FB\u52A0\u8F7D</button><a class='mdui-btn\
  \ mdui-btn-raised mdui-ripple' href=\"https://www.luogu.com.cn/problem/P4197\" target='_blank'>\u70B9\
  \u51FB\u8DF3\u8F6C</a><p></details>"
permalink: LG 4197 Peaks
tags:
- "kruskal\u91CD\u6784\u6811"
- "\u500D\u589E"
- "\u4E3B\u5E2D\u6811"
thumbnail: null
title: LG 4197 Peaks
top: 0
---
可以算是$kruskal$重构树的模板题

建完$kruskal$重构树,我们可以发现一个节点(新建的带点权的点)能走到的节点一定在它的子树中

那么我们可以用$dfs$序+主席树维护

> ## kruskal重构树
> 
> 我们回想一下$kruskal$生成最小生成树的过程：
> 
> 先将边按边权从小到大排序,然后依次加入
> 
> 如果$x,y$已经联通,则跳过这条边
> 
> 否则连接$x,y$
> 
> $kruskal$重构树是在$kruskal$生成最小生成树的,
> 
> 连接$x,y$时,将边权变成一个新的节点$t$权值为边权,然后连边> $t\rightarrow x,t\rightarrow y$
> 
> 代码：
> 
> ```cpp
> void kruskal(){
>     int x,y,tt=n;
>     sort(E+1,E+m+1);//将边排序
>     Fur(i,1,n)fa[i]=i;
>     Fur(i,1,m){
>         x=gf(E[i].x),y=gf(E[i].y);
>         if(x==y)continue;//如果已经联通则跳过
>         ne[++tt]=E[i].w;//点权赋值为边权
>         fa[x]=fa[y]=fa[tt]=tt;
>         f[0][x]=f[0][y]=tt;
>         //维护并查集
>         add(tt,x);add(tt,y);//连边t→x,t→y
>     }
> }
> ```
> 
> $kruskal$重构树还有很多有意思的性质
> 
> 1. 是一个二叉树
> 2. **如果是按最小生成树建立的话是一个大根堆**
> 3. 任意两个点路径上边权的最大值为它们的LCA的点权
> 4. 重构树中代表原树中的点的节点全是叶子节点,其余节点都代表了一条边的边权。

给出重构后的图(帮助理解)：

![](https://cdn.luogu.org/upload/pic/67842.png)

(红色的是原来的节点)

可以倍增求出最远的满足要求的祖先
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
#define N 200011
int n,m,q,SZ=0,rt[N];
struct node{
    int v,p;
    il bool operator<(node x){return v<x.v;}
}b[N];
int a[N],c[N];
struct link{
    int x,y,w;
    il bool operator<(link x){return w<x.w;}
}E[500011];
void init(){
    in(n,m,q);
    Fur(i,1,n)in(b[i].v),b[i].p=i;
    sort(b+1,b+n+1);
    b[0].v=-inf;
    sort(b+1,b+n+1);
    Fur(i,1,n){
        SZ+=(b[i].v!=b[i-1].v);
        c[a[b[i].p]=SZ]=b[i].v;
    }
    Fur(i,1,m)in(E[i].x,E[i].y,E[i].w);
}
int fa[N],f[21][N];
int gf(int x){return (x==fa[x])?x:(fa[x]=gf(fa[x]));}
struct tree{
    int s[N*20],sz=0,ls[N*20],rs[N*20];
    void build(int l,int r,int &x){
        s[x=++sz]=0;
        if(l==r)return;
        int m=(l+r)>>1;
        build(l,m,ls[x]);
        build(m+1,r,rs[x]);
    }
    void ins(int l,int r,int v,int &x,int pre){
        x=++sz;
        s[x]=s[pre]+1;
        ls[x]=ls[pre];
        rs[x]=rs[pre];
        if(l==r)return;
        int m=(l+r)>>1;
        if(v<=m)ins(l,m,v,ls[x],ls[pre]);
        else ins(m+1,r,v,rs[x],rs[pre]);
    }
    int ask(int l,int r,int k,int x,int y){
        if(l==r)return l;
        int m=(l+r)>>1,sum=s[rs[y]]-s[rs[x]];
        if(k<=sum)return ask(m+1,r,k,rs[x],rs[y]);
        else return ask(l,m,k-sum,ls[x],ls[y]);
    }
}T;
int cnt=0,head[N];
struct edge{
    int to,nxt;
}e[N*2];
il void add(int x,int y){e[++cnt].to=y;e[cnt].nxt=head[x];head[x]=cnt;}
int L[N],R[N],dfn=0;
void dfs(int x){
    Fur(i,1,20)f[i][x]=f[i-1][f[i-1][x]];
    L[x]=dfn;
    if(!head[x]){
        L[x]=++dfn;
        T.ins(1,SZ,a[x],rt[dfn],rt[dfn-1]);
        R[x]=dfn;
        return;
    }
    fl(i,x)dfs(to);
    R[x]=dfn;
}
int ne[N];
void kruskal(){
    int x,y,tt=n;
    sort(E+1,E+m+1);
    Fur(i,1,n)fa[i]=i;
    Fur(i,1,m){
        x=gf(E[i].x),y=gf(E[i].y);
        if(x==y)continue;
        ne[++tt]=E[i].w;
        fa[x]=fa[y]=fa[tt]=tt;
        f[0][x]=f[0][y]=tt;
        add(tt,x);add(tt,y);
    }
    T.build(1,SZ,rt[0]);
    dfs(tt);
}
void solve(){
    int x,w,k;
    while(q--){
        in(x,w,k);
        Fdr(i,20,0)if(f[i][x]&&ne[f[i][x]]<=w)x=f[i][x];
        if(R[x]-L[x]<k)out("-1\n");
        else out(c[T.ask(1,SZ,k,rt[L[x]],rt[R[x]])],ln);
    }
}
int main(){
    init();
    kruskal();
    solve();
    flush();
    return 0;
}
```
