#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=105;
const ll Mod=20170408,M=2e7+5;
#define DEBUG 0

ll n,m,p;

ll tot,pri[M],vis[M];
ll cnt1[N],cnt2[N];
void Euler(){
	ll i,j,k;
	vis[1]=1;
	for(i=1;i<=m;i++){
		if(!vis[i])pri[++tot]=i;
		for(j=1;j<=tot&&i*pri[j]<=m;j++){
			vis[i*pri[j]]=1;
			if(i%pri[j]==0)break;
		}
	}
	for(i=1;i<=m;i++){
		cnt1[i%p]++;
		if(vis[i])cnt2[i%p]++;
	}
}

typedef long long Matrix[N][N];
Matrix st,tmp1,tmp2,ans;
Matrix src;
void MMul(Matrix A,Matrix B){
	memset(src,0,sizeof(src));
	for(int i=0;i<p;i++)
		for(int j=0;j<p;j++)
			for(int k=0;k<p;k++)
				src[i][j]=(src[i][j]+A[i][k]*B[k][j]%Mod)%Mod;
	memcpy(A,src,sizeof(src));
}
void Mksm(Matrix a,ll b){
	memset(ans,0,sizeof(ans));
	for(int i=0;i<p;i++)ans[i][i]=1;
	for(;b;b>>=1,MMul(a,a))
		if(b&1)MMul(ans,a);
}
ll Ans;
int main(){
	freopen("count.in","r",stdin);
	freopen("count.out","w",stdout);
	ll i,j,k;
	scanf("%lld%lld%lld",&n,&m,&p);
	Euler();
	for(i=0;i<p;i++)
		for(j=0;j<p;j++){
			tmp1[i][j]=cnt1[(j-i+p)%p];
			tmp2[i][j]=cnt2[(j-i+p)%p];
		}

	for(i=0;i<p;i++)st[0][i]=cnt1[i];
#if DEBUG
	for(i=0;i<p;i++)printf("%lld ",st[0][i]);
	puts("");puts("");
	for(i=0;i<p;i++,puts(""))
		for(j=0;j<p;j++)printf("%lld ",tmp1[i][j]);
#endif
	Mksm(tmp1,n-1);
	MMul(st,ans);
#if DEBUG
	printf("%lld\n",st[0][0]);
#endif
	Ans=st[0][0];
	
	memset(st,0,sizeof(st));
	for(i=0;i<p;i++)st[0][i]=cnt2[i];
#if DEBUG
	puts("");puts("");
	for(i=0;i<p;i++)printf("%lld ",st[0][i]);
	puts("");puts("");
	for(i=0;i<p;i++,puts(""))
		for(j=0;j<p;j++)printf("%lld ",tmp2[i][j]);
#endif
	Mksm(tmp2,n-1);
	MMul(st,ans);
#if DEBUG
	printf("%lld\n",st[0][0]);
#endif
	Ans=(Ans-st[0][0]+Mod)%Mod;
	printf("%lld",Ans);
}
