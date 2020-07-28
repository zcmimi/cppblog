---
author: zc
avatar: null
categories:
- - 刷题记录
commnet: 1
date: 2019-12-21 19:47
html: '<details><summary>查看原题</summary><div id=''from''></div><p><button onclick="document.getElementById(''from'').innerHTML=''<iframe
  src=&quot;https://www.luogu.com.cn/problem/P2167&quot; width=100% height=800px style=&quot;border:
  none;&quot;><iframe>''" class=''mdui-btn mdui-btn-raised mdui-ripple''>点击加载</button><a
  class=''mdui-btn mdui-btn-raised mdui-ripple'' href="https://www.luogu.com.cn/problem/P2167"
  target=''_blank''>点击跳转</a><p></details>'
permalink: LG 2167 [SDOI2009]Bill的挑战
tags:
- 动态规划
- 状态压缩
- 容斥
thumbnail: null
title: LG 2167 [SDOI2009]Bill的挑战
top: 0
---
可以看到$n\le 15$,我们很容易想到状压

### 状压解法：

设$f[i][j]$表示到了第$i$位,匹配的状态为$j$

代码：
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
namespace IO{const int str=1<<20;static char in_buf[str],*in_s,*in_t;bool __=0;il char gc(){return (in_s==in_t)&&(in_t=(in_s=in_buf)+fread(in_buf,1,str,stdin)),in_s==in_t?EOF:*in_s++;}il void in(string &ch){ch.clear();if(__)return;char c;while((c=gc())!=EOF&&isspace(c));if(c==EOF){__=1;return;}ch+=c;while((c=gc())!=EOF&&!isspace(c))ch+=c;if(c==EOF)__=1;}il void in(char &ch){if(__)return;char c;while((c=gc())!=EOF&&isspace(c));if(c==EOF)__=1;else ch=c;}il void in(char *ch){*ch='\0';if(__)return;char c;while((c=gc())!=EOF&&isspace(c));if(c==EOF){__=1;return;}*ch=c;ch++;while((c=gc())!=EOF&&!isspace(c))*ch=c,ch++;if(c==EOF)__=1;*ch='\0';}template<typename T>il void in(T &x){if(__)return;char c=gc();bool f=0;while(c!=EOF&&(c<'0'||c>'9'))f^=(c=='-'),c=gc();if(c==EOF){__=1;return;}x=0;while(c!=EOF&&'0'<=c&&c<='9')x=x*10+c-48,c=gc();if(c==EOF)__=1;if(f)x=-x;}template<typename T,typename ... arr>il void in(T &x,arr & ... y){in(x),in(y...);}const char ln='\n';static char out_buf[str],*out_s=out_buf,*out_t=out_buf+str;il void flush(){fwrite(out_buf,1,out_s-out_buf,stdout);out_s=out_buf;}il void pt(char c){(out_s==out_t)?(fwrite(out_s=out_buf,1,str,stdout),*out_s++=c):(*out_s++=c);}il void out(const char* s){while(*s)pt(*s++);}il void out(char* s){while(*s)pt(*s++);}il void out(char c){pt(c);}il void out(string s){for(int i=0;s[i];i++)pt(s[i]);}template<typename T>il void out(T x){if(!x){pt('0');return;}if(x<0)pt('-'),x=-x;char a[50],t=0;while(x)a[t++]=x%10,x/= 10;while(t--)pt(a[t]+'0');}template<typename T,typename ... arr>il void out(T x,arr & ... y){out(x),out(y...);}}using namespace IO;
#define N 111
#define mod 1000003
#define M(x) ((x>=mod)?(x)%=mod:x)
int mt[N][30];
ll f[N][1<<15];
char ch[N][N];
il void work(){
    clr(mt,0);
    clr(f,0);
    int n,k,len;
    in(n,k);
    Fur(i,1,n)in(ch[i]);
    len=strlen(ch[1]);
    Fur(i,0,len-1)
        for(char t='a';t<='z';++t)
            Fur(j,1,n)
            if(ch[j][i]=='?'||ch[j][i]==t)
                mt[i][t-'a']|=(1<<(j-1));//更新比较当前位的影响
    f[0][(1<<n)-1]=1;
    Fur(i,0,len-1)
        Fur(j,0,(1<<n)-1)
        if(f[i][j])
            Fur(t,0,26)
                M(f[i+1][j&mt[i][t]]+=f[i][j]);
    ll ans=0;
    Fur(i,0,(1<<n)-1){
        int t=i,tt=0;
        while(t)tt+=(t&1),t>>=1;
        if(tt==k)M(ans+=f[len][i]);
    }
    out(ans,ln);
}
int main(){
    int T;in(T);
    while(T--)work();
    flush();
}
```

此题还有容斥解法：

看到恰好$k$个,我们就可以想到容斥套路

找出至少匹配$k$个的方案数$g(k)$,设$f(k)$为恰好$k$个的方案数

然后还是按套路就可以了

$$
g(n) = \sum_{i=k}^n {n\choose i}f(i)

\leftrightarrow 

f(n) = \sum_{i=k}^n {n\choose i}g(i) (-1)^{i-k}
$$

问题转换为如何求至少匹配$k$个的方案数

我们可以使用dfs来统计,~~这样比起状压思维难度可能降低了许多,只需要枚举排列组合(当然枚举二进制状态也可以)~~

状压需要处理全部状态

dfs只需要统计$k～n$的部分

最后统计的时间可忽略不计

状压：$492ms$

容斥: $100ms$
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
namespace IO{const int str=1<<20;static char in_buf[str],*in_s,*in_t;bool __=0;il char gc(){return (in_s==in_t)&&(in_t=(in_s=in_buf)+fread(in_buf,1,str,stdin)),in_s==in_t?EOF:*in_s++;}il void in(string &ch){ch.clear();if(__)return;char c;while((c=gc())!=EOF&&isspace(c));if(c==EOF){__=1;return;}ch+=c;while((c=gc())!=EOF&&!isspace(c))ch+=c;if(c==EOF)__=1;}il void in(char &ch){if(__)return;char c;while((c=gc())!=EOF&&isspace(c));if(c==EOF)__=1;else ch=c;}il void in(char *ch){*ch='\0';if(__)return;char c;while((c=gc())!=EOF&&isspace(c));if(c==EOF){__=1;return;}*ch=c;ch++;while((c=gc())!=EOF&&!isspace(c))*ch=c,ch++;if(c==EOF)__=1;*ch='\0';}template<typename T>il void in(T &x){if(__)return;char c=gc();bool f=0;while(c!=EOF&&(c<'0'||c>'9'))f^=(c=='-'),c=gc();if(c==EOF){__=1;return;}x=0;while(c!=EOF&&'0'<=c&&c<='9')x=x*10+c-48,c=gc();if(c==EOF)__=1;if(f)x=-x;}template<typename T,typename ... arr>il void in(T &x,arr & ... y){in(x),in(y...);}const char ln='\n';static char out_buf[str],*out_s=out_buf,*out_t=out_buf+str;il void flush(){fwrite(out_buf,1,out_s-out_buf,stdout);out_s=out_buf;}il void pt(char c){(out_s==out_t)?(fwrite(out_s=out_buf,1,str,stdout),*out_s++=c):(*out_s++=c);}il void out(const char* s){while(*s)pt(*s++);}il void out(char* s){while(*s)pt(*s++);}il void out(char c){pt(c);}il void out(string s){for(int i=0;s[i];i++)pt(s[i]);}template<typename T>il void out(T x){if(!x){pt('0');return;}if(x<0)pt('-'),x=-x;char a[50],t=0;while(x)a[t++]=x%10,x/= 10;while(t--)pt(a[t]+'0');}template<typename T,typename ... arr>il void out(T x,arr & ... y){out(x),out(y...);}}using namespace IO;
#define N 111
#define mod 1000003
char ch[N][N];
int len,n,k,cnt,c[N][N],up,tot=0,las,a[N];
void dfs(int x,int now){
    if(x==n+1){
        if(now!=up) return;
        ll lp=1;
        Fur(j,1,len){
            las=-1;
            Fur(i,1,up)
                if(ch[a[i]][j]!='?'){
                    if(las==-1)
                        las=ch[a[i]][j]-'a';
                    else if(las!=ch[a[i]][j]-'a')return;
                }
            if(las==-1)lp=(lp*26)%mod;
        }
        (tot+=lp)%=mod;
        return;
    }
    if(now<up){
        a[++cnt]=x;
        dfs(x+1,now+1);
        a[cnt--]=0;
    }
    if(n-x>=up-now)dfs(x+1,now);
}
ll g[N];
il void work(){
    clr(g,0);
    in(n,k);
    Fur(i,1,n)in(ch[i]+1);
    len=strlen(ch[1]+1);
    Fur(i,k,n){
        up=i;
        tot=0;
        dfs(1,0);
        g[i]=tot;
    }
    ll ans=0;
    Fur(i,k,n)
        if((i-k)&1)ans=(ans-1ll*c[i][k]*g[i]%mod+mod)%mod;
        else ans=(ans+1ll*c[i][k]*g[i]%mod)%mod;
    out(ans,ln);
}
int main(){
    Fur(i,0,20){
        c[i][0]=1;
        Fur(j,1,i)
            c[i][j]=c[i-1][j]+c[i-1][j-1];
    }
    int T;in(T);
    while(T--)work();
    flush();
}
```
