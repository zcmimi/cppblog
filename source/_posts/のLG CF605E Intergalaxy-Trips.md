---
author: zc
avatar: null
categories:
- - "\u5237\u9898\u8BB0\u5F55"
commnet: 1
date: 2019-12-21 19:47
html: "<details><summary>\u67E5\u770B\u539F\u9898</summary><div id='from'></div><p><button\
  \ onclick=\"document.getElementById('from').innerHTML='<iframe src=&quot;https://www.luogu.com.cn/problem/CF605E&quot;\
  \ width=100% height=800px style=&quot;border: none;&quot;><iframe>'\" class='mdui-btn\
  \ mdui-btn-raised mdui-ripple'>\u70B9\u51FB\u52A0\u8F7D</button><a class='mdui-btn\
  \ mdui-btn-raised mdui-ripple' href=\"https://www.luogu.com.cn/problem/CF605E\"\
  \ target='_blank'>\u70B9\u51FB\u8DF3\u8F6C</a><p></details>"
permalink: LG CF605E Intergalaxy-Trips
tags:
- "\u671F\u671B"
- "\u52A8\u6001\u89C4\u5212"
thumbnail: null
title: LG CF605E Intergalaxy-Trips
top: 0
---
设$E_x$为$x$到$n$的期望时间

$E_x = \sum_i E_i \times p_{xi}\prod_{j=1}^{i-1}(1-p_{xj})$

我们可以用类似`dij`的思想来更新

每次取出$E_x$最小的$x$来更新

要注意我们现在求出来的还没算上$1$需要先停留在原地的概率,

除掉一个$1-\prod p$才是最终的期望
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
#define N 1011
int n;
db g[N][N],p[N],E[N];
bool v[N];
int main(){
    in(n);
    int x;
    Fur(i,1,n)Fur(j,1,n)in(x),g[i][j]=x/100.0;
    if(n==1)return puts("0"),0;
    Fur(i,1,n)E[i]=1,p[i]=1-g[i][n];
    E[n]=0;v[n]=1;
    Fur(i,1,n){
        x=0;db mx=1e18;
        Fur(j,1,n)
        if(!v[j]&&E[j]/(1-p[j])<mx)
            mx=E[j]/(1-p[j]),x=j;
        v[x]=1;
        if(x==1)return printf("%.10f\n",E[1]/(1-p[1])),0;
        Fur(j,1,n)
            E[j]+=(E[x]/(1-p[x]))*g[j][x]*p[j],p[j]*=(1-g[j][x]);
    }
}
```
