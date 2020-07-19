---
author: zc
avatar: null
categories:
- - "\u5237\u9898\u8BB0\u5F55"
commnet: 1
date: 2019-12-21 19:47
html: "<details><summary>\u67E5\u770B\u539F\u9898</summary><div id='from'></div><p><button\
  \ onclick=\"document.getElementById('from').innerHTML='<iframe src=&quot;https://www.luogu.com.cn/problem/CF242E&quot;\
  \ width=100% height=800px style=&quot;border: none;&quot;><iframe>'\" class='mdui-btn\
  \ mdui-btn-raised mdui-ripple'>\u70B9\u51FB\u52A0\u8F7D</button><a class='mdui-btn\
  \ mdui-btn-raised mdui-ripple' href=\"https://www.luogu.com.cn/problem/CF242E\"\
  \ target='_blank'>\u70B9\u51FB\u8DF3\u8F6C</a><p></details>"
permalink: LG CF242E XOR-on-Segment
tags:
- "\u7EBF\u6BB5\u6811"
- "\u4F4D\u8FD0\u7B97"
thumbnail: null
title: LG CF242E XOR-on-Segment
top: 0
---
直接建立20棵线段树统计$1,2,4,8,...,2^20$就可以了

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
#define N 100011
#define int ll
#define ls rt<<1
#define rs rt<<1|1
#define pu s[rt]=s[ls]+s[rs]
int n;
struct seg{
    int s[N<<2],laz[N<<2];
    void pd(int rt,int ln,int rn){
        if(laz[rt]){
            laz[ls]^=1;
            laz[rs]^=1;
            s[ls]=ln-s[ls];
            s[rs]=rn-s[rs];
            laz[rt]=0;
        }
    }
    void upd(int L,int R,int l,int r,int rt){
        if(L<=l&&r<=R){
            s[rt]=r-l+1-s[rt];
            laz[rt]^=1;
            return;
        }
        int m=(l+r)>>1;
        pd(rt,m-l+1,r-m);
        if(L<=m)upd(L,R,l,m,ls);
        if(R>m)upd(L,R,m+1,r,rs);
        pu;
    }
    int ask(int L,int R,int l,int r,int rt){
        if(L<=l&&r<=R)return s[rt];
        int m=(l+r)>>1,ans=0;
        pd(rt,m-l+1,r-m);
        if(L<=m)ans=ask(L,R,l,m,ls);
        if(R>m)ans+=ask(L,R,m+1,r,rs);
        return ans;
    }
}T[21];
signed main(){
    in(n);
    int q,opt,l,r,x;
    Fur(i,1,n){
        in(x);
        Fur(j,0,20){
            if(x&1)T[j].upd(i,i,1,n,1);
            x>>=1;
        }
    }
    in(q);
    while(q--){
        in(opt,l,r);
        if(opt==1){
            ll ans=0;
            Fur(i,0,20)ans+=(1<<i)*T[i].ask(l,r,1,n,1);
            out(ans,ln);
        }
        else{
            in(x);
            Fur(i,0,20){
                if(x&1)T[i].upd(l,r,1,n,1);
                x>>=1;
            }
        }
    }
    flush();
}
```
