---
author: zc
avatar: null
categories:
- - "\u5237\u9898\u8BB0\u5F55"
commnet: 1
date: 2020-04-25 16:51
html: "<details><summary>\u67E5\u770B\u539F\u9898</summary><div id='from'></div><p><button\
  \ onclick=\"document.getElementById('from').innerHTML='<iframe src=&quot;https://www.luogu.com.cn/problem/P6477&quot;\
  \ width=100% height=800px style=&quot;border: none;&quot;><iframe>'\" class='mdui-btn\
  \ mdui-btn-raised mdui-ripple'>\u70B9\u51FB\u52A0\u8F7D</button><a class='mdui-btn\
  \ mdui-btn-raised mdui-ripple' href=\"https://www.luogu.com.cn/problem/P6477\" target='_blank'>\u70B9\
  \u51FB\u8DF3\u8F6C</a><p></details>"
permalink: "LG 6477 [NOI Online]\u5B50\u5E8F\u5217\u95EE\u9898"
tags:
- "\u7EBF\u6BB5\u6811"
- "\u8BA1\u6570"
- "\u6811\u72B6\u6570\u7EC4"
thumbnail: null
title: "LG 6477 [NOI Online]\u5B50\u5E8F\u5217\u95EE\u9898"
top: 0
---
枚举右端点$r$,当前颜色$x$

设$lst_x$为颜色$x$上一次出现的位置

假设我们已经得知了$f(l,r-1),l\in [1,r-1]$

那么$f(l,r),l\in [lst_x+1,r]=f(l,r-1)+1$

也就是说我们把$[lst_x+1,r]$区间$+1$就可以了

于是这题就变成了线段树(或树状数组)维护区间平方和
```cpp
#include<bits/stdc++.h>
#pragma GCC optimize(3)
#define il __inline__ __attribute__ ((always_inline))
typedef long long ll;typedef unsigned long long ull;typedef double db;typedef short sht;
#define fur(i,x,y) for(int i(x);i<=y;++i)
#define fdr(i,x,y) for(int i(x);i>=y;--i)
#define fl(i,x) for(int i(head[x]),to;to=e[i].to,i;i=e[i].nxt)
#define l2(n) ((int)(log2(n)))
template <class T>T ABS(T x){return x>0?x:-x;}
template <class T>T MAX(T x,T y){return x>y?x:y;}
template <class T>T MIN(T x,T y){return x<y?x:y;}
template <class T>T GCD(T x,T y){return y?GCD(y,x%y):x;}
template <class T>void SWAP(T &x,T &y){T t=x;x=y;y=t;}
namespace IO{const int str=1<<20;static char in_buf[str],*in_s,*in_t;bool __=0;char gc(){return (in_s==in_t)&&(in_t=(in_s=in_buf)+fread(in_buf,1,str,stdin)),in_s==in_t?EOF:*in_s++;}void in(char &ch){if(__)return;char c;while((c=gc())!=EOF&&isspace(c));if(c==EOF)__=1;else ch=c;}void in(char *ch){*ch='\0';if(__)return;char c;while((c=gc())!=EOF&&isspace(c));if(c==EOF){__=1;return;}*ch=c;ch++;while((c=gc())!=EOF&&!isspace(c))*ch=c,ch++;if(c==EOF)__=1;*ch='\0';}template<typename T>void in(T &x){if(__)return;char c=gc();bool f=0;while(c!=EOF&&(c<'0'||c>'9'))f^=(c=='-'),c=gc();if(c==EOF){__=1;return;}x=0;while(c!=EOF&&'0'<=c&&c<='9')x=x*10+c-48,c=gc();if(c==EOF)__=1;if(f)x=-x;}template<typename T,typename ... arr>void in(T &x,arr & ... y){in(x),in(y...);}const char ln='\n';static char out_buf[str],*out_s=out_buf,*out_t=out_buf+str;void flush(){fwrite(out_buf,1,out_s-out_buf,stdout);out_s=out_buf;}void pt(char c){(out_s==out_t)?(fwrite(out_s=out_buf,1,str,stdout),*out_s++=c):(*out_s++=c);}void out(const char* s){while(*s)pt(*s++);}void out(char* s){while(*s)pt(*s++);}void out(char c){pt(c);}template<typename T>void out(T x){if(!x){pt('0');return;}if(x<0)pt('-'),x=-x;char a[50],t=0;while(x)a[t++]=x%10,x/= 10;while(t--)pt(a[t]+'0');}template<typename T,typename ... arr>void out(T x,arr & ... y){out(x),out(y...);}}using namespace IO;
const int N=1000011,inf=2122219134;
int n;
__int128 s[N<<2],sq[N<<2],laz[N<<2],ans;
#define ls rt<<1
#define rs rt<<1|1
#include<bits/extc++.h>
using namespace __gnu_pbds;
gp_hash_table<int,int>lst;
void add(int rt,ull v,int len){
    sq[rt]+=2*s[rt]*v+v*v*len;
    s[rt]+=v*len;
}
void pd(int rt,int ln,int rn){
    if(laz[rt]){
        laz[ls]+=laz[rt];
        laz[rs]+=laz[rt];
        add(ls,laz[rt],ln);
        add(rs,laz[rt],rn);
        laz[rt]=0;
    }
}
void upd(int L,int R,int l,int r,int rt){
    if(L<=l&&r<=R){
        add(rt,1,r-l+1);++laz[rt];
        return;
    }
    int m=(l+r)>>1;
    pd(rt,m-l+1,r-m);
    if(L<=m)upd(L,R,l,m,ls);
    if(R>m)upd(L,R,m+1,r,rs);
    s[rt]=s[ls]+s[rs];
    sq[rt]=sq[ls]+sq[rs];
}
int main(){
    in(n);
    int x;
    fur(i,1,n){
        in(x);
        upd(lst[x]+1,i,1,n,1);
        lst[x]=i;
        ans+=sq[1];
    }
    printf("%d\n",ans%1000000007);
}
```
