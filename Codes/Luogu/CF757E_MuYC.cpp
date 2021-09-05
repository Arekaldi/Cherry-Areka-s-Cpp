#include <bits/stdc++.h>
using namespace std;
inline int read() {
    int x = 0, flag = 1;
    char ch = getchar();
    for( ; ch > '9' || ch < '0' ; ch = getchar()) if(ch == '-') flag = -1;
    for( ; ch >= '0' && ch <= '9' ; ch = getchar()) x = (x << 3) + (x << 1) + ch - '0';
    return x * flag;
}
const int MAXR = 1e6 + 5, MAXK = 20, MAXN = 1e6 + 5;
const int Mod = 1e9 + 7;
int f[MAXR][MAXK], P[MAXN], bk[MAXN], tot = 0;
void GetPrime(int N) {
    for(int i = 2 ; i <= N ; i ++) {
        if(!bk[i]) P[++ tot] = i;
        for(int j = 1 ; j <= tot && P[j] * i <= N ; j ++) {
            bk[P[j] * i] = 1;
            if(i % P[j] == 0) break;
        }
    }
    return;
}

signed main() {
    int q = read(); GetPrime(1e6);
    for(int i = 0; i <= 19 ; i ++) f[0][i] = i ? 2 : 1;
    for(int i = 1 ; i <= 1e6 ; i ++) {
        int S = 1;
        f[i][0] = 1;
        for(int k = 1 ; k <= 19 ; k ++) {
            S += f[i - 1][k], S %= Mod;
            f[i][k] = S;
        }
    }
    for(int i = 1 ; i <= q ; i ++) {
        int r = read(), n = read(), ans = 1;
        if(!bk[n]) { printf("%d\n", f[r][1]); continue; }
        else {
            for(int j = 1 ; P[j] <= 100 ; j ++) {
                int cnt = 0;
                while(n % P[j] == 0) n /= P[j], cnt ++;
                ans = 1ll * ans * f[r][cnt] % Mod;
            }
            if(n == 1) printf("%d\n", ans);
            else {
                if(sqrt(n) * sqrt(n) == n) ans = 1ll * ans * f[r][2] % Mod;
                else if(!bk[n]) ans = 1ll * ans * f[r][1] % Mod;
                else ans = 1ll * ans * f[r][1] % Mod * f[r][1] % Mod;
                printf("%d\n", ans);
            }
        }
    }
    return 0;
}