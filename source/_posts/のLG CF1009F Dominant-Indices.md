---
author: zc
avatar: null
categories:
- - "\u5237\u9898\u8BB0\u5F55"
commnet: 1
date: 2020-01-18 22:40
html: "<details><summary>\u67E5\u770B\u539F\u9898</summary><div id='from'></div><p><button\
  \ onclick=\"document.getElementById('from').innerHTML='<iframe src=&quot;https://www.luogu.com.cn/problem/CF1009F&quot;\
  \ width=100% height=800px style=&quot;border: none;&quot;><iframe>'\" class='mdui-btn\
  \ mdui-btn-raised mdui-ripple'>\u70B9\u51FB\u52A0\u8F7D</button><a class='mdui-btn\
  \ mdui-btn-raised mdui-ripple' href=\"https://www.luogu.com.cn/problem/CF1009F\"\
  \ target='_blank'>\u70B9\u51FB\u8DF3\u8F6C</a><p></details>"
permalink: LG CF1009F Dominant-Indices
tags:
- "\u957F\u94FE\u5256\u5206"
thumbnail: null
title: LG CF1009F Dominant-Indices
top: 0
---
长链剖分模板

长链剖分优化dp

设$f_{x,i}$表示$x$子树内与$x$距离为$i$的点的个数

$$
f_{x,i}= \sum f_{to,i-1}
\\\\
(f_{x,0}=1)
$$

可以发现$x$从它的儿子继承答案

这时就可以用长链剖分优化dp了(一种类似$\text{dsu on tree}$的方法)

设$len_x$为$x$到叶节点的最长距离

我们将$\max len_{to}$设为$x$的重儿子

$x$直接继承重儿子的答案,而不用重新再算一次

其他的儿子再按普通方式计算

因为每条链只会被合并一次,因此总复杂度就是$\Theta(n)$！


```cpp
#include<bits/stdc++.h>
#define il __inline__ __attribute__ ((always_inline))
#define Fur(i,x,y) for(int i(x);i<=y;++i)
#define fl(i,x) for(int i(head[x]),to;to=e[i].to,i;i=e[i].nxt)
using namespace std;
namespace IO{const int str=1<<20;static char in_buf[str],*in_s,*in_t;bool __=0;il char gc(){return (in_s==in_t)&&(in_t=(in_s=in_buf)+fread(in_buf,1,str,stdin)),in_s==in_t?EOF:*in_s++;}il void in(string &ch){ch.clear();if(__)return;char c;while((c=gc())!=EOF&&isspace(c));if(c==EOF){__=1;return;}ch+=c;while((c=gc())!=EOF&&!isspace(c))ch+=c;if(c==EOF)__=1;}il void in(char &ch){if(__)return;char c;while((c=gc())!=EOF&&isspace(c));if(c==EOF)__=1;else ch=c;}il void in(char *ch){*ch='\0';if(__)return;char c;while((c=gc())!=EOF&&isspace(c));if(c==EOF){__=1;return;}*ch=c;ch++;while((c=gc())!=EOF&&!isspace(c))*ch=c,ch++;if(c==EOF)__=1;*ch='\0';}template<typename T>il void in(T &x){if(__)return;char c=gc();bool f=0;while(c!=EOF&&(c<'0'||c>'9'))f^=(c=='-'),c=gc();if(c==EOF){__=1;return;}x=0;while(c!=EOF&&'0'<=c&&c<='9')x=x*10+c-48,c=gc();if(c==EOF)__=1;if(f)x=-x;}template<typename T,typename ... arr>il void in(T &x,arr & ... y){in(x),in(y...);}const char ln='\n';static char out_buf[str],*out_s=out_buf,*out_t=out_buf+str;il void flush(){fwrite(out_buf,1,out_s-out_buf,stdout);out_s=out_buf;}il void pt(char c){(out_s==out_t)?(fwrite(out_s=out_buf,1,str,stdout),*out_s++=c):(*out_s++=c);}il void out(const char* s){while(*s)pt(*s++);}il void out(char* s){while(*s)pt(*s++);}il void out(char c){pt(c);}il void out(string s){for(int i=0;s[i];i++)pt(s[i]);}template<typename T>il void out(T x){if(!x){pt('0');return;}if(x<0)pt('-'),x=-x;char a[50],t=0;while(x)a[t++]=x%10,x/= 10;while(t--)pt(a[t]+'0');}template<typename T,typename ... arr>il void out(T x,arr & ... y){out(x),out(y...);}}using namespace IO;
#define N 1000011
int n,cnt=0,head[N];
struct edge{
    int to,nxt;
}e[N<<1];
il void add(int x,int y){
    e[++cnt].to=y;e[cnt].nxt=head[x];head[x]=cnt;
}
int len[N],son[N],ans[N],tmp[N],*f[N],*id=tmp;
void dfs(int x,int fa){
    fl(i,x)if(to!=fa){
        dfs(to,x);
        if(len[to]>len[son[x]])son[x]=to;
    }
    len[x]=len[son[x]]+1;
}
void dp(int x,int fa){
    f[x][0]=1;
    if(son[x])f[son[x]]=f[x]+1,dp(son[x],x),ans[x]=ans[son[x]]+1;
    /*
    有重儿子

    len_x=len_{son_x}+1 , 所以把后面的空间直接开给son_x

    计算完重儿子x就可以直接继承了

    当然答案的深度+1

    */
    fl(i,x)if(to!=fa&&to!=son[x]){
        f[to]=id;id+=len[to];dp(to,x);
        //其他儿子暴力计算
        Fur(j,1,len[to]){
            f[x][j]+=f[to][j-1];
            if(j<ans[x]&&f[x][j]>=f[x][ans[x]]||(j>ans[x]&&f[x][j]>f[x][ans[x]]))ans[x]=j;
        }
    }
    if(f[x][ans[x]]==1)ans[x]=0;
}
int main(){
    in(n);
    int x,y;
    Fur(i,1,n-1){
        in(x,y);
        add(x,y),add(y,x);
    }
    dfs(1,0);
    f[1]=id;id+=len[1];//分配len_1的空间给1计算
    dp(1,0);
    Fur(i,1,n)out(ans[i],ln);
    flush();
}
```
