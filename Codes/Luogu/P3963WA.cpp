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

int Rt[maxn];
int n, m, c, f;
int Maxn = INT_MIN;

int ord[maxn], cnt;

struct Student {
	int a, b;
}s[maxn];

bool Comp(Student x, Student y) {
	return x.a == y.a ? x.b < y.b : x.a < y.a;
}

priority_queue <int> Q;

signed main() {
	n = read(), c = read(), f = read();
	
	if(n > c) {
		cout << "-1" << endl;
		return 0;
	}
	
	for(int i = 1; i <= c; ++i)
		s[i].a = read(), s[i].b = read(), ord[++cnt] = s[i].a, ord[++cnt] = s[i].b, Q.push(ord[cnt]);
		
	int num = 0, sum = 0;
	while(!Q.empty() and num <= n) {
		int x = Q.top(); Q.pop();
		sum += x;
		num++;
	}
	
	if(sum > f) {
		cout << "-1" << endl;
		return 0;
	}
		
	int New = unique(ord + 1, ord + cnt + 1) - ord - 1;
	
	for(int i = 1; i <= c; ++i) {
		s[i].a = lower_bound(ord + 1, ord + New + 1, s[i].a) - ord;
		s[i].b = lower_bound(ord + 1, ord + New + 1, s[i].b) - ord;
		Maxn = max(Maxn, s[i].a);
	}
	
	sort(s + 1, s + c + 1, Comp);
	
	Rt[0] = Build(1, Maxn);
	
	for(int i = c - n; i <= c; ++i) 
		Rt[i - (c - n) + 1] = Sg.Add(Rt[i - (c - n)], 1, Maxn, s[i].a);
	
	int ans = 
	
}
