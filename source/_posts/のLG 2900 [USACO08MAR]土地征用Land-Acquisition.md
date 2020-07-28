---
author: zc
avatar: null
categories:
- - 刷题记录
commnet: 1
date: 2019-12-21 19:47
html: '<details><summary>查看原题</summary><div id=''from''></div><p><button onclick="document.getElementById(''from'').innerHTML=''<iframe
  src=&quot;https://www.luogu.com.cn/problem/P2900&quot; width=100% height=800px style=&quot;border:
  none;&quot;><iframe>''" class=''mdui-btn mdui-btn-raised mdui-ripple''>点击加载</button><a
  class=''mdui-btn mdui-btn-raised mdui-ripple'' href="https://www.luogu.com.cn/problem/P2900"
  target=''_blank''>点击跳转</a><p></details>'
permalink: LG 2900 [USACO08MAR]土地征用Land-Acquisition
tags:
- 动态规划
- 斜率优化
thumbnail: null
title: LG 2900 [USACO08MAR]土地征用Land-Acquisition
top: 0
---
设$f_i$表示前$i$块土地

$$
f_i=\min_{j=1}^{i-1}(f_j+maxw[j-1][i]\times maxh[j-1][i])
$$

这样的话怎么想都没有办法优化

我们发现,如果一块土地被另一块土地所包含(即长和宽都比另一块土地小),

那么只需购买那另一块土地即可,于是我们可以据此筛掉其他的土地,

只剩下一些长度递减,宽度递增的土地

那么：

$$
f_i=\min_{j=1}^{i-1}(f_j+l[j+1]\times w[i])
$$

设任意$0\le j<k<i$,若从$j$转移比从$k$转移优,那么

$$
f_j+l[j+1]\times w[i]\le f_k+l[k+1]\times w[i]
\\
w[i](l[j+1]-l[k+1])\le f_k-f_j
\\
w[i]\le \frac{f_k-f_j}{l[j+1]-l[k+1]}
$$

维护一个下凸壳就完事了
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
#define N 50011
#define int ll
int n,f[N],q[N],l[N],w[N];
struct node{
    int l,w;
}a[N];
bool cmp(node x,node y){
    if(x.l!=y.l)return x.l>y.l;
    return x.w<y.w;    
}
db S(int i,int j){
    return ((db)(f[j]-f[i]))/((db)(l[i+1]-l[j+1]));
}
signed main(){
    in(n);
    Fur(i,1,n)in(a[i].w,a[i].l);
    sort(a+1,a+n+1,cmp);
    int h=1,t=1,d=0,mx=0;
    Fur(i,1,n)
    if(a[i].w>mx){
        mx=a[i].w;
        w[++d]=a[i].w;
        l[d]=a[i].l;
    }
    n=d;
    Fur(i,1,n){
        while(h<t&&S(q[h],q[h+1])<=(db)w[i])++h;
        f[i]=f[q[h]]+l[q[h]+1]*w[i];
        while(h<t&&S(q[t-1],q[t])>=S(q[t-1],i))--t;
        q[++t]=i;
    }
    cout<<f[n]<<endl;
}
```
