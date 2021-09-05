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

const int maxn = 1e7 + 1;
int mu[maxn], sum[maxn], pri[maxn], tot;

bool isp[maxn];

inline void Get_Mu() {
	memset(isp, true, sizeof(isp));
	isp[1] = false, mu[1] = 1;
	for(int i = 1; i <= maxn; ++i) {
		if(isp[i])
			pri[++tot] = i, mu[i] = -1;
		for(int j = 1; j <= tot and pri[j] * i <= maxn; ++j) {
			isp[pri[j] * i] = false;
			if(i % pri[j] == 0)
				break;
			else
				mu[i * pri[j]] = -mu[i];
		}
	}
	// 筛出所有的 p | i 的 sum[i] 
	for(int i = 1; i <= tot; ++i)
		for(int j = 1; j * pri[i] <= maxn; ++j)
			sum[j * pri[i]] += mu[j]; // sum[p * d] += mu[d]
	for(int i = 1; i <= maxn; ++i)
		sum[i] += sum[i - 1];
}

signed main() {
	int T = read();
	Get_Mu();
	while(T--) {
		int n = read(), m = read();
		int res = 0;
		if(n > m)
			swap(n, m);
		// 数论分块 维护双指针 
		for(int j, i = 1; i <= n; i = j + 1) {
			j = min(n / (n / i), m / (m / i));
//			cout << j << " " << i - 1 << endl;
			res += (sum[j] - sum[i - 1]) * (n / i) * (m / i);
		}
		printf("%lld\n", res);
	}
}
