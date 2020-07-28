---
author: zc
avatar: null
categories:
- - 刷题记录
commnet: 1
date: 2020-02-28 17:31
html: '<details><summary>查看原题</summary><div id=''from''></div><p><button onclick="document.getElementById(''from'').innerHTML=''<iframe
  src=&quot;https://www.luogu.com.cn/problem/P5584&quot; width=100% height=800px style=&quot;border:
  none;&quot;><iframe>''" class=''mdui-btn mdui-btn-raised mdui-ripple''>点击加载</button><a
  class=''mdui-btn mdui-btn-raised mdui-ripple'' href="https://www.luogu.com.cn/problem/P5584"
  target=''_blank''>点击跳转</a><p></details>'
permalink: LG 5584 【SWTR-01】Sunny's Crystals
tags:
- 贪心
- 线段树
thumbnail: null
title: LG 5584 【SWTR-01】Sunny's Crystals
top: 0
---
可以想到贪心: 

如果目前有可以摧毁的目标水晶,那么摧毁最靠后的

否则摧毁第一个水晶

证明: 

> 如果一个水晶目前无法摧毁,它必须等前面若干个水晶被摧毁它才能移动到目标位置
> 
> 所以当目标水晶没有可以摧毁的时候,摧毁序列第一个可以移动最多的目标水晶

> 当有超过一个目标水晶可以摧毁的时候,从后往前摧毁显然是最优的

那么要如何实现这个贪心呢?

很容易想到数据结构

1. 平衡树暴力操作: 数据范围$3\times 10^6$,显然是不行的
   
2. 线段树 目标水晶最多$1.5\times 10^6$,且线段树常数不大,可行

实现: 

1. 线段树维护

维护$d_1,d_2,\dots,d_{cnt}$表示目标水晶到可以摧毁的位置的距离

维护最小值

若最小值为$0$,这找到最靠后的$d_x=0$,摧毁,也就是距离赋值为无穷大,然后将$d_i,i\in[x+1,cnt]$都减去$1$

否则一直摧毁第一个水晶直到最小值为$0$,也就是所有$d_i$都减去$min(d_i)$

代码如下:

```cpp
#include<bits/stdc++.h>
#define il __inline__ __attribute__ ((always_inline))
#define Fur(i,x,y) for(int i=x;i<=y;++i)
il int MIN(int x,int y){return x<y?x:y;}
namespace IO{const int str=1<<20;static char in_buf[str],*in_s,*in_t;bool __=0;il char gc(){return (in_s==in_t)&&(in_t=(in_s=in_buf)+fread(in_buf,1,str,stdin)),in_s==in_t?EOF:*in_s++;}template<typename T>il void in(T &x){if(__)return;char c=gc();bool f=0;while(c!=EOF&&(c<'0'||c>'9'))f^=(c=='-'),c=gc();if(c==EOF){__=1;return;}x=0;while(c!=EOF&&'0'<=c&&c<='9')x=x*10+c-48,c=gc();if(c==EOF)__=1;if(f)x=-x;}template<typename T,typename ... arr>il void in(T &x,arr & ... y){in(x),in(y...);}const char ln='\n';static char out_buf[str],*out_s=out_buf,*out_t=out_buf+str;il void flush(){fwrite(out_buf,1,out_s-out_buf,stdout);out_s=out_buf;}il void pt(char c){(out_s==out_t)?(fwrite(out_s=out_buf,1,str,stdout),*out_s++=c):(*out_s++=c);}template<typename T>il void out(T x){if(!x){pt('0');return;}if(x<0)pt('-'),x=-x;char a[50],t=0;while(x)a[t++]=x%10,x/= 10;while(t--)pt(a[t]+'0');}}using namespace IO;
const int N=1500011;
int n,w,cnt=0,s[N<<2],laz[N<<2],a[N],old[N],ANS[N<<1],ans=0,oth[N<<1];
#define ls rt<<1
#define rs rt<<1|1
il void pu(int rt){s[rt]=MIN(s[ls],s[rs]);}
il void pd(int rt){
    if(laz[rt]){
        laz[ls]+=laz[rt];s[ls]-=laz[rt];
        laz[rs]+=laz[rt];s[rs]-=laz[rt];
        laz[rt]=0;
    }
}
void build(int l,int r,int rt){
    if(l==r){s[rt]=a[l];return;}
    int m=(l+r)>>1;
    build(l,m,ls);build(m+1,r,rs);
    pu(rt);
}
void upd(int L,int c,int l,int r,int rt){
    if(L<=l){s[rt]-=c;laz[rt]+=c;return;}
    int m=(l+r)>>1;
    pd(rt);
    if(L<=m)upd(L,c,l,m,ls);
    upd(L,c,m+1,r,rs);
    pu(rt);
}
int ask(int l,int r,int rt){
    if(l==r){
        s[rt]=(1<<30);
        ANS[++ans]=old[l];
        return l;
    }
    int m=(l+r)>>1,res;
    pd(rt);
    if(!s[rs])res=ask(m+1,r,rs);
    else res=ask(l,m,ls);
    pu(rt);
    return res;
}
int main(){
    in(n,w);
    int x,b=1,now=0;
    Fur(i,1,n){
        if((b<<1)<=i)b<<=1;
        in(x);
        if(x==w)a[++cnt]=i-b,old[cnt]=i;
        else oth[++now]=i;
    }
    now=0;
    build(1,cnt,1);
    Fur(t,1,cnt){
        if(s[1]){
            Fur(j,1,s[1])ANS[++ans]=oth[++now];
            upd(1,s[1],1,cnt,1);
        }
        x=ask(1,cnt,1)+1;
        if(x<=cnt)upd(x,1,1,cnt,1);
    }
    out(ans);pt('\n');
    Fur(i,1,ans)out(ANS[i]),pt(' ');
    flush();
}
```

