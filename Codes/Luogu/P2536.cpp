#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

const int maxn = 5e5 + 1;

char ss[1010], s[510];

namespace Trie {
    inline int id(char ch) {
        if(ch == 'A')
            return 1;
        else if(ch == 'G')
            return 2;
        else if(ch == 'C')
            return 3;
        else if(ch == 'T')
            return 4;
        else if(ch == '*')
            return 5;
        else
            return 6;
    }

    class Tree {
        public:
            int ch[6], ed;
    };

    Tree T[maxn];
    int tot = 0, ans = 0;
    bool vis[1001][300001];

    inline void Insert(char *s) {
        int p = 0;
        for(int i = 0; s[i]; ++i) {
            int q = id(s[i]);
            if(T[p].ch[q])
                p = T[p].ch[q];
            else
                p = T[p].ch[q] = ++tot;
        }
        T[p].ed++;
    }


    inline void Dfs(int p, int q) {
        if(vis[p][q] == true)
            return;
        vis[p][q] = true;
        if(p == strlen(ss)) {
            ans += T[q].ed;
            return;
        }
        int now = id(ss[p]);
        if(now >= 1 and now <= 4) {
            if(T[q].ch[now])
                Dfs(p + 1, T[q].ch[now]);
            else
                return;
        }

        else if(now == 5) {
            Dfs(p + 1, q);
            for(int i = 1; i <= 4; ++i)
                if(T[q].ch[i]) {
                    Dfs(p + 1, T[q].ch[i]);
                    Dfs(p, T[q].ch[i]);
                }
            return;
        }

        else {
            for(int i = 1; i <= 4; ++i)
                if(T[q].ch[i])
                    Dfs(p + 1, T[q].ch[i]);
        }
    }
}

signed main() {
    scanf("%s", ss);
    int n = read();
    for(int i = 1; i <= n; ++i)
        scanf("%s", s), Trie :: Insert(s);
    
    Trie :: Dfs(0, 0);

    printf("%d\n", n - Trie :: ans);
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}