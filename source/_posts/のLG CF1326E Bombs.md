---
author: zc
avatar: null
categories:
- - "\u5237\u9898\u8BB0\u5F55"
commnet: 1
date: 2020-04-28 17:21
html: "<details><summary>\u67E5\u770B\u539F\u9898</summary><div id='from'></div><p><button\
  \ onclick=\"document.getElementById('from').innerHTML='<iframe src=&quot;https://www.luogu.com.cn/problem/CF1326E&quot;\
  \ width=100% height=800px style=&quot;border: none;&quot;><iframe>'\" class='mdui-btn\
  \ mdui-btn-raised mdui-ripple'>\u70B9\u51FB\u52A0\u8F7D</button><a class='mdui-btn\
  \ mdui-btn-raised mdui-ripple' href=\"https://www.luogu.com.cn/problem/CF1326E\"\
  \ target='_blank'>\u70B9\u51FB\u8DF3\u8F6C</a><p></details>"
permalink: LG CF1326E Bombs
tags:
- "\u7EBF\u6BB5\u6811"
thumbnail: null
title: LG CF1326E Bombs
top: 0
---
可以发现答案是递减的

每个$q_i$相当于破坏掉$[1,q_i]$的最大值

那么我们把$[1,q_i]$区间$-1$

将最大值变为$p_k$的时候,相当于$[1,k]$的最大值都变成了$p_k$

那么把$[1,k]$区间$+1$

每次询问的时候,一直将当前最大值$-1$,应用变化,直到区间最大值大于$0$,输出答案

具体看代码
```cpp
#include<bits/stdc++.h>
#define fur(i,x,y) for(int i(x);i<=y;++i)
int max(int x,int y){return x>y?x:y;}
namespace IO{const int str=1<<20;static char in_buf[str],*in_s,*in_t;bool __=0;char gc(){return (in_s==in_t)&&(in_t=(in_s=in_buf)+fread(in_buf,1,str,stdin)),in_s==in_t?EOF:*in_s++;}void in(char &ch){if(__)return;char c;while((c=gc())!=EOF&&isspace(c));if(c==EOF)__=1;else ch=c;}void in(char *ch){*ch='\0';if(__)return;char c;while((c=gc())!=EOF&&isspace(c));if(c==EOF){__=1;return;}*ch=c;ch++;while((c=gc())!=EOF&&!isspace(c))*ch=c,ch++;if(c==EOF)__=1;*ch='\0';}template<typename T>void in(T &x){if(__)return;char c=gc();bool f=0;while(c!=EOF&&(c<'0'||c>'9'))f^=(c=='-'),c=gc();if(c==EOF){__=1;return;}x=0;while(c!=EOF&&'0'<=c&&c<='9')x=x*10+c-48,c=gc();if(c==EOF)__=1;if(f)x=-x;}template<typename T,typename ... arr>void in(T &x,arr & ... y){in(x),in(y...);}const char ln='\n';static char out_buf[str],*out_s=out_buf,*out_t=out_buf+str;void flush(){fwrite(out_buf,1,out_s-out_buf,stdout);out_s=out_buf;}void pt(char c){(out_s==out_t)?(fwrite(out_s=out_buf,1,str,stdout),*out_s++=c):(*out_s++=c);}void out(const char* s){while(*s)pt(*s++);}void out(char* s){while(*s)pt(*s++);}void out(char c){pt(c);}template<typename T>void out(T x){if(!x){pt('0');return;}if(x<0)pt('-'),x=-x;char a[50],t=0;while(x)a[t++]=x%10,x/= 10;while(t--)pt(a[t]+'0');}template<typename T,typename ... arr>void out(T x,arr & ... y){out(x),out(y...);}}using namespace IO;
const int N=300011;
#define ls rt<<1
#define rs rt<<1|1
int n,a[N],p[N],s[N<<2],laz[N<<2];
void pd(int rt){
    if(laz[rt]){
        laz[ls]+=laz[rt];
        laz[rs]+=laz[rt];
        s[ls]+=laz[rt];
        s[rs]+=laz[rt];
        laz[rt]=0;
    }
}
void upd(int L,int R,int v,int l=1,int r=n,int rt=1){
    if(L<=l&&r<=R){s[rt]+=v,laz[rt]+=v;return;}
    int m=l+r>>1;pd(rt);
    if(L<=m)upd(L,R,v,l,m,ls);
    if(R>m)upd(L,R,v,m+1,r,rs);
    s[rt]=max(s[ls],s[rs]);
}
int main(){
    in(n);
    fur(i,1,n)in(a[i]),p[a[i]]=i;
    upd(1,p[n],1);
    int x,res=n;out(n," ");
    fur(i,1,n-1){
        in(x);
        upd(1,x,-1);
        while(s[1]<=0)upd(1,p[--res],1);
        out(res," ");
    }in(x);
    flush();
}
```
