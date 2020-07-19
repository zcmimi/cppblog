---
author: zc
avatar: null
categories:
- - "\u5237\u9898\u8BB0\u5F55"
commnet: 1
date: 2020-04-25 19:52
html: "<details><summary>\u67E5\u770B\u539F\u9898</summary><div id='from'></div><p><button\
  \ onclick=\"document.getElementById('from').innerHTML='<iframe src=&quot;https://www.luogu.com.cn/problem/CF1312E&quot;\
  \ width=100% height=800px style=&quot;border: none;&quot;><iframe>'\" class='mdui-btn\
  \ mdui-btn-raised mdui-ripple'>\u70B9\u51FB\u52A0\u8F7D</button><a class='mdui-btn\
  \ mdui-btn-raised mdui-ripple' href=\"https://www.luogu.com.cn/problem/CF1312E\"\
  \ target='_blank'>\u70B9\u51FB\u8DF3\u8F6C</a><p></details>"
permalink: LG CF1312E Array Shrinking
tags:
- "\u52A8\u6001\u89C4\u5212"
- "\u533A\u95F4dp"
thumbnail: null
title: LG CF1312E Array Shrinking
top: 0
---
看到$n\le 500$容易想到是区间dp

设$f(i,j)$为$[i,j]$合并后的最小长度,$w(i,j)$为合并后的和

$f(i,j)=\min\left\{ f(i,k)+f(k+1,j)\right\}$

当$f(i,k)=f(k+1,j)=1$且$w(i,k)=w(k+1,j)$时,合并即可

```cpp
#include<bits/stdc++.h>
typedef long long ll;typedef unsigned long long ull;typedef double db;typedef short sht;
#define fur(i,x,y) for(int i(x);i<=y;++i)
void cmin(int &x,int y){if(x>y)x=y;}
namespace IO{const int str=1<<20;static char in_buf[str],*in_s,*in_t;bool __=0;char gc(){return (in_s==in_t)&&(in_t=(in_s=in_buf)+fread(in_buf,1,str,stdin)),in_s==in_t?EOF:*in_s++;}void in(char &ch){if(__)return;char c;while((c=gc())!=EOF&&isspace(c));if(c==EOF)__=1;else ch=c;}void in(char *ch){*ch='\0';if(__)return;char c;while((c=gc())!=EOF&&isspace(c));if(c==EOF){__=1;return;}*ch=c;ch++;while((c=gc())!=EOF&&!isspace(c))*ch=c,ch++;if(c==EOF)__=1;*ch='\0';}template<typename T>void in(T &x){if(__)return;char c=gc();bool f=0;while(c!=EOF&&(c<'0'||c>'9'))f^=(c=='-'),c=gc();if(c==EOF){__=1;return;}x=0;while(c!=EOF&&'0'<=c&&c<='9')x=x*10+c-48,c=gc();if(c==EOF)__=1;if(f)x=-x;}template<typename T,typename ... arr>void in(T &x,arr & ... y){in(x),in(y...);}const char ln='\n';static char out_buf[str],*out_s=out_buf,*out_t=out_buf+str;void flush(){fwrite(out_buf,1,out_s-out_buf,stdout);out_s=out_buf;}void pt(char c){(out_s==out_t)?(fwrite(out_s=out_buf,1,str,stdout),*out_s++=c):(*out_s++=c);}void out(const char* s){while(*s)pt(*s++);}void out(char* s){while(*s)pt(*s++);}void out(char c){pt(c);}template<typename T>void out(T x){if(!x){pt('0');return;}if(x<0)pt('-'),x=-x;char a[50],t=0;while(x)a[t++]=x%10,x/= 10;while(t--)pt(a[t]+'0');}template<typename T,typename ... arr>void out(T x,arr & ... y){out(x),out(y...);}}using namespace IO;
const int N=511;
int n,a[N],f[N][N],w[N][N];
int main(){
    in(n);
    fur(i,1,n)in(a[i]),f[i][i]=1,w[i][i]=a[i];
    fur(i,2,n)
        fur(l,1,n-i+1){
            int r=l+i-1;f[l][r]=r-l+1;
            fur(k,l,r-1)
                if(f[l][k]==1&&f[k+1][r]==1&&w[l][k]==w[k+1][r]){
                    f[l][r]=1,w[l][r]=w[l][k]+1;
                    break;
                }
                else cmin(f[l][r],f[l][k]+f[k+1][r]);
        }
    printf("%d\n",f[1][n]);
}
```
