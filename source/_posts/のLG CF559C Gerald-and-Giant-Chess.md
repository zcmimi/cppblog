---
author: zc
avatar: null
categories:
- - 刷题记录
commnet: 1
date: 2019-12-31 11:31
html: '<details><summary>查看原题</summary><div id=''from''></div><p><button onclick="document.getElementById(''from'').innerHTML=''<iframe
  src=&quot;https://www.luogu.com.cn/problem/CF559C&quot; width=100% height=800px
  style=&quot;border: none;&quot;><iframe>''" class=''mdui-btn mdui-btn-raised mdui-ripple''>点击加载</button><a
  class=''mdui-btn mdui-btn-raised mdui-ripple'' href="https://www.luogu.com.cn/problem/CF559C"
  target=''_blank''>点击跳转</a><p></details>'
permalink: LG CF559C Gerald-and-Giant-Chess
tags:
- 动态规划
- 计数dp
thumbnail: null
title: LG CF559C Gerald-and-Giant-Chess
top: 0
---
设$f_i$表示只经过第$i$个黑点的方案数

$f_i$最初为${x_i+y_i-2}\choose {x_i-1}$

减去$(1,1)$到$(x_i,y_i)$这个范围内所有$f_j$的方案数就是最终答案了


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
#define N 2011
const int mod=1000000007;
int h,w,n,f[N];
struct node{
    int x,y;
}a[N];
bool cmp(node p,node q){
    if(p.x!=q.x)return p.x<q.x;
    return p.y<q.y;
}
#define M 200011
int fac[200012],inv[200012];
int pw(int x,int p){
    int ans=1;
    while(p){
        if(p&1)ans=1ll*ans*x%mod;
        p>>=1;x=1ll*x*x%mod;
    }
    return ans;
}
void init(){
    fac[0]=1;
    Fur(i,1,M)fac[i]=1ll*fac[i-1]*i%mod;
    inv[M]=pw(fac[M],mod-2);
    Fdr(i,M-1,0)inv[i]=1ll*inv[i+1]*(i+1)%mod;
}
int C(int x,int y){
    if(x<y)return 0;
    return 1ll*fac[x]*inv[y]%mod*inv[x-y]%mod;
}
signed main(){
    init();
    in(h,w,n);
    Fur(i,1,n)in(a[i].x,a[i].y);
    sort(a+1,a+n+1,cmp);
    a[++n]=node{h,w};
    Fur(i,1,n){
        f[i]=C(a[i].x+a[i].y-2,a[i].x-1);
        Fur(j,1,i-1)
        if(a[j].y<=a[i].y){
            f[i]-=1ll*f[j]*C(a[i].x-a[j].x+a[i].y-a[j].y,a[i].x-a[j].x)%mod;
            while(f[i]<0)f[i]+=mod;
        }
    }
    cout<<f[n]<<endl;
}
```
