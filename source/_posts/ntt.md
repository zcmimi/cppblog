---
date: 2020-02-27
tags: 
- 数论
- 高精度
- 算法
- ntt

categories:
  - [算法,数论]
  - [note]
---

NTT基本上跟FFT一样,就是把单位根换成了原根(原根和单位根一样具有FFT需要的特殊性质)

前置知识: 

1. [FFT](/posts/fft)
   
2. [原根](/posts/原根)

## 原根的性质

设$p$是质数,$g$为模$p$的原根,$n|(p-1)$,$g_n=g^{(p-1)/n}$

> 单位根:
> 
> $\omega_n^n=1,\omega_n^{n/2}=-1$

原根:

$g_n^n=g^{p-1}\equiv 1\mod p$

$g_n^{n/2}=g^{(p-1)/2}$

其中$\left(g^{(p-1)/2}\right)^2=1,g_n^{n/2}=\pm1$

由于$g$是原根,所以$g^{p-1}\neq g^{(p-1)/2}$,所以$g_n^{n/2}=-1$

> 单位根：$w_{dn}^{dk}=w_n^k$

原根:

$g_{dn}^{dk}=g^{dk(p-1)/(dn)}=g^{k(p-1)/n}=g_n^k$

> 单位根: $({w_n^k})^2=w_{n/2}^k$

原根: 

$(g_n^k)^2=g_n^{2k}=g_{n/2}^k$

$(g_n^{k+n/2})^2=g_n^{2k+n}\equiv g_n^{2k}=g_{n/2}^k$

FFT需要单位复数根该有的性质原根都有

## 实现

和FFT基本上一样

```cpp
#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define For(i,x,y) for(int i=x;i<=y;++i)
#define il __inline__ __attribute__ ((always_inline))
il int gi(){char c;int x=0,f=0;while((c=getchar())<'0'||'9'<c)f^=(c=='-');while('0'<=c&&c<='9')x*=10,x+=c-48,c=getchar();return f?-x:x;}
const int N=3000011,P=998244353,G=3,Gi=332748118;
int n,m,limit=1,l=0,r[N],a[N],b[N];
il int pw(int x,int p){
    int ans=1;
    while(p){
        if(p&1)ans=1ll*ans*x%P;
        x=1ll*x*x%P;p>>=1;
    }
    return ans;
}
il void ntt(int *A,int typ){
    For(i,0,limit-1)
        if(i<r[i])std::swap(A[i],A[r[i]]);
    for(int len=1;len<limit;len<<=1){
        int Wn=pw(~typ?G:Gi,(P-1)/(len<<1));
        //Gi指1/G在模P下的逆元,相当于pw(G,P-2)
        for(int i=0;i<limit;i+=(len<<1)){
            int w=1;
            For(k,0,len-1){//蝴蝶操作
                int t=1ll*w*A[i+k+len]%P;
                A[i+k+len]=(A[i+k]-t+P)%P;
                A[i+k]=(A[i+k]+t)%P;
                w=1ll*w*Wn%P;
            }
        }
    }
}
int main(){
    n=gi(),m=gi();
    For(i,0,n)a[i]=(gi()+P)%P;
    For(i,0,m)b[i]=(gi()+P)%P;
    while(limit<=n+m)limit<<=1,++l;
    For(i,0,limit-1)
        r[i]=(r[i>>1]>>1)|((i&1)<<(l-1));
    ntt(a,1);ntt(b,1);
    For(i,0,limit)a[i]=1ll*a[i]*b[i]%P;
    ntt(a,-1);
    int inv=pw(limit,P-2);//limit在模P下的逆元
    For(i,0,n+m)printf("%d ",1ll*a[i]*inv%P);
}
```

原根表:

