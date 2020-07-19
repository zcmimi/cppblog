---
author: zc
avatar: null
categories:
- - "\u5237\u9898\u8BB0\u5F55"
commnet: 1
date: 2020-06-04 07:29
html: "<details><summary>\u67E5\u770B\u539F\u9898</summary><div id='from'></div><p><button\
  \ onclick=\"document.getElementById('from').innerHTML='<iframe src=&quot;https://www.luogu.com.cn/problem/CF724G&quot;\
  \ width=100% height=800px style=&quot;border: none;&quot;><iframe>'\" class='mdui-btn\
  \ mdui-btn-raised mdui-ripple'>\u70B9\u51FB\u52A0\u8F7D</button><a class='mdui-btn\
  \ mdui-btn-raised mdui-ripple' href=\"https://www.luogu.com.cn/problem/CF724G\"\
  \ target='_blank'>\u70B9\u51FB\u8DF3\u8F6C</a><p></details>"
permalink: LG CF724G Xor-matic Number of the Graph
tags:
- "\u7EBF\u6027\u57FA"
- "\u601D\u7EF4"
- "\u56FE\u8BBA"
thumbnail: null
title: LG CF724G Xor-matic Number of the Graph
top: 0
---
做这题之前可以看看[\[WC20$1$\]最大XOR和路径](https://www.luogu.com.cn/problem/P4151)

可以考虑换个思路:

对于每一对点的每一位,有多少种方案能使该位的$xor$和为$1$

`dfs`求出$1$到各点$x$的任意一条简单路径$xor$和$d_x$,那么求$x$到$y$的简单路径长度就是$d_x ~ xor ~ d_y$

在`dfs`的过程中也可以顺便求出所有环的$xor$和,这些可以用来增广简单路径,我们将这些环的$xor$和插入到线性基中

若线性基中有$cnt$个非零位,则一共会产生$2^{cnt}$个不同的$xor$值

到了这一步,通过枚举两个点来统计路径的复杂度仍然是$O(n^2 \cdot 60)$的,我们要采用更高效的方法

直接讨论$d_x$对答案的贡献

先统计出第$k$位为$0$的数的个数,我们将其记为$x$,再统计出第$k$位为$1$的数的个数,记为$y$,总共有$point$个点

1. $d_x$的第$k$位为$1$,线性基中有第$k$位为$1$的数: 
   此时我们有两种选择：
   - 选线性基中的,另一个点选择第$k$位为$0$的。
   - 不选线性基中的,另一个点选择第$k$位为$1$的。总体对于答案的贡献为：$2^k\cdot 2^{cnt-1}\cdot (point-1)$,减$1$就是为了把自己给去掉。

2. $d_i$的第$k$位为$1$,线性基中没有第$k$位为$1$的数: 这个时候另一个点只能取第$k$位为$0$的,, 所以总贡献为: $2^k\cdot 2^{cnt}\cdot x$。

3. $d_i$的第$k$位为$0$,线性基中有第$k$位为$1$的数: 一样的,, 两种选择:
   - 选线性基中的,另一个点选择第$k$位为$0$的。 
   - 不选线性基中的,另一个点选择第$k$位为$1$的。总贡献为: $2^k\cdot2^{cnt-1}\cdot(point-1)$。

3. $d_i$的第$k$位为$0$,线性基中没有第$k$位为$1$的数: 另一个点只能取第$k$位为$1$的,总贡献: $2^k\cdot 2^{cnt}\cdot y$。

```cpp

#include<bits/stdc++.h>
typedef long long ll;
const int N=100001;
const ll P=1000000007,inv=500000004;
struct edge{int to,nxt;ll w;}e[N<<2];
int n,m,cnt=1,head[N],tt;
ll pw[61],p[61],a[N],d[N];
bool v[N],u[N<<2];
void add(int x,int y,ll w){e[++cnt].to=y,e[cnt].nxt=head[x],head[x]=cnt,e[cnt].w=w;}
void ins(ll x){
    for(int i=60;x,~i;--i)if(x>>i){
        if(!p[i]){p[i]=x;return;}
        x^=p[i];
    }
}
void dfs(int x){
    a[++tt]=d[x],v[x]=1;
    for(int i=head[x],to;to=e[i].to,i;i=e[i].nxt)
        if(!v[to])d[to]=d[x]^e[i].w,dfs(to);
        else if(!u[i^1])ins(d[x]^d[to]^e[i].w),u[i^1]=1;
}
ll calc(){
    ll ans=0;int x,y,tot=0;bool ff;
    for(int i=0;i<=60;++i)tot+=p[i]>0;
    for(int j=0;j<=60;++j){
        x=y=ff=0;
        for(int i=1;i<=tt;++i)
            (a[i]>>j&1)?++x:++y;
        for(int i=0;i<=60;++i)
            if(p[i]>>j&1){ff=1;break;}
        for(int i=1;i<=tt;++i,ans%=P)
            if(a[i]>>j&1)
                if(ff)ans+=pw[tot-1]*(tt-1)%P*pw[j]%P;
                else ans+=pw[tot]*y%P*pw[j]%P;
            else
                if(ff)ans+=pw[tot-1]*(tt-1)%P*pw[j]%P;
                else ans+=pw[tot]*x%P*pw[j]%P;
    }
    return ans;
}
int main(){
    scanf("%d%d",&n,&m);
    int x,y;ll w,ans=0;
    while(m--)
        scanf("%d%d%lld",&x,&y,&w),
        add(x,y,w),add(y,x,w);
    pw[0]=1;
    for(int i=1;i<=60;++i)pw[i]=(pw[i-1]<<1)%P;
    for(int i=1;i<=n;++i)if(!v[i]){
        memset(p,0,sizeof p);
        tt=0,dfs(i);
        (ans+=calc())%=P;
    }
    ans=ans*inv%P;
    printf("%lld\n",ans);
}
```