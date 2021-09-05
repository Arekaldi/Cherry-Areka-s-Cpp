#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

const int maxn = 4e5 + 1;

int n;
int a[maxn], b[maxn];

class Tree_Array {
	private:
		int t[maxn];
		inline int lowbit(int x) {
			return x & (-x);
		}
	public:
		inline void init() {
			memset(t, 0, sizeof(t));
		}
		inline void Add(int pos, int v) {
			if(pos <= 0)
				return;
			while(pos <= n) {
				t[pos] += v;
				pos += lowbit(pos);
			}
		}
		inline int Ask(int pos) {
			if(pos <= 0)
				return 0;
			int res = 0;
			while(pos) {
				res += t[pos];
				pos -= lowbit(pos);
			}
			return res;
		}
}T;

signed main() {
	n = read();
	for(int i = 1; i <= n; ++i)
		a[i] = read(), b[i] = a[i];
	sort(b + 1, b + n + 1);
	int nn = unique(b + 1, b + n + 1) - b - 1;
	for(int i = 1; i <= n; ++i)
		a[i] = lower_bound(b + 1, b + nn + 1, a[i]) - b;
	
	int res = 0;
	for(int i = 1; i <= n; ++i) {
		T.Add(a[i], 1);
		res = max(res, T.Ask(n) - T.Ask(a[i] + 1));
	}
	cout << max(res, 1);
}
