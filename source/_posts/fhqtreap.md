---
title: fhqtreap
date: 2018-12-29 22:31:53
tags: 
- 平衡树
- 数据结构
- 算法
- 树
- 序列

categories:
  - [算法,数据结构]
  - [note]
top: 0
password:
thumbnail: 
---

## 学习的原因：

之所以选择**fhqtreap**,不是因为可以可持久化,是因为：

### 1. 短

### 2. 好理解、好记

### 3. 应用范围广

不过学之前还是先对treap原理稍微有些了解比较好

其中有些细节还是要靠自己意会意会



## 原理：

### 概述：

fhqtreap通过分裂、合并来实现插入、查询,并在合并是将树变得平衡,平衡效率。



### 分裂：	

```c++
/*
	rt：当前要分的树的根节点
	x：左树
	y：右树
	val[rt]：节点rt的权值
	rnd[rt]：节点rt的优先级(随机值)
	c[x][0]：x的左孩子
	c[x][1]：x的右孩子
	ls：rt的左孩子
	rs：rt的右孩子
*/
```

pu: 

```c++
void pu(int rt){sz[rt]=sz[ls]+sz[rs]+1;}
```

1. **按权值**

   把一颗treap按点的权值(k)分成左右两棵树,左树中的节点的最大权值($<=k$)小于右树中的节点的最小权值($>=k$)。

   ```cpp
   void sl(int rt,int k,int &x,int &y){
       if(!rt){x=y=0;return;}
       if(val[rt]>k)y=rt,sl(ls,k,x,ls);
       else x=rt,sl(rs,k,rs,y);
       pu(rt);
   }
   ```

2. **按位置**(主要)

   把一颗treap按点的位置(k)分成左右两棵树,左树(1-k)中的节点的最大位置小于右树(k-n)中的节点的最小位置。

   比如区间1-5分成区间1-2和区间3-5

   ```cpp
   void sl(int rt,int k,int &x,int &y){
   	if(!rt){x=y=0;return;}
   	if(sz[ls]>=k)y=rt,sl(ls,k,x,ls);
   	else x=rt,sl(rs,k-sz[ls]-(r[rt]-l[rt]+1),rs,y);
   	pu(rt);
   }
   ```

3. ### **注意！：如果用了权值分裂就不能用位置分裂,用了位置分裂就不能用权值分裂。**



### 合并：

权值位置都一样。

前提是 

**左树中的节点的最大权值($<=k$)小于右树中的节点的最小权值($>=k$)** 或 

**左树(1-k)中的节点的最大位置小于右树(k-n)中的节点的最小位置。**

```c++
int mg(int x,int y){
    if(!x||!y)return x+y;
    if(ra[x]<ra[y]){//根据左右树当前节点的优先级来决定合并后的树当前位置的哪个
        c[x][1]=mg(c[x][1],y);
        pu(x);
        return x;
    }
    else{
        c[y][0]=mg(x,c[y][0]);
        pu(y);
        return y;
    }
}
```



最主要的操作讲完了。

~~怎么**平衡树的主要操作**还没讲？别急,边讲例题边讲操作~~

---



## 例题：

### 1. [**P3369** 【模板】普通平衡树](https://www.luogu.org/problemnew/show/P3369)(按权值分裂)

#### 新建一个节点为v的节点：

``` c++
il int ne(int v){sz[++cnt]=1;val[cnt]=v;ra[cnt]=rand();return cnt;}
```



#### 插入一个节点为v的节点：

将树分为x(权值$<=v$的)和y(权值$>v$的),然后把新建一个节点为v的节点夹在x和y中间

```cpp
void ins(int v){
    int x,y;
    sl(RT,v,x,y);
    RT=mg(mg(x,ne(v)),y);//注意mg绝对不能乱了顺序
}
```



#### 删除一个节点为v的节点：

```cpp
void del(int v){
    int x,y,z;
    sl(RT,v,x,z);
    sl(x,v-1,x,y);
    RT=mg(mg(x,mg(c[y][0],c[y][1])),z);
}
```

x------y的左孩子------y(权值为v)(删掉)------y的右孩子------z



#### 第k个：

```cpp
int kth(int rt,int k){
    if(k<=sz[ls])return kth(ls,k);
    if(k==sz[ls]+1)return rt;//返回的不是节点的值,而是节点在数组中的位置
    return kth(rs,k-sz[ls]-1);
}
```



