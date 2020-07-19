---
author: zc
avatar: null
categories:
- - "\u5237\u9898\u8BB0\u5F55"
commnet: 1
date: 2020-01-18 22:40
html: "<details><summary>\u67E5\u770B\u539F\u9898</summary><div id='from'></div><p><button\
  \ onclick=\"document.getElementById('from').innerHTML='<iframe src=&quot;https://www.luogu.com.cn/problem/CF1196F&quot;\
  \ width=100% height=800px style=&quot;border: none;&quot;><iframe>'\" class='mdui-btn\
  \ mdui-btn-raised mdui-ripple'>\u70B9\u51FB\u52A0\u8F7D</button><a class='mdui-btn\
  \ mdui-btn-raised mdui-ripple' href=\"https://www.luogu.com.cn/problem/CF1196F\"\
  \ target='_blank'>\u70B9\u51FB\u8DF3\u8F6C</a><p></details>"
permalink: LG CF1196F K-th-Path
tags:
- "\u5806"
- "\u8D2A\u5FC3"
- floyed
thumbnail: null
title: LG CF1196F K-th-Path
top: 0
---
仔细看题意,发现$k$最大只有$400$

解法1： 堆 贪心

先把和每个点相连的所有边按边权从小到大排序。

考虑一条路径的两个端点,如果这两个端点间的路径第一次被弹出（是两点间最短路）,则我们向其中一端扩展一条与它相连的最短边。

现在假设堆顶有一条路径$u\rightarrow v$,它的一个端点$v$是由$u\rightarrow$扩展来的,此时我们可以尝试把与$x$相连的边中比$x\rightarrow v$权值略大的取出来（即排好序后的下一条边）,压到堆中。

因为要处理两个端点比较麻烦,我们转化成有向路径（只有一个端点）,然后取第$2k$大的。

记住我们需要维护的信息：路径的两个端点$st,ed$,端点$ed$前面的点$x$（即$ed$是由$st\rightarrow x$扩展来的）,以及这条路径的长度。

解法2： floyd

考虑答案应该小于等于第$k$小的边的长度。因此只有前$k$小的边对答案有贡献。这$k$条边构成的子图的节点数也是$O(k)$的,于是我们就可以做floyd了。
```cpp
#include<bits/stdc++.h>
namespace ZDY{
    #pragma GCC optimize(3)
    #define il __inline__ __attribute__ ((always_inline))
    #define register
    #define ll long long
    #define ull unsigned long long
    #define db double
    #define sht short
    #define MB template <class T>il
    #define Fur(i,x,y) for(int i(x);i<=y;++i)
    #define Fdr(i,x,y) for(int i(x);i>=y;--i)
    #define fl(i,x) for(int i(head[x]),to;to=e[i].to,i;i=e[i].nxt)
    #define clr(x,y) memset(x,y,sizeof(x))
    #define cpy(x,y) memcpy(x,y,sizeof(x))
    #define fin(s) freopen(s".in","r",stdin)
    #define fout(s) freopen(s".out","w",stdout)
    #define fcin ios::sync_with_stdio(false)
    #define l2(n) ((int)(log2(n)))
    #define inf 2122219134
    MB T ABS(T x){return x>0?x:-x;}
    MB T MAX(T x,T y){return x>y?x:y;}
    MB T MIN(T x,T y){return x<y?x:y;}
    MB T GCD(T x,T y){return y?GCD(y,x%y):x;}
    MB void SWAP(T &x,T &y){T t=x;x=y;y=t;}
}using namespace ZDY;using namespace std;
namespace IO{const int str=1<<20;static char in_buf[str],*in_s,*in_t;bool __=0;il char gc(){return (in_s==in_t)&&(in_t=(in_s=in_buf)+fread(in_buf,1,str,stdin)),in_s==in_t?EOF:*in_s++;}il void in(string &ch){ch.clear();if(__)return;char c;while((c=gc())!=EOF&&isspace(c));if(c==EOF){__=1;return;}ch+=c;while((c=gc())!=EOF&&!isspace(c))ch+=c;if(c==EOF)__=1;}il void in(char &ch){if(__)return;char c;while((c=gc())!=EOF&&isspace(c));if(c==EOF)__=1;else ch=c;}il void in(char *ch){*ch='\0';if(__)return;char c;while((c=gc())!=EOF&&isspace(c));if(c==EOF){__=1;return;}*ch=c;ch++;while((c=gc())!=EOF&&!isspace(c))*ch=c,ch++;if(c==EOF)__=1;*ch='\0';}template<typename T>il void in(T &x){if(__)return;char c=gc();bool f=0;while(c!=EOF&&(c<'0'||c>'9'))f^=(c=='-'),c=gc();if(c==EOF){__=1;return;}x=0;while(c!=EOF&&'0'<=c&&c<='9')x=x*10+c-48,c=gc();if(c==EOF)__=1;if(f)x=-x;}template<typename T,typename ... arr>il void in(T &x,arr & ... y){in(x),in(y...);}const char ln='\n';static char out_buf[str],*out_s=out_buf,*out_t=out_buf+str;il void flush(){fwrite(out_buf,1,out_s-out_buf,stdout);out_s=out_buf;}il void pt(char c){(out_s==out_t)?(fwrite(out_s=out_buf,1,str,stdout),*out_s++=c):(*out_s++=c);}il void out(const char* s){while(*s)pt(*s++);}il void out(char* s){while(*s)pt(*s++);}il void out(char c){pt(c);}il void out(string s){for(int i=0;s[i];i++)pt(s[i]);}template<typename T>il void out(T x){if(!x){pt('0');return;}if(x<0)pt('-'),x=-x;char a[50],t=0;while(x)a[t++]=x%10,x/= 10;while(t--)pt(a[t]+'0');}template<typename T,typename ... arr>il void out(T x,arr & ... y){out(x),out(y...);}}using namespace IO;
#define N 200011
int n,m,k;
struct edge{
    int to,w;
    bool operator<(edge x)const {
        return w<x.w;
    }
};
vector<edge>e[N];
struct node{
    int x,y,idx;
    ll v;
    bool operator<(node a)const{
        return v>a.v;
    }
};
priority_queue<node>q;
#include<bits/extc++.h>
using namespace __gnu_pbds;
cc_hash_table<int,bool>b[N];
signed main(){
    in(n,m,k);
    int x,y,w;
    Fur(i,1,m)
        in(x,y,w),
        e[x].push_back({y,w}),
        e[y].push_back({x,w});
    Fur(i,1,n){
        b[i][i]=1,sort(e[i].begin(),e[i].end());
        q.push({i,i,0,e[i][0].w});
    }
    k<<=1;
    while(!q.empty()){
        node t=q.top();q.pop();
        int x=t.x,y=t.y;
        if(!b[x][e[y][t.idx].to]){
            b[x][e[y][t.idx].to]=1;
            --k;
            if(!k)return cout<<t.v<<endl,0;
            q.push({x,e[y][t.idx].to,0,t.v+e[e[y][t.idx].to][0].w});
        }
        if(t.idx+1<e[y].size())
            q.push({x,y,t.idx+1,t.v-e[y][t.idx].w+e[y][t.idx+1].w});
    }
}
```
