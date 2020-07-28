---
author: zc
avatar: null
categories:
- - 刷题记录
commnet: 1
date: 2019-12-21 19:47
html: '<details><summary>查看原题</summary><div id=''from''></div><p><button onclick="document.getElementById(''from'').innerHTML=''<iframe
  src=&quot;https://www.luogu.com.cn/problem/P1654&quot; width=100% height=800px style=&quot;border:
  none;&quot;><iframe>''" class=''mdui-btn mdui-btn-raised mdui-ripple''>点击加载</button><a
  class=''mdui-btn mdui-btn-raised mdui-ripple'' href="https://www.luogu.com.cn/problem/P1654"
  target=''_blank''>点击跳转</a><p></details>'
permalink: LG 1654 OSU!
tags:
- 期望
thumbnail: null
title: LG 1654 OSU!
top: 0
---
```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 10011
int n;
int main(){
	double ans=0,a=0,b=0,x;
	scanf("%d",&n);
	while(n--){
		scanf("%lf",&x);
		ans=ans+x*(3*a+3*b+1);
		a=(a+b*2+1)*x;
		b=(b+1)*x;
	}
	printf("%.1f\n",ans);
}
```
