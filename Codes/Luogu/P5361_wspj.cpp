#include<bits/stdc++.h>
#define MAXN 120000
using namespace std;
int tot;
int head[MAXN],nxt[MAXN],to[MAXN];
int tmp[MAXN],du[MAXN],p[MAXN];
int n,m;
bool vis[MAXN];
vector<int> ans;
vector<int> ans_1;
void add(int u,int v)
{
     tot++;
     to[tot]=v;
     nxt[tot]=head[u];
     head[u]=tot;
}
bool check(int x)
{

}

void solve()
{

}
int main()
{
    int T;
    cin>>T;
    while(T--)
    {
//      memset(du,0,sizeof(du));
        solve();
        cout<<ans.size()<<" ";
        for(int i=0;i<ans.size();i++)
        {
            cout<<ans[i]<<" ";
        }
        cout<<endl;
        cout<<ans_1.size()<<" ";
        for(int i=0;i<ans_1.size();i++)
        {
            cout<<ans_1[i]<<" ";
        }
        cout<<endl;
    }
}