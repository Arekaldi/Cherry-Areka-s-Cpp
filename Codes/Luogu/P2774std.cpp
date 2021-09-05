//Dinic 理解代价低 
#include <cstdio>
#include <cctype>
#include <cstring>
#include <queue>
#define N 10010
#define E 100010
#define S 0
#define T (m * n + 1)
#define code(i, j) ((i - 1) * m + j)//点的线性标号 
#define between(x, flo, top) (flo <= x and x <= top)//您是不是不喜欢这个qwq 
int getint() {
	int res = 0, ch = getchar();
	while (!isdigit(ch) and ch != EOF)
		ch = getchar();
	while (isdigit(ch))
		res = res * 10 + (ch - '0'), ch = getchar();
	return res;
}
inline int min(int x, int y) { return (x < y) ? x : y; }
using std::queue;
const int d[4][2] = {//待会枚举四个方向用的 
	{0, 1},
	{0, -1},
	{1, 0},
	{-1, 0}
};

int m, n;
int sum = 0;

int first[N];
int nxt[E], to[E], val[E], cnt = 1;
void addE(int u, int v, int w) {
	++cnt;
	to[cnt] = v;
	val[cnt] = w;
	nxt[cnt] = first[u];
	first[u] = cnt;
}

int dep[N];
queue<int> q;
bool bfs() {
	memset(dep, 0, sizeof(dep));
	
	dep[S] = 1;
	q.push(S);
	while (not q.empty()) {
		int u = q.front();
		q.pop();
		for (int p = first[u]; p; p = nxt[p]) {
			int v = to[p];
			if (dep[v])
				continue;
			if (val[p]) {//放心，开始都是正权的情况下，不会出现负数的 
				dep[v] = dep[u] + 1;
				q.push(v);
			}
		}
	}
	return dep[T];
}

int dfs(int u, int in) {
	if (u == T)
		return in;
	int out = 0;
	for (int p = first[u]; p and in; p = nxt[p]) {
		
		if (val[p] == 0)
			continue;
		int v = to[p];
		if (dep[v] != dep[u] + 1)
			continue;
		
		int res = dfs(v, min(val[p], in));
		val[p] -= res;
		val[p ^ 1] += res;
		in -= res;
		out += res;
	}
	
	return out;
}

int main() {
	n = getint(), m = getint();
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j) {
			int w = 0;
			sum += w = getint();//假定全部都取，随后会删 
			if ((i + j) % 2 == 0) {//阵营A，源点连向自己，自己连向阵营B 
				addE(S, code(i, j), w);
				addE(code(i, j), S, 0);
				
				for (int k = 0; k <= 3; ++k) {
					int x = i + d[k][0], y = j + d[k][1];
					if (between(x, 1, n) and between(y, 1, m)) {
						addE(code(i, j), code(x, y), 2e9);
						addE(code(x, y), code(i, j), 0);
					}
				}				
			}
			else {//阵营B，连向汇点 
				addE(code(i, j), T, w);
				addE(T, code(i, j), 0);
			}
		}
	
	int cut = 0;//最小割 
	while (bfs())
		cut += dfs(S, 2e9);//最小割 = 最大流 
	printf("%d\n", sum - cut);
	return 0;
}
