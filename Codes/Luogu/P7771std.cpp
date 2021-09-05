#include<bits/stdc++.h>
using namespace std;
#define ll long long
namespace IO{//by cyffff
    inline int read() {
        int x;
        cin >> x;
        return x;
    }
    inline void write(int x) {
        cout << x;
    }
}
#define mpr make_pair
const int N=1e5+10;
int cnt,n,m,ind[N],oud[N],st[N];
vector<pair<int,int>>a[N];
bool vis[N<<1];
stack<int>ans;
inline void dfs(int x){
    for(int i=st[x];i<a[x].size();i=max(i+1,st[x])){
        int t=a[x][i].first;
        if(!vis[a[x][i].second]){
            vis[a[x][i].second]=1;
            st[x]=i+1;
            dfs(t);
        }
    }
    ans.push(x);
}
using namespace IO;
int main(){
    int s=0,t=0;
    n=read(),m=read();
    for(int i=1;i<=m;i++){
        int u=read(),v=read();
        oud[u]++,ind[v]++;
        a[u].push_back(mpr(v,i));
    }
    for(int i=1;i<=n;i++)
        if(ind[i]!=oud[i]){
            cnt++;
            if(ind[i]==oud[i]-1)
                s=i;
            if(ind[i]==oud[i]+1)
                t=i;
        }
    if(cnt!=0&&cnt!=2)
        return puts("No"),0;
    if(cnt==0)
        s=t=1;
    if(!s||!t)
        return puts("No"),0;
    for(int i=1;i<=n;i++)
        sort(a[i].begin(),a[i].end());
    dfs(s);
    while(!ans.empty()){
    	write(ans.top()),putchar(' ');
    	ans.pop();
	}
}