
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

const int maxn = 1e6 + 1;

int head, tail, n, k, tot, now_kind;
int cnt[maxn];

class Node {
	public:
		int pos, id;
		inline bool operator < (const Node &a) const {
			return a.pos > pos;
		}
};

Node a[maxn], que[maxn];

signed main() {
	tail = 1;
	n = read(), k = read();
	for(int i = 1; i <= k; ++i) {
		int t = read();
		for(int x, j = 1; j <= t; ++j)
			a[++tot].pos = (x = read()), a[tot].id = i;
	}
	int res = (1 << 30);
	sort(a + 1, a + tot + 1);
	for(int i = 1; i <= tot; ++i) {
		que[++head] = a[i];
		cnt[que[head].id]++;
		if(cnt[que[head].id] == 1)
			now_kind++;
		while(tail <= head and cnt[que[tail].id] > 1)
			cnt[que[tail].id]--, tail++;
		if(now_kind == k)
			res = min(res, que[head].pos - que[tail].pos);
	}
	cout << res << endl;
	return 0;
}
