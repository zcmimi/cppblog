---
author: zc
avatar: null
categories:
- - "\u5237\u9898\u8BB0\u5F55"
commnet: 1
date: 2019-12-21 19:47
html: "<details><summary>\u67E5\u770B\u539F\u9898</summary><div id='from'></div><p><button\
  \ onclick=\"document.getElementById('from').innerHTML='<iframe src=&quot;https://www.luogu.com.cn/problem/CF1008D&quot;\
  \ width=100% height=800px style=&quot;border: none;&quot;><iframe>'\" class='mdui-btn\
  \ mdui-btn-raised mdui-ripple'>\u70B9\u51FB\u52A0\u8F7D</button><a class='mdui-btn\
  \ mdui-btn-raised mdui-ripple' href=\"https://www.luogu.com.cn/problem/CF1008D\"\
  \ target='_blank'>\u70B9\u51FB\u8DF3\u8F6C</a><p></details>"
permalink: LG CF1008D Pave-the-Parallelepiped
tags:
- "\u5BB9\u65A5"
- "\u601D\u7EF4"
- "\u6570\u8BBA"
- "\u7B5B\u6CD5"
- "\u7EA6\u6570"
thumbnail: null
title: LG CF1008D Pave-the-Parallelepiped
top: 0
---
先筛选出$d_a,d_b,d_c$

如果$a,b,c$的约数都不相同,那么$ans = d_a \cdot d_b \cdot d_c$

我们来考虑要减去的部分

$(a,b,c) , (b,a,c)$这样的是不符合的,减去其中一个

也就是减去$d(gcd(a,b))\times(d(gcd(a,b)-1))$

同理,$(a,c,b),(c,b,a)$也要减去.

这样的话会多减了一个$d(gcd(a,b,c))*(d(gcd(a,b,c))-1)$,要加回来

...

https://www.luogu.com.cn/blog/lingchi/solution-cf1008d
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
#define int ll
int n,d[N],pri[N],tot=0,a[N];
bool v[N];
void sieve(){
    n=100000;
    v[1]=1;
    d[1]=1;
    Fur(i,2,n){
        if(!v[i])pri[++tot]=i,a[i]=1,d[i]=2;
        for(int j=1;j<=tot&&i*pri[j]<=n;++j){
            v[i*pri[j]]=1;
            if(i%pri[j])d[i*pri[j]]=d[i]*d[pri[j]],a[i*pri[j]]=1;
            else{
                d[i*pri[j]]=d[i]/(a[i]+1)*(a[i]+2);
                a[i*pri[j]]=a[i]+1;
                break;
            }
        }
    }
}
il ll Qjy(ll u){return u*(u-1);}
void work(){
    int a,b,c;
    in(a,b,c);
    int ga=GCD(b,c),gb=GCD(a,c),gc=GCD(a,b),gg=GCD(ga,a);
printf("%lld\n", d[a] * d[b] * d[c]
  - (d[a] * Qjy(d[ga]) + d[b] * Qjy(d[gb]) + d[c] * Qjy(d[gc]) >> 1)
  + (Qjy(d[gg]) * (d[gg] - 2) / 3 << 1)
  + (Qjy(d[gg]) * (d[ga] + d[gb] + d[gc] - 3 * d[gg] + 2) >> 1)
  - (d[ga] - d[gg]) * (d[gb] - d[gg]) * (d[gc] - d[gg]));
}
signed main(){
    sieve();
    int T;in(T);
    while(T--)work();
    flush();
}
```
