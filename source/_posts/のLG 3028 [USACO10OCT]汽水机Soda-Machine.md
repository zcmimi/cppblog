---
author: zc
avatar: null
categories:
- - "\u5237\u9898\u8BB0\u5F55"
commnet: 1
date: 2019-12-21 19:47
html: "<details><summary>\u67E5\u770B\u539F\u9898</summary><div id='from'></div><p><button\
  \ onclick=\"document.getElementById('from').innerHTML='<iframe src=&quot;https://www.luogu.com.cn/problem/P3028&quot;\
  \ width=100% height=800px style=&quot;border: none;&quot;><iframe>'\" class='mdui-btn\
  \ mdui-btn-raised mdui-ripple'>\u70B9\u51FB\u52A0\u8F7D</button><a class='mdui-btn\
  \ mdui-btn-raised mdui-ripple' href=\"https://www.luogu.com.cn/problem/P3028\" target='_blank'>\u70B9\
  \u51FB\u8DF3\u8F6C</a><p></details>"
permalink: "LG 3028 [USACO10OCT]\u6C7D\u6C34\u673ASoda-Machine"
tags: []
thumbnail: null
title: "LG 3028 [USACO10OCT]\u6C7D\u6C34\u673ASoda-Machine"
top: 0
---
```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn=5000110;
int n;
char s[maxn];
int Mini(int l){    
    int i,j,k;  
    i=0;j=1;k=0;  
    while(i<l&&j<l)  
    {  
        k=0;  
        while(s[(i+k)%l]==s[(j+k)%l]&&k<l) k++;  
        if(k==l) return (i<j)?i:j;  
        if(s[(i+k)%l]>s[(j+k)%l])i=i+k+1;
        else j=j+k+1;
        if(i==j)j++;
    } 
    return (i<j)?i:j;
}     
int main(){
    cin>>n;
    for(int i=0;i<n;i++)cin>>s[i];
    int l=Mini(n);
    cout<<l<<endl;
}
```
