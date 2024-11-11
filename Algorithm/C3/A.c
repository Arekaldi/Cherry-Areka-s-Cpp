#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int Tm;

long long dp[10010][3];
long long P[10010][3];
long long T[3][3];

long long min3(long long a, long long b, long long c) {
    return a < b ? (a < c ? a : c) : (b < c ? b : c);
}

int main() {
    scanf("%d", &Tm);
    int m;
    while(Tm--) {
        scanf("%d", &m);
        memset(dp, 0, sizeof(dp));
        for(int k = 0; k < 3; ++k)
            for(int i = 1; i <= m; ++i)
                scanf("%lld", &P[i][k]);
        for(int i = 0; i < 3; ++i)
            scanf("%lld%lld%lld", &T[i][0], &T[i][1], &T[i][2]),
            dp[1][i] = P[1][i];
        for(int i = 2; i <= m; ++i) {
            dp[i][0] = min3(dp[i - 1][0] + T[0][0], dp[i - 1][1] + T[1][0], dp[i - 1][2] + T[2][0]) + P[i][0];
            dp[i][1] = min3(dp[i - 1][0] + T[0][1], dp[i - 1][1] + T[1][1], dp[i - 1][2] + T[2][1]) + P[i][1];
            dp[i][2] = min3(dp[i - 1][0] + T[0][2], dp[i - 1][1] + T[1][2], dp[i - 1][2] + T[2][2]) + P[i][2];
        }
        printf("%lld\n", min3(dp[m][0], dp[m][1], dp[m][2]));
    }
}