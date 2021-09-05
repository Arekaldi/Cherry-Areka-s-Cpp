#pragma GCC diagnostic error "-std=c++11"
#pragma GCC target("avx")
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")
#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

const int maxn = 4e2 + 1;

//#define int long long

int n;
int f[3][maxn], dp[2][maxn][maxn][3];
int R, G, Y;
int sum[3][maxn];
int id[maxn];

char s[maxn];
int pos, now;

//#define 0 0ll

signed main() {
	
	freopen("b.in", "r", stdin);
	freopen("b.out", "w", stdout);
	
    n = read();
    cin >> (s + 1);
    
    for(int i = 1; i <= n; ++i) {
        if(s[i] == 'R')
            sum[0][++R] = i;
        f[0][i] = f[0][i - 1] + (s[i] == 'R');
        if(s[i] == 'G')
            sum[1][++G] = i;
        f[1][i] = f[1][i - 1] + (s[i] == 'G');
        if(s[i] == 'Y')
            sum[2][++Y] = i;
        f[2][i] = f[2][i - 1] + (s[i] == 'Y');
        id[i] = id[i - 1] ^ 1;
    }

    memset(dp, 0x3f3f3f, sizeof(dp));
    dp[1][1][0][0] = sum[0][1] - 1;
    dp[1][0][1][1] = sum[1][1] - 1;
    dp[1][0][0][2] = sum[2][1] - 1;

    for(int i = 2; i <= n; ++i) {
        for(int j = 0; j <= R; ++j) {
            for(int k = 0; k <= G; ++k) {
//                int pos, now;
				if(i - j - k > Y)
					continue;
                if(j) {
                    pos = sum[0][j], now = pos;
                    now += max(0, k - f[1][pos]), now += max(0, i - j - k - f[2][pos]);
                    dp[id[i]][j][k][0] = min(dp[id[i]][j][k][0], dp[id[i] ^ 1][j - 1][k][1] + now - i);
                    dp[id[i]][j][k][0] = min(dp[id[i]][j][k][0], dp[id[i] ^ 1][j - 1][k][2] + now - i);
                }
                if(k) {
                    pos = sum[1][k], now = pos;
                    now += max(0, j - f[0][pos]), now += max(0, i - j - k - f[2][pos]); 
                    dp[id[i]][j][k][1] = min(dp[id[i]][j][k][1], dp[id[i] ^ 1][j][k - 1][0] + now - i);
                    dp[id[i]][j][k][1] = min(dp[id[i]][j][k][1], dp[id[i] ^ 1][j][k - 1][2] + now - i);
                }
                 if(i - j - k) {    
                    pos = sum[2][i - j - k], now = pos;
                    now += max(0, k - f[1][pos]), now += max(0, j - f[0][pos]);
                    dp[id[i]][j][k][2] = min(dp[id[i]][j][k][2], dp[id[i] ^ 1][j][k][0] + now - i);
                    dp[id[i]][j][k][2] = min(dp[id[i]][j][k][2], dp[id[i] ^ 1][j][k][1] + now - i);
                 }
            }
        }
        memset(dp[id[i] ^ 1], 0x3f3f3f, sizeof(dp[id[i] ^ 1]));
    }

    int ans;

     ans = min(dp[id[n]][R][G][0], min(dp[id[n]][R][G][1], dp[id[n]][R][G][2]));
    if(ans >= 0x3f3f3f3f) cout << -1 << endl;
    else cout << ans << endl;
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
