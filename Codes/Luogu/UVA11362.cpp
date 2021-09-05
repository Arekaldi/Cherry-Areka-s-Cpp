#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

const int maxm = 1e7 + 10, maxn = 1e5 + 2;

struct Node {
    int ch[10], end;
}T[maxm];
int tot;
int n, l;

class Tree {
    public :
        void Insert(char *s) {
            int p = 0;
            for(int i = 0; s[i]; ++i) {
                int x = s[i] - '0';
                if(!T[p].ch[x]) T[p].ch[x] = ++tot;
                p = T[p].ch[x];
            }
            T[p].end = 1;
        }
        bool Ask(int p) {
            if(T[p].end) 
                for(int i = 0; i <= 9; ++i) if(T[p].ch[i]) return true;
            for(int i = 0; i <= 9; ++i) {
                if(T[p].ch[i]) return Ask(T[p].ch[i]);
            }
        }
}Trie;

char s[maxn][11];

queue <bool> Q;

signed main() {
    l = read();
    while(l--) {
        memset(T, 0, sizeof(T));
        for(int i = 1; i <= n; ++i) cout << T[i].end << endl;
        memset(s, 0, sizeof(s));
        n = read();
        for(int i = 1; i <= n; ++i) {
            scanf("%s", s[i]);
            Trie.Insert(s[i]);
        }
        Q.push(Trie.Ask(0));
    }
    
    while(Q.size() > 1) {
        cout << (Q.front() ? "NO" : "YES") << endl;
        Q.pop();
    }

    cout << (Q.front() ? "NO" : "YES");
    Q.pop();
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
