---
author: zc
avatar: null
categories:
- - "\u5237\u9898\u8BB0\u5F55"
commnet: 1
date: 2020-03-20 16:33
html: "<details><summary>\u67E5\u770B\u539F\u9898</summary><div id='from'></div><p><button\
  \ onclick=\"document.getElementById('from').innerHTML='<iframe src=&quot;https://www.luogu.com.cn/problem/P5221&quot;\
  \ width=100% height=800px style=&quot;border: none;&quot;><iframe>'\" class='mdui-btn\
  \ mdui-btn-raised mdui-ripple'>\u70B9\u51FB\u52A0\u8F7D</button><a class='mdui-btn\
  \ mdui-btn-raised mdui-ripple' href=\"https://www.luogu.com.cn/problem/P5221\" target='_blank'>\u70B9\
  \u51FB\u8DF3\u8F6C</a><p></details>"
permalink: LG 5221 Product
tags:
- "\u6570\u8BBA"
- "\u6B27\u62C9\u51FD\u6570"
- "\u6570\u8BBA\u5206\u5757"
thumbnail: null
title: LG 5221 Product
top: 0
---
$$
\prod_{i=1}^n\prod_{j=1}^n\frac{lcm(i,j)}{\gcd(i,j)}
\\
=\prod_{i=1}^n\prod_{j=1}^n\frac{ij}{\gcd(i,j)^2}
\\
=\prod_{i=1}^n\prod_{j=1}^n ij \prod_{d=1}^n {\frac 1{d^2}}^{\sum_{i=1}^n\sum_{j=1}^n [\gcd(i,j)=d]}
\\
=(n!)^{2n} \left (\prod_{d=1}^n d^{\sum_{i=1}^n\sum_{j=1}^n [\gcd(i,j)=d]} \right )^{-2}
$$

其中:

$$
\prod_{d=1}^n d^{\sum_{i=1}^n\sum_{j=1}^n [\gcd(i,j)=d]}
\\
=\prod_{d=1}^n d^{\sum_{i=1}^{\left \lfloor \frac nd \right \rfloor}\sum_{j=1}^{\left \lfloor \frac nd \right \rfloor} [\gcd(i,j)=1]}
\\
=\prod_{d=1}^n d^{-1+2\sum_{i=1}^{\left \lfloor \frac nd \right \rfloor} \varphi(i)}
$$

因为$mod=104857601$是质数,使用可以用欧拉定理

```cpp
#include<cstdio>
const int N=1000001,P=104857601;
int n,cnt=0,pri[78499],phi[N];
bool b[N];
inline int pw(int x,int b){
    int ans=1;
    while(b){
        if(b&1)ans=1ll*ans*x%P;
        b>>=1;x=1ll*x*x%P;
    }
    return ans;
}
int main(){
    scanf("%d",&n);
    phi[1]=1;
    for(int i=2;i<=n;++i){
        if(!b[i])pri[++cnt]=i,phi[i]=i-1;
        for(int j=1,x;j<=cnt&&(x=i*pri[j])<=n;++j){
            b[x]=1;
            if(i%pri[j])phi[x]=phi[i]*(pri[j]-1);
            else{phi[x]=phi[i]*pri[j];break;}
        }
    }
    for(int i=1;i<=n;++i)phi[i]<<=1,(phi[i]+=phi[i-1])%=(P-1);
    int ans=1,ANS=1,pre=1;
    for(int l=1,r,i;l<=n;l=r+1){
        i=n/l,r=n/i;
        pre=ans;for(int j=l;j<=r;++j)ans=1ll*ans*j%P;
        ANS=1ll*ANS*pw(1ll*ans*pw(pre,P-2)%P,phi[i]-1)%P;
    }
    printf("%d\n",1ll*pw(ans,n<<1)*pw(1ll*ANS*ANS%P,P-2)%P);
}
```
