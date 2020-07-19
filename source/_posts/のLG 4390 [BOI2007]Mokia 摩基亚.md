---
author: zc
avatar: null
categories:
- - "\u5237\u9898\u8BB0\u5F55"
commnet: 1
date: 2020-03-28 23:23
html: "<details><summary>\u67E5\u770B\u539F\u9898</summary><div id='from'></div><p><button\
  \ onclick=\"document.getElementById('from').innerHTML='<iframe src=&quot;https://www.luogu.com.cn/problem/P4390&quot;\
  \ width=100% height=800px style=&quot;border: none;&quot;><iframe>'\" class='mdui-btn\
  \ mdui-btn-raised mdui-ripple'>\u70B9\u51FB\u52A0\u8F7D</button><a class='mdui-btn\
  \ mdui-btn-raised mdui-ripple' href=\"https://www.luogu.com.cn/problem/P4390\" target='_blank'>\u70B9\
  \u51FB\u8DF3\u8F6C</a><p></details>"
permalink: "LG 4390 [BOI2007]Mokia \u6469\u57FA\u4E9A"
tags:
- "\u6811\u72B6\u6570\u7EC4"
- "\u6811\u5957\u6811"
- "\u7EBF\u6BB5\u6811"
- "cdq\u5206\u6CBB"
thumbnail: null
title: "LG 4390 [BOI2007]Mokia \u6469\u57FA\u4E9A"
top: 0
---
## 树套树解法

此题对树套树爱好者极不友好！

首先高高兴兴地写了个树状数组套动态开点权值线段树,发现MLE了,多次调整空间后发现要么re要么mle,难道只能用cdq分治或k-dtree了吗？

好不容易写完的代码舍不得随便删掉

既然卡空间,那我离散化坐标,再把树状数组也改成动态开点线段树还不行吗？ 还真不行

我感到了这题深深的恶毒

只能动用黑科技了！

"线段树的压缩路径",如果没有询问要访问这个节点,那就不继续向下开点,以节约空间！

内层和外层都开,终于通过了这道恶毒的题

