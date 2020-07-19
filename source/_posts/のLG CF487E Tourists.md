---
author: zc
avatar: null
categories:
- - "\u5237\u9898\u8BB0\u5F55"
commnet: 1
date: 2020-01-27 18:12
html: "<details><summary>\u67E5\u770B\u539F\u9898</summary><div id='from'></div><p><button\
  \ onclick=\"document.getElementById('from').innerHTML='<iframe src=&quot;https://www.luogu.com.cn/problem/CF487E&quot;\
  \ width=100% height=800px style=&quot;border: none;&quot;><iframe>'\" class='mdui-btn\
  \ mdui-btn-raised mdui-ripple'>\u70B9\u51FB\u52A0\u8F7D</button><a class='mdui-btn\
  \ mdui-btn-raised mdui-ripple' href=\"https://www.luogu.com.cn/problem/CF487E\"\
  \ target='_blank'>\u70B9\u51FB\u8DF3\u8F6C</a><p></details>"
permalink: LG CF487E Tourists
tags:
- "\u4ED9\u4EBA\u638C"
- tarjan
- "\u6811\u94FE\u5256\u5206"
- "\u7EBF\u6BB5\u6811"
thumbnail: null
title: LG CF487E Tourists
top: 0
---
建完广义圆方树后用树链剖分+线段树维护

