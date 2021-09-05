#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

int n;
int a[101];

signed main() {
	n = read();
	for(int i = 1; i <= n; ++i)
		a[i] = read();
	for(int i = 1; i <= n; ++i) {
		int res = 0;
		for(int j = 1; j < i; ++j)
			res += (a[j] < a[i]);
		cout << res << " ";
	}
}
