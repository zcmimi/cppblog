---
author: zc
avatar: null
categories:
- - 刷题记录
commnet: 1
date: 2020-05-16 14:13
html: '<details><summary>查看原题</summary><div id=''from''></div><p><button onclick="document.getElementById(''from'').innerHTML=''<iframe
  src=&quot;https://www.luogu.com.cn/problem/SP694&quot; width=100% height=800px style=&quot;border:
  none;&quot;><iframe>''" class=''mdui-btn mdui-btn-raised mdui-ripple''>点击加载</button><a
  class=''mdui-btn mdui-btn-raised mdui-ripple'' href="https://www.luogu.com.cn/problem/SP694"
  target=''_blank''>点击跳转</a><p></details>'
permalink: LG SP694 DISUBSTR - Distinct Substrings
tags:
- 后缀数组
thumbnail: null
title: LG SP694 DISUBSTR - Distinct Substrings
top: 0
---
```cpp
#include<bits/stdc++.h>
const int N=100011;
char s[N];
int n,m,tax[N],tp[N],rnk[N],sa[N],height[N];
void qsort(){
    for(int i=0;i<=m;++i)tax[i]=0;
    for(int i=1;i<=n;++i)++tax[rnk[i]];
    for(int i=1;i<=m;++i)tax[i]+=tax[i-1];
    for(int i=n;i;--i)sa[tax[rnk[tp[i]]]--]=tp[i];
}
void suffix(){
    m=200;
    for(int i=1;i<=n;++i)sa[i]=0,rnk[i]=s[i]-'A'+1,tp[i]=i;
    qsort();
    for(int w=1,p=0;p<n;m=p,w<<=1){
        p=0;
        for(int i=1;i<=w;++i)tp[++p]=n-w+i;
        for(int i=1;i<=n;++i)
            if(sa[i]>w)tp[++p]=sa[i]-w;
        qsort();
        std::swap(tp,rnk);
        rnk[sa[1]]=p=1;
        for(int i=2;i<=n;++i)
            rnk[sa[i]]=p+=tp[sa[i]]^tp[sa[i-1]]||tp[sa[i]+w]^tp[sa[i-1]+w];
    }
}
void solve(){
    scanf("%s",s+1),n=strlen(s+1);
    suffix();
    long long ans=n*(n+1)>>1;
    for(int i=1,k=0;i<=n;++i){
        if(k)--k;
        int j=sa[rnk[i]-1];
        while(s[i+k]==s[j+k]&&i+k<=n&&j+k<=n)++k;
        ans-=k;
    }
    printf("%lld\n",ans);
}
int main(){
    int T;scanf("%d",&T);
    while(T--)solve();
}
```
