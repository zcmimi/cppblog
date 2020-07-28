---
author: zc
avatar: null
categories:
- - 刷题记录
commnet: 1
date: 2019-12-21 19:47
html: '<details><summary>查看原题</summary><div id=''from''></div><p><button onclick="document.getElementById(''from'').innerHTML=''<iframe
  src=&quot;https://www.luogu.com.cn/problem/P3565&quot; width=100% height=800px style=&quot;border:
  none;&quot;><iframe>''" class=''mdui-btn mdui-btn-raised mdui-ripple''>点击加载</button><a
  class=''mdui-btn mdui-btn-raised mdui-ripple'' href="https://www.luogu.com.cn/problem/P3565"
  target=''_blank''>点击跳转</a><p></details>'
permalink: LG 3565 [POI2014]HOT-Hotels
tags:
- 树形dp
- 长链剖分
thumbnail: null
title: LG 3565 [POI2014]HOT-Hotels
top: 0
---
树形dp 长链剖分

[加强版](https://www.lydsy.com/JudgeOnline/problem.php?id=4543)

先来考虑$1 \le n \le 5000$

设$f[i][j]$表示在$i$的子树中与$i$距离为$j$的点数

显然$f[i][j] = \sum f[to][j-1](f[i][0] = 1)$

设$g[i][j]$表示以$i$为根的子树中,点对$(x,y)$满足$x,y$到$lca(x,y)$距离都是$d$,并且$lca(x,y)$到$i$的距离为$d-j$的点对数

$g[i][j] = \sum g[to][j+1]$

$ans = \sum_{i=1}^n (g[i][0]+g[i][j] \times f[to][j-1])$

我们来考虑加强版

$n \le 100000$

有点像静态链分治和树链剖分

我们计算长链的时候结果不需要清空,其他儿子节点重新计算

这样可以省下长链的时间

长链剖分真是个毒瘤(指针毒瘤)
```cpp
#include<bits/stdc++.h>
namespace ZDY{
    #pragma GCC optimize(3)
    #define il __inline__ __attribute__ ((always_inline))
    #define rg register
    #define ll long long
    #define ull unsigned long long
    #define db double
    #define sht short
    #define MB template <class T>il
    #define Fur(i,x,y) for(int i=x;i<=y;++i)
    #define Fdr(i,x,y) for(int i=x;i>=y;--i)
    #define fl(i,x) for(int i=head[x],to;to=e[i].to,i;i=e[i].nxt)
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
namespace IO{const char* ln="\n";const int str=1<<20;struct IN{char buf[str],*s,*t;bool _;IN():s(buf),t(buf),_(0){}il char gc(){return s==t&&((t=(s=buf)+fread(buf,1,str,stdin))==s)?EOF:(*s++);}IN&operator>>(char&ch){if(_)return *this;char c;while((c=gc())!=EOF&&isspace(c));if(c==EOF)_=1;else ch=c;return *this;}IN& operator>>(char* ch){clr(ch,0);if(_)return *this;char c;while((c=gc())!=EOF&&isspace(c));if(c==EOF)return _=1,*this;*ch=c;ch++;while((c=gc())!=EOF&&!isspace(c))*ch=c,ch++;if(c==EOF)_=1;return *this;}IN& operator>>(string& ch){if(_)return *this;char c;while((c=gc())!=EOF&&isspace(c));if(c==EOF)return _=1,*this;ch+=c;while((c=gc())!=EOF&&!isspace(c))ch+=c;if(c==EOF)_=1;return *this;}template<typename T>IN&operator>>(T&x){if(_)return *this;char c=gc();bool ff=0;while(c!=EOF&&(c<'0'||c>'9'))ff^=(c=='-'),c=gc();if(c==EOF){_=1;return *this;}x=0;while(c!=EOF&&'0'<=c&&c<='9')x=(x<<3)+(x<<1)+c-48,c=gc();if(c==EOF)_=1;if(ff)x=-x;return *this;}}in;struct OUT{char buf[str],*s,*t;OUT():s(buf),t(buf+str){}~OUT(){fwrite(buf,1,s-buf,stdout);}void pt(char c){(s==t)?(fwrite(s=buf,1,str,stdout),*s++=c):(*s++=c);}OUT&operator<<(const char*s){while(*s)pt(*s++);return *this;}OUT&operator<<(char*s){while(*s)pt(*s++);return *this;}OUT&operator<<(string s){for(int i=0;s[i];i++)pt(s[i]);return *this;}template<typename T>OUT&operator<<(T x){if(!x)return pt('0'),*this;if(x<0)pt('-'),x=-x;char a[30],t=0;while(x)a[t++]=x%10,x/=10;while(t--)pt(a[t]+'0');return *this;}}out;}using namespace IO;
const int N(100011);
int n,cnt=0,head[N];
struct edge{
    int to,nxt;
}e[N*2];
void add(int x,int y){
    e[++cnt].to=y;e[cnt].nxt=head[x];head[x]=cnt;
}
int d[N],mxd[N],son[N];
void dfs(int x,int fa){
    fl(i,x)if(to!=fa){
        d[to]=d[x]+1;
        dfs(to,x);
        mxd[x]=MAX(mxd[x],mxd[to]);
        if(mxd[to]>mxd[son[x]])son[x]=to;
    }
    mxd[x]=mxd[son[x]]+1;
}
ll *f[N],*g[N],ans=0,pool[N<<2],*id=pool;
void sol(int x,int fa){
    if(son[x])f[son[x]]=f[x]+1,g[son[x]]=g[x]-1,sol(son[x],x);
    f[x][0]=1;ans+=g[x][0];
    fl(i,x)if(to!=fa&&to!=son[x]){
        f[to]=id;id+=mxd[to]<<1;
        g[to]=id;id+=mxd[to]<<1;
        sol(to,x);
        Fur(j,0,mxd[to]-1){
            if(j)ans+=f[x][j-1]*g[to][j];
            ans+=g[x][j+1]*f[to][j];
        }
        Fur(j,0,mxd[to]-1){
            g[x][j+1]+=f[x][j+1]*f[to][j];
            if(j)g[x][j-1]+=g[to][j];
            f[x][j+1]+=f[to][j];
        }
    }
}
int main(){
    fin("in");
    in>>n;
    int x,y;
    Fur(i,1,n-1)in>>x>>y,add(x,y),add(y,x);
    dfs(1,0);
    f[1]=id;id+=mxd[1]<<1;g[1]=id;id+=mxd[1]<<1;
    sol(1,0);
    out<<ans<<ln;
}
```
