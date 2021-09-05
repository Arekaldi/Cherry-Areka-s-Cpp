#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

const int maxn = 5e6 + 1;

int n;

int ans[11], tot, cnt;
int O[maxn];

inline void Dfs(int Dpt, int sum) {
    if(Dpt > 11)
        return;
    if(sum >= n and Dpt < 11)
        return;
    if(3 * (11 - Dpt) + sum < n)
        return;
    if(Dpt == 11 and sum == n) {
        for(int i = 1; i <= 10; ++i) 
            O[++cnt] = ans[i];
        return;
    }

    for(int i = 1; i <= 3; ++i) {
        ans[Dpt] = i;
        Dfs(Dpt + 1, sum + ans[Dpt]);
        ans[Dpt] = 0;
    }

    return;
}

signed main() {
    n = read();
    
    Dfs(1, 0);

    cout << cnt / 10 << endl;

    for(int i = 1; i <= cnt; ++i) {
        cout << O[i] << " ";
        if(i % 10 == 0)
            puts("");
    }
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
