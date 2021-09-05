#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

const int maxn = 51, Inf = (1 << 29);
const double delta = 0.9960;

int n, k, m;
bool vis[maxn];
int val[maxn][maxn];
int to[maxn];
int min_ans;

vector <int> V;

inline int Ans() {
    int an = 0;
    for(int i = 1; i <= n; ++i) {
        if(vis[i]) continue;
        int Dis = Inf;
        for(int j = 1; j <= n; ++j)
            if(i == j)
                continue;
            else 
                if(vis[j] and val[i][j] < Dis)
                    Dis = val[i][j];
        if(Dis > an)
            an = Dis;
    }
    return an;
}

inline void Sa() {
    double T = 2000.0, T0 = 1e-5;
    double ans = min_ans;
    int len = V.size() - 1;
    while(T > T0) {
        int now_x = ((int)(rand() * T) % len) + 1, now_y = ((int)(rand() * T) % len) + 1;
        swap(vis[V[now_x]], vis[V[now_y]]);
        int now_ans = Ans();
        int E = now_ans - ans;
        if(E < 0) 
            ans = now_ans;
        else if(exp(-E / T) * RAND_MAX <= rand())
            swap(vis[V[now_x]], vis[V[now_y]]);
            
        T *= delta;
    }

    if(ans < min_ans) 
        min_ans = ans;

    return;
}

signed main() {
    srand(20051104);
    srand(rand());

    n = read(), m = read(), k = read();

    if(m + k >= n) {
        puts("0");
        return 0;
    }

    for(int i = 1; i <= n; ++i) {
        to[i] = read();
        to[i]++;
    }

    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= n; ++j)
            if(i != j)
                val[i][j] = Inf;
            else
                val[i][j] = 0;

    for(int i = 1; i <= n; ++i) {
        int v = read();
        val[i][to[i]] = val[to[i]][i] = min(val[to[i]][i], v);
    }
    
    for(int i = 1; i <= m; ++i) {
        int u = read();
        u++;
        vis[u] = true;
    }

    for(int o = 1; o <= n; ++o) {
        for(int i = 1; i <= n; ++i) {
            for(int j = 1; j <= n; ++j) 
                if(i == j)
                    continue;
                else
                    val[i][j] = min(val[i][j], val[i][o] + val[o][j]);
        }
    }

    V.push_back(0);

    for(int i = 1; i <= n; ++i) {
        if(vis[i]) continue;
        V.push_back(i);
    }

    int len = V.size() - 1;
    int j = min(len, k);

    for(int i = 1; i <= j; ++i) {
        if(!vis[V[i]])
            vis[V[i]] = true;
    }
    
    min_ans = Ans();

    do
        Sa();
    while((double)clock() / CLOCKS_PER_SEC <= 0.7);

    printf("%d\n", min_ans);

    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
