---
author: zc
avatar: null
categories:
- - "\u5237\u9898\u8BB0\u5F55"
commnet: 1
date: 2020-05-02 23:47
html: "<details><summary>\u67E5\u770B\u539F\u9898</summary><div id='from'></div><p><button\
  \ onclick=\"document.getElementById('from').innerHTML='<iframe src=&quot;https://www.luogu.com.cn/problem/CF1320D&quot;\
  \ width=100% height=800px style=&quot;border: none;&quot;><iframe>'\" class='mdui-btn\
  \ mdui-btn-raised mdui-ripple'>\u70B9\u51FB\u52A0\u8F7D</button><a class='mdui-btn\
  \ mdui-btn-raised mdui-ripple' href=\"https://www.luogu.com.cn/problem/CF1320D\"\
  \ target='_blank'>\u70B9\u51FB\u8DF3\u8F6C</a><p></details>"
permalink: LG CF1320D Reachable Strings
tags:
- "\u54C8\u5E0C"
thumbnail: null
title: LG CF1320D Reachable Strings
top: 0
---
可以发现$110\leftrightarrow 011$相当于$0$前/后移动了2格,那么每个$0$位置的奇偶性是不变的

而且每个$0$无法移动到下一个$0$的后面

把这些$0$记录到一个序列里,然后通过哈希判断两个子串在序列中对应的部分是否相同

因为子序列的起点奇偶性不同,分别表示以起点为奇数和偶数为标准时哈希得的前缀$0$序列数组。
```cpp
#include<cstdio>
const int N=200011,P=998244353;
int n,q,s[N],b[N],h[N],H[N];
char a[N];
int get(int l,int r){
    int*g=(l&1)?h:H;
    return (g[r]-1ll*g[l-1]*b[s[r]-s[l-1]]%P+P)%P;
}
int main(){
    scanf("%d%s%d",&n,a+1,&q);
    b[0]=1;
    for(int i=1;i<=n;++i){
        b[i]=23ll*b[i-1]%P;
        s[i]=s[i-1]+(a[i]==48);
        if(a[i]==48)
            h[i]=(23ll*h[i-1]+1+(i&1))%P,
            H[i]=(23ll*H[i-1]+1+(i&1^1))%P;
        else h[i]=h[i-1],H[i]=H[i-1];
    }
    while(q--){
        int x,y,w;
        scanf("%d%d%d",&x,&y,&w);
        printf(get(x,x+w-1)==get(y,y+w-1)?"Yes\n":"No\n");
    }
}
```
