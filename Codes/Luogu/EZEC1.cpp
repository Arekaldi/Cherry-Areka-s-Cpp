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

const int maxn = 1e5 + 1;

int n, m, a[maxn];

inline bool camp(int a, int b) {
	return a > b;
}

signed main() {
    
    #define Point
    // #define Areka
    #ifdef Areka
        freopen("1.txt", "r", stdin);
        freopen("wans.txt", "w", stdout);
    #endif

    n = read(), m = read();

	for(int i = 1; i <= n; ++i)
		a[i] = read();
	
	sort(a + 1, a + n + 1, camp);
	
	for(int i = 2; i < n; ++i) {
		int w = a[1] - a[i];
		if(m - w >= 0) {
			a[i] += w;
			m -= w;
		}
        else {
            if(a[i] + m <= a[1] and m) {
                a[i] += m;
                m = 0;
            }
        }
	}
	
	int ans = 0;
	if(m > 0) {
        int p = n - 1;
        double m1 = double(m * 1.0);
        double p1 = double(p * 1.0);
        double x = ceil(m1 / p1);
        ans = m - x;
    }
	
	for(int i = 2; i < n; ++i)
		ans += a[i];
	printf("%lld\n", ans);
    
    #ifdef Point
        getchar();
    #endif
    return 0;
}
