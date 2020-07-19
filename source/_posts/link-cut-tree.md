---
title: link-cut tree 
date: 2020-03-29 16:58
author: 
avatar:
tags: 
 - 数据结构
 - 树论

categories:
 - [算法,数据结构]
 - [note]

thumbnail: 
top: 0 
comment: 1
---

`link-cut tree`是一个挺复杂的东西,本文主要用于复习巩固`link-cut tree`

> 推荐: 
> 
> - https://www.cnblogs.com/flashhu/p/8324551.html
> 
> - https://oi-wiki.org/ds/lct/

## 简介

`link-cut tree`是一种数据结构,我们用它来解决动态树问题。

> **动态树问题**
> 
> 维护一个森林, 支持删除某条边,加⼊某条边,并保证加边,删边之后仍是森林。我们要维护这个森林的一些信息。
> 
> 一般的操作有两点连通性,两点路径权值和(或最值等),连接两点和切断某条边、修改信息等。

`link-cut tree`简称`LCT`,但它不叫动态树,动态树是指一类问题。

`Splay Tree`是`LCT`的基础(使用`Splay`维护森林),但是`LCT`⽤的`Splay Tree`和普通的`Splay`在细节处不太一样(进行了一些扩展)。

## 概念

`LCT`基于实链剖分

> 将向某一个儿子的连边划分为实边,连向其他子树的边划分为虚边。
> 
> 虚边、实边可动态变化
> 
> 虚边：儿子认父,父不认子
>
> 实边：儿子认父,父也认子

`LCT`支持: 

1. 查询、修改链上的信息(最值,总和等)
   
2. 换根
   
3. 动态连边、删边

`LCT`的基本操作复杂度均摊为$\log n$

但是常数较大,在可以使用树链剖分的情况下还是使用树链剖分比较好

## 性质

1. 每一个`Splay`(森林)维护的是**一条从上到下按在原树中深度严格递增的路径,且中序遍历Splay得到的每个点的深度序列严格递增**。
   
2. 每个节点包含且仅包含于一个`Splay`(森林)中 ~~(这不是废话吗？)~~

## 操作

以下的`ls(x)`等同于`c[0][x]`,表示左儿子,`rs(x)`等同于`c[1][x]`,表示左儿子

### Push up

```cpp
void pu(int x){
    siz[x]=siz[ls(x)]+siz[rs(x)]+1;
}
```

### Push rev

```cpp
void pr(int x){
    swap(ls(x),rs(x));
    rev[x]^=1;
}
```

### Push down

```cpp
void pd(int x){
    if(rev[x]){
        if(ls(x))pr(ls(x));
        if(rs(x))pr(rs(x));
        rev[x]=0;
    }
}
```

### rotate & splay

`LCT`中的`splay`和普通的`splay`有一定区别

不会`splay`的请先自行了解

```cpp
void g(int x){return rs(f[x])==x;}
void rotate(int x){
    int y=f[x],z=f[y],l=g(x),r=!l,w=c[r][x];
    if(nrt(y))c[g(y)][z]=x;
    c[r][x]=y;c[l][y]=w;
    if(w)f[w]=y;
    f[x]=z,f[y]=x;
    pu(y),pu(x);
}
int st[N];
void splay(int x){
    int z=0,y=st[++z]=x;
    while(nrt(y))st[++z]=y=f[y];
    while(z)pd(st[z--]);
    for(;nrt(x);rotate(x))
        if(nrt(f[x]))turn(g(x)^g(f[x])?x:f[x]);
}
```

### Access

`LCT`的核心操作

`access`的四步操作：

1. 把当前节点转到根
2. 把儿子换成上一次操作的节点(如果没有上一次就是没有)
3. 更新当前点的信息。
4. 把当前点换成当前点的父亲,继续操作

```cpp
void access(int x){
    for(int y=0;x;x=f[y=x])
        splay(x),rs(x)=y,pu(x);
}
```

### Make root

仅次于`Access`的核心操作

```cpp
void mrt(int x){
    access(x),splay(x),pr(x);
}
```

当连接$x$到根,并把$x$旋转到根后

$x$成为树根,$x$变为树上深度最小的点,$x$到原树根的路径上的边全部反向

那么翻转`access(x)`后形成的$x$到原树根的链所在的`splay`即可

### Find root

`access(x),splay(x)`后,原来的根变成$x$所在`splay`里深度最小的那个,那么一直往左儿子走就可以找到原来的根了(记得`push down`)

注意最后要把原来的根`splay`上去,保证复杂度

```cpp
void frt(int x){
    for(access(x),splay(x);ls(x);pd(x),x=ls(x));
    splay(x);return x;
}
```

### Link

直接看代码就可以懂了

```cpp
void link(int x,int y){
    mrt(x);
    if(frt(y)!=x)f[x]=y;
}
```

### Split

直接将$x$到$y$的路径提出来,为了方便我们将$y$作为该`splay`的根

```cpp
void sl(int x,int y){
    mrt(x),access(y),splay(y);
}
```

### Cut

若存在边连接$x,y$

将根换为$x$后,$x$的深度最小,其次是$y$

`find root`之后$x$被旋转到了根节点

$y$为$x$的右儿子且$y$没有左儿子

判断完毕就是可以断开$x,y$之间的关系并更新$x$了

```cpp
void cut(int x,int y){
    mrt(x);
    if(frt(y)==x&&f[y]==x&&!ls(y))f[y]=rs(x)=0,pu(x);
}
```

