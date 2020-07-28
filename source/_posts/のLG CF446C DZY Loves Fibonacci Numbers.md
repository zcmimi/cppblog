---
author: zc
avatar: null
categories:
- - 刷题记录
commnet: 1
date: 2019-12-21 19:47
html: '<details><summary>查看原题</summary><div id=''from''></div><p><button onclick="document.getElementById(''from'').innerHTML=''<iframe
  src=&quot;https://www.luogu.com.cn/problem/CF446C&quot; width=100% height=800px
  style=&quot;border: none;&quot;><iframe>''" class=''mdui-btn mdui-btn-raised mdui-ripple''>点击加载</button><a
  class=''mdui-btn mdui-btn-raised mdui-ripple'' href="https://www.luogu.com.cn/problem/CF446C"
  target=''_blank''>点击跳转</a><p></details>'
permalink: LG CF446C DZY Loves Fibonacci Numbers
tags:
- 线段树
thumbnail: null
title: LG CF446C DZY Loves Fibonacci Numbers
top: 0
---
打算直接把标记用$vector$记录里,以为可以水过去,结果mle了

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
#define N 300011
#define ls rt<<1
#define rs rt<<1|1
#define mod 1000000009
#define pu s[rt]=(s[ls]+s[rs])%mod
int n,q;
ll f[N],sf[N],s[N<<2];
vector<int>add[N<<2];
void build(int l,int r,int rt){
    if(l==r){
        in>>s[rt];
        return;
    }
    int m=(l+r)>>1;
    build(l,m,ls);build(m+1,r,rs);
    pu;
}
int get(int p,int len){
    return (sf[p+len-1]-sf[p-1]+mod)%mod;
}
void pd(int rt,int ln,int rn){
    if(add[rt].empty())return;
    Fur(i,0,add[rt].size()-1){
        int v=add[rt][i];
        add[ls].push_back(v);
        add[rs].push_back(v+ln);
        s[ls]+=get(v,ln);
        s[rs]+=get(v+ln,rn);
    }
    add[rt].clear();
}
void upd(int L,int R,int l,int r,int rt){
    if(L<=l&&r<=R){
        s[rt]=(s[rt]+get(l-L+1,r-l+1))%mod;
        add[rt].push_back(l-L+1);
        return;
    }
    int m=(l+r)>>1;
    pd(rt,m-l+1,r-m);
    if(L<=m)upd(L,R,l,m,ls);
    if(R>m)upd(L,R,m+1,r,rs);
    pu;
}
int ask(int L,int R,int l,int r,int rt){
    if(L<=l&&r<=R)return s[rt]%mod;
    int m=(l+r)>>1,ans=0;
    pd(rt,m-l+1,r-m);
    if(L<=m)ans=ask(L,R,l,m,ls);
    if(R>m)ans+=ask(L,R,m+1,r,rs);
    return ans%mod;
}
signed main(){
    in>>n>>q;
    f[1]=f[2]=1;
    Fur(i,3,n)f[i]=(f[i-1]+f[i-2])%mod;
    Fur(i,1,n)sf[i]=(sf[i-1]+f[i])%mod;
    build(1,n,1);
    int l,r,u;
    while(q--){
        in>>u>>l>>r;
        if(u==1)upd(l,r,1,n,1);
        else out<<ask(l,r,1,n,1)<<ln;
    }
}
```

[正解：](https://xiaohuang888.github.io/2019/08/02/%E3%80%8E%E9%A2%98%E8%A7%A3%E3%80%8FCodeforces446C%20DZY%20Loves%20Fibonacci%20Numbers)

设$S_n=\sum_{i=1}^n f_i$

$S_n = f_{n+2} - f_2$

证明：

$S_{i+1}=S_i + f_{i+1} = f_{i+2} - f_2 + f_{i+1} = f_{i+3} - f_2$

任意两段不同的广义斐波那契数列段相加（逐项相加）,所得的数列任然是广义斐波那契数列。


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
#define N 300011
#define ls rt<<1
#define rs rt<<1|1
#define mod 1000000009
int n,q;
ll f[N],S[N],s[N<<2],sum[N],a1[N<<2],a2[N<<2];
void pu(int rt,int p){
    a1[rt]%=mod,a2[rt]%=mod;
    s[rt]=(s[ls]+s[rs]+a1[rt]*f[p]+a2[rt]*f[p+1]-a2[rt])%mod;
}
void pd(int rt,int ln,int rn){
    if(!a1[rt]&&!a2[rt])return;
    a1[ls]+=a1[rt];a1[rs]+=a1[rt]*(ln-1)+a2[rt]*f[ln];
    a2[ls]+=a2[rt];a2[rs]+=a1[rt]*ln+a2[rt]*f[ln+1];
    a1[rt]=a2[rt]=0;
    pu(ls,ln);pu(rs,rn);
}
void upd(int L,int R,int l,int r,int rt){
    if(L<=l&&r<=R){
        a1[rt]+=f[l-L+1];a1[rt]%=mod;
        a2[rt]+=f[l-L+2];a2[rt]%=mod;
        pu(rt,r-l+1);
        return;
    }
    int m=(l+r)>>1;
    pd(rt,m-l+1,r-m);
    if(L<=m)upd(L,R,l,m,ls);
    if(R>m)upd(L,R,m+1,r,rs);
    pu(rt,r-l+1);
}
int ask(int L,int R,int l,int r,int rt){
    if(L<=l&&r<=R)return s[rt]%mod;
    int m=(l+r)>>1,ans=0;
    pd(rt,m-l+1,r-m);
    if(L<=m)ans=ask(L,R,l,m,ls);
    if(R>m)ans+=ask(L,R,m+1,r,rs);
    return ans%mod;
}
signed main(){
    fin("in");
    in>>n>>q;
    f[1]=f[2]=1;
    Fur(i,3,n+1)f[i]=(f[i-1]+f[i-2])%mod;
    Fur(i,1,n+1)S[i]=(S[i-1]+f[i])%mod;
    Fur(i,1,n)in>>sum[i],sum[i]+=sum[i-1];
    int l,r,u;
    while(q--){
        in>>u>>l>>r;
        if(u==1)upd(l,r,1,n,1);
        else out<<(ask(l,r,1,n,1)+(sum[r]-sum[l-1]+mod)%mod)%mod<<ln;
    }
}
```
