#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

string A, B;

inline int check(int j, int i) {
	if(A[j] == '0' and A[i] == '1')
		return 0;
	if(A[j] == '1' and A[i] == '0')
		return 1;
	if(A[j] == '1' and A[i] == '1')
		return 2;
	if(A[j] == '0' and A[i] == '0')
		return 3;
}

signed main() {
	int T = read();
	while(T--) {
		int n = read(), m = read();
		if(n != 0)
			cin >> A;
		if(m <= n or m == 1 or n == 1 or m == 0 or n == 0)
			puts("-1");
		else if(n == 2 and A[0] != A[1])
			puts("-1");
		else {
			int cnt1 = 0, cnt2 = 0;
			for(int i = 0; i < n; ++i)
				cnt1 += (A[i] == '1'), cnt2 += (A[i] == '0');
			char id = cnt1 < cnt2 ? '1' : '0';
			int j;
			for(int i = 0; i < n; ++i) {
				putchar(A[i]);
				j = i;
				if(A[i] == '1' and id == '0')
					break;
				else if(A[i] == '0' and id == '1')
					break;
			}
			for(int i = 0; i < m - n; ++i)
				putchar(id);
			for(int i = j + 1; i < n; ++i)
				putchar(A[i]);
			puts("");
		}
	}
    return 0;
}
