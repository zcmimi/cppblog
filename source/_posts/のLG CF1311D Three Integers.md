---
author: zc
avatar: null
categories:
- - "\u5237\u9898\u8BB0\u5F55"
commnet: 1
date: 2020-05-03 01:04
html: "<details><summary>\u67E5\u770B\u539F\u9898</summary><div id='from'></div><p><button\
  \ onclick=\"document.getElementById('from').innerHTML='<iframe src=&quot;https://www.luogu.com.cn/problem/CF1311D&quot;\
  \ width=100% height=800px style=&quot;border: none;&quot;><iframe>'\" class='mdui-btn\
  \ mdui-btn-raised mdui-ripple'>\u70B9\u51FB\u52A0\u8F7D</button><a class='mdui-btn\
  \ mdui-btn-raised mdui-ripple' href=\"https://www.luogu.com.cn/problem/CF1311D\"\
  \ target='_blank'>\u70B9\u51FB\u8DF3\u8F6C</a><p></details>"
permalink: LG CF1311D Three Integers
tags:
- "\u66B4\u529B"
- "\u679A\u4E3E"
thumbnail: null
title: LG CF1311D Three Integers
top: 0
---
暴力枚举即可
```cpp
#include<bits/stdc++.h>
int abs(int x){return x<0?-x:x;}
void solve(){
    int a,b,c,ans=1<<30,lim,res,A,B,C;
    scanf("%d%d%d",&a,&b,&c);lim=c<<1;
    for(int i=1;i<=lim;++i)
        for(int j=i;j<=lim;j+=i)
            for(int k=j;k<=lim;k+=j){
                res=abs(a-i)+abs(b-j)+abs(c-k);
                if(res<ans)ans=res,A=i,B=j,C=k;
            }
    printf("%d\n%d %d %d\n",ans,A,B,C);
}
int main(){
    int t;scanf("%d",&t);
    while(t--)solve();
}
```
