#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

#define int long long

inline int read() {
    register int x = 0, f = 1;
    register char ch = getchar();
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

inline int gcd(int a, int b) {
    return b == 0 ? a : gcd(a % b, b);
}

inline int Min(int a, int b) {
    return a > b ? b : a;
}

int n, a[1010], b[1010];
int dp[2][12010];
const int mod = 6000;

signed main() {
    n = read();
    
    memset(dp, 0x7f, sizeof(dp));

    dp[0][mod] = 0;

	for(int i = 1; i <= n; ++i) 
		a[i]= read(), b[i] = read();
	
    int k = 1;
    for(int i = 1; i <= n; ++i, k ^= 1) {
        for(int j = -5050; j <= 5050; ++j) {
            dp[k][j + mod] = Min(dp[k ^ 1][j - (a[i] - b[i]) + mod] + 1, dp[k ^ 1][j - (b[i] - a[i]) + mod]);
        }
    }

    // int ans;
    for(int i = 0; i <= 5000; ++i) {
        int out = Min(dp[n & 1][i + mod], dp[n & 1][mod - i]);
        if(out <= 1000) {cout << out << endl; break;}
        // if(dp[n][i + mod] >= 0 and dp[n][i + mod] <= n) {printf("%lld\n", dp[n][i + mod]); break;}
        // else if(dp[n][-i + mod] >= 0 and dp[n][-i + mod] <= n) {printf("%lld\n", dp[n][-i + mod]); break;}
        // cout << dp[n][i] << endl;
    }
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
