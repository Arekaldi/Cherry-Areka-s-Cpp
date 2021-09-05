#include <bits/stdc++.h>

using namespace std;

#define ll long long

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

const int maxn = 21, maxm = 1e6 + 10, maxx = 2e3 + 10;
const ll mod = 9e6 + 7, Lit = -4000000000;

class Hash_Map {
    public :
        ll H[mod];
        Hash_Map() {
            for(int i = 1; i < mod; ++i)
                H[i] = Lit;
        }
        inline int Hash(int x) {
            int r = x % mod;
            while(H[r] != Lit and H[r] != x) {
                r++;
                if(r > mod) r = 0;
            }
            H[r] = x;
            return r;
        }
}G;

struct Node {
    int to, nxt;
}E[maxm];

int N, M[maxn];
int mid, p, tot, ans;
int head[mod];

bool vis[maxx][maxx];

void Add_edge(int u, int v) {
    E[++tot].to = v, E[tot].nxt = head[u];
    head[u] = tot;
}

inline void dfs1(int now, int Pa, int Pb, int st) {
    if(now == mid + 1) {
        if(Pa < Pb) return;
        p = G.Hash(Pa - Pb);
        Add_edge(p, st);
        return;
    }
    dfs1(now + 1, Pa, Pb, st << 1);
    dfs1(now + 1, Pa + M[now], Pb, (st << 1) + 1);
    dfs1(now + 1, Pa, Pb + M[now], (st << 1) + 1);
}

inline void dfs2(int now, int Pa, int Pb, int st) {
    if(now == mid) {
        if(Pa < Pb) return;
        p = G.Hash(Pa - Pb);
        for(int i = head[p]; i; i = E[i].nxt) {
            if(!vis[E[i].to][st])
                vis[E[i].to][st] = true, ans++;
        }
        return;
    }
    dfs2(now - 1, Pa, Pb, st << 1);
    dfs2(now - 1, Pa + M[now], Pb, (st << 1) + 1);
    dfs2(now - 1, Pa, Pb + M[now], (st << 1) + 1);
}

signed main() {
    freopen("subset.in", "r", stdin);
    freopen("subset.out", "w", stdout);
    N = read();
    for(int i = 1; i <= N; ++i)
        M[i] = read();

    mid = N >> 1;

    dfs1(1, 0, 0, 0);
    dfs2(N, 0, 0, 0);

    cout << ans - 1 << endl;
    
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
