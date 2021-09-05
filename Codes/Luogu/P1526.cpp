#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

const int maxn = 1e4 + 1;
class Node {
	public:
		int x, y;
};

inline bool Judge(Node a, Node b, int k) {
	long long jl = (long long)((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
//	if(b.x == 1 and b.y == 5 and a.x == 6 and a.y == 0)
//		cout << a.x << " " << a.y << " " <<  b.x << " " << b.y << " " << jl << endl;
	return jl <= (long long)(k * k);
}

int m, n, k, res = (1 << 30);
Node a[maxn], b[maxn];
int f[maxn][maxn], g[maxn];
bool vis[maxn], dis[maxn][maxn];

inline void Dfs(int used, int Bom, int v) {
	res = min(res, used + g[Bom] + v);
	if(res <= used + g[Bom])
		return;
	if(Bom == m + 1) {
//			for(int i = 1; i <= n; ++i)
//				cout << vis[i] << " ";
//			cout << endl;
		res = min(res, used);
		return;
	}
	for(int i = 1; i <= n; ++i) {
		if(!vis[i] and dis[i][Bom]) {
			vis[i] = true;
			Dfs(used + 1, f[i][Bom], v);
			vis[i] = false;
		}
	}
}

signed main() {
	m = read(), n = read(), k = read();
	for(int i = 1; i <= m; ++i)
		a[i].x = read(), a[i].y = read();
	for(int i = 1; i <= n; ++i)
		b[i].x = read(), b[i].y = read();
	
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= m; ++j)
			dis[i][j] = Judge(b[i], a[j], k);
	
	for(int i = 1; i <= n; ++i) {
		for(int j = m; j >= 1; --j) {
			if(dis[i][j])
				f[i][j] = max(j + 1, f[i][j + 1]);
		}
//		if(i == 1) {
//			for(int j = 1; j <= m; ++j)
//				cout << f[i][j] << " ";
//			cout << endl;
//		}
	}
	
//	cout << Judge(a[3], b[1], k) << endl;
	
//	g[m] = 0;
//	memset(g, 0x3f, sizeof(g));
	for(int i = m; i >= 1; --i) {
//		g[i] = (1 << 30);
		g[i] = 110;
		for(int j = 1; j <= n; ++j)
			if(dis[j][i])
				g[i] = min(g[i], g[f[j][i]] + 1);
	}
	
	Dfs(0, 1, (n <= 15) ? 1000 : 0);
	
	printf("%d\n", res);
}
