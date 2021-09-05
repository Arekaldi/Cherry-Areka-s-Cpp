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

const int maxn = 5e6 + 1;

char s[maxn];

class Perticulery_AuM {
    private:
        int len[maxn], fail[maxn], ch[maxn][26],
            num[maxn];
        int now, tot = 1, lst;

    public:

        inline void init() {
            len[1] = -1, len[0] = 0;
            fail[0] = 1;
            lst = 0, now = 0;
        }

        inline int Find_fail(int x, int i) {
            while(i - len[x] - 1 < 0 or s[i - len[x] - 1] != s[i])
                x = fail[x];
            return x;
        }

        inline void Insert(int p) {
            int A = Find_fail(now, p);
            if(!ch[A][s[p] - 'a']) {
                tot++;
                fail[tot] = ch[Find_fail(fail[A], p)][s[p] - 'a'];
                ch[A][s[p] - 'a'] = tot;
                len[tot] = len[A] + 2;
            }
            now = ch[A][s[p] - 'a'];
            num[now]++;
        }

        inline int Ask() {
            int res = 0;
            for(int i = tot; i > 0; --i) {
                num[fail[i]] += num[i];
                res = max(res, num[i] * len[i]);
            }
            return res;
        }
};

Perticulery_AuM P;

signed main() {
    cin >> s;
    P.init();
    
    int len = strlen(s);
    for(int i = 0; i < len; ++i)
        P.Insert(i);

    printf("%lld\n", P.Ask());

    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
