> B-LiftOff
>
> 23371041-李一鸣

## 题目描述

- 给定 $G(V,E)$ 和 $q$ 组询问，询问是否存在一条从 $s$ 到 $t$ 经过编号为 $k$ 的边
- $1 \le n \le 500, 1 \le m \le 5000, 1\le q \le 10^5$

## 解题思路

- 由于 $n$ 较小，而 $q$ 较大，因此考虑预处理。
- 要处理出多组的 $s, t$ 因此考虑不能用单源最短路径算法，因此考虑用 $Floyd$ 算法
- 预处理出各点对之间的 $dis$，同时记下 $edge_k$ 对应的 $(u_{from}, u_{to}, val)$
- 在询问时，判断 $dis(u_{from}) + val = dis(u_{to})$ 即可

## 代码实现

```cpp

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
```

