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

int vis[100010];
// 访问过为1, 在栈中为2, 未访问为0

int to[200010], val[200010], next[200010], head[200010];
int tot = 0;

void addEdge(int u, int v, int w) {
    to[++tot] = v, val[tot] = w, next[tot] = head[u], head[u] = tot;
}

int n, m;
int visitInNode[100010];
int output[100010];
int top;
void dfs(int u, int last) {
    vis[u] = 1;
    s.push(u);
    for(int i = head[u]; i; i = next[i]) {
        int v = to[i];
        if(top)
            return;
        if(!vis[v])
            dfs(v, u);
        else if(v != last) {
            output[++top] = v;
            while(!s.empty() && s.top() != v)
                output[++top] = s.top(), s.pop();
            while(!s.empty())
                s.pop();
            return;
        }
    }
    s.pop();
}

int main() {
    n = read();
    for(int i = 1; i <= n; i++) {
        int u = read(), v = read();
        if(u == v) {
            write(u);
            putchar('\n');
            return 0;
        }
        addEdge(u, v, 1);
        addEdge(v, u, 1);
    }
    dfs(1, 0);
    std :: sort(output + 1, output + 1 + top);
    for(int i = 1; i <= top; i++)
        write(output[i]), putchar(' ');
    putchar('\n');
    return 0;
}