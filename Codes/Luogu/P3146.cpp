#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

const int maxn = 250;

int f[maxn][maxn], n, ans;
int num[maxn];

signed main() {
	n = read();
	for(int i = 1; i <= n; ++i) 
		num[i] = read();
		
	for(int i = 1; i <= n; ++i)
		f[i][i] = num[i];
	
	
	for(int l = 1; l <= n; ++l) {
		for(int i = 1; i + l <= n; ++i) {
			int j = i + l;
			for(int k = i; k <= j; ++k) {
				if(f[i][k] == f[k + 1][j])
					f[i][j] = max(f[i][j], f[i][k] + 1);
//				cout << i << " " << j << " " << f[i][j] << endl;
				ans = max(ans, f[i][j]);
			}
		}
	}
	
	cout << ans << endl;
}
