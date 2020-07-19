---
author: zc
avatar: null
categories:
- - "\u5237\u9898\u8BB0\u5F55"
commnet: 1
date: 2020-04-16 19:54
html: "<details><summary>\u67E5\u770B\u539F\u9898</summary><div id='from'></div><p><button\
  \ onclick=\"document.getElementById('from').innerHTML='<iframe src=&quot;https://www.luogu.com.cn/problem/P3769&quot;\
  \ width=100% height=800px style=&quot;border: none;&quot;><iframe>'\" class='mdui-btn\
  \ mdui-btn-raised mdui-ripple'>\u70B9\u51FB\u52A0\u8F7D</button><a class='mdui-btn\
  \ mdui-btn-raised mdui-ripple' href=\"https://www.luogu.com.cn/problem/P3769\" target='_blank'>\u70B9\
  \u51FB\u8DF3\u8F6C</a><p></details>"
permalink: "LG 3769 [CH\u5F31\u7701\u80E1\u7B56R2]TATT"
tags:
- kdt
thumbnail: null
title: "LG 3769 [CH\u5F31\u7701\u80E1\u7B56R2]TATT"
top: 0
---
可以看成思维偏序问题

先按第一维优先,相同则继续比较其他维排序(保证之后插入的点不会被之前插入的点的范围覆盖,防止统计的时候漏掉),

$f_i=\max{f_j + 1}$

剩下三维可以用`KDT`求出最大的$f_j$

有两种写法:

1. 带重构`KDT`
   
2. 先构建完整的`KDT`,然后把插入当作激活节点
```cpp
#include<bits/stdc++.h>
#pragma GCC optimize(3)
typedef double db;
#define fur(i,x,y) for(int i(x);i<=y;++i)
int max(int x,int y){return x>y?x:y;}
void cmin(int &x,int y){x=x<y?x:y;}
void cmax(int &x,int y){x=x>y?x:y;}
namespace IO{const int str=1<<20;static char in_buf[str],*in_s,*in_t;bool __=0;char gc(){return (in_s==in_t)&&(in_t=(in_s=in_buf)+fread(in_buf,1,str,stdin)),in_s==in_t?EOF:*in_s++;}void in(char &ch){if(__)return;char c;while((c=gc())!=EOF&&isspace(c));if(c==EOF)__=1;else ch=c;}void in(char *ch){*ch='\0';if(__)return;char c;while((c=gc())!=EOF&&isspace(c));if(c==EOF){__=1;return;}*ch=c;ch++;while((c=gc())!=EOF&&!isspace(c))*ch=c,ch++;if(c==EOF)__=1;*ch='\0';}template<typename T>void in(T &x){if(__)return;char c=gc();bool f=0;while(c!=EOF&&(c<'0'||c>'9'))f^=(c=='-'),c=gc();if(c==EOF){__=1;return;}x=0;while(c!=EOF&&'0'<=c&&c<='9')x=x*10+c-48,c=gc();if(c==EOF)__=1;if(f)x=-x;}template<typename T,typename ... arr>void in(T &x,arr & ... y){in(x),in(y...);}const char ln='\n';static char out_buf[str],*out_s=out_buf,*out_t=out_buf+str;void flush(){fwrite(out_buf,1,out_s-out_buf,stdout);out_s=out_buf;}void pt(char c){(out_s==out_t)?(fwrite(out_s=out_buf,1,str,stdout),*out_s++=c):(*out_s++=c);}void out(const char* s){while(*s)pt(*s++);}void out(char* s){while(*s)pt(*s++);}void out(char c){pt(c);}template<typename T>void out(T x){if(!x){pt('0');return;}if(x<0)pt('-'),x=-x;char a[50],t=0;while(x)a[t++]=x%10,x/= 10;while(t--)pt(a[t]+'0');}template<typename T,typename ... arr>void out(T x,arr & ... y){out(x),out(y...);}}using namespace IO;
const int N=50011,inf=2122219134;
int _cmp,n,rt,ans,ls[N],rs[N],mi[N][3],mx[N][3],s[N],g[N];
struct node{
    int v[4];
    int& operator[](int x){return v[x];}
    bool operator<(node p){fur(i,0,3)if(v[i]!=p[i])return v[i]<p[i];}
}t[N];
void pu(int x){
    fur(i,0,2){
        mi[x][i]=mx[x][i]=t[x][i+1];
        if(ls[x])cmin(mi[x][i],mi[ls[x]][i]),cmax(mx[x][i],mx[ls[x]][i]);
        if(rs[x])cmin(mi[x][i],mi[rs[x]][i]),cmax(mx[x][i],mx[rs[x]][i]);
    }
}
bool cmp(int a,int b){return t[a][_cmp]<t[b][_cmp];}
int build(int l,int r,int b){
    if(l>r)return 0;
    int m=l+r>>1;
    _cmp=b+1,std::nth_element(g+l,g+m,g+r+1,cmp);
    ls[g[m]]=build(l,m-1,(b+1)%3),
    rs[g[m]]=build(m+1,r,(b+1)%3),
    pu(g[m]);return g[m];
}
int id,as;
bool chk(int *p,int *q=t[id].v+1){
    fur(i,0,2)if(p[i]>q[i])return 0;
    return 1;
}
void ask(int x){
    if(!x||s[x]<=as)return;
    if(!chk(mi[x]))return;
    if(chk(mx[x])){as=s[x];return;}
    if(chk(t[x].v+1))cmax(as,t[x][0]);
    ask(ls[x]),ask(rs[x]);
}
void on(int x){
    if(x==id){cmax(s[x],t[x][0]=as);return;}
    if(!chk(t[id].v+1,mx[x])||!chk(mi[x]))return;
    if(ls[x])on(ls[x]);if(rs[x])on(rs[x]);
    cmax(s[x],s[ls[x]]),cmax(s[x],s[rs[x]]);
}
int main(){
    in(n);
    fur(i,1,n)in(t[i][0],t[i][1],t[i][2],t[i][3]),g[i]=i;
    std::sort(t+1,t+n+1);
    fur(i,1,n)t[i][0]=0;
    rt=build(1,n,0);
    fur(i,1,n)
        id=i,as=0,ask(rt),
        cmax(ans,++as),
        on(rt);
    printf("%d\n",ans);
}
```
