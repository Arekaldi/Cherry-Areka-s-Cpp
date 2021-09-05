#include <bits/stdc++.h>

using namespace std;

#define maxn 100050
#define int long long
#define lp p << 1
#define rp p << 1 | 1

inline int read() {
	int x = 0, f = 1;
	char ch = getchar();
	while(ch < '0' or ch > '9') {
		if(ch == '-') f = -1;
		ch = getchar();
	}
	while(ch >= '0' and ch <= '9') {
		x = (x << 1) + (x << 3) + (ch ^ 48);
		ch = getchar();
	}
	return x * f;
}

struct X_TrEE {
	int l, r, sum, add1, add2;
}T[maxn * 4];

int n, m, mod, a[maxn + 1];

void Build(int p, int x, int y) {
	T[p].l = x, T[p].r = y;
	T[p].add2 = 1;
	if(x == y) {
		T[p].sum = a[x] % mod;
	}
	else {
		int mid = (x + y) >> 1;
		Build(lp, x, mid);
		Build(rp, mid + 1, y);
		T[p].sum = (T[lp].sum + T[rp].sum) % mod;
	}
}

void Spread(int p) {
	T[lp].sum = ((T[lp].sum * T[p].add2) + (T[p].add1 * (T[lp].r - T[lp].l + 1))) % mod;
	T[rp].sum = ((T[rp].sum * T[p].add2) + (T[p].add1 * (T[rp].r - T[rp].l + 1))) % mod;
	
	T[lp].add2 = (T[lp].add2 * T[p].add2) % mod;
	T[rp].add2 = (T[rp].add2 * T[p].add2) % mod;
	
	T[lp].add1 = (T[lp].add1 * T[p].add2 + T[p].add1) % mod;
	T[rp].add1 = (T[rp].add1 * T[p].add2 + T[p].add1) % mod;
	
	T[p].add1 = 0, T[p].add2 = 1;
}

void Change_F(int p, int x, int y, int d) {
	if(x <= T[p].l and y >= T[p].r) {
		T[p].add1 = (T[p].add1 * d) % mod;
		T[p].add2 = (T[p].add2 * d) % mod;
		T[p].sum = (T[p].sum * d) % mod;
		return;
	}
	Spread(p);
	int mid = (T[p].l + T[p].r) >> 1;
	if(x <= mid) Change_F(lp, x, y, d);
	if(y > mid) Change_F(rp, x, y, d);
	T[p].sum = (T[lp].sum + T[rp].sum) % mod;
}

void Change_W(int p, int x, int y, int d) {
	if(x <= T[p].l and y >= T[p].r) {
		T[p].sum = (T[p].sum + d * (T[p].r - T[p].l + 1)) % mod;
		T[p].add1 = (T[p].add1 + d) % mod;
		return;
	}
	Spread(p);
	int mid = (T[p].l + T[p].r) >> 1;
	if(x <= mid) Change_W(lp, x, y, d);
	if(y > mid) Change_W(rp, x, y, d);
	T[p].sum = (T[lp].sum + T[rp].sum) % mod;
}

int ask(int p, int x, int y) {
	if(T[p].l >= x and T[p].r <= y) {
		return T[p].sum % mod;
	}
	Spread(p);
	int mid = (T[p].l + T[p].r) >> 1;
	int ans = 0;
	if(x <= mid)  ans = (ans + ask(lp, x, y)) % mod;
	if(y > mid) ans = (ans + ask(rp, x, y)) % mod;
	return ans;
}

signed main() {
	n = read();;
	mod = read();
	int sum = 0;
	for(int i = 1; i <= n; ++i) {
		a[i] = read();
		sum += a[i];
	}
    m = read();
	Build(1, 1, n);
	for(int i = 1; i <= m; ++i) {
		int u = read(), v = read(), w = read();
		if(u == 1) {
			int k = read();
			Change_F(1, v, w ,k);
		}
		if(u == 2) {
			int k = read();
			Change_W(1, v, w, k);
		}
		if(u == 3) {
			printf("%lld\n", ask(1, v, w));
		}
	}
}