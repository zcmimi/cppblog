---
author: zc
avatar: null
categories:
- - 刷题记录
commnet: 1
date: 2019-12-21 19:47
html: '<details><summary>查看原题</summary><div id=''from''></div><p><button onclick="document.getElementById(''from'').innerHTML=''<iframe
  src=&quot;https://www.luogu.com.cn/problem/CF739C&quot; width=100% height=800px
  style=&quot;border: none;&quot;><iframe>''" class=''mdui-btn mdui-btn-raised mdui-ripple''>点击加载</button><a
  class=''mdui-btn mdui-btn-raised mdui-ripple'' href="https://www.luogu.com.cn/problem/CF739C"
  target=''_blank''>点击跳转</a><p></details>'
permalink: LG CF739C Alyona and towers
tags:
- 线段树
thumbnail: null
title: LG CF739C Alyona and towers
top: 0
---
假设我们已经知道区间$[l,r]$左右节点的答案

记录：

```plain
lv,rv:左右端点的值
s: 区间答案
l:以左端开始最长下降
r:以右端结束的最长上升
L:以左端开始最长先上升(再下降)
R:以右端结束最长先上升(再下降)
```
然后考虑最高点再左节点还是有节点


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
#define N 300011
#define int ll
int n,a[N];
struct node{
    int l,r,lv,rv,s,L,R,len;
    // lv,rv:左右端点的值
    // s: 区间答案
    // l:以左端开始最长下降
    // r:以右端结束的最长上升
    // L:以左端开始最长先上升(再下降)
    // R:以右端结束最长先上升(再下降)
}s[N<<2];
int add[N<<2];
node operator + (node x,node y){
    node c;
    c.len=x.len+y.len;

    c.lv=x.lv;c.rv=y.rv;

    c.l=x.l;
    if(x.l==x.len&&x.rv>y.lv)c.l+=y.l;

    c.r=y.r;
    if(y.r==y.len&&y.lv>x.rv)c.r+=x.r;

    c.L=x.L;c.R=y.R;
    if(x.L==x.len&&x.rv>y.lv)c.L+=y.l;
    if(x.r==x.len&&x.rv<y.lv)c.L=MAX(c.L,x.r+y.L);

    if(y.R==y.len&&y.lv>x.rv)c.R+=x.r;
    if(y.l==y.len&&y.lv<x.rv)c.R=MAX(c.R,x.R+y.l);

    c.s=MAX(x.s,y.s);

    if(x.rv>y.lv)c.s=MAX(c.s,x.R+y.l);
    if(y.lv>x.rv)c.s=MAX(c.s,y.L+x.r);
        
    return c;
}
#define ls rt<<1
#define rs rt<<1|1
void build(int l,int r,int rt){
    if(l==r){
        s[rt].lv=s[rt].rv=a[l];
        s[rt].len=s[rt].l=s[rt].r=s[rt].s=s[rt].L=s[rt].R=1;
        return;
    }
    int m=(l+r)>>1;
    build(l,m,ls);build(m+1,r,rs);
    s[rt]=s[ls]+s[rs];
}
void pd(int rt){
    if(add[rt]){
        add[ls]+=add[rt];add[rs]+=add[rt];
        s[ls].lv+=add[rt];
        s[ls].rv+=add[rt];
        s[rs].lv+=add[rt];
        s[rs].rv+=add[rt];
        add[rt]=0;
    }
}
void upd(int L,int R,int v,int l,int r,int rt){
    if(L<=l&&r<=R){
        s[rt].lv+=v;s[rt].rv+=v;
        add[rt]+=v;
        return;
    }
    int m=(l+r)>>1;
    pd(rt);
    if(L<=m)upd(L,R,v,l,m,ls);
    if(R>m)upd(L,R,v,m+1,r,rs);
    s[rt]=s[ls]+s[rs];
}
signed main(){
    fin("in");
    in>>n;
    Fur(i,1,n)in>>a[i];
    build(1,n,1);
    int q,l,r,v;
    in>>q;
    while(q--){
        in>>l>>r>>v;
        upd(l,r,v,1,n,1);
        out<<s[1].s<<ln;
    }
}
```
