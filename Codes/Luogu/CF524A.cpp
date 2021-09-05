#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

const int maxm = 2010;

int m, k;

int a[maxm], b[maxm];
int l[maxm];
int ll;
bool ifd[maxm][maxm];

priority_queue <int, vector <int>, greater <int> > Q;

signed main() {
    m = read(), k = read();

    for(int i = 1; i <= m; ++i) {
        a[i] = read(), b[i] = read();
        l[++ll] = a[i], l[++ll] = b[i];
    }

    sort(l + 1, l + ll + 1);

    int k1 = unique(l + 1, l + ll + 1) - (l + 1);

    for(int i = 1; i <= m; ++i) {
        a[i] = lower_bound(l + 1, l + k1 + 1, a[i]) - l;
        b[i] = lower_bound(l + 1, l + k1 + 1, b[i]) - l;
        ifd[a[i]][b[i]] = ifd[b[i]][a[i]] = 1;
    }

    // for(int i = 0; i <= k1; ++i) cout << l[i] << endl;

    for(int i = 1; i <= k1; ++i) {
        cout << l[i] << ": ";
        int n = 0;

        for(int j = 1;j <= k1; ++j) {
            if(j == i) continue;
            if(ifd[i][j]) n++;
        }

        for(int j = 1; j <= k1; ++j) {
            if(j == i) continue;
            if(!ifd[i][j]) {
                int nj = 0;
                for(int o = 1; o <= k1; ++o) {
                    if(o == j or o == i) continue;
                    if(ifd[o][j] and ifd[o][i]) nj++;
                    // if(nj == n) break;
                }
                // if(i == 1 and j == 2) cout << nj << " " << n << endl;
                double nj1 = (double)nj * 1.0, n1 = (double)n * 1.0, k2 = (double)k * 1.0;
                // if(i == 1 and j == 2) {
                //     cout << (nj1 / n1) * 100.0 << " " << k2 << endl;
                // }
                if((nj1 / n1) >= (k2 / 100.0)) {
                    // if(i == 1 and j == 2) cout << 1 << endl;
                    Q.push(j);
                }
            }
        }

        cout << Q.size() << " ";
        while(!Q.empty()) {
            cout << l[Q.top()] << " ";
            Q.pop();
        }
        cout << endl;
        while(!Q.empty()) Q.pop();

    }

    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