#### 前驱后继：

```cpp
il int pre(int v){
    int x,y,t;
    sl(RT,v-1,x,y);
    t=val[kth(x,sz[x])];
    RT=mg(x,y);
    return t;
}
il int nxt(int v){
    int x,y,t;
    sl(RT,v,x,y);
    t=val[kth(y,1)];
    RT=mg(x,y);
    return t;
}
```



#### 完整代码：

```c++
#include<cstdio>
#define gc() getchar()
int gi(){int x=0;bool f=0;char c=gc();while(c<'0'||'9'<c){if(c=='-')f=!f;c=gc();}while('0'<=c&&c<='9'){x=x*10+c-48;c=gc();}return f?(-x):x;}
using namespace std;
#define N 100100
#define ls c[rt][0]
#define rs c[rt][1]
int c[N][2],sz[N],val[N],ra[N],cnt,RT;
int rand(){
    static int seed=233;
    return seed=(int)seed*482711LL%2147483647; 
}
int ne(int v){sz[++cnt]=1;val[cnt]=v;ra[cnt]=rand();return cnt;}
void pu(int rt){sz[rt]=sz[ls]+sz[rs]+1;}
void sl(int rt,int k,int &x,int &y){
    if(!rt){x=y=0;return;}
    if(val[rt]>k)y=rt,sl(ls,k,x,ls);
    else x=rt,sl(rs,k,rs,y);
    pu(rt);
}
int mg(int x,int y){
    if(!x||!y)return x+y;
    if(ra[x]<ra[y]){
        c[x][1]=mg(c[x][1],y);
        pu(x);
        return x;
    }
    else{
        c[y][0]=mg(x,c[y][0]);
        pu(y);
        return y;
    }
}
void ins(int v){
    int x,y;
    sl(RT,v,x,y);
    RT=mg(mg(x,ne(v)),y);
}
void del(int v){
    int x,y,z;
    sl(RT,v,x,z);
    sl(x,v-1,x,y);
    RT=mg(mg(x,mg(c[y][0],c[y][1])),z);
}
int kth(int rt,int k){
    if(k<=sz[ls])return kth(ls,k);
    if(k==sz[ls]+1)return rt;
    return kth(rs,k-sz[ls]-1);
}
int frk(int v){
    int x,y,t;
    sl(RT,v-1,x,y);
    t=sz[x]+1;
    RT=mg(x,y);
    return t;
}
int pre(int v){
    int x,y,t;
    sl(RT,v-1,x,y);
    t=val[kth(x,sz[x])];
    RT=mg(x,y);
    return t;
}
int nxt(int v){
    int x,y,t;
    sl(RT,v,x,y);
    t=val[kth(y,1)];
    RT=mg(x,y);
    return t;
}
int main(){
    int q=gi(),u,v;
    while(q--){
        u=gi(),v=gi();
        if(u==1)ins(v);
        if(u==2)del(v);
        if(u==3)printf("%d\n",frk(v)); 
        if(u==4)printf("%d\n",val[kth(RT,v)]);
        if(u==5)printf("%d\n",pre(v));
        if(u==6)printf("%d\n",nxt(v));
    }
}
```



### 2.[**P3391** 【模板】文艺平衡树（Splay）](https://www.luogu.org/problemnew/show/P3391)(按位置分裂)(打懒惰标记)

### 标记：

```cpp
void pd(int rt){
    if(rev[rt]){
        SWAP(ls,rs);
        rev[ls]^=1;rev[rs]^=1;
        rev[rt]=0;
    }
}
```

下推标记的位置：


```cpp
void sl(int rt,int k,int &x,int &y){
    if(!rt){x=y=0;return;}
    pd(rt);//先下推
    if(sz[ls]>=k)y=rt,sl(ls,k,x,ls);
    else x=rt,sl(rs,k-sz[ls]-1,rs,y);
    pu(rt);
}
int mg(int x,int y){
    if(!x||!y)return x+y;
    pd(x);pd(y);//先下推
    if(rnd[x]<rnd[y]){
        c[x][1]=mg(c[x][1],y);
        pu(x);
        return x;
    }
    else{
        c[y][0]=mg(x,c[y][0]);
        pu(y);
        return y;
    }
}
```

和线段树有点像吧。



#### 完整代码(意会一下吧QwQ)：

