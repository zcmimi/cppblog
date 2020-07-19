---
author: zc
avatar: null
categories:
- - "\u5237\u9898\u8BB0\u5F55"
commnet: 1
date: 2019-12-21 19:47
html: "<details><summary>\u67E5\u770B\u539F\u9898</summary><div id='from'></div><p><button\
  \ onclick=\"document.getElementById('from').innerHTML='<iframe src=&quot;https://loj.ac/problem/2157&quot;\
  \ width=100% height=800px style=&quot;border: none;&quot;><iframe>'\" class='mdui-btn\
  \ mdui-btn-raised mdui-ripple'>\u70B9\u51FB\u52A0\u8F7D</button><a class='mdui-btn\
  \ mdui-btn-raised mdui-ripple' href=\"https://loj.ac/problem/2157\" target='_blank'>\u70B9\
  \u51FB\u8DF3\u8F6C</a><p></details>"
permalink: LOJ 2157 Lightning-Conductor
tags:
- "\u52A8\u6001\u89C4\u5212"
- "\u5355\u8C03\u961F\u5217"
- "\u56DB\u8FB9\u5F62\u4E0D\u7B49\u5F0F"
- "\u51B3\u7B56\u5355\u8C03\u6027"
thumbnail: null
title: LOJ 2157 Lightning-Conductor
top: 0
---
## 题目大意：

给定一个长度为 $n\leq 500000$ 的序列 $a_1, a_2, \cdots, a_n$ ,要求对于每一个 $1 \leq r \leq n$ ,找到最小的非负整数 $f_{r}$ 满足

$$\forall l\in\left[1,n\right]:a_l \leq a_r + f_{r} - \sqrt{|r-l|}$$

## 解法

考虑$l<r,r>l$的将序列翻转后再来一次就可以了

$$f_r= \max(a_l+\sqrt{r-l})-a_r(l\in[1,r])$$

可以证明$f_r$的最优决策点是递增的

~~可以打表~~

### 分治解法

```cpp
#include<bits/stdc++.h>
namespace ZDY{
    #pragma GCC optimize(3)
    #define il __inline__ __attribute__ ((always_inline))
    #define rg register
    #define ll long long
    #define db double
    #define MB template <class T>il
    #define Fur(i,x,y) for(int i(x);i<=y;++i)
    MB T MAX(T x,T y){return x>y?x:y;}
    MB T MIN(T x,T y){return x<y?x:y;}
}using namespace ZDY;using namespace std;
namespace IO{const int str=1<<20;static char in_buf[str],*in_s,*in_t;bool __=0;il char gc(){return (in_s==in_t)&&(in_t=(in_s=in_buf)+fread(in_buf,1,str,stdin)),in_s==in_t?EOF:*in_s++;}il void in(string &ch){ch.clear();if(__)return;rg char c;while((c=gc())!=EOF&&isspace(c));if(c==EOF){__=1;return;}ch+=c;while((c=gc())!=EOF&&!isspace(c))ch+=c;if(c==EOF)__=1;}il void in(char &ch){if(__)return;rg char c;while((c=gc())!=EOF&&isspace(c));if(c==EOF)__=1;else ch=c;}il void in(char *ch){*ch='\0';if(__)return;rg char c;while((c=gc())!=EOF&&isspace(c));if(c==EOF){__=1;return;}*ch=c;ch++;while((c=gc())!=EOF&&!isspace(c))*ch=c,ch++;if(c==EOF)__=1;*ch='\0';}template<typename T>il void in(T &x){if(__)return;rg char c=gc();bool f=0;while(c!=EOF&&(c<'0'||c>'9'))f^=(c=='-'),c=gc();if(c==EOF){__=1;return;}x=0;while(c!=EOF&&'0'<=c&&c<='9')x=x*10+c-48,c=gc();if(c==EOF)__=1;if(f)x=-x;}template<typename T,typename ... arr>il void in(T &x,arr & ... y){in(x),in(y...);}const char ln='\n';static char out_buf[str],*out_s=out_buf,*out_t=out_buf+str;il void flush(){fwrite(out_buf,1,out_s-out_buf,stdout);out_s=out_buf;}il void pt(char c){(out_s==out_t)?(fwrite(out_s=out_buf,1,str,stdout),*out_s++=c):(*out_s++=c);}il void out(const char* s){while(*s)pt(*s++);}il void out(char* s){while(*s)pt(*s++);}il void out(char c){pt(c);}il void out(string s){for(int i=0;s[i];i++)pt(s[i]);}template<typename T>il void out(T x){if(!x){pt('0');return;}if(x<0)pt('-'),x=-x;char a[50],t=0;while(x)a[t++]=x%10,x/= 10;while(t--)pt(a[t]+'0');}template<typename T,typename ... arr>il void out(T x,arr & ... y){out(x),out(y...);}}using namespace IO;
#define N 500011
int n;
ll a[N];
long db f1[N],f2[N];
void work(int L,int R,int l,int r,long db *f){
    if(L>R)return;
    int m=(L+R)>>1,k=0;
    f[m]=a[m];
    long db t=0;
    Fur(i,l,MIN(r,m)){
        t=a[i]+sqrt(db(m-i));
        if(t>f[m])k=i,f[m]=t;
    }
    f[m]-=a[m];
    if(!k)k=m;
    work(L,m-1,l,k,f);
    work(m+1,R,k,r,f);
}
int main(){
    in(n);
    Fur(i,1,n)in(a[i]);
    work(1,n,1,n,f1);
    reverse(a+1,a+n+1);
    work(1,n,1,n,f2);
    Fur(i,1,n)out((ll)ceil(MAX(f1[i],f2[n-i+1])),ln);
    flush();
}
```

