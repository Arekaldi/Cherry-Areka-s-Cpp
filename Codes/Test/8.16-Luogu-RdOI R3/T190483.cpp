#include <bits/stdc++.h>

using namespace std;

#define int __int128

inline int read() {
	register int x = 0, f = 1;
	register char ch;
	while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
	for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
	return x * f;
}

int n, a, b, c, d, e;

signed main() {
	int T = read();
	while(T--) {
		n = read(), a = read(), b = read(), c = read(), d = read(), e = read();
		int Max = 0, Min = 0;
		if(e == 0) {
			if(d >= n)
				Max = n * a, Min = a + (n - 1) * c;
			else
				Max = d * a + (n - d) * c, Min = a + (n - 1) * c;
		}
		else if(d > e) {
			if(e <= n - 1)
				Min = b * e + (n - 1 - e) * c + a;
			else
				Min = (n - 1) * b + a;
			if(d - e >= n)
				Max = n * a;
			else
				Max = max((d - e) * a + (n - d + e) * c, min(d, n) * a + (d <= n) ? ((n - d) * c) : 0 + b);
				
		}
		else if(d == e) {
			// 胜 平 负
			// 全平 
			Max = max(n * c, (n - 1) * a + b), Min = min(n * c, (n - 2) * c + b + a);
		}
		else {
			if(d <= n - 1)
				Max = a * d + (n - 1 - d) * c + b;
			else
				Max = (n - 1) * a + b;
			if(e - d >= n)
				Min = n * b;
			else
				Min = min((e - d) * b + (n - e + d) * c, min(e, n) * b + (e <= n) ? ((n - e) * c) : 0 + a);
		}
		cout << (long long)Max << " " << (long long)Min << endl;
	}
}
