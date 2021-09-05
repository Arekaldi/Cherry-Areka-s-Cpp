#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

const int maxn = 1e3 + 1;

int m, n, a[maxn], b[maxn], ss[maxn], res, sum;
bool hv[maxn], vis[maxn], flag;

inline void Dfs(int now, int rest) {
	if(rest < ss[now])
		return;
	if(now <= 0) {
		flag = true;
		return;
	}
	if(flag)
		return;
	for(int i = m; i >= 1; --i) {
		if(a[i] >= b[now]) {
			a[i] -= b[now];
			rest -= b[now];
			if(a[i] < b[1])
				rest -= a[i];
			Dfs(now - 1, rest);
			a[i] += b[now];
			rest += b[now];
			if(a[i] - b[now] < b[1])
				rest += a[i] - b[now];
		}
	}
}

inline bool check(int mid) {
	flag = false;
	Dfs(mid, sum);
	return flag;
}

signed main() {
	m = read();
	for(int i = 1; i <= m; ++i)
		a[i] = read(), sum += a[i];
	n = read();
	for(int i = 1; i <= n; ++i)
		b[i] = read();
	sort(b + 1, b + n + 1);
	for(int i = 1; i <= n; ++i)
		ss[i] = ss[i - 1] + b[i];
	
	int l = 0, r = n;
	while(l <= r) {
		int mid = (l + r) >> 1;
		if(check(mid))
			l = mid + 1, res = mid;
		else
			r = mid - 1;
	}
	
	cout << res << endl;
}
