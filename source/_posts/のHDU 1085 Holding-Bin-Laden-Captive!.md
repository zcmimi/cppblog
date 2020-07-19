---
author: zc
avatar: null
categories:
- - "\u5237\u9898\u8BB0\u5F55"
commnet: 1
date: 2020-01-22 17:49
html: "<details><summary>\u67E5\u770B\u539F\u9898</summary><div id='from'></div><p><button\
  \ onclick=\"document.getElementById('from').innerHTML='<iframe src=&quot;http://acm.hdu.edu.cn/showproblem.php?pid=1085&quot;\
  \ width=100% height=800px style=&quot;border: none;&quot;><iframe>'\" class='mdui-btn\
  \ mdui-btn-raised mdui-ripple'>\u70B9\u51FB\u52A0\u8F7D</button><a class='mdui-btn\
  \ mdui-btn-raised mdui-ripple' href=\"http://acm.hdu.edu.cn/showproblem.php?pid=1085\"\
  \ target='_blank'>\u70B9\u51FB\u8DF3\u8F6C</a><p></details>"
permalink: HDU 1085 Holding-Bin-Laden-Captive!
tags:
- "\u751F\u6210\u51FD\u6570"
- "\u6570\u8BBA"
thumbnail: null
title: HDU 1085 Holding-Bin-Laden-Captive!
top: 0
---
$g(x)=(1+x+x^2+x^3+...+x^{num_1})(1+x^2+x^4+...+x^{2num_2})(1+x^5+x^{10}+x^{15}+...+x^{5num_3})$
```cpp
#include<bits/stdc++.h>
const int N=10011;
int n1,n2,n3,a[N],b[N],c[N];
int main(){
    while(~scanf("%d%d%d",&n1,&n2,&n3)&&(n1||n2||n3)){
        memset(a,0,sizeof a);
        memset(b,0,sizeof b);
        memset(c,0,sizeof c);
        int tot=n1+n2*2+n3*5;
        for(int i=0;i<=n1;++i)a[i]=1;
        for(int j=0;j<=tot;++j)
            for(int i=0;i<=n2*2&&i+j<=tot;i+=2)
                b[i+j]+=a[j];
        for(int j=0;j<=tot;++j)
            for(int i=0;i<=n3*5&&i+j<=tot;i+=5)
                c[i+j]+=b[j];
        int i;
        for(i=0;i<=tot;++i)if(!c[i])break;
        printf("%d\n",i);
    }
}
```
