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

const int maxn = 4e5 + 1;

class Suffer_AtM {
    private:
        /*
            trans[x][c] -> x 表示字符串在前面加一个 c 会指到哪里
            fa -> 就是 fa
            len -> 该点的字符串长度
            sz -> 就是子树的 size
            d -> 节点的度数(判断是否是叶子)
            st -> 类似队列的东西
        */

        map <int, int> trans[maxn];
        int fa[maxn], len[maxn],
            sz[maxn], d[maxn], st[maxn];
        int tot, lst;

    
    public:
        int res = 0;
        inline void init() {
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
                // 否则就进行更新
                int q = trans[p][x];
                if(len[p] + 1 == len[q])
                    fa[np] = q;
                else {
                    int nq = ++tot;
                    fa[nq] = fa[q];
                    len[nq] = len[p] + 1;
                    trans[nq] = trans[q];
                    fa[np] = fa[q] = nq;
                    while(p != -1 and trans[p][x] == q) {
                        trans[p][x] = nq;
                        p = fa[p];
                    }
                }
            }
            lst = np;
            res += len[np] - len[fa[np]];
        }
};

Suffer_AtM S;
int n;

signed main() {
    n = read();

    S.init();
    for(int i = 1; i <= n; ++i) {
        int x = read();
        S.Insert(x);
        printf("%lld\n", S.res);
    }


    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}