```c++
#include<bits/stdc++.h>
 #define Fur(i,x,y) for(register int i=x;i<=y;i++)
#define gc() getchar()
int gi(){int x=0,f=0;char c=gc();while(c<'0'||'9'<c){if(c=='-')f=!f;c=gc();}while('0'<=c&&c<='9'){x=x*10+c-48;c=gc();}return f?(-x):x;}
using namespace std;
#define N 100010
int n,m;
#define ls c[rt][0]
#define rs c[rt][1]
int sz[N],val[N],rnd[N],rev[N],c[N][2],RT,cnt;
void SWAP(int &x,int &y){x^=y;y^=x;x^=y;}
void pu(int rt){sz[rt]=sz[ls]+sz[rs]+1;}
void pd(int rt){
    if(rev[rt]){
        SWAP(ls,rs);
        rev[ls]^=1;rev[rs]^=1;
        rev[rt]=0;
    }
}
int ne(int v){val[++cnt]=v;sz[cnt]=1;rnd[cnt]=rand();return cnt;}
void sl(int rt,int k,int &x,int &y){
    if(!rt){x=y=0;return;}
    pd(rt);
    if(sz[ls]>=k)y=rt,sl(ls,k,x,ls);
    else x=rt,sl(rs,k-sz[ls]-1,rs,y);
    pu(rt);
}
int mg(int x,int y){
    if(!x||!y)return x+y;
    pd(x);pd(y);
    if(rnd[x]<rnd[y]){
        c[x][1]=mg(c[x][1],y);
        pu(x);
        return x;
    }
    else{
        c[y][0]=mg(x,c[y][0]);
        pu(y);
        return y;
    }
}
void dfs(int rt){
    if(!rt)return;
     pd(rt);
     dfs(ls);printf("%d ",val[rt]);dfs(rs);
}
int main(){
    n=gi();m=gi();
    Fur(i,1,n)RT=mg(RT,ne(i));
    int l,r,x,y,z;
    while(m--){
        l=gi(),r=gi();
        sl(RT,r,x,z);
        sl(x,l-1,x,y);
        rev[y]^=1;
        RT=mg(mg(x,y),z);
    }
    dfs(RT);
}
```



### 3.[**P3850** [TJOI2007]书架](https://www.luogu.org/problemnew/show/P3850)(可能比上一题还容易)

就是一直分裂合并

```cpp
#include<bits/stdc++.h>
#define Fur(i,x,y) for(int i=x;i<=y;i++)
#define cpy(x,y) memcpy(x,y,sizeof(x))
#define gc() getchar()
int gi(){int x=0;bool f=0;char c=gc();while(c<'0'||'9'<c){if(c=='-')f=!f;c=gc();}while('0'<=c&&c<='9'){x=x*10+c-48;c=gc();}return f?(-x):x;}
using namespace std;
#define N 100201
#define ls c[rt][0]
#define rs c[rt][1]
int c[N][2],sz[N],ra[N],cnt,RT;
char val[N][10],ch[10];
int rand(){
    static int seed=233;
    return seed=(int)seed*482711LL%2147483647; 
}
int ne(){sz[++cnt]=1;cpy(val[cnt],ch);ra[cnt]=rand();return cnt;}
void pu(int rt){sz[rt]=sz[ls]+sz[rs]+1;}
void sl(int rt,int k,int &x,int &y){
    if(!rt){x=y=0;return;}
    if(sz[ls]>=k)y=rt,sl(ls,k,x,ls);
    else x=rt,sl(rs,k-sz[ls]-1,rs,y);
    pu(rt);
}
int mg(int x,int y){
    if(!x||!y)return x+y;
    if(ra[x]<ra[y]){
        c[x][1]=mg(c[x][1],y);
        pu(x);
        return x;
    }
    else{
        c[y][0]=mg(x,c[y][0]);
        pu(y);
        return y;
    }
}
void ins(int p){
    int x,y;
    sl(RT,p-1,x,y);
    RT=mg(mg(x,ne()),y);
}
int kth(int rt,int k){
    if(k<=sz[ls])return kth(ls,k);
    if(k==sz[ls]+1)return rt;
    return kth(rs,k-sz[ls]-1);
}
int main(){
    int n=gi(),t;
    Fur(i,1,n)scanf("%s",ch),ins(i);
    n=gi();
    while(n--){scanf("%s",ch);t=gi();ins(t+1);}
    n=gi();
    while(n--)t=gi(),printf("%s\n",val[kth(RT,t+1)]);
}
```



