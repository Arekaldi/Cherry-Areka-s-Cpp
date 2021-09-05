#include <bits/stdc++.h>

using namespace std;

#define int long long

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

const int inv2 = 500000004, Mod = 1e9 + 7;

int n, k;

signed main() {
	int T = read();
	while(T--) {
	    n = read(), k = read();
	    int res1 = (n * (n + 1)) % Mod; res1 = (res1 * inv2) % Mod;
	    int res2 = (n * (n - 1)) % Mod; res2 = (res2 * inv2) % Mod;
	    int t = 1, nowt = 0, ans = 0;
		int mx = (k >> 1) + (k & 1);
		int nx = (res1 + res1 - mx + 1 + Mod) % Mod;
		int ny = (nx * mx) % Mod;
		int nz = (ny * inv2) % Mod;
		ans = (ans + nz) % Mod;
		mx = k >> 1;
		res1 = res2;
		nx = (res1 + res1 - mx + 1 + Mod) % Mod;
		ny = (nx * mx) % Mod;
		nz = (ny * inv2) % Mod;
		ans = (ans + nz) % Mod;
		printf("%lld\n", ans);
	}

    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
