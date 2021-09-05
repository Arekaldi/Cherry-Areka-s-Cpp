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
priority_queue <int> q;

signed main() {
	n = read();
	for(int x, i = 1; i <= n; ++i)
		x = read(), q.push(-x);
	for(int i = 1; i <= n; ++i)
		cout << -q.top() << " ", q.pop();
}
