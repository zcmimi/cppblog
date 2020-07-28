---
author: zc
avatar: null
categories:
- - 刷题记录
commnet: 1
date: 2019-12-21 19:47
html: '<details><summary>查看原题</summary><div id=''from''></div><p><button onclick="document.getElementById(''from'').innerHTML=''<iframe
  src=&quot;https://www.luogu.com.cn/problem/P3121&quot; width=100% height=800px style=&quot;border:
  none;&quot;><iframe>''" class=''mdui-btn mdui-btn-raised mdui-ripple''>点击加载</button><a
  class=''mdui-btn mdui-btn-raised mdui-ripple'' href="https://www.luogu.com.cn/problem/P3121"
  target=''_blank''>点击跳转</a><p></details>'
permalink: LG 3121 [USACO15FEB]审查（黄金）Censoring-
tags:
- AC自动机
- 栈
- kmp
- hash
thumbnail: null
title: LG 3121 [USACO15FEB]审查（黄金）Censoring-
top: 0
---
用`LG 4824 [USACO15FEB]Censoring"`的做法hash,kmp什么的因为数据水所以跑不满可以水过去

还是练一下AC自动机吧

解释见代码
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
int n,c[N][26],cnt=0,ed[N];
char s[N],ch[N];
il void ins(){
    int now=0,len=strlen(ch+1);
    Fur(i,1,len){
        int x=ch[i]-'a';
        if(!c[now][x])c[now][x]=++cnt;
        now=c[now][x];
    }
    ed[now]=len;
}
int q[N],fail[N];
il void ac(){
    int h=0,t=0;
    Fur(i,0,25)
        if(c[0][i])q[t++]=c[0][i];
    while(h<t){
        int now=q[h++];
        Fur(i,0,25){
            if(!c[now][i])
                c[now][i]=c[fail[now]][i];
            else
                fail[c[now][i]]=c[fail[now]][i],
                q[t++]=c[now][i];
        }
    }
}
int p[N];
int main(){
    in(s+1);
    in(n);
    Fur(i,1,n){
        in(ch+1);
        ins();//插入trie中
    }
    ac();// AC 自动机
    int tp=0,now=0,len=strlen(s+1);
    Fur(i,1,len){
        int x=s[i]-'a';
        now=c[now][x];
        q[++tp]=i;
        p[tp]=now;
        if(ed[now]){
            tp-=ed[now];
            if(!tp)now=0;
            else now=p[tp];
            //跳回之前
        }
    }
    Fur(i,1,tp)pt(s[q[i]]);
    flush();
}
```
