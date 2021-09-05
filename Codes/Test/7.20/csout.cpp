#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

int a[1992];

signed main() {
	freopen("C3.out", "w", stdout);
	
	srand(time(0));
	
	int n = 1991;
	cout << n << endl;
	
	for(int i = 1; i <= n; i += 2) {
		a[i] = 1, a[n - i] = n - 1;
	}
	for(int i = 1; i <= n; ++i)
		cout << a[i] << " ";
}
