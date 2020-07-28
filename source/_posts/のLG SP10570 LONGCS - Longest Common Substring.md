---
author: zc
avatar: null
categories:
- - 刷题记录
commnet: 1
date: 2020-05-16 14:13
html: '<details><summary>查看原题</summary><div id=''from''></div><p><button onclick="document.getElementById(''from'').innerHTML=''<iframe
  src=&quot;https://www.luogu.com.cn/problem/SP10570&quot; width=100% height=800px
  style=&quot;border: none;&quot;><iframe>''" class=''mdui-btn mdui-btn-raised mdui-ripple''>点击加载</button><a
  class=''mdui-btn mdui-btn-raised mdui-ripple'' href="https://www.luogu.com.cn/problem/SP10570"
  target=''_blank''>点击跳转</a><p></details>'
permalink: LG SP10570 LONGCS - Longest Common Substring
tags:
- 后缀数组
thumbnail: null
title: LG SP10570 LONGCS - Longest Common Substring
top: 0
---
```cpp
#include<bits/stdc++.h>
const int N=1000111;
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
    m=200;
    for(int i=1;i<=n;++i)sa[i]=0,rnk[i]=(s[i]<='a')?s[i]:(s[i]-'a'+1),tp[i]=i;
    qsort();
    for(int w=1,p=0;p<n;m=p,w<<=1){
        p=0;
        for(int i=1;i<=w;++i)tp[++p]=n-w+i;
        for(int i=1;i<=n;++i)
            if(sa[i]>w)tp[++p]=sa[i]-w;
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
int col[N],L[N],R[N],v[N],tot,q[N];
void add(int x){if(col[x])if(++v[col[x]]==1)++tot;}
void del(int x){if(col[x])if(!--v[col[x]])--tot;}
void cmax(int &x,int y){if(x<y)x=y;}
int main(){
    int T;scanf("%d",&T);
while(T--){
    n=tot=0;memset(height,0,sizeof height);
    memset(col,0,sizeof col);
    memset(v,0,sizeof v);
    memset(q,0,sizeof q);
    scanf("%d",&cnt);
    for(int i=1;i<=cnt;++i)
        L[i]=n+1,
        scanf("%s",s+n+1),
        s[n=strlen(s+1)+1]=i,
        R[i]=n-1;
    suffix();
    get_height();
    for(int i=1;i<=cnt;++i)
        for(int j=L[i];j<=R[i];++j)
            col[rnk[j]]=i;
	int l=1,ans=0,h=1,t;
    tot=0;
	add(1);
	for(int r=2;r<=n;++r){
		while(h<=t&&height[q[t]]>=height[r])--t;
		q[++t]=r;
		add(r);
		if(tot==cnt){
			while(tot==cnt&&l<r)del(l++);
			add(--l);
		}
		while(h<=t&&q[h]<=l)++h;
		if(tot==cnt)cmax(ans,height[q[h]]);
	}
    printf("%d\n",ans);
}
}
```
