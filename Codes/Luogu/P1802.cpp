#include <bits/stdc++.h>

using namespace std;

#define int long long

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

const int maxn = 1001;

int n, x, le[maxn], wn[maxn], w[maxn];
int f[maxn][maxn];

signed main() {
	n = read(), x = read();
	for(int i = 1; i <= n; ++i) 
		le[i] = read(), wn[i] = read(), w[i] = read();
		
	for(int i = 1; i <= n; ++i) 
		for(int j = 0; j <= x; ++j) {
			f[i][j] = max(f[i][j], f[i - 1][j] + le[i]);
			if(j >= w[i])
				f[i][j] = max(f[i][j], f[i - 1][j - w[i]] + wn[i]);
		}
			
	
	for(int j = x; j >= 0; --j)
		if(f[n][j]) {
			cout << f[n][j] * 5 << endl;
			return 0;
		}
}
