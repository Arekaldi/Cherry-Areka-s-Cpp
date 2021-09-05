#include <bits/stdc++.h>

#define int long long

using namespace std;

template <typename T>
inline void read (T &a) {
	T x = 0, f = 1;
	char ch = getchar ();
	while (! isdigit (ch)) {
		if (ch == '-') f = 0;
		ch = getchar ();
	}
	while (isdigit (ch)) {
		x = (x << 1) + (x << 3) + (ch ^ '0');
		ch = getchar ();
	}
	a = f ? x : -x;
}

int n, m;
int a[100010];
int minn = 1000000100, maxn;
long long sum;

signed main () {

    #define Areka
    #ifdef Areka
    freopen("1.txt", "r", stdin);
    freopen("rans.txt", "w", stdout);
    #endif

	read (n), read (m);
	for (int i = 1; i <= n; i++) {
		read (a[i]);
		sum += a[i];
	}
	sort (a + 1, a + n + 1);
	sum += m;
	for (int i = n - 1; i > 1; i--) {
		m -= (a[n] - a[i]);
		if (m <= 0) {
			break;
		}
	}
	int ans;
	if (m <= 0) {
		ans = sum - a[1] - a[n];
		printf ("%lld", ans);
		return 0;
	}
	int k = m / (n-1);
	a[n] += k;
	m %= (n-1);
	if (m) a[n] += 1;
	ans = sum - a[1] - a[n];
	printf ("%lld\n", ans);
}