#include<stdio.h>
#include<math.h>
#include<algorithm>
#include<complex>
using namespace std;
typedef double db;
typedef complex<db> cp;
const int N=350005;
const db pi=3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679;

cp fft_wi[N];
int fft_len;
void fft(cp A[],int ty){
    int i,j,k,m;
    cp f,g;
    for(i=0;i<fft_len;i++){
        for(j=0,k=i,m=1;m<fft_len;m<<=1,j=(j<<1)|(k&1),k>>=1);
        if(i<j)swap(A[i],A[j]);
    }
    fft_wi[0]=1;
    for(m=1;m<fft_len;m<<=1){
        f=exp(cp(0,ty*pi/m));
        for(i=1;i<m;i++)fft_wi[i]=fft_wi[i-1]*f;
        for(k=0;k<fft_len;k+=m<<1)
            for(i=k;i<k+m;i++){
                f=A[i],g=fft_wi[i-k]*A[i+m];
                A[i]=f+g,A[i+m]=f-g;
            }
    }
    if(ty==1)return;
    f=1.0/fft_len;
    for(i=0;i<fft_len;i++)A[i]*=f;
}

int n,m,a[N],b[N],c,Sum,Ans=1e9;
cp A[N],B[N];
int main(){
    int i,j,k;
    scanf("%d%d",&n,&m);
    for(i=0;i<n;i++)scanf("%d",&a[i]),c-=a[i];
    for(i=0;i<n;i++)scanf("%d",&b[i]),c+=b[i];
    c=round((db)c/n);
    for(i=0;i<n;i++)a[i]+=c;
    for(i=0;i<n;i++)Sum+=a[i]*a[i],A[i]=A[i+n]=a[i];
    for(i=0;i<n;i++)Sum+=b[i]*b[i],B[n-i-1]=b[i];
    for(fft_len=1;fft_len<n*3;fft_len<<=1);
    fft(A,1),fft(B,1);
    for(i=0;i<fft_len;i++)A[i]*=B[i];
    fft(A,-1);
    for(i=n-1;i<2*n-1;i++)Ans=min(Ans,Sum-2*(int)floor(A[i].real()+0.5));
    printf("%d\n",Ans);
}