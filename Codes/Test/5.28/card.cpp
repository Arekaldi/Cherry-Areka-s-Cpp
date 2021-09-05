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

int n1;

class Poker {
	public :
		int Flow, num;

		inline bool operator < (const Poker &a) const {
			return Flow == a.Flow ? a.num > num : a.Flow > Flow;
		}

		inline bool operator == (const Poker &a) const {
			return a.Flow == Flow and a.num == num;
		}

}M[maxn];

signed main() {
	freopen("card.in", "r", stdin);
	freopen("card.out", "w", stdout);

	n1 = read();
	for(int i = 1; i <= n1; ++i)
		M[i].Flow = read(), M[i].num = read();
	
	sort(M + 1, M + n1 + 1);
	int n = unique(M + 1, M + n1 + 1) - M - 1;

	int l = 1, r = 1, ans = 0;

	while(l <= n and r <= n) {
		while(r + 1 <= n and M[r + 1].Flow == M[l].Flow and M[r + 1].num - M[l].num < n)
			++r;
		ans = max(ans, (r - l + 1));
		if(M[r].Flow != M[l].Flow)
			l = r;
		else
			++l;
	}

	printf("%d\n", n1 - ans);

	getchar();
	return 0;
}
