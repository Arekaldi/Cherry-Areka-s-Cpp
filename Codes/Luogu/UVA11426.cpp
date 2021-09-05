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

const int maxn = 4e6 + 1;

int n, Maxp;

int g[maxn];
int pri[maxn], phi[maxn], sum_phi[maxn];
bool isp[maxn];
int f[maxn];
int tot = 0;

inline void Get_Phi() {
	memset(isp, true, sizeof(isp));
	// phi[1] = 1;
	for(int i = 2; i < maxn; ++i) {
		if(isp[i]) {
            Maxp = max(Maxp, i);
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
	}
}


signed main() {
	Get_Phi();

    for(int i = 1; i < maxn; ++i)
        for(int k = 1; k * i < maxn; ++k)
            g[k * i] += k * phi[i];

    for(int i = 1; i < maxn; ++i)
        f[i] = f[i - 1] + g[i];

    while(n = read())
        printf("%lld\n", f[n]);

    getchar();
    return 0;
}