```cpp
#include<bits/stdc++.h>
#define il __inline__ __attribute__ ((always_inline))
#define fur(i,x,y) for(int i(x);i<=y;++i)
namespace IO{const int str=1<<20;static char in_buf[str],*in_s,*in_t;bool __=0;il char gc(){return (in_s==in_t)&&(in_t=(in_s=in_buf)+fread(in_buf,1,str,stdin)),in_s==in_t?EOF:*in_s++;}il void in(char &ch){if(__)return;char c;while((c=gc())!=EOF&&isspace(c));if(c==EOF)__=1;else ch=c;}il void in(char *ch){*ch='\0';if(__)return;char c;while((c=gc())!=EOF&&isspace(c));if(c==EOF){__=1;return;}*ch=c;ch++;while((c=gc())!=EOF&&!isspace(c))*ch=c,ch++;if(c==EOF)__=1;*ch='\0';}template<typename T>il void in(T &x){if(__)return;char c=gc();bool f=0;while(c!=EOF&&(c<'0'||c>'9'))f^=(c=='-'),c=gc();if(c==EOF){__=1;return;}x=0;while(c!=EOF&&'0'<=c&&c<='9')x=x*10+c-48,c=gc();if(c==EOF)__=1;if(f)x=-x;}template<typename T,typename ... arr>il void in(T &x,arr & ... y){in(x),in(y...);}const char ln='\n';static char out_buf[str],*out_s=out_buf,*out_t=out_buf+str;il void flush(){fwrite(out_buf,1,out_s-out_buf,stdout);out_s=out_buf;}il void pt(char c){(out_s==out_t)?(fwrite(out_s=out_buf,1,str,stdout),*out_s++=c):(*out_s++=c);}il void out(const char* s){while(*s)pt(*s++);}il void out(char* s){while(*s)pt(*s++);}il void out(char c){pt(c);}template<typename T>il void out(T x){if(!x){pt('0');return;}if(x<0)pt('-'),x=-x;char a[50],t=0;while(x)a[t++]=x%10,x/= 10;while(t--)pt(a[t]+'0');}template<typename T,typename ... arr>il void out(T x,arr & ... y){out(x),out(y...);}}using namespace IO;
const int N=2000011,M=6000011;
int n,m,sz,SZ,RT,rt[M],s[M],ls[M],rs[M],LS[M],RS[M];
struct laz{int x,v;}laz[M];
struct LAZ{int x,y,v;}LAZ[M];
struct que{int opt,x,y,X,Y,a;}Q[N];
struct node{int v,id,typ;bool operator<(node t){return v<t.v;}}b[N<<1],B[N<<1];
void upd(int x,int v,int l,int r,int &o){
    if(!o)o=++sz;
    s[o]+=v;
    if(l==r)return;
    if(laz[o].x){
        int m=l+r>>1;
        if(laz[o].x<=m)upd(laz[o].x,laz[o].v,l,m,ls[o]);
        else upd(laz[o].x,laz[o].v,m+1,r,rs[o]);
    }
    laz[o]={x,v};
}
int ask(int L,int R,int l,int r,int o){
    if(!o)return 0;
    if(L<=l&&r<=R)return s[o];
    int m=l+r>>1,ans=0;
    if(laz[o].x){
        if(laz[o].x<=m)upd(laz[o].x,laz[o].v,l,m,ls[o]);
        else upd(laz[o].x,laz[o].v,m+1,r,rs[o]);
        laz[o]={0,0};
    }
    if(L<=m)ans=ask(L,R,l,m,ls[o]);
    if(R>m)ans+=ask(L,R,m+1,r,rs[o]);
    return ans;
}
void UPD(int x,int y,int v,int l,int r,int &o){
    if(!o)o=++SZ;
    upd(y,v,1,m,rt[o]);
    if(l==r)return;
    if(LAZ[o].x){
        int m=l+r>>1;
        if(LAZ[o].x<=m)UPD(LAZ[o].x,LAZ[o].y,LAZ[o].v,l,m,LS[o]);
        else UPD(LAZ[o].x,LAZ[o].y,LAZ[o].v,m+1,r,RS[o]);
    }
    LAZ[o]={x,y,v};
}
int ASK(int x,int y,int X,int Y,int l=1,int r=n,int o=1){
    if(!o)return 0;
    if(x<=l&&r<=X)return ask(y,Y,1,m,rt[o]);
    int m=l+r>>1,ans=0;
    if(LAZ[o].x){
        int m=l+r>>1;
        if(LAZ[o].x<=m)UPD(LAZ[o].x,LAZ[o].y,LAZ[o].v,l,m,LS[o]);
        else UPD(LAZ[o].x,LAZ[o].y,LAZ[o].v,m+1,r,RS[o]);
        LAZ[o]={0,0,0};
    }
    if(x<=m)ans=ASK(x,y,X,Y,l,m,LS[o]);
    if(X>m)ans+=ASK(x,y,X,Y,m+1,r,RS[o]);
    return ans;
}
int main(){
    int x,y,X,Y,a,opt,d=0,D=0,q=0;
    in(x,y);
    while(1){
        in(opt);if(opt==3)break;
        ++q;
        if(opt==1){
            in(x,y,a);
            b[++d]={x,q,0};
            B[++D]={y,q,0};
        }
        else{
            in(x,y,X,Y);
            b[++d]={x,q,0};
            b[++d]={X,q,1};
            B[++D]={y,q,0};
            B[++D]={Y,q,1};
        }
        Q[q]={opt,x,y,X,Y,a};
    }
    std::sort(b+1,b+d+1);std::sort(B+1,B+D+1);b[0].v=B[0].v=-(1<<30);
    fur(i,1,d)(b[i].typ?Q[b[i].id].X:Q[b[i].id].x)=n+=b[i].v!=b[i-1].v;
    fur(i,1,D)(B[i].typ?Q[B[i].id].Y:Q[B[i].id].y)=m+=B[i].v!=B[i-1].v;
    fur(i,1,q){
        x=Q[i].x,y=Q[i].y,X=Q[i].X,Y=Q[i].Y;a=Q[i].a;
        if(Q[i].opt==1)UPD(x,y,a,1,n,RT);
        else out(ASK(x,y,X,Y),ln);
    }
    flush();
}
```

## CDQ解法

这题还是拿来练CDQ好

可以容斥一下:

设$S_{X,Y}$为$(1,1)$到$X,Y$

$(X_1,Y_1)$到$(X_2,Y_2)$转化为$S_{X_2,Y_2}-S_{X_1-1,Y_2}-S_{X_2,Y_1-1}+S_{X_1-1,X_2-1}$

