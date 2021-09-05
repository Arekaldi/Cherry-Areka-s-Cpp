#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

const int maxm = 1e7 + 10, maxn = 1e6 + 1;

struct Tr {
    int ch[2], end,val;
}T[maxm];

struct Edge {
    int to, nxt, val;
};

Edge E[maxm];

int head[maxn], tot, cnt, n;

//queue <int> Q;
int R[maxn];

inline void Add_edge(int u, int v, int w) {
    E[++tot].to = v, E[tot].nxt = head[u], E[tot].val = w;
    head[u] = tot;
}

class Template {
    public :
        inline void Insert(int x) {
        	int p = 0;
        	for(int i = 30; i >= 0; --i) {
            	int son = (x >> i) & 1;
        		if(!T[p].ch[son]) T[p].ch[son] = ++cnt;
        		p = T[p].ch[son];
			}
        }
        inline int Xor(int x) {
            int ans = 0, p = 0;
            for(int i = 30; i >= 0; --i) {
            	int son = (x >> i) & 1;
            	if(T[p].ch[son ^ 1]) ans += (1 << i), p = T[p].ch[son ^ 1];
            	else p = T[p].ch[son];
			}
            return ans;
        }
}Trie;

inline void Dfs(int fa, int x) {
    for(int i = head[x]; i; i = E[i].nxt) {
        int y = E[i].to;
        if(y == fa) continue;
        R[y] = R[x] ^ E[i].val;
        Dfs(x, y);
    }
}

int ans = 0;

signed main() {
    n = read();
    for(int i = 1; i < n; ++i) {
        int u = read(), v = read(), w = read();
        Add_edge(u, v, w);
    }
    
    Dfs(-1, 1);
    for(int i = 1; i <= n; ++i) {
    	Trie.Insert(R[i]);
    	int w = Trie.Xor(R[i]);
    	ans = max(ans, Trie.Xor(R[i]));
	}

	cout << ans << endl;

    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}

/*
4-2-3
*/