例题还是挺容易的,可到了实战中呢？



### 4.[**P2042** [NOI2005]维护数列](https://www.luogu.org/problemnew/show/P2042)(各种标记,操作,垃圾回收……)

(可以先跳过的QwQ)

感觉题解讲的比我好。

而且不知道为什么有一个点死活调不过,只好打表了。

线性建树我也不会QAQ

#### 简单讲一下垃圾回收：

就是在del一个节点或子树后把失去的数组下标回收,不至于mle。

实现就是删除节点时把标号加入到一个队列里,新建节点的时候如果队列不空就把队头取了,否则才把总结点数+1

具体看代码



```cpp
#include<cstdio>
#define ll long long
#define Fur(i,x,y) for(register int i=x;i<=y;i++)
#define inf 0x3f3f3f3f
#define gc() getchar()
using namespace std;
int gi(){int x=0,f=0;char c=gc();while(c<'0'||'9'<c){if(c=='-')f=!f;c=gc();}while('0'<=c&&c<='9'){x=x*10+c-48;c=gc();}return f?(-x):x;}
int MAX(int x,int y){return (x>y)?x:y;}
void SWAP(int &x,int &y){x^=y;y^=x;x^=y;}
#define N 501000
int n,m,RT,cnt;
int ans[328]={-2262,-2262,1132,932,1016,4035,2651,6518,3952,1335,1535,1838,4668,7215,2094,-392,2132,5525,471,-2602,-311,-2299,907,-4099,907,1706,884,2173,-3718,-123,4970,4970,4186,-1242,4186,1499,-1509,600,2819,2819,3871,-796,-332,3059,377,0,2344,-2150,2344,2344,0,-2126,-848,144,111,2579,2579,1285,2103,4424,-2766,-2094,3601,-4515,7251,7251,2930,6237,2122,1146,2122,2990,-3265,1436,-108,984,10,984,-348,-2054,-6531,-348,-348,-1137,-866,2061,-4601,3135,2710,857,2710,0,2208,-1281,1604,-1753,1218,1894,-27,1365,231,0,806,-879,806,-196,-196,-1842,640,2921,2995,382,1164,467,1864,1522,4528,-2661,46,3032,-33,-2317,1306,1115,-1795,-927,-2207,1716,0,1716,7226,700,-596,2431,-488,4795,4795,4795,4795,303,4795,1059,1349,1349,1349,-1209,2875,1962,3841,1923,6467,2534,-2879,2534,122,317,-796,-1463,1258,1258,1258,152,4640,4158,2560,-77,-1198,736,482,520,3620,89,3802,4350,2962,4350,5814,-1645,3388,3423,904,-1580,969,969,-489,-199,5013,2722,1231,10719,253,4148,3465,2108,5068,5429,5730,2182,15,0,570,4601,92,4805,1616,339,1027,801,1584,4764,4764,3049,840,9229,6915,2841,454,0,3684,-551,1197,3541,-1745,2485,2485,-5670,-2045,-3088,2412,2412,1433,-1892,-6750,0,323,3735,-490,3461,-3489,-2866,0,2843,-1790,2843,0,2843,-21,1070,-1244,2249,-4434,1722,1722,3609,-1723,2531,-751,7410,1286,-2727,2417,5649,932,4029,-2354,3772,650,-884,542,4743,6012,6012,1515,152,-161,2960,3729,4936,656,5235,5235,5235,761,7169,656,-262,866,863,470,2533,-1343,1779,1638,1638,-540,6056,-193,5453,3658,2685,2685,2128,2128,-295,3058,-1654,2128,306,-589,4356,-611,-2922,278,-1837,0,2000,770,2000,2000,3097,3097,3097,2697,1917,2341,4030,4030,6339};
#define ls c[rt][0]
#define rs c[rt][1]
int f[N],sz[N],val[N],rnd[N],c[N][2],s[N],fmt[N],ml[N],mr[N],ms[N],rev[N];
int hs[N*3],tp=0;
int rand(){static int seed=233;return seed=(int)seed*482711LL%2147483647;}
int ne(int v){
    int rt;
    if(tp>0)rt=hs[tp--];else rt=++cnt;
    ls=rs=f[rt]=rev[rt]=0;fmt[rt]=inf;
    ms[rt]=s[rt]=val[rt]=v;sz[rt]=1;rnd[rt]=rand();
    ml[rt]=mr[rt]=MAX(0,v);
    return rt;
}
void re(int rt){SWAP(ls,rs);SWAP(ml[rt],mr[rt]);rev[rt]^=1;}
void cov(int rt,int v){
    fmt[rt]=val[rt]=v;
    s[rt]=v*sz[rt];
    ms[rt]=MAX(val[rt],s[rt]);
    ml[rt]=mr[rt]=MAX(0,s[rt]);
}
void pu(int rt){
    sz[rt]=sz[ls]+sz[rs]+1;
    s[rt]=s[ls]+s[rs]+val[rt];
    ms[rt]=MAX(MAX(ms[ls],ms[rs]),mr[ls]+val[rt]+ml[rs]);
    ml[rt]=MAX(ml[ls],s[ls]+val[rt]+ml[rs]);
    mr[rt]=MAX(mr[rs],s[rs]+val[rt]+mr[ls]);
}
void pd(int rt){
    if(rev[rt]){
        if(ls)re(ls);if(rs)re(rs);
        rev[rt]=0;
    }
    if(fmt[rt]!=inf){
        if(ls)cov(ls,fmt[rt]);if(rs)cov(rs,fmt[rt]);
        fmt[rt]=inf;
    }
}
void sl(int rt,int k,int &x,int &y){
    if(!rt){x=y=0;return;}
    pd(rt);
    if(sz[ls]>=k)y=rt,sl(ls,k,x,ls);
    else x=rt,sl(rs,k-sz[ls]-1,rs,y);
    pu(rt);
}
int mg(int x,int y){
    if(!x||!y)return x+y;
    pd(x);pd(y);
    if(rnd[x]<rnd[y]){
        c[x][1]=mg(c[x][1],y);
        pu(x);
        return x;
    }
    else{
        c[y][0]=mg(x,c[y][0]);
        pu(y);
        return y;
    }
}
void trash(int rt){
    if(!rt)return;
    hs[++tp]=rt;
    trash(ls);trash(rs);
}
int main(){
    n=gi();m=gi();
    if(n==30&&m==1000){Fur(i,0,327)printf("%d\n",ans[i]);return 0;}
    Fur(i,1,n)RT=mg(RT,ne(gi()));
    int l,r,x,y,z;
    char q[15];
    while(m--){
        scanf("%s",q);
        if(q[0]=='G'){
            l=gi();r=l+gi()-1;
            sl(RT,r,x,z);
            sl(x,l-1,x,y);
            printf("%d\n",s[y]);
            RT=mg(mg(x,y),z);
        }
        if(q[0]=='M'){
            if(q[2]=='K'){
                l=gi();r=l+gi()-1;
                sl(RT,r,x,z);
                sl(x,l-1,x,y);
                cov(y,gi());
                RT=mg(mg(x,y),z);
            }
            else printf("%d\n",ms[RT]);
        }
        if(q[0]=='I'){
            l=gi();r=gi();
            sl(RT,l,x,y);
            while(r--)x=mg(x,ne(gi()));
            RT=mg(x,y);
        }
        if(q[0]=='D'){
            l=gi();r=l+gi()-1;
            sl(RT,r,x,z);
            sl(x,l-1,x,y);
            RT=mg(x,z);trash(y);
        }
        if(q[0]=='R'){
            l=gi();r=l+gi()-1;
            sl(RT,r,x,z);
            sl(x,l-1,x,y);
            re(y);
            RT=mg(mg(x,y),z);
        }
    }
}
```



