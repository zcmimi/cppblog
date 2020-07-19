---
author: zc
avatar: null
categories:
- - "\u5237\u9898\u8BB0\u5F55"
commnet: 1
date: 2019-12-21 19:47
html: "<details><summary>\u67E5\u770B\u539F\u9898</summary><div id='from'></div><p><button\
  \ onclick=\"document.getElementById('from').innerHTML='<iframe src=&quot;https://www.luogu.com.cn/problem/CF868F&quot;\
  \ width=100% height=800px style=&quot;border: none;&quot;><iframe>'\" class='mdui-btn\
  \ mdui-btn-raised mdui-ripple'>\u70B9\u51FB\u52A0\u8F7D</button><a class='mdui-btn\
  \ mdui-btn-raised mdui-ripple' href=\"https://www.luogu.com.cn/problem/CF868F\"\
  \ target='_blank'>\u70B9\u51FB\u8DF3\u8F6C</a><p></details>"
permalink: LG CF868F Yet-Another-Minimization-Problem
tags:
- "\u51B3\u7B56\u5355\u8C03\u6027"
- "\u52A8\u6001\u89C4\u5212"
thumbnail: null
title: LG CF868F Yet-Another-Minimization-Problem
top: 0
---
设$f(i,j)$表示前$i$个划分成$j$段最少的费用

我们设$calc(l,r)$表示$[l,r]$划分成一段的费用

$$f(i,j)=\min_{x=1}^i(f(x-1,j-1)+calc(x,i))$$

可以发现这个dp方程具有决策单调性

若$i<i'$,那么$k_i\le k_{i'}$(决策点)

> 把连续一段拆成两边更优$x^2+y^2\le (x+y)^2(x,y\ge 0)$

更巧的是$w(l,r)$可以用类似莫队的方法线性转移

这里采用分治的方法实现
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
#define N 100011
int n,q,a[N],c[N];
ll f[N],g[N],w=0;
#define inc(x) w+=c[a[x]]++
#define dec(x) w-=--c[a[x]]
void solve(int L,int R,int l,int r){
    if(L>R)return;
    int k=0,m=(L+R)>>1,t;
    g[m]=inf;
    Fur(i,L,m)inc(i);
    Fur(i,MIN(m,r),l){
        dec(i);
        if(f[i]+w<g[m])g[m]=f[i]+w,k=i;
    }

    Fur(i,l,MIN(m,r))inc(i);
    Fur(i,L,m)dec(i);
    //还原

    solve(L,m-1,l,k);    

    Fur(i,L,m)inc(i);
    Fur(i,l,k-1)dec(i);

    solve(m+1,R,k,r);

    Fur(i,L,m)dec(i);
    Fur(i,l,k-1)inc(i);
    //还原
}
int main(){
    in(n,q);
    Fur(i,1,n)
        in(a[i]),
        f[i]=f[i-1]+c[a[i]]++;
    //第一次直接算
    
    clr(c,0);
    while(--q)//转移k次,省去一维
        solve(1,n,1,n),std::swap(f,g);

    cout<<f[n]<<endl;
}
```
