
//O(4LgN + 4N)

#include <bits/stdc++.h>

using namespace std;

inline int read() {
    int x = 0, f = 1;
    char ch = getchar();
    while(ch < '0' or ch > '9') {
        if(ch == '-') f = -1;
        ch = getchar();
    }
    while(ch >= '0' and ch <= '9') {
        x = (x << 1) + (x << 3) + (ch ^ 48);
        ch = getchar();
    }
    return x * f;
}

const int maxn = 1e5 + 10;

int N;
int A[maxn], B[maxn], C[maxn], D[maxn];
int la, lb, lc, ld;

int ans = 0, p = 1;

signed main() {
	freopen("ples.in", "r", stdin);
	freopen("ples.out", "w", stdout);
	
	N = read();
	for(int i = 1; i <= N; ++i) {
		int x = read();
		if(x < 0)
			A[++la] = -x;
		else
			B[++lb] = x;
	}
	
	for(int i = 1; i <= N; ++i) {
		int x = read();
		if(x < 0)
			C[++lc] = -x;
		else
			D[++ld] = x;
	}
	
//	cout << la << " " << lb << " " << lc << " " << ld << endl;
	
	sort(A + 1, A + la + 1);
	sort(B + 1, B + lb + 1);
	sort(C + 1, C + lc + 1);
	sort(D + 1, D + ld + 1);
	
	for(int i = 1; i <= la; ++i) {
		if(p > ld)
			break;
		if(A[i] > D[p])
			ans++, p++;
	}
	/*
	A: 1732 2134 2255
	B: 1640 2047 2342
	C: 1849 2135
	D: 1603 2106 2273 2347
	*/
	p = 1;
	for(int i = 1; i <= lc; ++i) {
		if(p > lb)
			break;
		if(C[i] > B[p])
			ans++, p++;
	}
	
	cout << ans << endl;
}
