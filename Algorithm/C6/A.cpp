#include <stdio.h>

int n, m, tot, os, op, find_to, find_dis, u, v, fv;
int to[400010], net[400010], head[400010], dis[400010], dds[200010];
bool vis[200010];

void Add_edge(int x, int y, int w) {
    to[++tot] = y, net[tot] = head[x], dis[tot] = w;
    head[x] = tot;
}

int main() {
    scanf("%d %d", &n, &m);
    for(int i = 1; i <= n; ++i)
        dds[i] = 1e9;
    for(int i = 1; i <= m; ++i) {
        int x, y, z;
        scanf("%d %d %d", &x, &y, &z);
        Add_edge(x, y, z), Add_edge(y, x, z);
    }
    find_to = 1; vis[1] = 1, dds[1] = 0;
    for(int i = head[1]; i; i = net[i])
        dds[to[i]] = dds[to[i]] > dis[i] ? dis[i] : dds[to[i]];
    while(op != n - 1) {
        find_dis = 1e9;
        for(int i = 1; i <= n; ++i) {
            if(vis[i])
                continue;
            if(dds[i] < find_dis)
                find_dis = dds[i], find_to = i;
        }
        vis[find_to] = 1;
        os += find_dis;
        for(int i = head[find_to]; i; i = net[i])
            dds[to[i]] = dds[to[i]] > dis[i] ? dis[i] : dds[to[i]];
        op++;
         
    }
    for(int i = 1; i <= n; ++i) {
        if(!vis[i]) {
            printf("orz\n");
            return 0;
        }
    }
    printf("%d\n", os);
    return 0;
}