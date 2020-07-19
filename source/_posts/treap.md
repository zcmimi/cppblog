---
title: treap
copyright: true
permalink: 
top: 0
date: 2018-12-01 21:10:58
tags: 
  - 平衡树
  - 数据结构
  - 算法
categories: 
  - [算法,数据结构]
  - [note]
password:
---

https://www.luogu.org/problemnew/show/P3369

最短（最简洁）代码：

```
解释：
turn(x,p):
	将x的左(p=0)/右(p=1)儿子旋转到x的头顶(变成x的父亲)
```

![](https://i.loli.net/2018/12/05/5c07efc526458.png)
![](https://i.loli.net/2018/12/05/5c07efc536041.png)
![](https://i.loli.net/2018/12/05/5c07efc54a39b.png)

这样一看旋转的操作应该很好理解吧？

因为网上其他地方的讲解都很详细,我在这里就只给好打好理解的代码了。



```c++
#include<cstdio>
#define il inline
#define inf 10000010
il char gc(){static char buf[1000000],*s,*t;return s==t?(((t=(s=buf)+fread(buf,1,1000000,stdin))==s)?-1:*s++) : *s++;}
il int gi(){int x=0;bool f=0;char c=gc();while(c<'0'||'9'<c){if(c=='-')f=!f;c=gc();}while('0'<=c&&c<='9'){x=x*10+c-48;c=gc();}return f?(-x):x;}
il int MAX(int x,int y){return x>y?x:y;}
il int MIN(int x,int y){return x<y?x:y;}
using namespace std;
#define N 100001
int sz[N],c[N][2],ra[N],w[N],cnt=0,rt=0;
#define pu(x) sz[x]=sz[c[x][0]]+sz[c[x][1]]+1
il int rand(){
    static int seed=233;
    return seed=(int)seed*482711LL%2147483647; 
}
il void turn(int &x,int p){
    int t=c[x][p];
    c[x][p]=c[t][!p];
    c[t][!p]=x;
    pu(x);pu(x=t);
}
il void ins(int &x,int v){
    if(!x){
        sz[x=++cnt]=1;w[x]=v;ra[x]=rand();
        return;
    }
    sz[x]++;
    int p=(v>w[x]);
    ins(c[x][p],v);
    if(ra[c[x][p]]<ra[x])turn(x,p);
}
il void del(int &x,int v){
    if(w[x]==v){
        if((!c[x][0])||(!c[x][1])){x=c[x][0]+c[x][1];return;}
        int p=(ra[c[x][0]]>ra[c[x][1]]);
        turn(x,p);del(c[x][!p],v);
    }
    else del(c[x][v>=w[x]],v);
    pu(x);
}
il int frk(int x,int v){
    if(!x)return 1;
    return (w[x]>=v)?frk(c[x][0],v):(frk(c[x][1],v)+sz[c[x][0]]+1);
}
il int ask(int x,int k){
    if(sz[c[x][0]]==k-1)return w[x];
    return (sz[c[x][0]]>=k)?ask(c[x][0],k):ask(c[x][1],k-sz[c[x][0]]-1);
}
il int pre(int x,int v){
    if(!x)return -inf;
    return (w[x]<v)?MAX(w[x],pre(c[x][1],v)):pre(c[x][0],v);
}
il int nxt(int x,int v){
    if(!x)return inf;
    return (w[x]>v)?MIN(w[x],nxt(c[x][0],v)):nxt(c[x][1],v);
}
int main(){
    int t=gi(),x,y;
    while(t--){
        x=gi();y=gi();
        if(x==1)ins(rt,y);
        if(x==2)del(rt,y);
        if(x==3)printf("%d\n",frk(rt,y));
        if(x==4)printf("%d\n",ask(rt,y));
        if(x==5)printf("%d\n",pre(rt,y));
        if(x==6)printf("%d\n",nxt(rt,y));
    }
}
```

