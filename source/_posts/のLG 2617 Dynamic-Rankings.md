---
author: zc
avatar: null
categories:
- - 刷题记录
commnet: 1
date: 2019-12-21 21:54
html: '<details><summary>查看原题</summary><div id=''from''></div><p><button onclick="document.getElementById(''from'').innerHTML=''<iframe
  src=&quot;https://www.luogu.com.cn/problem/P2617&quot; width=100% height=800px style=&quot;border:
  none;&quot;><iframe>''" class=''mdui-btn mdui-btn-raised mdui-ripple''>点击加载</button><a
  class=''mdui-btn mdui-btn-raised mdui-ripple'' href="https://www.luogu.com.cn/problem/P2617"
  target=''_blank''>点击跳转</a><p></details>'
permalink: LG 2617 Dynamic-Rankings
tags:
- 树状数组
- 主席树
thumbnail: null
title: LG 2617 Dynamic-Rankings
top: 0
---
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
#define N 100011
int n,q,tot,sz,a[N],c[N<<1],RT[N],s[N*400],ls[N*400],rs[N*400];
struct que{bool opt;int l,r,k;}Q[N];
struct node{int v,id,typ;bool operator<(node t)const{return v<t.v;}}b[N<<1];
void upd(int x,int v,int l,int r,int &rt){
    if(!rt)rt=++sz;
    s[rt]+=v;
    if(l==r){return;}
    int m=l+r>>1;
    if(x<=m)upd(x,v,l,m,ls[rt]);
    else upd(x,v,m+1,r,rs[rt]);
}
il void UPD(int x,int v){for(int i=x;i<=n;i+=i&-i)upd(a[x],v,1,tot,RT[i]);}
int tl[20],tr[20];
il int ask(int l,int r,int k){
    int cl=0,cr=0,cnt,m;
    for(int i=l-1;i;i^=i&-i)tl[++cl]=RT[i];
    for(int i=r;i;i^=i&-i)tr[++cr]=RT[i];
    l=1,r=tot;
    while(l<r){
        m=l+r>>1;cnt=0;
        Fur(i,1,cl)cnt-=s[ls[tl[i]]];
        Fur(i,1,cr)cnt+=s[ls[tr[i]]];
        if(k<=cnt){
            Fur(i,1,cl)tl[i]=ls[tl[i]];
            Fur(i,1,cr)tr[i]=ls[tr[i]];
            r=m;
        }
        else{
            Fur(i,1,cl)tl[i]=rs[tl[i]];
            Fur(i,1,cr)tr[i]=rs[tr[i]];
            k-=cnt,l=m+1;
        }
    }
    return l;
}
int main(){
    in(n,q);
    char ch;bool opt;int l,r,k,d=n,t=0,x;
    Fur(i,1,n)in(x),b[i]={x,i,0};
    Fur(i,1,q){
        in(ch,l,r);
        opt=ch=='Q';
        if(opt)in(k);
        else b[++d]={r,i,1};
        Q[i]=que{opt,l,r,k};
    }
    sort(b+1,b+d+1);b[0].v=-(1<<30);
    Fur(i,1,d)c[(b[i].typ?Q[b[i].id].r:a[b[i].id])=tot+=b[i].v!=b[i-1].v]=b[i].v;
    Fur(i,1,n)UPD(i,1);
    Fur(i,1,q)
    if(Q[i].opt)out(c[ask(Q[i].l,Q[i].r,Q[i].k)],ln);
    else UPD(Q[i].l,-1),a[Q[i].l]=Q[i].r,UPD(Q[i].l,1);
    flush();
}
```
