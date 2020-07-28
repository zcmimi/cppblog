---
author: zc
avatar: null
categories:
- - 刷题记录
commnet: 1
date: 2019-12-21 19:47
html: '<details><summary>查看原题</summary><div id=''from''></div><p><button onclick="document.getElementById(''from'').innerHTML=''<iframe
  src=&quot;https://www.luogu.com.cn/problem/P3145&quot; width=100% height=800px style=&quot;border:
  none;&quot;><iframe>''" class=''mdui-btn mdui-btn-raised mdui-ripple''>点击加载</button><a
  class=''mdui-btn mdui-btn-raised mdui-ripple'' href="https://www.luogu.com.cn/problem/P3145"
  target=''_blank''>点击跳转</a><p></details>'
permalink: LG 3145 [USACO16OPEN]分割田地Splitting-the-Field
tags:
- 计算几何
- 枚举
- 排序
thumbnail: null
title: LG 3145 [USACO16OPEN]分割田地Splitting-the-Field
top: 0
---
只用一个矩形的当然很容易求

用两个矩形的话：

先把所有点按$x$坐标排序,提前记录从前数和从后面数的最大的坐标和最小的坐标($x,y$都要)

枚举断开的位置,记录最小值

计算按$y$轴方向断开的方式一样,把$x,y$交换后如法炮制就可以了

tip:

记录坐标最小值时要把坐标初始化为$- \infty$,要开$long\ long$,要不然会出锅
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
    #define Fur(i,x,y) for(int i=x;i<=y;i++)
    #define Fdr(i,x,y) for(int i=x;i>=y;i--)
    #define fl(i,x) for(int i=head[x],to;to=e[i].to,i;i=e[i].nxt)
    #define clr(x,y) memset(x,y,sizeof(x))
    #define cpy(x,y) memcpy(x,y,sizeof(x))
    #define fin(s) freopen(s".in","r",stdin)
    #define fout(s) freopen(s".out","w",stdout)
    #define fcin ios::sync_with_stdio(false)
    #define l2(n) (int(log2(n)))
    // #define inf 0x3f3f3f3f
    MB T ABS(T x){return x>0?x:-x;}
    MB T MAX(T x,T y){return x>y?x:y;}
    MB T MIN(T x,T y){return x<y?x:y;}
    MB T GCD(T x,T y){return y?GCD(y,x%y):x;}
    MB void SWAP(T &x,T &y){T t=x;x=y;y=t;}
}using namespace ZDY;using namespace std;
namespace IO{const char* ln="\n";const int str=1<<20;struct IN{char buf[str],*s,*t;bool _;IN():s(buf),t(buf),_(0){}il char gc(){return s==t&&((t=(s=buf)+fread(buf,1,str,stdin))==s)?EOF:(*s++);}IN&operator>>(char&ch){if(_)return *this;char c;while((c=gc())!=EOF&&isspace(c));if(c==EOF)_=1;else ch=c;return *this;}IN& operator>>(char* ch){clr(ch,0);if(_)return *this;char c;while((c=gc())!=EOF&&isspace(c));if(c==EOF)return _=1,*this;*ch=c;ch++;while((c=gc())!=EOF&&!isspace(c))*ch=c,ch++;if(c==EOF)_=1;return *this;}IN& operator>>(string& ch){if(_)return *this;char c;while((c=gc())!=EOF&&isspace(c));if(c==EOF)return _=1,*this;ch+=c;while((c=gc())!=EOF&&!isspace(c))ch+=c;if(c==EOF)_=1;return *this;}template<typename T>IN&operator>>(T&x){if(_)return *this;char c=gc();bool ff=0;while(c!=EOF&&(c<'0'||c>'9'))ff^=(c=='-'),c=gc();if(c==EOF){_=1;return *this;}x=0;while(c!=EOF&&'0'<=c&&c<='9')x=(x<<3)+(x<<1)+c-48,c=gc();if(c==EOF)_=1;if(ff)x=-x;return *this;}}in;struct OUT{char buf[str],*s,*t;OUT():s(buf),t(buf+str){}~OUT(){fwrite(buf,1,s-buf,stdout);}void pt(char c){(s==t)?(fwrite(s=buf,1,str,stdout),*s++=c):(*s++=c);}OUT&operator<<(const char*s){while(*s)pt(*s++);return *this;}OUT&operator<<(char*s){while(*s)pt(*s++);return *this;}OUT&operator<<(string s){for(int i=0;s[i];i++)pt(s[i]);return *this;}template<typename T>OUT&operator<<(T x){if(!x)return pt('0'),*this;if(x<0)pt('-'),x=-x;char a[30],t=0;while(x)a[t++]=x%10,x/=10;while(t--)pt(a[t]+'0');return *this;}}out;}using namespace IO;
#define N 100011
#define int ll
#define inf (1ll<<60)
struct node{
    int x,y;
}a[N];
il bool cmp(node x,node y){
    return (x.x==y.x)?(x.y<y.y):(x.x<y.x);
}

int n,x=inf,X=-inf,y=inf,Y=-inf,a1;
int xx[N],XX[N],yy[N],YY[N];
int xxx[N],XXX[N],yyy[N],YYY[N];
int work(){
    sort(a+1,a+n+1,cmp);
    xx[0]=inf,XX[0]=-inf;
    yy[0]=inf,YY[0]=-inf;
    Fur(i,1,n){
        xx[i]=MIN(xx[i-1],a[i].x);
        yy[i]=MIN(yy[i-1],a[i].y);
        XX[i]=MAX(XX[i-1],a[i].x);
        YY[i]=MAX(YY[i-1],a[i].y);
    }
    xxx[n+1]=inf,XXX[n+1]=-inf;
    yyy[n+1]=inf,YYY[n+1]=-inf;
    Fdr(i,n,1){
        xxx[i]=MIN(xxx[i+1],a[i].x);
        yyy[i]=MIN(yyy[i+1],a[i].y);
        XXX[i]=MAX(XXX[i+1],a[i].x);
        YYY[i]=MAX(YYY[i+1],a[i].y);
    }
    int a2=inf;
    Fur(i,1,n-1)if(a[i].x!=a[i+1].x)a2=MIN(a2,(XX[i]-xx[i])*(YY[i]-yy[i])+(XXX[i+1]-xxx[i+1])*(YYY[i+1]-yyy[i+1]));
    return a2;
}
signed main(){
    in>>n;
    Fur(i,1,n){
        in>>a[i].x>>a[i].y;
        x=MIN(x,a[i].x);
        y=MIN(y,a[i].y);
        X=MAX(X,a[i].x);
        Y=MAX(Y,a[i].y);
    }
    a1=(X-x)*(Y-y);
    int a2=work();
    Fur(i,1,n)SWAP(a[i].x,a[i].y);
    a2=MIN(a2,work());
    a1-=a2;
    out<<a1<<ln;
}

```
