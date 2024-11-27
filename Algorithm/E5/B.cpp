#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <algorithm>

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

int dist[501][501];

struct Edge {
    Edge() {}
    Edge(int u, int v, int w) : from(u), to(v), val(w) {}
    int from, to, val;
};

Edge e[5001];

int main() {
    int n = read(), m = read(), q = read();
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= n; ++j)
            dist[i][j] = (i == j) ? 0 : 0x3f3f3f3f;
    for(int i = 1; i <= m; ++i) {
        int u = read(), v = read(), w = read();
        dist[u][v] = dist[v][u] = std :: min(w, dist[u][v]);
        e[i] = Edge(u, v, w);
    }
    for(int k = 1; k <= n; ++k)
        for(int i = 1; i <= n; ++i) {
            if(i == k)
                continue;
            for(int j = 1; j <= n; ++j) {
                if(j == i || j == k)
                    continue;
                if(dist[i][j] > dist[i][k] + dist[k][j])
                    dist[i][j] = dist[i][k] + dist[k][j];
            }
        }

    for(int i = 1; i <= q; ++i) {
        int s = read(), t = read(), k = read();
        if(dist[s][t] == dist[s][e[k].from] + e[k].val + dist[e[k].to][t] || 
           dist[s][t] == dist[s][e[k].to] + e[k].val + dist[e[k].from][t])
            puts("Yes");
        else
            puts("No");
    }
    return 0;
}