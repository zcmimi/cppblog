---
author: zc
avatar: null
categories:
- - 刷题记录
commnet: 1
date: 2020-01-18 22:40
html: '<details><summary>查看原题</summary><div id=''from''></div><p><button onclick="document.getElementById(''from'').innerHTML=''<iframe
  src=&quot;https://www.luogu.com.cn/problem/P1646&quot; width=100% height=800px style=&quot;border:
  none;&quot;><iframe>''" class=''mdui-btn mdui-btn-raised mdui-ripple''>点击加载</button><a
  class=''mdui-btn mdui-btn-raised mdui-ripple'' href="https://www.luogu.com.cn/problem/P1646"
  target=''_blank''>点击跳转</a><p></details>'
permalink: LG 1646 [国家集训队]happiness
tags:
- 网络流
- 最小割
thumbnail: null
title: LG 1646 [国家集训队]happiness
top: 0
---
总和减去最小割即为答案

最小割删掉的边就是要减去的值,这样就可以最小化要减去的值,即答案最大化

那我们如何构造这张图呢?

1. $ST \xrightarrow{\text{选文科的值}} (i,j) \xrightarrow{\text{选理科的值}}ED$
   
2. $ST \xrightarrow{\text{同时选文科的额外快乐}}new,new\rightarrow(i,j),new\rightarrow(i+1,j)$(其他同理)
   
3. $(i,j)\rightarrow new,(i+1,j)\rightarrow new,new \xrightarrow{\text{同时选理科的额外快乐}}ED$(其他同理)

每个点只能选择文科或理科,当某个点选择了文科,那么它向理科(ED)的边都应该要被断开。

它直接连向ED的边、它和别的点组合连向ED的边都要切断

这些边的权值就会从最终答案中减去

