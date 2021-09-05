#include <bits/stdc++.h>

using namespace std;

#define ll long long

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

const int maxk = 11451420;

const int maxn = 4e7 + 1;

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

int p, k;

ll sum[maxk];

signed main() {

	#define Areka
	#ifdef Areka
		freopen("b.in", "r", stdin);
		freopen("b.out", "w", stdout);
	#endif
    
    clock_t a = clock();
    
	n = read(), m = read();
	if(n == 1) {
		puts("0");
		return 0;
	}
	Get_Phi();
	printf("%d\n", (sum_phi[n - 1] << 1) + 1);

    p = read(), k = read();
    
    sum[1] = p - 1;

    for(int i = 2; i <= k; ++i) {
    	int x = p - i;
    	while(x < 0)
    		x += p;
    	sum[i] = ((sum[i - 1]) * (x % p)) % p;
    }

    ll res = 1;

    for(int i = 2; i <= k; i += 2)
        res = (res * sum[i]) % p;

	clock_t b = clock();
	
	double s = a * 1.0, t = b * 1.0;

    printf("%lld\n", res % p);
    
    // printf("%.6f", (t - s) / CLOCKS_PER_SEC);
    
//    printf()
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
