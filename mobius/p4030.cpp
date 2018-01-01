#include<stdio.h>
#include<math.h>
#include<string.h>
#include<algorithm>
#include<vector>
using namespace std;
const int N=20005;

struct Query{
	int l,r,dx,id;
	bool operator < (const Query& a)const{return dx==a.dx?r<a.r:dx<a.dx;}
}Q[N];

int tot,p[N],vis[N],phi[N];
vector<int>G[N];
void Euler(){
	int i,j,k;
	phi[1]=1;
	for(i=2;i<=N-5;i++){
		if(!vis[i])p[++tot]=i,phi[i]=i-1;
		for(j=1;j<=tot&&i*p[j]<=N-5;j++){
			k=i*p[j];
			vis[k]=1;
			if(i%p[j])phi[k]=phi[i]*phi[p[j]];
			else{phi[k]=phi[i]*p[j];break;}
		}
	}
	for(i=1;i<=N-5;i++)
		for(j=i;j<=N-5;j+=i)
			G[j].push_back(i);
}
int T,n,m,a[N],Len;
int Now,cnt[N],Ans[N];
void Modify(int x,int k){
	for(int j,i=0;i<G[x].size();i++){
		j=G[x][i];
		Now-=cnt[j]*(cnt[j]-1)/2*phi[j];
		cnt[j]+=k;
		Now+=cnt[j]*(cnt[j]-1)/2*phi[j];
	}
}
void Init(){
	Now=0;
	memset(cnt,0,sizeof(cnt));
}
int main(){
	int i,j,k,l,r;
	scanf("%d",&T);
	Euler();
	for(k=1;k<=T;k++){
		Init();
		scanf("%d",&n);
		for(i=1;i<=n;i++)scanf("%d",&a[i]);
		Len=sqrt(n);
		scanf("%d",&m);
		for(i=1;i<=m;i++){
			scanf("%d%d",&Q[i].l,&Q[i].r);
			Q[i].dx=(Q[i].l-1)/Len+1;
			Q[i].id=i;
		}
		sort(Q+1,Q+1+m);
		for(i=1,l=r=1,Modify(a[1],1);i<=m;i++){
			while(r<Q[i].r)Modify(a[++r],1);
			while(r>Q[i].r)Modify(a[r--],-1);
			while(l>Q[i].l)Modify(a[--l],1);
			while(l<Q[i].l)Modify(a[l++],-1);
			Ans[Q[i].id]=Now;
		}
		printf("Case #%d:\n",k);
		for(i=1;i<=m;i++)printf("%d\n",Ans[i]);
	}
}