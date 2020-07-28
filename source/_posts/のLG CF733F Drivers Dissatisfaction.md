---
author: zc
avatar: null
categories:
- - 刷题记录
commnet: 1
date: 2019-12-21 19:47
html: '<details><summary>查看原题</summary><div id=''from''></div><p><button onclick="document.getElementById(''from'').innerHTML=''<iframe
  src=&quot;https://www.luogu.com.cn/problem/CF733F&quot; width=100% height=800px
  style=&quot;border: none;&quot;><iframe>''" class=''mdui-btn mdui-btn-raised mdui-ripple''>点击加载</button><a
  class=''mdui-btn mdui-btn-raised mdui-ripple'' href="https://www.luogu.com.cn/problem/CF733F"
  target=''_blank''>点击跳转</a><p></details>'
permalink: LG CF733F Drivers Dissatisfaction
tags:
- 树链剖分
- 最小生成树
thumbnail: null
title: LG CF733F Drivers Dissatisfaction
top: 0
---
仔细考虑一下,最终能够形成最小权值的生成树的情况一定是把S都用在减小某条边的费用

1. 如果那条边在最小生成树上,那么直接处理即可

2. 如果在外面,设这条边为$x \rightarrow y$,我们求出最小生成树上$x$到$y$上最大的一条边,删掉这条边

枚举删掉哪条边,然后执行上面的操作就可以了

记得开$long\ long$,$rmq$的数组开大点

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
#define N 300111
#define int ll
int n,m,S,OLD=0;
int cnt=0,head[N];
struct edge{
    int to,nxt,w,old;
}e[N*2];
void add(int x,int y,int w,int old){
    e[++cnt].to=y;e[cnt].old=old;e[cnt].w=w;e[cnt].nxt=head[x];head[x]=cnt;
}
struct link{
    int id,x,y,w,c;
}E[N];
bool used[N];
bool cmp(link x,link y){
    return x.w<y.w;
}
int fa[N];
int gf(int x){
    return (x==fa[x])?x:(fa[x]=gf(fa[x]));
}
int f[N],top[N],d[N],siz[N],id[N],sz=0,s[25][N],val[N];
void dfs(int x){
    siz[x]=1;
    fl(i,x)if(to!=f[x]){
        f[to]=x;d[to]=d[x]+1;val[to]=i;
        dfs(to);siz[x]+=siz[to];
    }
}
void bt(int x,int tp){
    top[x]=tp;id[x]=++sz;
    s[0][id[x]]=val[x];
    int k=0;
    fl(i,x)if(to!=f[x]&&siz[to]>siz[k])k=to;
    if(!k)return;bt(k,tp);
    fl(i,x)if(!top[to])bt(to,to);
}
int get(int x,int y){
    return e[x].w>e[y].w?x:y;
}
void st(){
    Fur(k,1,20)
		Fur(i,1,n-(1<<k)+1)
		s[k][i]=get(s[k-1][i],s[k-1][i+(1<<(k-1))]);
}
int ask(int l,int r){
    if(l>r)return 0;
	int k=l2(r-l+1);
	return get(s[k][l],s[k][r-(1<<k)+1]);
}
int fm(int x,int y){
    int ans=0;
    while(top[x]!=top[y]){
        if(d[top[x]]<d[top[y]])SWAP(x,y);
        ans=get(ans,ask(id[top[x]],id[x]));x=f[top[x]];
    }
    if(id[x]>id[y])SWAP(x,y);
    ans=get(ans,ask(id[x]+1,id[y]));
    return ans;
}
signed main(){
    fin("in");
    in>>n>>m;
    Fur(i,1,m)in>>E[i].w;
    Fur(i,1,m)in>>E[i].c;
    Fur(i,1,m)in>>E[i].x>>E[i].y,E[i].id=i;
    in>>S;
    sort(E+1,E+m+1,cmp);
    Fur(i,1,n)fa[i]=i;
    int x,y,w;
    e[0].w=-inf;
    Fur(i,1,m){
        x=E[i].x,y=E[i].y,w=E[i].w;
        if(gf(x)!=gf(y)){
            fa[fa[x]]=fa[y];
            OLD+=w;
            add(x,y,w,i);add(y,x,w,i);
            used[i]=1;
        }
    }
    dfs(1);bt(1,1);
    st();
    int ans=OLD,as,aw=0;
    Fur(i,1,m){
        int tmp,w=0;
        if(used[i])tmp=OLD-(S/E[i].c);
        else tmp=OLD-e[(w=fm(E[i].x,E[i].y))].w+E[i].w-(S/E[i].c);
        if(tmp<ans)ans=tmp,as=i,aw=w;
    }
    out<<ans<<ln;
    used[as]=1;E[as].w-=(S/E[as].c);
    used[e[aw].old]=0;
    Fur(i,1,m)if(used[i])
        out<<E[i].id<<" "<<E[i].w<<ln;
}
```
