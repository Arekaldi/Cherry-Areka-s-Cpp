#include <cstdlib>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include<random>
#include <map>
using namespace std;
const int inf = 0x3f3f3f3f;
typedef long long ll;
typedef vector<int>::iterator vit;
#define SWAP(x,y) x^=y^=x^=y
typedef pair<int,int> P;

const int maxn = 10000;
map<int,int> mp;
bool v[200005];
int tot, num, fa[maxn];

void dfs(int cur, int dep) // 随机生成树型数据的代码
{
    if (dep >= 6)
    {
        return;
    }
    if(cur >= 3)
        return;
    int chnum = rand()%1+3;
    for (int i = 1; i<=chnum; i++)
    {
        ++tot;
        fa[tot] = cur;      
        dfs(tot, dep+1);
    }
}

int main()
{
    freopen("data.in", "w", stdout);
    srand((int)(time(0)));

    int n,m;

    dfs(++tot, 1);
    n = tot;
    m = rand() % 5;
    printf("%d %d\n", n, m);
    for (int i = 1; i<=n; i++)
    {
        printf("%d ", rand() % 10);
    }
    puts("");
    for (int i = 2, a, v;i<=n; i++)
    {
        a = rand()%2;
        if (a)
        {
            v = rand()%10;
        }
        else
        {
            v = rand() % 10;
        }
        printf("%d %d %d\n", fa[i], a, v);
    }
    puts("");
    for (int i = 1; i<=m; i++)
    {
        printf("%d %d\n", rand() % 10, rand()%n+1);
    }
    fclose(stdout); 
    return 0;
}