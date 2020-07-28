---
author: zc
avatar: null
categories:
- - 刷题记录
commnet: 1
date: 2019-12-21 19:47
html: '<details><summary>查看原题</summary><div id=''from''></div><p><button onclick="document.getElementById(''from'').innerHTML=''<iframe
  src=&quot;https://www.luogu.com.cn/problem/CF147B&quot; width=100% height=800px
  style=&quot;border: none;&quot;><iframe>''" class=''mdui-btn mdui-btn-raised mdui-ripple''>点击加载</button><a
  class=''mdui-btn mdui-btn-raised mdui-ripple'' href="https://www.luogu.com.cn/problem/CF147B"
  target=''_blank''>点击跳转</a><p></details>'
permalink: LG CF147B Smile House
tags:
- 倍增
thumbnail: null
title: LG CF147B Smile House
top: 0
---
倍增思想

$f[s][i][j]$表示最多走$s$条边,$i,j$之间最大掉边权和时多少
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
    #define l2(n) (int(log2(n)))
    #define inf 0x3f3f3f3f
    MB T ABS(T x){return x>0?x:-x;}
    MB T MAX(T x,T y){return x>y?x:y;}
    MB T MIN(T x,T y){return x<y?x:y;}
    MB T GCD(T x,T y){return y?GCD(y,x%y):x;}
    MB void SWAP(T &x,T &y){T t=x;x=y;y=t;}
}using namespace ZDY;using namespace std;
namespace IO{const char* ln="\n";const int str=1<<20;struct IN{char buf[str],*s,*t;bool _;IN():s(buf),t(buf),_(0){}il char gc(){return s==t&&((t=(s=buf)+fread(buf,1,str,stdin))==s)?EOF:(*s++);}IN&operator>>(char&ch){if(_)return *this;char c;while((c=gc())!=EOF&&isspace(c));if(c==EOF)_=1;else ch=c;return *this;}IN& operator>>(char* ch){clr(ch,0);if(_)return *this;char c;while((c=gc())!=EOF&&isspace(c));if(c==EOF)return _=1,*this;*ch=c;ch++;while((c=gc())!=EOF&&!isspace(c))*ch=c,ch++;if(c==EOF)_=1;return *this;}IN& operator>>(string& ch){if(_)return *this;char c;while((c=gc())!=EOF&&isspace(c));if(c==EOF)return _=1,*this;ch+=c;while((c=gc())!=EOF&&!isspace(c))ch+=c;if(c==EOF)_=1;return *this;}template<typename T>IN&operator>>(T&x){if(_)return *this;char c=gc();bool ff=0;while(c!=EOF&&(c<'0'||c>'9'))ff^=(c=='-'),c=gc();if(c==EOF){_=1;return *this;}x=0;while(c!=EOF&&'0'<=c&&c<='9')x=(x<<3)+(x<<1)+c-48,c=gc();if(c==EOF)_=1;if(ff)x=-x;return *this;}}in;struct OUT{char buf[str],*s,*t;OUT():s(buf),t(buf+str){}~OUT(){fwrite(buf,1,s-buf,stdout);}void pt(char c){(s==t)?(fwrite(s=buf,1,str,stdout),*s++=c):(*s++=c);}OUT&operator<<(const char*s){while(*s)pt(*s++);return *this;}OUT&operator<<(char*s){while(*s)pt(*s++);return *this;}OUT&operator<<(string s){for(int i=0;s[i];i++)pt(s[i]);return *this;}template<typename T>OUT&operator<<(T x){if(!x)return pt('0'),*this;if(x<0)pt('-'),x=-x;char a[30],t=0;while(x)a[t++]=x%10,x/=10;while(t--)pt(a[t]+'0');return *this;}}out;}using namespace IO;
#define N 305
int n,m,cnt=0,f[15][N][N],g[N][N],t[N][N];
int main(){
    fin("in");
    memset(f,0xcf,sizeof(f));
    memset(g,0xcf,sizeof(g));
    int x,y,w;
    in>>n>>m;
    Fur(i,1,m){
        in>>x>>y;
        in>>f[0][x][y]>>f[0][y][x];
    }
    Fur(i,1,n)f[0][i][i]=0,g[i][i]=0;
    Fur(s,1,10)
        Fur(k,1,n)
            Fur(i,1,n)
                Fur(j,1,n)
                    f[s][i][j]=MAX(f[s][i][j],f[s-1][i][k]+f[s-1][k][j]);
    int ans=0;
    Fdr(s,10,0){
        bool ff=0;
        memset(t,0xcf,sizeof(t));
        Fur(k,1,n)
            Fur(i,1,n)
                Fur(j,1,n)
                    t[i][j]=MAX(t[i][j],g[i][k]+f[s][k][j]);

        Fur(i,1,n)if(t[i][i]>0){
            ff=1;
            break;
        }
        if(!ff){
            Fur(i,1,n)Fur(j,1,n)g[i][j]=t[i][j];
            ans+=(1<<s);
        }
    }
    if(ans>=n)ans=0;
    else ans++;
    out<<ans<<ln;
}

```