2. 巧妙的模拟

可以只维护所有$2$次幂位置在原序列中的位置

每次修改只需要修改$\log_2 n$个位置,复杂度完全可以接受

根据这个特性,暴力跑的比正解线段树还快

代码如下: 
```cpp
#include<bits/stdc++.h>
#define il __inline__ __attribute__ ((always_inline))
#define Fur(i,x,y) for(int i=x;i<=y;++i)
#define Fdr(i,x,y) for(int i=x;i>=y;--i)
il int MIN(int x,int y){return x<y?x:y;}
namespace IO{const int str=1<<20;static char in_buf[str],*in_s,*in_t;bool __=0;il char gc(){return (in_s==in_t)&&(in_t=(in_s=in_buf)+fread(in_buf,1,str,stdin)),in_s==in_t?EOF:*in_s++;}template<typename T>il void in(T &x){if(__)return;char c=gc();bool f=0;while(c!=EOF&&(c<'0'||c>'9'))f^=(c=='-'),c=gc();if(c==EOF){__=1;return;}x=0;while(c!=EOF&&'0'<=c&&c<='9')x=x*10+c-48,c=gc();if(c==EOF)__=1;if(f)x=-x;}template<typename T,typename ... arr>il void in(T &x,arr & ... y){in(x),in(y...);}const char ln='\n';static char out_buf[str],*out_s=out_buf,*out_t=out_buf+str;il void flush(){fwrite(out_buf,1,out_s-out_buf,stdout);out_s=out_buf;}il void pt(char c){(out_s==out_t)?(fwrite(out_s=out_buf,1,str,stdout),*out_s++=c):(*out_s++=c);}template<typename T>il void out(T x){if(!x){pt('0');return;}if(x<0)pt('-'),x=-x;char a[50],t=0;while(x)a[t++]=x%10,x/= 10;while(t--)pt(a[t]+'0');}}using namespace IO;
const int N=3000011;
int n,tot=0,b=0,w,a[N],p[N],ans=0,ANS[N];
int main(){
    in(n,w);
    Fur(i,1,n){
        in(a[i]);
        if(a[i]==w)++tot;
    }
    a[n+1]=-1;
    while((1<<b)<=n)p[b+1]=(1<<b),++b;
    while(tot){
        bool f=0;
        Fdr(i,b,1)if(a[p[i]]==w){
            ANS[++ans]=p[i];
            a[p[i]]=0;
            Fur(j,i,b)if(p[j]<=n)
                while(!a[++p[j]]);
            --tot;f=1;break;
        }
        if(!f){
            ANS[++ans]=p[1],a[p[1]]=0;
            Fur(i,1,b)if(p[i]<=n)
                while(!a[++p[i]]);
        }
    }
    out(ans);pt('\n');
    Fur(i,1,ans)out(ANS[i]),pt(' ');
    flush();
}
```