| p         | r  | k  | g  |
| ----------- | ---- | ---- | ---- |
| 81788929    | 21   | 39   | 7    |
| 104857601   | 21   | 50   | 3    |
| 104857601   | 22   | 25   | 3    |
| 113246209   | 21   | 54   | 7    |
| 113246209   | 22   | 27   | 7    |
| 132120577   | 21   | 63   | 5    |
| 136314881   | 21   | 65   | 3    |
| 138412033   | 21   | 66   | 5    |
| 155189249   | 21   | 74   | 6    |
| 167772161   | 23   | 20   | 3    |
| 249561089   | 21   | 119  | 3    |
| 377487361   | 21   | 180  | 7    |
| 377487361   | 22   | 90   | 7    |
| 383778817   | 21   | 183  | 5    |
| 415236097   | 22   | 99   | 5    |
| 415236097   | 21   | 198  | 5    |
| 469762049   | 24   | 28   | 3    |
| 469762049   | 21   | 224  | 3    |
| 469762049   | 23   | 56   | 3    |
| 469762049   | 22   | 112  | 3    |
| 576716801   | 21   | 275  | 6    |
| 645922817   | 22   | 154  | 3    |
| 645922817   | 21   | 308  | 3    |
| 666894337   | 21   | 318  | 5    |
| 683671553   | 22   | 163  | 3    |
| 740294657   | 21   | 353  | 3    |
| 897581057   | 22   | 214  | 3    |
| 897581057   | 21   | 428  | 3    |
| 918552577   | 22   | 219  | 5    |
| 935329793   | 22   | 223  | 3    |
| 935329793   | 21   | 446  | 3    |
| 950009857   | 21   | 453  | 7    |
| 962592769   | 21   | 459  | 7    |
| 998244353   | 23   | 119  | 3    |
| 1004535809  | 21   | 479  | 3    |
| 1107296257  | 23   | 132  | 10   |
| 1107296257  | 24   | 66   | 10   |
| 1107296257  | 21   | 528  | 10   |
| 1138753537  | 21   | 543  | 5    |
| 1161822209  | 22   | 277  | 3    |
| 1161822209  | 21   | 554  | 3    |
| 1205862401  | 21   | 575  | 3    |
| 1212153857  | 22   | 289  | 3    |
| 1212153857  | 21   | 578  | 3    |
| 1214251009  | 21   | 579  | 7    |
| 1218445313  | 21   | 581  | 3    |
| 1224736769  | 22   | 292  | 3    |
| 1224736769  | 21   | 584  | 3    |
| 1281359873  | 21   | 611  | 3    |
| 1300234241  | 23   | 155  | 3    |
| 1300234241  | 21   | 620  | 3    |
| 1306525697  | 21   | 623  | 3    |
| 1327497217  | 21   | 633  | 5    |
| 1438646273  | 21   | 686  | 3    |
| 1484783617  | 21   | 708  | 5    |
| 1570766849  | 21   | 749  | 3    |
| 1709178881  | 21   | 815  | 3    |
| 1835008001  | 21   | 875  | 6    |
| 1866465281  | 22   | 445  | 3    |
| 1866465281  | 21   | 890  | 3    |
| 1893728257  | 21   | 903  | 5    |
| 1931476993  | 21   | 921  | 5    |
| 2088763393  | 22   | 498  | 5    |
| 2113929217  | 22   | 504  | 5    |
| 2113929217  | 25   | 63   | 5    |
| 2113929217  | 23   | 252  | 5    |
| 2130706433  | 22   | 508  | 3    |
| 2130706433  | 23   | 254  | 3    |
| 2281701377  | 27   | 17   | 3    |
| 2483027969  | 23   | 296  | 3    |
| 2483027969  | 25   | 74   | 3    |
| 2533359617  | 24   | 151  | 3    |
| 2533359617  | 23   | 302  | 3    |
| 2558525441  | 23   | 305  | 3    |
| 2671771649  | 22   | 637  | 3    |
| 2680160257  | 22   | 639  | 7    |
| 2717908993  | 22   | 648  | 5    |
| 2717908993  | 24   | 162  | 5    |
| 2722103297  | 22   | 649  | 3    |
| 2780823553  | 22   | 663  | 10   |
| 2885681153  | 24   | 172  | 3    |
| 2885681153  | 26   | 43   | 3    |
| 2910846977  | 22   | 694  | 3    |
| 2998927361  | 22   | 715  | 3    |
| 3112173569  | 22   | 742  | 2    |
| 3221225473  | 24   | 192  | 3    |
| 3221225473  | 25   | 96   | 3    |
| 3221225473  | 26   | 48   | 3    |
| 3238002689  | 22   | 772  | 2    |
| 3238002689  | 23   | 386  | 2    |
| 3313500161  | 22   | 790  | 2    |
| 3414163457  | 23   | 407  | 3    |
| 3435134977  | 22   | 819  | 2    |
| 3451912193  | 22   | 823  | 2    |
| 3489660929  | 23   | 416  | 2    |
| 3489660929  | 25   | 104  | 2    |
| 3489660929  | 22   | 832  | 2    |
| 3510632449  | 22   | 837  | 2    |
| 3577741313  | 22   | 853  | 2    |
| 3615490049  | 23   | 431  | 2    |
| 3615490049  | 22   | 862  | 2    |
| 3628072961  | 22   | 865  | 2    |
| 3665821697  | 23   | 437  | 2    |
| 3686793217  | 22   | 879  | 2    |
| 3749707777  | 23   | 447  | 2    |
| 3892314113  | 23   | 464  | 2    |
| 3892314113  | 25   | 116  | 2    |
| 3892314113  | 24   | 232  | 2    |
| 3892314113  | 22   | 928  | 2    |
| 3938451457  | 22   | 939  | 2    |
| 3942645761  | 23   | 470  | 2    |
| 3942645761  | 24   | 235  | 2    |
| 3942645761  | 22   | 940  | 2    |
| 4013948929  | 22   | 957  | 2    |
| 4194304001  | 24   | 250  | 2    |
| 4253024257  | 23   | 507  | 2    |
| 4630511617  | 26   | 69   | 2    |
| 4630511617  | 25   | 138  | 2    |
| 4882169857  | 24   | 291  | 2    |
| 4882169857  | 23   | 582  | 2    |
| 5158993921  | 23   | 615  | 2    |
| 5175771137  | 23   | 617  | 2    |
| 5251268609  | 23   | 626  | 2    |
| 5528092673  | 23   | 659  | 2    |
| 5536481281  | 24   | 330  | 2    |
| 5578424321  | 23   | 665  | 2    |
| 5788139521  | 24   | 345  | 2    |
| 5788139521  | 23   | 690  | 2    |
| 5838471169  | 25   | 174  | 2    |
| 5838471169  | 26   | 87   | 2    |
| 6014631937  | 23   | 717  | 2    |
| 6165626881  | 23   | 735  | 2    |
| 6333399041  | 23   | 755  | 2    |
| 6434062337  | 23   | 767  | 2    |
| 6534725633  | 23   | 779  | 2    |
| 6593445889  | 24   | 393  | 2    |
| 6660554753  | 23   | 794  | 2    |
| 6719275009  | 23   | 801  | 2    |
| 6811549697  | 25   | 203  | 2    |
| 6811549697  | 23   | 812  | 2    |
| 6996099073  | 23   | 834  | 2    |
| 6996099073  | 24   | 417  | 2    |
| 7096762369  | 24   | 423  | 2    |
| 7348420609  | 24   | 438  | 2    |
| 7348420609  | 25   | 219  | 2    |
| 7474249729  | 23   | 891  | 2    |
| 7566524417  | 23   | 902  | 2    |
| 7717519361  | 26   | 115  | 2    |
| 7717519361  | 25   | 230  | 2    |
| 7717519361  | 23   | 920  | 2    |
| 7818182657  | 23   | 932  | 2    |
| 7843348481  | 23   | 935  | 2    |
| 7918845953  | 27   | 59   | 2    |
| 8170504193  | 24   | 487  | 2    |
| 8220835841  | 25   | 245  | 2    |
| 8220835841  | 23   | 980  | 2    |
| 8279556097  | 23   | 987  | 2    |
| 8858370049  | 26   | 132  | 2    |
| 8858370049  | 27   | 66   | 2    |
| 9177137153  | 24   | 547  | 2    |
| 9227468801  | 25   | 275  | 2    |
| 9865003009  | 24   | 588  | 2    |
| 10267656193 | 24   | 612  | 2    |
| 10267656193 | 26   | 153  | 2    |
| 10267656193 | 25   | 306  | 2    |
| 10619977729 | 24   | 633  | 2    |
| 10871635969 | 26   | 162  | 2    |
| 10871635969 | 24   | 648  | 2    |
| 10871635969 | 25   | 324  | 2    |
| 11123294209 | 24   | 663  | 2    |
| 11173625857 | 25   | 333  | 2    |
| 11173625857 | 24   | 666  | 2    |
| 11341398017 | 26   | 169  | 2    |
| 11341398017 | 25   | 338  | 2    |
| 11693719553 | 24   | 697  | 2    |
| 12297699329 | 24   | 733  | 2    |
| 12348030977 | 27   | 92   | 2    |
| 12348030977 | 25   | 368  | 2    |
| 12348030977 | 26   | 184  | 2    |
| 13186891777 | 25   | 393  | 2    |
| 13757317121 | 26   | 205  | 2    |
| 13857980417 | 25   | 413  | 2    |
| 13857980417 | 24   | 826  | 2    |
| 14042529793 | 24   | 837  | 2    |
| 14092861441 | 26   | 210  | 2    |
| 14092861441 | 27   | 105  | 2    |
| 14092861441 | 24   | 840  | 2    |
| 15065939969 | 24   | 898  | 2    |
| 15065939969 | 25   | 449  | 2    |
| 15619588097 | 24   | 931  | 2    |
| 15653142529 | 24   | 933  | 2    |
| 15854469121 | 24   | 945  | 2    |
| 16475226113 | 24   | 982  | 2    |
| 16575889409 | 24   | 988  | 2    |
| 16626221057 | 24   | 991  | 2    |
| 17314086913 | 26   | 258  | 2    |
| 17314086913 | 25   | 516  | 2    |
| 17314086913 | 27   | 129  | 2    |
| 18387828737 | 26   | 274  | 2    |
| 19998441473 | 26   | 298  | 2    |
| 19998441473 | 25   | 596  | 2    |
| 20501757953 | 25   | 611  | 2    |