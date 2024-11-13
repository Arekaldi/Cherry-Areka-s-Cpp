#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
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

int tot = -1;
int head[210], next[10010], val[10010], to[10010];
int cur[210];

void addEdge(int u, int v, int w) {
    to[++tot] = v, next[tot] = head[u], head[u] = tot;
    val[tot] = w;
}

std :: queue <int> q;
int dep[210], numOfDepth[210];
void bfs(int s, int t) {
    q.push(t);
    dep[t] = 1, numOfDepth[1] = 1;
    while(!q.empty()) {
        int u = q.front();
        q.pop();
        for(int i = head[u]; i != -1; i = next[i]) {
            int v = to[i];
            if(dep[v])
                continue;
            dep[v] = dep[u] + 1;
            numOfDepth[dep[v]]++;
            q.push(v);
        }
    }
}

int ans, n, m, s, t;
int dfs(int now, int flow) {
    if(now == t) {
        ans += flow;
        return flow;
    }

    int usedFlow = 0;
    for(int i = cur[now]; i != -1; i = next[i]) {
        cur[now] = i;
        int v = to[i], w = val[i];
        if(dep[v] == dep[now] - 1 && w > 0) {
            int nextFlow = std :: min(flow - usedFlow, w);
            int getFLow = dfs(v, nextFlow);
            if(getFLow) {
                val[i] -= getFLow, val[i ^ 1] += getFLow;
                usedFlow += getFLow;
                if(usedFlow == flow)
                    return flow;
            }
        }
    }
    numOfDepth[dep[now]]--;
    if(!numOfDepth[dep[now]])
        dep[s] = n + 1;
    dep[now]++, numOfDepth[dep[now]]++;
    return usedFlow;
}

int ISAP() {
    bfs(s, t);
    while(dep[s] <= n) {
        memcpy(cur, head, sizeof(cur));
        dfs(s, 1ll << 61);
    }
    return ans;
}

signed main() {
    int T = read();
    while(T--) {
        memset(head, -1, sizeof(head));
        memset(dep, 0, sizeof(dep));
        memset(numOfDepth, 0, sizeof(numOfDepth));
        memset(next, 0, sizeof(next));
        memset(val, 0, sizeof(val));
        tot = -1;
        n = read(), m = read(), s = read(), t = read();
        for(int i = 1; i <= m; i++) {
            int u = read(), v = read(), w = read();
            addEdge(u, v, w), addEdge(v, u, 0);
        }
        write(ISAP());
        return 0;
    }
}