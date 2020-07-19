#include<cstdio>
#include<cstring>
#define clr(x,y) memset(x,y,sizeof(x))
#define gc getchar
#define pc putchar
int gi(){int x=0,f=0;char c=gc();while(c<'0'||'9'<c){if(c=='-')f=!f;c=gc();}while('0'<=c&&c<='9'){x=x*10+c-48;c=gc();}return f?(-x):x;}
using namespace std;
#define N 1010
int n,q;
struct segy{
    #define Z int m=(l+r)>>1
    #define ls rt<<1
    #define rs rt<<1|1
    bool tag[N*3];
    void clean(){clr(tag,0);}
    void upd(int L,int R,int l,int r,int rt){
        if(L<=l&&r<=R){tag[rt]^=1;return;}
        Z;
        if(L<=m)upd(L,R,l,m,ls);
        if(R>m)upd(L,R,m+1,r,rs);
    }
    bool ask(int L,int l,int r,int rt,bool ad){
        ad^=tag[rt];
        if(l==r)return ad;
        Z;
        if(L<=m)return ask(L,l,m,ls,ad);
        else return ask(L,m+1,r,rs,ad);
    }
}tag[N*3];
void upd(int x,int y,int xx,int yy,int l,int r,int rt){
    if(x<=l&&r<=xx){tag[rt].upd(y,yy,1,n,1);return;}
    Z;
    if(x<=m)upd(x,y,xx,yy,l,m,ls);
    if(xx>m)upd(x,y,xx,yy,m+1,r,rs);
}
bool ask(int x,int y,int l,int r,int rt,int ad){
    ad^=tag[rt].ask(y,1,n,1,0);
    if(l==r)return ad;
    Z;
    if(x<=m)return ask(x,y,l,m,ls,ad);
    else return ask(x,y,m+1,r,rs,ad);
}
void clean(int l,int r,int rt){
    tag[rt].clean();
    if(l==r)return;
    Z;clean(l,m,ls);clean(m+1,r,rs);
}
int main(){
int T=gi();
while(T--){
    n=gi();q=gi();
    clean(1,n,1);
    char p[2];int x,y,xx,yy;
    while(q--){
        scanf("%s",p);x=gi();y=gi();
        if(p[0]=='Q')pc(ask(x,y,1,n,1,0)+48),pc('\n');
        else xx=gi(),yy=gi(),upd(x,y,xx,yy,1,n,1);
    }
    pc('\n');
}
}