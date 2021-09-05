#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}


const int maxn = 1e7 + 1, maxm = 1e7 + 1;

bool vis[maxn];
int n, k, A, B, C;
int head[maxn], dis[maxn], tot;
class Edge {
    public :
        int to, val, nxt;
}E[maxm];

inline void Add_edge(int u, int v, int w) {
    E[++tot].to = v, E[tot].val = w, E[tot].nxt = head[u];
    head[u] = tot;
}

inline int id(int i, int j, int k) {
    return (i - 1) * n + j + (k - 1) * n * n;
}

// inline int id(int i, int j) {
//     return (i - 1) * n + j;
// }

class Node {
    public :
        int v, val;
        Node(int V, int Val) : v(V), val(Val) {}
        friend bool operator < (const Node a, const Node b) {
            return a.val > b.val;
        }
};

priority_queue <Node, vector <Node> > Q;

inline int Dij() {
    int s = 1;
    memset(dis, 0x7f, sizeof(dis));
    dis[s] = 0;
    Q.push(Node(s, 0));
    while(!Q.empty()) {
        Node u = Q.top();
        Q.pop();
        if(vis[u.v])
            continue;
        int v = u.v, val = u.val;
        vis[v] = true;
        for(int i = head[v]; i; i = E[i].nxt) {
            int y = E[i].to;
            if(dis[y] > dis[v] + E[i].val) {
                dis[y] = dis[v] + E[i].val;
                Q.push(Node(y, dis[y]));
            }
        }
    }

    int ans = (1 << 30);
    for(int i = 1; i <= k + 1; ++i)
        ans = min(ans, dis[n * n * i]);
    
    return ans;
}

// #define add Add_edge

signed main() {
    n = read(), k = read(), A = read(), B = read(), C = read();

    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= n; ++j) {
            int p = read();
            if(p) {
                for(int u = 2; u <= k + 1; ++u)  
                    Add_edge(id(i, j, u), id(i, j, 1), A);

                if(i < n)
                    Add_edge(id(i, j, 1), id(i + 1, j, 2), 0);
                if(j < n)
                    Add_edge(id(i, j, 1), id(i, j + 1, 2), 0);
                if(i > 1)
                    Add_edge(id(i, j, 1), id(i - 1, j, 2), B);
                if(j > 1)
                    Add_edge(id(i, j, 1), id(i, j - 1, 2), B);
            }
            else {
                for(int u = 1; u <= k; ++u) {
                    Add_edge(id(i, j, u), id(i, j, 1), A + C);
                    if(i < n)
                        Add_edge(id(i, j, u), id(i + 1, j, u + 1), 0);
                    if(j < n)
                        Add_edge(id(i, j, u), id(i, j + 1, u + 1), 0);
                    if(i > 1)
                        Add_edge(id(i, j, u), id(i - 1, j, u + 1), B);
                    if(j > 1)
                        Add_edge(id(i, j, u), id(i, j - 1, u + 1), B);
                }
                Add_edge(id(i, j, k + 1), id(i, j, 1), A + C);
            }
        }
    }
    
// for(int i=1;i<=n;i++) {
// 		for(int j=1;j<=n;j++) {
// 			bool flag;
// 			cin>>flag;
// 			if(flag) {
// 				int now=id(i,j);
// 				for(int t=1;t<=k;t++) add(now+t*n*n,now,A);
// 				if(i<n) add(now,id(i+1,j)+n*n,0);
// 				if(j<n) add(now,id(i,j+1)+n*n,0);
// 				if(i>1) add(now,id(i-1,j)+n*n,B);
// 				if(j>1) add(now,id(i,j-1)+n*n,B);
// 			}
// 			else {
// 				int now=id(i,j);
// 				for(int t=0;t<k;t++) {
// 					add(now+t*n*n,now,C+A);
// 					if(i<n) add(now+t*n*n,id(i+1,j)+(t+1)*n*n,0);
// 					if(j<n) add(now+t*n*n,id(i,j+1)+(t+1)*n*n,0);
// 					if(i>1) add(now+t*n*n,id(i-1,j)+(t+1)*n*n,B);
// 					if(j>1) add(now+t*n*n,id(i,j-1)+(t+1)*n*n,B);
// 				}
// 				add(now+k*n*n,now,A+C);
// 			}
// 		}
// 	}

    printf("%d\n", Dij());

    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
