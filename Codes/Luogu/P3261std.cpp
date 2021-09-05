#include<bits/stdc++.h>
#define int long long 
using namespace std;
int n,m;
int h[1000001];
int opt[1000001],v[1000001];
int killd[1000001],dead[1000001];
struct node{
	int ls,rs,dis,rt;
	int lazy_ad,lazy_ch;
	pair<int,int>val;
}t[1000001];
int rts[1000001];
void push_down(int x)
{
	t[x].val=make_pair(t[x].val.first*t[x].lazy_ch+t[x].lazy_ad,t[x].val.second);
	if(t[x].ls)
	{
		t[t[x].ls].lazy_ad*=t[x].lazy_ch;
		t[t[x].ls].lazy_ch*=t[x].lazy_ch;
		t[t[x].ls].lazy_ad+=t[x].lazy_ad;
	}
	if(t[x].rs)
	{
		t[t[x].rs].lazy_ad*=t[x].lazy_ch;
		t[t[x].rs].lazy_ch*=t[x].lazy_ch;
		t[t[x].rs].lazy_ad+=t[x].lazy_ad;
	}
	t[x].lazy_ad=0;
	t[x].lazy_ch=1;
}
int merge(int x,int y)
{
	if(!x||!y)return x+y;
	push_down(x);
	push_down(y);
	if(t[x].val>t[y].val)swap(x,y);
	t[x].rs=merge(t[x].rs,y);
	if(t[t[x].ls].dis<t[t[x].rs].dis)
		swap(t[x].ls,t[x].rs);
	t[x].rt=t[t[x].ls].rt=t[t[x].rs].rt=x;
	t[x].dis=t[t[x].rs].dis+1;
	return x;
}
int pop(int x)
{
	return t[x].rt=t[t[x].rs].rt=t[t[x].ls].rt=merge(t[x].ls,t[x].rs);
}
int find_(int x)
{
	return t[x].rt= t[x].rt==x?x:find_(t[x].rt);
}
int dep[1000001];
int s[1000001],c[1000001],tot;
vector<int>road[1000001];
void dfs(int x)
{
	for(int i=0;i<road[x].size();++i)
	{
		dep[road[x][i]]=dep[x]+1;
		dfs(road[x][i]);
		rts[x]=merge(rts[x],rts[road[x][i]]);
	}
	push_down(rts[x]);
	while(rts[x]&&t[rts[x]].val.first<h[x])
	{
		int no=t[rts[x]].val.second;
	//	cout<<t[rts[x]].val.first<<" asfaf"<<x<<"  "<<no<<" "<<dep[x]<<endl;
		rts[x]=pop(rts[x]);
		killd[x]++;
		dead[no]-=dep[x];
		push_down(rts[x]);
	}
	if(rts[x])
	{
	//	cout<<x<<" fsdfdsghhfrghgrhhg"<<s[x]<<" "<<v[x]<<endl;
		if(opt[x]==0)
			t[rts[x]].lazy_ad+=v[x];
		else
		{
			t[rts[x]].lazy_ad*=v[x];
			t[rts[x]].lazy_ch*=v[x];
		}
	}
}
int make(int v,int poi)
{
	++tot;
	t[tot].val=make_pair(v,poi);
	t[tot].rt=tot;
	t[tot].dis=1;
	t[tot].lazy_ch=1;
	return tot;
}
signed main()
{
    #define Areka
    #ifdef Areka
        freopen("data.in", "r", stdin);
        freopen("a.out", "w", stdout);
    #endif
	scanf("%lld %lld",&n,&m);
	for(int i=1;i<=n;++i)
		scanf("%lld",&h[i]);
	for(int i=2,in;i<=n;++i)
	{
		scanf("%lld %lld %lld",&in,&opt[i],&v[i]);
		road[in].push_back(i);
	}
	for(int i=1;i<=m;++i)
	{
		scanf("%lld %lld",&s[i],&c[i]);
		rts[c[i]]=merge(rts[c[i]],make(s[i],i));
	}
	dep[1]=1;
	dfs(1);
	for(int i=1;i<=n;++i)
		cout<<killd[i]<<endl;
	for(int i=1;i<=m;++i)
		cout<<dead[i]+dep[c[i]]<<endl;
}