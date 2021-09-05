#include <bits/stdc++.h>

using namespace std;

#define low x & (-x)

inline int read() {
    register int x = 0, f = 1;
    register char ch
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}


const int maxn = 1e6 + 1, maxm = 1e7 + 1;

struct Trie_Tree {
    int ch[26], val, fail;
}pot[maxn];
int cnt;

class AC_Auto_Machine {
    public :
        void Insert(char *s) {
            int len = strlen(s), now = 0;
            for(int i = 0; i < len; ++i) {
                pot[now].ch[s[i] - 'a'] = pot[now].ch[s[i] - 'a'] == 0 ? ++cnt : pot[now].ch[s[i] - 'a'];
                now = pot[now].ch[s[i] - 'a'];
            }
        }
        void Build_Fail() {
            queue <int> Q;

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
}Trie;

int n, m;

string stx;

struct Edge {
    int to, int nxt;
}E[maxm];

int head[maxn], cntt;

void Add_edge(int u, int v) {
    E[++cntt].to = v;
    E[tott].nxt = head[u];
    head[u] = tott;
}

int dfn[maxn];
void Dfs(int x) {
    for(int i = head[x]; i; i = E[i].nxt) {
        int y = E[i].to;
        if(!dfn[y]) {
            dfn[y] = dfn[x] + 1;
            Dfs(y);
        }
    }
}

struct Ques {
    int x, int y;
}Q[maxn];

bool comp(Ques a, Ques b) {
    return a.y < b.y;
}

signed main() {
    getline(cin, stx);

    string t;
    for(int i = 0; stx[i]; ++i) 
        if(stx[i] != 'P' and stx[i] != 'B') t += stx[i];

    Trie.Insert(st, 0);

    Trie.Build_Fail();

    for(int i = 0; i <= cnt; ++i)
        Add_edge(pot[i].fail, i);
    
    m = read();
    for(int i = 1; i <= m; ++i) 
        Q[i].x = read(), Q[i].y = read();
    
    sort(Q + 1, Q + m + 1, comp);

    for(int i = )


    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