然后就是经典的CDQ分治解决三位数点了
```cpp
#include<bits/stdc++.h>
#define il __inline__ __attribute__ ((always_inline))
#define fur(i,x,y) for(int i(x);i<=y;++i)
il void cmax(int &x,int y){x=x>y?x:y;}
namespace IO{const int str=1<<20;static char in_buf[str],*in_s,*in_t;bool __=0;il char gc(){return (in_s==in_t)&&(in_t=(in_s=in_buf)+fread(in_buf,1,str,stdin)),in_s==in_t?EOF:*in_s++;}il void in(char &ch){if(__)return;char c;while((c=gc())!=EOF&&isspace(c));if(c==EOF)__=1;else ch=c;}il void in(char *ch){*ch='\0';if(__)return;char c;while((c=gc())!=EOF&&isspace(c));if(c==EOF){__=1;return;}*ch=c;ch++;while((c=gc())!=EOF&&!isspace(c))*ch=c,ch++;if(c==EOF)__=1;*ch='\0';}template<typename T>il void in(T &x){if(__)return;char c=gc();bool f=0;while(c!=EOF&&(c<'0'||c>'9'))f^=(c=='-'),c=gc();if(c==EOF){__=1;return;}x=0;while(c!=EOF&&'0'<=c&&c<='9')x=x*10+c-48,c=gc();if(c==EOF)__=1;if(f)x=-x;}template<typename T,typename ... arr>il void in(T &x,arr & ... y){in(x),in(y...);}const char ln='\n';static char out_buf[str],*out_s=out_buf,*out_t=out_buf+str;il void flush(){fwrite(out_buf,1,out_s-out_buf,stdout);out_s=out_buf;}il void pt(char c){(out_s==out_t)?(fwrite(out_s=out_buf,1,str,stdout),*out_s++=c):(*out_s++=c);}il void out(const char* s){while(*s)pt(*s++);}il void out(char* s){while(*s)pt(*s++);}il void out(char c){pt(c);}template<typename T>il void out(T x){if(!x){pt('0');return;}if(x<0)pt('-'),x=-x;char a[50],t=0;while(x)a[t++]=x%10,x/= 10;while(t--)pt(a[t]+'0');}template<typename T,typename ... arr>il void out(T x,arr & ... y){out(x),out(y...);}}using namespace IO;
const int N=2000001;
int n,ans[N],s[N];
struct que{
    int typ,id,x,y,v;
    il bool operator<(que t){return x<t.x;}
}Q[N],T[N];
il void add(int x,int v){for(;x<=n;x+=x&-x)s[x]+=v;}
il int ask(int x){int res=0;for(;x;x^=x&-x)res+=s[x];return res;}
void cdq(int l,int r){
    if(l>=r)return;
    int m=l+r>>1,j=l;
    cdq(l,m),cdq(m+1,r);
    fur(i,m+1,r)if(!Q[i].typ){
        for(;j<=m&&Q[j].x<=Q[i].x;++j)if(Q[j].typ)add(Q[j].y,Q[j].v);
        ans[Q[i].id]+=Q[i].v*ask(Q[i].y);
    }
    fur(i,l,j-1)if(Q[i].typ)add(Q[i].y,-Q[i].v);
    for(int i=l,p=l,q=m+1;i<=r;++i)
        if(p>m)T[i]=Q[q++];
        else if(q>r)T[i]=Q[p++];
        else T[i]=Q[p]<Q[q]?Q[p++]:Q[q++];
    fur(i,l,r)Q[i]=T[i];
}
int main(){
    int x,y,X,Y,a,opt,q=0,d=0;
    in(x,y);
    while(1){
        in(opt);if(opt==3)break;
        if(opt==1)in(x,y,a),Q[++q]={1,0,x,y,a},cmax(n,y);
        else in(x,y,X,Y),++d,
        Q[++q]={0,d,X,Y,1},
        Q[++q]={0,d,X,y-1,-1},
        Q[++q]={0,d,x-1,Y,-1},
        Q[++q]={0,d,x-1,y-1,1},
        cmax(n,y),cmax(n,Y);
    }
    cdq(1,q);
    fur(i,1,d)out(ans[i],ln);
    flush();
}
```
