---
author: zc
avatar: null
categories:
- - 刷题记录
commnet: 1
date: 2019-12-21 19:47
html: '<details><summary>查看原题</summary><div id=''from''></div><p><button onclick="document.getElementById(''from'').innerHTML=''<iframe
  src=&quot;https://www.luogu.com.cn/problem/CF5E&quot; width=100% height=800px style=&quot;border:
  none;&quot;><iframe>''" class=''mdui-btn mdui-btn-raised mdui-ripple''>点击加载</button><a
  class=''mdui-btn mdui-btn-raised mdui-ripple'' href="https://www.luogu.com.cn/problem/CF5E"
  target=''_blank''>点击跳转</a><p></details>'
permalink: LG CF5E Bindian Signalizing
tags: []
thumbnail: null
title: LG CF5E Bindian Signalizing
top: 0
---
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
#define N 2011
int n,a[N][N],b[N][N],f[N][N],F[N][N],p[N][N],q[N][N];
char ans[N*N];
int main(){
    fin("in");
    in>>n;
    int x,y,X=0,Y=0;
    Fur(i,1,n)Fur(j,1,n){
        int x;in>>x;
        if(x==0)X=i,Y=j;
        else{
            while(x%2==0)a[i][j]++,x>>=1;
            while(x%5==0)b[i][j]++,x/=5;
        }
    }
    if(X){
        out<<"0\n";
        Fur(i,1,X-1)out<<"D";
        Fur(i,1,Y-1)out<<"R";
        Fur(i,X+1,n)out<<"D";
        Fur(i,Y+1,n)out<<"R";
        return 0;
    }
    f[1][1]=a[1][1];
    F[1][1]=b[1][1];
    Fur(i,2,n){
        f[1][i]=f[1][i-1]+a[1][i];
        F[1][i]=F[1][i-1]+b[1][i];
        f[i][1]=f[i-1][1]+a[i][1];p[i][1]=1;
        F[i][1]=F[i-1][1]+b[i][1];q[i][1]=1;
    }
    Fur(i,2,n)
        Fur(j,2,n){
            if(f[i-1][j]<f[i][j-1])f[i][j]=f[i-1][j]+a[i][j];
            else p[i][j]=1,f[i][j]=f[i][j-1]+a[i][j];
            if(F[i-1][j]<F[i][j-1])F[i][j]=F[i-1][j]+b[i][j];
            else q[i][j]=1,F[i][j]=F[i][j-1]+b[i][j];
        }
    int d=0;
    if(f[n][n]<F[n][n]){
        out<<f[n][n]<<ln;
        x=n,y=n;
        while(x!=1||y!=1){
            if(p[x][y])ans[d++]='D',x--;
            else ans[d++]='R',y--;
        }
    }
    else{
        out<<F[n][n]<<ln;
        x=n,y=n;
        while(x!=1||y!=1){
            if(q[x][y])ans[d++]='D',x--;
            else ans[d++]='R',y--;
        }
    }
    reverse(ans,ans+d);
    out<<ans<<ln;
}
```
