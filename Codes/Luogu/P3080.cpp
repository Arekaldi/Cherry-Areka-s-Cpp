#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

const int maxn = 2e3 + 1;

int n, flag;
int f[maxn][maxn][2],
	p[maxn], sum[maxn][maxn];

signed main() {
	memset(f, 0x3f, sizeof(f));
	n = read();
	for(int i = 1; i <= n; ++i)
		p[i] = read(), (p[i] == 0) and (flag = i);
	if(!flag)
		p[++n] = 0;
	sort(p + 1, p + n + 1);
	for(int i = 1; i <= n; ++i)
		(p[i] == 0) and (flag = i);
	f[flag][flag][0] = f[flag][flag][1] = 0;
	for(int i = 1; i <= n; ++i)
		for(int j = i; j <= n; ++j)
			sum[i][j] = n - (j - i + 1);
	for(int len = 1; len <= n; ++len) {
		for(int l = 1; l <= n; ++l) {
			int r = len + l;
			f[l][r][0] = min(f[l][r][0], min(f[l + 1][r][0] + (p[l + 1] - p[l]) * sum[l + 1][r], f[l + 1][r][1] +(p[r] - p[l]) * sum[l + 1][r]));
            f[l][r][1] = min(f[l][r][1], min(f[l][r - 1][1] + (p[r] - p[r - 1]) * sum[l][r - 1], f[l][r - 1][0] + (p[r] - p[l]) * sum[l][r - 1]));
		}
	}
	printf("%d\n", min(f[1][n][0], f[1][n][1]));
}
