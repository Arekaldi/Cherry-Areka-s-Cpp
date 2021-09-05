#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e6 + 10;

inline int read() {
	int x = 0, f = 1;
	char ch = getchar();
	while(ch < '0' or ch > '9') {
		f = ch == '-' ? -1 : f;
		ch = getchar();
	}
	while(ch >= '0' and ch <= '9') {
		x = (x << 1) + (x << 3) + (ch ^48);
		ch = getchar();
	}
	return x * f;
}

struct Node {
	int dat;
	int ls, rs;
	#define Ls(p) T[p].ls
	#define Rs(p) T[p].rs
}T[maxn * 20];

int tot;

class Seg_Ment {
	public :
		inline void Upd(int p) {
			T[p].dat = T[Ls(p)].dat + T[Rs(p)].dat;
		}
		
		inline int Build(int L, int R) {
			int p = ++tot;
			if(L == R) {
				T[p].dat = 0;
				return p;
			}
			
			int mid = (L + R) >> 1;
			Ls(p) = Build(L, mid), Rs(p) = Build(mid + 1, R);
			T[p].dat = 0;
			Upd(p);
			return p;
		}
		
		inline int Add(int Last, int L, int R, int x) {
			int p = ++tot;
			T[p] = T[Last];
			if(L == R) {
				T[p].dat++;
				return p;
			}
			int mid = (L + R) >> 1;
			if(x <= mid)
				Ls(p) = Add(Ls(p), L, mid, x);
			else
				Rs(p) = Add(Rs(p), mid + 1, R, x)				;
			Upd(p);
			return p;
		}
		
		inline int Ask(int p, int q, int L, int R, int x) {
			if(L == R)
				return L;
			int mid = (L + R) >> 1;
			int num = T[Ls(p)].dat - T[Ls(q)].dat;
			if(x <= num)
				return Ask(Ls(p), Ls(q), L, mid, x);
			else
				return Ask(Rs(p), Rs(q), mid + 1, R, x - num);
		}
}Sg;

int a[maxn], b[maxn], c[maxn], Rt[maxn];
int n, m;
int Maxn = INT_MIN;

signed main() {
	n = read(), m = read();
	for(int i = 1; i <= n; ++i)
		b[i] = read(), c[i] = b[i];
		
	sort(b + 1, b + n + 1);
	int New = unique(b + 1, b + n + 1) - (b + 1);
	
	for(int i = 1; i <= n; ++i) {
		a[i] = lower_bound(b + 1, b + New + 1, c[i]) - b;
		Maxn = max(Maxn, a[i]);
	}
	
	Rt[0] = Sg.Build(1, Maxn);
	
	for(int i = 1; i <= n; ++i)
		Rt[i] = Sg.Add(Rt[i - 1], 1, Maxn, a[i]);
		
	for(int i = 1; i <= m; ++i) {
		int L = read(), R = read(), k = read();
        int len = R - L + 1;
		int ans = Sg.Ask(Rt[R], Rt[L - 1], 1, Maxn, k);
		printf("%d\n", b[ans]);
	}

    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}

// 1 2 3 4 5 6 7
// k - 1, k, (len - k + 1)