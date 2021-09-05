#include <bits/stdc++.h>

using namespace std;

#define RE register

inline int read()
{
    RE int x = 0, f = 1;
    RE char ch = getchar();
    while (ch < '0' or ch > '9')
    {
        f = ch == '-' ? -1 : f;
        ch = getchar();
    }
    while (ch >= '0' and ch <= '9')
    {
        x = (x << 1) + (x << 3) + (ch ^ 48);
        ch = getchar();
    }
    return x * f;
}

const int maxn = 1e7 + 1, maxm = 1e6 + 1;

queue<int> Q;

struct Trie_Tree
{
    int ch[26], val, fail;
}pot[105001];
int cnt;
int id[151];

class AC_Auto_Machine
{
	public:
    void Insert(char *s, int x)
    {
        int len = strlen(s), now = 0;
        for (int i = 0; i < len; ++i)
        {
            pot[now].ch[s[i] - 'a'] = pot[now].ch[s[i] - 'a'] == 0 ? ++cnt : pot[now].ch[s[i] - 'a'];
            now = pot[now].ch[s[i] - 'a'];
        }
        id[x] = now;
    }
    void Build_Fail()
    {
        for (int i = 0; i < 26; ++i)
            if (pot[0].ch[i])
            {
                pot[pot[0].ch[i]].fail = 0;
                Q.push(pot[0].ch[i]);
            }

        while (!Q.empty())
        {
            // cout << 1 << endl;
            int u = Q.front();
            Q.pop();
            for (int i = 0; i < 26; ++i)
            {
                if (pot[u].ch[i])
                {
                    pot[pot[u].ch[i]].fail = pot[pot[u].fail].ch[i];
                    Q.push(pot[u].ch[i]);
                }
                else
                    pot[u].ch[i] = pot[pot[u].fail].ch[i];
            }
        }
        // cout << 1 << endl;
    }
    int Ask(char *s)
    {
        int len = strlen(s), now = 0, ans = 0;
        for (int i = 0; i < len; ++i)
        {
            now = pot[now].ch[s[i] - 'a'];
            for (int j = now; j and pot[j].val != -1; j = pot[j].fail)
            {
                ans += pot[j].val;
                pot[j].val = -1;
            }
        }
        return ans;
    }
} Trie;

int n, ppp;
char smod[71], stxt[maxm];
string a[151];

struct Node
{
    int nxt, to;
}E[maxm];

int head[105001], toto;
int sum[105001];

void Add_edge(int u, int v)
{
    E[++toto].nxt = head[u];
    head[u] = toto;
    E[toto].to = v;
}

void dfs(int v)
{
    for (int i = head[v]; i; i = E[i].nxt)
    {
        int s = E[i].to;
        dfs(s);
        sum[v] += sum[s];
    }
}

void init() {
    memset(sum, 0, sizeof(sum));
    memset(head, 0, sizeof(head));
    memset(id, 0, sizeof(id));
    memset(pot, 0, sizeof(pot));
    memset(E, 0, sizeof(E));
    memset(pot, 0, sizeof(pot));
    cnt = toto = ppp = 0;
//    for(int i = 0; i < maxn; ++i) {
//        for(int j = 0; j < 26; ++j) pot[i].ch[j] = 0;
//        pot[i].val = pot[i].fail = 0;
//    }
}

queue <string> q;

signed main()
{
    n = 1;
    while (n)
    {
        n = read();
        if(!n) return 0;
        init();
        for (int i = 1; i <= n; ++i)
        {
            cin >> smod;
            a[++ppp] = smod;
            Trie.Insert(smod, i);
        }
        
        Trie.Build_Fail();


        cin >> stxt;
        int k = 0;
        for (int i = 0; stxt[i]; ++i)
        {
            k = pot[k].ch[stxt[i] - 'a'];
            sum[k]++;
        }


        for (int i = 1; i <= cnt; ++i)
        {
            Add_edge(pot[i].fail, i);
        }

        dfs(0);

        int maxh = 0, ans = 0;
        for (int i = 1; i <= n; ++i)
            maxh = max(maxh, sum[id[i]]);

        cout << maxh << endl;
        for (int i = 1; i <= n; ++i)
        {
            if (sum[id[i]] == maxh)
                ans++, q.push(a[i]);
        }

        // cout << q.size() << endl;
        // cout << ans << endl;
        while (!q.empty())
        {
            string sp = q.front();
            // cout << q.front() << endl;
            q.pop();
            cout << sp << endl;
        }
    }

    // cout << sum[id[i]] << endl;

    return 0;

    // cin >> (stxt);
    // printf("%d\n", Trie.Ask(stxt));
}
