---
author: zc
avatar: null
categories:
- - 刷题记录
commnet: 1
date: 2020-01-18 22:40
html: '<details><summary>查看原题</summary><div id=''from''></div><p><button onclick="document.getElementById(''from'').innerHTML=''<iframe
  src=&quot;https://www.luogu.com.cn/problem/CF1076E&quot; width=100% height=800px
  style=&quot;border: none;&quot;><iframe>''" class=''mdui-btn mdui-btn-raised mdui-ripple''>点击加载</button><a
  class=''mdui-btn mdui-btn-raised mdui-ripple'' href="https://www.luogu.com.cn/problem/CF1076E"
  target=''_blank''>点击跳转</a><p></details>'
permalink: LG CF1076E Vasya-and-a-Tree
tags:
- 差分
- 树状数组
thumbnail: null
title: LG CF1076E Vasya-and-a-Tree
top: 0
---
解法1(在线)：

bfs序,实现较为麻烦

解法2(离线)：

考虑单独的一个节点$u$,它的操作影响的都是在它子树内的与$u$深度差小于等于$k$的节点,那么我们只要维护每层深度的操作总和就行了

修改$x$影响的只有$x$的子树,我们可以在dfs时这样操作：

1.进入该点
2. 实现该点的所有操作
3. 递归它的子树
4. 撤销操作

这样就不会影响到其他点了
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
#define N 300011
int n,cnt=0,head[N];
struct edge{
    int to,nxt;
}e[N<<1];
il void add(int x,int y){
    e[++cnt].to=y;e[cnt].nxt=head[x];head[x]=cnt;
}
ll s[N],ans[N];
il void upd(int x,int v){
    for(int i=x;i<=n;i+=i&-i)
        s[i]+=v;
}
il ll ask(int x){
    ll ans=0;
    for(int i=x;i;i-=i&-i)
        ans+=s[i];
    return ans;
}
struct node{int v,d;};
vector<node>opt[N];
void dfs(int x,int d,int f){
    for(auto i:opt[x])
        upd(MIN(n,d+i.d),i.v);
    ans[x]=ask(n)-ask(d-1);
    fl(i,x)if(to!=f)dfs(to,d+1,x);
    for(auto i:opt[x])
        upd(MIN(n,d+i.d),-i.v);
}
int main(){
    in(n);
    int x,y,q,v,d;
    Fur(i,1,n-1)
        in(x,y),
        add(x,y),add(y,x);
    in(q);
    while(q--){
        in(x,d,v);
        opt[x].push_back(node{v,d});
    }
    dfs(1,1,0);
    Fur(i,1,n)out(ans[i]," ");
    flush();
}
```
