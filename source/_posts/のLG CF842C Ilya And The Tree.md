---
author: zc
avatar: null
categories:
- - 刷题记录
commnet: 1
date: 2019-12-21 19:47
html: '<details><summary>查看原题</summary><div id=''from''></div><p><button onclick="document.getElementById(''from'').innerHTML=''<iframe
  src=&quot;https://www.luogu.com.cn/problem/CF842C&quot; width=100% height=800px
  style=&quot;border: none;&quot;><iframe>''" class=''mdui-btn mdui-btn-raised mdui-ripple''>点击加载</button><a
  class=''mdui-btn mdui-btn-raised mdui-ripple'' href="https://www.luogu.com.cn/problem/CF842C"
  target=''_blank''>点击跳转</a><p></details>'
permalink: LG CF842C Ilya And The Tree
tags:
- 并查集
thumbnail: null
title: LG CF842C Ilya And The Tree
top: 0
---
把所有路径上的最大值的和 和 所有路径上的最小值的和 分开算

我们按最大值的计算考虑（最小值就是反过来）

我们考虑一个点能贡献多少次

从它的各个子树中拿出来组合

我们可以按权值从小到大的顺序添加节点

这样就只要和当前要添加的节点联通的点都符合要求

这样的话我们可以用并查集来维护连通块大小


```cpp
#include<iostream>
#include<vector>
#include<cstring>
#include<algorithm>
using namespace std;
struct edge{
    int to,next;
}e[400040];
int eid=0,head[200010];
void insert(int u,int v){
    eid++;
    e[eid].to=v;
    e[eid].next=head[u];
    head[u]=eid;
}
int a[200010];
int n;
int fa[200010];
int dp[200010];//某一个点的美丽值 
vector<int>v[200010];//存储每一个点的美丽值的可能值 
int gcd(int a,int b){
    if(b==0)return a;
    return gcd(b,a%b);
}
void dfs(int x,int pre){
    for(int i=head[x];i+1;i=e[i].next){
        int k=e[i].to;
        if(k==pre)continue;
        dp[k]=gcd(dp[x],a[k]);
        v[k].push_back(dp[x]);
        for(int j=0;j<v[x].size();j++){
            v[k].push_back(gcd(v[x][j],a[k]));
        }
        sort(v[k].begin(),v[k].end());//排序+去重,保证最后面的元素最优 
        v[k].erase(unique(v[k].begin(),v[k].end()),v[k].end());
        dfs(k,x);
    }
}
int main(){
    memset(head,-1,sizeof(head));
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    for(int i=1;i<n;i++){
        int x,y;
        cin>>x>>y;
        insert(x,y);
        insert(y,x);
        fa[y]=x;
    }
    fa[1]=0;
    dp[1]=a[1];
    v[1].push_back(0);
    dfs(1,0);
    for(int i=1;i<=n;i++){
        dp[i]=max(dp[i],v[i].back());//用vector里面的最优答案更新结果 
    }
    for(int i=1;i<=n;i++){
        cout<<dp[i];
        if(i!=n)cout<<" ";
        else cout<<endl;
    }
}
```
