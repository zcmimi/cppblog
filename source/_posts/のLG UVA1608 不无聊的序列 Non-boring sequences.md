---
author: zc
avatar: null
categories:
- - 刷题记录
commnet: 1
date: 2020-01-04 10:21
html: '<details><summary>查看原题</summary><div id=''from''></div><p><button onclick="document.getElementById(''from'').innerHTML=''<iframe
  src=&quot;https://www.luogu.com.cn/problem/UVA1608&quot; width=100% height=800px
  style=&quot;border: none;&quot;><iframe>''" class=''mdui-btn mdui-btn-raised mdui-ripple''>点击加载</button><a
  class=''mdui-btn mdui-btn-raised mdui-ripple'' href="https://www.luogu.com.cn/problem/UVA1608"
  target=''_blank''>点击跳转</a><p></details>'
permalink: LG UVA1608 不无聊的序列 Non-boring sequences
tags:
- 分治
- 思维
thumbnail: null
title: LG UVA1608 不无聊的序列 Non-boring sequences
top: 0
---
我们先预处理出$L_i,R_i$分别表示与$a_i$相同的数出现在$i$左边和右边的位置

我们可以使用分治来判断一个区间是否合法

我们设当前区间为$[l,r]$

从两边一起找

假设枚举到位置$i$若$L_i＜l$且$R_i>r$,那么左端点在$[l,i]$,右端点在$[i,r]$的区间都是"non-boring"

这时我们只需要判断区间$[l,i-1]$和$[i+1,r]$是否合法就可以了

复杂度可以降至$\Theta(n \log n)$
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
    #define inf 2122219134
    MB T ABS(T x){return x>0?x:-x;}
    MB T MAX(T x,T y){return x>y?x:y;}
    MB T MIN(T x,T y){return x<y?x:y;}
    MB T GCD(T x,T y){return y?GCD(y,x%y):x;}
    MB void SWAP(T &x,T &y){T t=x;x=y;y=t;}
}using namespace ZDY;using namespace std;
namespace IO{const char* ln="\n";const int str=1<<20;struct IN{char buf[str],*s,*t;bool _;IN():s(buf),t(buf),_(0){}il char gc(){return s==t&&((t=(s=buf)+fread(buf,1,str,stdin))==s)?EOF:(*s++);}IN&operator>>(char&ch){if(_)return *this;char c;while((c=gc())!=EOF&&isspace(c));if(c==EOF)_=1;else ch=c;return *this;}IN& operator>>(char* ch){clr(ch,0);if(_)return *this;char c;while((c=gc())!=EOF&&isspace(c));if(c==EOF)return _=1,*this;*ch=c;ch++;while((c=gc())!=EOF&&!isspace(c))*ch=c,ch++;if(c==EOF)_=1;return *this;}IN& operator>>(string& ch){if(_)return *this;char c;while((c=gc())!=EOF&&isspace(c));if(c==EOF)return _=1,*this;ch+=c;while((c=gc())!=EOF&&!isspace(c))ch+=c;if(c==EOF)_=1;return *this;}template<typename T>IN&operator>>(T&x){if(_)return *this;char c=gc();bool ff=0;while(c!=EOF&&(c<'0'||c>'9'))ff^=(c=='-'),c=gc();if(c==EOF){_=1;return *this;}x=0;while(c!=EOF&&'0'<=c&&c<='9')x=(x<<3)+(x<<1)+c-48,c=gc();if(c==EOF)_=1;if(ff)x=-x;return *this;}}in;struct OUT{char buf[str],*s,*t;OUT():s(buf),t(buf+str){}~OUT(){fwrite(buf,1,s-buf,stdout);}void pt(char c){(s==t)?(fwrite(s=buf,1,str,stdout),*s++=c):(*s++=c);}OUT&operator<<(const char*s){while(*s)pt(*s++);return *this;}OUT&operator<<(char*s){while(*s)pt(*s++);return *this;}OUT&operator<<(string s){for(int i=0;s[i];i++)pt(s[i]);return *this;}template<typename T>OUT&operator<<(T x){if(!x)return pt('0'),*this;if(x<0)pt('-'),x=-x;char a[30],t=0;while(x)a[t++]=x%10,x/=10;while(t--)pt(a[t]+'0');return *this;}}out;}using namespace IO;
#define N 200011
int n,a[N],L[N],R[N];
map<int,int>mp;
bool chk(int l,int r){
    if(l>=r)return 1;
    int i=l,j=r;
    while(i<=j){
        if(L[i]<l&&R[i]>r)return chk(l,i-1)&&chk(i+1,r);
        if(L[j]<l&&R[j]>r)return chk(l,j-1)&&chk(j+1,r);
        ++i;--j;
    }
    return 0;
}
void work(){
    in>>n;
    Fur(i,1,n)in>>a[i];
    mp.clear();
    Fdr(i,n,1){
        R[i]=mp[a[i]];
        if(!R[i])R[i]=n+1;
        mp[a[i]]=i;
    }
    mp.clear();
    Fur(i,1,n){
        L[i]=mp[a[i]];
        mp[a[i]]=i;
    }
    out<<(chk(1,n)?"non-boring":"boring")<<ln;
}
int main(){
    fin("in");
    int T;in>>T;
    while(T--)work();
}
```
