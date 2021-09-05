#include <bits/stdc++.h>

using namespace std;

inline int read() {
	int x = 0, f = 1;
	char ch = getchar();
	while(ch < '0' or ch > '9') {
		f = ch == '-' ? -1 : 1;
		ch = getchar();
	}
	while(ch >= '0' and ch <= '9') {
		x = (x << 1) + (x << 3) + (ch ^ 48);
		ch = getchar();
	}
	return x * f;
}

const int maxn = 5e4 + 1;

int dfn[maxn], low[maxn];
int ind;
int s[maxn], top;
int cnt_scc;
int scc[maxn], cntscc[maxn];

bool in[maxn];

struct Edge {
	int to, next;
}e[maxn];

int h[maxn];
int tot;
void add_edge(int u, int v) {
	e[++tot].to = v; e[tot].next = h[u]; h[u] = tot;
}

inline int Min(int a, int b) {
    if(a <= b)
        return a;
    else 
        return b;
}

void Tarjan(int x) {
	dfn[x] = ++ind;
	low[x] = dfn[x];
	s[top++] = x;
	in[x] = true;
	for(int i = h[x]; i; i = e[i].next) {
		int v = e[i].to;
		if(!dfn[v]) {
			Tarjan(v);
			low[x] = Min(low[x], low[v]);
		}
		else {
			if(in[v]) {
				low[x] = Min(low[x], dfn[v]);
			}
		}
	}
	if(dfn[x] == low[x]) {
		cnt_scc++;
		while(s[top] != x) {
			in[s[--top]] = false;
			scc[s[top]] = cnt_scc;
			cntscc[cnt_scc]++;
		}
	}
}

int n, m;
int out[maxn], Gin[maxn], ans;

int main() {

	n = read();
	for(int i = 1; i <= n; ++i) {
		int x = read();
		while(x) {
			if(!x) break;
			else add_edge(i,x);
			x = read();
		}
	}
	for(int i = 1; i <= n; ++i) {
		if(!dfn[i]) Tarjan(i);
	}
	for(int i = 1; i <= n; ++i) {
		for(int j = h[i]; j; j = e[j].next) {
			int v = e[j].to;
			if(scc[i] != scc[v]) {
				out[scc[i]]++;
				Gin[scc[v]]++;
			}
		}
	}
	//
	int ans1 = 0;
	for(int i = 1; i <= cnt_scc; ++i) 
		if(!Gin[i]) ans1++;
        
	cout << ans1;
    getchar();
	return 0;
}