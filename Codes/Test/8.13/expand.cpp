#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

const int maxn = 3e2 + 1;

class Node {
    public:
        int mr, sv, ssp;
        // 最短路，当前的体积，体积和，当前逛完了多少商店
        int x, y;
        Node() {}
        Node(int a, int b, int c, int e, int f) :
            x(a), y(b), mr(c), sv(e), ssp(f) {}
        inline bool operator < (const Node &g) const {
            if(g.ssp == ssp) {
                if(g.mr == mr)
                    return g.sv > sv;
                else
                    return g.mr < mr;
            }
            else
                return g.ssp > ssp;
        }
};

int n, m, s, p;
int mp[maxn][maxn];
bool vis[maxn][maxn];

priority_queue <Node> Q;

inline int Get_Sv(int x, int y) {
    int res = 0;
    return min(res, s);
}

int go[][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

inline void Bfs(int stx, int sty) {
    int res1 = 0, res2 = 0;
    Q.push(Node(stx, sty, 0, Get_Sv(stx, sty), 0));
    while(!Q.empty()) {
        Node now = Q.top();
        Q.pop();
        if(now.ssp == p) {
            res1 = now.mr, res2 = now.sv;
            break;
        }
        vis[now.x][now.y] = true;
        for(int i = 0; i < 4; ++i) {
            int nx = now.x + go[i][0], ny = now.y + go[i][1];
            if(nx < 0 or nx >= n or ny < 0 or ny >= m)
                continue;
            if(mp[nx][ny] == 1)
                continue;
            if(vis[nx][ny])
                continue;
            Q.push(Node(nx, ny, now.mr + 1, now.sv + Get_Sv(nx, ny), now.ssp + (mp[nx][ny] == 2)));
        }
    }

    printf("%d %d\n", res1, res2);
}

signed main() {

    #define Areka
    #ifdef Areka
        freopen("expand.in", "r", stdin);
        freopen("expand.out", "w", stdout);
    #endif

    n = read(), m = read(), s = read();
    
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < m; ++j)
            mp[i][j] = read();
    
    int x = read(), y = read();
    p = read();

    for(int i = 1; i <= p; ++i) {
        int u = read(), v = read();
        mp[u][v] = 2;
    }
    
    Bfs(x, y);

    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
