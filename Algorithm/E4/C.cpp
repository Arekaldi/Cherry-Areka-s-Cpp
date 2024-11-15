#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <algorithm>
#include <queue>

#define int long long

int read(void) {
    int x, f = 1;
    char ch;
    while(!isdigit(ch = getchar()))
        (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 1) + (x << 3) + (ch ^ 48));
    return x * f;
}

void write(int x)
{
    if(x < 0)
        putchar('-'), x = -x;
    if(x > 9)
        write(x / 10);
    putchar(x % 10 + '0');
    return;
}

struct Node {
    int now, val;
    Node(int _now, int _val) : now(_now), val(_val) {}
    bool operator < (const Node& b) const {
        return val > b.val;
    }
};

int to[1000010], next[1000010], head[100010], val[1000010];
int tot;

void addEdge(int u, int v, int w) {
    to[++tot] = v, next[tot] = head[u], head[u] = tot, val[tot] = w;
}

int dist[2][100010];

std :: priority_queue<Node> q;

int n;

void dijkstra(int s, int index) {
    // memset(dist, 0x7f, sizeof(dist));
    for(int i = 1; i <= n; ++i)
        dist[index][i] = 1ll << 61;
    q.push(Node(s, 0));
    dist[index][s] = 0;
    while(!q.empty()) {
        Node now = q.top();
        q.pop();
        int u = now.now, d = now.val;
        if(d > dist[index][u])
            continue;
        for(int i = head[u]; i; i = next[i]) {
            int v = to[i], w = val[i];
            if(dist[index][u] + w < dist[index][v]) {
                dist[index][v] = dist[index][u] + w;
                q.push(Node(v, dist[index][v]));
            }
        }
    }
}

int p[100010];

signed main() {
    int T = read();
    // int T = 1;
    while(T--) {
        n = read();
        int m = read(), k = read();
        for(int i = 1; i <= k; ++i)
            p[i] = read();
        memset(head, 0, sizeof(head));
        tot = 0;
        for(int i = 1; i <= m; i++) {
            int u = read(), v = read(), w = read();
            addEdge(u, v, w);
            addEdge(v, u, w);
        }
        int ans = 1ll << 61;
        dijkstra(1, 0);
        dijkstra(n, 1);
        for(int i = 1; i <= k; i++) {
            int pp = p[i];
            ans = std::min(ans, dist[0][pp] + dist[1][pp]);
        }
        write(ans > 1ll << 60 ? -1 : ans);
        putchar('\n');
    }
}