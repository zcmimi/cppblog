---
author: zc
avatar: null
categories:
- - "\u5237\u9898\u8BB0\u5F55"
commnet: 1
date: 2020-03-21 23:31
html: "<details><summary>\u67E5\u770B\u539F\u9898</summary><div id='from'></div><p><button\
  \ onclick=\"document.getElementById('from').innerHTML='<iframe src=&quot;https://www.luogu.com.cn/problem/P4169&quot;\
  \ width=100% height=800px style=&quot;border: none;&quot;><iframe>'\" class='mdui-btn\
  \ mdui-btn-raised mdui-ripple'>\u70B9\u51FB\u52A0\u8F7D</button><a class='mdui-btn\
  \ mdui-btn-raised mdui-ripple' href=\"https://www.luogu.com.cn/problem/P4169\" target='_blank'>\u70B9\
  \u51FB\u8DF3\u8F6C</a><p></details>"
permalink: "LG 4169 [Violet]\u5929\u4F7F\u73A9\u5076"
tags:
- "\u79BB\u7EBF"
- "cdq\u5206\u6CBB"
- "\u6570\u636E\u7ED3\u6784"
- kdt
thumbnail: null
title: "LG 4169 [Violet]\u5929\u4F7F\u73A9\u5076"
top: 0
---
允许离线处理

可以看成三维偏序(坐标和时间)

考虑如果要求的点都在当前点的左上方

那么也就是要求$x_j\le x_i,y_j\le y_i,time_j\le time_i$

$x_i+y_i-\max(x_j+y_j)$

坐标再旋转并处理三次就可以了
```cpp
#include<bits/stdc++.h>
#define il inline
il void cmax(int &x,int y){x=x>y?x:y;}
il void cmin(int &x,int y){x=x<y?x:y;}
namespace IN{const int str=1<<20;static char in_buf[str],*in_s,*in_t;bool __=0;il char gc(){return (in_s==in_t)&&(in_t=(in_s=in_buf)+fread(in_buf,1,str,stdin)),in_s==in_t?EOF:*in_s++;}template<typename T>il void in(T &x){if(__)return;char c=gc();bool f=0;while(c!=EOF&&(c<'0'||c>'9'))f^=(c=='-'),c=gc();if(c==EOF){__=1;return;}x=0;while(c!=EOF&&'0'<=c&&c<='9')x=x*10+c-48,c=gc();if(c==EOF)__=1;if(f)x=-x;}template<typename T,typename ... arr>il void in(T &x,arr & ... y){in(x),in(y...);}}using namespace IN;
namespace OUT{const char ln='\n';const int str=1<<20;static char out_buf[str],*out_s=out_buf,*out_t=out_buf+str;il void flush(){fwrite(out_buf,1,out_s-out_buf,stdout);out_s=out_buf;}il void pt(char c){(out_s==out_t)?(fwrite(out_s=out_buf,1,str,stdout),*out_s++=c):(*out_s++=c);}template<typename T>il void out(T x){if(!x){pt('0');return;}if(x<0)pt('-'),x=-x;char a[50],t=0;while(x)a[t++]=x%10,x/= 10;while(t--)pt(a[t]+'0');}template<typename T,typename ... arr>il void out(T x,arr & ... y){out(x),out(y...);}}using namespace OUT;
const int N=300011;
using std::merge;
int n,q,cnt=0,ans[N],s[1000011],limx,limy,nn;
struct node{
    int x,y,typ,id,ans;
    il bool operator <(node &t){return x<=t.x;}
}b[N<<1],a[N<<1],c[N<<1];
il void upd(int x,int v){for(;x<=limy;x+=x&-x)cmax(s[x],v);}
il int ask(int x){int res=0;for(;x;x-=x&-x)cmax(res,s[x]);return res;}
il void clr(int x){for(;x<=limy;x+=x&-x)if(s[x])s[x]=0;else break;}
void cdq(int l,int r){
    if(l>=r)return;
    int m=(l+r)>>1,j=l;
    cdq(l,m);cdq(m+1,r);
    for(int i=m+1;i<=r;++i)if(!a[i].typ){
        for(;j<=m&&a[j].x<=a[i].x;++j)if(a[j].typ)
            upd(a[j].y,a[j].x+a[j].y);
        int res=ask(a[i].y);
        if(res)cmin(ans[a[i].id],a[i].x+a[i].y-res);
    }
    for(int i=l;i<j;++i)if(a[i].typ)clr(a[i].y);
    merge(a+l,a+m+1,a+m+1,a+r+1,c+l);
    for(int i=l;i<=r;++i)a[i]=c[i];
}
il void del(){
    int rx=0,ry=0;nn=0;
    for(int i=1;i<=n;++i)if(!a[i].typ)
        cmax(rx,a[i].x),cmax(ry,a[i].y);
    for(int i=1;i<=n;++i)
        if(a[i].x<=rx&&a[i].y<=ry)c[++nn]=a[i];
    for(int i=1;i<=nn;++i)a[i]=c[i];
}
int main(){
    in(n,q);
    int x,y,typ;
    for(int i=1;i<=n;++i)
        in(x,y),++x,++y,b[i]=node{x,y,1,0,0},
        cmax(limx,x),cmax(limy,y);
    while(q--){
        in(typ,x,y);++x,++y;
        b[++n]=node{x,y,typ&1,cnt+=typ-1,0};
        cmax(limx,x),cmax(limy,y);
    }
    for(int i=1;i<=n;++i)a[i]=b[i];
    memset(ans,126,sizeof ans);
    ++limx,++limy;
    del(),cdq(1,nn);
    
    for(int i=1;i<=n;++i)a[i]=b[i],a[i].x=limx-a[i].x;
    del(),cdq(1,nn);

    for(int i=1;i<=n;++i)a[i]=b[i],a[i].y=limy-a[i].y;
    del(),cdq(1,nn);

    for(int i=1;i<=n;++i)a[i]=b[i],a[i].x=limx-a[i].x,a[i].y=limy-a[i].y;
    del(),cdq(1,nn);

    for(int i=1;i<=cnt;++i)out(ans[i]),pt('\n');
    flush();
}
```