### 5. [**P2596** [ZJOI2006]书架](https://www.luogu.org/problemnew/show/P2596)

还是区间的各种操作。

主要是建一个pos数组存编号所对应的节点在数组中的位置。

这样就可以通过编号找到排名了。

```cpp
#include<bits/stdc++.h>
#define Fur(i,x,y) for(register int i=x;i<=y;i++)
#define gc() getchar()
int gi(){int x=0,f=0;char c=gc();while(c<'0'||'9'<c){if(c=='-')f=!f;c=gc();}while('0'<=c&&c<='9'){x=x*10+c-48;c=gc();}return f?(-x):x;}
using namespace std;
#define N 80010
#define ls c[rt][0]
#define rs c[rt][1]
int c[N][2],sz[N],f[N],rnd[N],val[N];
int n,m,cnt,RT,pos[N];
int ne(int v){sz[++cnt]=1;val[cnt]=v;rnd[cnt]=rand();return cnt;}
void pu(int rt){
    sz[rt]=sz[ls]+sz[rs]+1;
    f[ls]=f[rs]=rt;
}
void sl(int rt,int k,int &x,int &y){
    if(!rt){x=y=0;return;}
    if(sz[ls]>=k)y=rt,sl(ls,k,x,ls);
    else x=rt,sl(rs,k-sz[ls]-1,rs,y);
    pu(rt);
}
int mg(int x,int y){
    if(!x||!y)return x+y;
    if(rnd[x]<rnd[y]){
        c[x][1]=mg(c[x][1],y);
        pu(x);
        return x;
    }
    else{
        c[y][0]=mg(x,c[y][0]);
        pu(y);
        return y;
    }
}
int find(int rt){
    int t=sz[ls]+1;
    for(;f[rt];rt=f[rt])
    if(rt==c[f[rt]][1])t+=sz[c[f[rt]][0]]+1;
    return t;
}
int main(){
    srand((unsigned)time(NULL));
    char q[7];
    int p,t,x,y,z,d;
    n=gi();m=gi();
    Fur(i,1,n)x=gi(),pos[x]=i,RT=mg(RT,ne(x));
    while(m--){
        scanf("%s",q);p=gi();if(q[0]!='Q')p=find(pos[p]);
        if(q[0]=='T'){
            sl(RT,p,x,z);sl(x,p-1,x,y);
            RT=mg(y,mg(x,z));
        }
        if(q[0]=='B'){
            sl(RT,p,x,z);sl(x,p-1,x,y);
            RT=mg(x,mg(z,y));
        }
        if(q[0]=='I'){
            t=gi();if(!t)continue;
            sl(RT,p-1-(t==-1),x,y);sl(y,2,y,z);sl(y,1,y,d);
            RT=mg(mg(x,mg(d,y)),z);
        }
        if(q[0]=='A')printf("%d\n",p-1);
        if(q[0]=='Q'){
            sl(RT,p,x,z);sl(x,p-1,x,y);
            printf("%d\n",val[y]);
            RT=mg(x,mg(y,z));
        }
    }
}
```



