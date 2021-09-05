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

        int trans[maxn][26], fa[maxn], len[maxn],
            sz[maxn], d[maxn], st[maxn];
        int tot, lst, rt;

    
    public:
        inline void init() {
            len[0] = 0;
            fa[0] = -1;
            tot = 0, lst = 0;
        }

        inline void Insert(int x, int opt) {
            int p = lst, np = ++tot;
            len[np] = len[p] + 1, sz[np] = !opt;

            // 新建节点
            while(p != -1 and !trans[p][x]) {
                trans[p][x] = np;
                p = fa[p];
            }
            // 因为 np 是最靠下的点，所以就直接将 trans 连上
            if(p == -1)
                fa[np] = 0;
            // 如果 Last 为 0，说明节点应该链接到根上
            // 因为直到根都没有找到 trans 指针
            else {
                // 否则就进行更新
                int q = trans[p][x];
                // 取出 p 的 trans 指针(现在也就是 np)，进行大力分讨
                // 因为现在要把 np 接到 p 的 trans 指针下面
                if(len[p] + 1 == len[q])
                    fa[np] = q;
                else {
                    // 我们发现 trans 直接指到 np 会指过
                    // 因为是一个一个插的，每一个节点都在上一个节点下面，所以不存在
                    // 过短的情况
                    int nq = ++tot;
                    fa[nq] = fa[q];
                    // 进行分叉
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
                d[len[i]]++;
            for(int i = 1; i <= tot; ++i)
                d[i] += d[i - 1];
            for(int i = 1; i <= tot; ++i)
                st[d[len[i]]--] = i;
            for(int i = tot; i >= 1; --i)
                sz[fa[st[i]]] += sz[st[i]];
            for(int i = 1; i <= tot; ++i) 
                res = max(res, sz[i] * len[i]);
            return res;
        }
};

Suffer_AtM S;
// #define Insert extend

string s;
int n;
string p;

signed main() {
    n = read();
    getline(cin, s);
    getline(cin, p);

    S.init();
    for(int j = 0; s[j]; ++j)
        S.Insert(s[j] - 'a', p[j] - '0');
    
    int ans = S.Ask();
    
    printf("%lld\n", ans);

    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}