#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

const int maxn = 1e6 + 1;

int n, m;
int T[maxn], Nt[maxn];

inline bool Check() {
    // memcpy(Nt, T, sizeof(T));
    for(int i = 1; i <= n; ++i)
        Nt[i] = T[i];
    Nt[n + 1] = Nt[n + 2] = 0;
    for(int i = 1; i <= n + 2; ++i) {
        if(Nt[i] < 0)
            return false;
        Nt[i] %= 3;
        Nt[i + 1] -= Nt[i], Nt[i + 2] -= Nt[i];
    }
    return true;
}

signed main() {
    n = read(), m = read();
    
    for(int i = 1; i <= 3 * m + 1; ++i) {
        int x = read();
        T[x]++;
    }

    bool flag = false;
    for(int i = 1; i <= n; ++i) {
        T[i]++;
        for(int j = 1; j <= n; ++j) {
            if(T[j] < 2)
                continue;
            T[j] -= 2;
            if(Check()) {
                printf("%d ", i);
                T[j] += 2;
                flag = true;
                break;
            }
            T[j] += 2;
        }
        T[i]--;
    }

    puts(flag ? "" : "NO");
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
