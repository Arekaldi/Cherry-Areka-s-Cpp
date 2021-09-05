#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

int n, res, x;
priority_queue <int> q;

signed main() {
    n = read();
    for(int i = 1; i <= n; ++i)
        q.push(-(x = read()));
    while(q.size() > 1) {
        int h = q.top(); q.pop();
        h += q.top(), q.pop();
        res -= h; q.push(h);
    }
    cout << res;
    
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
