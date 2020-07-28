---
author: zc
avatar: null
categories:
- - 刷题记录
commnet: 1
date: 2020-01-18 22:40
html: '<details><summary>查看原题</summary><div id=''from''></div><p><button onclick="document.getElementById(''from'').innerHTML=''<iframe
  src=&quot;https://www.luogu.com.cn/problem/SP10707&quot; width=100% height=800px
  style=&quot;border: none;&quot;><iframe>''" class=''mdui-btn mdui-btn-raised mdui-ripple''>点击加载</button><a
  class=''mdui-btn mdui-btn-raised mdui-ripple'' href="https://www.luogu.com.cn/problem/SP10707"
  target=''_blank''>点击跳转</a><p></details>'
permalink: LG SP10707 COT2
tags:
- 树上莫队
thumbnail: null
title: LG SP10707 COT2
---
Count-on-a-tree-II
top: 0

---
树上莫队模板
```cpp
#include<bits/stdc++.h>
namespace ZDY{
    #pragma GCC optimize(3)
    #define il __inline__ __attribute__ ((always_inline))
    #define register
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
namespace IO{const int str=1<<20;static char in_buf[str],*in_s,*in_t;bool __=0;il char gc(){return (in_s==in_t)&&(in_t=(in_s=in_buf)+fread(in_buf,1,str,stdin)),in_s==in_t?EOF:*in_s++;}il void in(string &ch){ch.clear();if(__)return;char c;while((c=gc())!=EOF&&isspace(c));if(c==EOF){__=1;return;}ch+=c;while((c=gc())!=EOF&&!isspace(c))ch+=c;if(c==EOF)__=1;}il void in(char &ch){if(__)return;char c;while((c=gc())!=EOF&&isspace(c));if(c==EOF)__=1;else ch=c;}il void in(char *ch){*ch='\0';if(__)return;char c;while((c=gc())!=EOF&&isspace(c));if(c==EOF){__=1;return;}*ch=c;ch++;while((c=gc())!=EOF&&!isspace(c))*ch=c,ch++;if(c==EOF)__=1;*ch='\0';}template<typename T>il void in(T &x){if(__)return;char c=gc();bool f=0;while(c!=EOF&&(c<'0'||c>'9'))f^=(c=='-'),c=gc();if(c==EOF){__=1;return;}x=0;while(c!=EOF&&'0'<=c&&c<='9')x=x*10+c-48,c=gc();if(c==EOF)__=1;if(f)x=-x;}template<typename T,typename ... arr>il void in(T &x,arr & ... y){in(x),in(y...);}const char ln='\n';static char out_buf[str],*out_s=out_buf,*out_t=out_buf+str;il void flush(){fwrite(out_buf,1,out_s-out_buf,stdout);out_s=out_buf;}il void pt(char c){(out_s==out_t)?(fwrite(out_s=out_buf,1,str,stdout),*out_s++=c):(*out_s++=c);}il void out(const char* s){while(*s)pt(*s++);}il void out(char* s){while(*s)pt(*s++);}il void out(char c){pt(c);}il void out(string s){for(int i=0;s[i];i++)pt(s[i]);}template<typename T>il void out(T x){if(!x){pt('0');return;}if(x<0)pt('-'),x=-x;char a[50],t=0;while(x)a[t++]=x%10,x/= 10;while(t--)pt(a[t]+'0');}template<typename T,typename ... arr>il void out(T x,arr & ... y){out(x),out(y...);}}using namespace IO;
const int N=40011,M=100011;
int n,cnt=0,head[N],val[N],old[N];
struct edge{
    int to,nxt;
}e[N<<1];
il void add(int x,int y){
    e[++cnt].to=y;e[cnt].nxt=head[x];head[x]=cnt;
}
int T[N*2],dfn=0,st[N],ed[N],top[N],siz[N],f[N],d[N];
void dfs(int x){
    T[st[x]=++dfn]=x;
    siz[x]=1;
    fl(i,x)if(to!=f[x]){
        f[to]=x;
        d[to]=d[x]+1;
        dfs(to);
        siz[x]+=siz[to];
    }
    T[ed[x]=++dfn]=x;
}
void bt(int x,int tp){
    top[x]=tp;
    int k=0;
    fl(i,x)if(to!=f[x]&&siz[to]>siz[k])k=to;
    if(!k)return;bt(k,tp);
    fl(i,x)if(!top[to])bt(to,to);
}
il int lca(int x,int y){
    while(top[x]!=top[y]){
        if(d[top[x]]<d[top[y]])SWAP(x,y);
        x=f[top[x]];
    }
    return d[x]<d[y]?x:y;
}
int blk,bl[N<<1];
struct que{
    int l,r,lca,id;
    il bool operator<(que t)const{
        return (bl[l]==bl[t.l])?((bl[l]&1)?r<t.r:r>t.r):(l<t.l);
    }
}Q[M];
int ans=0,c[N],ANS[M];
bool v[N];
il void inc(int x){ans+=!c[val[x]]++;}
il void dec(int x){ans-=!--c[val[x]];}
il void op(int x){
    v[x]?dec(x):inc(x);
    v[x]^=1;
}
struct node{
    int v,p;
    il bool operator<(node t)const{
        return v<t.v;
    }
}a[N];
int main(){
    int q,x,y,l=1,r=0;
    in(n,q);
    blk=n*2/sqrt(q*2/3);
    Fur(i,1,n*2)bl[i]=(i-1)/blk+1;
    Fur(i,1,n)in(a[i].v),a[i].p=i;
    sort(a+1,a+n+1);
    int tt=0;
    Fur(i,1,n)old[val[a[i].p]=(tt+=a[i].v!=a[i-1].v)]=a[i].v;
    Fur(i,1,n-1)in(x,y),add(x,y),add(y,x);
    dfs(1);bt(1,1);
    Fur(i,1,q){
        in(x,y);
        if(st[x]>st[y])SWAP(x,y);
        int t=lca(x,y);
        if(t==x)Q[i]=que{st[x],st[y],0,i};
        else Q[i]=que{ed[x],st[y],t,i};
    }
    sort(Q+1,Q+q+1);
    Fur(i,1,q){
        while(l>Q[i].l)op(T[--l]);
        while(r<Q[i].r)op(T[++r]);
        while(l<Q[i].l)op(T[l++]);
        while(r>Q[i].r)op(T[r--]);
        if(Q[i].lca)op(Q[i].lca);
        ANS[Q[i].id]=ans;
        if(Q[i].lca)op(Q[i].lca);
    }
    Fur(i,1,q)out(ANS[i],ln);
    flush();
}
```
