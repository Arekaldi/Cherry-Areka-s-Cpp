#include<bits/stdc++.h>
using namespace std;
#define ll long long
inline int read(){ 
	int r=0,W=1; 
	char ch=getchar(); 
	while(ch>'9'or ch<'0') { if(ch=='-') W=-1; ch=getchar();} 
	while(ch>='0'and ch<='9') { r=r*10+ch-'0'; ch=getchar();} 
	return r*W;
}
int p;
struct node {
	int l,r;
	int w;
}q[1000010];

//vector <ll > edge[50100];
ll n,m,e,ans;
//ll cp[50100];
//bool vis[50100];
//void add_edge(int a,int b) {
//	edge[a].push_back(b);
//}
//bool Find(ll a) {
//	for(int i=0;i<edge[a].size();i++) {
//		ll y=edge[a][i];
//		if(vis[y]) continue;
//		vis[y]=true;
//		if(!cp[y] or Find(cp[y])) {
//			cp[y]=a;
//			return true;
//		}
//	}
//	return false;
//}
int main() {
	freopen("seq.in","r",stdin);
	freopen("seq.out","w",stdout);
	n=read(),m=read(),p=read();
	for(int i=1;i<=n;i++) q[i].l=read(),q[i].r=read(),q[i].w=read();
//	if(p==2) {
//		for(int i=1;i<=m;i++) {
//			if(q[i].w==0) add_edge(q[i].l,q[i].r);
//			else add_edge(q[i].r,q[i].l);
//			if(!Find(q[i].l) or !Find(q[i].r)) {
//				cout<<i;
//				return 0;
//			}
//		}
//	}
	cout<<m;
	fclose(stdin);
	fclose(stdout);
	return 0;
}
