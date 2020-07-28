---
author: zc
avatar: null
categories:
- - 刷题记录
commnet: 1
date: 2020-05-05 09:31
html: '<details><summary>查看原题</summary><div id=''from''></div><p><button onclick="document.getElementById(''from'').innerHTML=''<iframe
  src=&quot;https://www.luogu.com.cn/problem/CF1310B&quot; width=100% height=800px
  style=&quot;border: none;&quot;><iframe>''" class=''mdui-btn mdui-btn-raised mdui-ripple''>点击加载</button><a
  class=''mdui-btn mdui-btn-raised mdui-ripple'' href="https://www.luogu.com.cn/problem/CF1310B"
  target=''_blank''>点击跳转</a><p></details>'
permalink: LG CF1310B Double Elimination
tags:
- 状压dp
- 动态规划
thumbnail: null
title: LG CF1310B Double Elimination
top: 0
---
设$f(i,j,0/1,0/1)$表示第$i$轮的第$j$场,你是否是胜利者的粉丝,是否是失败者的粉丝

可以发现轮数有点像堆,如果轮数从$0$开始编号,第$i$轮的第$j$场由第$i-1$轮的第$2j$场、第$i-1$轮的第$2j+1$场转移而来


```cpp
#include<bits/stdc++.h>
#define gc getchar()
#define fur(i,x,y) for(int i=x;i<=y;++i)
void in(int &x){x=0;char c;bool f=0;for(c=gc;c<'0'||'9'<c;c=gc)f^=c=='-';for(x=c-48,c=gc;'0'<=c&&c<='9';x=x*10+c-48,c=gc);if(f)x=-x;}
int n,k,f[18][2][2][1<<18];
bool w[1<<17|1];
void cmax(int &x,int y){if(y>x)x=y;}
int main(){
    in(n),in(k);
    int x;
    fur(i,1,k)in(x),w[x-1]=1;
    memset(f,-0x3f,sizeof f);
    fur(i,0,(1<<n-1)-1)
        f[1][w[i<<1]][w[i<<1|1]][i]=f[1][w[i<<1|1]][w[i<<1]][i]=w[i<<1]|w[i<<1|1];
    fur(i,2,n)
        fur(j,0,(1<<n-i)-1)
            fur(wl,0,1)fur(ll,0,1)fur(wr,0,1)fur(lr,0,1){
                int t=f[i-1][wl][ll][j<<1]+f[i-1][wr][lr][j<<1|1];
                cmax(f[i][wl|wr][ll|lr][j],t+((ll|lr)<<1)+(wl|wr));
                if(wl|wr)cmax(f[i][wl+wr-1][1][j],t+(ll|lr)+(wl|wr)+1);
            }
    x=0;
    fur(wl,0,1)fur(ll,0,1)cmax(x,f[n][wl][ll][0]+(wl|ll));
    printf("%d\n",x);
}
```
