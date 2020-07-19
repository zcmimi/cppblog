#include<cstdio>
#define inf 0x3f3f3f3f
int MAX(int x,int y){return x>y?x:y;}
#define gc getchar
int gi(){int x=0,f=0;char c=gc();while(c<'0'||'9'<c){if(c=='-')f=!f;c=gc();}while('0'<=c&&c<='9'){x=x*10+c-48;c=gc();}return f?(-x):x;}
using namespace std;
#define N 1010
int D,S,q;
struct segy{
    #define Z int m=(l+r)>>1
    #define ls rt<<1
    #define rs rt<<1|1
    int mx[N*3],tag[N*3];
    void upd(int L,int R,int v,int l,int r,int rt){
        mx[rt]=MAX(mx[rt],v);
        if(L<=l&&r<=R){
            tag[rt]=MAX(tag[rt],v);
            return;
        }
        Z;
        if(L<=m)upd(L,R,v,l,m,ls);
        if(R>m)upd(L,R,v,m+1,r,rs);
    }
    int qm(int L,int R,int l,int r,int rt){
        if(L<=l&&r<=R)return MAX(mx[rt],tag[rt]);
        Z,ans=tag[rt];
        if(L<=m)ans=MAX(ans,qm(L,R,l,m,ls));
        if(R>m)ans=MAX(ans,qm(L,R,m+1,r,rs));
        return ans;
    }
}tag[N*3],mx[N*3];
void upd(int x,int y,int xx,int yy,int v,int l,int r,int rt){
    mx[rt].upd(y,yy,v,1,S,1);
    if(x<=l&&r<=xx){
        tag[rt].upd(y,yy,v,1,S,1);
        return;
    }
    Z;
    if(x<=m)upd(x,y,xx,yy,v,l,m,ls);
    if(xx>m)upd(x,y,xx,yy,v,m+1,r,rs);
}
int qm(int x,int y,int xx,int yy,int l,int r,int rt){
    if(x<=l&&r<=xx)return MAX(tag[rt].qm(y,yy,1,S,1),mx[rt].qm(y,yy,1,S,1));
    Z,ans=tag[rt].qm(y,yy,1,S,1);
    if(x<=m)ans=MAX(ans,qm(x,y,xx,yy,l,m,ls));
    if(xx>m)ans=MAX(ans,qm(x,y,xx,yy,m+1,r,rs));
    return ans;
}
int main(){
    D=gi()+1;S=gi()+1;q=gi();
    int c,k,v,x,y;
    while(q--){
        c=gi();k=gi();v=gi();x=gi()+1;y=gi()+1;
        upd(x,y,x+c-1,y+k-1,qm(x,y,x+c-1,y+k-1,1,D,1)+v,1,D,1);
    }
    printf("%d\n",qm(1,1,D,S,1,D,1));
}