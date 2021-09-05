#include<map>
#include<queue>
#include<cmath>
#include<cstdio>
#include<string>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;
#define N 650000
#define int long long 
#define mod 1000000007
#define debug cout<<__LINE__<<" "<<__FUNCTION__<<"\n"

inline int read(){
	int x=0;
	char ch=getchar();
	while(ch<'0'||ch>'9'){ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
	return x;
}
void put(int x){
	if(x<0) putchar('-'),x=-x;
	if(x>=10) put(x/10);
	putchar((x%10)+48);
}
int n,sqr,prime[N],sum_f[N],sum_g[N],sum_h[N],tot;
bool ispri[N];
int m,w[N],id1[N],id2[N],g[N],h[N],s[N];
inline void pri(){
	for(int i=2;i<=sqr;i++){
		if(!ispri[i]){
			prime[++tot]=i;
			sum_f[tot]=(sum_f[tot-1]+(i*(i-1))%mod)%mod;
			sum_g[tot]=(sum_g[tot-1]+(i*i)%mod)%mod;
			sum_h[tot]=(sum_h[tot-1]+i)%mod;
		}
		for(int j=1;j<=tot&&i*prime[j]<=sqr;j++){
			ispri[i*prime[j]]=1;
			if(i%prime[j]==0) break;
		}
	}
}
inline int Id(int x){return x<=sqr?id1[x]:id2[n/x];}
inline int S(int x,int y){
	if(x<prime[y]) return 0;
	int ans=((g[Id(x)]-sum_f[y-1])%mod+mod)%mod; 
	if(y>tot||prime[y]*prime[y]>x) return ans;
	for(int i=y,res;i<=tot&&prime[i]*prime[i]<=x;i++){
		res=prime[i];
		for(int j=1;res*prime[i]<=x;j++){
			ans=(ans+((res*prime[i])%mod)*((res*prime[i]-1ll)%mod)%mod+(((res%mod)*((res-1)%mod)%mod)*S(x/res,i+1))%mod)%mod;
			res*=prime[i];
		}
	}
	return ans%mod;
}
signed main(){
// 	freopen(".in","r",stdin);
// 	freopen(".out","w",stdout);
	n=read();sqr=sqrt(n);
	pri();
	for(int i=1,j;i<=n;i=j+1){
		w[++m]=n/i;j=n/w[m];
		if(w[m]<=sqr) id1[w[m]]=m/*,cout<<"1: "<<w[m]<<" "<<m<<"\n"*/;
		else id2[j]=m/*,cout<<"2: "<<j<<" "<<m<<"\n"*/;
		g[m]=(((((w[m]*((((w[m]+1)%mod)*((2*w[m]+1)%mod))%mod))%mod)*166666668)%mod)+mod-1)%mod;
		h[m]=((((w[m]-1)%mod)*((w[m]+2)%mod))%mod*500000004)%mod; 
	}
	for(int i=1,lim;i<=tot;i++){
		lim=prime[i]*prime[i];
		for(int j=1;lim<=w[j];j++){
			g[j]=(g[j]-((prime[i]*prime[i])%mod)*((g[Id(w[j]/prime[i])]-sum_g[i-1])%mod))%mod;
			h[j]=(h[j]-(prime[i]*((h[Id(w[j]/prime[i])]-sum_h[i-1])%mod))%mod)%mod;
		}
	}
	for(int i=1;i<=m;i++){
		/*s[i]=*/g[i]=(g[i]-h[i]+mod)%mod;
	}
	cout<<(S(n,1)+1)%mod<<"\n";
//	fclose(stdin);
//	fclose(stdout);
    return 0;
}