---
author: zc
avatar: null
categories:
- - "\u5237\u9898\u8BB0\u5F55"
commnet: 1
date: 2020-02-02 17:36
html: "<details><summary>\u67E5\u770B\u539F\u9898</summary><div id='from'></div><p><button\
  \ onclick=\"document.getElementById('from').innerHTML='<iframe src=&quot;https://www.luogu.com.cn/problem/CF547E&quot;\
  \ width=100% height=800px style=&quot;border: none;&quot;><iframe>'\" class='mdui-btn\
  \ mdui-btn-raised mdui-ripple'>\u70B9\u51FB\u52A0\u8F7D</button><a class='mdui-btn\
  \ mdui-btn-raised mdui-ripple' href=\"https://www.luogu.com.cn/problem/CF547E\"\
  \ target='_blank'>\u70B9\u51FB\u8DF3\u8F6C</a><p></details>"
permalink: LG CF547E Mike-and-Friends
tags:
- "AC\u81EA\u52A8\u673A"
- "\u79BB\u7EBF"
- "\u6811\u72B6\u6570\u7EC4"
- "\u4E3B\u5E2D\u6811"
thumbnail: null
title: LG CF547E Mike-and-Friends
top: 0
---
AC自动机建完fail树之后子树的siz就是里面相同字符串的个数

每个询问可以拆成$r$的前缀和-$l$的前缀和

然后离线处理后用树状数组维护就可以了

主席树在线也可以
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
const int N=200011,M=500011;
int n,m,cnt=0,head[N],k[M],ans[M];
char ch[N];
struct edge{int to,nxt;}e[N*26];
il void add(int x,int y){e[++cnt].to=y;e[cnt].nxt=head[x];head[x]=cnt;}
int tot=1,tr[N][26],ed[N],f[N],fail[N],q[N*26];
il void build(){
    int h=0,t=0,x;
    Fur(i,0,25)
    if(tr[1][i])fail[tr[1][i]]=1,q[t++]=tr[1][i];
    else tr[1][i]=1;

    while(h<t){
        x=q[h++];
        Fur(i,0,25)
        if(tr[x][i])fail[tr[x][i]]=tr[fail[x]][i],q[t++]=tr[x][i];
        else tr[x][i]=tr[fail[x]][i];
    }
}
int id[N],sz=0,siz[N];
void dfs(int x){
    id[x]=++sz;siz[x]=1;
    fl(i,x)dfs(to),siz[x]+=siz[to];
}
int s[N];
il void upd(int x){for(int i=x;i<=tot;i+=i&-i)++s[i];}
il int ask(int x){int t=0;for(int i=x;i;i-=i&-i)t+=s[i];return t;}
int main(){
    in(n,m);
    Fur(i,1,n){
        in(ch);
        int p=1,len=strlen(ch),c;
        Fur(j,0,len-1){
            c=ch[j]-'a';
            if(!tr[p][c])f[tr[p][c]=++tot]=p;
            p=tr[p][c];
        }
        ed[i]=p;
    }

    build();
    Fur(i,2,tot)add(fail[i],i);
    dfs(1);

    clr(head,0);cnt=0;
    int l,r,x;
    Fur(i,1,m){
        in(l,r,k[i]);
        if(l>1)add(l-1,-i);
        add(r,i);
    }
    Fur(i,1,n){
        for(x=ed[i];x!=1;x=f[x])upd(id[x]);
        fl(j,i){
            int v=to>0?1:-1;
            to*=v;x=ed[k[to]];
            ans[to]+=v*(ask(id[x]+siz[x]-1)-ask(id[x]-1));
        }
    }
    Fur(i,1,m)out(ans[i],ln);
    flush();
}
```
