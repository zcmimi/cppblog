---
title: SPOJ GSS 系列
date: 2020-05-25 19:22
author: 
avatar:
tags: 
  - 数据结构
  - 线段树
  - 平衡树

categories:
  - [刷题记录]

thumbnail: 
top: 0 
comment: 1
html:
---

SPOJ的GSS系列是关于区间统计技巧的集合

~~非常适合锻炼码力~~

[LG GSS1](https://www.luogu.com.cn/problem/SP1043) | [SPOJ GSS1](https://www.SPOJ.com/problems/GSS1)

[LG GSS2](https://www.luogu.com.cn/problem/SP1557) | [SPOJ GSS2](https://www.SPOJ.com/problems/GSS2)

[LG GSS3](https://www.luogu.com.cn/problem/SP1716) | [SPOJ GSS3](https://www.SPOJ.com/problems/GSS3)

[LG GSS4](https://www.luogu.com.cn/problem/SP2713) | [SPOJ GSS4](https://www.SPOJ.com/problems/GSS4)

[LG GSS5](https://www.luogu.com.cn/problem/SP2916) | [SPOJ GSS5](https://www.SPOJ.com/problems/GSS5)

[LG GSS6](https://www.luogu.com.cn/problem/SP4487) | [SPOJ GSS6](https://www.SPOJ.com/problems/GSS6)

[LG GSS7](https://www.luogu.com.cn/problem/SP6779) | [SPOJ GSS7](https://www.SPOJ.com/problems/GSS7)

[LG GSS8](https://www.luogu.com.cn/problem/SP19543) | [SPOJ GSS8](https://www.SPOJ.com/problems/GSS8)

GSS1,GSS3: 最大子段和:

每个节点记录区间和,最大后缀和,最大前缀和,答案

```cpp
node operator+(node x,node y){
    node c;
    c.s=x.s+y.s;// 和
    c.mx=max(max(x.mx,y.mx),x.r+y.l); //答案
    c.l=max(x.l,x.s+y.l);//最大前缀
    c.r=max(y.r,y.s+x.r);//最大后缀
    return c;
}
```

## GSS3 & GSS 1

> 静态区间最大子段和,单点修改

线段树

```cpp
#include<bits/stdc++.h>
int max(int x,int y){return x>y?x:y;}
int rd(){int x=0;char c;bool f=0;for(c=getchar();c<'0'||'9'<c;c=getchar())f^=c=='-';for(x=c-48,c=getchar();'0'<=c&&c<='9';x=x*10+c-48,c=getchar());return f?-x:x;}
const int N=50011;
#define ls rt<<1
#define rs rt<<1|1
int n,q;
struct node{int s,l,r,mx;}s[N<<2];
node operator+(node x,node y){
    node c;
    c.s=x.s+y.s;
    c.mx=max(max(x.mx,y.mx),x.r+y.l);
    c.l=max(x.l,x.s+y.l);
    c.r=max(y.r,y.s+x.r);
    return c;
}
void build(int l,int r,int rt){
    if(l==r){s[rt].s=s[rt].mx=s[rt].l=s[rt].r=rd();return;}
    int m=l+r>>1;
    build(l,m,ls),build(m+1,r,rs);
    s[rt]=s[ls]+s[rs];
}
void upd(int p,int v,int l,int r,int rt){
    if(l==r){s[rt]={v,v,v,v};return;}
    int m=l+r>>1;
    if(p<=m)upd(p,v,l,m,ls);
    else upd(p,v,m+1,r,rs);
    s[rt]=s[ls]+s[rs];
}
node ask(int L,int R,int l,int r,int rt){
    if(L==l&&r==R)return s[rt];
    int m=l+r>>1;
    if(L>m)return ask(L,R,m+1,r,rs);
    else if(R<=m)return ask(L,R,l,m,ls);
    else return ask(L,m,l,m,ls)+ask(m+1,R,m+1,r,rs);
}
int main(){
    n=rd();
    build(1,n,1);
    q=rd();
    while(q--){
        int opt=rd(),x=rd(),y=rd();
        if(opt)printf("%d\n",ask(x,y,1,n,1).mx);
        else upd(x,y,1,n,1);
    }
}
```

## GSS5

> 给定一个序列。查询左端点在$[x_1, y_1]$之间,且右端点在$[x_2, y_2]$之间的最大子段和,数据保证$x_1\leq x_2,y_1\leq y_2$​ ,但是不保证端点所在的区间不重合

分类讨论

1. 不重合:
   
   $[y_1,x_2]$的和+$[x_1,y_1-1]$的最大后缀和+$[x_2+1,y_2]$的最大前缀和

2. 重合:
   
   - $[x_2,y_1]$的最大子段和
   - $[x_2,y_1]$的和+$[x_1,x_2-1]$的最大后缀和+$[y_1+1,x_2]$的最大前缀和
   - $[x_1,x_2-1]$最大后缀和+$[x_2,y_1]$最大前缀和
   - $[x_2,y_1]$最大后缀和+$[y_1+1,y_2]$最大前缀和

```cpp
#include<bits/stdc++.h>
int max(int x,int y){return x>y?x:y;}
int rd(){int x=0;char c;bool f=0;for(c=getchar();c<'0'||'9'<c;c=getchar())f^=c=='-';for(x=c-48,c=getchar();'0'<=c&&c<='9';x=x*10+c-48,c=getchar());return f?-x:x;}
const int N=10011;
int n,q;
#define ls rt<<1
#define rs rt<<1|1
struct node{int s,l,r,mx;}s[N<<2];
node operator+(node x,node y){
    node c;
    c.s=x.s+y.s;
    c.mx=max(max(x.mx,y.mx),x.r+y.l);
    c.l=max(x.l,x.s+y.l);
    c.r=max(y.r,y.s+x.r);
    return c;
}
void build(int l,int r,int rt){
    if(l==r){s[rt].s=s[rt].mx=s[rt].l=s[rt].r=rd();return;}
    int m=l+r>>1;
    build(l,m,ls),build(m+1,r,rs);
    s[rt]=s[ls]+s[rs];
}
node ask(int L,int R,int l=1,int r=n,int rt=1){
    if(L>R)return s[0];
    if(L==l&&r==R)return s[rt];
    int m=l+r>>1;
    if(L>m)return ask(L,R,m+1,r,rs);
    else if(R<=m)return ask(L,R,l,m,ls);
    else return ask(L,m,l,m,ls)+ask(m+1,R,m+1,r,rs);
}
void solve(){
    n=rd();
    build(1,n,1);
    q=rd();
    while(q--){
        int x=rd(),y=rd(),X=rd(),Y=rd();
        if(y<X)printf("%d\n",max(ask(x,y-1).r,0)+ask(y,X).s+max(ask(X+1,Y).l,0));
        else{
            node a=ask(x,X-1),b=ask(X,y),c=ask(y+1,Y);
            printf("%d\n",max(max(b.mx,max(a.r,0)+b.s+max(c.l,0)),max(a.r+b.l,b.r+c.l)));
        }
    }
}
int main(){
    int T=rd();
    while(T--)solve();
}
```

## GSS6

> 给出一个由$N$个整数组成的序列$A$,你需要应用$M$> 个操作：
> 
> - `I p x` 在$~p~$处插入插入一个元素$~x~$
> - `D p` 删除$~p~$处的一个元素
> - `R p x` 修改$~p~$处元素的值为$~x~$
> - `Q l r` 查询一个区间$[l,r]$的最大子段和

最大子段和搬到了平衡树上

```cpp
#include<bits/stdc++.h>
int max(int x,int y){return x>y?x:y;}
int rd(){int x=0;char c;bool f=0;for(c=getchar();c<'0'||'9'<c;c=getchar())f^=c=='-';for(x=c-48,c=getchar();'0'<=c&&c<='9';x=x*10+c-48,c=getchar());return f?-x:x;}
const int N=200001;
struct node{
    int s,l,r,mx;
    node(){s=l=r=mx=0;}
    node(int v){s=l=r=mx=v;}
}s[N<<1];
node operator+(node x,node y){
    node c;
    c.s=x.s+y.s;
    c.mx=max(max(x.mx,y.mx),x.r+y.l);
    c.l=max(x.l,x.s+y.l);
    c.r=max(y.r,y.s+x.r);
    return c;
}
int RT,cnt,sz[N],v[N],rnd[N],c[2][N];
#define ls c[0][x]
#define rs c[1][x]
int ne(int val){
    s[++cnt]=node(val),rnd[cnt]=rand(),v[cnt]=val,sz[cnt]=1;
    return cnt;
}
void pu(int x){
    sz[x]=sz[ls]+1+sz[rs];
    s[x]=node(v[x]);
    if(ls)s[x]=s[ls]+s[x];
    if(rs)s[x]=s[x]+s[rs];
}
void sl(int x,int k,int &a,int &b){
    if(!x){a=b=0;return;}
    if(sz[ls]>=k)b=x,sl(ls,k,a,ls);
    else a=x,sl(rs,k-sz[ls]-1,rs,b);
    pu(x);
}
int mg(int x,int y){
    if(!x||!y)return x|y;
    if(rnd[x]<rnd[y]){
        c[1][x]=mg(c[1][x],y);
        pu(x);return x;
    }
    else{
        c[0][y]=mg(x,c[0][y]);
        pu(y);return y;
    }
}
int main(){
    srand(time(0));
    for(int n=rd();n--;)RT=mg(RT,ne(rd()));
    char opt;
    for(int q=rd(),x,y,z,l,r;q--;){
        while(isspace(opt=getchar()));
        if(opt=='I')
            sl(RT,rd()-1,x,z),
            RT=mg(x,mg(ne(rd()),z));
        else if(opt=='D')
            sl(RT,rd()-1,x,z),sl(z,1,y,z),
            RT=mg(x,z);
        else if(opt=='R')
            sl(RT,rd()-1,x,z),sl(z,1,y,z),
            s[y]=node(v[y]=rd()),
            RT=mg(x,mg(y,z));
        else if(opt=='Q')
            l=rd(),r=rd(),
            sl(RT,r,x,z),sl(x,l-1,x,y),
            printf("%d\n",s[y].mx),
            RT=mg(x,mg(y,z));
    }
}
```

## GSS7

> 给定一棵树,有$N(N \le 100000)$个节点,每一个节点都有一个权值$x_i (|x_i| \le 10000)$
> 
> 你需要执行$Q (Q \le 100000)$次操作：
> 
> 1. `1 a b` 查询`(a,b)`这条链上的最大子段和,**可以为空**（即输出$0$）
> 2. `2 a b c` 将`(a,b)`这条链上的所有点权变为`c` $(|c| \le 10000)$

最大子段和搬到了树上,树链剖分

树剖查询时注意合并顺序和反转左边

```cpp
#include<bits/stdc++.h>
void swap(int&x,int&y){x^=y,y^=x,x^=y;}
int max(int x,int y){return x>y?x:y;}
void rd(int&x){x=0;char c;bool f=0;for(c=getchar();c<'0'||'9'<c;c=getchar())f^=c=='-';for(x=c-48,c=getchar();'0'<=c&&c<='9';x=x*10+c-48,c=getchar());if(f)x=-x;}
const int N=100001;
int n,cnt,head[N],a[N],c[N];
struct edge{int to,nxt;}e[N<<1];
void add(int x,int y){e[++cnt].to=y;e[cnt].nxt=head[x];head[x]=cnt;}
int d[N],f[N],siz[N],top[N],id[N],sz;
void dfs(int x){
    siz[x]=1;
    for(int i=head[x],to;to=e[i].to,i;i=e[i].nxt)
        if(to!=f[x])
            f[to]=x,d[to]=d[x]+1,
            dfs(to),siz[x]+=siz[to];
}
void bt(int x,int tp){
    top[x]=tp;c[id[x]=++sz]=a[x];
    int k=0;
    for(int i=head[x],to;to=e[i].to,i;i=e[i].nxt)
        if(to!=f[x]&&siz[to]>siz[k])k=to;
    if(k)bt(k,tp);
    for(int i=head[x],to;to=e[i].to,i;i=e[i].nxt)
        if(!top[to])bt(to,to);
}
struct node{
    int s,l,r,mx;
    node(){s=l=r=mx=0;}
    node(int v){s=v,l=r=mx=max(v,0);}
    void rev(){swap(l,r);}
}s[N<<2];
node operator+(node x,node y){
    node c;
    c.s=x.s+y.s;
    c.mx=max(max(x.mx,y.mx),x.r+y.l);
    c.l=max(x.l,x.s+y.l);
    c.r=max(y.r,y.s+x.r);
    return c;
}
int laz[N<<2];bool tag[N<<2];
#define ls rt<<1
#define rs rt<<1|1
void build(int l,int r,int rt){
    if(l==r){s[rt]=node(c[l]);return;}
    int m=l+r>>1;
    build(l,m,ls),build(m+1,r,rs);
    s[rt]=s[ls]+s[rs];
}
void pd(int rt,int ln,int rn){
    if(tag[rt]){
        laz[ls]=laz[rs]=laz[rt];
        tag[ls]=tag[rs]=1;
        s[ls]=node(laz[rt]*ln);
        s[rs]=node(laz[rt]*rn);
        tag[rt]=0;
    }
}
void mdy(int L,int R,int v,int l,int r,int rt){
    if(L<=l&&r<=R){
        s[rt]=node(v*(r-l+1));
        laz[rt]=v;tag[rt]=1;
        return;
    }
    int m=l+r>>1;
    pd(rt,m-l+1,r-m);
    if(L<=m)mdy(L,R,v,l,m,ls);
    if(R>m)mdy(L,R,v,m+1,r,rs);
    s[rt]=s[ls]+s[rs];
}
node qry(int L,int R,int l,int r,int rt){
    if(L==l&&r==R)return s[rt];
    int m=l+r>>1;
    pd(rt,m-l+1,r-m);
    if(L>m)return qry(L,R,m+1,r,rs);
    else if(R<=m)return qry(L,R,l,m,ls);
    else return qry(L,m,l,m,ls)+qry(m+1,R,m+1,r,rs);
}
int ask(int x,int y){
    node l,r;
    while(top[x]^top[y])
        if(d[top[x]]>d[top[y]])
            l=qry(id[top[x]],id[x],1,n,1)+l,x=f[top[x]];
        else 
            r=qry(id[top[y]],id[y],1,n,1)+r,y=f[top[y]];
    if(d[x]>d[y])
        l=qry(id[y],id[x],1,n,1)+l;
    else 
        r=qry(id[x],id[y],1,n,1)+r;
    l.rev();
    return (l+r).mx;
}
void upd(int x,int y,int v){
    while(top[x]^top[y]){
        if(d[top[x]]<d[top[y]])swap(x,y);
        mdy(id[top[x]],id[x],v,1,n,1),x=f[top[x]];
    }
    if(d[x]>d[y])swap(x,y);
    mdy(id[x],id[y],v,1,n,1);
}
int main(){
    rd(n);
    for(int i=1;i<=n;++i)rd(a[i]);
    int q,opt,x,y,v;
    for(int i=1;i<n;++i)
        rd(x),rd(y),
        add(x,y),add(y,x);
    dfs(1),bt(1,1),build(1,n,1);
    for(rd(q);q--;){
        rd(opt),rd(x),rd(y);
        if(opt==1)printf("%d\n",ask(x,y));
        else rd(v),upd(x,y,v);
    }
}
```

## GSS2

> 静态区间最大子段和,**相同的数只算一次**

难度激增

参考[\[SDOI2009\]HH的项链](https://www.luogu.com.cn/problem/P1972)的做法

GSS1的合并最大前缀和,最大子段和,最大后缀和的方法以不再适用

对每个位置$i$求出上一次出现相同数的位置$pre_i$

还是按照右端点排序,按顺序添加元素,添加$a_i$时,更新$[pre_i-1,i]$

线段树每个节点维护4个值,$sum,hismax,sumtag,hismaxtag$。

对于叶子节点:

$sum$表示从这个叶结点所对应的原序列的所有元素和

$hismax$表示$sum$的历史最大值（最小为0）

对于非叶子节点:

$sum$表示左右儿子的$sum$的最大值,

$hismax$表示左右儿子的$hismax$的最大值。

查询区间的$hismax$即可

特别注意`pushdown()`函数的更新顺序

```cpp
#include<bits/stdc++.h>
typedef long long ll;
template<class T>
void rd(T&x){char c;bool f=0;for(c=getchar();c<'0'||'9'<c;c=getchar())f^=c=='-';for(x=c-48,c=getchar();'0'<=c&&c<='9';x=x*10+c-48,c=getchar());if(f)x=-x;}
ll max(ll x,ll y){return x>y?x:y;}
void cmax(ll&x,ll y){if(x<y)x=y;}
const int N=100001;
int n,m,b[N<<1],pre[N];
ll a[N],ans[N];
struct node{ll s,hs,laz,hlaz;}s[N<<2];
node operator+(node a,node b){return {max(a.s,b.s),max(a.hs,b.hs),0,0};}
#define ls rt<<1
#define rs rt<<1|1
void pd(int rt){
    cmax(s[ls].hs,s[ls].s+s[rt].hlaz);
    cmax(s[rs].hs,s[rs].s+s[rt].hlaz);
    s[ls].s+=s[rt].laz;
    s[rs].s+=s[rt].laz;
    cmax(s[ls].hlaz,s[ls].laz+s[rt].hlaz);
    cmax(s[rs].hlaz,s[rs].laz+s[rt].hlaz);
    s[ls].laz+=s[rt].laz;
    s[rs].laz+=s[rt].laz;
    s[rt].laz=s[rt].hlaz=0;
}
void upd(int L,int R,ll v,int l,int r,int rt){
    if(L<=l&&r<=R){
        cmax(s[rt].hs,s[rt].s+=v);
        cmax(s[rt].hlaz,s[rt].laz+=v);
        return;
    }
    int m=l+r>>1;pd(rt);
    if(L<=m)upd(L,R,v,l,m,ls);
    if(R>m)upd(L,R,v,m+1,r,rs);
    s[rt]=s[ls]+s[rs];
}
node ask(int L,int R,int l,int r,int rt){
    if(L<=l&&r<=R)return s[rt];
    int m=l+r>>1;pd(rt);
    if(L>m)return ask(L,R,m+1,r,rs);
    else if(R<=m)return ask(L,R,l,m,ls);
    else return ask(L,R,l,m,ls)+ask(L,R,m+1,r,rs);
}
struct que{
    int l,r,id;
    bool operator<(que t){return r<t.r;}
}q[N];
int main(){
    rd(n);
    for(int i=1;i<=n;++i)
        rd(a[i]),
        pre[i]=b[a[i]+100000],
        b[a[i]+100000]=i;
    rd(m);
    for(int i=1;i<=m;++i)
        rd(q[i].l),rd(q[i].r),q[i].id=i;
    std::sort(q+1,q+m+1);
    for(int i=1,j=1;i<=n;++i){
        upd(pre[i]+1,i,a[i],1,n,1);
        for(;j<=m&&q[j].r<=i;++j)
            ans[q[j].id]+=ask(q[j].l,q[j].r,1,n,1).hs;
    }
    for(int i=1;i<=m;++i)
        printf("%lld\n",ans[i]);
}
```

## GSS4

> 区间开方(向下取整),区间求和

可以发现$10^{18}$次方最多开方$6$次就会变成$1$

那么每个数都在$6$次以内就会变成$1$,然后不变,所以最多修改$6\times10^5$次

打标记记录区间是否都是$1$,如果区间被标记,就不用向下继续

```cpp
#include<bits/stdc++.h>
const int N=100011;
typedef long long ll;
ll s[N<<2];
bool b[N<<2];
#define ls rt<<1
#define rs rt<<1|1
void pu(int rt){s[rt]=s[ls]+s[rs],b[rt]=b[ls]&b[rs];}
void build(int l,int r,int rt){
    if(l==r){
        scanf("%lld",s+rt);
        b[rt]=s[rt]<=1;
        return;
    }
    int m=l+r>>1;
    build(l,m,ls),build(m+1,r,rs);
    pu(rt);
}
void upd(int L,int R,int l,int r,int rt){
    if(b[rt])return;
    if(l==r){
        s[rt]=sqrt(s[rt]),
        b[rt]=s[rt]<=1;
        return;
    }
    int m=l+r>>1;
    if(L<=m)upd(L,R,l,m,ls);
    if(R>m)upd(L,R,m+1,r,rs);
    pu(rt);
}
ll ask(int L,int R,int l,int r,int rt){
    if(L<=l&&r<=R)return s[rt];
    int m=l+r>>1;
    return ((L<=m)?ask(L,R,l,m,ls):0)+((R>m)?ask(L,R,m+1,r,rs):0);
}
int main(){
    int n,q,opt,x,y,id=0;
    while(~scanf("%d",&n)){
        printf("Case #%d:\n",++id);
        build(1,n,1);
        scanf("%d",&q);
        while(q--){
            scanf("%d%d%d",&opt,&x,&y);
            if(x>y)x^=y,y^=x,x^=y;
            if(opt)printf("%lld\n",ask(x,y,1,n,1));
            else upd(x,y,1,n,1);
        }
    }
}
```

## GSS8

> 给你一个序列,$A[0], A[1]...A[N - 1]. (0 \le A[i] \lt 2^{32})$
> 
> 你需要支持$Q$次操作
> 
> 1. `I pos val` 插入一个数字在第$pos$个位置之前,$0 \le val \lt 2^{32}$, 如果$pos=current_length$,那么你需要将这个数字放到序列末尾
> 2. `D pos` 删除第$pos$个元素
> 3. `R pos val` 将第$pos$个元素变为$val(0 \le val \lt 2^{32})$
> 4. `Q l r k` 询问$(\sum\limits_{i=l}^{r} A[i] \cdot (i - l + 1) ^ k) \mod 2^{32}$,保证$0 \le k \le 10$
> 
> 第一行一个正整数 $n$,接下来一行 $n$ 个整数,表示 $a_0,a_1...a_{n-1}$。  
> 
> 第三行一个整数 $q$,表示操作个数。
> 
> 接下来 $q$ 行,每行表示一个操作。
> 
> 数据点保证：
> $1\le n \le 10^5,0 \le q \le 10^5$

平衡树

由于$0\le k \le 10$,可以用$ans_k$储存当前$k$的区间答案

考虑如何合并左右儿子区间($m=\left\lfloor\frac{l+r}2\right\rfloor$):

$$
\sum^r_{i=1}a_i(i-l+1)^k=\sum^m_{i=1}a_i(i-l+1)^k+\sum^r_{i=m+1}a_i(i-l+1)^k
\\ 
\begin{aligned}
\sum^r_{i=m+1}a_i(i-l+1)^k
&=\sum^r_{i=m+1}a_i[(m-l+1)-(i-m)]^k\\
&=\sum^r_{i=m+1}a_i \sum_{j=0}^k{k\choose j}(m-l+1)^{k-j}(i-m)^k\\
&=\sum_{j=0}^k{k\choose j}(m-l+1)^{k-j}\sum^r_{i=m+1}a_i(i-m)^k\\
&=\sum_{j=0}^k{k\choose j}(m-l+1)^{k-j} rans_j\\
\end{aligned}
\\
\sum^r_{i=1}a_i(i-l+1)^k=lans_k+\sum_{j=0}^k{k\choose j}(m-l+1)^{k-j} rans_j
$$

这样就可以方便地合并左右儿子区间了

```cpp
#include<bits/stdc++.h>
#define int unsigned int
int rd(){int x=0;char c;for(c=getchar();c<'0'||'9'<c;c=getchar());for(x=c-48,c=getchar();'0'<=c&&c<='9';x=x*10+c-48,c=getchar());return x;}
const int N=200001;
int RT,cnt,sz[N],v[N],rnd[N],c[2][N],s[N][11],C[11][11],pw[11];
#define ls c[0][x]
#define rs c[1][x]
void init(int x,int val){
    v[x]=val;
    for(int i=0;i<=10;++i)s[x][i]=val;
}
int ne(int val){
    init(++cnt,val),rnd[cnt]=rand(),sz[cnt]=1;
    return cnt;
}
void pu(int x){
    sz[x]=sz[ls]+1+sz[rs];
    for(int i=pw[0]=1;i<=10;++i)pw[i]=pw[i-1]*(sz[ls]+1);
    for(int k=0;k<=10;++k){
        s[x][k]=s[ls][k]+v[x]*pw[k];
        for(int j=0;j<=k;++j)
            s[x][k]+=C[k][j]*pw[k-j]*s[rs][j];
    }
}
void sl(int x,int k,int &a,int &b){
    if(!x){a=b=0;return;}
    if(sz[ls]>=k)b=x,sl(ls,k,a,ls);
    else a=x,sl(rs,k-sz[ls]-1,rs,b);
    pu(x);
}
int mg(int x,int y){
    if(!x||!y)return x|y;
    if(rnd[x]<rnd[y]){
        c[1][x]=mg(c[1][x],y);
        pu(x);return x;
    }
    else{
        c[0][y]=mg(x,c[0][y]);
        pu(y);return y;
    }
}
signed main(){
    srand(time(0));
    for(int i=C[0][0]=1;i<=10;++i)
        for(int j=C[i][0]=1;j<=i;++j)
            C[i][j]=C[i-1][j]+C[i-1][j-1];
    for(int n=rd();n--;)RT=mg(RT,ne(rd()));
    char opt;
    for(int q=rd(),x,y,z,l,r;q--;){
        while(isspace(opt=getchar()));
        if(opt=='I')
            sl(RT,rd(),x,z),
            RT=mg(x,mg(ne(rd()),z));
        else if(opt=='D')
            sl(RT,rd(),x,z),sl(z,1,y,z),
            RT=mg(x,z);
        else if(opt=='R')
            sl(RT,rd(),x,z),sl(z,1,y,z),
            init(y,rd()),
            RT=mg(x,mg(y,z));
        else if(opt=='Q')
            l=rd()+1,r=rd()+1,
            sl(RT,r,x,z),sl(x,l-1,x,y),
            printf("%u\n",s[y][rd()]),
            RT=mg(x,mg(y,z));
    }
}
```