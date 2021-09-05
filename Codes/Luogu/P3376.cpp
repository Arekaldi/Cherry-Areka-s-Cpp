#include <bits/stdc++.h>

using namespace std;

#define RE register
const int maxn = 201, maxm = 100001;
#define int long long

inline int read() {
	RE int x = 0, f = 1;
	RE char ch = getchar();
	while(ch < '0' or ch > '9') {
		f = ch == '-' ? -1 : f;
		ch = getchar();
	}
	while(ch >= '0' and ch <= '9') {
		x = (x << 1) + (x << 3) + (ch ^48);
		ch = getchar();
	}
	return x * f;
}

struct edge {
    int to, val, next;
}E[maxm];

int n, m, s, t;

int tot = -1, dis[maxn], head[maxn];
int cur[maxm];

void Add_edge(int u, int v, int w) {
	E[++tot].to = v, E[tot].val = w, E[tot].next = head[u];
	head[u] = tot;
}

queue <int> Q;
bool Bfs(int s, int t) {
	memset(dis, -1, sizeof(dis));
	
	while(!Q.empty()) Q.pop();
	
	Q.push(s); dis[s] = 0;
	
	while(!Q.empty()) {
		int x = Q.front(); Q.pop();
		
		for(int i = head[x]; i > -1; i = E[i].next) {
			int v = E[i].to;
			if(dis[v] == -1 and E[i].val) {
				dis[v] = dis[x] + 1;
				Q.push(v);
			}
		}
	}
	
	return dis[t] != -1;
}

int Dfs(int x, int flew, int t) {
	if(x == t) return flew;
	
	int rest = flew;
	
	for(int i = cur[x]; i > -1 && rest; i = E[i].next) {
		int v = E[i].to, f = E[i].val;
		
		cur[x] = i;
		
		if(!f or dis[v] != dis[x] + 1) continue;
		
		int k = Dfs(v, min(rest, f), t);
		E[i].val -= k, E[i ^ 1].val += k;
		rest -= k;
		
		if(!k) dis[v] = 0;
	}
	return flew - rest;
}

int Dinic(int s, int t) {
	int ans = 0, k;
	while(Bfs(s, t)) {
		// memcpy(cur, head, sizeof(head));
        for(int i = s; i <= t; ++i) cur[i] = head[i];
		k = Dfs(s, INT_MAX, t);
		ans += k;
	}
	return ans;
}

signed main() {
	n = read(), m = read(), s = read(), t = read();
	memset(head, -1, sizeof(head));
	for(int i = 1; i <= m; ++i) {
		int u = read(), v = read(), w = read();
		Add_edge(u, v, w);
		Add_edge(v, u, 0);
	}
	
	printf("%lld\n", Dinic(s, t));
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}