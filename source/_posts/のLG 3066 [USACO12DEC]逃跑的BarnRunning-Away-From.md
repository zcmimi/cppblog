---
author: zc
avatar: null
categories:
- - 刷题记录
commnet: 1
date: 2019-12-31 11:31
html: '<details><summary>查看原题</summary><div id=''from''></div><p><button onclick="document.getElementById(''from'').innerHTML=''<iframe
  src=&quot;https://www.luogu.com.cn/problem/P3066&quot; width=100% height=800px style=&quot;border:
  none;&quot;><iframe>''" class=''mdui-btn mdui-btn-raised mdui-ripple''>点击加载</button><a
  class=''mdui-btn mdui-btn-raised mdui-ripple'' href="https://www.luogu.com.cn/problem/P3066"
  target=''_blank''>点击跳转</a><p></details>'
permalink: LG 3066 [USACO12DEC]逃跑的BarnRunning-Away-From
tags:
- 主席树
- dfs序
- 离散化
- 差分
- 倍增
thumbnail: null
title: LG 3066 [USACO12DEC]逃跑的BarnRunning-Away-From
top: 0
---
## 解法1

主席树+离散化(深度太大需要离散化)

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
    #define inf (1ll<<60)
    MB T ABS(T x){return x>0?x:-x;}
    MB T MAX(T x,T y){return x>y?x:y;}
    MB T MIN(T x,T y){return x<y?x:y;}
    MB T GCD(T x,T y){return y?GCD(y,x%y):x;}
    MB void SWAP(T &x,T &y){T t=x;x=y;y=t;}
}using namespace ZDY;using namespace std;
namespace IO{const int str=1<<20;static char in_buf[str],*in_s,*in_t;bool __=0;il char gc(){return (in_s==in_t)&&(in_t=(in_s=in_buf)+fread(in_buf,1,str,stdin)),in_s==in_t?EOF:*in_s++;}il void in(string &ch){ch.clear();if(__)return;char c;while((c=gc())!=EOF&&isspace(c));if(c==EOF){__=1;return;}ch+=c;while((c=gc())!=EOF&&!isspace(c))ch+=c;if(c==EOF)__=1;}il void in(char &ch){if(__)return;char c;while((c=gc())!=EOF&&isspace(c));if(c==EOF)__=1;else ch=c;}il void in(char *ch){*ch='\0';if(__)return;char c;while((c=gc())!=EOF&&isspace(c));if(c==EOF){__=1;return;}*ch=c;ch++;while((c=gc())!=EOF&&!isspace(c))*ch=c,ch++;if(c==EOF)__=1;*ch='\0';}template<typename T>il void in(T &x){if(__)return;char c=gc();bool f=0;while(c!=EOF&&(c<'0'||c>'9'))f^=(c=='-'),c=gc();if(c==EOF){__=1;return;}x=0;while(c!=EOF&&'0'<=c&&c<='9')x=x*10+c-48,c=gc();if(c==EOF)__=1;if(f)x=-x;}template<typename T,typename ... arr>il void in(T &x,arr & ... y){in(x),in(y...);}const char ln='\n';static char out_buf[str],*out_s=out_buf,*out_t=out_buf+str;il void flush(){fwrite(out_buf,1,out_s-out_buf,stdout);out_s=out_buf;}il void pt(char c){(out_s==out_t)?(fwrite(out_s=out_buf,1,str,stdout),*out_s++=c):(*out_s++=c);}il void out(const char* s){while(*s)pt(*s++);}il void out(char* s){while(*s)pt(*s++);}il void out(char c){pt(c);}il void out(string s){for(int i=0;s[i];i++)pt(s[i]);}template<typename T>il void out(T x){if(!x){pt('0');return;}if(x<0)pt('-'),x=-x;char a[50],t=0;while(x)a[t++]=x%10,x/= 10;while(t--)pt(a[t]+'0');}template<typename T,typename ... arr>il void out(T x,arr & ... y){out(x),out(y...);}}using namespace IO;
#define N 200011
#define int ll
int n,len;
int cnt=0,head[N];
int d[N],f[N],mxd=0,siz[N],DFN=0,dfn[N];
int rt[N],ls[N*30],rs[N*30],s[N*30],sz=0,b[N],tt;
struct edge{
    int to,nxt;
}e[N];
void add(int x,int y){
    e[++cnt].to=y;e[cnt].nxt=head[x];head[x]=cnt;
}
int build(int l,int r){
    int x=++sz;
    if(l==r)return x;
    int m=(l+r)>>1;
    ls[x]=build(l,m);
    rs[x]=build(m+1,r);
    return x;
}
void ins(int l,int r,int v,int &x,int pre){
    x=++sz;
    ls[x]=ls[pre];
    rs[x]=rs[pre];
    s[x]=s[pre]+1;
    if(l==r)return;
    int m=(l+r)>>1;
    if(v<=m)ins(l,m,v,ls[x],ls[pre]);
    else ins(m+1,r,v,rs[x],rs[pre]);
}
int ask(int ql,int qr,int l,int r,int x,int y){
    if(ql<=l&&r<=qr)return s[y]-s[x];
    int m=(l+r)>>1,ans=0;
    if(ql<=m)ans=ask(ql,qr,l,m,ls[x],ls[y]);
    if(qr>m)ans+=ask(ql,qr,m+1,r,rs[x],rs[y]);
    return ans;
}
void dfs(int x){
    siz[x]=1;
    dfn[x]=++DFN;
    int k=lower_bound(b+1,b+tt+1,d[x])-b;
    ins(1,tt,k,rt[DFN],rt[DFN-1]);
    fl(i,x)dfs(to),siz[x]+=siz[to];
}
signed main(){
    in(n,len);
    int x,y;
    b[1]=0;
    Fur(i,2,n)
        in(f[i],y),
        b[i]=d[i]=y+d[f[i]],
        add(f[i],i);
    
    b[n+1]=inf;
    sort(b+1,b+n+2);
    tt=unique(b+1,b+n+2)-b-1;

    rt[0]=build(1,tt);
    dfs(1);

    Fur(i,1,n){
        int k=lower_bound(b+1,b+tt+1,d[i])-b-1;
        if(b[k+1]==d[i])++k;
        int kk=lower_bound(b+1,b+tt+1,d[i]+len)-b-1;
        if(b[kk+1]==d[i]+len)++kk;
        if(kk==tt-1)out(siz[i],ln);
        else out(ask(k,kk,1,tt,rt[dfn[i]-1],rt[dfn[i]+siz[i]-1]),ln);
    }
    flush();
}
```
## 解法2

树上查分+倍增

对于每个点u,找到离他最远的祖先v(满足距离小于len)

那么u到v路径上每个点答案+1

可以使用树上差分维护
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
    #define inf (1ll<<60)
    MB T ABS(T x){return x>0?x:-x;}
    MB T MAX(T x,T y){return x>y?x:y;}
    MB T MIN(T x,T y){return x<y?x:y;}
    MB T GCD(T x,T y){return y?GCD(y,x%y):x;}
    MB void SWAP(T &x,T &y){T t=x;x=y;y=t;}
}using namespace ZDY;using namespace std;
namespace IO{const int str=1<<20;static char in_buf[str],*in_s,*in_t;bool __=0;il char gc(){return (in_s==in_t)&&(in_t=(in_s=in_buf)+fread(in_buf,1,str,stdin)),in_s==in_t?EOF:*in_s++;}il void in(string &ch){ch.clear();if(__)return;char c;while((c=gc())!=EOF&&isspace(c));if(c==EOF){__=1;return;}ch+=c;while((c=gc())!=EOF&&!isspace(c))ch+=c;if(c==EOF)__=1;}il void in(char &ch){if(__)return;char c;while((c=gc())!=EOF&&isspace(c));if(c==EOF)__=1;else ch=c;}il void in(char *ch){*ch='\0';if(__)return;char c;while((c=gc())!=EOF&&isspace(c));if(c==EOF){__=1;return;}*ch=c;ch++;while((c=gc())!=EOF&&!isspace(c))*ch=c,ch++;if(c==EOF)__=1;*ch='\0';}template<typename T>il void in(T &x){if(__)return;char c=gc();bool f=0;while(c!=EOF&&(c<'0'||c>'9'))f^=(c=='-'),c=gc();if(c==EOF){__=1;return;}x=0;while(c!=EOF&&'0'<=c&&c<='9')x=x*10+c-48,c=gc();if(c==EOF)__=1;if(f)x=-x;}template<typename T,typename ... arr>il void in(T &x,arr & ... y){in(x),in(y...);}const char ln='\n';static char out_buf[str],*out_s=out_buf,*out_t=out_buf+str;il void flush(){fwrite(out_buf,1,out_s-out_buf,stdout);out_s=out_buf;}il void pt(char c){(out_s==out_t)?(fwrite(out_s=out_buf,1,str,stdout),*out_s++=c):(*out_s++=c);}il void out(const char* s){while(*s)pt(*s++);}il void out(char* s){while(*s)pt(*s++);}il void out(char c){pt(c);}il void out(string s){for(int i=0;s[i];i++)pt(s[i]);}template<typename T>il void out(T x){if(!x){pt('0');return;}if(x<0)pt('-'),x=-x;char a[50],t=0;while(x)a[t++]=x%10,x/= 10;while(t--)pt(a[t]+'0');}template<typename T,typename ... arr>il void out(T x,arr & ... y){out(x),out(y...);}}using namespace IO;
#define N 200011
int f[20][N],n,s[N];
ll len,d[N];
il void gf(int x){Fur(i,1,19)f[i][x]=f[i-1][f[i-1][x]];}
il void work(int x){
    ++s[x];
    ll t=len;
    Fdr(i,19,0)if(d[x]-d[f[i][x]]<=t)
        t-=d[x]-d[f[i][x]],x=f[i][x];
    if(x!=1)--s[f[0][x]];
}
int main(){
    in(n,len);
    ll x;
    f[0][1]=1;
    Fur(i,2,n){
        in(f[0][i],x);
        d[i]=d[f[0][i]]+x;
        gf(i);
    }
    Fur(i,1,n)work(i);
    Fdr(i,n,2)s[f[0][i]]+=s[i];
    Fur(i,1,n)out(s[i],ln);
    flush();
}
```
