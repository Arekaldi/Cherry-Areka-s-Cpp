#include<bits/stdc++.h>
#define mode 10007
using namespace std;
int n,a,b;
int w[2000001],ans,maxn,now;
int sons[4];
vector<int>road[2000001];
int main()
{
    scanf("%d",&n);
    for(int i=1;i<n;++i)
    {
        scanf("%d %d",&a,&b);
        road[a].push_back(b);
        road[b].push_back(a);
    }
    for(int i=1;i<=n;++i)
        scanf("%d",&w[i]);
    for(int i=1;i<=n;++i)
    {
        now=0;
        sons[1]=sons[2]=sons[3]=0;
        for(int j=0;j<road[i].size();++j)
        {
            sons[1]=w[road[i][j]];
            sort(sons+1,sons+1+3);
            ans-=w[road[i][j]]*w[road[i][j]];
            ans%=mode;
            now+=w[road[i][j]];
            now%=mode;
        }
        ans+=now*now;
        ans%=mode;
        maxn=max(maxn,sons[3]*sons[2]);
    }
    cout<<maxn<<" "<<(ans+mode)%mode;
    return 0;
}