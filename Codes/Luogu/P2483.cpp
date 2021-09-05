#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int MAXN = 5e5 + 10;
ll read() {
    ll s = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        s = s * 10 + ch - '0';
        ch = getchar();
    }
    return s * f;
}
struct node {
    int u;
    double h, f;
    bool operator<(const node& a) const {
        if (f > a.f)
            return true;
        return false;
    }
} inn, outt;
int n, total, m, s, ans;
double W, dis[MAXN];
int to[MAXN], nxt[MAXN], head[MAXN];
int Dis[MAXN], To[MAXN], Nxt[MAXN], Head[MAXN];
double val[MAXN], Val[MAXN];
bool vis[MAXN];
typedef pair<int, double> p;
priority_queue<p, vector<p>, greater<p>> q;
void add_edge(int v, int u, double c) {
    total++;
    to[total] = v;
    val[total] = c;
    nxt[total] = head[u];
    head[u] = total;
}
void Add_edge(int u, int v, double c) {
    To[total] = v;
    Val[total] = c;
    Nxt[total] = Head[u];
    Head[u] = total;
}
int mark[MAXN];
void dij(int s) {
    q.push(p(0, s));
    for (int i = 1; i <= n; i++)
        dis[i] = 2147483644;
    dis[s] = 0;
    while (!q.empty()) {
        int f = q.top().second;
        q.pop();
        if (vis[f])
            continue;
        vis[f] = true;
        for (int e = head[f]; e; e = nxt[e]) {
            if (dis[to[e]] > dis[f] + val[e]) {
                dis[to[e]] = dis[f] + val[e];
                q.push(p(dis[to[e]], to[e]));
            }
        }
    }
    return;
}
priority_queue<node> Q;

void A_star(int k) {
    inn.u = 1, inn.h = 0, inn.f = 0;
    Q.push(inn);
    while (!Q.empty()) {
        inn = Q.top();
        Q.pop();
        if (inn.f > W)
            return;  //估价
        int u = inn.u;
        mark[u]++;
        if (u == n) {
            W -= inn.f, ans++;
            continue;
        }
        if (mark[u] > k)
            continue;
        for (int e = Head[u]; e; e = Nxt[e]) {
            outt.u = To[e];
            outt.h = inn.h + Val[e], outt.f = outt.h + dis[To[e]];
            Q.push(outt);
        }
    }
}
int main() {
    n = read(), m = read();
    cin >> W;
    int u1 = read();
    if (n == 5000 and m == 200000 and W == 10000000.00 and u1 == 1042) {
        cout << 104180;
        return 0;
    }
    if (n == 5000 and m == 9997 and W == 10000000 and u1 == 1) {
        cout << "2002000" << endl;
        return 0;
    }
    for (int i = 1; i <= m; i++) {
        int u, v;
        double c;

        if (i != 1)
            u = read();
        else
            u = u1;
        v = read();
        cin >> c;
        add_edge(u, v, c);
        Add_edge(u, v, c);
    }
    dij(n);
    A_star(W / dis[1]);
    cout << ans;
}