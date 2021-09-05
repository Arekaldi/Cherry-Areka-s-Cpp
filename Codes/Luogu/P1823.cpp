// Down
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

const int maxn = 5e5 + 1;

class Stack {
	public:
		int num, cnt;
};

Stack stk[maxn];

int top, bot = 1, n, res;

signed main() {
	n = read();
	for(int x, i = 1; i <= n; ++i) {
		x = read();
		int tot = 0;
		while(top >= bot and stk[top].num <= x)
			res += stk[top].cnt, tot += (stk[top].num == x) * (stk[top].cnt), top--;
		res += (top >= bot);
		stk[++top].num = x, stk[top].cnt = tot + 1;
	}
	printf("%lld\n", res);
}
