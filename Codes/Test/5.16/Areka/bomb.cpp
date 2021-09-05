#include <bits/stdc++.h>

using namespace std;

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

const int maxn = 1e6 + 5;

int n;
int dis[maxn];
double Ml[maxn], Mr[maxn];

inline double E2(int x) {
	double e1 = x * 1.0, e2 = (3.0 / 2.0);
	double e = ceil(e1 * e2);
	return e;
}

inline int E(double x) {
	return (int)ceil(x);
}

int ans = (1 << 30);

deque <int> Q;

signed main() {
	freopen("bomb.in", "r", stdin);
	freopen("bomb.out", "w", stdout);
	
	n = read();
	
	for(int i = 1; i <= n; ++i)
		dis[i] = read(), Ml[i] = Mr[i] = (1 << 30);
	sort(dis + 1, dis + n + 1);
	
	int j = 1;
	Ml[1] = 0, Mr[n] = 0;
	for(int i = 2; i <= n; ++i) {
		while(j < i - 1 and E2(Ml[j + 1]) <= dis[i] - dis[j + 1])
			j++;
		Ml[i] = min(E2(Ml[j + 1]), (double)(dis[i] - dis[j]) * 1.0);
	}
	
	j = n;

	for(int i = n - 1; i >= 1; --i) {
		while(j > i + 1 and E2(Mr[j - 1]) <= dis[j - 1] - dis[i])
			j--;
		Mr[i] = min(E2(Mr[j - 1]), (double)(dis[j] - dis[i]));
	}
	
	for(int i = 1; i <= n; ++i) {
		double e = max(Ml[i], Mr[i]);
		int x = (int)e;
		ans = min(ans, x);
	}
	
	cout << ans << endl;

	#ifndef	ONLINE_JUDGE
		getchar();
	#endif
	return 0;
}

// 1 10000 2 3 4 5 6
// e1 e2 e3 e4 e5
// e2 = d2 - d1
// e3 = e2 * 1.5
