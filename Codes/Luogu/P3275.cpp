#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

const int maxm = 5e6 + 1;

#define int long long

int n, m;
class Edge {
    public :
        int to, nxt, val;
}E[maxm];

int head[maxm], tot;
inline void Add_edge(int u, int v, int w) {
    E[++tot].to = v, E[tot].nxt = head[u], E[tot].val = w;
    head[u] = tot;
}

int cnt[maxm], dis[maxm];
bool inq[maxm];
deque <int> Q;

inline bool SPFA() {
    inq[0] = true, Q.push_back(0);
    dis[0] = 0;
    while(!Q.empty()) {
        int x = Q.front();
        Q.pop_front();
        inq[x] = false;
        for(int i = head[x]; i; i = E[i].nxt) {
            int v = E[i].to;
            // cout << dis[v] << " " << dis[x] + E[i].val << endl;
            if(dis[v] < dis[x] + E[i].val) {
                dis[v] = dis[x] + E[i].val;
                cnt[v]++;
                if(cnt[v] >= n + 1) return false;
                if(!inq[v]) {
                    inq[v] = true;
                    if(!Q.empty() and dis[v] > dis[Q.front()])
                        Q.push_front(v);
                    else
                        Q.push_back(v);
                }
            }
        }
    }
    return true;
}

signed main() {
    n = read(), m = read();
    for(int i = 1; i <= m; ++i) {
        int Tp = read(), a = read(), b = read();
        switch(Tp) {
            case 1 : {
                // a = b a <= b + 0 and b <= a + 0
                Add_edge(a, b, 0);
                Add_edge(b, a, 0);
                break;
            }
            case 2 : {
                // a <= b - 1 b >= a + 1
                Add_edge(a, b, 1);
                break;
            }
            case 3 : {
                // a >= b b -> a, 0
                Add_edge(b, a, 0);
                break;
            }
            case 4 : {
                // a > b a >= b + 1
                Add_edge(b, a, 1);
                break;
            }
            case 5 : {
                // a <= b b >= a + 0
                Add_edge(a, b, 0);
                break;
            }
        }
    }
    
    for(int i = n; i >= 1; --i)
        Add_edge(0, i, 1);

    if(SPFA()) {
        int ans = 0;
        for(int i = 1; i <= n; ++i) 
            // cout << dis[i] << endl;
            ans += dis[i];
        printf("%lld\n", ans);
    }
    else puts("-1");
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
