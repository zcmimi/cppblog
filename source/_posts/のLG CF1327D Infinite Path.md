---
author: zc
avatar: null
categories:
- - "\u5237\u9898\u8BB0\u5F55"
commnet: 1
date: 2020-04-28 00:27
html: "<details><summary>\u67E5\u770B\u539F\u9898</summary><div id='from'></div><p><button\
  \ onclick=\"document.getElementById('from').innerHTML='<iframe src=&quot;https://www.luogu.com.cn/problem/CF1327D&quot;\
  \ width=100% height=800px style=&quot;border: none;&quot;><iframe>'\" class='mdui-btn\
  \ mdui-btn-raised mdui-ripple'>\u70B9\u51FB\u52A0\u8F7D</button><a class='mdui-btn\
  \ mdui-btn-raised mdui-ripple' href=\"https://www.luogu.com.cn/problem/CF1327D\"\
  \ target='_blank'>\u70B9\u51FB\u8DF3\u8F6C</a><p></details>"
permalink: LG CF1327D inftyite Path
tags:
- "\u56FE\u8BBA"
thumbnail: null
title: LG CF1327D inftyite Path
top: 0
---
首先把连接所有$i\rightarrow p_i$,可以得到若干个环

每$k$次$p_i=p_{p_i}$后会让$i$指向环上从$i$数起的$k+1$个点

只需要让一个环满足条件既可以,我们可以对每个环分别处理,然后答案取$\min$

可以发现假设一个环长度为$l$,若$k$可行,那么$\gcd(k,l)$也是可行的

我们判断是否存在$0\le t < \gcd(k,l)$,使环上所有模$\gcd(k,l)$等于$t$的点的颜色都相同就可以了
```cpp
#include<bits/stdc++.h>
#define gc getchar()
#define fur(i,x,y) for(int i=x;i<=y;++i)
void cmin(int &x,int y){if(x>y)x=y;}
void in(int &x){x=0;char c;bool f=0;for(c=gc;c<'0'||'9'<c;c=gc)f^=c=='-';for(x=c-48,c=gc;'0'<=c&&c<='9';x=x*10+c-48,c=gc);if(f)x=-x;}
const int N=200011;
bool v[N];
int n,c[N],p[N],a[N],cnt,ans,d[N],tot;
int solve(){
    tot=0;
    for(int i=1;1ll*i*i<=cnt;++i)
        if(cnt%i==0){
            d[++tot]=i;
            if(i*i!=cnt)d[++tot]=cnt/i;
        }
    std::sort(d+1,d+tot+1);
    fur(t,1,tot)
        fur(i,0,d[t]-1){
            for(int j=i;j<cnt;j+=d[t])
                if(a[i]!=a[j])goto ski;
            return d[t];
            ski:;
        }
    return cnt;
}
int main(){
    int T;in(T);
    while(T--){
        in(n),ans=n;
        fur(i,1,n)in(p[i]),v[i]=0;
        fur(i,1,n)in(c[i]);
        fur(i,1,n)if(!v[i]){
            a[0]=c[i];v[i]=1;cnt=1;
            for(int j=p[i];j!=i;j=p[j])a[cnt++]=c[j],v[j]=1;
            cmin(ans,solve());
        }
        printf("%d\n",ans);
    }
}
```
