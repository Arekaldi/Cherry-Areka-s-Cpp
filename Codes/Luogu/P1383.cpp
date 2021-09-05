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
		inline int Add(int Last, int L, int R, int x, int num) {
			int p = ++tot;
			T[p] = T[Last];
			if(L == R) {
				T[p].dat = x;
                // cout << x << endl;
				return p;
			}
			
			int mid = (L + R) >> 1;
			if(num <= mid)
				Ls(p) = Add(Ls(p), L, mid, x, num);
			else
				Rs(p) = Add(Rs(p), mid + 1, R, x, num);
				
			return p;
		}
		
		inline int Ask(int p, int L, int R, int num) {
			if(L == R) {
                // cout << p << endl;
				return T[p].dat;
            }
			int mid = (L + R) >> 1;
			
			if(num <= mid)
				return Ask(Ls(p), L, mid, num);
			else
				return Ask(Rs(p), mid + 1, R, num);
		}
}Sg;

int Rt[maxn], L[maxn];

int n, cnt;

signed main() {
	n = read();
	
	for(int i = 1; i <= n; ++i) {
		char Type;
		cin >> Type;
		
		if(Type == 'T') {
			char x; cin >> x;
            cnt++;
			L[cnt] = L[cnt - 1] + 1;
			Rt[cnt] = Sg.Add(Rt[cnt - 1], 1, maxn, (int)x, L[cnt]);
			continue;
		}
		
		int x;
		cin >> x;
			
		if(Type == 'U') {
			++cnt;
			L[cnt] = L[cnt - x - 1];
			Rt[cnt] = Rt[cnt - x - 1];
		}
			
		if(Type == 'Q') {
			int ans = Sg.Ask(Rt[cnt], 1, maxn, x);
			cout << (char)ans << endl;
		}
	}

    return 0;
}