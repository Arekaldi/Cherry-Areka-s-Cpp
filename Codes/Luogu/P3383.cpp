#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

const int maxn = 1e8 + 1;

bool isp[maxn];
int n, tot, pri[4000000];

signed main() {
	n = read();
	memset(isp, true, sizeof(isp));
	isp[1] = false;
	for(int i = 1; i <= n; ++i) {
		if(isp[i]) {
			pri[++tot] = i;
		}
		for(int j = 1; j <= tot and i * pri[j] <= n; ++j) {
			isp[i * pri[j]] = false;
			if(i % pri[j] == 0)
				break;
		}
	}
	int q = read();
	for(int x, i = 1; i <= q; ++i)
		cout << pri[x = read()] << endl;
}
