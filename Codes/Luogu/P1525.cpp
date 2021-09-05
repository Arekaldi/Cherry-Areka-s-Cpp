#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int inf=1000003;

inline ll read()
{
    ll x=0,f=1;
    char ch=getchar();
    while (!isdigit(ch)) {if (ch=='-') f=-1; ch=getchar();}
    while (isdigit(ch)) {x=x*10+ch-48; ch=getchar();}
    return x*f;
}

#define max MAX
ll MAX(ll a,ll b){return a>b?a:b;}
#define min MIN
ll MIN(ll a,ll b){return a<b?a:b;}

ll ver[inf<<1],nxt[inf<<1],head[inf],edge[inf<<1],tot,col[inf];
ll n,m,l,r,mid,ans;

void add(ll x,ll y,ll z)
{
    ++tot;
    ver[tot]=y;
    nxt[tot]=head[x];
    head[x]=tot;
    edge[tot]=z;
}

/*
    就这个题啊
    它让 冲突 的  最大值 最小
    所以我们可以  二分  这个冲突值 
    题目里边说把罪犯分成两组
    必然要把  冲突值大  的罪犯分开
    所以把冲突值  > mid  的罪犯加进来 
    然后还是 染铯法 判断二分图 
    行的话就尽量去扩大值 
    不行就相反 
*/

/*
    当然你用 扩展域 或者 带权 并查集  AC 此题 
    我也没话说 qwq 
*/ 

bool dfs(ll x, int now){
    for(int i=head[now];i;i=nxt[i])
    {
        int y=ver[i];
        if(edge[y]>=x)
        {
            if(col[y]==0) {
                col[y] = ( col[x] == 1 ? 2 : 1 ) ; //相邻的点标记成相反的颜色 
                return dfs(x, y);
            }
            else if(col[now]==col[y]) return false;
        }
        else {
            col[y] = col[now];
            return dfs(x, y);
        }
    }
    return true;
}

int main()
{
    n=read(); m=read();
    l=0,r=0,mid;
    for(int i=1;i<=m;i++)
    {
        ll u,v,w;
        u=read(); v=read(); w=read();
        r=max(w,r);
        add(u,v,w);
        add(v,u,w);
    }
    cout << r << endl; 
    while(l<=r)
    {
        mid = ( ( l + r ) >> 1 ) ;
        memset(col, 0, sizeof(col));
        col[1] = 1;
        if(dfs(mid, 1)==true) r=mid-1,ans=mid;
        else l=mid+1;
    }
    cout<<ans<<endl;
    getchar();
    return 0;
}

/*
    in

    4 6
    1 4 2534
    2 3 3512
    1 2 28351
    1 3 6618
    2 4 1805
    3 4 12884

    out

    3512
*/