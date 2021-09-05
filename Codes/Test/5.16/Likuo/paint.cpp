#include<bits/stdc++.h>
using namespace std;
const int ma=1e5+100;
int n,m,k;
struct rec{
	int l;
	int r;
	int up;
	int down;
}kp[ma]; 
int rest[ma];
int main(){
	freopen("paint.in","r",stdin);
	freopen("paint.out","w",stdout);
	cin>>n>>m>>k;
	short int mp[n+1][m+1];
	for(int i=1;i<=k;i++){
		kp[i].l=ma;
		kp[i].up=ma;
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++){
			scanf("%d",&mp[i][j]);
			kp[mp[i][j]].r=max(kp[mp[i][j]].r,j);
			kp[mp[i][j]].l=min(kp[mp[i][j]].l,j);
			kp[mp[i][j]].up=min(kp[mp[i][j]].up,i);
			kp[mp[i][j]].down=max(kp[mp[i][j]].down,i);
		}
	}
	for(int i=1;i<=k;i++){
		int u=kp[i].up;
		int d=kp[i].down;
		int le=kp[i].l;
		int ri=kp[i].r;
		for(int ii=u;ii<=d;ii++){
			for(int j=le;j<=ri;j++)
			{
				if(mp[ii][j]!=i) rest[mp[ii][j]]=1;
			}
		}
	}
	int ans=0;
	for(int i=1;i<=k;i++) if(!rest[i]) ans++;
	cout<<ans;
	
	return 0;
	fclose(stdin);
	fclose(stdout);
}
