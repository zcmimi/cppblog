---
author: zc
avatar: null
categories:
- - "\u5237\u9898\u8BB0\u5F55"
commnet: 1
date: 2020-01-24 16:39
html: "<details><summary>\u67E5\u770B\u539F\u9898</summary><div id='from'></div><p><button\
  \ onclick=\"document.getElementById('from').innerHTML='<iframe src=&quot;&quot;\
  \ width=100% height=800px style=&quot;border: none;&quot;><iframe>'\" class='mdui-btn\
  \ mdui-btn-raised mdui-ripple'>\u70B9\u51FB\u52A0\u8F7D</button><a class='mdui-btn\
  \ mdui-btn-raised mdui-ripple' href=\"\" target='_blank'>\u70B9\u51FB\u8DF3\u8F6C\
  </a><p></details>"
permalink: "Acwing 361 \u521B\u4E16\u7EAA"
tags:
- "\u57FA\u73AF\u6811"
- "\u52A8\u6001\u89C4\u5212"
thumbnail: null
title: "Acwing 361 \u521B\u4E16\u7EAA"
top: 0
---
两次dp解决代替基环树dp

所有的$A_i\rightarrow i$构成了一棵基环树

我们先考虑如果基环树的子树怎么做

也就是树型dp

($f_x$表示不放,$g_x$表示放)

若元素$i$不投放,

$$f_x=\sum_{A_y=x}\max(f_y,g_y)$$

否则必须至少有一个元素限制$i$,不能投放

$$g_x=\max_{A_y=x}\{f_y+\sum_{A_z=x,z\not = y}\max(f_z,g_z)\}$$

找到环上的一个点,将它和它限制的那个点断开,先后进行两次树形dp,

第一次是假设环上的这个点对其限制的点不起限制作用

另外一次是强制环上那个点已经限制了其可以限制的点（也就是环上那个点不选）
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
namespace IO{const int str=1<<20;static char in_buf[str],*in_s,*in_t;bool __=0;il char gc(){return (in_s==in_t)&&(in_t=(in_s=in_buf)+fread(in_buf,1,str,stdin)),in_s==in_t?__=1,EOF:*in_s++;}il void in(string &ch){ch.clear();if(__)return;char c;while((c=gc())!=EOF&&isspace(c));if(c==EOF){__=1;return;}ch+=c;while((c=gc())!=EOF&&!isspace(c))ch+=c;if(c==EOF)__=1;}il void in(char &ch){if(__)return;char c;while((c=gc())!=EOF&&isspace(c));if(c==EOF)__=1;else ch=c;}il void in(char *ch){*ch='\0';if(__)return;char c;while((c=gc())!=EOF&&isspace(c));if(c==EOF){__=1;return;}*ch=c;ch++;while((c=gc())!=EOF&&!isspace(c))*ch=c,ch++;if(c==EOF)__=1;*ch='\0';}template<typename T>il void in(T &x){if(__)return;char c=gc();bool f=0;while(c!=EOF&&(c<'0'||c>'9'))f^=(c=='-'),c=gc();if(c==EOF){__=1;return;}x=0;while(c!=EOF&&'0'<=c&&c<='9')x=x*10+c-48,c=gc();if(c==EOF)__=1;if(f)x=-x;}template<typename T,typename ... arr>il void in(T &x,arr & ... y){in(x),in(y...);}const char ln='\n';static char out_buf[str],*out_s=out_buf,*out_t=out_buf+str;il void flush(){fwrite(out_buf,1,out_s-out_buf,stdout);out_s=out_buf;}il void pt(char c){(out_s==out_t)?(fwrite(out_s=out_buf,1,str,stdout),*out_s++=c):(*out_s++=c);}il void out(const char* s){while(*s)pt(*s++);}il void out(char* s){while(*s)pt(*s++);}il void out(char c){pt(c);}il void out(string s){for(int i=0;s[i];i++)pt(s[i]);}template<typename T>il void out(T x){if(!x){pt('0');return;}if(x<0)pt('-'),x=-x;char a[50],t=0;while(x)a[t++]=x%10,x/= 10;while(t--)pt(a[t]+'0');}template<typename T,typename ... arr>il void out(T x,arr & ... y){out(x),out(y...);}}using namespace IO;
const int N=1000011;
int n,cnt=0,head[N],A[N],f[N],g[N],RT;
struct edge{
    int to,nxt;
}e[N<<1];
il void add(int x,int y){
    e[++cnt].to=y;e[cnt].nxt=head[x];head[x]=cnt;
}
bool v[N];
void dp(int x){
    v[x]=1;f[x]=0;
    int res=inf;
    fl(i,x)if(to!=RT){
        dp(to);
        f[x]+=MAX(f[to],g[to]);
        res=MIN(res,MAX(g[to]-f[to],0));
    }
    g[x]=f[x]+1-res;
}

int main(){
    in(n);
    Fur(i,1,n)in(A[i]),add(A[i],i);
    int ans=0;
    Fur(i,1,n)if(!v[i]){
        int res=0;
        RT=i;
        while(!v[A[RT]]){
            v[RT]=1;
            RT=A[RT];
        }
        dp(RT);
        res=MAX(f[RT],g[RT]);
        RT=A[RT];
        dp(RT);
        ans+=MAX(res,MAX(f[RT],g[RT]));
    }
    printf("%d\n",ans);
}
```
