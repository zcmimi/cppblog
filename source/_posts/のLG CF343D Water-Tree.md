---
author: zc
avatar: null
categories:
- - 刷题记录
commnet: 1
date: 2019-12-21 19:47
html: '<details><summary>查看原题</summary><div id=''from''></div><p><button onclick="document.getElementById(''from'').innerHTML=''<iframe
  src=&quot;https://www.luogu.com.cn/problem/CF343D&quot; width=100% height=800px
  style=&quot;border: none;&quot;><iframe>''" class=''mdui-btn mdui-btn-raised mdui-ripple''>点击加载</button><a
  class=''mdui-btn mdui-btn-raised mdui-ripple'' href="https://www.luogu.com.cn/problem/CF343D"
  target=''_blank''>点击跳转</a><p></details>'
permalink: LG CF343D Water-Tree
tags:
- 树链剖分
- 线段树
thumbnail: null
title: LG CF343D Water-Tree
top: 0
---
直接树剖即可
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
#define N 500011
int n;
struct edge{
    int to,nxt;
}e[N*2];
int cnt=0,head[N],d[N],top[N],f[N],siz[N],id[N],sz=0;
void add(int x,int y){
    e[++cnt].to=y;e[cnt].nxt=head[x];head[x]=cnt;
}
void dfs(int x){
    siz[x]=1;
    fl(i,x)if(to!=f[x]){
        f[to]=x;d[to]=d[x]+1;
        dfs(to);siz[x]+=siz[to];
    }
}
void bt(int x,int tp){
    top[x]=tp;
    id[x]=++sz;
    int k=0;
    fl(i,x)if(to!=f[x]&&siz[to]>siz[k])k=to;
    if(!k)return;bt(k,tp);
    fl(i,x)if(!top[to])bt(to,to);
}
struct seg{
    #define ls rt<<1
    #define rs rt<<1|1
    #define pu s[rt]=s[ls]|s[rs]
    int s[N<<2],laz[N<<2];
    seg(){clr(laz,-1);}
    void pd(int rt){
        if(~laz[rt]){
            laz[ls]=laz[rs]=s[ls]=s[rs]=laz[rt];
            laz[rt]=-1;
        }
    }
    void upd(int L,int R,int v,int l,int r,int rt){
        if(L<=l&&r<=R){
            s[rt]=laz[rt]=v;
            return;
        }
        int m=(l+r)>>1;
        pd(rt);
        if(L<=m)upd(L,R,v,l,m,ls);
        if(R>m)upd(L,R,v,m+1,r,rs);
        pu;
    }
    int get(int x,int l,int r,int rt){
        if(!s[rt])return 0;
        if(l==r)return s[rt];
        int m=(l+r)>>1;
        pd(rt);
        if(x<=m)return get(x,l,m,ls);
        else return get(x,m+1,r,rs);
    }
}T;
int main(){
    in(n);
    int x,y,q,opt;
    Fur(i,1,n-1){
        in(x,y);
        add(x,y);add(y,x);
    }
    dfs(1);bt(1,1);
    in(q);
    while(q--){
        in(opt,x);
        if(opt==1)
            T.upd(id[x],id[x]+siz[x]-1,1,1,n,1);
        
        if(opt==2){
            while(top[x]!=1){
                T.upd(id[top[x]],id[x],0,1,n,1);
                x=f[top[x]];
            }
            T.upd(1,id[x],0,1,n,1);
        }
        if(opt==3)pt(T.get(id[x],1,n,1)?'1':'0'),pt('\n');
    }
    flush();
}
```
