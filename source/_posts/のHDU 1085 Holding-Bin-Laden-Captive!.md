---
author: zc
avatar: null
categories:
- - 刷题记录
commnet: 1
date: 2020-01-22 17:49
html: '<details><summary>查看原题</summary><div id=''from''></div><p><button onclick="document.getElementById(''from'').innerHTML=''<iframe
  src=&quot;http://acm.hdu.edu.cn/showproblem.php?pid=1085&quot; width=100% height=800px
  style=&quot;border: none;&quot;><iframe>''" class=''mdui-btn mdui-btn-raised mdui-ripple''>点击加载</button><a
  class=''mdui-btn mdui-btn-raised mdui-ripple'' href="http://acm.hdu.edu.cn/showproblem.php?pid=1085"
  target=''_blank''>点击跳转</a><p></details>'
permalink: HDU 1085 Holding-Bin-Laden-Captive!
tags:
- 生成函数
- 数论
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
