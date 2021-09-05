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

const int maxn = 5e5 + 1;

int n;
int t[maxn];
int a[maxn], b[maxn], c[maxn];

inline void ad(int pos, int v) {
	while(pos <= n) {
		t[pos] += v;
		pos += (-pos) & pos;
	}
}

inline int sk(int pos) {
	int res = 0;
	while(pos) {
		res += t[pos];
		pos -= (-pos) & pos;
	}
	return res;
}

signed main() {
	n = read();
	for(int i = 1; i <= n; ++i)
		a[i] = read(), b[i] = a[i];
	sort(b + 1, b + n + 1);
	int nn = unique(b + 1, b + n + 1) - b - 1;
	for(int i = 1; i <= n; ++i)
		a[i] = lower_bound(b + 1, b + nn + 1, a[i]) - b;
	int res = 0;
	for(int i = n; i >= 1; --i) {
		res += sk(a[i] - 1);
		ad(a[i], 1);
	}
	cout << res;
}
