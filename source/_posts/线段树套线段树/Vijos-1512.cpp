#include<cstdio>
#define gc getchar
int gi(){int x=0,f=0;char c=gc();while(c<'0'||'9'<c){if(c=='-')f=!f;c=gc();}while('0'<=c&&c<='9'){x=x*10+c-48;c=gc();}return f?(-x):x;}
using namespace std;
#define N 20971520
#define c1 (rt*4-2)
#define c2 (rt*4-1)
#define c3 (rt*4)
#define c4 (rt*4+1)
#define Z int mx=(x+xx)>>1,my=(y+yy)>>1
int s[N],n;
bool b[N];
#define ca x,y,mx,my
#define cb x,my+1,mx,yy
#define cc mx+1,y,xx,my
#define cd mx+1,my+1,xx,yy
#define pu s[rt]=s[c1]+s[c2]+s[c3]+s[c4]
void build(int rt,int x,int y,int xx,int yy){
    if(x>xx||y>yy){b[rt]=1;return;}
    if(x==xx&&y==yy)return;
    int mx=(x+xx)>>1,my=(y+yy)>>1;
    build(c1,ca);build(c2,cb);
    build(c3,cc);build(c4,cd);
}
void upd(int X,int Y,int v,int rt,int x,int y,int xx,int yy){
    if(b[rt])return;
    if(x==xx&&y==yy){s[rt]+=v;return;}
    Z;
    if(X<=mx&&Y<=my)upd(X,Y,v,c1,ca);
    if(X<=mx&&Y>my)upd(X,Y,v,c2,cb);
    if(X>mx&&Y<=my)upd(X,Y,v,c3,cc);
    if(X>mx&&Y>my)upd(X,Y,v,c4,cd);
    pu;
}
int qh(int X,int Y,int XX,int YY,int rt,int x,int y,int xx,int yy){
    if(b[rt])return 0;
    if(X<=x&&xx<=XX&&Y<=y&&yy<=YY)return s[rt];
    Z,ans=0;
    if(X<=mx&&Y<=my)ans+=qh(X,Y,XX,YY,c1,ca);
    if(X<=mx&&YY>my)ans+=qh(X,Y,XX,YY,c2,cb);
    if(XX>mx&&Y<=my)ans+=qh(X,Y,XX,YY,c3,cc);
    if(XX>mx&&YY>my)ans+=qh(X,Y,XX,YY,c4,cd);
    return ans;
}
int main(){
    n=gi();
    build(1,1,1,n,n);
    int p,x,y,xx,yy;
    while(1){
        p=gi();if(p==3)break;
		x=gi()+1;y=gi()+1;
        if(p==1)upd(x,y,gi(),1,1,1,n,n);
        if(p==2)xx=gi()+1,yy=gi()+1,printf("%d\n",qh(x,y,xx,yy,1,1,1,n,n));
    }
}