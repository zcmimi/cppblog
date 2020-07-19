---
author: zc
avatar: null
categories:
- - "\u5237\u9898\u8BB0\u5F55"
commnet: 1
date: 2019-12-21 19:47
html: "<details><summary>\u67E5\u770B\u539F\u9898</summary><div id='from'></div><p><button\
  \ onclick=\"document.getElementById('from').innerHTML='<iframe src=&quot;https://www.luogu.com.cn/problem/CF613C&quot;\
  \ width=100% height=800px style=&quot;border: none;&quot;><iframe>'\" class='mdui-btn\
  \ mdui-btn-raised mdui-ripple'>\u70B9\u51FB\u52A0\u8F7D</button><a class='mdui-btn\
  \ mdui-btn-raised mdui-ripple' href=\"https://www.luogu.com.cn/problem/CF613C\"\
  \ target='_blank'>\u70B9\u51FB\u8DF3\u8F6C</a><p></details>"
permalink: LG CF613C Necklace
tags:
- gcd
- "\u6784\u9020"
- "\u601D\u7EF4"
thumbnail: null
title: LG CF613C Necklace
top: 0
---
1. 如果个数中没有奇数,那么答案就是所有数字的$gcd$,然后构造答案就是输出$\frac {gcd}2$个回文串

2. 如果个数中只有一个奇数,那么答案也是所有数字的$gcd$,然后构造答案就是输出$gcd$个回文串,个数为奇数的颜色放在回文串的中间

3. 如果个数中有两个或以上的奇数,那么答案就是$0$,因为两个奇数就已经构造不出有优美$cut$的环来了
```cpp
#include<bits/stdc++.h>
namespace ZDY{
	#pragma GCC optimize(3)
	#define il __inline__ __attribute__ ((always_inline))
	#define ll long long
	#define MB template <class T>il
	#define Fur(i,x,y) for(int i=x;i<=y;i++)
	#define Fdr(i,x,y) for(int i=x;i>=y;i--)
	#define fcin ios::sync_with_stdio(false)
	MB T GCD(T x,T y){return y?GCD(y,x%y):x;}
}using namespace ZDY;using namespace std;
#define N 10011
int n,a[30];
int main(){
	fcin;
	cin>>n;
	int f=0,x;
	Fur(i,1,n){cin>>a[i];if(a[i]&1)x=i,f++;}
	int ans=a[1];
	Fur(i,2,n)ans=GCD(ans,a[i]);
	if(f>1)ans=0;
	cout<<ans<<endl;
	if(f>1){
		Fur(i,1,n)while(a[i]--)cout<<char('a'-1+i);
		return 0;
	}
	if(f){
		Fur(i,1,ans)
			Fur(j,1,n)
			if(j!=x)
				Fur(k,1,a[j]/ans/2)cout<<char('a'-1+j);
		Fur(j,1,a[x]/ans)cout<<char('a'-1+x);
		Fdr(j,n,1)
		if(j!=x)
			Fur(k,1,a[j]/ans/2)cout<<char('a'-1+j);
	}
	else{
		Fur(i,1,ans/2){
			Fur(j,1,n)
				Fur(k,1,a[j]/ans)cout<<char('a'-1+j);
			Fdr(j,n,1)
				Fur(k,1,a[j]/ans)cout<<char('a'-1+j);
		}
	}
}
```