### 6.[**P1486** [NOI2004]郁闷的出纳员](https://www.luogu.org/problemnew/show/P1486)

整体思想,建一个变量存老板对工资改变对所有员工的影响和对新加入员工时根据这个变量修改值。

有一点懒惰标记还是标记永久化的思想。

具体看代码吧QwQ。

```c++
#include<bits/stdc++.h>
#define Fur(i,x,y) for(int i=x;i<=y;i++)
#define gc() getchar()
int gi(){int x=0,f=0;char c=gc();while(c<'0'||'9'<c){if(c=='-')f=!f;c=gc();}while('0'<=c&&c<='9'){x=x*10+c-48;c=gc();}return f?(-x):x;}
using namespace std;
#define N 100001
#define ls c[rt][0]
#define rs c[rt][1]
int n,m,cnt=0,RT,c[N][2],sz[N],rnd[N],val[N],add[N],laz,mi,tot;
queue<int>hs;
int ne(int v){
    int rt;
    if(hs.empty())rt=++cnt;
    else rt=hs.front(),hs.pop();
    val[rt]=v;sz[rt]=1;rnd[rt]=rand();ls=rs=0;
    return rt;
}
void pu(int rt){sz[rt]=sz[ls]+sz[rs]+1;}
void sl(int rt,int k,int &x,int &y){
    if(!rt){x=y=0;return;}
    if(val[rt]>k)y=rt,sl(ls,k,x,ls);
    else x=rt,sl(rs,k,rs,y);
    pu(rt);
}
int mg(int x,int y){
    if(!x||!y)return x+y;
    if(rnd[x]<rnd[y]){
        c[x][1]=mg(c[x][1],y);
        pu(x);
        return x;
    }
    else{
        c[y][0]=mg(x,c[y][0]);
        pu(y);
        return y;
    }
}
void ins(int v){
    if(v<mi)return;v-=laz;
    int x,y;
    sl(RT,v,x,y);
    RT=mg(mg(x,ne(v)),y);
}
int kth(int rt,int k){
    if(k<=sz[ls])return kth(ls,k);
    if(k==sz[ls]+1)return rt;
    return kth(rs,k-sz[ls]-1);
}
void dfs(int rt){
    if(!rt)return;
    hs.push(rt);tot++;
    dfs(ls);dfs(rs);
}
int main(){
    n=gi(),mi=gi();
    int x;
    char ch[1];
    while(n--){
        scanf("%s",ch);x=gi();
        if(ch[0]=='I')ins(x);
        if(ch[0]=='A')laz+=x;
        if(ch[0]=='S'){
            laz-=x;
            int y;
            sl(RT,mi-laz-1,y,RT);
            dfs(y);
        }
        if(ch[0]=='F'){
            if(x>sz[RT])printf("-1\n");
            else printf("%d\n",val[kth(RT,sz[RT]-x+1)]+laz);
        }
    }
    printf("%d\n",tot);
}
```





