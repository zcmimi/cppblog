---
author: zc
avatar: null
categories:
- - 刷题记录
commnet: 1
date: 2019-12-21 19:47
html: '<details><summary>查看原题</summary><div id=''from''></div><p><button onclick="document.getElementById(''from'').innerHTML=''<iframe
  src=&quot;https://www.luogu.com.cn/problem/CF609E&quot; width=100% height=800px
  style=&quot;border: none;&quot;><iframe>''" class=''mdui-btn mdui-btn-raised mdui-ripple''>点击加载</button><a
  class=''mdui-btn mdui-btn-raised mdui-ripple'' href="https://www.luogu.com.cn/problem/CF609E"
  target=''_blank''>点击跳转</a><p></details>'
permalink: LG CF609E Minimum spanning tree for each edge
tags: []
thumbnail: null
title: LG CF609E Minimum spanning tree for each edge
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
    #define Fur(i,x,y) for(int i=x;i<=y;++i)
    #define Fdr(i,x,y) for(int i=x;i>=y;--i)
    #define fl(i,x) for(int i=head[x],to;to=e[i].to,i;i=e[i].nxt)
    #define clr(x,y) memset(x,y,sizeof(x))
    #define cpy(x,y) memcpy(x,y,sizeof(x))
    #define fin(s) freopen(s".in","r",stdin)
    #define fout(s) freopen(s".out","w",stdout)
    #define fcin ios::sync_with_stdio(false)
    #define l2(n) ((int)(log2(n)))
    #define inf 0x3f3f3f3f
    MB T ABS(T x){return x>0?x:-x;}
    MB T MAX(T x,T y){return x>y?x:y;}
    MB T MIN(T x,T y){return x<y?x:y;}
    MB T GCD(T x,T y){return y?GCD(y,x%y):x;}
    MB void SWAP(T &x,T &y){T t=x;x=y;y=t;}
}using namespace ZDY;using namespace std;
namespace IO{const char* ln="\n";const int str=1<<20;struct IN{char buf[str],*s,*t;bool _;IN():s(buf),t(buf),_(0){}il char gc(){return s==t&&((t=(s=buf)+fread(buf,1,str,stdin))==s)?EOF:(*s++);}IN&operator>>(char&ch){if(_)return *this;char c;while((c=gc())!=EOF&&isspace(c));if(c==EOF)_=1;else ch=c;return *this;}IN& operator>>(char* ch){clr(ch,0);if(_)return *this;char c;while((c=gc())!=EOF&&isspace(c));if(c==EOF)return _=1,*this;*ch=c;ch++;while((c=gc())!=EOF&&!isspace(c))*ch=c,ch++;if(c==EOF)_=1;return *this;}IN& operator>>(string& ch){if(_)return *this;char c;while((c=gc())!=EOF&&isspace(c));if(c==EOF)return _=1,*this;ch+=c;while((c=gc())!=EOF&&!isspace(c))ch+=c;if(c==EOF)_=1;return *this;}template<typename T>IN&operator>>(T&x){if(_)return *this;char c=gc();bool ff=0;while(c!=EOF&&(c<'0'||c>'9'))ff^=(c=='-'),c=gc();if(c==EOF){_=1;return *this;}x=0;while(c!=EOF&&'0'<=c&&c<='9')x=(x<<3)+(x<<1)+c-48,c=gc();if(c==EOF)_=1;if(ff)x=-x;return *this;}}in;struct OUT{char buf[str],*s,*t;OUT():s(buf),t(buf+str){}~OUT(){fwrite(buf,1,s-buf,stdout);}void pt(char c){(s==t)?(fwrite(s=buf,1,str,stdout),*s++=c):(*s++=c);}OUT&operator<<(const char*s){while(*s)pt(*s++);return *this;}OUT&operator<<(char*s){while(*s)pt(*s++);return *this;}OUT&operator<<(string s){for(int i=0;s[i];i++)pt(s[i]);return *this;}template<typename T>OUT&operator<<(T x){if(!x)return pt('0'),*this;if(x<0)pt('-'),x=-x;char a[30],t=0;while(x)a[t++]=x%10,x/=10;while(t--)pt(a[t]+'0');return *this;}}out;}using namespace IO;
#define N 400011
#define int ll
struct edge{
    int to,nxt,w;
}e[N*2];
int n,m,cnt=0,head[N],B=0,sz=0;
void add(int x,int y,int w){
    e[++cnt].to=y;e[cnt].w=w;e[cnt].nxt=head[x];head[x]=cnt;
}
int fa[N];
struct node{
    int x,y,w,id;
    bool v=0;
}E[N];
bool cmp(node x,node y){
    return x.w<y.w;
}
bool CMP(node x,node y){
    return x.id<y.id;
}
int gf(int x){return (fa[x]==x)?x:(fa[x]=gf(fa[x]));}
void kru(){
    Fur(i,1,n)fa[i]=i;
    sort(E+1,E+m+1,cmp);
    int x,y,w;
    Fur(i,1,m){
        x=E[i].x,y=E[i].y,w=E[i].w;
        if(gf(x)!=gf(y)){
            E[i].v=1;
            fa[fa[x]]=fa[y];
            add(x,y,w);add(y,x,w);
            B+=w;
        }
    }
    sort(E+1,E+m+1,CMP);
}
int top[N],siz[N],f[N],v[N],s[N<<2],id[N],d[N],a[N];
void dfs(int x){
    siz[x]=1;id[x]=++sz;a[id[x]]=v[x];
    fl(i,x)if(to!=f[x]){
        f[to]=x;d[to]=d[x]+1;v[to]=e[i].w;
        dfs(to);siz[x]+=siz[to];
    }
}
void bt(int x,int tp){
    top[x]=tp;int k=0;
    fl(i,x)if(to!=f[x]&&siz[to]>siz[k])k=to;
    if(!k)return;bt(k,tp);
    fl(i,x)if(!top[to])bt(to,to);
}
#define ls rt<<1
#define rs rt<<1|1
void build(int l,int r,int rt){
    if(l==r){
        s[rt]=a[l];
        return;
    }
    int m=(l+r)>>1;
    build(l,m,ls);
    build(m+1,r,rs);
    s[rt]=MAX(s[ls],s[rs]);
}
int ask(int L,int R,int l=1,int r=n,int rt=1){
    if(L<=l&&r<=R)return s[rt];
    int m=(l+r)>>1,ans=0;
    if(L<=m)ans=ask(L,R,l,m,ls);
    if(R>m)ans=MAX(ans,ask(L,R,m+1,r,rs));
    return ans;
}
int fh(int x,int y){
    int ans=0;
    while(top[x]!=top[y]){
        if(d[top[x]]<d[top[y]])SWAP(x,y);
        ans=MAX(ans,ask(id[top[x]],id[x]));x=f[top[x]];
    }
    if(id[x]>id[y])SWAP(x,y);
    return MAX(ans,ask(id[x]+1,id[y]));
}
signed main(){
    fin("in");
    in>>n>>m;
    int x,y;
    Fur(i,1,m)in>>E[i].x>>E[i].y>>E[i].w,E[i].id=i;
    kru();
    dfs(1);
    bt(1,1);
    build(1,n,1);
    Fur(i,1,m)
        if(E[i].v)out<<B<<ln;
        else out<<(ll)B+E[i].w-fh(E[i].x,E[i].y)<<ln;
}
```
