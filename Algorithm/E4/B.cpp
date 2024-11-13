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
int head[5010], next[20010], val[20010], to[20010];
int cur[5010];

void addEdge(int u, int v, int w) {
    to[++tot] = v, next[tot] = head[u], head[u] = tot;
    val[tot] = w;
}

std :: queue <int> q;
int dep[5010], numOfDepth[5010];
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

int a[410], p[410], b[410], qq[410];

signed main() {
    memset(head, -1, sizeof(head));
    n = read();
    for(int i = 1; i <= n; ++i)
        a[i] = read();
    for(int i = 1; i <= n; ++i)
        p[i] = read();
    for(int i = 1; i <= n; ++i)
        b[i] = read();
    for(int i = 1; i <= n; ++i)
        qq[i] = read();
    s = (n << 1) | 1, t = s + 1;
    for(int i = 1; i <= n; ++i) {
        addEdge(s, i, 1);
        addEdge(i + n, t, 1);
    }
    for(int i = 1; i <= n; ++i) {
        for(int j = n + 1; j <= (n << 1); ++j) {
            int male = i, female = j - n;
            if(a[male]>= qq[female] && b[female] >= p[male]) {
                addEdge(i, j, 1ll << 31), addEdge(j, i, 0);
            }
        }
    }
    n = t;
    write(ISAP());
    return 0;
}