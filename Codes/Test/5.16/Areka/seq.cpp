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

#define int long long

const int maxm = 1e6 + 5;

int n, m, Mod;

class Answer {
	public :
		int l, r, sum;
}Q[maxm];

class Point {
	public :
		int Fa, V;
}P[maxm];

inline int Find(int x) {
	if(x != P[x].Fa) {
		int f = Find(P[x].Fa);
		P[x].V += P[P[x].Fa].V;
        P[x].V %= Mod;
        return P[x].Fa = f;
	}
	else
        return x;
}

signed main() {
	freopen("seq.in", "r", stdin);
	freopen("seq.out", "w", stdout);

	n = read(), m = read(), Mod = read();
	
	for(Rint i = 0; i <= n; ++i)
		P[i].Fa = i;
	
	for(Rint i = 1; i <= m; ++i) {
		int x = read(), y = read(), sum = read();

		x--;
		
        int f1 = Find(x), f2 = Find(y);

        // if(x == 1)
        //     cout << f1 << endl;

		if(f1 != f2) {
            P[f1].Fa = f2;
            P[f1].V = (sum - P[x].V + P[y].V + Mod) % Mod;
            // cout << f1 << " " << P[f1].V << endl;
		}
		
		else if((P[x].V - P[y].V + Mod) % Mod != sum % Mod) {
            
            // cout << P[x].V << " " << P[y].V << endl;

			cout << i - 1 << endl;

            #ifndef ONLINE_JUDGE
                getchar();
            #endif
            return 0;
		}
	}
	
	cout << m << endl;

	#ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
