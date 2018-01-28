#include<stdio.h>
typedef long long ll;
const ll mod=1000000007;
ll n,m,f[2005][2005];
int main(){
	scanf("%lld%lld",&n,&m);
	f[0][0]=1;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			f[i][j]=(f[i-1][j-1]+f[i-1][j]*(i-1+j)%mod)%mod,
			printf("%d %d %lld\n",i,j,f[i][j]);
	printf("%lld",f[n][m]);
}
