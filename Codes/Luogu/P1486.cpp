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
const int SIZE = 1e6 + 10;
#define INF 0x7fffffff
#define int long long

struct Tree_ {
	int size, cnt;
	int dat, val;
	int ls, rs;
	#define l T[p].ls
	#define r T[p].rs
}T[SIZE];
int n, m, tot, root, minx;
int dt, red;

void record(int p) {red += T[p].cnt; return;}

void Update(int p) {
	T[p].size = T[p].cnt + T[l].size + T[r].size;
}

void Zig(int &p) {
	int q = T[p].ls;
	T[p].ls = T[q].rs, T[q].rs = p, p = q;
	Update(T[p].rs), Update(p);
}

void Zag(int &p) {
	int q = T[p].rs;
	T[p].rs = T[q].ls, T[q].ls = p, p = q;
	Update(T[p].ls), Update(p);
}

int New(int val) {
	T[++tot].val = val;
	T[tot].dat = rand();
	T[tot].size = T[tot].cnt = 1;
	return tot;
}

int Get_VR(int &p, int rank) {
	if(T[r].size >= rank) return Get_VR(r, rank);
	if(T[r].size + T[p].cnt >= rank) return T[p].val;
	return Get_VR(l, rank - T[r].size - T[p].cnt);
}

void Insert(int &p, int val) {
	if(p == 0) {
		p = New(val), Update(p);
		return;
	}
	if(T[p].val == val) {
		T[p].cnt++, Update(p);
		return;
	}
	if(val < T[p].val) {
		Insert(l, val);
		if(T[p].dat < T[l].dat) Zig(p);
	}
	else {
		Insert(r, val);
		if(T[p].dat < T[r].dat) Zag(p);
	}
	Update(p); return;
}

void Remove(int &p, int val) {
	if(p == 0) return;
	else {
		if(T[p].val == val) {
			if(T[p].cnt > 1) {
				T[p].cnt--, Update(p);
				return;
			}
			if(l or r) {
				if(!r or T[l].dat > T[r].dat)
					Zig(p), Remove(r, val);
				else {
					Zag(p), Remove(l, val);
				}
				Update(p);
			}
			else p = 0;
		}
		val < T[p].val ? Remove(l, val) : Remove(r, val);
		Update(p);
	}
	return;
}

void Add_Rec(int p, int k) {
	if(p == 0) return;
	T[p].val += k;
	Add_Rec(l, k), Add_Rec(r, k);
	return;
}

void Recover(int p) {
	if(p == 0) return;
	Recover(l); Recover(r);
	if(T[p].val < minx) {
		record(p);
		int Tx = T[p].cnt;
		while(Tx--) Remove(root, T[p].val);
	}
	return;
}

void out(int p) {
	if(p == 0) return;
	else {
		cout << T[p].val << endl;
		out(l); out(r);
	}
}

signed main() {
//	freopen("1.in", "r", stdin);
//	freopen("1.out", "w", stdout);
	n = read(), minx = read();
	for(int i = 1; i <= n; ++i) {
		char x; int k;
		cin >> x >> k;
		if(x == 'I') {
			if(k >= minx) Insert(root, k);
		}
		if(x == 'A' or x == 'S') {
			if(x == 'A') Add_Rec(root, k);
			else {
				Add_Rec(root, -k);
				Recover(root);
			}
		}
		if(x == 'F') {
			if(k > T[root].size) cout << "-1" << endl;
			else
				cout << Get_VR(root, k) << endl;
		}
	}
	cout << red << endl;
}