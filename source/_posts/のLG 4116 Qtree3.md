---
author: zc
avatar: null
categories:
- - 刷题记录
commnet: 1
date: 2019-12-21 19:47
html: '<details><summary>查看原题</summary><div id=''from''></div><p><button onclick="document.getElementById(''from'').innerHTML=''<iframe
  src=&quot;https://www.luogu.com.cn/problem/P4116&quot; width=100% height=800px style=&quot;border:
  none;&quot;><iframe>''" class=''mdui-btn mdui-btn-raised mdui-ripple''>点击加载</button><a
  class=''mdui-btn mdui-btn-raised mdui-ripple'' href="https://www.luogu.com.cn/problem/P4116"
  target=''_blank''>点击跳转</a><p></details>'
permalink: LG 4116 Qtree3
tags:
- 树链剖分
- set
- 二分
thumbnail: null
title: LG 4116 Qtree3
top: 0
---
在每条重链上搞一个set

或者用线段树+二分
```cpp
// luogu-judger-enable-o2
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
    #define Fur(i,x,y) for(int i=x;i<=y;i++)
    #define Fdr(i,x,y) for(int i=x;i>=y;i--)
    #define fl(i,x) for(int i=head[x],to;to=e[i].to,i;i=e[i].nxt)
    #define clr(x,y) memset(x,y,sizeof(x))
    #define cpy(x,y) memcpy(x,y,sizeof(x))
    #define fin(s) freopen(s".in","r",stdin)
    #define fout(s) freopen(s".out","w",stdout)
    #define fcin ios::sync_with_stdio(false)
    #define l2(n) (int(log2(n)))
    #define inf 0x3f3f3f3f
    MB T ABS(T x){return x>0?x:-x;}
    MB T MAX(T x,T y){return x>y?x:y;}
    MB T MIN(T x,T y){return x<y?x:y;}
    MB T GCD(T x,T y){return y?GCD(y,x%y):x;}
    MB void SWAP(T &x,T &y){T t=x;x=y;y=t;}
}using namespace ZDY;using namespace std;
namespace IO{const char* ln="\n";const int str=1<<20;struct IN{char buf[str],*s,*t;bool _;IN():s(buf),t(buf),_(0){}il char gc(){return s==t&&((t=(s=buf)+fread(buf,1,str,stdin))==s)?EOF:(*s++);}IN&operator>>(char&ch){if(_)return *this;char c;while((c=gc())!=EOF&&isspace(c));if(c==EOF)_=1;else ch=c;return *this;}IN& operator>>(char* ch){if(_)return *this;char c;while((c=gc())!=EOF&&isspace(c));if(c==EOF)return _=1,*this;*ch=c;ch++;while((c=gc())!=EOF&&!isspace(c))*ch=c,ch++;if(c==EOF)_=1;return *this;}IN& operator>>(string& ch){if(_)return *this;char c;while((c=gc())!=EOF&&isspace(c));if(c==EOF)return _=1,*this;ch+=c;while((c=gc())!=EOF&&!isspace(c))ch+=c;if(c==EOF)_=1;return *this;}template<typename T>IN&operator>>(T&x){if(_)return *this;char c=gc();bool ff=0;while(c!=EOF&&(c<'0'||c>'9'))ff^=(c=='-'),c=gc();if(c==EOF){_=1;return *this;}x=0;while(c!=EOF&&'0'<=c&&c<='9')x=(x<<3)+(x<<1)+c-48,c=gc();if(c==EOF)_=1;if(ff)x=-x;return *this;}}in;struct OUT{char buf[str],*s,*t;OUT():s(buf),t(buf+str){}~OUT(){fwrite(buf,1,s-buf,stdout);}void pt(char c){(s==t)?(fwrite(s=buf,1,str,stdout),*s++=c):(*s++=c);}OUT&operator<<(const char*s){while(*s)pt(*s++);return *this;}OUT&operator<<(char*s){while(*s)pt(*s++);return *this;}OUT&operator<<(string s){for(int i=0;s[i];i++)pt(s[i]);return *this;}template<typename T>OUT&operator<<(T x){if(!x)return pt('0'),*this;if(x<0)pt('-'),x=-x;char a[30],t=0;while(x)a[t++]=x%10,x/=10;while(t--)pt(a[t]+'0');return *this;}}out;}using namespace IO;
#define N 100011
#define ls rt<<1
#define rs rt<<1|1
int head[N],n,q,sz=0,cnt=0;
int top[N],d[N],f[N],siz[N],id[N],dfn[N];
bool ff[N];
set<int>mi[N]; 
struct edge{
    int to,nxt;
}e[N*2];
void add(int x,int y){
    e[++cnt].to=y;e[cnt].nxt=head[x];head[x]=cnt;
}
void dfs(int x){
    siz[x]=1;
    fl(i,x)if(to!=f[x]){
        f[to]=x;d[to]=d[x]+1;
        dfs(to);siz[x]+=siz[to];
    }
}
void bt(int x,int tp){
    top[x]=tp;dfn[id[x]=++sz]=x;
    int k=0;
    fl(i,x)if(to!=f[x]&&siz[to]>siz[k])k=to;
    if(!k)return;bt(k,tp);
    fl(i,x)if(!top[to])bt(to,to);
}
int main(){
    in>>n>>q;
    int x,y,u,ans;
    Fur(i,1,n-1)in>>x>>y,add(x,y),add(y,x);
    dfs(1);bt(1,1);
    while(q--){
        in>>u>>x;
        if(u==0){
            if(ff[x])mi[top[x]].erase(id[x]);
            else mi[top[x]].insert(id[x]);
            ff[x]^=1;
        }
        else{
            ans=-1;
            while(x){
                int k=*mi[top[x]].begin();
                if(mi[top[x]].size()&&d[dfn[k]]<=d[x])ans=dfn[k];
                x=f[top[x]];
            }
            out<<ans<<ln;
        }
    }
}

```
