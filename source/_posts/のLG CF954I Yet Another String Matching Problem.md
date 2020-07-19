---
author: zc
avatar: null
categories:
- - "\u5237\u9898\u8BB0\u5F55"
commnet: 1
date: 2020-05-05 00:18
html: "<details><summary>\u67E5\u770B\u539F\u9898</summary><div id='from'></div><p><button\
  \ onclick=\"document.getElementById('from').innerHTML='<iframe src=&quot;https://www.luogu.com.cn/problem/CF954I&quot;\
  \ width=100% height=800px style=&quot;border: none;&quot;><iframe>'\" class='mdui-btn\
  \ mdui-btn-raised mdui-ripple'>\u70B9\u51FB\u52A0\u8F7D</button><a class='mdui-btn\
  \ mdui-btn-raised mdui-ripple' href=\"https://www.luogu.com.cn/problem/CF954I\"\
  \ target='_blank'>\u70B9\u51FB\u8DF3\u8F6C</a><p></details>"
permalink: LG CF954I Yet Another String Matching Problem
tags:
- kmp
- "\u5B57\u7B26\u4E32"
thumbnail: null
title: LG CF954I Yet Another String Matching Problem
top: 0
---
枚举变换情况($6!$),然后`kmp`$\Theta(n)$判断即可
```cpp
#include<bits/stdc++.h>
const int N=125011,inf=2122219134;
char s1[N],s2[N];
int n,m,a[N],b[N],nxt[N],p[6],now,ans[N];
void kmp(){
    for(int i=1,k=0;i<m;++i){
        while(k&&b[i]^b[k])k=nxt[k-1];
        if(b[i]==b[k])++k;
        nxt[i]=k;
    }
    for(int i=0,k=0;i<n;++i){
        while(k&&a[i]^b[k])k=nxt[k-1];
        if(a[i]==b[k])++k;
        if(k==m){
            if(now<ans[i])ans[i]=now;
            k=nxt[k-1];
        }
    }
}
int main(){
    scanf("%s%s",s1,s2);
    n=strlen(s1),m=strlen(s2);
    for(int i=m-1;i<n;++i)ans[i]=-1u>>1;
    p[5]=5;
    for(p[0]=0;p[0]<6;++p[0])
    for(p[1]=1;p[1]<6;++p[1])
    for(p[2]=2;p[2]<6;++p[2])
    for(p[3]=3;p[3]<6;++p[3])
    for(p[4]=4;p[4]<6;++p[4]){
        for(int i=0;i<n;++i)a[i]=p[s1[i]-'a'];
        for(int i=0;i<m;++i)b[i]=p[s2[i]-'a'];
        now=(p[0]>0)+(p[1]>1)+(p[2]>2)+(p[3]>3)+(p[4]>4);
        kmp();
    }
    for(int i=m-1;i<n;++i)printf("%d ",ans[i]);
}
```
