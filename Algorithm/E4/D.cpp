#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <algorithm>
#include <stack>
#include <assert.h>

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

std :: stack <int> s;

int vis[2010];
int visit[2010];

int to[2010], val[2010], next[2010], head[2010], from[2010];
int tot = 0;

void addEdge(int u, int v, int w) {
    to[++tot] = v, val[tot] = w, next[tot] = head[u], head[u] = tot;
    from[tot] = u;
}

double ans = 1ll << 32;

int n, m, pppp;
int map[2010][2010];
int temp[2010];
int output[2010];
void dfs(int u) {
    for(int i = head[u]; i; i = next[i]) {
        int v = to[i];

        if(vis[v]) {
            pppp++;
            double n = 1.0, w = val[i] * 1.0;
            int top = 0, p = 0;
            while(s.size() && from[s.top()] != v) {
                temp[++top] = s.top();
                n += 1.0, w += val[s.top()] * 1.0;
                output[++p] = to[s.top()];
                s.pop();
            }
            // output[++p] = v, output[++p] = to[s.top()];
            // std :: sort(output + 1, output + p + 1);
            // for(int j = 1; j <= p; ++j) {
            //     printf("%d ", output[j]);
            // }
            if(s.size())
                w += val[s.top()] * 1.0, n += 1.0;
            for(int j = top; j >= 1; --j)
                s.push(temp[j]);

            double t = w / n;
            // printf("%lf %lf\n", n, w);
            // printf("%.8lf\n", t);
            // puts("");
            if(t < ans || ans == 0) {
                ans = t;
                // printf("%.8lf\n", t);
            }
            continue;
        }

        vis[v] = 1;
        s.push(i);
        dfs(v);
        vis[v] = 0;
        s.pop();
    }
}

int main() {
    int T = read();
    while(T--) {
        memset(head, 0, sizeof(head));
        memset(map, 0x7f, sizeof(map));
        tot = 0;
        n = read();
        m = read();
        ans = 0;
        for(int i = 1; i <= m; i++) {
            int u = read(), v = read(), w = read();
            if(w > 3000)
                continue;
            if(u == v) {
                ans = std :: min(ans, w * 1.0);
                continue;
            }
            addEdge(u, v, w);
        } 
        for(int i = 1; i <= n; ++i) {
            memset(vis, 0, sizeof(vis));
            vis[i] = 1;
            dfs(i);
            vis[i] = 0;
            while(!s.empty())
                s.pop();
        }
        printf("%.4lf\n", ans);
    }
}