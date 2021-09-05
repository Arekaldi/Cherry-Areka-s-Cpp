#include <iostream>
#include <stdio.h>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <cstdlib>
#define lowbit(x) ((x)&(-x))
#define Heriko return
#define Deltana 0
#define Romanno 1
#define S signed
#define LL long long
#define R register
#define I inline
#define CI const int
#define mst(a, b) memset(a, b, sizeof(a))
#define ON std::ios::sync_with_stdio(false);cin.tie(0)
using namespace std;

template<typename J>
I void fr(J &x)
{
    short f(1);
    char c=getchar();
    x=0;
    while(c<'0' or c>'9')
    {
        if(c=='-') f=-1;
        c=getchar();
    }
    while (c>='0' and c<='9') 
    {
        x=(x<<3)+(x<<1)+c-'0';
        c=getchar();
    }
    x*=f;
}

template<typename J>
I void fw(J x,bool k)
{
    if(x<0) putchar('-'),x=-x;
    static short stak[35];
    short top(0);
    do
    {
        stak[top++]=x%10;
        x/=10;
    }
    while(x);
    while(top) putchar(stak[--top]+'0');
    if(k) putchar('\n');
    else putchar(' ');
}

CI EXX=2e6+10,MXX=1e6+6,NXX=1e5+3,inf=0x7fffffff;

int n,c1[EXX],c2[EXX],P[NXX],solu[NXX],tot,spa;

bool vis[NXX];

I void Add(int x,int y,int g[])
{
    x+=MXX;
    while(x<=EXX) g[x]+=y,x +=lowbit(x);
    Heriko;
}

I int Query(int x,int g[])
{
    x+=MXX;
    int res(0);
    while(x) res+=g[x],x-=lowbit(x);
    Heriko res;
}

char s[20];

int x,y,z;

S main()
{
    // #define Areka
    #ifdef Areka
        freopen("P5482_1.in", "r", stdin);
        freopen("w.out", "w", stdout);
    #endif
    fr(n);
    while(n--)
    {
        cin>>s;
        if(s[0]=='A')
        {
            fr(x),fr(y),fr(z);
            if(!x)
            {
                if(y>z) ++spa,solu[++tot]=3;
                else solu[++tot]=0;
            }
            else if(x>0)
            {
                P[++tot]=floor((z*1.0-y)/x),solu[tot]=1;
                if(P[tot]>MXX) solu[tot]=0;
                else if(P[tot] < -MXX) ++spa,solu[tot]=3;
                else Add(P[tot],1,c1);
            }
            else if(x<0)
            {
                P[++tot]=ceil((z*1.0-y)/x),solu[tot]=2;
                if(P[tot] < -MXX) solu[tot]=0;
                else if(P[tot]>MXX) ++spa,solu[tot]=3;
                else Add(P[tot],1,c2);
            }
        }
        else if(s[0]=='D')
        {
            fr(x);
            if(vis[x]) continue;
            vis[x]=1;
            if(solu[x]==3) --spa;
            else if(solu[x]==1) Add(P[x],-1,c1);
            else if(solu[x]==2) Add(P[x],-1,c2);
        }
        else if(s[0]=='Q') fr(x),fw(Query(x-1,c1)+(Query(MXX,c2)-Query(x,c2))+spa,1);
    }
    Heriko Deltana;
}