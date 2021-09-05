#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

const int maxn = 1e5 + 1;

int n, tot, a[maxn];
bool vis[500001];

class Tree_Array {
    private:
        int t[maxn];
        
        inline int lowbit(int x) {
            return x & (-x);
        }
    
    public:
        
        inline void init() {
            memset(t, 0, sizeof(t));
        }

        inline void Add(int pos, int v) {
            while(pos <= n)
                t[pos] += v, pos += lowbit(pos);
        }

        inline int Ask(int pos) {
            int res = 0;
            while(pos)
                res += t[pos], pos -= lowbit(pos);
            return res;
        }
};

Tree_Array T;

class Node {
    public:
        int id, nid, tm;
        inline friend bool operator < (const Node &a, const Node &b) {
            if(a.id == b.id)
                return a.tm > b.tm;
            else
                return a.id > b.id;
        }
        Node() {}
        Node(int i, int i1, int t) : id(i), nid(i1), tm(t) {}
};

class Node1 {
    public:
        int id, nid, tm;
        inline friend bool operator < (const Node1 &a, const Node1 &b) {
            if(a.tm == b.tm)
                return a.id > b.id;
            else
                return a.tm > b.tm;
        }
        Node1() {}
        Node1(int i, int i1, int t) : id(i), nid(i1), tm(t) {}
};

class Node2 {
    public:
        int nid, tm;
        Node2() {}
        Node2(int i1, int t) : nid(i1), tm(t) {}
};

priority_queue <Node> Q1;
priority_queue <Node1> Q2;

deque <Node2> v[maxn];

inline void init() {
    tot = 0;
    memset(vis, 0, sizeof(vis));
    while(!Q1.empty())
        Q1.pop();
    while(!Q2.empty())
        Q2.pop();
    for(int i = 1; i < maxn; ++i)
        while(!v[i].empty())
            v[i].pop_front();
    T.init();
}
signed main() {
    int ss = read();
    while(ss--) {
        init();
        n = read();
        for(int i = 1; i <= n; ++i)
            a[i] = read();
        int Qs = read();
        for(int i = 1, id; i <= Qs; ++i) {
            int t = read(), opt = read();
            while(!Q2.empty() and Q2.top().tm <= t) {
                Node1 x = Q2.top();
                Q2.pop();
                if(vis[x.nid])
                    continue;
                Node pp;
                pp.id = x.id, pp.nid = x.nid, pp.tm = x.tm;
                Q1.push(pp);
                T.Add(x.id, 1);
            }

            if(opt == 0) {
                id = read();
                Q2.push(Node1(id, ++tot, a[id] + t));
                v[id].push_back(Node2(tot, a[id] + t));
            }

            if(opt == 1) {
                if(Q1.empty())
                    puts("Yazid is angry.");
                else {
                    Node x;
                    x.id = -1;
                    while(!Q1.empty()) {
                        x = Q1.top();
                        Q1.pop();
                        if(vis[x.nid])
                            continue;
                        break;
                    }
                    if(x.id == -1 or v[x.id].empty() or vis[x.nid])
                        puts("Yazid is angry.");
                    else {
                        T.Add(x.id, -1);
                        v[x.id].pop_front();
                        vis[x.nid] = true;
                        printf("%d\n", x.id);
                    }
                }
            }

            if(opt == 2) {
                id = read();
                if(v[id].empty())
                    puts("YJQQQAQ is angry.");
                else {
                    deque <Node2> :: iterator it = v[id].begin();
                    Node2 x = *it;
                    if(x.tm > t)
                        printf("%d\n", x.tm - t);
                    else {
                        vis[x.nid] = true;
                        T.Add(id, -1);
                        v[id].pop_front();
                        puts("Succeeded!");
                    }
                }
            }

            if(opt == 3) {
                int l = read(), r = read();
                printf("%d\n", T.Ask(r) - T.Ask(l - 1));
            }
        }
    }

	init();

    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
