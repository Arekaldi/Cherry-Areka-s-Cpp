#include<bits/stdc++.h>
#define ll int
using namespace std;

inline ll read()
{
	ll x=0,f=1;
	char ch=getchar();
	while (!isdigit(ch)) {if (ch=='-') f=-1; ch=getchar();}
	while (isdigit(ch)) {x=x*10+ch-48; ch=getchar();}
	return x*f;
}

#define max MAX
inline ll MAX(ll a,ll b){return a>b?a:b;}
#define min MIN
inline ll MIN(ll a,ll b){return a<b?a:b;}

const ll inf=2049;
ll n,m;

/*
X 4 4
L 1 1 3 3 2
L 2 2 4 4 1
k 2 2 3 3

12
*/ 

struct tree_array_2
{
	
	ll tree[inf][inf];
	
	inline ll lowbit(ll x) {return x&(-x);}
	
	void add(int x,int y,int de)
	{
		for(register ll i=x;i<=n;i+=lowbit(i))
			for(register ll j=y;j<=m;j+=lowbit(j))
				tree[i][j]+=de;
	}
	
	inline ll ask(ll x,ll y)
	{
		ll ans=0;
		for(register ll i=x;i>=1;i-=lowbit(i))
			for(register ll j=y;j>=1;j-=lowbit(j))
			    ans+=tree[i][j];
		return ans;
	}
	
}a,ai,aj,aij;

inline ll ans1(ll x,ll y)
{
//	cout<<"I'm deduging."<<endl;
//	cout<<"a : "<<a.ask(x,y)*(x*y+x+y+1)<<endl;
//	cout<<"ai : "<<ai.ask(x,y)*(y+1)<<endl;
//	cout<<"aj : "<<aj.ask(x,y)*(x+1)<<endl;
//	cout<<"aij : "<<aij.ask(x,y)<<endl<<endl;
//	cout<<"ans is : "<<a.ask(x,y)*(x*y+x+y+1)-ai.ask(x,y)*(y+1)-aj.ask(x,y)*(x+1)+aij.ask(x,y)<<endl;
	return  a.ask(x,y)*(x*y+x+y+1)-
			ai.ask(x,y)*(y+1)-
			aj.ask(x,y)*(x+1)+
			aij.ask(x,y);
}

inline void add1(ll x,ll y,ll de)
{
	a.add(x,y,de);
	ai.add(x,y,de*x);
	aj.add(x,y,de*y);
	aij.add(x,y,de*x*y);
}

int main()
{
	char jb,opt;
	cin>>jb;
//	cout<<jb<<endl;
	n=read(); m=read();
	while(cin>>opt)
	{
		if(opt=='L')
		{
			ll x1,y1,x2,y2,de;
			x1=read(); y1=read(); x2=read(); y2=read(); de=read();
			add1(x1,y1,de);
			add1(x1,y2+1,-de);
			add1(x2+1,y1,-de);
			add1(x2+1,y2+1,de);//一维差分转二维 
		}
		else
		{
//二维前缀和 sum i j = sum i-1 j + sum i j-1 - sum i-1 j-1 + a i j 
			ll x1,y1,x2,y2;
			x1=read(); y1=read(); x2=read(); y2=read();
//			cout<<"My asking 's answer is : "<<endl;
//			cout<<ans1(x2,y2)<<" "<<ans1(x1-1,y2)<<" "<<ans1(x2,y1-1)<<" "<<ans1(x1-1,y1-1)<<endl;
			cout<<ans1(x2,y2)-ans1(x1-1,y2)-ans1(x2,y1-1)+ans1(x1-1,y1-1) << endl;
		}
	}
	return 0;
}