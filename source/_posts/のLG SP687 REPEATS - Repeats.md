---
author: zc
avatar: null
categories:
- - "\u5237\u9898\u8BB0\u5F55"
commnet: 1
date: 2020-05-16 14:13
html: "<details><summary>\u67E5\u770B\u539F\u9898</summary><div id='from'></div><p><button\
  \ onclick=\"document.getElementById('from').innerHTML='<iframe src=&quot;https://www.luogu.com.cn/problem/SP687&quot;\
  \ width=100% height=800px style=&quot;border: none;&quot;><iframe>'\" class='mdui-btn\
  \ mdui-btn-raised mdui-ripple'>\u70B9\u51FB\u52A0\u8F7D</button><a class='mdui-btn\
  \ mdui-btn-raised mdui-ripple' href=\"https://www.luogu.com.cn/problem/SP687\" target='_blank'>\u70B9\
  \u51FB\u8DF3\u8F6C</a><p></details>"
permalink: LG SP687 REPEATS - Repeats
tags:
- "\u540E\u7F00\u6570\u7EC4"
thumbnail: null
title: LG SP687 REPEATS - Repeats
top: 0
---
枚举长度$L$,然后判断长度为$L$的子串能连续出现几次(1次肯定可以,这里判断出现2次以上的)

复杂度$\Theta(\frac n1+\frac n2+\cdots +\frac nn)$

假设现在枚举到位置$j$

找到$k=\operatorname{LCP}(suf(j),suf(j+L))$,$\left \lfloor \frac ki \right \rfloor +1$就是从$j$开始到$j$之后循环的次数

再判断一下$j$之前是否有再出现过,就可以得出当前答案


```cpp
#include<bits/stdc++.h>
const int N=50011;
int n,m,sa[N],rnk[N],tax[N],tp[N],height[N];
char s[N];
void qsort(){
    for(int i=0;i<=m;++i)++tax[i]=0;
    for(int i=1;i<=n;++i)++tax[rnk[i]];
    for(int i=1;i<=m;++i)tax[i]+=tax[i-1];
    for(int i=n;i;--i)sa[tax[rnk[tp[i]]]--]=tp[i];
}
int f[17][N];
int min(int x,int y){return x<y?x:y;}
void st(){
    for(int i=1;i<=n;++i)f[0][i]=height[i];
    for(int k=1;k<=16;++k)
        for(int i=1;i+(1<<k)-1<=n;++i)
            f[k][i]=min(f[k-1][i],f[k-1][i+(1<<(k-1))]);
}
int ask(int l,int r){
    if(l==r)return -1u>>1;
    if(l>r)l^=r,r^=l,l^=r;++l;
    int k=log2(r-l+1);
    return min(f[k][l],f[k][r-(1<<k)+1]);
}
int get(){char c;while((c=getchar())<'a');return c-'a'+1;}
void solve(){
    scanf("%d",&n);
    m=3;
    for(int i=1;i<=n;++i)sa[i]=0,rnk[i]=s[i]=get(),tp[i]=i;
    qsort();
    for(int w=1,p=0;p<n;m=p,w<<=1){
        p=0;
        for(int i=1;i<=w;++i)tp[++p]=n-w+i;
        for(int i=1;i<=n;++i)if(sa[i]>w)tp[++p]=sa[i]-w;
        qsort();
        std::swap(tp,rnk);
        rnk[sa[1]]=p=1;
        for(int i=2;i<=n;++i)
            rnk[sa[i]]=p+=tp[sa[i]]^tp[sa[i-1]]||tp[sa[i]+w]^tp[sa[i-1]+w];
    }
    for(int i=1,k=0;i<=n;++i){
        if(k)--k;
        int j=sa[rnk[i]-1];
        while(s[i+k]==s[j+k]&&i+k<=n&&j+k<=n)++k;
        height[rnk[i]]=k;
    }
    st();
    int ans=1;
    for(int i=1;i<=n;++i)
        for(int j=1;j+i<=n;j+=i){
            int k=ask(rnk[j],rnk[j+i]),now=k/i+1,t=j-i+k%i;
            if(ask(rnk[t],rnk[t+i])>k)++now;
            if(now>ans)ans=now;            
        }
    printf("%d\n",ans);
}
int main(){
    int T;scanf("%d",&T);
    while(T--)solve();
}
```
