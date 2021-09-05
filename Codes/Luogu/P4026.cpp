#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

const int maxn = 1e3 + 5, Inf = 0x7f7f7f7f;

class Per {
    public :
        int C[7], sum;
        Per() : sum(0) {}
}P[4];

int E[7] = {0, 100, 50, 20, 10, 5, 1};

int X1, X2, X3, tot;
int dp[maxn][maxn][maxn];
int ans = Inf, inf = Inf;
int T[7];

inline int A(int x) {
    return x < 0 ? -x : x;
}

signed main() {
    X1 = read(), X2 = read(), X3 = read();

    for(int i = 1; i <= 3; ++i) {
        for(int j = 1; j <= 6; ++j) {
            P[i].C[j] = read();
            P[i].sum += P[i].C[j] * E[j];
            T[j] += P[i].C[j];
        }
        tot += P[i].sum;
    }

    memset(dp, 0x7f, sizeof(dp));

    dp[0][P[1].sum][P[2].sum] = 0;

    for(int i = 1; i <= 6; ++i)
        for(int j = 0; j <= tot; ++j)
            for(int k = 0; k + j <= tot; ++k)
                if(dp[i - 1][j][k] != Inf) {
                    dp[i][j][k] = min(dp[i][j][k], dp[i - 1][j][k]);
                    for(int p = 0; p <= T[i]; ++p) {
                        for(int q = 0; q + p <= T[i]; ++q) {
                            int Na = j - (P[1].C[i] - p) * E[i];
                            int Nb = k - (P[2].C[i] - q) * E[i];
                            if(Na < 0 or Nb < 0 or Na + Nb > tot)
                                continue;
                            int ntt = T[i] - p - q;
                            int kkk = A(P[1].C[i] - p) + A(P[2].C[i] - q) + A(P[3].C[i] - ntt);
                            dp[i][Na][Nb] = min(dp[i][Na][Nb], dp[i - 1][j][k] + (kkk >> 1));
                        }
                    }
                }

    int E1 = P[1].sum - X1 + X3, E2 = P[2].sum - X2 + X1, E3 = P[3].sum - X3 + X2;

    if(E1 < 0 or E2 < 0 or E3 < 0 or E1 + E2 + E3 > tot) {
        puts("impossible");
        // goto Areka;
    }

    for(int i = 0; i <= 6; ++i)
        ans = min(ans, dp[i][E1][E2]);


// Areka :
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