<svg width="701px" height="701px"><g><g><g><path d="M 366.42685126423726 297.01122406350703 L 69.59851319063789 367.32614574153" fill="none" stroke-width="2" stroke="black"></path><path d="M 366.42685126423726 297.01122406350703 L 69.59851319063789 367.32614574153" opacity="0" fill="none" stroke-width="30" stroke="black"></path><text font-size="15px" dy="0.35em" text-anchor="middle" style="user-select: none;" x="203.08299255371094" y="319.824951171875">inf</text><path stroke="black" fill="black" d="M -15 7.5 L 0 0 L -15 -7.5 Z" transform="translate (88.18415832519531 362.9234313964844) rotate(166.6733220082538)"></path></g><g><path d="M 366.42685126423726 297.01122406350703 L 662 359.99965163378397" fill="none" stroke-width="2" stroke="black"></path><path d="M 366.42685126423726 297.01122406350703 L 662 359.99965163378397" opacity="0" fill="none" stroke-width="30" stroke="black"></path><text font-size="15px" dy="0.35em" text-anchor="middle" style="user-select: none;" x="529.1431274414062" y="316.16168212890625">inf</text><path stroke="black" fill="black" d="M -15 7.5 L 0 0 L -15 -7.5 Z" transform="translate (643.3194580078125 356.01873779296875) rotate(12.029297457258082)"></path></g><g><path d="M 364.74554582466936 69.59851319063789 L 366.42685126423726 297.01122406350703" fill="none" stroke-width="2" stroke="black"></path><path d="M 364.74554582466936 69.59851319063789 L 366.42685126423726 297.01122406350703" opacity="0" fill="none" stroke-width="30" stroke="black"></path><text font-size="15px" dy="0.35em" text-anchor="middle" style="user-select: none;" x="408.093994140625" y="183.20348001051042">同时选文科</text><path stroke="black" fill="black" d="M -15 7.5 L 0 0 L -15 -7.5 Z" transform="translate (366.28564453125 277.9117431640625) rotate(89.57713222549252)"></path></g><g><path d="M 662 359.99965163378397 L 367.32129017837025 661.8540224083981" fill="none" stroke-width="2" stroke="black"></path><path d="M 662 359.99965163378397 L 367.32129017837025 661.8540224083981" opacity="0" fill="none" stroke-width="30" stroke="black"></path><text font-size="15px" dy="0.35em" text-anchor="middle" style="user-select: none;" x="487.15283203125" y="498.22804661328314">选理科</text><path stroke="black" fill="black" d="M -15 7.5 L 0 0 L -15 -7.5 Z" transform="translate (380.59375 648.2583618164062) rotate(134.3112058351374)"></path></g><g><path d="M 364.74554582466936 69.59851319063789 L 662 359.99965163378397" fill="none" stroke-width="2" stroke="black"></path><path d="M 364.74554582466936 69.59851319063789 L 662 359.99965163378397" opacity="0" fill="none" stroke-width="30" stroke="black"></path><text font-size="15px" dy="0.35em" text-anchor="middle" style="user-select: none;" x="540.880615234375" y="201.12721252441406">选文科</text><path stroke="black" fill="black" d="M -15 7.5 L 0 0 L -15 -7.5 Z" transform="translate (648.3377075195312 346.65234375) rotate(44.329078091112564)"></path></g><g><path d="M 366.16238212372537 450.0657305441708 L 367.32129017837025 661.8540224083981" fill="none" stroke-width="2" stroke="black"></path><path d="M 366.16238212372537 450.0657305441708 L 367.32129017837025 661.8540224083981" opacity="0" fill="none" stroke-width="30" stroke="black"></path><text font-size="15px" dy="0.35em" text-anchor="middle" style="user-select: none;" x="409.2496643066406" y="555.888781785965">同时选理科</text><path stroke="black" fill="black" d="M -15 7.5 L 0 0 L -15 -7.5 Z" transform="translate (367.2167663574219 642.7542724609375) rotate(89.68627984680484)"></path></g><g><path d="M 69.59851319063789 367.32614574153 L 366.16238212372537 450.0657305441708" fill="none" stroke-width="2" stroke="black"></path><path d="M 69.59851319063789 367.32614574153 L 366.16238212372537 450.0657305441708" opacity="0" fill="none" stroke-width="30" stroke="black"></path><text font-size="15px" dy="0.35em" text-anchor="middle" style="user-select: none;" x="232.81011962890625" y="396.3599853515625">inf</text><path stroke="black" fill="black" d="M -15 7.5 L 0 0 L -15 -7.5 Z" transform="translate (347.76495361328125 444.9329528808594) rotate(15.590839129065841)"></path></g><g><path d="M 662 359.99965163378397 L 366.16238212372537 450.0657305441708" fill="none" stroke-width="2" stroke="black"></path><path d="M 662 359.99965163378397 L 366.16238212372537 450.0657305441708" opacity="0" fill="none" stroke-width="30" stroke="black"></path><text font-size="15px" dy="0.35em" text-anchor="middle" style="user-select: none;" x="499.1436767578125" y="392.68896484375">inf</text><path stroke="black" fill="black" d="M -15 7.5 L 0 0 L -15 -7.5 Z" transform="translate (384.4343566894531 444.5029296875) rotate(163.06625459626565)"></path></g><g><path d="M 69.59851319063789 367.32614574153 L 367.32129017837025 661.8540224083981" fill="none" stroke-width="2" stroke="black"></path><path d="M 69.59851319063789 367.32614574153 L 367.32129017837025 661.8540224083981" opacity="0" fill="none" stroke-width="30" stroke="black"></path><text font-size="15px" dy="0.35em" text-anchor="middle" style="user-select: none;" x="245.96771240234375" y="501.582275390625">选理科</text><path stroke="black" fill="black" d="M -15 7.5 L 0 0 L -15 -7.5 Z" transform="translate (353.81396484375 648.4916381835938) rotate(44.691477026263726)"></path></g><g><path d="M 364.74554582466936 69.59851319063789 L 69.59851319063789 367.32614574153" fill="none" stroke-width="2" stroke="black"></path><path d="M 364.74554582466936 69.59851319063789 L 69.59851319063789 367.32614574153" opacity="0" fill="none" stroke-width="30" stroke="black"></path><text font-size="15px" dy="0.35em" text-anchor="middle" style="user-select: none;" x="189.6642303466797" y="204.90884896565618">选文科</text><path stroke="black" fill="black" d="M -15 7.5 L 0 0 L -15 -7.5 Z" transform="translate (82.97493743896484 353.832763671875) rotate(134.74968255229285)"></path></g></g><g><g fixed="false" style="cursor: pointer;"><circle stroke-width="5" fill="white" stroke="black" r="19" cx="364.74554582466936" cy="69.59851319063789"></circle><text font-size="14" dy=".35em" text-anchor="middle" stroke-width="1" fill="black" stroke="black" x="364.74554582466936" y="69.59851319063789" style="user-select: none;">ST</text></g><g fixed="false" style="cursor: pointer;"><circle stroke-width="5" fill="white" stroke="black" r="19" cx="69.59851319063789" cy="367.32614574153"></circle><text font-size="14" dy=".35em" text-anchor="middle" stroke-width="1" fill="black" stroke="black" x="69.59851319063789" y="367.32614574153" style="user-select: none;">(i,j)</text></g><g fixed="false" style="cursor: pointer;"><circle stroke-width="5" fill="white" stroke="black" r="19" cx="367.32129017837025" cy="661.8540224083981"></circle><text font-size="14" dy=".35em" text-anchor="middle" stroke-width="1" fill="black" stroke="black" x="367.32129017837025" y="661.8540224083981" style="user-select: none;">ED</text></g><g fixed="false" style="cursor: pointer;"><circle stroke-width="5" fill="white" stroke="black" r="19" cx="662" cy="359.99965163378397"></circle><text font-size="14" dy=".35em" text-anchor="middle" stroke-width="1" fill="black" stroke="black" x="662" y="359.99965163378397" style="user-select: none;">(i+1,j)</text></g><g fixed="false" style="cursor: pointer;"><circle stroke-width="5" fill="white" stroke="black" r="19" cx="366.42685126423726" cy="297.01122406350703"></circle><text font-size="14" dy=".35em" text-anchor="middle" stroke-width="1" fill="black" stroke="black" x="366.42685126423726" y="297.01122406350703" style="user-select: none;">new</text></g><g fixed="false" style="cursor: pointer;"><circle stroke-width="5" fill="white" stroke="black" r="19" cx="366.16238212372537" cy="450.0657305441708"></circle><text font-size="14" dy=".35em" text-anchor="middle" stroke-width="1" fill="black" stroke="black" x="366.16238212372537" y="450.0657305441708" style="user-select: none;">new'</text></g></g></g></svg>

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
    #define inf (1<<30)
    MB T ABS(T x){return x>0?x:-x;}
    MB T MAX(T x,T y){return x>y?x:y;}
    MB T MIN(T x,T y){return x<y?x:y;}
    MB T GCD(T x,T y){return y?GCD(y,x%y):x;}
    MB void SWAP(T &x,T &y){T t=x;x=y;y=t;}
}using namespace ZDY;using namespace std;
namespace IO{const int str=1<<20;static char in_buf[str],*in_s,*in_t;bool __=0;il char gc(){return (in_s==in_t)&&(in_t=(in_s=in_buf)+fread(in_buf,1,str,stdin)),in_s==in_t?__=1,EOF:*in_s++;}il void in(string &ch){ch.clear();if(__)return;char c;while((c=gc())!=EOF&&isspace(c));if(c==EOF){__=1;return;}ch+=c;while((c=gc())!=EOF&&!isspace(c))ch+=c;if(c==EOF)__=1;}il void in(char &ch){if(__)return;char c;while((c=gc())!=EOF&&isspace(c));if(c==EOF)__=1;else ch=c;}il void in(char *ch){*ch='\0';if(__)return;char c;while((c=gc())!=EOF&&isspace(c));if(c==EOF){__=1;return;}*ch=c;ch++;while((c=gc())!=EOF&&!isspace(c))*ch=c,ch++;if(c==EOF)__=1;*ch='\0';}template<typename T>il void in(T &x){if(__)return;char c=gc();bool f=0;while(c!=EOF&&(c<'0'||c>'9'))f^=(c=='-'),c=gc();if(c==EOF){__=1;return;}x=0;while(c!=EOF&&'0'<=c&&c<='9')x=x*10+c-48,c=gc();if(c==EOF)__=1;if(f)x=-x;}template<typename T,typename ... arr>il void in(T &x,arr & ... y){in(x),in(y...);}const char ln='\n';static char out_buf[str],*out_s=out_buf,*out_t=out_buf+str;il void flush(){fwrite(out_buf,1,out_s-out_buf,stdout);out_s=out_buf;}il void pt(char c){(out_s==out_t)?(fwrite(out_s=out_buf,1,str,stdout),*out_s++=c):(*out_s++=c);}il void out(const char* s){while(*s)pt(*s++);}il void out(char* s){while(*s)pt(*s++);}il void out(char c){pt(c);}il void out(string s){for(int i=0;s[i];i++)pt(s[i]);}template<typename T>il void out(T x){if(!x){pt('0');return;}if(x<0)pt('-'),x=-x;char a[50],t=0;while(x)a[t++]=x%10,x/= 10;while(t--)pt(a[t]+'0');}template<typename T,typename ... arr>il void out(T x,arr & ... y){out(x),out(y...);}}using namespace IO;
const int N=100011,M=5000011;
int n,m,cnt=1,head[N],ST,ED,d[N],q[N];
struct edge{
    int to,nxt,w;
}e[M];
#define fl(i,x) for(int i=head[x],to;to=e[i].to,i;i=e[i].nxt)
void add(int x,int y,int w){
    e[++cnt].to=y;e[cnt].nxt=head[x];head[x]=cnt;e[cnt].w=w;
    e[++cnt].to=x;e[cnt].nxt=head[y];head[y]=cnt;e[cnt].w=0;
}
bool bfs(){
    int h=0,t=1,x;
    memset(d,0,sizeof d);
    q[h]=ST;d[ST]=1;
    while(h<t){
        x=q[h++];
        if(x==ED)return 1;
        fl(i,x)if(!d[to]&&e[i].w)
            d[to]=d[x]+1,q[t++]=to;
    }
    return 0;
}
int dfs(int x,int mf){
    if(x==ED)return mf;
    int us=0,w;
    fl(i,x)if(e[i].w&&d[to]==d[x]+1){
        w=dfs(to,min(mf-us,e[i].w));
        e[i].w-=w;
        e[i^1].w+=w;
        us+=w;
        if(us==mf)return mf;
    }
    if(!us)d[x]=-1;
    return us;
}
int id(int x,int y){
    return (x-1)*m+y;
}
int main(){
    in(n,m);
    ST=0,ED=n*m+2*(n-1)*m+2*n*(m-1)+1;
    int ans=0,w,tt=n*m;
    //选文科ST→(i,j)
    Fur(i,1,n)Fur(j,1,m)
        in(w),ans+=w,
        add(ST,id(i,j),w);
    //选理科(i,j)→ED
    Fur(i,1,n)Fur(j,1,m)
        in(w),ans+=w,
        add(id(i,j),ED,w);
    //ST→new,new→(i,j),new→(i+1,j)
    Fur(i,1,n-1)Fur(j,1,m)
        in(w),ans+=w,
        add(ST,++tt,w),
        add(tt,id(i,j),inf),
        add(tt,id(i+1,j),inf);
    //(i,j)→new,(i+1,j)→new,new→ED
    Fur(i,1,n-1)Fur(j,1,m)
        in(w),ans+=w,
        add(++tt,ED,w),
        add(id(i,j),tt,inf),
        add(id(i+1,j),tt,inf);
    //ST→new,new→(i,j),new→(i,j+1)
    Fur(i,1,n)Fur(j,1,m-1)
        in(w),ans+=w,
        add(ST,++tt,w),
        add(tt,id(i,j),inf),
        add(tt,id(i,j+1),inf);
    //(i,j)→new,(i,j+1)→new,new→ED
    Fur(i,1,n)Fur(j,1,m-1)
        in(w),ans+=w,
        add(++tt,ED,w),
        add(id(i,j),tt,inf),
        add(id(i,j+1),tt,inf);
    
    while(bfs())ans-=dfs(ST,inf);
    printf("%d\n",ans);
}
```
