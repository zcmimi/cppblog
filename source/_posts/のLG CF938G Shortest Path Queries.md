---
author: zc
avatar: null
categories:
- - "\u5237\u9898\u8BB0\u5F55"
commnet: 1
date: 2020-06-04 19:43
html: "<details><summary>\u67E5\u770B\u539F\u9898</summary><div id='from'></div><p><button\
  \ onclick=\"document.getElementById('from').innerHTML='<iframe src=&quot;https://www.luogu.com.cn/problem/CF938G&quot;\
  \ width=100% height=800px style=&quot;border: none;&quot;><iframe>'\" class='mdui-btn\
  \ mdui-btn-raised mdui-ripple'>\u70B9\u51FB\u52A0\u8F7D</button><a class='mdui-btn\
  \ mdui-btn-raised mdui-ripple' href=\"https://www.luogu.com.cn/problem/CF938G\"\
  \ target='_blank'>\u70B9\u51FB\u8DF3\u8F6C</a><p></details>"
permalink: LG CF938G Shortest Path Queries
tags:
- "\u79BB\u7EBF"
- "\u7EBF\u6027\u57FA"
- "\u5E76\u67E5\u96C6"
- "\u7EBF\u6BB5\u6811\u5206\u6CBB"
thumbnail: null
title: LG CF938G Shortest Path Queries
top: 0
---
先了解[\[WC2011\]最大XOR和路径](https://www.luogu.com.cn/problem/P4151)的做法

线段树分治+并查集+线性基

加边删边可以用按秩合并的并查集解决,遇到环就插入线性基

由于并查集无法删除元素,删边可以用线段树分治处理(转化为每条边在一个时间段存在)
```cpp
#include<bits/stdc++.h>
int rd(){int x=0;char c;bool f=0;for(c=getchar();c<'0'||'9'<c;c=getchar())f^=c=='-';for(x=c-48,c=getchar();'0'<=c&&c<='9';x=x*10+c-48,c=getchar());return f?-x:x;}
const int N=200011;
struct edge{int x,y,w;}e[N*2];
int n,m,q,bg[N*2],ed[N*2],ql[N],qr[N],f[N],d[N],dep[N];
using namespace std;
map<pair<int,int>,int>T;
struct XOR{
    int p[32];
    void ins(int x){
        for(int i=30;x,~i;--i)if(x>>i){
            if(!p[i]){p[i]=x;return;}
            x^=p[i];
        }
    }
    int ask(int x){
        for(int i=30;~i;--i)
            if((x^p[i])<x)x^=p[i];
        return x;
    }
}_;
int gf(int x){return x==f[x]?x:gf(f[x]);}
int gd(int x){return x==f[x]?0:d[x]^gd(f[x]);}
list<int>s[N<<2];
#define ls rt<<1
#define rs rt<<1|1
void upd(int L,int R,int v,int l,int r,int rt){
    if(L<=l&&r<=R){s[rt].push_back(v);return;}
    int m=l+r>>1;
    if(L<=m)upd(L,R,v,l,m,ls);
    if(R>m)upd(L,R,v,m+1,r,rs);
}
void swap(int &x,int &y){x^=y,y^=x,x^=y;}
int X[N<<2],Y[N<<2],tp;
bool dd[N<<2];
void qry(int l,int r,int rt,XOR c){
    int otp=tp;
    for(auto i:s[rt]){
        int x=e[i].x,y=e[i].y,
            fx=gf(x),fy=gf(y),
            w=e[i].w^gd(x)^gd(y);
        if(fx==fy)c.ins(w);
        else{
            if(dep[fx]>dep[fy])swap(x,y),swap(fx,fy);
            f[fx]=fy,d[fx]=w;
            X[++tp]=fx,Y[tp]=fy;
            if(dep[fx]==dep[fy])++dep[fy],dd[tp]=1;
        }
    }
    if(l==r)printf("%d\n",c.ask(gd(ql[l])^gd(qr[l])));
    else{
        int m=l+r>>1;
        qry(l,m,ls,c),qry(m+1,r,rs,c);
    }
    while(tp!=otp)
        d[f[X[tp]]=X[tp]]=0,dep[Y[tp]]-=dd[tp],--tp;
}
int main(){
    n=rd(),m=rd();
    int opt,x,y,w,t=m,ti=1;
    for(int i=1;i<=m;++i)
        x=rd(),y=rd(),w=rd(),
        e[i]={x,y,w},bg[i]=1,ed[i]=-1,
        T[make_pair(x,y)]=i;
    q=rd();
    for(int i=1;i<=q;++i){
        opt=rd(),x=rd(),y=rd();
        if(opt==1)
            e[++t]={x,y,rd()},bg[t]=ti,ed[t]=-1,
            T[make_pair(x,y)]=t;
        else if(opt==2)ed[T[make_pair(x,y)]]=ti-1;
        else ql[ti]=x,qr[ti]=y,++ti;
    }
    --ti;
    for(int i=1;i<=t;++i){
        if(ed[i]==-1)ed[i]=ti;
        if(bg[i]<=ed[i])upd(bg[i],ed[i],i,1,ti,1);
    }
    for(int i=1;i<=n;++i)f[i]=i;
    qry(1,ti,1,_);
}
```
