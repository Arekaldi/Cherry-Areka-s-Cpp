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

int r, res;

inline void check(int g) {
	if(r % g)
		return;
	for(int s = 1; s * s <= r; ++s) {
		int t = sqrt((r / g) - s * s);
		if(s * s + t * t != (r / g))
			continue;
		if(__gcd(s, t) != 1)
			continue;
		int x = g * s * t, y = (t * t - s * s) / 2 * g;
		if(x > 0 and y > 0 and x * x + y * y == 1ll * (r / 2) * (r / 2))
			res += 8;
	}
}

signed main() {
	r = read() * 2;
	for(int g = 1; g * g <= r; ++g)
		if(r % g)
			continue;
		else
			check(g), (r / g != g) and (check(r / g), 1);
	printf("%lld\n", (long long)((res + 4) * 1ll));
}