[LG 3690 【模板】link-cut tree （动态树）](https://www.luogu.com.cn/problem/P3690)

这题就是标准的模板了

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

## 进阶

### 维护树链信息

[LG 1501 \[国家集训队\]Tree II](https://www.luogu.com.cn/problem/P1501)

经典的`link-cut tree`维护树链信息,区间加区间乘区间查询

关键在于打标记和下推,记得先下推乘法再下推加法

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

### 维护双连通分量

[LG 2542 \[AHOI2005\]航线规划](https://www.luogu.com.cn/problem/P2542)

首先看到这种题我们可以考虑倒序添加

假设每个点代表一个双连通分量,那么两个点之间的关键路径数就是链长-1

可以用`LCT`+并查集来维护

连接一条边:

1. 两端在同一个双连通分量中: 什么都不用干
   
2. 两端还未连通: 直接`link`

3. 两端已经联通: 缩点
   
   将连接两端的路径提取出来,合并这些点

```cpp
int BL(int x){return bl[x]==x?x:(bl[x]=BL(bl[x]));}//并查集
void set(int x,int y){if(x)bl[x]=y,set(ls(x),x),set(rs(x),x);}
void mg(int x,int y){
    if(x==y)return;//在同一个双连通分量
    mrt(x);
    if(frt(y)!=x){f[x]=y;return;}//未连通

    /*
    在find root的过程中已经access(y)提出了x到y的路径
    我们现在只需要把x的子树的并查集祖先都改成x,然后断开x与子树的连接即可
    */
    set(rs(x),x),rs(x)=0,pu(x);
}
void access(int x){
    /*
    缩点的时候x的子树指空了,我们需要在access的时候接回去

    这样原本连接链上其他节点的access后都会指向x了
    */
    for(int y=0;x;x=f[y=x]=BL(f[x]))
        splay(x),rs(x)=y,pu(x);
}
```

```cpp
#include<bits/stdc++.h>
#pragma GCC optimize(3)
#define il __inline__ __attribute__ ((always_inline))
namespace IO{const int str=1<<20;static char in_buf[str],*in_s,*in_t;bool __=0;il char gc(){return (in_s==in_t)&&(in_t=(in_s=in_buf)+fread(in_buf,1,str,stdin)),in_s==in_t?EOF:*in_s++;}il void in(char &ch){if(__)return;char c;while((c=gc())!=EOF&&isspace(c));if(c==EOF)__=1;else ch=c;}il void in(char *ch){*ch='\0';if(__)return;char c;while((c=gc())!=EOF&&isspace(c));if(c==EOF){__=1;return;}*ch=c;ch++;while((c=gc())!=EOF&&!isspace(c))*ch=c,ch++;if(c==EOF)__=1;*ch='\0';}template<typename T>il void in(T &x){if(__)return;char c=gc();bool f=0;while(c!=EOF&&(c<'0'||c>'9'))f^=(c=='-'),c=gc();if(c==EOF){__=1;return;}x=0;while(c!=EOF&&'0'<=c&&c<='9')x=x*10+c-48,c=gc();if(c==EOF)__=1;if(f)x=-x;}template<typename T,typename ... arr>il void in(T &x,arr & ... y){in(x),in(y...);}const char ln='\n';static char out_buf[str],*out_s=out_buf,*out_t=out_buf+str;il void flush(){fwrite(out_buf,1,out_s-out_buf,stdout);out_s=out_buf;}il void pt(char c){(out_s==out_t)?(fwrite(out_s=out_buf,1,str,stdout),*out_s++=c):(*out_s++=c);}il void out(const char* s){while(*s)pt(*s++);}il void out(char* s){while(*s)pt(*s++);}il void out(char c){pt(c);}template<typename T>il void out(T x){if(!x){pt('0');return;}if(x<0)pt('-'),x=-x;char a[50],t=0;while(x)a[t++]=x%10,x/= 10;while(t--)pt(a[t]+'0');}template<typename T,typename ... arr>il void out(T x,arr & ... y){out(x),out(y...);}}using namespace IO;
il void swap(int &x,int &y){x^=y,y^=x,x^=y;}
const int N=30011,M=100011;
int n,m,s[N],c[2][N],f[N],st[N],bl[N];
bool rev[N];
#define ls(x) c[0][x]
#define rs(x) c[1][x]
il void pu(int x){s[x]=s[ls(x)]+s[rs(x)]+1;}
il void pr(int x){swap(ls(x),rs(x));rev[x]^=1;}
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
    f[y]=x,f[x]=z;
    pu(y),pu(x);
}
il void splay(int x){
    int z=0,y=st[++z]=x;
    while(nrt(y))st[++z]=y=f[y];
    while(z)pd(st[z--]);
    for(;nrt(x);rotate(x))if(nrt(f[x]))
        rotate(g(x)^g(f[x])?x:f[x]);
}
int BL(int x){return bl[x]==x?x:(bl[x]=BL(bl[x]));}
il void access(int x){for(int y=0;x;x=f[y=x]=BL(f[x]))splay(x),rs(x)=y,pu(x);}
il void mrt(int x){access(x),splay(x),pr(x);}
il int frt(int x){
    for(access(x),splay(x);ls(x);pd(x),x=ls(x));
    splay(x);return x;
}
il void sl(int x,int y){mrt(x),access(y),splay(y);}
void set(int x,int y){if(x)bl[x]=y,set(ls(x),x),set(rs(x),x);}
il void mg(int x,int y){
    if(x==y)return;
    mrt(x);
    if(frt(y)!=x){f[x]=y;return;}
    set(rs(x),x),rs(x)=0,pu(x);
}
#include<bits/extc++.h>
using namespace __gnu_pbds;
gp_hash_table<int,bool>vis[N];
int X[M],Y[M],A[M],B[M],O[M],ans[M];
int main(){
    in(n,m);
    int c,x,y,q;
    for(int i=1;i<=n;++i)s[i]=1,bl[i]=i;
    for(int i=1;i<=m;++i){
        in(X[i],Y[i]);
        if(X[i]>Y[i])swap(X[i],Y[i]);
    }
    for(q=1;in(O[q]),~O[q];++q){
        in(x,y);
        if(x>y)swap(x,y);
        if(!O[q])vis[x][y]=1;
        A[q]=x,B[q]=y;
    }
    for(int i=1;i<=m;++i)if(!vis[X[i]][Y[i]])mg(BL(X[i]),BL(Y[i]));
    for(c=0,--q;q;--q){
        x=BL(A[q]),y=BL(B[q]);
        if(O[q])sl(x,y),ans[++c]=s[y]-1;
        else mg(x,y);
    }
    while(c)out(ans[c--],ln);
    flush();
}
```

[BZ 2959 长跑](http://www.lydsy.com/JudgeOnline/problem.php?id=2959)

和上一题有点像

缩点的时候顺便和并所有点的信息

```cpp
#include<bits/stdc++.h>
#define il __inline__ __attribute__ ((always_inline))
il int min(int x,int y){return x<y?x:y;}
il int max(int x,int y){return x>y?x:y;}
namespace IN{const int str=1<<20;static char in_buf[str],*in_s,*in_t;bool __=0;inline char gc(){return (in_s==in_t)&&(in_t=(in_s=in_buf)+fread(in_buf,1,str,stdin)),in_s==in_t?EOF:*in_s++;}template<typename T>inline void in(T &x){if(__)return;char c=gc();bool f=0;while(c!=EOF&&(c<'0'||c>'9'))f^=(c=='-'),c=gc();if(c==EOF){__=1;return;}x=0;while(c!=EOF&&'0'<=c&&c<='9')x=x*10+c-48,c=gc();if(c==EOF)__=1;if(f)x=-x;}template<typename T,typename ... arr>inline void in(T &x,arr & ... y){in(x),in(y...);}}using namespace IN;
namespace OUT{const char ln='\n';const int str=1<<20;static char out_buf[str],*out_s=out_buf,*out_t=out_buf+str;inline void flush(){fwrite(out_buf,1,out_s-out_buf,stdout);out_s=out_buf;}inline void pt(char c){(out_s==out_t)?(fwrite(out_s=out_buf,1,str,stdout),*out_s++=c):(*out_s++=c);}inline void out(char c){pt(c);}template<typename T>inline void out(T x){if(!x){pt('0');return;}if(x<0)pt('-'),x=-x;char a[50],t=0;while(x)a[t++]=x%10,x/= 10;while(t--)pt(a[t]+'0');}template<typename T,typename ... arr>inline void out(T x,arr & ... y){out(x),out(y...);}}using namespace OUT;
const int N=150011,inf=2122219134;
int n,q,s[N],f[N],c[2][N],v[N],bl[N],a[N];
bool rev[N];
int BL(int x){return bl[x]==x?x:(bl[x]=BL(bl[x]));}
#define ls c[0][x]
#define rs c[1][x]
il void pu(int x){s[x]=s[ls]+s[rs]+v[x];}
il void pr(int x){rev[x]^=1,ls^=rs,rs^=ls,ls^=rs;}
il void pd(int x){
    if(rev[x]){
        if(ls)pr(ls);
        if(rs)pr(rs);
        rev[x]=0;
    }
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
void pda(int x){if(nrt(x))pda(f[x]);pd(x);}
il void splay(int x){
    for(pda(x);nrt(x);rotate(x))if(nrt(f[x]))
        rotate(g(x)^g(f[x])?x:f[x]);
}
il void access(int x){
    for(int y=0;x;x=f[y=x]=BL(f[x]))
        splay(x),rs=y,pu(x);
}
il void mrt(int x){access(x),splay(x),pr(x);}
il int frt(int x){
    for(access(x),splay(x);ls;pd(x),x=ls);
    splay(x);return x;
}
int tmp;
void get(int x,int y){
    if(x)tmp+=v[x],bl[x]=y,get(ls,x),get(rs,x);
}
int main(){
    in(n,q);
    for(int i=1;i<=n;++i)in(a[i]),s[i]=v[i]=a[i],bl[i]=i;
    int opt,x,y;
    while(q--){
        in(opt,x,y);
        if(opt==1){
            x=BL(x),y=BL(y);
            if(x==y)continue;
            mrt(x);
            if(frt(y)!=x)f[x]=y;
            else tmp=0,get(rs,x),rs=0,v[x]+=tmp,pu(x);
        }
        if(opt==2){
            mrt(BL(x));
            v[BL(x)]+=y-a[x];
            s[BL(x)]+=y-a[x];
            a[x]=y;
        }
        if(opt==3){
            x=BL(x),y=BL(y);
            mrt(x);
            if(frt(y)!=x)out(-1,ln);
            else out(s[x],ln);
        }
    }
    flush();
}
```

### 维护边权(动态维护生成树)

`link-cut tree`不能直接维护边权

我们可以通过拆边,把边转化为点再向两端连边

可以通过这种方式用`LCT`**动态维护生成树**

> 注意: LCT上节点没有固定的父子关系,不能像树剖一样用点权记录边权

[LG 4234 最小差值生成树](https://www.luogu.com.cn/problem/P4234)

按边权从小到大排序后,依次添加边

问题转化为了: 

每次加边的时候,

如果两点为连通,则加边

否则在目前的生成树上找到边权最小的边, 并替换为新边

可以用`LCT`维护

```cpp
#include<bits/stdc++.h>
#pragma GCC optimize(3)
#define il __inline__ __attribute__ ((always_inline))
il int min(int x,int y){return x<y?x:y;}
namespace IN{const int str=1<<20;static char in_buf[str],*in_s,*in_t;bool __=0;inline char gc(){return (in_s==in_t)&&(in_t=(in_s=in_buf)+fread(in_buf,1,str,stdin)),in_s==in_t?EOF:*in_s++;}template<typename T>inline void in(T &x){if(__)return;char c=gc();bool f=0;while(c!=EOF&&(c<'0'||c>'9'))f^=(c=='-'),c=gc();if(c==EOF){__=1;return;}x=0;while(c!=EOF&&'0'<=c&&c<='9')x=x*10+c-48,c=gc();if(c==EOF)__=1;if(f)x=-x;}template<typename T,typename ... arr>inline void in(T &x,arr & ... y){in(x),in(y...);}}using namespace IN;
const int N=250001,inf=-1u>>1;
int n,m,rev[N],c[2][N],f[N],s[N];
struct edge{int x,y,w;bool operator<(edge t){return w<t.w;}}e[N];
#define ls(x) c[0][x]
#define rs(x) c[1][x]
il void pu(int x){s[x]=min(x>n?x:inf,min(s[ls(x)],s[rs(x)]));}
il void pr(int x){rev[x]^=1;int t=ls(x);ls(x)=rs(x),rs(x)=t;}
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
int st[N];
il void splay(int x){
    int z=0,y=st[++z]=x;
    while(nrt(y))st[++z]=y=f[y];
    while(z)pd(st[z--]);
    for(;nrt(x);rotate(x))if(nrt(f[x]))
        rotate(g(x)^g(f[x])?x:f[x]);
}
il void access(int x){for(int y=0;x;x=f[y=x])splay(x),rs(x)=y,pu(x);}
il void mrt(int x){access(x),splay(x),pr(x);}
il int frt(int x){
    for(access(x),splay(x);ls(x);pd(x),x=ls(x));
    splay(x);return x;
}
il void link(int x,int y){mrt(x),f[x]=y;}
bool b[N];
int main(){
    s[0]=inf;
    in(n,m);
    for(int i=1;i<=m;++i)in(e[i].x,e[i].y,e[i].w);
    std::sort(e+1,e+m+1);
    int x,y,t=n,tt=0,p=1,ans=inf;
    for(int i=1;i<=m;++i){
        x=e[i].x,y=e[i].y;++t;
        if(x==y){b[i]=1;continue;}//要特判,re了不知道多少次就是因为这个
        mrt(x);
        if(frt(y)!=x)f[f[x]=t]=y,++tt;
        else{
            mrt(x),access(y),splay(y);
            int now=s[y];
            b[now-n]=1;splay(now);
            f[ls(now)]=f[rs(now)]=0;
            link(x,t),link(t,y);
        }
        while(b[p]&&p<=i)++p;
        if(tt>=n-1)ans=min(ans,e[i].w-e[p].w);
    }
    printf("%d\n",ans);
}
```

[LG 4180 \[BJWC2010\]严格次小生成树](https://www.luogu.com.cn/problem/P4180)

`LCT`动态维护最小生成树

维护链上的最大值和次大值

先找出最小生成树,然后枚举剩下的边,找出相差最小的,得出答案

这题还可以用kruskal生成树+倍增(或树剖)做,常数会小很多

```cpp
#include<bits/stdc++.h>
#define il __inline__ __attribute__ ((always_inline))
il int min(int x,int y){return x<y?x:y;}
il int max(int x,int y){return x>y?x:y;}
namespace IN{const int str=1<<20;static char in_buf[str],*in_s,*in_t;bool __=0;inline char gc(){return (in_s==in_t)&&(in_t=(in_s=in_buf)+fread(in_buf,1,str,stdin)),in_s==in_t?EOF:*in_s++;}template<typename T>inline void in(T &x){if(__)return;char c=gc();bool f=0;while(c!=EOF&&(c<'0'||c>'9'))f^=(c=='-'),c=gc();if(c==EOF){__=1;return;}x=0;while(c!=EOF&&'0'<=c&&c<='9')x=x*10+c-48,c=gc();if(c==EOF)__=1;if(f)x=-x;}template<typename T,typename ... arr>inline void in(T &x,arr & ... y){in(x),in(y...);}}using namespace IN;
const int N=100001;
int n,m,s[N<<1],S[N<<1],c[2][N<<1],f[N<<1],v[N<<1];
bool rev[N<<1];
#define ls c[0][x]
#define rs c[1][x]
il void pu(int x){
    if(s[ls]>s[rs])s[x]=s[ls],S[x]=max(S[ls],s[rs]);
    else if(s[rs]>s[ls])s[x]=s[rs],S[x]=max(s[ls],S[rs]);
    else s[x]=s[ls],S[x]=max(S[ls],S[rs]);

    if(v[x]>s[x])S[x]=s[x],s[x]=v[x];
    else if(v[x]!=s[x]&&v[x]>S[x])S[x]=v[x];
}
il void pr(int x){rev[x]^=1,ls^=rs,rs^=ls,ls^=rs;}
il void pd(int x){
    if(rev[x]){
        if(ls)pr(ls);
        if(rs)pr(rs);
        rev[x]=0;
    }
}
il int g(int x){return c[1][f[x]]==x;}
il int nrt(int x){return c[0][f[x]]==x||c[1][f[x]]==x;}
void pda(int x){if(nrt(x))pda(f[x]);pd(x);}
il void rotate(int x){
    int y=f[x],z=f[y],l=g(x),r=!l,w=c[r][x];
    if(nrt(y))c[g(y)][z]=x;
    c[r][x]=y,c[l][y]=w;
    if(w)f[w]=y;
    f[x]=z,f[y]=x;
    pu(y),pu(x);
}
il void splay(int x){
    for(pda(x);nrt(x);rotate(x))if(nrt(f[x]))
        rotate(g(x)^g(f[x])?x:f[x]);
}
il void access(int x){
    for(int y=0;x;x=f[y=x])
        splay(x),rs=y,pu(x);
}
il void mrt(int x){access(x),splay(x),pr(x);}
struct edge{
    int x,y,w;
    bool operator<(edge t){return w<t.w;}
}e[300001];
int fa[N];
int gf(int x){return x==fa[x]?x:(fa[x]=gf(fa[x]));}
int main(){
    in(n,m);
    for(int i=1;i<=m;++i)in(e[i].x,e[i].y,e[i].w);
    std::sort(e+1,e+m+1);
    long long tot=0;int x,y,id=n,ans=-1u>>1;
    for(int i=1;i<=n;++i)fa[i]=i;
    for(int i=1;i<=m;++i){
        x=e[i].x,y=e[i].y;
        if(gf(x)!=gf(y)){
            fa[fa[x]]=fa[y];
            tot+=e[i].w;
            v[++id]=e[i].w;
            mrt(x),mrt(y),f[x]=f[y]=id;
        }
        else{
            mrt(x),access(y),splay(y);
            ans=min(ans,e[i].w-(e[i].w>s[y]?s[y]:S[y]));
        }
    }
    printf("%lld\n",tot+ans);
}
```

### 维护子树信息

> 注: 此部分可直接跳过

`LCT`并不擅长维护子树,~~Top tree更适合,退役树我也不会~~

除了维护当前实链的信息,额外维护它的虚子树的信息(`siz2[x]`)

这样我们就可以得到整课树的信息

push up 变成

```cpp
void pu(int x){
    siz[x]=siz[ls(x)]+1+siz[rs(x)]+siz2[x];
}
```

那么如何维护`siz2[x]`呢?

在改变边的虚实状况的时候要及时修改`siz2[x]`

在`rotate,splay`操作中,我们都只是改变了`splay`中结点的相对位置,没有改变任意一条边的虚实情况,所以不对`siz2[x]`进行任何修改。

在`access`操作中,在每次`splay`完后,都会改变刚刚`splay`完的结点的右儿子,即该结点与其原右儿子的连边和该节点和新右儿子的连边的虚实情况发生了变化,我们需要加上新变成虚边所连的子树的贡献,减去刚刚变成实边所连的子树的贡献。

在`link`操作中添加了虚链,要加上新的虚子树的贡献

```cpp
void access(int x){
    for(int y=0;x;x=f[y=x])
        splay(x),siz2[x]+=siz[rs(x)]-siz[rs(x)=y],pu(x);
}
void link(int x,int y){
    mrt(x),mrt(y),
    siz2[f[x]=y]+=siz[x];
}
```

其他地方和普通的`LCT`一样

注意:

1. 维护的信息要有**可减性**,如子树结点数,子树权值和,但不能直接维护子树最大最小值,因为在将一条虚边变成实边时要排除原先虚边的贡献
   
2. 如果维护的信息没有可减性,如维护区间最值,可以对每个结点开一个平衡树维护结点的虚子树中的最值。

[LG4219 \[BJOI2014\]大融合](https://www.luogu.com.cn/problem/P4219)

路径数量为断开该边后两端子树大小的乘积

```cpp
#include<bits/stdc++.h>
#pragma GCC optimize(3)
#define il __inline__ __attribute__ ((always_inline))
namespace IO{const int str=1<<20;static char in_buf[str],*in_s,*in_t;bool __=0;il char gc(){return (in_s==in_t)&&(in_t=(in_s=in_buf)+fread(in_buf,1,str,stdin)),in_s==in_t?EOF:*in_s++;}il void in(char &ch){if(__)return;char c;while((c=gc())!=EOF&&isspace(c));if(c==EOF)__=1;else ch=c;}il void in(char *ch){*ch='\0';if(__)return;char c;while((c=gc())!=EOF&&isspace(c));if(c==EOF){__=1;return;}*ch=c;ch++;while((c=gc())!=EOF&&!isspace(c))*ch=c,ch++;if(c==EOF)__=1;*ch='\0';}template<typename T>il void in(T &x){if(__)return;char c=gc();bool f=0;while(c!=EOF&&(c<'0'||c>'9'))f^=(c=='-'),c=gc();if(c==EOF){__=1;return;}x=0;while(c!=EOF&&'0'<=c&&c<='9')x=x*10+c-48,c=gc();if(c==EOF)__=1;if(f)x=-x;}template<typename T,typename ... arr>il void in(T &x,arr & ... y){in(x),in(y...);}const char ln='\n';static char out_buf[str],*out_s=out_buf,*out_t=out_buf+str;il void flush(){fwrite(out_buf,1,out_s-out_buf,stdout);out_s=out_buf;}il void pt(char c){(out_s==out_t)?(fwrite(out_s=out_buf,1,str,stdout),*out_s++=c):(*out_s++=c);}il void out(const char* s){while(*s)pt(*s++);}il void out(char* s){while(*s)pt(*s++);}il void out(char c){pt(c);}template<typename T>il void out(T x){if(!x){pt('0');return;}if(x<0)pt('-'),x=-x;char a[50],t=0;while(x)a[t++]=x%10,x/= 10;while(t--)pt(a[t]+'0');}template<typename T,typename ... arr>il void out(T x,arr & ... y){out(x),out(y...);}}using namespace IO;
const int N=100011;
int n,q,siz[N],siz2[N],c[2][N],f[N];
bool rev[N];
#define ls(x) c[0][x]
#define rs(x) c[1][x]
il void pu(int x){siz[x]=siz[ls(x)]+siz[rs(x)]+1+siz2[x];}
il void pr(int x){rev[x]^=1;int t=ls(x);ls(x)=rs(x),rs(x)=t;}
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
void pda(int x){
    if(nrt(x))pda(f[x]);
    pd(x);
}
il void splay(int x){
    for(pda(x);nrt(x);rotate(x))if(nrt(f[x]))
        rotate(g(x)^g(f[x])?x:f[x]);
}
il void access(int x){
    for(int y=0;x;x=f[y=x])
        splay(x),siz2[x]+=siz[rs(x)]-siz[rs(x)=y],pu(x);
}
il void mrt(int x){access(x),splay(x),pr(x);}
int main(){
    in(n,q);
    for(int i=1;i<=n;++i)siz[i]=1;
    char opt;int x,y;
    while(q--){
        in(opt,x,y);
        if(opt=='A')
            mrt(x),mrt(y),
            siz2[f[x]=y]+=siz[x];
        else{
            mrt(x),access(y),splay(y);  
            f[x]=ls(y)=0,pu(x);
            mrt(x),mrt(y);
            out((long long)siz[x]*siz[y],ln);
            siz2[f[x]=y]+=siz[x];
        }
    }
    flush();
}
```

[SPOJ QTREE5 - Query on a tree V](https://www.luogu.org/problemnew/show/SP2939)

根据套路,用`LCT`维护子树,信息为最值,每个节点都开一个`multiset`来记录虚子树信息

思考`LCT`的定义,每个`splay`维护的是一条深度单调递增的链(也可以说是实链)

我们定义`lm[x],rm[x]`分别为每条实链的上端和下端能够到达最近的白点的距离

这样就可以方便地更新信息了

每次求解可以`access(x),splay(x)`,然后$x$就是树根所在实链的下端,输出`rm[x]`就可以了

这样不需要换根什么的,也就不需要翻转操作,省去了复杂的pushdown过程

```cpp
#include<bits/stdc++.h>
#pragma GCC optimize(3)
#define il __inline__ __attribute__ ((always_inline))
namespace IO{const int str=1<<20;static char in_buf[str],*in_s,*in_t;bool __=0;il char gc(){return (in_s==in_t)&&(in_t=(in_s=in_buf)+fread(in_buf,1,str,stdin)),in_s==in_t?EOF:*in_s++;}il void in(char &ch){if(__)return;char c;while((c=gc())!=EOF&&isspace(c));if(c==EOF)__=1;else ch=c;}il void in(char *ch){*ch='\0';if(__)return;char c;while((c=gc())!=EOF&&isspace(c));if(c==EOF){__=1;return;}*ch=c;ch++;while((c=gc())!=EOF&&!isspace(c))*ch=c,ch++;if(c==EOF)__=1;*ch='\0';}template<typename T>il void in(T &x){if(__)return;char c=gc();bool f=0;while(c!=EOF&&(c<'0'||c>'9'))f^=(c=='-'),c=gc();if(c==EOF){__=1;return;}x=0;while(c!=EOF&&'0'<=c&&c<='9')x=x*10+c-48,c=gc();if(c==EOF)__=1;if(f)x=-x;}template<typename T,typename ... arr>il void in(T &x,arr & ... y){in(x),in(y...);}const char ln='\n';static char out_buf[str],*out_s=out_buf,*out_t=out_buf+str;il void flush(){fwrite(out_buf,1,out_s-out_buf,stdout);out_s=out_buf;}il void pt(char c){(out_s==out_t)?(fwrite(out_s=out_buf,1,str,stdout),*out_s++=c):(*out_s++=c);}il void out(const char* s){while(*s)pt(*s++);}il void out(char* s){while(*s)pt(*s++);}il void out(char c){pt(c);}template<typename T>il void out(T x){if(!x){pt('0');return;}if(x<0)pt('-'),x=-x;char a[50],t=0;while(x)a[t++]=x%10,x/= 10;while(t--)pt(a[t]+'0');}template<typename T,typename ... arr>il void out(T x,arr & ... y){out(x),out(y...);}}using namespace IO;
const int N=100011,inf=1000000000;
int n,q,siz[N],c[2][N],f[N],lm[N],rm[N];
bool rev[N],col[N];
using std::multiset;
multiset<int>s2[N];
#define ls(x) c[0][x]
#define rs(x) c[1][x]
il int min(int x,int y){return x<y?x:y;}
il void pu(int x){
    siz[x]=siz[ls(x)]+siz[rs(x)]+1;
    int t=s2[x].empty()?inf:*s2[x].begin();
    lm[x]=min(lm[ls(x)],siz[ls(x)]+min(col[x]?0:inf,min(t,lm[rs(x)]+1)));
    rm[x]=min(rm[rs(x)],siz[rs(x)]+min(col[x]?0:inf,min(t,rm[ls(x)]+1)));
}
il int g(int x){return rs(f[x])==x;}
il int nrt(int x){return ls(f[x])==x||rs(f[x])==x;}
il void rotate(int x){
    int y=f[x],z=f[y],l=g(x),r=!l,w=c[r][x];
    if(nrt(y))c[g(y)][z]=x;
    c[r][x]=y,c[l][y]=w;
    if(w)f[w]=y;
    f[y]=x,f[x]=z;
    pu(y),pu(x);
}
il void splay(int x){
    for(;nrt(x);rotate(x))if(nrt(f[x]))
        rotate(g(x)^g(f[x])?x:f[x]);
}
il void access(int x){
    for(int y=0;x;x=f[y=x]){
        splay(x);
        s2[x].insert(lm[rs(x)]+1);
        rs(x)=y;
        multiset<int>::iterator it=s2[x].lower_bound(lm[rs(x)]+1);
        if(it!=s2[x].end()&&(*it)==lm[rs(x)]+1)s2[x].erase(it);
        pu(x);
    }
}
struct edge{int to,nxt;}e[N<<1];
int cnt=0,head[N];
il void add(int x,int y){e[++cnt].to=y;e[cnt].nxt=head[x];head[x]=cnt;}
void dfs(int x,int fa){
    for(int i=head[x],to;to=e[i].to,i;i=e[i].nxt)
    if(to!=fa){
        f[to]=x;s2[x].insert(inf+1);pu(x);
        dfs(to,x);
    }
}
int main(){
    in(n);
    lm[0]=rm[0]=inf;
    int opt,x,y;
    for(int i=1;i<n;++i)in(x,y),add(x,y),add(y,x);
    dfs(1,0);
    in(q);
    while(q--){
        in(opt,x);
        access(x),splay(x);
        if(!opt)col[x]^=1,pu(x);
        else out(rm[x]>n?-1:rm[x],ln);
    }
    flush();
}
```

[LG 4299 首都](https://www.luogu.com.cn/problem/P4299)

`LCT`维护重心

这里利用了两个重心性质:

1. 树中所有点到某个点的距离和中,到重心的距离和是最小的,如果有两个距离和,他们的距离和一样。
   
2. 把两棵树通过某一点相连得到一颗新的树,新的树的重心必然在连接原来两棵树重心的路径上。

我们需要维护子树的大小

合并的时候连接两棵树,分离出连接原来两棵树重心的路径,在链上搜索出答案

方法类似平衡树的查找

可以用并查集来记录重心位置,这样不用调用复杂度较高的`find root`

每次合并后记得把新的重心旋转到根,保证复杂度

```cpp
#include<bits/stdc++.h>
const int N=100011;
int n,q,s[N],s2[N],c[2][N],f[N],bl[N],ans;
bool rev[N];
int BL(int x){return x==bl[x]?x:(bl[x]=BL(bl[x]));}
#define ls c[0][x]
#define rs c[1][x]
void pu(int x){s[x]=s[ls]+s[rs]+1+s2[x];}
void pr(int x){rev[x]^=1;ls^=rs,rs^=ls,ls^=rs;}
void pd(int x){
    if(rev[x]){
        if(ls)pr(ls);
        if(rs)pr(rs);
        rev[x]=0;
    }
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
void pda(int x){if(nrt(x))pda(f[x]);pd(x);}
void splay(int x){
    for(pda(x);nrt(x);rotate(x))if(nrt(f[x]))
        rotate(g(x)^g(f[x])?x:f[x]);
    pu(x);
}
void access(int x){
    for(int y=0;x;x=f[y=x])
        splay(x),s2[x]+=s[rs]-s[rs=y],pu(x);
}
void mrt(int x){access(x),splay(x),pr(x);}
void link(int x,int y){
    mrt(x),access(y),splay(y);
    f[x]=y;
    s2[y]+=s[x];
    pu(y);
}
int find(int x){
    bool ff=s[x]&1;
    int sum=s[x]>>1,cl,cr,as=n+1,lsum=0,rsum=0;
    while(x){
        pd(x);
        cl=s[ls]+lsum,cr=s[rs]+rsum;
        if(cl<=sum&&cr<=sum){
            if(ff)return x;
            else if(as>x)as=x;
        }
        if(cl<cr)lsum+=s[ls]+s2[x]+1,x=rs;
        else rsum+=s[rs]+s2[x]+1,x=ls;
    }
    return as;
}
int main(){
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;++i)s[i]=1,bl[i]=i,ans^=i;
    char opt[5];
    int x,y;
    while(q--){
        scanf("%s",opt);
        if(opt[0]=='X')printf("%d\n",ans);
        else if(opt[0]=='Q')
            scanf("%d",&x),
            printf("%d\n",BL(x));
        else{
            scanf("%d%d",&x,&y);
            link(x,y);
            x=BL(x),y=BL(y);
            mrt(x),access(y),splay(y);
            int z=find(y);
            bl[x]=bl[y]=bl[z]=z;
            ans^=x^y^z;
            splay(z);
        }
    }
}
```

### 维护树上染色联通块

[LG SP16549 QTREE6 - Query on a tree VI](https://www.luogu.com.cn/problem/SP16549)

#### 解法一

化边为点

每个点的父边赋予该点的颜色。我们需要两个LCT,每种对应一个颜色。一条边只有在对应颜色的LCT中才会被连上。

接着可以发现,修改一个点的颜色,只需要在原来颜色对应`LCT`中断开父边,在新颜色`LCT`中连接父边,就可以维护同色连通块了

查询的时候只要找到$x$所在`splay`的根,右子树大小就是答案(相当于边的数目,根的深度最浅,只有右子树)

注意: 1节点是没有父亲的,不过为了模型的建立,要有父边,于是需要加一个虚点,让1的父亲指向它连边

手动模拟一下应该可以懂

这个类型的`LCT`比较特殊,代码可能也会有少许不同,多看代码理解一下

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

#### 解法2

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

[SP16580 QTREE7 - Query on a tree VII](https://www.luogu.com.cn/problem/SP16580)

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

### 一些灵活巧妙的link-cut tree用法

[LG 3203 \[HNOI2010\]弹飞绵羊](https://www.luogu.com.cn/problem/P3203)



[LG 3703 \[SDOI2017\]树点涂色](https://www.luogu.com.cn/problem/P3703)

`1 x`表示把点$x$到根节点的路径上所有的点染上一种没有用过的新颜色

从这里可以看出每种颜色在树上都是一条链的形式存在

可以发现这和`LCT`很像

那么`1`操作可以看成`access`操作,(如何操作先放着

$x$到根的颜色种数也就是要经过的虚边的条数,设为$S_x$

求$x$到$y$的路径的权值,可以使用树上差分的形式

也就是转化为$S_x + S_y - 2\times S_{lca(x,y)} + 1$

`3`操作也就是求子树最值

我们回过头来看`access`操作:

1. 原来的实边变虚,意味着要多走一条虚边,将此链所管辖的区域全部+1
   
2. 虚边变实边,意味着要多少一条虚边,将此链所管辖的区域全部-1

注意: `LCT`中`splay`的父子关系并不是原树中的父子关系,要找到该`splay`中深度最小的节点(也就是这条链的顶端再操作)

综上可以用 lct+lca+dfs序+线段树 解决

当然也可以通过树剖模拟`access`的形式来解决

```cpp
#include<bits/stdc++.h>
#pragma GCC optimize(3)
#define il __inline__ __attribute__ ((always_inline))
#define fur(i,x,y) for(int i(x);i<=y;++i)
#define fl(i,x) for(int i(head[x]),to;to=e[i].to,i;i=e[i].nxt)
template <class T>il T MAX(T x,T y){return x>y?x:y;}
using namespace std;
namespace IO{const int str=1<<20;static char in_buf[str],*in_s,*in_t;bool __=0;il char gc(){return (in_s==in_t)&&(in_t=(in_s=in_buf)+fread(in_buf,1,str,stdin)),in_s==in_t?EOF:*in_s++;}il void in(string &ch){ch.clear();if(__)return;char c;while((c=gc())!=EOF&&isspace(c));if(c==EOF){__=1;return;}ch+=c;while((c=gc())!=EOF&&!isspace(c))ch+=c;if(c==EOF)__=1;}il void in(char &ch){if(__)return;char c;while((c=gc())!=EOF&&isspace(c));if(c==EOF)__=1;else ch=c;}il void in(char *ch){*ch='\0';if(__)return;char c;while((c=gc())!=EOF&&isspace(c));if(c==EOF){__=1;return;}*ch=c;ch++;while((c=gc())!=EOF&&!isspace(c))*ch=c,ch++;if(c==EOF)__=1;*ch='\0';}template<typename T>il void in(T &x){if(__)return;char c=gc();bool f=0;while(c!=EOF&&(c<'0'||c>'9'))f^=(c=='-'),c=gc();if(c==EOF){__=1;return;}x=0;while(c!=EOF&&'0'<=c&&c<='9')x=x*10+c-48,c=gc();if(c==EOF)__=1;if(f)x=-x;}template<typename T,typename ... arr>il void in(T &x,arr & ... y){in(x),in(y...);}const char ln='\n';static char out_buf[str],*out_s=out_buf,*out_t=out_buf+str;il void flush(){fwrite(out_buf,1,out_s-out_buf,stdout);out_s=out_buf;}il void pt(char c){(out_s==out_t)?(fwrite(out_s=out_buf,1,str,stdout),*out_s++=c):(*out_s++=c);}il void out(const char* s){while(*s)pt(*s++);}il void out(char* s){while(*s)pt(*s++);}il void out(char c){pt(c);}il void out(string s){for(int i=0;s[i];i++)pt(s[i]);}template<typename T>il void out(T x){if(!x){pt('0');return;}if(x<0)pt('-'),x=-x;char a[50],t=0;while(x)a[t++]=x%10,x/= 10;while(t--)pt(a[t]+'0');}template<typename T,typename ... arr>il void out(T x,arr & ... y){out(x),out(y...);}}using namespace IO;
const int N=100011;
int n,q,cnt,head[N],a[N];
struct seg{
    #define ls rt<<1
    #define rs rt<<1|1
    #define pu s[rt]=MAX(s[ls],s[rs])
    int s[N<<2],laz[N<<2];
    void build(int l=1,int r=n,int rt=1){
        if(l==r)return void(s[rt]=a[l]);
        int m=l+r>>1;
        build(l,m,ls);build(m+1,r,rs);
        pu;
    }
    il void pd(int rt){
        if(laz[rt]){
            laz[ls]+=laz[rt];
            laz[rs]+=laz[rt];
            s[ls]+=laz[rt];
            s[rs]+=laz[rt];
            laz[rt]=0;
        }
    }
    void upd(int L,int R,int v,int l=1,int r=n,int rt=1){
        if(L<=l&&r<=R){
            s[rt]+=v,laz[rt]+=v;
            return;
        }
        int m=l+r>>1;
        pd(rt);
        if(L<=m)upd(L,R,v,l,m,ls);
        if(R>m)upd(L,R,v,m+1,r,rs);
        pu;
    }
    int ask(int L,int R,int l=1,int r=n,int rt=1){
        if(L<=l&&r<=R)return s[rt];
        int m=l+r>>1,ans=0;
        pd(rt);
        if(L<=m)ans=ask(L,R,l,m,ls);
        if(R>m)ans=MAX(ans,ask(L,R,m+1,r,rs));
        return ans;
    }
    il int operator[](int x){
        int l=1,r=n,rt=1;
        while(1){
            if(l==r)return s[rt];
            int m=l+r>>1;
            pd(rt);
            if(x<=m)r=m,rt=ls;
            else l=m+1,rt=rs;
        }
    }
    #undef ls
    #undef rs
}S;
struct edge{int to,nxt;}e[N<<1];
il void add(int x,int y){e[++cnt].to=y;e[cnt].nxt=head[x];head[x]=cnt;}
int siz[N],top[N],id[N],sz;
struct lct{
    #define ls c[0][x]
    #define rs c[1][x]
    int f[N],c[2][N];
    il int g(int x){return c[1][f[x]]==x;}
    il int nrt(int x){return c[0][f[x]]==x||c[1][f[x]]==x;}
    il void rotate(int x){
        int y=f[x],z=f[y],l=g(x),r=!l,w=c[r][x];
        if(nrt(y))c[g(y)][z]=x;
        c[r][x]=y,c[l][y]=w;
        if(w)f[w]=y;
        f[x]=z,f[y]=x;
    }
    il void splay(int x){
        for(;nrt(x);rotate(x))if(nrt(f[x]))
            rotate(g(x)^g(f[x])?x:f[x]);
    }
    il int frt(int x){while(ls)x=ls;return x;}
    il void access(int x){
        for(int y=0,t;x;x=f[y=x]){
            splay(x);
            if(rs)t=frt(rs),S.upd(id[t],id[t]+siz[t]-1,1);
            if(rs=y)t=frt(y),S.upd(id[t],id[t]+siz[t]-1,-1);
        }
    }
    #undef ls
    #undef rs
}T;
int f[N],d[N];
void dfs(int x){
    siz[x]=1;d[x]=d[f[x]]+1;
    fl(i,x)if(to!=f[x])
        f[to]=T.f[to]=x,dfs(to),siz[x]+=siz[to];
}
void bt(int x,int tp){
    top[x]=tp;a[id[x]=++sz]=d[x];int k=0;
    fl(i,x)if(to!=f[x]&&siz[to]>siz[k])k=to;
    if(!k)return;bt(k,tp);
    fl(i,x)if(!top[to])bt(to,to);
}
il int lca(int x,int y){
    while(top[x]^top[y])
        d[top[x]]>d[top[y]]?x=f[top[x]]:y=f[top[y]];
    return d[x]<d[y]?x:y;
}
int main(){
    in(n,q);
    int opt,x,y;
    fur(i,2,n)in(x,y),add(x,y),add(y,x);
    dfs(1);bt(1,1);S.build();
    while(q--){
        in(opt,x);
        if(opt==1)T.access(x);
        else if(opt==2)
            in(y),out(S[id[x]]+S[id[y]]-(S[id[lca(x,y)]]<<1)+1,ln);
        else out(S.ask(id[x],id[x]+siz[x]-1),ln);
    }
    flush();
}
```