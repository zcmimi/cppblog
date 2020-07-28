---
author: zc
avatar: null
categories:
- - 刷题记录
commnet: 1
date: 2020-05-16 21:36
html: '<details><summary>查看原题</summary><div id=''from''></div><p><button onclick="document.getElementById(''from'').innerHTML=''<iframe
  src=&quot;https://www.luogu.com.cn/problem/P2463&quot; width=100% height=800px style=&quot;border:
  none;&quot;><iframe>''" class=''mdui-btn mdui-btn-raised mdui-ripple''>点击加载</button><a
  class=''mdui-btn mdui-btn-raised mdui-ripple'' href="https://www.luogu.com.cn/problem/P2463"
  target=''_blank''>点击跳转</a><p></details>'
permalink: LG 2463 [SDOI2008]Sandy的卡片
tags:
- 后缀数组
- 二分
- 差分
- 单调队列
thumbnail: null
title: LG 2463 [SDOI2008]Sandy的卡片
top: 0
---
> 相同的定义为：两个子串长度相同且一个串的全部元素加上一个数就会变成另一个串

那么我们差分之后再判断即可
```cpp
#include<bits/stdc++.h>
#define gc getchar()
#define fur(i,x,y) for(int i=x;i<=y;++i)
void cmin(int &x,int y){if(x>y)x=y;}
int rd(){int x=0;char c;bool f=0;for(c=gc;c<'0'||'9'<c;c=gc)f^=c=='-';for(x=c-48,c=gc;'0'<=c&&c<='9';x=x*10+c-48,c=gc);return f?-x:x;}
const int N=1000011;
int cnt,n,m,sa[N],rnk[N],height[N],tax[N],tp[N],col[N],s[N];
void qsort(){
    fur(i,0,m)tax[i]=0;
    fur(i,1,n)++tax[rnk[i]];
    fur(i,1,m)tax[i]+=tax[i-1];
    for(int i=n;i;--i)sa[tax[rnk[tp[i]]]--]=tp[i];
}
void suffix(){
    m=3000;
    fur(i,1,n)rnk[i]=s[i],tp[i]=i;
    qsort();
    for(int w=1,p=0;p<n;m=p,w<<=1){
        p=0;
        fur(i,1,w)tp[++p]=n-w+i;
        fur(i,1,n)if(sa[i]>w)tp[++p]=sa[i]-w;
        qsort();
        std::swap(tp,rnk);
        rnk[sa[1]]=p=1;
        fur(i,2,n)
            rnk[sa[i]]=p+=tp[sa[i]]^tp[sa[i-1]]||tp[sa[i]+w]^tp[sa[i-1]+w];
    }
}
void gh(){
    for(int i=1,k=0;i<=n;++i){
        if(k)--k;
        int j=sa[rnk[i]-1];
        while(s[i+k]==s[j+k]&&i+k<=n&&j+k<=n)++k;
        height[rnk[i]]=k;
    }
}
/* 二分判断
bool v[N];
int sta[N],top;
bool chk(int x){
	while(top)v[sta[top--]]=0;
	for (int i=1;i<=n;i++) {
		if (height[i]<x)while(top)v[sta[top--]]=0;
		if(!v[col[sa[i]]]){
			v[col[sa[i]]]=1;
			sta[++top]=col[sa[i]];
			if(top==cnt)return 1; 
		}
	}
	return 0;
}
*/
int tot,v[N],q[N],L[N],R[N];
void add(int x){if(col[x]&&++v[col[x]]==1)++tot;}
void del(int x){if(col[x]&&!--v[col[x]])--tot;}
int main(){
    int mi=-1u>>1;
    cnt=rd();
    fur(i,1,cnt){
        int t=rd(),la=rd();
        L[i]=n+1;
        while(--t)s[++n]=rd()-la,la+=s[n],cmin(mi,s[i]);
        R[i]=n;
        s[++n]=1865+i;
    }
    fur(i,1,n)s[i]=s[i]-mi+1;
    suffix(),gh();
    /* 二分
    int l=0,r=110,ans=0;
    while (l<=r){
		int mid=l+r>>1;
		if (chk(mid))l=mid+1,ans=mid;
		else r=mid-1;
	}
    */
    fur(i,1,cnt)fur(j,L[i],R[i])col[rnk[j]]=i;
    int h=1,t=0,l=1,ans=0;
    add(1);
    fur(i,2,n){
        while(h<=t&&height[i]<=height[q[t]])--t;
        q[++t]=i;
        add(i);
        if(tot==cnt){
            while(tot==cnt&&l<i)del(l++);
            add(--l);
        }
        while(h<=t&&q[h]<=l)++h;
        if(tot==cnt&&height[q[h]]>ans)ans=height[q[h]];
    }
    printf("%d\n",ans+1);
}
```
