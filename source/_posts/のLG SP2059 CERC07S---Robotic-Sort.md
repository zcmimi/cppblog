---
author: zc
avatar: null
categories:
- - 刷题记录
commnet: 1
date: 2019-12-21 19:47
html: '<details><summary>查看原题</summary><div id=''from''></div><p><button onclick="document.getElementById(''from'').innerHTML=''<iframe
  src=&quot;https://www.luogu.com.cn/problem/SP2059&quot; width=100% height=800px
  style=&quot;border: none;&quot;><iframe>''" class=''mdui-btn mdui-btn-raised mdui-ripple''>点击加载</button><a
  class=''mdui-btn mdui-btn-raised mdui-ripple'' href="https://www.luogu.com.cn/problem/SP2059"
  target=''_blank''>点击跳转</a><p></details>'
permalink: LG SP2059 CERC07S
tags:
- 平衡树
thumbnail: null
title: LG SP2059 CERC07S
---
Robotic-Sort
top: 0

---
同排序机械臂
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
#define N 100011
#define ls c[rt][0]
#define rs c[rt][1]
int sz[N],val[N],rnd[N],rev[N],c[N][2],RT,cnt,n,s[N];
void pu(int rt){
    sz[rt]=sz[ls]+sz[rs]+1;
    s[rt]=MIN(val[rt],MIN(s[ls],s[rs]));
}
void pd(int rt){
    if(rev[rt]){
        SWAP(ls,rs);
        rev[ls]^=1;rev[rs]^=1;
        rev[rt]=0;
    }
}
int ne(int v){val[++cnt]=v;s[cnt]=v;sz[cnt]=1;rnd[cnt]=rand();return cnt;}
void sl(int rt,int k,int &x,int &y){
    if(!rt){x=y=0;return;}
    pd(rt);
    if(sz[ls]>=k)y=rt,sl(ls,k,x,ls);
    else x=rt,sl(rs,k-sz[ls]-1,rs,y);
    pu(rt);
}
int mg(int x,int y){
    if(!x||!y)return x+y;
    pd(x);pd(y);
    if(rnd[x]<rnd[y]){
        c[x][1]=mg(c[x][1],y);
        pu(x);
        return x;
    }
    else{
        c[y][0]=mg(x,c[y][0]);
        pu(y);
        return y;
    }
}
int get(int rt){
    pd(rt);
    if(s[ls]==s[rt])return get(ls);
    if(val[rt]==s[rt])return sz[ls]+1;
    return sz[ls]+1+get(rs);
}
struct node{
    int v,p;
    bool operator<(node t){if(v!=t.v)return v<t.v;return p<t.p;}
}a[N];
int b[N];
void work(){
    clr(s,0);clr(c,0);clr(val,0);clr(rev,0);RT=0;clr(rnd,0);clr(sz,0);
    in(n);
    if(!n)flush(),exit(0);
    Fur(i,1,n)in(a[i].v),a[i].p=i;
    sort(a+1,a+n+1);
    Fur(i,1,n)b[a[i].p]=i;
    int x,y,z,t;
    s[0]=inf;sz[0]=0;
    Fur(i,1,n)RT=mg(RT,ne(b[i]));
    Fur(i,1,n){
        sl(RT,i-1,x,y);
        int p=get(y);
        out(p+i-1," ");
        sl(y,p,y,z);
        rev[y]^=1;
        RT=mg(x,mg(y,z));
    }
    out(ln);
}
int main(){
    while(1)work();
}
```
