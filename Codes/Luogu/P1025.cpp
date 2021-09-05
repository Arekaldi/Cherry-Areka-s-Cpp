#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

int n, k, ans;

void dfs(int max, int sum, int num) {
    if(sum >= n and num < k) return;
    if(sum < n and num == k) return;
    if(n - sum == 1 and num < k - 1) return;
    if(num == k and sum == n) {
        ans++;
        return;
    }
    for(int i = max; i <= n - sum; ++i)
        dfs(i, sum + i, num + 1);
}

signed main() {
    n = read(), k = read();
    dfs(1, 0, 0);
    cout << ans << endl;
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
