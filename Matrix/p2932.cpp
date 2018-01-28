#include<stdio.h>
#include<algorithm>
using namespace std;
typedef unsigned int uint;
const int N=1005;

int n;
uint a[N][N],b[N][N],c[N][N],A,B,C,D;
int main(){
	register int i,j,k;
	scanf("%d",&n);
	scanf("%u%u%u%u%u",&a[1][1],&A,&B,&C,&D);
	for(j=2;j<=n;j++)a[1][j]=C*a[1][j-1]+D;
	for(i=2;i<=n;i++){
		a[i][1]=a[i-1][n]*A+B;
		for(j=2;j<=n;j++)a[i][j]=C*a[i][j-1]+D;
	}
	scanf("%u%u%u%u%u",&b[1][1],&A,&B,&C,&D);
	for(j=2;j<=n;j++)b[1][j]=C*b[1][j-1]+D;
	for(i=2;i<=n;i++){
		b[i][1]=b[i-1][n]*A+B;
		for(j=2;j<=n;j++)b[i][j]=C*b[i][j-1]+D;
	}
	for(i=1;i<=n;i++)
		for(j=1;j<=i;j++)swap(b[i][j],b[j][i]);
	for(i=1;i<=n;i++)
		for(j=1;j<=n;j++){
			uint &x=c[i][j],*t1=a[i]+1,*t2=b[j]+1;
			for(k=1;k<=n;k++,t1++,t2++)
				x+=(*t1)*(*t2);
		}
	uint ans=0;
	for(i=1;i<=n;i++)
		for(j=1;j<=n;j++)ans^=c[i][j];
	printf("%u",ans);
}
