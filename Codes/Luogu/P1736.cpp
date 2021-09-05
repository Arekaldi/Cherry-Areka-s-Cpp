#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}


const int maxn = 2501;

int n, m;
int up[maxn][maxn], il[maxn][maxn], ir[maxn][maxn];
int f[2][maxn][2], s[maxn][maxn];
int ans = 0;

int main() {
	n = read(), m = read();
	for(int i = 1; i <= n; ++i) 
		for(int j = 1; j <= m; ++j) {
			s[i][j] = read();
			if(s[i][j]) up[i + 1][j] = i, il[i][j + 1] = j;
			else
				up[i + 1][j] = up[i][j], il[i][j + 1] = il[i][j];
		}
	
	for(int i = 1; i <= n; ++i) 
		for(int j = m; j >= 1; --j)
			if(j < m) ir[i][j] = s[i][j + 1] == 0 ? ir[i][j + 1] : j + 1;
			else ir[i][j] = m + 1;

	for(int j = 1; j <= m; ++j) if(s[1][j]) f[1][j][0] = f[1][j][1] = 1, ans = 1;
	for(int i = 2; i <= n; ++i) {
		for(int j = 1; j <= m; ++j) {
			if(s[i][j]) {
				f[i % 2][j][0] = min(min(j - il[i][j], i - up[i][j]), f[!(i % 2)][j - 1][0] + 1);
				f[i % 2][j][1] = min(min(ir[i][j] - j, i - up[i][j]), f[!(i % 2)][j + 1][1] + 1);
				ans = max(ans, max(f[i % 2][j][0], f[i % 2][j][1]));
			}
			else f[i % 2][j][0] = f[i % 2][j][1] = 0;
		}
	}

	
	// for(int i = 1; i <= n; ++i) {
		// for(int j = 1; j <= m; ++j) {
			// cout << f[i][j][0] << ", " << f[i][j][1] << "    ";
            // printf("%d, %d, %d  ", up[i][j], il[i][j], ir[i][j]);
		// }
		// cout << endl;
	// }
	
	cout << ans << endl;

    #ifndef ONLINE_JUDGE
        getchar();
    #endif
}
