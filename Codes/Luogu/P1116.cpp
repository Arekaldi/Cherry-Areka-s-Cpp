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
int a[10001];

signed main() {
	n = read();
	for(int i = 1; i <= n; ++i)
		a[i] = read();
	int res = 0;
	for(int i = 1; i <= n; ++i) {
		for(int j = 2; j <= n; ++j) {
			if(a[j] < a[j - 1]) {
				swap(a[j - 1], a[j]);
				res++;
			}
		}
	}
	cout << res;
}
