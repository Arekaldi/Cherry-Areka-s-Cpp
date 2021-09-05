#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

int t, x, a1, a2 = -1, n, m, ans;
string s;

signed main() {
    n = read(), m = read();
    for(int i = 1; i <= n; ++i) {
        cin >> s;
        x = read();
		if(s == "AND") a1 &= x, a2 &= x;
		if(s == "XOR") a1 ^= x, a2 ^= x;
		if(s == "OR") a1 |= x, a2 |= x;
    }

    for(int j = 30; j >= 0; --j) {
		if(a1 & (1 << j)) ans += 1 << j;
		else if((a2 & (1 << j)) and (1 << j) <= m)
            ans += 1 << j, m -= 1 << j;
    }
    
    printf("%d\n", ans);
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
