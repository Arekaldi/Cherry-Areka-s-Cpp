#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

const int maxn = 1e7 + 1;

int n;

int pri[maxn], phi[maxn], sum_phi[maxn];
bool isp[maxn];

inline void Get_Phi() {
	memset(isp, true, sizeof(isp));
	int tot = 0;
	phi[1] = 1;
	sum_phi[1] = 1;
	for(int i = 2; i <= n; ++i) {
		if(isp[i]) {
			pri[++tot] = i;
			phi[i] = i - 1;
		}
		for(int j = 1; j <= tot and i * pri[j] <= n; ++j) {
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

signed main() {
	n = read();
	if(n == 1) {
		puts("0");
		return 0;
	}
	Get_Phi();
	printf("%d\n", (sum_phi[n - 1] << 1) + 1);
    getchar();
    return 0;
}
