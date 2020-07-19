---
author: zc
avatar: null
categories:
- - "\u5237\u9898\u8BB0\u5F55"
commnet: 1
date: 2020-06-14 13:07
html: "<details><summary>\u67E5\u770B\u539F\u9898</summary><div id='from'></div><p><button\
  \ onclick=\"document.getElementById('from').innerHTML='<iframe src=&quot;https://www.luogu.com.cn/problem/P3533&quot;\
  \ width=100% height=800px style=&quot;border: none;&quot;><iframe>'\" class='mdui-btn\
  \ mdui-btn-raised mdui-ripple'>\u70B9\u51FB\u52A0\u8F7D</button><a class='mdui-btn\
  \ mdui-btn-raised mdui-ripple' href=\"https://www.luogu.com.cn/problem/P3533\" target='_blank'>\u70B9\
  \u51FB\u8DF3\u8F6C</a><p></details>"
permalink: LG 3533 [POI2012]RAN-Rendezvous
tags:
- "\u500D\u589E"
- "\u57FA\u73AF\u6811"
- lca
thumbnail: null
title: LG 3533 [POI2012]RAN-Rendezvous
top: 0
---
可以看出这是多颗基环树

分三种情况:

1. $x,y$在不同的两颗树上
   
2. $x,y$还没到达环就相遇了
   
3. $x,y$的祖先在环上不同位置


```cpp
#include<bits/stdc++.h>
#define fur(i,x,y) for(int i=x;i<=y;++i)
int rd(){int x=0;char c;bool f=0;for(c=getchar();c<'0'||'9'<c;c=getchar())f^=c=='-';for(x=c-48,c=getchar();'0'<=c&&c<='9';x=x*10+c-48,c=getchar());return f?-x:x;}
const int N=500011;
int n,q,f[20][N],cnt,head[N],d[N],fr[N],deg[N],Q[N],s[N],sz[N],bl[N];
std::list<int>e[N];
bool v[N];
void dfs(int x,int F){
    fr[x]=F;
    for(auto to:e[x])if(v[to])
        d[to]=d[x]+1,dfs(to,F);
}
int lca(int x,int y){
    if(d[x]<d[y])x^=y,y^=x,x^=y;
    int t=d[x]-d[y];
    for(int i=19;~i;--i)
        if((t>>i)&1)x=f[i][x];
    if(x==y)return y;
    for(int i=19;~i;--i)
        if(f[i][x]^f[i][y])
            x=f[i][x],y=f[i][y];
    return f[0][x];
}
void gl(int x,int id,int now){
    if(s[x])return;
    s[x]=now,++sz[id],bl[x]=id;
    gl(f[0][x],id,now+1);
}
bool pd(int x1,int y1,int x2,int y2) {
	if(std::max(x1,y1)!=std::max(x2,y2))return std::max(x1,y1)<std::max(x2,y2);
	if(std::min(x1,y1)!=std::min(x2,y2))return std::min(x1,y1)<std::min(x2,y2);
	return x1>=y1;
}
int main(){
    n=rd(),q=rd();
    fur(i,1,n)
        ++deg[f[0][i]=rd()],
        e[f[0][i]].push_back(i);
    fur(k,1,19)fur(i,1,n)
        f[k][i]=f[k-1][f[k-1][i]];
    int tp=0,x,y,z,fx,fy;
    for(int i=1;i<=n;++i)if(!deg[i])Q[++tp]=i;
    while(tp){
        v[x=Q[tp--]]=1;
        if(!--deg[f[0][x]])Q[++tp]=f[0][x];
    }
    for(int i=1;i<=n;++i)
        if(!v[i])dfs(i,i),gl(i,++cnt,1);
    while(q--){
        fx=fr[x=rd()],fy=fr[y=rd()];
        if(bl[fx]^bl[fy])printf("-1 -1\n");
        else if(fx==fy)
            z=lca(x,y),
            printf("%d %d\n",d[x]-d[z],d[y]-d[z]);
        else{
            int more1=d[x]+(s[fy]-s[fx]+sz[bl[fx]])%sz[bl[fx]],more2=d[y]+(s[fx]-s[fy]+sz[bl[fx]])%sz[bl[fx]];
			if(pd(d[x],more2,more1,d[y]))printf("%d %d\n",d[x],more2);
			else printf("%d %d\n",more1,d[y]);
        }
    }
}
```