修改一个点的时候,考虑到要修改它所在的双连通分量中的点,我们可以在（它的父亲）方点建一个对顶堆来维护最小值
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
    #define FL(i,x) for(int i(HEAD[x]),to;to=e[i].to,i;i=e[i].nxt)
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
namespace IO{const int str=1<<20;static char in_buf[str],*in_s,*in_t;bool __=0;il char gc(){return (in_s==in_t)&&(in_t=(in_s=in_buf)+fread(in_buf,1,str,stdin)),in_s==in_t?__=1,EOF:*in_s++;}il void in(string &ch){ch.clear();if(__)return;char c;while((c=gc())!=EOF&&isspace(c));if(c==EOF){__=1;return;}ch+=c;while((c=gc())!=EOF&&!isspace(c))ch+=c;if(c==EOF)__=1;}il void in(char &ch){if(__)return;char c;while((c=gc())!=EOF&&isspace(c));if(c==EOF)__=1;else ch=c;}il void in(char *ch){*ch='\0';if(__)return;char c;while((c=gc())!=EOF&&isspace(c));if(c==EOF){__=1;return;}*ch=c;ch++;while((c=gc())!=EOF&&!isspace(c))*ch=c,ch++;if(c==EOF)__=1;*ch='\0';}template<typename T>il void in(T &x){if(__)return;char c=gc();bool f=0;while(c!=EOF&&(c<'0'||c>'9'))f^=(c=='-'),c=gc();if(c==EOF){__=1;return;}x=0;while(c!=EOF&&'0'<=c&&c<='9')x=x*10+c-48,c=gc();if(c==EOF)__=1;if(f)x=-x;}template<typename T,typename ... arr>il void in(T &x,arr & ... y){in(x),in(y...);}const char ln='\n';static char out_buf[str],*out_s=out_buf,*out_t=out_buf+str;il void flush(){fwrite(out_buf,1,out_s-out_buf,stdout);out_s=out_buf;}il void pt(char c){(out_s==out_t)?(fwrite(out_s=out_buf,1,str,stdout),*out_s++=c):(*out_s++=c);}il void out(const char* s){while(*s)pt(*s++);}il void out(char* s){while(*s)pt(*s++);}il void out(char c){pt(c);}il void out(string s){for(int i=0;s[i];i++)pt(s[i]);}template<typename T>il void out(T x){if(!x){pt('0');return;}if(x<0)pt('-'),x=-x;char a[50],t=0;while(x)a[t++]=x%10,x/= 10;while(t--)pt(a[t]+'0');}template<typename T,typename ... arr>il void out(T x,arr & ... y){out(x),out(y...);}}using namespace IO;
const int N=200011;
int n,m,q,tot,cnt=0,head[N],HEAD[N],val[N];
struct node{
    priority_queue<int,vector<int>,greater<int>>a,b;
    il void push(int x){a.push(x);}
    il void del(int x){b.push(x);}
    il int top(){
        while(!b.empty()&&a.top()==b.top())a.pop(),b.pop();
        return a.top();
    }
}ne[N];
struct edge{int to,nxt;}e[N<<2];
il void add(int x,int y){
    e[++cnt].to=y;e[cnt].nxt=head[x];head[x]=cnt;
    e[++cnt].to=x;e[cnt].nxt=head[y];head[y]=cnt;
}
il void ADD(int x,int y){
    e[++cnt].to=y;e[cnt].nxt=HEAD[x];HEAD[x]=cnt;
    e[++cnt].to=x;e[cnt].nxt=HEAD[y];HEAD[y]=cnt;
}
int dfn[N],low[N],sz=0,st[N],tp=0;
void tarjan(int x,int fa){
    dfn[x]=low[x]=++sz;st[++tp]=x;
    fl(i,x)
    if(!dfn[to]){
        tarjan(to,x);
        low[x]=MIN(low[x],low[to]);
        if(low[to]>=dfn[x]){
            ADD(++tot,x);
            while(int k=st[tp--]){
                ADD(tot,k);
                if(k==to)break;
            }
        }
    }
    else if(to!=fa)low[x]=MIN(low[x],dfn[to]);
}
int s[N<<2],a[N];
#define ls rt<<1
#define rs rt<<1|1
#define pu s[rt]=MIN(s[ls],s[rs])
void build(int l,int r,int rt){
    if(l==r)return void(s[rt]=a[l]);
    int m=(l+r)>>1;
    build(l,m,ls);build(m+1,r,rs);
    pu;
}
void upd(int p,int v,int l=1,int r=tot,int rt=1){
    if(l==r)return void(s[rt]=v);
    int m=(l+r)>>1;
    if(p<=m)upd(p,v,l,m,ls);
    else upd(p,v,m+1,r,rs);
    pu;
}
int ask(int L,int R,int l=1,int r=tot,int rt=1){
    if(L<=l&&r<=R)return s[rt];
    int m=(l+r)>>1;
    return MIN(((L<=m)?ask(L,R,l,m,ls):inf),((R>m)?ask(L,R,m+1,r,rs):inf));
}
int siz[N],top[N],d[N],f[N],son[N],id[N],SZ=0;
void dfs(int x){
    siz[x]=1;
    FL(i,x)if(to!=f[x]){
        f[to]=x;
        d[to]=d[x]+1;
        dfs(to);
        siz[x]+=siz[to];
        if(siz[to]>siz[son[x]])son[x]=to;
    }
}
void bt(int x,int tp){
    top[x]=tp;id[x]=++SZ;a[id[x]]=val[x];
    if(son[x])bt(son[x],tp);
    FL(i,x)if(!top[to])bt(to,to);
}
int fm(int x,int y){
    int ans=inf;
    while(top[x]!=top[y]){
        if(d[top[x]]<d[top[y]])SWAP(x,y);
        ans=MIN(ans,ask(id[top[x]],id[x]));x=f[top[x]];
    }
    if(d[x]>d[y])SWAP(x,y);
    if(x>n)ans=MIN(ans,val[f[x]]);
    return MIN(ans,ask(id[x],id[y]));
}
int main(){
    in(n,m,q);tot=n;
    int x,y;
    char ch;
    Fur(i,1,n)in(val[i]);
    Fur(i,1,m)in(x,y),add(x,y);
    tarjan(1,0);
    dfs(1);
    Fur(i,1,n)if(f[i])
        ne[f[i]].push(val[i]);
    Fur(i,n+1,tot)val[i]=ne[i].top();
    bt(1,1);
    build(1,tot,1);
    while(q--){
        in(ch,x,y);
        if(ch=='C'){
            upd(id[x],y);
            if(f[x]){
                ne[f[x]].del(val[x]);
                ne[f[x]].push(y);
                if(val[f[x]]!=ne[f[x]].top())
                    upd(id[f[x]],val[f[x]]=ne[f[x]].top());
            }
            val[x]=y;
        }
        else out(fm(x,y),ln);
    }
    flush();
}
```
