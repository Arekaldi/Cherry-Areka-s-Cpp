#include <bits/stdc++.h>

using namespace std;

#define int long long

inline int read() {
	char ch;
	int x = 0, f = 1;
	while(!isdigit(ch = getchar()))
		(ch == '-') and (f = -1);
	for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 1) + (x << 3) + (ch ^ 48));
	return x * f;
}

const int Mod = 19260817;

inline int Power(int x, int a) {
	int ans = 1;
	while(a) {
		if(a & 1)
			ans = (ans * x) % Mod;
		x = (x * x) % Mod;
		a >>= 1;
	}
	return ans;
}

signed main() {
	int a = read(), b = read();
	if(b % Mod == 0)
		puts("Angry!");
	else {
		printf("%lld\n", a * Power(b, Mod - 2) % Mod);
	}
}
