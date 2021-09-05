#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

inline int Count(int n) {
    n = (n & 0x55555555) + ((n >> 1) & 0x55555555);
    n = (n & 0x33333333) + ((n >> 2) & 0x33333333);
    n = (n & 0x0f0f0f0f) + ((n >> 4) & 0x0f0f0f0f);
    n = (n & 0x00ff00ff) + ((n >> 8) & 0x00ff00ff);
    n = (n & 0x0000ffff) + ((n >> 16) & 0x0000ffff);
    return n;
}

#define rint register int

const int maxn = 3e5 + 1, maxk = (1 << 14);

int n, m, k, tot, T;
int numk[maxn], a[maxn];
long long t[maxn], s1[maxn], s2[maxn], g[maxn], ans[maxn];
class Question {
    public:
        int l, r, id;
};

Question q[maxn];
vector <Question> vl[maxn];

inline Question Qup(int L, int R, int ID) {
    Question ans;
    ans.l = L, ans.r = R, ans.id = ID;
    return ans;
}

inline bool Camp(Question a, Question b) {
    return (a.l / T == b.l / T) ? (a.r < b.r) : (a.l < b.l);
}

signed main() {
    n = read(), m = read(), k = read();

    if(k > 14) {
        for(rint i = 1; i <= m; ++i)
            puts("0");
        exit(0);
    }

    T = sqrt(n);
    
    for(rint i = 0; i < maxk; ++i)
        if(Count(i) == k)
            numk[++tot] = i;

    for(rint i = 1; i <= n; ++i)
        a[i] = read();

    for(int i = 1; i <= m; ++i)
        q[i].l = read(), q[i].r = read(), q[i].id = i;

    sort(q + 1, q + n + 1, Camp);

    rint l = q[1].r + 1, r = q[1].r;
    // vl[a].push_back(b, c, ...) 表示统计所有的 delta_ans += \forall x \in (b, c) => (1, a)的贡献
    // 当范围缩小时 ans -= delta_ans 反之则加
    for(rint i = 1; i <= m; ++i) {
        if(l < q[i].l)
            vl[r].push_back(Qup(l, q[i].l - 1, q[i].id << 1));
        if(l > q[i].l)
            vl[r].push_back(Qup(q[i].l, l - 1, q[i].id << 1));
        l = q[i].l;
        if(r < q[i].r)
            vl[l - 1].push_back(Qup(r + 1, q[i].r, (q[i].id << 1) | 1));
        if(r > q[i].r)
            vl[l - 1].push_back(Qup(q[i].r + 1, r, (q[i].id << 1) | 1));
        r = q[i].r;
    }

    //动 l 和动 r 不同！！
    /*
        考虑从[l,r] => [l + p, r]
        delta_ans += f(i, [i + 1, r])
        delta_ans += f(i, [1, r]) - f(i, [1, i])
    */

    /*
    首先预处理出前缀 i => [1, i - 1] 直接 O(1) 查询
        也就是s1
    然后进行二次离线
   */
   //一次离线
    for(rint i = 1; i <= n; ++i) {
        s1[i] = s1[i - 1] + t[a[i]];
        // 处理前缀即 x => [1, x - 1]
        for(rint j = 1; j <= tot; ++j)
            t[a[i] ^ numk[j]]++; //统计数的个数
        s2[i] = s2[i - 1] + t[a[i]]; //处理要减部分的贡献
        for(rint j = 0; j < vl[i].size(); ++j) {
            for(rint k = vl[i][j].l; k <= vl[i][j].r; ++k)
                g[vl[i][j].id] += t[a[k]]; //统计减号后面的
                // g 是个桶
        }
    }

    //二次离线
    long long anss = 0;
    l = q[1].r + 1, r = q[1].r;
    for(rint i = 1; i <= m; ++i) {
        if(l < q[i].l)
            anss += s2[q[i].l - 1] - s2[l - 1] - g[q[i].id << 1];
        if(l > q[i].l)
            anss += s2[q[i].l - 1] - s2[l - 1] + g[q[i].id << 1];
        l = q[i].l;
        if(r < q[i].r)
            anss += s1[q[i].r] - s1[r] - g[(q[i].id << 1) | 1];
        if(r > q[i].r)
            anss += s1[q[i].r] - s1[r] + g[(q[i].id << 1) | 1];
        r = q[i].r;
        ans[q[i].id] = anss;
    }
    
    for(rint i = 1; i <= m; ++i)
        printf("%lld\n", ans[i]);

    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
