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

const int maxn = 1e5 + 1;

int n;

int pri[maxn], phi[maxn], sum_phi[maxn];
bool isp[maxn];
int ans;
int tot = 0;

inline void Get_Phi() {
	memset(isp, true, sizeof(isp));
	phi[1] = 1;
	sum_phi[1] = 1;
	for(int i = 2; i < maxn; ++i) {
		if(isp[i]) {
			pri[++tot] = i;
			phi[i] = i - 1;
		}
		for(int j = 1; j <= tot and i * pri[j] < maxn; ++j) {
			isp[i * pri[j]] = false;
			if(i % pri[j]) {
				phi[i * pri[j]] = phi[i] * phi[pri[j]];
				
			}
			else {
				phi[i * pri[j]] = phi[i] * pri[j];
				break;
			}
		}
		sum_phi[i] = sum_phi[i - 1] + phi[i];
	}
}

inline int Ans(int x) {
    return x == 1 ? 1 : (sum_phi[x] << 1) - 1;
}

inline int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

signed main() {
	n = read();

	Get_Phi();

    // for(int i = 1; i <= 10; ++i)
    //     cout << i << " " << Ans(i) << " " << sum_phi[i] << endl;

	for(int i = 1; i <= n; ++i) {
        int d = i;
        ans += d * Ans(n / d);
    }

    // while(++n <= 10) {
    //     ans = 0;
    //     printf("the first ans of %d: ", n);
    //     for(int i = 1; i <= n; ++i)
    //         for(int j = 1; j <= n; ++j)
    //             ans += gcd(i, j);
    //     printf("%lld\n", ans);
    // }

    printf("%lld\n", ans);

    getchar();
    return 0;
}