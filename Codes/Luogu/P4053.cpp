#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

const int maxn = 1e6 + 1;

class Node {
    public:
        int cst, dap;
        inline bool operator < (const Node &g) const {
            return g.dap > dap;
        }
};

int n;
Node P[maxn];
priority_queue <int> q;

signed main() {
    n = read();
    for(int i = 1; i <= n; ++i)
        P[i].cst = read(), P[i].dap = read();
    
    sort(P + 1, P + n + 1);

    int now_t = 0, ans = 0;
	for(int i = 1; i <= n; ++i)
	{
		if(now_t + P[i].cst <= P[i].dap)
		{
			now_t += P[i].cst;
			q.push(P[i].cst);
			ans++;
		}
		else if(P[i].cst < q.top())
		{
			now_t += P[i].cst - q.top();
			q.pop();
			q.push(P[i].cst);
		}
	}

    printf("%d\n", ans);
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
