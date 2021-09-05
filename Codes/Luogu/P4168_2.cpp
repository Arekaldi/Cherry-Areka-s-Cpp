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

const int maxn = 5e6 + 10, Sn = 35;
double st;

int op[maxn], a[maxn];
int m, n, t;
int num[maxn];

signed main() {
	
	n = read(), m = read();
	for(int i = 1; i <= n; ++i)
		a[i] = read(), op[i] = a[i];
	
	sort(op + 1, op + n + 1);
	int k = unique(op + 1, op + n + 1) - op - 1;
	
	for(int i = 1; i <= n; ++i) 
		a[i] = lower_bound(op + 1, op + k + 1, a[i]) - op;
	
	int last = 0;
	for(int i = 1; i <= m; ++i) {
		int l = read(), r = read();
		
		l = (l + last - 1) % n + 1, r = (r + last - 1) % n + 1;
		
		if(l > r) swap(l, r);
		
		memset(num, 0, sizeof(num));
		int maxn = 0, ans = 0;
		for(int i = l; i <= r; ++i) {
			num[a[i]]++;
			if(maxn < num[a[i]])
				maxn = num[a[i]];
		}
		
		for(int i = 1; i <= n; ++i)
			if(num[a[i]] == maxn) {
				ans = a[i];
				break;
			}
		
		last = ans;
		
		cout << ans << endl;
	}
	
}

// 1 4
