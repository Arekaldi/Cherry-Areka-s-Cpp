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

const int maxn = 1e4 + 1;

int f[10000001], t, m;
int w[maxn], v[maxn];

signed main() {
    t = read(), m = read();
	for(int i = 1; i <= m; ++i)
		w[i] = read(), v[i] = read();

	for(int i = 1; i <= m; ++i) {
		for(int j = w[i]; j <= t; ++j)
			f[j] = max(f[j], f[j - w[i]] + v[i]);
	}
    cout << f[t] << endl;
    
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
