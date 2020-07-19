---
author: zc
avatar: null
categories:
- - "\u5237\u9898\u8BB0\u5F55"
commnet: 1
date: 2020-04-10 20:51
html: "<details><summary>\u67E5\u770B\u539F\u9898</summary><div id='from'></div><p><button\
  \ onclick=\"document.getElementById('from').innerHTML='<iframe src=&quot;https://www.luogu.com.cn/problem/SP16549&quot;\
  \ width=100% height=800px style=&quot;border: none;&quot;><iframe>'\" class='mdui-btn\
  \ mdui-btn-raised mdui-ripple'>\u70B9\u51FB\u52A0\u8F7D</button><a class='mdui-btn\
  \ mdui-btn-raised mdui-ripple' href=\"https://www.luogu.com.cn/problem/SP16549\"\
  \ target='_blank'>\u70B9\u51FB\u8DF3\u8F6C</a><p></details>"
permalink: LG SP16549 QTREE6 - Query on a tree VI
tags:
- lct
thumbnail: null
title: LG SP16549 QTREE6 - Query on a tree VI
top: 0
---
## 解法一

化边为点

每个点的父边赋予该点的颜色。我们需要两个LCT,每种对应一个颜色。一条边只有在对应颜色的LCT中才会被连上。

接着可以发现,修改一个点的颜色,只需要在原来颜色对应`LCT`中断开父边,在新颜色`LCT`中连接父边,就可以维护同色连通块了

查询的时候只要找到$x$所在`splay`的根,右子树大小就是答案(相当于边的数目,根的深度最浅,只有右子树)

注意: 1节点是没有父亲的,不过为了模型的建立,要有父边,于是需要加一个虚点,让1的父亲指向它连边

手动模拟一下应该可以懂

```cpp
#include<bits/stdc++.h>
#pragma GCC optimize(3)
#define il __inline__ __attribute__ ((always_inline))
namespace IO{const int str=1<<20;static char in_buf[str],*in_s,*in_t;bool __=0;il char gc(){return (in_s==in_t)&&(in_t=(in_s=in_buf)+fread(in_buf,1,str,stdin)),in_s==in_t?EOF:*in_s++;}il void in(char &ch){if(__)return;char c;while((c=gc())!=EOF&&isspace(c));if(c==EOF)__=1;else ch=c;}il void in(char *ch){*ch='\0';if(__)return;char c;while((c=gc())!=EOF&&isspace(c));if(c==EOF){__=1;return;}*ch=c;ch++;while((c=gc())!=EOF&&!isspace(c))*ch=c,ch++;if(c==EOF)__=1;*ch='\0';}template<typename T>il void in(T &x){if(__)return;char c=gc();bool f=0;while(c!=EOF&&(c<'0'||c>'9'))f^=(c=='-'),c=gc();if(c==EOF){__=1;return;}x=0;while(c!=EOF&&'0'<=c&&c<='9')x=x*10+c-48,c=gc();if(c==EOF)__=1;if(f)x=-x;}template<typename T,typename ... arr>il void in(T &x,arr & ... y){in(x),in(y...);}const char ln='\n';static char out_buf[str],*out_s=out_buf,*out_t=out_buf+str;il void flush(){fwrite(out_buf,1,out_s-out_buf,stdout);out_s=out_buf;}il void pt(char c){(out_s==out_t)?(fwrite(out_s=out_buf,1,str,stdout),*out_s++=c):(*out_s++=c);}il void out(const char* s){while(*s)pt(*s++);}il void out(char* s){while(*s)pt(*s++);}il void out(char c){pt(c);}template<typename T>il void out(T x){if(!x){pt('0');return;}if(x<0)pt('-'),x=-x;char a[50],t=0;while(x)a[t++]=x%10,x/= 10;while(t--)pt(a[t]+'0');}template<typename T,typename ... arr>il void out(T x,arr & ... y){out(x),out(y...);}}using namespace IO;
const int N=100011;
int n,q,cnt,head[N],fa[N],v[N];
bool col[N];
struct edge{int to,nxt;}e[N<<1];
il void add(int x,int y){e[++cnt].to=y;e[cnt].nxt=head[x];head[x]=cnt;}
struct LCT{
    int s[N],c[2][N],s2[N],f[N];
    il void build(){for(int i=1;i<=n+1;++i)s[i]=1;}
    #define ls c[0][x]
    #define rs c[1][x]
    il void pu(int x){s[x]=s[ls]+s[rs]+1+s2[x];}
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
    il void access(int x){for(int y=0;x;x=f[y=x])splay(x),s2[x]+=s[rs]-s[rs=y],pu(x);}
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
    T[0].link(x);
}
int main(){
    in(n);
    T[0].build(),T[1].build();
    int x,y;
    for(int i=1;i<n;++i)in(x,y),add(x,y),add(y,x);
    fa[1]=n+1;dfs(1);
    in(q);
    while(q--){
        in(y,x);
        if(y)T[col[x]].cut(x),T[col[x]^=1].link(x);
        else out(T[col[x]].ask(x),ln);
    }
    flush();
}
```

