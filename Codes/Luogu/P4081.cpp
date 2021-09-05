#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

const int maxn = 4e5 + 1;

class Suffer_AtM {
    private:

        int trans[maxn][26], fa[maxn], len[maxn],
            sz[maxn], d[maxn], st[maxn];
        int tot, lst;

    
    public:
        inline void init() {
            memset(trans, 0, sizeof(trans));
            memset(fa, 0, sizeof(fa));
            memset(len, 0, sizeof(len));
            memset(sz, 0, sizeof(sz));
            memset(d, 0, sizeof(d));
            memset(st, 0, sizeof(st));
            len[0] = 0;
            fa[0] = -1;
            tot = 0, lst = 0;
        }

        inline void Insert(int x) {
            int p = lst, np = ++tot;
            len[np] = len[p] + 1, sz[np] = 1;

            while(p != -1 and !trans[p][x]) {
                trans[p][x] = np;
                p = fa[p];
            }
            if(p == -1)
                fa[np] = 0;
            else {
                int q = trans[p][x];
                if(len[p] + 1 == len[q])
                    fa[np] = q;
                else {
                    int nq = ++tot;
                    fa[nq] = fa[q];
                    len[nq] = len[p] + 1;
                    for(int i = 0; i < 26; ++i)
                        trans[nq][i] = trans[q][i];
                    fa[np] = fa[q] = nq;
                    while(p != -1 and trans[p][x] == q) {
                        trans[p][x] = nq;
                        p = fa[p];
                    }
                }
            }
            lst = np;
        }

        inline int Ask() {
            int res = 0;
            for(int i = 1; i <= tot; ++i)
                res += len[i] - len[fa[i]];
            return res;
        }
};

Suffer_AtM S;

string s;
int T;

signed main() {

    T = read();
    while(T--) {
        cin >> s;
        int l = s.length();
        S.init();
        for(int i = 0; i < l; ++i)
            S.Insert(s[i] - 'a');
        printf("%d\n", S.Ask());
    }

    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
