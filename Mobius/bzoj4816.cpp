#include<stdio.h>
#include<ctype.h>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000005,M=N-5;
const ll Mod=1000000007LL;

inline ll _R(){
	ll d=0;char t=getchar();
	while(!isdigit(t))t=getchar();
	for(;isdigit(t);t=getchar())d=(d<<3)+(d<<1)+t-'0';
	return d;
}

ll f[N],h[N],rev[N];
ll tot,p[N],mu[N];
bool vis[N];
ll ksm(ll a,ll b){
	ll ans=1;
	for(;b;b>>=1,a=a*a%Mod)
		if(b&1)ans=ans*a%Mod;
	return ans;
}
void Euler(){
	mu[1]=1;
	ll i,j,k;
	for(i=2;i<=M;i++){
		if(!vis[i])p[++tot]=i,mu[i]=-1;
		for(j=1;j<=tot&&i*p[j]<=M;j++){
			k=i*p[j];
			vis[k]=1;
			if(i%p[j])mu[k]=-mu[i];
			else {
				mu[k]=0;
				break;
			}
		}
	}
	f[1]=f[2]=1;
	for(i=3;i<=M;i++)f[i]=(f[i-1]+f[i-2])%Mod;
	for(i=1;i<=M;i++)rev[i]=ksm(f[i],Mod-2);
	for(i=0;i<=M;i++)h[i]=1;
	for(i=1;i<=M;i++)
		for(j=i;j<=M;j+=i){
			if(mu[j/i]==-1)h[j]=h[j]*rev[i]%Mod;
			else if(mu[j/i]==1)h[j]=h[j]*f[i]%Mod;
		}
	for(i=1;i<=M;i++)h[i]=h[i]*h[i-1]%Mod;
	for(i=0;i<=M;i++)rev[i]=ksm(h[i],Mod-2);
}

ll Q,n,m,ans;
int main(){
	freopen("product.in","r",stdin);
	freopen("product.out","w",stdout);
	ll i,j,k;
	Euler();
	scanf("%lld",&Q);
	while(Q--){
		scanf("%lld%lld",&n,&m);
		ans=1;
		for(i=1;i<=min(n,m);i=j+1){
			j=min(n/(n/i),m/(m/i));
			ans=ans*ksm(h[j]*rev[i-1]%Mod,(n/i)*(m/i))%Mod;
		}
		printf("%lld\n",ans);
	}
}
