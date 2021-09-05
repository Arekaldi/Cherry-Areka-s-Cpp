/*枚举的对象：对角线*/
#include <bits/stdc++.h>
using namespace std;

int n, m, ans;
int vis[40 + 10];

void dfs(int k) //枚举对象，对角线编号，min = 2, max = n + m
{
    ans = max(ans, k - 2);
    if (k > n + m)
        return;
    for (int x = 1; x <= k - 1; x++) //按行（x）枚举
    {
        int y = k - x; // x + y = k (对对角线编号的定义)
        if (x < 1 || x > n || y < 1 || y > m)
            continue;                  //判断是否越界
        else if (vis[x - y + 20] == 1) //判断另一条对角线是否被占用
            continue;                  //标记另一条对角线已被占用
        vis[x - y + 20] = 1;
        dfs(k + 1);
        vis[x - y + 20] = 0;
    }
}

int main()
{
    cin >> n >> m;
    dfs(2); //从 2 到 n + m
    cout << ans << endl;
    return 0;
}