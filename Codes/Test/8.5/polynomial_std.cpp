#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <queue>
#include <iostream>
#include <bitset>
using namespace std;
#define N 100005
#define ll long long
#define mod 1000000007
struct node{int to,next;}e[N<<1];
int f[N][105][2][2],n,K,head[N],cnt,siz[N],g[105][2][2];
void add(int x,int y){e[cnt]=(node){y,head[x]};head[x]=cnt++;}
void dfs(int x,int from)
{
    f[x][1][1][0]=1;f[x][0][0][0]=1;siz[x]=1;
    for(int i=head[x];i!=-1;i=e[i].next)
    {
        int to1=e[i].to;
        if(to1!=from)
        {
            dfs(to1,x);int mx=min(siz[x],K),mt=min(siz[to1],K);
            for(int j=0;j<=mx;j++)for(int k=0;k<2;k++)for(int l=0;l<2;l++)g[j][k][l]=f[x][j][k][l],f[x][j][k][l]=0;
            for(int j=0;j<=mx;j++)
            for(int k=0;k<=mt&&j+k<=K;k++)
            {
                f[x][j+k][0][0]=(f[x][j+k][0][0]+(ll)g[j][0][0]*f[to1][k][0]
                [1])%mod;
                f[x][j+k][0][1]=(f[x][j+k][0][1]+(ll)g[j][0][1]*(f[to1][k][0]
                [1]+f[to1][k][1][1])
                +(ll)g[j][0][0]*f[to1][k][1][1])%mod;
                f[x][j+k][1][0]=(f[x][j+k][1][0]+(ll)g[j][1][0]*(f[to1][k][0]
                [0]+f[to1][k][0][1]))%mod;
                f[x][j+k][1][1]=(f[x][j+k][1][1]+(ll)g[j][1][1]*(f[to1][k][0]
                [0]+f[to1][k][0][1])+
                (ll)(g[j][1][0]+g[j][1][1])*(f[to1][k][1][0]+f[to1]
                [k][1][1]))%mod;
            }
            siz[x]+=siz[to1];
        }
    }
}
int main()
{
    scanf("%d%d",&n,&K);memset(head,-1,sizeof(head));
    for(int i=1,x,y;i<n;i++)scanf("%d%d",&x,&y),add(x,y),add(y,x);dfs(1,0);
    printf("%d\n",(f[1][K][0][1]+f[1][K][1][1])%mod);
}