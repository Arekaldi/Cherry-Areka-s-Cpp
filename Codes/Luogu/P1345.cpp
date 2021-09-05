#include<bits/stdc++.h>
using namespace std;
#define MAXN 10100000
#define INF 101010000 
#define ll long long
ll total=-1,head[200010],to[200010],nxt[200010],val[200010],cur[200010];
ll dis[200010];
ll n,m,s,f,d,t;
ll p;
ll read() {
    ll s=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9') {
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9') {
        s=s*10+ch-'0';
        ch=getchar();
    }
    return s*f;
}
void add_edge(int u,int v,int c) {
    to[++total]=v;
    val[total]=c;
    nxt[total]=head[u];
    head[u]=total;
    swap(u,v);
    to[++total]=v;
    val[total]=0;
    nxt[total]=head[u];
    head[u]=total;
}
queue <ll > q;
bool bfs(ll s,ll t) {
//	for(int i=1;i<=n + n;i++) dis[i]=-1;
	memset(dis, -1, sizeof(dis));
//	cout << dis[4] << endl;
	while(!q.empty()) q.pop();
	q.push(s);
	dis[s]=0;	
	while(!q.empty()) {
		ll now=q.front();
		q.pop();
		for(int e=head[now];e>-1;e=nxt[e]) {
			ll y=to[e];
			if(dis[y]==-1 and val[e]) { //δ�ֲ��ҺϷ� 
				dis[y]=dis[now]+1;
				q.push(y);
			}
		}
	}
	return dis[t]!=-1;
	
}
ll dfs(ll x,ll flow,ll t) {
	if(x==t) return flow;
	ll rest=flow;//rest Ϊÿ���ߵ�ʣ������,flow�Ǳ������������� flow-rest�Ƕ���һ�εĹ��� 
	for(int e=cur[x];e>-1 and rest;e=nxt[e]) {
		ll y=to[e],f=val[e];
		cur[x]=e;
		if(!f or dis[y]!=dis[x]+1) continue;
		ll k=dfs(y,min(rest,f),t);//kΪ������������� 
		val[e]-=k,val[e^1]+=k;//б�Գ� 
		rest-=k;//ʣ������-k 
		if(!k) dis[y]=-1;//����Ϊ0֮�����ٱ���(��֦) 
	}
	return flow-rest;//����-ʣ�µ�=���ι��� 
}
ll dinic(ll s,ll t) {
	ll ans=0,k;
	while(bfs(s,t)) {
		for(int i=1;i<=n + n;i++) cur[i]=head[i];
//		memcpy(cur,head,sizeof(head));
		k=dfs(s,INT_MAX,t);
//		cout << k << endl;
		ans+=k;
	}
	return ans;
}

int main() {
	n=read(),m=read(),s=read(),t=read();
	s=s+n;
	memset(head,-1,sizeof(head));
	for(int i=1;i<=n;i++) add_edge(i,i+n,1);
	for(int i=1;i<=m;i++) {
		ll u,v;
		u=read(),v=read();
		add_edge(u+n,v,INF);
		add_edge(v+n,u,INF);
	}
//	for(int i=1;i<=n;i++) add_edge(i+n*2,t,2);
	cout<<dinic(s,t);
	return 0;
}
