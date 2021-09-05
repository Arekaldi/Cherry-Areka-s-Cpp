#include <bits/stdc++.h>

using namespace std;

#define int unsigned long long

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

int f[22][22];
int xm, ym, n, m;

bool Judge(int x, int y) {
	if(x == xm and y == ym) return true;
	if(x == xm - 1 and y == ym - 2) return true;
	if(x == xm - 2 and y == ym - 1) return true;
	if(x == xm + 1 and y == ym - 2) return true;
	if(x == xm + 2 and y == ym - 1) return true;
	if(x == xm + 2 and y == ym + 1) return true;
	if(x == xm + 1 and y == ym + 2) return true;
	if(x == xm - 2 and y == ym + 1) return true;
	if(x == xm - 1 and y == ym + 2) return true;
	return false;
}

signed main() {
	n = read(), m = read(), xm = read(), ym = read();
	f[1][1] = 1;
//	cout << Judge(0, 0) << endl;
	for(int i = 1; i <= n + 1; ++i) {
		for(int j = 1; j <= m + 1; ++j) {
			f[i][j] = max(f[i][j], f[i][j - 1] + f[i - 1][j]);
//			cout << i - 1 << " " << j - 1 << " " << f[i][j] << " " << f[i - 1][j] << " " << f[i][j - 1] << endl;
//			cout << i - 1 << " " << j << " " << i << " " << j - 1 << endl;
			if(Judge(i - 1, j - 1)) f[i][j] = 0;
		}
	}
	
	cout << f[n + 1][m + 1] << endl;
}
