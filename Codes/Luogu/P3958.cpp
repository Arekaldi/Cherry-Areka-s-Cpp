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

const int maxn = 1e3 + 1;

int fa[maxn], n, h, r;
bool can[maxn];
vector <int> id;

inline void init() {
    memset(fa, 0, sizeof(fa));
    memset(can, false, sizeof(can));
    id.clear();
}

inline int Find(int x) {
    if(fa[x] == 0)
        return fa[x] = x;
    else
        return fa[x] == x ? x : fa[x] = Find(fa[x]);
}

class Node {
    public:
        int x, y, z;
        Node() {}
        Node(int a, int b, int c) : x(a), y(b), z(c) {}
};

Node mk[maxn];

inline int Get_JL(const Node &a, const Node &b) {
    int diss = (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) +
                (a.z - b.z) * (a.z - b.z);
    return diss;
}


signed main() {
    int T = read();
    while(T--) {
        n = read(), h = read(), r = read(), init();
        for(int i = 1; i <= n; ++i) {
            int x = read(), y = read(), z = read();
            if(z + r >= h)
                can[i] = true;
            if(z - r <= 0)
                id.push_back(i);
            mk[i] = Node(x, y, z);
        }
        for(int i = 1; i <= n; ++i) {
            for(int j = i + 1; j <= n; ++j) {
                if(Get_JL(mk[i], mk[j]) <= 4 * r * r) {
                    int fi = Find(i), fj = Find(j);
                    if(fi == fj)
                        continue;
                    if(mk[fi].z < mk[fj].z)
                        fa[fi] = fj;
                    else
                        fa[fj] = fi;
                }
            }
        }

        for(auto it = id.begin(); it != id.end(); ++it) {
            if(can[Find(*it)]) {
                puts("Yes");
                goto Areka;
            }
        }

        puts("No");
        Areka:
            continue;
    }
    
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
