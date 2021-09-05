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

const int maxn = 1e5 + 1, Mod = 1e8 - 3;

int n, tot;
int t[maxn], d[maxn];

class Query {
	public:
		int a, b;
		inline bool operator < (const Query &g) const {
			return g.a > a;
		}
};
Query a[maxn], b[maxn];

inline void ad(int pos, int v) {
	while(pos <= n) {
		t[pos] += v;
		pos += (-pos) & pos;
	}
}

inline int sk(int pos) {
	int res = 0;
	while(pos) {
		res = (res + t[pos]) % Mod;
		pos -= (-pos) & pos;
	}
	return res % Mod;
}

signed main() {
	n = read();
	for(int i = 1; i <= n; ++i)
		a[i].a = read(), a[i].b = i;
	for(int i = 1; i <= n; ++i)
		b[i].a = read(), b[i].b = i;
		
	sort(a + 1, a + n + 1);
	sort(b + 1, b + n + 1);
	
	for(int i = 1; i <= n; ++i)
		d[a[i].b] = b[i].b;
	int res = 0;
	for(int i = n; i >= 1; --i) {
		res = (res + sk(d[i] - 1)) % Mod;
		ad(d[i], 1);
	}
	cout << res % Mod;
}
