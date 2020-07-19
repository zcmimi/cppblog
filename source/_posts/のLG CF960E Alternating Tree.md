---
author: zc
avatar: null
categories:
- - "\u5237\u9898\u8BB0\u5F55"
commnet: 1
date: 2019-12-21 19:47
html: "<details><summary>\u67E5\u770B\u539F\u9898</summary><div id='from'></div><p><button\
  \ onclick=\"document.getElementById('from').innerHTML='<iframe src=&quot;https://www.luogu.com.cn/problem/CF960E&quot;\
  \ width=100% height=800px style=&quot;border: none;&quot;><iframe>'\" class='mdui-btn\
  \ mdui-btn-raised mdui-ripple'>\u70B9\u51FB\u52A0\u8F7D</button><a class='mdui-btn\
  \ mdui-btn-raised mdui-ripple' href=\"https://www.luogu.com.cn/problem/CF960E\"\
  \ target='_blank'>\u70B9\u51FB\u8DF3\u8F6C</a><p></details>"
permalink: LG CF960E Alternating Tree
tags:
- "\u52A8\u6001\u89C4\u5212"
- "\u6811\u5F62dp"
thumbnail: null
title: LG CF960E Alternating Tree
top: 0
---
这篇题解可能是对楼下的补充

我们考虑每个点能贡献多少次

![无标题.png](https://i.loli.net/2019/10/25/Evy74V8rpIaec1F.png)

设当前节点为$x$,路径有三种情况,上图分别对应情况$1$,情况$2$,情况$3$

1. $x$子树内$\rightarrow x \rightarrow x$子树外(包括$x$)
    
2. $x$子树内(包括$x$)$\rightarrow x \rightarrow x$子树内

3. $x$子树外$\rightarrow x \rightarrow x$子树内

我们可以先处理出与$x$的距离为偶数和与$x$的距离为奇数的点的个数,分别记作$f_x,g_x$

那么$f_x = 1 + \sum g_{to},g_x = 1 + \sum f_{to}$($to$指$x$的孩子)

我们来考虑所有情况

1. $ans += V_x \times (f_x-g_x) \times (n-siz_x+1)$(可以在$x$的子树中随机选一个往子树外面走(可以指走到$x$))

2. $ans += V_x \times (g_{to}-f_{to}) \times (siz_x-siz_{to}-1)$
  
   $ans+= V_x \times (siz_x-1)$(可以从$x$直接向下走)

3. 我们需要记录$x$子树外与$x$的距离为偶数和与$x$的距离为奇数的点的个数,分别记作$uf_x,ug_x$

	我们可以通过$bfs$从上到下来处理,那么
    
   $uf_x=ug_{fa_x}+g_{fa_x}-f_x$
    
   $ug_x=uf_{fa_x}+f_{fa_x}-g_x$
   
   $ans += V_x \times (uf_x-ug_x) \times siz_x$
   
接下来放代码：
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
#define N 200011
const ll mod = 1000000007;
int n,cnt=0,head[N];
ll ans=0;
struct edge{
    int to,nxt;
}e[N*2];
il void add(int x,int y){
    e[++cnt].to=y;e[cnt].nxt=head[x];head[x]=cnt;
}
int a[N],siz[N],f[N],g[N],fa[N];
il ll mo(ll x,ll y){
    if(x>y)return x-y;
    return x;
}
#define A%B mo(A,B)
void dfs(int x){
    f[x]=siz[x]=1;
    fl(i,x)if(to!=fa[x]){
        fa[to]=x;dfs(to);
        siz[x]+=siz[to];
        f[x]+=g[to];
        g[x]+=f[to];
    }
    // 1:
    ans=(ans+1ll*(f[x]-g[x])*(n-siz[x]+1)%mod*a[x]%mod)%mod;
    //2:
    ans=(ans+1ll*(siz[x]-1)*a[x]%mod)%mod;
    fl(i,x)if(to!=fa[x])
        ans=(ans+1ll*(g[to]-f[to])*(siz[x]-siz[to]-1)%mod*a[x]%mod)%mod;
}
int uf[N],ug[N];
il void bfs(){
    queue<int>q;
    fl(i,1)q.push(to);
    while(!q.empty()){
        int x=q.front();q.pop();
        uf[x]=ug[fa[x]]+g[fa[x]]-f[x];
        ug[x]=uf[fa[x]]+f[fa[x]]-g[x];
        ans=(ans+1ll*(uf[x]-ug[x])*siz[x]%mod*a[x]%mod)%mod;
        fl(i,x)if(to!=fa[x])q.push(to);
    }
}
int main(){
    fin("in");
    in>>n;
    Fur(i,1,n)in>>a[i];
    int x,y;
    Fur(i,1,n-1)in>>x>>y,add(x,y),add(y,x);
    dfs(1);
    bfs();
    cout<<(ans+mod)%mod<<endl;
}
```
