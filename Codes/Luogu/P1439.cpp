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

const int SIZE = 1e5 + 10;

int a[SIZE], b[SIZE], n;
int dp[5][SIZE];

signed main() {
	n = read();
	for(int i = 1; i <= n; ++i) 
		a[i] = read();
	for(int i = 1; i <= n; ++i) 
		b[i] = read();
//	int p = n & 1;
	for(int i = 1; i <= n; ++i) {
		int p = i & 1;
		for(int j = 1; j <= n; ++j) {
			if(a[i] != b[j]) dp[p][j] = max(dp[p ^ 1][j], dp[p][j - 1]);
			else 
				dp[p][j] = max(dp[p][j], dp[p ^ 1][j - 1] + 1);
		}
//		p ^= 1;
	}
	cout << dp[(n & 1)][n] << endl;
}