## 解法2

类似QTREE5的做法

记录实链顶端和底端的答案

要仔细考虑`push up`

```cpp
#include<bits/stdc++.h>
const int N=100011;
int n,q,s[2][N],c[2][N],f[N],sl[N],sr[N],col[N],tc[N],lc[N],rc[N];
#define ls c[0][x]
#define rs c[1][x]
void pu(int x){
    sl[x]=sl[ls]+(((tc[ls]!=2&&col[x]==tc[ls])||!ls)?s[col[x]][x]+1+(lc[rs]==col[x]?sl[rs]:0):0);
    sr[x]=sr[rs]+(((tc[rs]!=2&&col[x]==tc[rs])||!rs)?s[col[x]][x]+1+(rc[ls]==col[x]?sr[ls]:0):0);
    lc[x]=ls?lc[ls]:col[x];
    rc[x]=rs?rc[rs]:col[x];
    if(tc[ls]==2||tc[rs]==2||(ls&&tc[ls]!=col[x])||(rs&&tc[rs]!=col[x]))tc[x]=2;
    else tc[x]=col[x];
}
int g(int x){return c[1][f[x]]==x;}
int nrt(int x){return c[0][f[x]]==x||c[1][f[x]]==x;}
void rotate(int x){
    int y=f[x],z=f[y],l=g(x),r=!l,w=c[r][x];
    if(nrt(y))c[g(y)][z]=x;
    c[r][x]=y,c[l][y]=w;
    if(w)f[w]=y;
    f[x]=z,f[y]=x;
    pu(y),pu(x);
}
void splay(int x){
    for(;nrt(x);rotate(x))if(nrt(f[x]))
        rotate(g(x)^g(f[x])?x:f[x]);
}
void access(int x){
    for(int y=0;x;x=f[y=x]){
        splay(x);
        s[lc[rs]][x]+=sl[rs];
        rs=y;
        s[lc[y]][x]-=sl[y];
        pu(x);
    }
}
int cnt=0,head[N];
struct edge{int to,nxt;}e[N<<1];
void add(int x,int y){e[++cnt].to=y;e[cnt].nxt=head[x];head[x]=cnt;}
void dfs(int x,int fa){
    for(int i=head[x],to;to=e[i].to,i;i=e[i].nxt)
    if(to!=fa){
        dfs(to,x);
        f[to]=x;s[lc[to]][x]+=sl[to];
    }
    pu(x);
}
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;++i)sl[i]=sr[i]=1;
    int x,y;
    for(int i=1;i<n;++i){
        scanf("%d%d",&x,&y);
        add(x,y),add(y,x);
    }
    dfs(1,0);
    scanf("%d",&q);
    while(q--){
        scanf("%d%d",&y,&x);
        access(x),splay(x);
        if(y)col[x]^=1,pu(x);
        else printf("%d\n",sr[x]);
    }
}
```