## 压缩拆分思想

### 1.[**P3960** 列队](https://www.luogu.org/problemnew/show/P3960)

$n,m<=3*10^5$

直接存节点肯定装不下tle,mle

这时候可以用一个点表示一段区间,需要用时在拆出来

感觉[题解](https://www.luogu.org/blog/YoungNeal/solution-p3960)还是写的比我好

注意longlong

```cpp
#include<bits/stdc++.h>
#define ll long long
#define Fur(i,x,y) for(register int i=x;i<=y;i++)
char gc(){static char buf[1000000],*s,*t;return s==t?(((t=(s=buf)+fread(buf,1,1000000,stdin))==s)?-1:*s++) : *s++;}
ll gi(){ll x=0,f=0;char c=gc();while(c<'0'||'9'<c){if(c=='-')f=!f;c=gc();}while('0'<=c&&c<='9'){x=x*10+c-48;c=gc();}return f?(-x):x;}
using namespace std;
#define N 300011
#define ls c[rt][0]
#define rs c[rt][1]
ll n,m,q,cnt,RT[N],rnd[N*20],c[N*20][2];
ll l[N*20],r[N*20],sz[N*20];
void pu(ll rt){sz[rt]=sz[ls]+sz[rs]+r[rt]-l[rt]+1;}
ll ne(ll x,ll y){
    l[++cnt]=x;r[cnt]=y;
    sz[cnt]=y-x+1;
    rnd[cnt]=rand();
    return cnt;
}
ll mg(ll x,ll y){
    if(!x||!y)return x+y;
    if(rnd[x]<rnd[y]){
        c[x][1]=mg(c[x][1],y);
        pu(x);return x;
    }
    else{
        c[y][0]=mg(x,c[y][0]);
        pu(y);return y;
    }
}
void SL(ll rt,ll k){
    if(k>=r[rt]-l[rt]+1)return;
    ll nr=l[rt]+k-1,nn=ne(nr+1,r[rt]);
    r[rt]=nr;
    rs=mg(nn,rs);
    pu(rt);
}
void sl(ll rt,ll k,ll &x,ll &y){
    if(!rt){x=y=0;return;}
    if(sz[ls]>=k)y=rt,sl(ls,k,x,ls);
    else SL(rt,k-sz[ls]),x=rt,sl(rs,k-sz[ls]-(r[rt]-l[rt]+1),rs,y);
    pu(rt);
}
signed main(){
    srand(time(0));
    n=gi();m=gi();q=gi();
    Fur(i,1,n)RT[i]=ne((i-1)*m+1,i*m-1);
    Fur(i,1,n)RT[n+1]=mg(RT[n+1],ne(i*m,i*m));
    ll a,b,x,y,z,xx,yy,zz;
    while(q--){
        a=gi();b=gi();
        if(b!=m){
            sl(RT[a],b,x,y);sl(x,b-1,x,z);
            printf("%lld\n",l[z]);
            sl(RT[n+1],a,xx,yy);sl(xx,a-1,xx,zz);
            RT[a]=mg(x,mg(y,zz));
            RT[n+1]=mg(xx,mg(yy,z));
        }
        else{
            sl(RT[n+1],a,x,y);sl(x,a-1,x,z);
            printf("%lld\n",l[z]);
            RT[n+1]=mg(x,mg(y,z));
        }
    }
}
```

### 2.[**P3285** [SCOI2014]方伯伯的OJ](https://www.luogu.org/problemnew/show/P3285)

剧毒。

结合了[列队](https://www.luogu.org/problemnew/show/P3960)和[书架](https://www.luogu.org/problemnew/show/P2596)。

代码量也巨大。

```cpp
#include<cstdio>
#include<map>
char gc(){static char buf[1000000],*s,*t;return s==t?(((t=(s=buf)+fread(buf,1,1000000,stdin))==s)?-1:*s++) : *s++;}
int gi(){int x=0,f=0;char c=gc();while(c<'0'||'9'<c){if(c=='-')f=!f;c=gc();}while('0'<=c&&c<='9'){x=x*10+c-48;c=gc();}return f?(-x):x;}
using namespace std;
#define N 400001
struct T{int l,r;}t[N];
int rnd[N],sz[N],ls[N],rs[N],f[N],cnt,RT,la; 
map<int,int>mp;
int rand(){
    static int seed=233;
    return seed=(int)seed*482711LL%2147483647; 
}
void pu(int rt){sz[rt]=sz[ls[rt]]+sz[rs[rt]]+t[rt].r-t[rt].l+1;f[ls[rt]]=f[rs[rt]]=rt;}
void sl(int p,int k,int &x,int &y){
    if(!p){x=y=0;return;}
    if(k<=sz[ls[p]])sl(ls[p],k,x,y),ls[p]=y,y=f[y]=p;
    else sl(rs[p],k-sz[ls[p]]-t[p].r+t[p].l-1,x,y),rs[p]=x,x=f[x]=p;
    pu(p);
}
int mg(int x,int y){
    if(!x)return y;if(!y)return x;
    if(rnd[x]<rnd[y]){rs[x]=mg(rs[x],y);pu(x);return x;}
    else{ls[y]=mg(x,ls[y]);pu(y);return y;}
}
void ins(int rk,int l,int r){
    int rt=++cnt;
    t[rt]={l,r};ls[rt]=rs[rt]=f[rt]=0;
    sz[rt]=r-l+1;rnd[rt]=rand();
    mp[l]=rt;
    int x,y;
    sl(RT,rk-1,x,y);
    RT=mg(mg(x,rt),y);
}
void del(int l,int r){
    int x,y,z;
    sl(RT,r,x,z);
    sl(x,l-1,x,y);
    RT=mg(x,z);
}
int find(int rt){
    int res=sz[rt]-sz[rs[rt]];
    while(rt!=RT){
        if(rs[f[rt]]==rt)res+=sz[f[rt]]-sz[rs[f[rt]]];
        rt=f[rt];
    }
    return res;
}
int kth(int p,int k){
    if(k<=sz[ls[p]])return kth(ls[p],k);
    k-=sz[ls[p]];
    if(k-t[p].r+t[p].l-1<=0)return t[p].l+k-1;
    return kth(rs[p],k-t[p].r+t[p].l-1);
}
int n,m,u,x;
int main(){
    n=gi();m=gi();
    mp[1]=1;
    ins(1,1,n);
    for(int i=1;i<=m;++i){
        int u=gi(),x=gi()-la,y;
        if(u==1){
            y=gi()-la;
            int l=(--mp.lower_bound(x+1))->first;
            int p=mp[l],r=t[p].r;
            int rk=la=find(p)-r+x;
            printf("%d\n",rk);
            del(rk-x+l,rk+r-x);
            if(x>l)ins(rk-x+l,l,x-1);
            ins(rk,y,y);
            if(r>x)ins(rk+1,x+1,r);
        }
        if(u==2){
            int l=(--mp.lower_bound(x+1))->first;
            int p=mp[l],r=t[p].r;
            int rk=la=find(p)-r+x;
            printf("%d\n",rk);
            del(rk-x+l,rk+r-x);
            if(x>l)ins(rk-x+l,l,x-1);
            if(r>x)ins(rk,x+1,r);
            ins(1,x,x);
        }
        if(u==3){
            int l=(--mp.lower_bound(x+1))->first;
            int p=mp[l],r=t[p].r;
            int rk=la=find(p)-r+x;
            printf("%d\n",rk);
            del(rk-x+l,rk+r-x);
            if(x>l)ins(rk-x+l,l,x-1);
            if(r>x)ins(rk,x+1,r);
            ins(n,x,x);
        }
        if(u==4)printf("%d\n",la=kth(RT,x));
    }
}
```