### 队列实现决策二分栈

对于每个$j$,把$a_j+\sqrt{i-j}$看成关于$i$的函数$f_j$。

我们要做的就是在所有$j\leq i$的函数中找到最值

队列实现决策二分栈,按$j$从小到大依次维护这些函数。

对于其中任意两个相邻的函数$f_t,f_{t+1}$ ,它们都有一个临界值$k_{t,t+1}$

显然序列中的$k_{1,2},k_{2,3}...$也要严格递增。

否则,如果$k_{t,t+1}\ge k_{t+1,t+2}$,$f_{t+1}$根本没有用。

每次加入$f_i$的时候：

设队尾为$t$,如果当前$i$比$t$优($calc(k_{t-1},i)\ge calc(k_{t-1},t)$),那么弹出$t$

现在来考虑队头$h$

若$k_h\le i$那么把$h$弹出
```cpp
#include<bits/stdc++.h>
namespace ZDY{
    #pragma GCC optimize(3)
    #define il __inline__ __attribute__ ((always_inline))
    #define rg register
    #define ll long long
    #define db double
    #define MB template <class T>il
    #define Fur(i,x,y) for(int i(x);i<=y;++i)
    #define Fdr(i,x,y) for(int i(x);i>=y;--i)
    MB T MAX(T x,T y){return x>y?x:y;}
    MB T MIN(T x,T y){return x<y?x:y;}
}using namespace ZDY;using namespace std;
namespace IO{const int str=1<<20;static char in_buf[str],*in_s,*in_t;bool __=0;il char gc(){return (in_s==in_t)&&(in_t=(in_s=in_buf)+fread(in_buf,1,str,stdin)),in_s==in_t?EOF:*in_s++;}il void in(string &ch){ch.clear();if(__)return;rg char c;while((c=gc())!=EOF&&isspace(c));if(c==EOF){__=1;return;}ch+=c;while((c=gc())!=EOF&&!isspace(c))ch+=c;if(c==EOF)__=1;}il void in(char &ch){if(__)return;rg char c;while((c=gc())!=EOF&&isspace(c));if(c==EOF)__=1;else ch=c;}il void in(char *ch){*ch='\0';if(__)return;rg char c;while((c=gc())!=EOF&&isspace(c));if(c==EOF){__=1;return;}*ch=c;ch++;while((c=gc())!=EOF&&!isspace(c))*ch=c,ch++;if(c==EOF)__=1;*ch='\0';}template<typename T>il void in(T &x){if(__)return;rg char c=gc();bool f=0;while(c!=EOF&&(c<'0'||c>'9'))f^=(c=='-'),c=gc();if(c==EOF){__=1;return;}x=0;while(c!=EOF&&'0'<=c&&c<='9')x=x*10+c-48,c=gc();if(c==EOF)__=1;if(f)x=-x;}template<typename T,typename ... arr>il void in(T &x,arr & ... y){in(x),in(y...);}const char ln='\n';static char out_buf[str],*out_s=out_buf,*out_t=out_buf+str;il void flush(){fwrite(out_buf,1,out_s-out_buf,stdout);out_s=out_buf;}il void pt(char c){(out_s==out_t)?(fwrite(out_s=out_buf,1,str,stdout),*out_s++=c):(*out_s++=c);}il void out(const char* s){while(*s)pt(*s++);}il void out(char* s){while(*s)pt(*s++);}il void out(char c){pt(c);}il void out(string s){for(int i=0;s[i];i++)pt(s[i]);}template<typename T>il void out(T x){if(!x){pt('0');return;}if(x<0)pt('-'),x=-x;char a[50],t=0;while(x)a[t++]=x%10,x/= 10;while(t--)pt(a[t]+'0');}template<typename T,typename ... arr>il void out(T x,arr & ... y){out(x),out(y...);}}using namespace IO;
#define N 500011
int n,a[N],q[N],k[N];
db p[N],sq[N];
il db calc(int i,int j){return a[j]+sq[i-j];}//函数值
il int bound(int x,int y){
    int l=y,r=(k[x]?k[x]:n),m,ret=r+1;
    while(l<=r){
        m=(l+r)>>1;
        if(calc(m,x)<=calc(m,y))
            ret=m,r=m-1;
        else l=m+1;
    }
    return ret;
}
void work(){
    int h=1,t=0;
    Fur(i,1,n){
        while(h<t&&calc(k[t-1],q[t])<calc(k[t-1],i))--t;
        //保持k单调
        k[t]=bound(q[t],i);
        //二分出临界点
        q[++t]=i;
        while(h<t&&k[h]<=i)++h;
        //不优的出队
        p[i]=MAX(p[i],calc(i,q[h]));
        //两遍取max
    }
}
int main(){
    in(n);
    Fur(i,1,n)in(a[i]),sq[i]=sqrt(i);
    work();

    //翻转序列
    reverse(a+1,a+n+1);
    reverse(p+1,p+n+1);
    memset(k,0,(n+1)<<2);
    work();

    //翻转后需要倒序输出
    Fdr(i,n,1)out(MAX(int(ceil(p[i]))-a[i],0),ln);
    flush();
}
```
