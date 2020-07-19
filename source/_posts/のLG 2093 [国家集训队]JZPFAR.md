---
author: zc
avatar: null
categories:
- - "\u5237\u9898\u8BB0\u5F55"
commnet: 1
date: 2020-04-13 20:52
html: "<details><summary>\u67E5\u770B\u539F\u9898</summary><div id='from'></div><p><button\
  \ onclick=\"document.getElementById('from').innerHTML='<iframe src=&quot;https://www.luogu.com.cn/problem/P2093&quot;\
  \ width=100% height=800px style=&quot;border: none;&quot;><iframe>'\" class='mdui-btn\
  \ mdui-btn-raised mdui-ripple'>\u70B9\u51FB\u52A0\u8F7D</button><a class='mdui-btn\
  \ mdui-btn-raised mdui-ripple' href=\"https://www.luogu.com.cn/problem/P2093\" target='_blank'>\u70B9\
  \u51FB\u8DF3\u8F6C</a><p></details>"
permalink: "LG 2093 [\u56FD\u5BB6\u96C6\u8BAD\u961F]JZPFAR"
tags:
- kdt
thumbnail: null
title: "LG 2093 [\u56FD\u5BB6\u96C6\u8BAD\u961F]JZPFAR"
top: 0
---
```cpp
#include<bits/stdc++.h>
#pragma GCC optimize(3)
#define il __inline__ __attribute__ ((always_inline))
typedef long long ll;typedef unsigned long long ull;typedef double db;typedef short sht;
#define fur(i,x,y) for(int i(x);i<=y;++i)
#define fdr(i,x,y) for(int i(x);i>=y;--i)
#define fl(i,x) for(int i(head[x]),to;to=e[i].to,i;i=e[i].nxt)
#define clr(x,y) memset(x,y,sizeof(x))
#define cpy(x,y) memcpy(x,y,sizeof(x))
#define fin(s) freopen(s".in","r",stdin)
#define fout(s) freopen(s".out","w",stdout)
#define fcin ios::sync_with_stdio(false)
#define l2(n) ((int)(log2(n)))
template <class T>il T ABS(T x){return x>0?x:-x;}
template <class T>il T MAX(T x,T y){return x>y?x:y;}
template <class T>il T MIN(T x,T y){return x<y?x:y;}
template <class T>il T GCD(T x,T y){return y?GCD(y,x%y):x;}
template <class T>il void SWAP(T &x,T &y){T t=x;x=y;y=t;}
using namespace std;
namespace IO{const int str=1<<20;static char in_buf[str],*in_s,*in_t;bool __=0;il char gc(){return (in_s==in_t)&&(in_t=(in_s=in_buf)+fread(in_buf,1,str,stdin)),in_s==in_t?EOF:*in_s++;}il void in(string &ch){ch.clear();if(__)return;char c;while((c=gc())!=EOF&&isspace(c));if(c==EOF){__=1;return;}ch+=c;while((c=gc())!=EOF&&!isspace(c))ch+=c;if(c==EOF)__=1;}il void in(char &ch){if(__)return;char c;while((c=gc())!=EOF&&isspace(c));if(c==EOF)__=1;else ch=c;}il void in(char *ch){*ch='\0';if(__)return;char c;while((c=gc())!=EOF&&isspace(c));if(c==EOF){__=1;return;}*ch=c;ch++;while((c=gc())!=EOF&&!isspace(c))*ch=c,ch++;if(c==EOF)__=1;*ch='\0';}template<typename T>il void in(T &x){if(__)return;char c=gc();bool f=0;while(c!=EOF&&(c<'0'||c>'9'))f^=(c=='-'),c=gc();if(c==EOF){__=1;return;}x=0;while(c!=EOF&&'0'<=c&&c<='9')x=x*10+c-48,c=gc();if(c==EOF)__=1;if(f)x=-x;}template<typename T,typename ... arr>il void in(T &x,arr & ... y){in(x),in(y...);}const char ln='\n';static char out_buf[str],*out_s=out_buf,*out_t=out_buf+str;il void flush(){fwrite(out_buf,1,out_s-out_buf,stdout);out_s=out_buf;}il void pt(char c){(out_s==out_t)?(fwrite(out_s=out_buf,1,str,stdout),*out_s++=c):(*out_s++=c);}il void out(const char* s){while(*s)pt(*s++);}il void out(char* s){while(*s)pt(*s++);}il void out(char c){pt(c);}il void out(string s){for(int i=0;s[i];i++)pt(s[i]);}template<typename T>il void out(T x){if(!x){pt('0');return;}if(x<0)pt('-'),x=-x;char a[50],t=0;while(x)a[t++]=x%10,x/= 10;while(t--)pt(a[t]+'0');}template<typename T,typename ... arr>il void out(T x,arr & ... y){out(x),out(y...);}}using namespace IO;
const int N=100011,inf=2122219134;
int n,rt,cnt,siz[N],c[2][N],L[N],R[N],D[N],U[N];
#define ls c[0][x]
#define rs c[1][x]
bool d[N];
db a=0.75;
struct node{int x,y,v;}t[N];
bool cmpx(node p,node q){return p.x<q.x;}
bool cmpy(node p,node q){return p.y<q.y;}
void upd(int x,int y){
    L[x]=MIN(L[x],L[y]),R[x]=MAX(R[x],R[y]),
    D[x]=MIN(D[x],D[y]),U[x]=MAX(U[x],U[y]);
}
void pu(int x){
    siz[x]=siz[ls]+siz[rs]+1;
    L[x]=R[x]=t[x].x;
    D[x]=U[x]=t[x].y;
    if(ls)upd(x,ls);
    if(rs)upd(x,rs);
}
int build(int l,int r){
    if(l>r)return 0;
    int m=l+r>>1,x=m;
    db av1=0,av2=0,v1=0,v2=0;
    fur(i,l,r)av1+=t[i].x,av2+=t[i].y;
    av1/=r-l+1,av2/=r-l+1;
    fur(i,l,r)
        v1+=(av1-t[i].x)*(av1-t[i].x),
        v2+=(av2-t[i].y)*(av2-t[i].y);
    nth_element(t+l,t+m,t+r+1,(v1>v2)?cmpx:cmpy);
    d[x]=v1>v2;
    ls=build(l,m-1),rs=build(m+1,r);
    pu(x);return x;
}
int qx,qy;
struct dat{
    ll d;int id;
    bool operator<(dat p)const{return d>p.d||(d==p.d&&id<p.id);}
};
priority_queue<dat>q;
ll dis(node p){return 1ll*(p.x-qx)*(p.x-qx)+1ll*(p.y-qy)*(p.y-qy);}
ll mxd(int x){
    return MAX(1ll*(L[x]-qx)*(L[x]-qx),1ll*(R[x]-qx)*(R[x]-qx))+
           MAX(1ll*(D[x]-qy)*(D[x]-qy),1ll*(U[x]-qy)*(U[x]-qy));
}
void ask(int x){
    if(!x)return;
    ll res=dis(t[x]),ld=0,rd=0;
    if(res>q.top().d||(res==q.top().d&&t[x].v<q.top().id))
        q.pop(),q.push(dat{res,t[x].v});
    if(ls)ld=mxd(ls);
    if(rs)rd=mxd(rs);
    if(ld>rd){
        if(ld>=q.top().d)ask(ls);
        if(rd>=q.top().d)ask(rs);
    }
    else{
        if(rd>=q.top().d)ask(rs);
        if(ld>=q.top().d)ask(ls);
    }
}
int main(){
    in(n);
    int m,x,y,k;
    fur(i,1,n)in(x,y),t[i]=node{x,y,i};
    rt=build(1,n);
    in(m);
    while(m--){
        in(qx,qy,k);
        while(!q.empty())q.pop();
        while(k--)q.push(dat{-1,0});
        ask(rt);
        out(q.top().id,ln);
    }
    flush();
}
```
