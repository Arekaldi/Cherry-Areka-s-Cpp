#include <bits/stdc++.h>

using namespace std;

#define RE register

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

const int maxn = 1e6 + 1, maxm = 1e7 + 1;

queue <int> Q;

struct Trie_Tree {
	int ch[26], val, fail;
	// Val may be the tag for the end : Yes!
}pot[maxn];
int cnt;
int id[maxn];

class AC_Auto_Machine {
	public :
	void Insert(char *s, int x) {
		int len = strlen(s), now = 0;
		for(int i = 0; i < len; ++i) {
			pot[now].ch[s[i] - 'a'] = pot[now].ch[s[i] - 'a'] == 0 ? ++cnt : pot[now].ch[s[i] - 'a'];
			now = pot[now].ch[s[i] - 'a'];
		}
		// pot[now].val++;
        id[x] = now;
	}
	void Build_Fail() {
		for(int i = 0; i < 26; ++i)
			if(pot[0].ch[i]) {
				pot[pot[0].ch[i]].fail = 0;
				Q.push(pot[0].ch[i]);
			}
			
		while(!Q.empty()) {
			int u = Q.front(); Q.pop();
			for(int i = 0; i < 26; ++i) {
				if(pot[u].ch[i]) {
					pot[pot[u].ch[i]].fail = pot[pot[u].fail].ch[i];
					Q.push(pot[u].ch[i]);
				}
				else pot[u].ch[i] = pot[pot[u].fail].ch[i];
			}
		}
	}
	int Ask(char *s) {
		int len = strlen(s), now = 0, ans = 0;
		for(int i = 0; i < len; ++i) {
			now = pot[now].ch[s[i] - 'a'];
			for(int j = now; j and pot[j].val != -1; j = pot[j].fail) {
				ans += pot[j].val;
				pot[j].val = -1;
			}
		}
		return ans;
	}
}Trie;

int n;
char smod[maxn], stxt[maxn];

struct Node {
	int nxt, to;
}E[maxm];

int head[maxn], toto;
int sum[maxn];


void Add_edge(int u, int v) {
    E[++toto].nxt = head[u];
    head[u] = toto;
    E[toto].to = v;
}

void dfs(int v) {
    for(int i = head[v]; i; i = E[i].nxt) {
        int s = E[i].to;
        dfs(s);
        sum[v] += sum[s];
    }
}

signed main() {
	n = read();
	for(int i = 1; i <= n; ++i) {
		cin >> (smod);
		Trie.Insert(smod, i);
	}
	
	Trie.Build_Fail();

    cin >> (stxt);
    int k = 0;
    for(int i = 0; stxt[i]; ++i) {
        k = pot[k].ch[stxt[i] - 'a'];
        sum[k]++;
    }
	
	for(int i = 1; i <= cnt; ++i) {
        Add_edge(pot[i].fail, i);
    }

    dfs(0);
    for(int i = 1; i <= n; ++i) 
        cout << sum[id[i]] << endl;
    
    return 0;

	// cin >> (stxt);
	// printf("%d\n", Trie.Ask(stxt));
}