#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>



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

int head[200010], next[200010], to[200010];
int tot;

void addEdge(int u, int v) {
    to[++tot] = v, next[tot] = head[u], head[u] = tot;
}

struct Node {
    int vis, val;
    int color, colorNum;
};

int ans, blackNum, n;
int vis[100010];

struct Node node[1000010];

int stack[100010], top;

void FindSon(int now) {
    vis[now] = 1;
    node[now].colorNum = node[now].color;
    node[now].vis = 0, node[now].val = 0;
    for(int i = head[now]; i; i = next[i]) {
        int v = to[i];
        if(vis[v])
            continue;
        FindSon(v);
        node[now].val++;
        node[now].colorNum += node[v].colorNum;
    }
    return;
}

void Solve() {
    int p = 1;
    stack[++top] = 1;
    while(p <= top) {
        int now = stack[p++];
        vis[now] = 1;
        for(int i = head[now]; i; i = next[i]) {
            int v = to[i];
            if(vis[v])
                continue;
            stack[++top] = v;
        }
    }
    memset(vis, 0, sizeof(vis));
    while(top) {
        int now = stack[top--];
        vis[now] = 1;
        int colorNumInSon = 0;
        for(int i = head[now]; i; i = next[i]) {
            int v = to[i];
            if(!vis[v])
                continue;
            if(node[v].vis)
                node[now].val--;
            colorNumInSon += (node[v].colorNum != 0);
        }
        if(node[now].val == 0 && !node[now].color)
            node[now].vis = 1;
        if(node[now].colorNum == blackNum && colorNumInSon == 1)
            node[now].vis = 1;
        ans += (!node[now].color & !node[now].vis);
    }
    return;
}

int main() {
    n = read();
    for(int i = 1; i <= n; ++i) {
        node[i].color = read();
        node[i].vis = 0;
        blackNum += node[i].color;
    }
    for(int i = 1; i < n; ++i) {
        int u = read(), v = read();
        addEdge(u, v), addEdge(v, u);
    }
    FindSon(1);
    memset(vis, 0, sizeof(vis));
    Solve(1);
    write(ans);
    return 0;
}