---
author: zc
avatar: null
categories:
- - 刷题记录
commnet: 1
date: 2019-12-21 19:47
html: '<details><summary>查看原题</summary><div id=''from''></div><p><button onclick="document.getElementById(''from'').innerHTML=''<iframe
  src=&quot;https://www.luogu.com.cn/problem/CF891C&quot; width=100% height=800px
  style=&quot;border: none;&quot;><iframe>''" class=''mdui-btn mdui-btn-raised mdui-ripple''>点击加载</button><a
  class=''mdui-btn mdui-btn-raised mdui-ripple'' href="https://www.luogu.com.cn/problem/CF891C"
  target=''_blank''>点击跳转</a><p></details>'
permalink: LG CF891C Envy
tags:
- kruskal
thumbnail: null
title: LG CF891C Envy
top: 0
---
关于同一张图上的最小生成树,有一些性质：

对于任意权值的边,所有最小生成树中这个权值的边的数量是一定的

对于任意正确加边方案,加完小于某权值的所有边后图的连通性是一样的
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
#define N 500011
int n,m,q;
struct link{
    int x,y,w,id,bx,by;
}E[N],tmp[N];
bool cmp(link x,link y){return x.w<y.w;}
bool CMP(link x,link y){return x.id<y.id;}
int f[N];
int gf(int x){return (x==f[x])?x:(f[x]=gf(f[x]));}
il void mg(int x,int y){f[gf(y)]=gf(x);}
int cnt[N];
int main(){
    in(n,m);
    int x,y,w;
    Fur(i,1,m){
        in(x,y,w);
        E[i]=link{x,y,w,i,0,0};
    }
    sort(E+1,E+m+1,cmp);
    Fur(i,1,n)f[i]=i;
    E[0].w=-1;
    for(int i=1;i<=m;){
        int j=i;
        do{
            E[j].bx=gf(E[j].x);
            E[j].by=gf(E[j].y);
            ++j;
        }while(j<=m&&E[j].w==E[j-1].w);
        while(i<j){
            while(gf(E[i].x)==gf(E[i].y)&&i<j)++i;
            if(i<j)mg(E[i].x,E[i].y);
        }
    }
    sort(E+1,E+m+1,CMP);
    in(q);
    Fur(i,1,n)f[i]=i;
    while(q--){
        bool ff=1;
        int t;in(t);
        Fur(i,1,t){
            in(x);
            tmp[i]=E[x];
        }
        sort(tmp+1,tmp+t+1,cmp);
        int tot=0;
        Fur(i,1,t){
            x=tmp[i].bx,y=tmp[i].by;
            if(x==y){ff=0;break;}
            mg(x,y);
            int j=i+1;
            while(j<=t&&tmp[j].w==tmp[i].w){
                if(gf(tmp[j].bx)==gf(tmp[j].by)){ff=0;break;}
                mg(tmp[j].bx,tmp[j].by);++j;
            }
            while(i<j)f[tmp[i].bx]=tmp[i].bx,f[tmp[i].by]=tmp[i].by,++i;
        }
        if(ff)out("YES\n");
        else out("NO\n");
    }
    flush();
}
```
