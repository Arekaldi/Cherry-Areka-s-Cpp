#include <bits/stdc++.h>

using namespace std;

inline int read() {
	int x = 0, f = 1;
	char ch = getchar();
	while(ch < '0' or ch > '9') {
		if(ch == '-') f = -1;
		ch = getchar();
	}
	while(ch >= '0' and ch <= '9') {
		x = (x << 1) + (x << 3) + (ch ^ 48);
		ch = getchar();
	}
	return x * f;
}

#define Rint register int

const int maxm = 1e7 + 5;

int n, m, T;

class Point {
	public :
		int Fa, V;
}P[maxm];

inline int Find(int x) {
	if(x != P[x].Fa) {
		int f = Find(P[x].Fa);
		P[x].V += P[P[x].Fa].V;
        return P[x].Fa = f;
	}
	else
        return x;
}

signed main() {

    T = read();

    for(Rint i = 1; i <= T; ++i) {

        bool flag = true;

        n = read(), m = read();
        for(Rint i = 0; i <= n; ++i)
            P[i].Fa = i, P[i].V = 0;
        
        for(Rint i = 1; i <= m; ++i) {
            int x = read(), y = read(), sum = read();

            x--;
            
            int f1 = Find(x), f2 = Find(y);

            if(f1 != f2) {
                P[f1].Fa = f2;
                P[f1].V = sum - P[x].V + P[y].V;
            }

            else if(P[x].V - P[y].V != sum) {
                flag = false;
                break;
            }
        }

        puts(flag ? "true" : "false");

        #ifndef ONLINE_JUDGE
            getchar();
        #endif
    }

}
