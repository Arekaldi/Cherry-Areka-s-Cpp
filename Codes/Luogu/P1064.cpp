#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

const int maxn = 3.2e4 + 1, maxm = 61;

int f[maxn];
int n, m, v[maxm], w[maxm], p[maxm];

vector <int> son[maxm];
vector <int> mar;

signed main() {
    n = read(), m = read();
    for(int i = 1; i <= m; ++i) {
        v[i] = read(), w[i] = read(), p[i] = read();
        if(p[i] != 0)
            son[p[i]].push_back(i);
        else
            mar.push_back(i);
    }
    
    int ans = 0;
    for(int it = 0; it < mar.size(); ++it) {
        int i = mar[it];
        for(int k = n; k >= v[i]; --k) {
            f[k] = max(f[k], f[k - v[i]] + (v[i] * w[i]));
            for(int pp = 0; pp < son[i].size(); ++pp) {
                int j = son[i][pp];
                if(k >= v[i] + v[j])
                    f[k] = max(f[k], f[k - v[i] - v[j]] + (v[i] * w[i]) + (v[j] * w[j]));
                if(pp == 1) {
                    int p1 = son[i][0], p2 = son[i][1];
                    if(k >= v[i] + v[p1] + v[p2])
                        f[k] = max(f[k], f[k - v[i] - v[p1] - v[p2]] + (v[i] * w[i]) + (v[p1] * w[p1]) + (v[p2] * w[p2]));
                }
            }
        }
    }

    cout << f[n];
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
