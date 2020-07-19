---
title: cdq分治 
date: 2020-03-20 20:36
author: 
avatar:
tags: 
 - 算法
 - 分治
 - 数据结构
 - 离线

categories:
 - [算法,离线]
 - [note]

thumbnail: 
top: 0 
comment: 1
---

## 二维偏序

先按 第一维 排序, 第二维 用数据结构维护

例题: [\[SHOI2007\]园丁的烦恼](https://www.luogu.com.cn/problem/P2163)

离线操作

先将每个询问拆成4个点查询

设$(1,1)$到$(x,y)$中点数为$s(x,y)$.

那么答案就为$s(c,d)-s(a-1,d)-s(c,b-1)+s(a-1,b-1)$

先将 点和询问 按$x$轴排序,点按顺序插入

$y$轴用树状数组维护,查询即可

```cpp
#include<bits/stdc++.h>
namespace FastIO{const char* ln="\n";struct Reader{char buf[1<<20],*s,*t;bool EOF_FLG;Reader():s(buf),t(buf),EOF_FLG(false) {};char gt() {return s==t&&((t=(s=buf)+fread(buf,1,1<<20,stdin))==s)?EOF:(*s++);}Reader& operator>>(char* str) {if(EOF_FLG)return *str=0,*this;while((*str=gt())!=' '&&*str!='\n'&&*str!=EOF)++str;if(*str==EOF)EOF_FLG=true;*str=0;return *this;}template<typename T>Reader&operator>>(T&x) {if(EOF_FLG)return *this;char c=0,d;while(c!=EOF&&(c<'0'||c>'9'))d=c,c=gt();if(c==EOF){EOF_FLG=true;return *this;}else x=0;while(c>='0'&&c<='9')x=(x<<3)+(x<<1)+c-'0',c=gt();if(d=='-')x=-x;return *this;}}in;struct Writer{char buf[1<<20],*s,*t;Writer():s(buf),t(buf+(1<<20)){}~Writer(){fwrite(buf,1,s-buf,stdout);}void pt(char c){(s==t)?(fwrite(s=buf,1,1<<20,stdout),*s++=c):(*s++=c);}template<typename T>Writer&operator<<(T x){if(!x)return pt('0'),*this;if(x<0)pt('-'),x=-x;char a[40],t=0;while(x)a[t++]=x%10,x/=10;while(t--)pt(a[t]+'0');return *this;}Writer&operator<<(const char*s) {while(*s)pt(*s++);return *this;}}out;}using namespace FastIO;
#define Fur(i,x,y) for(int i=x;i<=y;i++)
using namespace std;
#define N 500000
int n,q;
struct node{
    int x,y,id,opt;
}a[N+1],b[N*4+1];
int tr[N+1],ans[N+1];
void add(int x){while(x<=N)tr[x]++,x+=(x&-x);};
int get(int x){int s=0;while(x)s+=tr[x],x-=(x&-x);return s;}
bool cmp(node x,node y){
    if(x.x!=y.x)return x.x<y.x;
    return x.y<y.y;
}
int main(){
    in>>n>>q;
    int d=0,x,y,xx,yy;
    Fur(i,1,n)in>>x>>y,a[i].x=x+1,a[i].y=y+1;
    sort(a+1,a+n+1,cmp);
    Fur(i,1,q){
        in>>x>>y>>xx>>yy;
        x++;y++;xx++;yy++;
        b[++d].x=x-1,b[d].y=y-1,b[d].opt=1,b[d].id=i;
        b[++d].x=x-1,b[d].y=yy,b[d].opt=-1,b[d].id=i;
        b[++d].x=xx,b[d].y=y-1,b[d].opt=-1,b[d].id=i;
        b[++d].x=xx,b[d].y=yy,b[d].opt=1,b[d].id=i;
    }
    sort(b+1,b+d+1,cmp);
    int j=1;
    Fur(i,1,d){
        while(j<=n&&a[j].x<=b[i].x)add(a[j].y),j++;
        ans[b[i].id]+=get(b[i].y)*b[i].opt;
    }
    Fur(i,1,q)out<<ans[i]<<ln;
}
```

## 三维偏序

如果按第一维排序,第二、三维用高级数据结构维护,有点麻烦,而且空间时间复杂度高

在允许离线的条件下,**cdq分治**为上等选择

cdq分治有点类似 归并排序求逆序对 的思路

还是全部先按第一维排序

接着把数列拆成相等的两半

分别按第二维排序

处理出 前半部分 对 后半部分 的影响(结果)

这样第一维和第二维都确定的,有顺序的,我们只需要考虑第三维

还是用 简单的数据结构维护就可以了(如 树状数组 、 线段树)

例题: [LG 3810 【模板】三维偏序（陌上花开）](https://www.luogu.com.cn/problem/P3810)

```cpp
#include<bits/stdc++.h>
typedef long long ll;typedef double db;typedef unsigned long long ull;
namespace IN{const int str=1<<20;static char in_buf[str],*in_s,*in_t;bool __=0;inline char gc(){return (in_s==in_t)&&(in_t=(in_s=in_buf)+fread(in_buf,1,str,stdin)),in_s==in_t?EOF:*in_s++;}template<typename T>inline void in(T &x){if(__)return;char c=gc();bool f=0;while(c!=EOF&&(c<'0'||c>'9'))f^=(c=='-'),c=gc();if(c==EOF){__=1;return;}x=0;while(c!=EOF&&'0'<=c&&c<='9')x=x*10+c-48,c=gc();if(c==EOF)__=1;if(f)x=-x;}template<typename T,typename ... arr>inline void in(T &x,arr & ... y){in(x),in(y...);}}using namespace IN;
namespace OUT{const char ln='\n';const int str=1<<20;static char out_buf[str],*out_s=out_buf,*out_t=out_buf+str;inline void flush(){fwrite(out_buf,1,out_s-out_buf,stdout);out_s=out_buf;}inline void pt(char c){(out_s==out_t)?(fwrite(out_s=out_buf,1,str,stdout),*out_s++=c):(*out_s++=c);}template<typename T>inline void out(T x){if(!x){pt('0');return;}if(x<0)pt('-'),x=-x;char a[50],t=0;while(x)a[t++]=x%10,x/= 10;while(t--)pt(a[t]+'0');}template<typename T,typename ... arr>inline void out(T x,arr & ... y){out(x),out(y...);}}using namespace OUT;
const int N=100011;
using std::sort;
int d,n,k,s[N<<1],ans[N];
struct node{int x,y,z,ans,w;}b[N],a[N];
bool cmpx(node x,node y){
    if(x.x!=y.x)return x.x<y.x;
    if(x.y!=y.y)return x.y<y.y;
    return x.z<y.z;
}
bool cmpy(node x,node y){
    if(x.y!=y.y)return x.y<y.y;
    return x.z<y.z;
}
inline void add(int x,int v){
    for(int i=x;i<=k;i+=i&-i)
        s[i]+=v;
}
inline int ask(int x){
    int res=0;
    for(int i=x;i;i-=i&-i)
        res+=s[i];
    return res;
}
inline void cdq(int l,int r){
    if(l>=r)return;
    int m=(l+r)>>1,j=l;
    cdq(l,m);cdq(m+1,r);
    sort(a+l,a+m+1,cmpy);
    sort(a+m+1,a+r+1,cmpy);
    for(int i=m+1;i<=r;++i){
        for(;j<=m&&a[j].y<=a[i].y;++j)
            add(a[j].z,a[j].w);
        a[i].ans+=ask(a[i].z);
    }
    for(int i=l;i<=j-1;++i)
        add(a[i].z,-a[i].w);
}
int main(){
    in(d,k);
    for(int i=1;i<=d;++i)
        in(b[i].x,b[i].y,b[i].z);
    sort(b+1,b+d+1,cmpx);
    for(int i=1,c=1;i<=d;++i,++c)
    if(b[i].x!=b[i+1].x||b[i].y!=b[i+1].y||b[i].z!=b[i+1].z)
        a[++n]=b[i],a[n].w=c,c=0;
    cdq(1,n);
    for(int i=1;i<=n;++i)
        ans[a[i].ans+a[i].w]+=a[i].w;
    for(int i=1;i<=d;++i)
        out(ans[i]),pt('\n');
    flush();
}
```

[LG 3157 \[CQOI2011\]动态逆序对](https://www.luogu.com.cn/problem/P3157)

将问题转化为三维偏序

我们先找出对答案有贡献的点$(i,j)$满足的条件：

$time_i<time_j$

$val_i<val_j,pos_i>pos_j$或$val_i>val_j,pos_i<pos_j$

```cpp
#include<bits/stdc++.h>
namespace IN{const int str=1<<20;static char in_buf[str],*in_s,*in_t;bool __=0;inline char gc(){return (in_s==in_t)&&(in_t=(in_s=in_buf)+fread(in_buf,1,str,stdin)),in_s==in_t?EOF:*in_s++;}template<typename T>inline void in(T &x){if(__)return;char c=gc();bool f=0;while(c!=EOF&&(c<'0'||c>'9'))f^=(c=='-'),c=gc();if(c==EOF){__=1;return;}x=0;while(c!=EOF&&'0'<=c&&c<='9')x=x*10+c-48,c=gc();if(c==EOF)__=1;if(f)x=-x;}template<typename T,typename ... arr>inline void in(T &x,arr & ... y){in(x),in(y...);}}using namespace IN;
namespace OUT{const char ln='\n';const int str=1<<20;static char out_buf[str],*out_s=out_buf,*out_t=out_buf+str;inline void flush(){fwrite(out_buf,1,out_s-out_buf,stdout);out_s=out_buf;}inline void pt(char c){(out_s==out_t)?(fwrite(out_s=out_buf,1,str,stdout),*out_s++=c):(*out_s++=c);}inline void out(char c){pt(c);}template<typename T>inline void out(T x){if(!x){pt('0');return;}if(x<0)pt('-'),x=-x;char a[50],t=0;while(x)a[t++]=x%10,x/= 10;while(t--)pt(a[t]+'0');}template<typename T,typename ... arr>inline void out(T x,arr & ... y){out(x),out(y...);}}using namespace OUT;
const int N=100011,inf=2122219134;
int n,q,s[N],pos[N];
long long ans[50011];
void add(int x,int v){for(;x<=n;x+=x&-x)s[x]+=v;}
int ask(int x){int res=0;for(;x;x-=x&-x)res+=s[x];return res;}
struct node{
    int v,w,p,id;
    bool operator<(node t){return p<t.p;}
}b[N+50000],c[N+50000];
void cdq(int l,int r){
    if(l>=r)return;
    int m=(l+r)>>1,j=l;
    cdq(l,m);cdq(m+1,r);
    for(int i=m+1;i<=r;++i){
        for(;j<=m&&b[j].p<=b[i].p;++j)add(b[j].v,b[j].w);
        ans[b[i].id]+=b[i].w*(ask(n)-ask(b[i].v));// 统计在i之前的与i组成的逆序对个数
    }
    for(int i=l;i<j;++i)add(b[i].v,-b[i].w);
    j=m;
    for(int i=r;i>m;--i){
        for(;j>=l&&b[j].p>=b[i].p;--j)add(b[j].v,b[j].w);
        ans[b[i].id]+=b[i].w*ask(b[i].v-1);// 统计在i之后的与i组成的逆序对个数
    }
    for(int i=m;i>j;--i)add(b[i].v,-b[i].w);
    std::merge(b+l,b+m+1,b+m+1,b+r+1,c+l);//使用merge合并比排序更快(归并排序)
    for(int i=l;i<=r;++i)b[i]=c[i];
}
int main(){
    in(n,q);
    int x;
    for(int i=1;i<=n;++i)in(x),b[i]=node{x,1,pos[x]=i,0};
    for(int i=1;i<q;++i)in(x),b[n+i]=node{x,-1,pos[x],i};
    cdq(1,n+q-1);
    for(int i=1;i<q;++i)ans[i]+=ans[i-1];
    for(int i=0;i<q;++i)out(ans[i],ln);
    flush();
}
```