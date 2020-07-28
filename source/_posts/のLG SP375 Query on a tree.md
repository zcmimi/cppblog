---
author: zc
avatar: null
categories:
- - 刷题记录
commnet: 1
date: 2019-12-21 19:47
html: '<details><summary>查看原题</summary><div id=''from''></div><p><button onclick="document.getElementById(''from'').innerHTML=''<iframe
  src=&quot;https://www.luogu.com.cn/problem/SP375&quot; width=100% height=800px style=&quot;border:
  none;&quot;><iframe>''" class=''mdui-btn mdui-btn-raised mdui-ripple''>点击加载</button><a
  class=''mdui-btn mdui-btn-raised mdui-ripple'' href="https://www.luogu.com.cn/problem/SP375"
  target=''_blank''>点击跳转</a><p></details>'
permalink: LG SP375 Query on a tree
tags: []
thumbnail: null
title: LG SP375 Query on a tree
top: 0
---
```cpp
#include<stdio.h>
#include<string.h>
#define clr(x,y) memset(x,y,sizeof(x))
#define Fur(i,x,y) for(int i=x;i<=y;i++)
#define fl(i,x) for(int i=head[x],to;to=e[i].to,i;i=e[i].nxt)
int MAX(int x,int y){return x>y?x:y;}
#define SWAP(A, B)   \
    {                \
        int __T = A; \
        A = B;       \
        B = __T;     \
    }
#define N 20011
#define ls rt<<1
#define rs rt<<1|1
#define pu s[rt]=MAX(s[ls],s[rs])
int head[N],n,sz=0,cnt=0;
int top[N],d[N],f[N],siz[N],id[N],val[N],a[N],s[N<<2];
struct edge{
    int to,nxt,w;
}e[N*2];
void add(int x,int y,int w){
    e[++cnt].to=y;e[cnt].w=w;e[cnt].nxt=head[x];head[x]=cnt;
}
void dfs(int x){
    siz[x]=1;
    fl(i,x)if(to!=f[x]){
        f[to]=x;d[to]=d[x]+1;val[to]=e[i].w;
        dfs(to);siz[x]+=siz[to];
    }
}
void bt(int x,int tp){
    top[x]=tp;a[id[x]=++sz]=val[x];
    int k=0;
    fl(i,x)if(to!=f[x]&&siz[to]>siz[k])k=to;
    if(!k)return;bt(k,tp);
    fl(i,x)if(!top[to])bt(to,to);
}
void build(int l,int r,int rt){
    if(l==r){
        s[rt]=a[l];
        return;
    }
    int m=(l+r)>>1;
    build(l,m,ls);build(m+1,r,rs);
    pu;
}
int ask(int L,int R,int l,int r,int rt){
    if(L<=l&&r<=R)return s[rt];
    int m=(l+r)>>1,ans=0;
    if(L<=m)ans=ask(L,R,l,m,ls);
    if(R>m)ans=MAX(ans,ask(L,R,m+1,r,rs));
    return ans;
}
void upd(int x,int v,int l,int r,int rt){
    if(l==r){
        s[rt]=v;
        return;
    }
    int m=(l+r)>>1;
    if(x<=m)upd(x,v,l,m,ls);
    else upd(x,v,m+1,r,rs);
    pu;
}
int fh(int x,int y){
    int ans=0;
    while(top[x]!=top[y]){
        if(d[top[x]]<d[top[y]]){SWAP(x,y);}
        ans=MAX(ans,ask(id[top[x]],id[x],1,n,1));
        x=f[top[x]];
    }
    if(id[x]>id[y])SWAP(x,y);
    return MAX(ans,ask(id[x]+1,id[y],1,n,1));
}
int main(){
int T;scanf("%d",&T);
while(T--){
    scanf("%d",&n);
    int x,y,w;
    char ch[20];
    cnt=sz=0;
    clr(head,0);clr(s,0);clr(f,0);clr(a,0);clr(top,0);clr(d,0);
    Fur(i,1,n-1)scanf("%d%d%d",&x,&y,&w),add(x,y,w),add(y,x,w);
    dfs(1);bt(1,1);build(1,n,1);
    while(1){
        scanf("%s",ch);
        if(ch[0]=='D')break;
        scanf("%d%d",&x,&y);
        if(ch[0]=='C'){
            x*=2;
            x=(d[e[x].to]>d[e[x-1].to])?e[x].to:e[x-1].to;
            upd(id[x],y,1,n,1);
        }
        else printf("%d\n",fh(x,y));
    }
}
}

```
