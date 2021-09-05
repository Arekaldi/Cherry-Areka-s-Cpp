#include <bits/stdc++.h>

using namespace std;

inline int read() {
	register int x = 0, f = 1;
	register char ch;
	while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
	for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
	return x * f;
}

const int maxn = 26, Mod = 998244353;

int a[maxn], P[maxn];

signed main() {
    #define Areka
    #ifdef Areka
        freopen("puzzle.in", "r", stdin);
        freopen("puzzle.out", "w", stdout);
    #endif
	int T = read();
	while(T--) {
		int n = read();
		a[1] = read();
		int flag = false;
		for(int i = 2; i <= n; ++i) {
			a[i] = read();
			if(a[i] != a[i - 1] or a[i] % 2 != 0) {
				flag = 1;
				break;
			}
		}
		if(n == 1) {
			cout << 1 << " " << (int)sqrt(a[1]) % Mod << endl;
			continue;
		}
		if(n == 2) {
			double k = a[1] * 1.0 / 2;
			int f = sqrt(k);
			if(f * f * 2 < a[1]) {
				cout << 0 << endl;
				continue;
			}
			else {
				cout << 1 << " " << f % Mod << " " << f % Mod << endl;
				continue;
			}
		}
	}

	#ifndef ONLINE_JUDGE
		getchar();
	#endif
	return 0;
}
