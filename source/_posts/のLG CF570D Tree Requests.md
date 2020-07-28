---
author: zc
avatar: null
categories:
- - 刷题记录
commnet: 1
date: 2019-12-21 19:47
html: '<details><summary>查看原题</summary><div id=''from''></div><p><button onclick="document.getElementById(''from'').innerHTML=''<iframe
  src=&quot;https://www.luogu.com.cn/problem/CF570D&quot; width=100% height=800px
  style=&quot;border: none;&quot;><iframe>''" class=''mdui-btn mdui-btn-raised mdui-ripple''>点击加载</button><a
  class=''mdui-btn mdui-btn-raised mdui-ripple'' href="https://www.luogu.com.cn/problem/CF570D"
  target=''_blank''>点击跳转</a><p></details>'
permalink: LG CF570D Tree Requests
tags:
- 状态压缩
- 静态链分治
thumbnail: null
title: LG CF570D Tree Requests
top: 0
---
> ## 题意
>
> 一棵以1为根的树,每个节点上都有1个字母,有m个询问。每次询问v对应的子树中,深度为h的这层节点的字母,能否打乱重排组成回文串。根的深度为1,每个点的深度为到根的距离。
>
> ## 思路
>
> 一层结点的字母是否能组成回文串,只需观察每个字母出现次数要么都是偶数,要么只有一个字母奇数次出现。
>
> ### 解法一
>
> > DSU
>
> 二进制优化,每次都异或上字母对应的二进制位,只需记录答案1位是否<2即可。
>
> ### 代码1
>
> ```c++
> #include<bits/stdc++.h>
> #define M 500005
> using namespace std;
> struct query {
>     int de,id;
> };
> int n,m;
> vector<int>G[M];
> vector<query>Q[M];
> int L[M],R[M],ID[M],T;
> int dep[M],son[M],sz[M];
> int check[M],ans[M];
> char A[M];
> void dfs(int v,int d) {
>     L[v]=++T;
>     ID[T]=v;
>     dep[v]=d,son[v]=0,sz[v]=1;
>     for(int i=0; i<G[v].size(); i++) {
>         int u=G[v][i];
>         dfs(u,d+1);
>         if(sz[u]>sz[son[v]])son[v]=u;
>         sz[v]+=sz[u];
>     }
>     R[v]=T;
> }
> void Add_point(int x,int a) {
>     int r=A[x]-'a',d=dep[x];
>     check[d]^=(1<<r);//二进制优化
> }
> void Add_tree(int x,int a) {
>     for(int i=L[x]; i<=R[x]; i++)Add_point(ID[i],a);
> }
> void Solve(int v) {
>     for(int i=0; i<G[v].size(); i++) {
>         int u=G[v][i];
>         if(u==son[v])continue;
>         Solve(u);
>         Add_tree(u,-1);
>     }
>     if(son[v])Solve(son[v]);
>     for(int i=0; i<G[v].size(); i++) {
>         int u=G[v][i];
>         if(u==son[v])continue;
>         Add_tree(u,1);
>     }
>     Add_point(v,1);
>     for(int i=0; i<Q[v].size(); i++){
>         int d=Q[v][i].de,r=check[d],id=Q[v][i].id;
>         ans[id]=(r==(r&-r));
>     }
> }
> int main() {
>     scanf("%d%d",&n,&m);
>     for(int i=2,f; i<=n; i++) {
>         scanf("%d",&f);
>         G[f].push_back(i);
>     }
>     dfs(1,1);
>     scanf("%s",A+1);
>     for(int i=1; i<=m; i++) {
>         int x,d;
>         scanf("%d%d",&x,&d);
>         Q[x].push_back((query) {d,i});
>     }
>     Solve(1);
>     for(int i=1; i<=m; i++)
>         if(ans[i])puts("Yes");
>         else puts("No");
>     return 0;
> }
> ```
>
> ### 解法二
>
> > dfs作差
>
> 同样是二进制,每次进结点时记录原先的二进制数,出结点时再用更新过的数据异或上原来的即为答案。
>
> ### 代码二
>
> ```c++
> #include<bits/stdc++.h>
> #define M 500005
> using namespace std;
> struct query{
>     int de,id;
> };
> int n,m;
> vector<int>G[M],tmp[M];
> vector<query>Q[M];
> int cnt[M],ans[M];
> char A[M];
> void dfs(int v,int d){
>     cnt[d]^=1<<A[v]-'a';
>     for(int i=0;i<Q[v].size();i++)
>         tmp[v].push_back(cnt[Q[v][i].de]);
>     for(int i=0;i<G[v].size();i++)
>         dfs(G[v][i],d+1);
>     for(int i=0;i<Q[v].size();i++)
>         ans[Q[v][i].id]=(tmp[v][i]^cnt[Q[v][i].de]);
> }
> int main(){
>     scanf("%d%d",&n,&m);
>     for(int i=2,f;i<=n;i++){
>         scanf("%d",&f);
>         G[f].push_back(i);
>     }
>     scanf("%s",A+1);
>     for(int i=1;i<=m;i++){
>         int x,d;
>         scanf("%d%d",&x,&d);
>         Q[x].push_back((query){
>             d,i
>         });
>     }
>     dfs(1,1);
>     for(int i=1;i<=m;i++)
>         puts(ans[i]==(ans[i]&-ans[i])?"Yes":"No");
>     return 0;
> }
> ```
>
> ### 解法三
>
> > 在线 异或前缀和
>
> 只需将每个深度的结点按照dfs序排到一个vector里,同时记录每个对应的异或前缀和,则对于一个询问x,只需在给定深度里找比L[x]大的和比R[x]小的两个端点即可,再异或一下前缀和即可。
>
> ### 代码三
>
> ```c++
> #include<bits/stdc++.h>
> #define M 500005
> using namespace std;
> int n,m;
> vector<int>G[M],deep[M],Xor[M];
> int L[M],R[M],ID[M],T,mxdep;
> int dep[M];
> char A[M];
> void dfs(int v,int d) {
>     L[v]=++T;
>     ID[T]=v,dep[v]=d;
>     mxdep=max(mxdep,d);
>     deep[d].push_back(L[v]);
>     for(int i=0; i<G[v].size(); i++) {
>         int u=G[v][i];
>         dfs(u,d+1);
>     }
>     R[v]=T;
> }
> int main() {
>     scanf("%d%d",&n,&m);
>     for(int i=2,f; i<=n; i++) {
>         scanf("%d",&f);
>         G[f].push_back(i);
>     }
>     scanf("%s",A+1);
>     dfs(1,1);
>     for(int i=1;i<=mxdep;i++){
>         Xor[i].push_back(1<<(A[ID[deep[i][0]]]-'a'));
>         for(int j=1;j<deep[i].size();j++)//异或前缀和
>             Xor[i].push_back(Xor[i][j-1]^(1<<(A[ID[deep[i][j]]]-'a')));
>     }
>     while(m--){
>         int x,d,ans=0;
>         scanf("%d%d",&x,&d);
>         int l=lower_bound(deep[d].begin(),deep[d].end(),L[x])-deep[d].begin();
>         int r=upper_bound(deep[d].begin(),deep[d].end(),R[x])-deep[d].begin()-1;
>         //在当前深度找xdfs序之内的点
>         if(r<0)puts("Yes");
>         else {
>             if(l==0)ans=Xor[d][r];//处理前缀和
>             else ans=Xor[d][r]^Xor[d][l-1];
>             if(ans==(ans&-ans))puts("Yes");
>             else puts("No");
>         }
>     }
>     return 0;
> }
> ```
```cpp
#include<bits/stdc++.h>
namespace ZDY{
    #pragma GCC optimize(3)
    #define il __inline__ __attribute__ ((always_inline))
    #define rg register
    #define ll long long
    #define ull unsigned long long
    #define db double
    #define sht short
    #define MB template <class T>il
    #define Fur(i,x,y) for(int i=x;i<=y;++i)
    #define Fdr(i,x,y) for(int i=x;i>=y;--i)
    #define fl(i,x) for(int i=head[x],to;to=e[i].to,i;i=e[i].nxt)
    #define clr(x,y) memset(x,y,sizeof(x))
    #define cpy(x,y) memcpy(x,y,sizeof(x))
    #define fin(s) freopen(s".in","r",stdin)
    #define fout(s) freopen(s".out","w",stdout)
    #define fcin ios::sync_with_stdio(false)
    #define l2(n) ((int)(log2(n)))
    #define inf 0x3f3f3f3f
    MB T ABS(T x){return x>0?x:-x;}
    MB T MAX(T x,T y){return x>y?x:y;}
    MB T MIN(T x,T y){return x<y?x:y;}
    MB T GCD(T x,T y){return y?GCD(y,x%y):x;}
    MB void SWAP(T &x,T &y){T t=x;x=y;y=t;}
}using namespace ZDY;using namespace std;
namespace IO{const char* ln="\n";const int str=1<<20;struct IN{char buf[str],*s,*t;bool _;IN():s(buf),t(buf),_(0){}il char gc(){return s==t&&((t=(s=buf)+fread(buf,1,str,stdin))==s)?EOF:(*s++);}IN&operator>>(char&ch){if(_)return *this;char c;while((c=gc())!=EOF&&isspace(c));if(c==EOF)_=1;else ch=c;return *this;}IN& operator>>(char* ch){clr(ch,0);if(_)return *this;char c;while((c=gc())!=EOF&&isspace(c));if(c==EOF)return _=1,*this;*ch=c;ch++;while((c=gc())!=EOF&&!isspace(c))*ch=c,ch++;if(c==EOF)_=1;return *this;}IN& operator>>(string& ch){if(_)return *this;char c;while((c=gc())!=EOF&&isspace(c));if(c==EOF)return _=1,*this;ch+=c;while((c=gc())!=EOF&&!isspace(c))ch+=c;if(c==EOF)_=1;return *this;}template<typename T>IN&operator>>(T&x){if(_)return *this;char c=gc();bool ff=0;while(c!=EOF&&(c<'0'||c>'9'))ff^=(c=='-'),c=gc();if(c==EOF){_=1;return *this;}x=0;while(c!=EOF&&'0'<=c&&c<='9')x=(x<<3)+(x<<1)+c-48,c=gc();if(c==EOF)_=1;if(ff)x=-x;return *this;}}in;struct OUT{char buf[str],*s,*t;OUT():s(buf),t(buf+str){}~OUT(){fwrite(buf,1,s-buf,stdout);}void pt(char c){(s==t)?(fwrite(s=buf,1,str,stdout),*s++=c):(*s++=c);}OUT&operator<<(const char*s){while(*s)pt(*s++);return *this;}OUT&operator<<(char*s){while(*s)pt(*s++);return *this;}OUT&operator<<(string s){for(int i=0;s[i];i++)pt(s[i]);return *this;}template<typename T>OUT&operator<<(T x){if(!x)return pt('0'),*this;if(x<0)pt('-'),x=-x;char a[30],t=0;while(x)a[t++]=x%10,x/=10;while(t--)pt(a[t]+'0');return *this;}}out;}using namespace IO;
#define N 500011
int n,q,head[N],cnt=0;
struct edge{
    int to,nxt;
}e[N];
void add(int x,int y){
    e[++cnt].to=y;e[cnt].nxt=head[x];head[x]=cnt;
}
char ch[N];
int T[N],L[N],R[N],dfn=0,d[N],siz[N],son[N];
void dfs(int x){
    L[x]=++dfn;
    T[dfn]=x;
    siz[x]=1;son[x]=0;
    fl(i,x){
        d[to]=d[x]+1;
        dfs(to);
        if(siz[to]>siz[son[x]])son[x]=to;
        siz[x]+=siz[to];
    }
    R[x]=dfn;
}
int sta[N];
struct node{
    int d,id;
};
vector<node>que[N];
bool ans[N];
void Add(int x){
    int r=ch[x]-'a',D=d[x];
    sta[D]^=(1<<r);
}
void upd(int x){
    Fur(i,L[x],R[x])Add(T[i]);
}
void sol(int x){
    fl(i,x)if(to!=son[x]){
        sol(to);
        upd(to);
    }
    if(son[x])sol(son[x]);
    fl(i,x)if(to!=son[x])upd(to);
    Add(x);
    for(int i=0;i<que[x].size();++i){
        int D=que[x][i].d,r;r=sta[D];
        ans[que[x][i].id]=(r==(r&-r));
    }
}
int main(){
    fin("in");
    in>>n>>q;
    int x,y;
    Fur(i,2,n)in>>x,add(x,i);
    in>>(ch+1);
    d[1]=1;dfs(1);
    Fur(i,1,q)in>>x>>y,que[x].push_back(node{y,i});
    sol(1);
    Fur(i,1,q)out<<(ans[i]?"Yes":"No")<<ln;
}
```
