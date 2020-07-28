---
author: zc
avatar: null
categories:
- - 刷题记录
commnet: 1
date: 2019-12-21 19:47
html: '<details><summary>查看原题</summary><div id=''from''></div><p><button onclick="document.getElementById(''from'').innerHTML=''<iframe
  src=&quot;https://www.luogu.com.cn/problem/CF741D&quot; width=100% height=800px
  style=&quot;border: none;&quot;><iframe>''" class=''mdui-btn mdui-btn-raised mdui-ripple''>点击加载</button><a
  class=''mdui-btn mdui-btn-raised mdui-ripple'' href="https://www.luogu.com.cn/problem/CF741D"
  target=''_blank''>点击跳转</a><p></details>'
permalink: LG CF741D Arpa’s letter-marked tree and Mehrdad’s Dokhtar-kosh paths
tags:
- 静态链分治
- 状态压缩
- 桶
thumbnail: null
title: LG CF741D Arpa’s letter-marked tree and Mehrdad’s Dokhtar-kosh paths
top: 0
---
好题！

重新排序后能变成回文串,出现次数为奇数的字母最多只能有一种

因为只有$22$种字符所以我们可以用状态压缩来记录每种字母出现的次数是奇数或者偶数

设路径端点的两端为$x,y$,$d_x$表示1~x所有状态的异或值,$D_x$表示$x$的深度

那么如果这条路径满足条件,则$d_x \oplus d_y$在二进制下最多只有一个$1$

它的长度为$D_x + D_y - 2 \times D_{lca(x,y)}$

我们可以开一个桶来记录每种状态出现的最深的位置是哪里

设$sta$为满足条件的状态

用每个店更新答案的时候就$ans=\max(ans,b[sta \oplus d_x] + D_x - 2 \times D_{lca})$

接下来就按静态链分治的套路操作就可以了

复杂度: $\Theta( n \log n)$
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
    #define Fur(i,x,y) for(int i=x;i<=y;++i)
    #define Fdr(i,x,y) for(int i=x;i>=y;--i)
    #define fl(i,x) for(int i=head[x],to;to=e[i].to,i;i=e[i].nxt)
    #define clr(x,y) memset(x,y,sizeof(x))
    #define cpy(x,y) memcpy(x,y,sizeof(x))
    #define fin(s) freopen(s".in","r",stdin)
    #define fout(s) freopen(s".out","w",stdout)
    #define fcin ios::sync_with_stdio(false)
    #define l2(n) ((int)(log2(n)))
    #define inf 0x3f3f3f3f
    MB T ABS(T x){return x>0?x:-x;}
    MB T MAX(T x,T y){return x>y?x:y;}
    MB T MIN(T x,T y){return x<y?x:y;}
    MB T GCD(T x,T y){return y?GCD(y,x%y):x;}
    MB void SWAP(T &x,T &y){T t=x;x=y;y=t;}
}using namespace ZDY;using namespace std;
namespace IO{const char* ln="\n";const int str=1<<20;struct IN{char buf[str],*s,*t;bool _;IN():s(buf),t(buf),_(0){}il char gc(){return s==t&&((t=(s=buf)+fread(buf,1,str,stdin))==s)?EOF:(*s++);}IN&operator>>(char&ch){if(_)return *this;char c;while((c=gc())!=EOF&&isspace(c));if(c==EOF)_=1;else ch=c;return *this;}IN& operator>>(char* ch){clr(ch,0);if(_)return *this;char c;while((c=gc())!=EOF&&isspace(c));if(c==EOF)return _=1,*this;*ch=c;ch++;while((c=gc())!=EOF&&!isspace(c))*ch=c,ch++;if(c==EOF)_=1;return *this;}IN& operator>>(string& ch){if(_)return *this;char c;while((c=gc())!=EOF&&isspace(c));if(c==EOF)return _=1,*this;ch+=c;while((c=gc())!=EOF&&!isspace(c))ch+=c;if(c==EOF)_=1;return *this;}template<typename T>IN&operator>>(T&x){if(_)return *this;char c=gc();bool ff=0;while(c!=EOF&&(c<'0'||c>'9'))ff^=(c=='-'),c=gc();if(c==EOF){_=1;return *this;}x=0;while(c!=EOF&&'0'<=c&&c<='9')x=(x<<3)+(x<<1)+c-48,c=gc();if(c==EOF)_=1;if(ff)x=-x;return *this;}}in;struct OUT{char buf[str],*s,*t;OUT():s(buf),t(buf+str){}~OUT(){fwrite(buf,1,s-buf,stdout);}void pt(char c){(s==t)?(fwrite(s=buf,1,str,stdout),*s++=c):(*s++=c);}OUT&operator<<(const char*s){while(*s)pt(*s++);return *this;}OUT&operator<<(char*s){while(*s)pt(*s++);return *this;}OUT&operator<<(string s){for(int i=0;s[i];i++)pt(s[i]);return *this;}template<typename T>OUT&operator<<(T x){if(!x)return pt('0'),*this;if(x<0)pt('-'),x=-x;char a[30],t=0;while(x)a[t++]=x%10,x/=10;while(t--)pt(a[t]+'0');return *this;}}out;}using namespace IO;
#define N 500011
int n,d[N],siz[N],son[N],D[N];
int cnt=0,head[N];
struct edge{
    int to,nxt,w;
}e[N];
void add(int x,int y,int w){
    e[++cnt].to=y;e[cnt].w=w;e[cnt].nxt=head[x];head[x]=cnt;
}
void dfs(int x){
    siz[x]=1;
    fl(i,x){
        d[to]=d[x]^e[i].w;D[to]=D[x]+1;
        dfs(to);siz[x]+=siz[to];
        if(siz[to]>siz[son[x]])son[x]=to;
    }
}
int b[1<<22],ans=0,sta[23],lca;
void Add(int x){
    Fur(i,0,22)
        ans=MAX(ans,D[x]+b[sta[i]^d[x]]-2*D[lca]);
    b[d[x]]=MAX(b[d[x]],D[x]);
}
void upd(int x){
    Add(x);
    fl(i,x)upd(to);
}
void dde(int x){
    b[d[x]]=-inf;
    fl(i,x)dde(to);
}
int ANS[N];
void sol(int x){
    fl(i,x)if(to!=son[x]){
        sol(to);
        // dde(to);
        clr(b,128);
        ans=0;
        ANS[x]=MAX(ANS[x],ANS[to]);
    }
    if(son[x])sol(son[x]),ANS[x]=MAX(ANS[x],ANS[son[x]]);
    lca=x;
    Add(x);
    fl(i,x)if(to!=son[x])upd(to);
    ANS[x]=MAX(ANS[x],ans);
}
int main(){
    fin("in");
    in>>n;
    int x;char w;
    Fur(i,2,n)in>>x>>w,add(x,i,(1<<(w-'a')));
    dfs(1);
    sta[0]=0;
    Fur(i,1,22)sta[i]=(1<<(i-1));
    sol(1);
    Fur(i,1,n)out<<ANS[i]<<" ";
}
```
