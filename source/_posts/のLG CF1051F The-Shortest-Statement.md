---
author: zc
avatar: null
categories:
- - 刷题记录
commnet: 1
date: 2019-12-21 19:47
html: '<details><summary>查看原题</summary><div id=''from''></div><p><button onclick="document.getElementById(''from'').innerHTML=''<iframe
  src=&quot;https://www.luogu.com.cn/problem/CF1051F&quot; width=100% height=800px
  style=&quot;border: none;&quot;><iframe>''" class=''mdui-btn mdui-btn-raised mdui-ripple''>点击加载</button><a
  class=''mdui-btn mdui-btn-raised mdui-ripple'' href="https://www.luogu.com.cn/problem/CF1051F"
  target=''_blank''>点击跳转</a><p></details>'
permalink: LG CF1051F The-Shortest-Statement
tags:
- lca
- 最短路
- 最小生成树
thumbnail: null
title: LG CF1051F The-Shortest-Statement
top: 0
---
思路很妙

注意$m-n \le 20$！

也就是说最多只有$21$条非树边

我们可以先跑一遍kruskal,然后按套路建树,两点之间的距离就是$d_x+d_y-2\times lca(x,y)$

接着剩下最多$21$条边($42$个节点),再跑最多$42$次最短路就可以处理出加上非树边的结果了
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
namespace IO{const int str=1<<20;static char in_buf[str],*in_s,*in_t;bool __=0;il char gc(){return (in_s==in_t)&&(in_t=(in_s=in_buf)+fread(in_buf,1,str,stdin)),in_s==in_t?EOF:*in_s++;}il void in(string &ch){ch.clear();if(__)return;rg char c;while((c=gc())!=EOF&&isspace(c));if(c==EOF){__=1;return;}ch+=c;while((c=gc())!=EOF&&!isspace(c))ch+=c;if(c==EOF)__=1;}il void in(char &ch){if(__)return;rg char c;while((c=gc())!=EOF&&isspace(c));if(c==EOF)__=1;else ch=c;}il void in(char *ch){*ch='\0';if(__)return;rg char c;while((c=gc())!=EOF&&isspace(c));if(c==EOF){__=1;return;}*ch=c;ch++;while((c=gc())!=EOF&&!isspace(c))*ch=c,ch++;if(c==EOF)__=1;*ch='\0';}template<typename T>il void in(T &x){if(__)return;rg char c=gc();bool f=0;while(c!=EOF&&(c<'0'||c>'9'))f^=(c=='-'),c=gc();if(c==EOF){__=1;return;}x=0;while(c!=EOF&&'0'<=c&&c<='9')x=x*10+c-48,c=gc();if(c==EOF)__=1;if(f)x=-x;}template<typename T,typename ... arr>il void in(T &x,arr & ... y){in(x),in(y...);}const char ln='\n';static char out_buf[str],*out_s=out_buf,*out_t=out_buf+str;il void flush(){fwrite(out_buf,1,out_s-out_buf,stdout);out_s=out_buf;}il void pt(char c){(out_s==out_t)?(fwrite(out_s=out_buf,1,str,stdout),*out_s++=c):(*out_s++=c);}il void out(const char* s){while(*s)pt(*s++);}il void out(char* s){while(*s)pt(*s++);}il void out(char c){pt(c);}il void out(string s){for(int i=0;s[i];i++)pt(s[i]);}template<typename T>il void out(T x){if(!x){pt('0');return;}if(x<0)pt('-'),x=-x;char a[50],t=0;while(x)a[t++]=x%10,x/= 10;while(t--)pt(a[t]+'0');}template<typename T,typename ... arr>il void out(T x,arr & ... y){out(x),out(y...);}}using namespace IO;
#define N 100111
int n,m,q,cnt=0,head[N];
struct edge{
    int to,nxt,w;
}e[N*2],ee[60];
il void add(int x,int y,int w){
    e[++cnt].to=y;e[cnt].nxt=head[x];head[x]=cnt;
    e[cnt].w=w;
    e[++cnt].to=x;e[cnt].nxt=head[y];head[y]=cnt;
    e[cnt].w=w;
}
ll D[N];
int siz[N],top[N],f[N],d[N];
void dfs(int x){
    siz[x]=1;
    fl(i,x)if(to!=f[x]){
        D[to]=D[x]+e[i].w;f[to]=x;
        d[to]=d[x]+1;
        dfs(to);siz[x]+=siz[to];
    }
}
void bt(int x,int tp){
    top[x]=tp;int k=0;
    fl(i,x)if(to!=f[x]&&siz[to]>siz[k])k=to;
    if(!k)return;bt(k,tp);
    fl(i,x)if(!top[to])bt(to,to);
}
ll get(int x,int y){
    int ox=x,oy=y;
    while(top[x]!=top[y]){
        if(d[top[x]]<d[top[y]])SWAP(x,y);
        x=f[top[x]];
    }
    if(d[x]>d[y])SWAP(x,y);
    return D[ox]+D[oy]-2*D[x];
}
struct link{
    int x,y,w,u;
}E[N];
int tt=0;
bool cmp(link x,link y){return x.w<y.w;}
int fa[N];
int gf(int x){
    return (x==fa[x])?x:(fa[x]=gf(fa[x]));
}
ll dis[60][N];
bool v[N];
struct node{
    int x;
    ll d;
    bool operator<(node x)const{
        return d>x.d;
    }
};
priority_queue<node>T;
void dij(int id,int st){
    dis[id][st]=0;
    T.push(node{st,0});
    clr(v,0);
    while(!T.empty()){
        int x=T.top().x;T.pop();
        if(v[x])continue;
        v[x]=1;
        fl(i,x)if(dis[id][x]+e[i].w<dis[id][to]){
            dis[id][to]=dis[id][x]+e[i].w;
            T.push(node{to,dis[id][to]});
        }
    }
}
void init(){
    clr(dis,126);
    sort(E+1,E+m+1,cmp);
    Fur(i,1,n)fa[i]=i;
    int x,y,w;
    Fur(i,1,m){
        x=E[i].x,y=E[i].y,w=E[i].w;
        if(gf(x)!=gf(y)){
            fa[fa[y]]=fa[x];
            add(x,y,w);
        }
        else E[i].u=1;
    }
    dfs(1);bt(1,1);
    Fur(i,1,m)if(E[i].u)
        add(E[i].x,E[i].y,E[i].w);
    Fur(i,1,m)if(E[i].u)
        dij(++tt,E[i].x),dij(++tt,E[i].y);
}
signed main(){
    in(n,m);
    int x,y,w;
    Fur(i,1,m)in(x,y,w),E[i]=link{x,y,w};
    init();
    in(q);
    while(q--){
        in(x,y);
        ll ans=get(x,y);
        Fur(i,1,tt)
            ans=MIN(ans,dis[i][x]+dis[i][y]);
        out(ans,ln);
    }
    flush();
}
```
