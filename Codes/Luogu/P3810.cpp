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

int n, k, len, tot;
int ans[maxn];

class Node {
    public:
        int a, b, c;
        int ans, num;
        // num 去重用
        inline bool operator == (const Node &x) const {
            return x.a == a and x.b == b and x.c == c;
        }
}a[maxn], b[maxn];

class Tree_Array {
    private:
        int t[maxn];
        inline int lowbit(int x) {
            return x & (-x);
        }
    public:
        inline void Add(int pos, int v) {
            while(pos <= k) {
                t[pos] += v;
                pos += lowbit(pos);
            }
            return;
        }

        inline int Ask(int pos) {
            int ans = 0;
            while(pos) {
                ans += t[pos];
                pos -= lowbit(pos);
            }
            return ans;
        }
}T;

inline bool Camp1(Node a, Node b) {
    if(a.a != b.a)
        return a.a < b.a;
    if(a.b != b.b)
        return a.b < b.b;
    return a.c < b.c;
}

inline bool Camp2(Node a, Node b) {
    if(a.b != b.b)
        return a.b < b.b;
    return a.c < b.c;
}

inline void CDQ(int l, int r) {
    if(l == r)
        return;
    int mid = (l + r) >> 1;
    CDQ(l, mid), CDQ(mid + 1, r);
    sort(a + l, a + mid + 1, Camp2), sort(a + mid + 1, a + r + 1, Camp2);
    int j = l;
    for(int i = mid + 1; i <= r; ++i) {
        while(a[i].b >= a[j].b and j <= mid)
            // 双指针
            T.Add(a[j].c, a[j].num), j++;
        a[i].ans += T.Ask(a[i].c);
    }
    for(int i = l; i < j; ++i)
        T.Add(a[i].c, -a[i].num);
        // 以 a[i].c 为下标 清空树状数组
}

signed main() {
    n = read(), k = read();
    
    for(int i = 1; i <= n; ++i)
        b[i].a = read(), b[i].b = read(), b[i].c = read();
    
    sort(b + 1, b + n + 1, Camp1);
    
    for(int i = 1; i <= n; ++i) {
        if(b[i] == b[i - 1])
            a[len].num++;
            // 这个数有几个
        else {
            a[++len] = b[i];
            a[len].num++;
        }
    }

    CDQ(1, len);

    for(int i = 1; i <= len; ++i)
        ans[a[i].ans + a[i].num - 1] += a[i].num;
    
    for(int i = 0; i < n; ++i)
        printf("%d\n", ans[i]);
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
