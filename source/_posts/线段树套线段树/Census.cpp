#include<cstdio>
#define inf 0x3f3f3f3f
int MAX(int x,int y){return x>y?x:y;}
int MIN(int x,int y){return x<y?x:y;}
#define gc getchar
int gi(){int x=0,f=0;char c=gc();while(c<'0'||'9'<c){if(c=='-')f=!f;c=gc();}while('0'<=c&&c<='9'){x=x*10+c-48;c=gc();}return f?(-x):x;}
using namespace std;
#define N 501
#define Z int m=(l+r)>>1
int a[N<<2][N<<2],b[N<<2][N<<2],n,q,ma,mi;
void pux(int xt,int yt){
    a[xt][yt]=MAX(a[xt<<1][yt],a[xt<<1|1][yt]);
    b[xt][yt]=MIN(b[xt<<1][yt],b[xt<<1|1][yt]);
}
void puy(int xt,int yt){
    a[xt][yt]=MAX(a[xt][yt<<1],a[xt][yt<<1|1]);
    b[xt][yt]=MIN(b[xt][yt<<1],b[xt][yt<<1|1]);
}
void by(int l,int r,int xt,int yt,int ff){
    if(l==r){
        if(ff)a[xt][yt]=b[xt][yt]=gi();
        else pux(xt,yt);
        return;
    }
    Z;
    by(l,m,xt,yt<<1,ff);
    by(m+1,r,xt,yt<<1|1,ff);
    puy(xt,yt);
}
void bx(int l,int r,int xt){
    if(l==r){
        by(1,n,xt,1,1);
        return;
    }
    Z;
    bx(l,m,xt<<1);
    bx(m+1,r,xt<<1|1);
    by(1,n,xt,1,0);
}
void updy(int L,int v,int l,int r,int xt,int yt,int ff){
    if(l==r){
        if(ff)a[xt][yt]=b[xt][yt]=v;
        else pux(xt,yt);
        return;
    }
    Z;
    if(L<=m)updy(L,v,l,m,xt,yt<<1,ff);
    else updy(L,v,m+1,r,xt,yt<<1|1,ff);
    puy(xt,yt);
}
void updx(int x,int y,int v,int l,int r,int xt){
    if(l==r){
        updy(y,v,1,n,xt,1,1);
        return;
    }
    Z;
    if(x<=m)updx(x,y,v,l,m,xt<<1);
    else updx(x,y,v,m+1,r,xt<<1|1);
    updy(y,v,1,n,xt,1,0);
}
void qhy(int L,int R,int l,int r,int xt,int yt){
    if(L<=l&&r<=R){
        mi=MIN(mi,b[xt][yt]);
        ma=MAX(ma,a[xt][yt]);
        return;
    }
    Z;
    if(L<=m)qhy(L,R,l,m,xt,yt<<1);
    if(R>m)qhy(L,R,m+1,r,xt,yt<<1|1);
}
void qhx(int x,int y,int xx,int yy,int l,int r,int xt){
    if(x<=l&&r<=xx){
        qhy(y,yy,1,n,xt,1);
        return;
    }
    Z;
    if(x<=m)qhx(x,y,xx,yy,l,m,xt<<1);
    if(xx>m)qhx(x,y,xx,yy,m+1,r,xt<<1|1);
}
int main(){
    n=gi();
    bx(1,n,1);
    q=gi();
    char p[2];
    int x,y,xx,yy;
    while(q--){
        scanf("%s",p);x=gi();y=gi();
        if(p[0]=='q')xx=gi(),yy=gi(),ma=-inf,mi=inf,qhx(x,y,xx,yy,1,n,1),printf("%d %d\n",ma,mi);
        else updx(x,y,gi(),1,n,1);
    }
}