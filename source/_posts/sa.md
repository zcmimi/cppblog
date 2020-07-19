---
title: 后缀数组
date: 2020-05-13 19:00
author: 
avatar:
tags: 
 - 字符串
 - 后缀数组

categories:
 - [算法,字符串]
 - [note]

thumbnail: 
top: 0 
comment: 1
---

## 简介

后缀数组,又称`SA`

是OI中处理字符串的有力工具

## 实现

有两种实现的方法

1. 倍增法
2. DC3

这里主要讲倍增法

`sa[i]`表示所有后缀中的字典序排名为$i$的后缀的起始位置

`rnk[i]`表示起始位置为$i$的后缀(后缀$i$)在所有后缀中的排名

图解:

![](1.png)

从长度$1$的块开始排序,接着是长度为$2$,然后每次长度都倍增

第一次直接对所有字符进行排序

每次将当前块分为相等的两段,这两段的排名上一轮已经求出了,变成一个二元组$(a,b)$

比较两个块相当于比较两个二元组

一直倍增知道块长大于字符串长度,终止即可

这里的排序使用基数排序加快速度

[LG P3809 【模板】后缀排序](https://www.luogu.com.cn/problem/P3809)

```cpp
#include<bits/stdc++.h>
#define fur(i,x,y) for(int i=x;i<=y;++i)
const int N=1000001;
char s[N];
int n,m,sa[N],rnk[N],tp[N],tax[N];
void qsort(){//对(rnk[i],tp[i])进行排序
    // tax[i]: i号元素出现了多少次
    fur(i,0,m)tax[i]=0;
    fur(i,1,n)++tax[rnk[i]];
    fur(i,1,m)tax[i]+=tax[i-1];
    for(int i=n;i;--i)
        sa[tax[rnk[tp[i]]]--]=tp[i];
}
void suffix(){
    m=75;
    fur(i,1,n)rnk[i]=s[i]-'a'+1,tp[i]=i;
    qsort();
    for(int w=1,p=0;p<n;m=p,w<<=1){
        p=0;
        fur(i,1,w)tp[++p]=n-w+i;
        fur(i,1,n)if(sa[i]>w)
            tp[++p]=sa[i]-w;
        qsort();
        std::swap(tp,rnk);
        rnk[sa[1]]=p=1;
        fur(i,2,n)
            rnk[sa[i]]=p+=tp[sa[i-1]]^tp[sa[i]]||tp[sa[i-1]+w]^tp[sa[i]+w];
    }
}
int main(){
    scanf("%s",s+1),n=strlen(s+1);
    suffix();
    fur(i,1,n)printf("%d ",sa[i]);
}
```

## height数组

单纯看`sa`数组,可能没什么用

我们定义`height[i]`表示后缀`sa[i]`与后缀`sa[i-1]`的最长公共前缀(`LCP`)

仔细思考可以发现,后缀$j$和后缀$k$($rnk_j<rnk_k$)的最长公共前缀为:

$$\min_{i=rnk_j}^{rnk_k}\left\{height_i\right\}$$

这样一来建立一个`ST`表就可以快速求出任意两个后缀的`LCP`了

如果直接通过枚举计算`height`数组,时间复杂度为$\Theta(n^2)$

如何快速求`height`数组？

再定义`H[i]=height[rnk[i]]`

结论: $H_i\ge H_{i-1}-1$

![](height.png)

浅蓝的是`H[i-1]`的结果,蓝色部分最多比浅蓝部分少了开头一小段

红线截取的部分也一定是相同的

所以$H_i\ge H_{i-1}-1$

按照`H[1],H[2],...,H[n]`的顺序计算,并利用`H`数组的性质,时间复杂度可以降为$\Theta(n)$

```cpp
int height[N];
void get_height(){
    for(int i=1,k=0;i<=n;++i){
		if(k)--k;
		int j=sa[rnk[i]-1];
		while(s[i+k]==s[j+k]&&i+k<=n&&j+k<=n)++k;
		height[rnk[i]]=k; 
	}
}
```

## 最长公共子串

1. 连接两个字符串
2. 求$sa,rnk,height$
3. 求排名相邻但原来不在同一个字符串中的两个后缀的`height`值的最大值。
   
时间复杂度$\Theta(A+B)$已经取到下限,由此看出,这是一个非常优秀的算法。

![](lcs.png)

## 习题

[LG P5546 \[POI2000\]公共串](https://www.luogu.com.cn/problem/P5546)

多个字符串的共同子串

```cpp
#include<bits/stdc++.h>
const int N=10111;
int cnt,n,m,sa[N],rnk[N],height[N],tax[N],tp[N];
char s[N];
void qsort(){
    for(int i=0;i<=m;++i)tax[i]=0;
    for(int i=1;i<=n;++i)++tax[rnk[i]];
    for(int i=1;i<=m;++i)tax[i]+=tax[i-1];
    for(int i=n;i;--i)
        sa[tax[rnk[tp[i]]]--]=tp[i];
}
void suffix(){
    m=100;
    for(int i=1;i<=n;++i)tp[i]=i,rnk[i]=s[i]-'a'+1;
    qsort();
    for(int w=1,p=0;p<n;m=p,w<<=1){
        p=0;
        for(int i=1;i<=w;++i)tp[++p]=n-w+i;
        for(int i=1;i<=n;++i)if(sa[i]>w)
            tp[++p]=sa[i]-w;
        qsort();
        std::swap(tp,rnk);
        rnk[sa[1]]=p=1;
        for(int i=2;i<=n;++i)
            rnk[sa[i]]=p+=tp[sa[i]]^tp[sa[i-1]]||tp[sa[i]+w]^tp[sa[i-1]+w];
    }
}
void get_height(){
    for(int i=1,k=0;i<=n;++i){
        if(k)--k;
        int j=sa[rnk[i]-1];
        while(s[i+k]==s[j+k]&&i+k<=n&&j+k<=n)++k;
        height[rnk[i]]=k;
    }
}
int col[N],L[N],R[N],v[N],tot;
void add(int x){if(col[x])if(++v[col[x]]==1)++tot;}
void del(int x){if(col[x])if(!--v[col[x]])--tot;}
void cmax(int &x,int y){if(x<y)x=y;}
int main(){
    scanf("%d",&cnt);
    for(int i=1;i<=cnt;++i)
        L[i]=n+1,
        scanf("%s",s+n+1),
        s[n=strlen(s+1)+1]=i+'a'-1,
        R[i]=n-1;
    suffix();
    get_height();
    for(int i=1;i<=cnt;++i)
        for(int j=L[i];j<=R[i];++j)
            col[rnk[j]]=i;
    using std::deque;
    deque<int>q;
	int l=1,ans=0;
	add(1);
	for(int r=2;r<=n;++r){
		while(!q.empty()&&height[q.back()]>=height[r])q.pop_back();
		q.emplace_back(r);
		add(r);
		if(tot==cnt){
			while(tot==cnt&&l<r)del(l++);
			add(--l);
		}
		while(!q.empty()&&q.front()<=l) q.pop_front();
		if(tot==cnt)cmax(ans,height[q.front()]);
	}
    printf("%d\n",ans);
}
```

[\[SCOI2012\]喵星球上的点名](https://www.luogu.com.cn/problem/P2336)
