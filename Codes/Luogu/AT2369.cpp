#include <bits/stdc++.h>

using namespace std;

inline int read() {
	register int x = 0, f = 1;
	register char ch;
	while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
	for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
	return x * f;
}

const int maxn = 1e5 + 1;

class Ant {
    public: 
        int pos, face;
        inline bool operator < (const Ant a) const {
            return a.pos > pos;
        }
}a[maxn];

int n, T, L;

signed main() {
	n = read(), T = read(), L = read();
	
	for(int i = 1; i <= n; ++i) {
		a[i].pos = read(), a[i].face = read();
		a[i].face = a[i].face == 2 ? 1 : -1;
		a[i].pos += a[i].face * T;
        while(a[i].pos < 0)
            a[i].pos += L;
        a[i].pos %= L;
	}

    sort(a + 1, a + n + 1);

    for(int i = 1; i <= n; ++i)
        printf("%d\n", a[i].pos);
	
	#ifndef ONLINE_JUDGE
		getchar();
	#endif
	return 0;
}
