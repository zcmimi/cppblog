---
author: zc
avatar: null
categories:
- - 刷题记录
commnet: 1
date: 2019-12-21 19:47
html: '<details><summary>查看原题</summary><div id=''from''></div><p><button onclick="document.getElementById(''from'').innerHTML=''<iframe
  src=&quot;https://www.luogu.com.cn/problem/P3008&quot; width=100% height=800px style=&quot;border:
  none;&quot;><iframe>''" class=''mdui-btn mdui-btn-raised mdui-ripple''>点击加载</button><a
  class=''mdui-btn mdui-btn-raised mdui-ripple'' href="https://www.luogu.com.cn/problem/P3008"
  target=''_blank''>点击跳转</a><p></details>'
permalink: LG 3008 [USACO11JAN]道路和飞机Roads and Planes
tags:
- 拓扑排序
- 最短路
thumbnail: null
title: LG 3008 [USACO11JAN]道路和飞机Roads and Planes
top: 0
---
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
#define N 25011
#define FL(i,x) for(int i(HEAD[x]),to;to=E[i].to,i;i=E[i].nxt)
int n,cnt=0,head[N],R,P,S;
int CNT=0,HEAD[N];
struct edge{
    int to,nxt,w;
}e[100011],E[50011];
il void add(int x,int y,int w){
    e[++cnt].to=y;e[cnt].nxt=head[x];head[x]=cnt;e[cnt].w=w;
}
il void ADD(int x,int y,int w){
    E[++CNT].to=y;E[CNT].nxt=HEAD[x];HEAD[x]=CNT;E[CNT].w=w;
}
vector<int>T[N];
int bl[N],tt=0,d[N],deg[N];
void dfs(int x,int y){
    bl[x]=y;T[y].push_back(x);
    fl(i,x)if(!bl[to])dfs(to,y);
}
struct cmp{il bool operator()(int x,int y){return d[x]>d[y];}};
bool v[N];
il void spfa(int X){
    priority_queue<int,vector<int>,cmp>p;
    for(auto t:T[X])
    if(d[t]!=inf)p.push(t),v[t]=1;
    while(!p.empty()){
        int x=p.top();p.pop();v[x]=0;
        fl(i,x)if(d[x]+e[i].w<d[to]){
            d[to]=d[x]+e[i].w;
            if(!v[to])p.push(to);
        }
        FL(i,x)d[to]=MIN(d[to],d[x]+E[i].w);
    }
}
int main(){
    fin("in");
    in(n,R,P,S);
    int x,y,w;
    Fur(i,1,R){
        in(x,y,w);
        add(x,y,w);add(y,x,w);
    }
    Fur(i,1,n)if(!bl[i])dfs(i,++tt);
    Fur(i,1,P){
        in(x,y,w);
        ADD(x,y,w);++deg[bl[y]];
    }
    clr(d,126);
    d[S]=0;
    queue<int>q;
    Fur(i,1,tt)if(!deg[i])q.push(i);
    while(!q.empty()){
        x=q.front();q.pop();
        spfa(x);
        for(auto t:T[x])
            FL(i,t)
            if(--deg[bl[to]]==0)
                q.push(bl[to]);
    }
    Fur(i,1,n)
        if(d[i]==inf)out("NO PATH\n");
        else out(d[i],ln);
    flush();
}

```
