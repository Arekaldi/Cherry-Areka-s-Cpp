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

inline int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

const int maxn = 1e6 + 1;
int ans[maxn];
int n;

int tot = 0;
int pri[maxn], phi[maxn];
bool isp[maxn];

inline void Get_Phi() {
    memset(isp, true, sizeof(isp));
    phi[1] = 1;
    for(int i = 2; i < maxn; ++i) {
        if(isp[i]) 
            pri[++tot] = i, phi[i] = i - 1;
        for(int j = 1; j <= tot and i * pri[j] < maxn; ++j) {
            isp[i * pri[j]] = false;
            if(i % pri[j])
                phi[i * pri[j]] = phi[i] * phi[pri[j]];
            else {
                phi[i * pri[j]] = pri[j] * phi[i];
                break;
            }
        }
    }

    for(int i = 1; i < maxn; ++i)
        for(int j = i; j < maxn; j += i)
            ans[j] += (phi[i] * i + 1ll) >> 1;
}

signed main() {
    Get_Phi();

    int T = read();
    while(T--) {
        int n = read();
        printf("%lld\n", ans[n] * n);
    }
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
