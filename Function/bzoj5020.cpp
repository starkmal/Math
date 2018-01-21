#include<stdio.h>
#include<math.h>
#include<algorithm>
using namespace std;
typedef double db;
const int N=100005;
const db fact[15]={1,1,2,6,24,120,720,5040,40320,362880,3628800,39916800,479001600,6227020800};

struct Func{
	const static int ARGS=13;
	db arg[15];
	Func(){}
	Func(int ty,db a,db b){
		for(int i=0;i<=ARGS;i++)arg[i]=0.0;
		if(ty==1){
			db sn=sin(b),cs=cos(b),bs=1,sgn=1;
			for(int i=0;i<=ARGS;i++,bs*=a){
				arg[i]=sgn*bs*((i&1)?cs:sn)/fact[i];
				if(i&1)sgn*=-1.0;
			}
		}
		else if(ty==2){
			db eb=exp(b),bs=1;
			for(int i=0;i<=ARGS;i++,bs*=a)
				arg[i]=eb*bs/fact[i];
		}
		else if(ty==3)arg[0]=b,arg[1]=a;
	}
	db GetAns(db x){
		db ans=0.0;
		for(int i=ARGS;i>=0;i--)
			ans=ans*x+arg[i];
		return ans;
	}
	friend Func operator + (const Func& lhs,const Func& rhs){
		Func ans;
		for(int i=0;i<=ARGS;i++)ans.arg[i]=lhs.arg[i]+rhs.arg[i];
		return ans;
	}
};

Func Sum[N],Val[N];
int Son[N][2],Fa[N];
bool Rev[N];
inline bool isRoot(int x){
	return !Fa[x]||(Son[Fa[x]][0]!=x&&Son[Fa[x]][1]!=x);
}
inline void PushUp(int x){
	Sum[x]=Sum[Son[x][0]]+Sum[Son[x][1]]+Val[x];
}
inline int Setr(int x){
	Rev[x]^=1;
	swap(Son[x][0],Son[x][1]);
	return 0;
}
inline void PushDown(int x){
	if(Rev[x]){
		Son[x][0]?Setr(Son[x][0]):0;
		Son[x][1]?Setr(Son[x][1]):1;
		Rev[x]=0;
	}
}
inline void Rotate(int x){
	int y=Fa[x],z=Fa[y],l=Son[y][0]==x,r=l^1;
	if(!isRoot(y))Son[z][Son[z][1]==y]=x;Fa[x]=z;
	Son[y][r]=Son[x][l],Fa[Son[x][l]]=y,Son[x][l]=y,Fa[y]=x;
	PushUp(y),PushUp(x);
}
int s[N],top;
void Splay(int x){
	s[top=1]=x;
	for(int i=x;!isRoot(i);i=Fa[i])s[++top]=Fa[i];
	while(top)PushDown(s[top--]);
	while(!isRoot(x)){
		int y=Fa[x],z=Fa[y];
		if(!isRoot(y)){
			if(Son[y][0]==x^Son[z][0]==y)Rotate(x);
			else Rotate(y);
		}
		else Rotate(x);
	}
}
void Access(int x){
	for(int t=0;x;t=x,x=Fa[x]){
		Splay(x);
		Son[x][1]=t;
		PushUp(x);
	}
}
void MakeToRoot(int x){
	Access(x),Splay(x),Setr(x);
}
void Link(int x,int y){
	MakeToRoot(x);
	Fa[x]=y;
}
void Cut(int x,int y){
	MakeToRoot(x);
	Access(y),Splay(y);
	Son[y][0]=Fa[x]=0;
}
bool Bridge(int x,int y){
	Access(x),Splay(x);
	while(Son[x][0])x=Son[x][0];
	Access(y),Splay(y);
	while(Son[y][0])y=Son[y][0];
	return x==y;
}

int n,m;
char str[N];
int main(){
	int i,j,k,f,u,v;
	db x,y;
	scanf("%d%d%s",&n,&m,str);
	for(i=1;i<=n;i++){
		scanf("%d%lf%lf",&f,&x,&y);
		Sum[i]=Val[i]=Func(f,x,y);
	}
	for(i=1;i<=m;i++){
		scanf("%s",str);
		if(str[0]=='a')scanf("%d%d",&u,&v),Link(u+1,v+1);
		else if(str[0]=='d')scanf("%d%d",&u,&v),Cut(u+1,v+1);
		else if(str[0]=='m'){
			scanf("%d%d%lf%lf",&u,&f,&x,&y);
			u++;
			MakeToRoot(u);
			Val[u]=Func(f,x,y);
			PushUp(u);
		}
		else {
			scanf("%d%d%lf",&u,&v,&x);
			u++,v++;
			if(!Bridge(u,v))puts("unreachable");
			else{
				MakeToRoot(u),Access(v),Splay(v);
				printf("%.12lf\n",Sum[v].GetAns(x));
			}
		}
	}
}
