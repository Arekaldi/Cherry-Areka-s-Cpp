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

int n, m;
int a[maxn];

class Segment_Tree {
    private :
        class Tree {
            public :
                int l, r;
                int Mark, sum;
            #define Ls p << 1
            #define Rs p << 1 | 1
        }T[maxn << 2];

        inline void Upd(int p) {
            T[p].sum = T[Ls].sum + T[Rs].sum;
            return;
        }

        inline void Spread(int p) {
            if(!T[p].Mark)
                return;
            int Mid = (T[p].l + T[p].r) >> 1;
            T[Ls].Mark = T[Rs].Mark = T[p].Mark;
            T[Ls].sum = T[p].Mark == 1 ? Mid - T[p].l + 1 : 0;
            T[Rs].sum = T[p].Mark == 1 ? T[p].r - Mid : 0;
            T[p].Mark = 0;
        }

    public :
        inline void Build(int p, int L, int R, int k) {
            T[p].l = L, T[p].r = R;
            if(L == R) {
                T[p].sum = a[L] >= k;
                T[p].Mark = 0;
                return;
            }
            int mid = (L + R) >> 1;
            Build(Ls, L, mid, k);
            Build(Rs, mid + 1, R, k);
            Upd(p);
            T[p].Mark = 0;
            return;
        }

        inline void Add(int p, int L, int R, int k) {
        	if(T[p].r < L or T[p].l > R)
        		return;
            if(T[p].l >= L and T[p].r <= R) {
                T[p].sum = k * (T[p].r - T[p].l + 1);
                T[p].Mark = k ? 1 : -1;
                return;
            }
            Spread(p);
            int mid = (T[p].l + T[p].r) >> 1;
            if(L <= mid)
                Add(Ls, L, R, k);
            if(R > mid)
                Add(Rs, L, R, k);
            Upd(p);
            return;
        }

        inline int Ask_Sum(int p, int L, int R) {
            if(T[p].l >= L and T[p].r <= R) 
                return T[p].sum;
            
            Spread(p);
            int mid = (T[p].l + T[p].r) >> 1;
            int ans = 0;
            if(L <= mid)
                ans += Ask_Sum(Ls, L, R);
            if(R > mid)
                ans += Ask_Sum(Rs, L, R);
            
            return ans;
        }

        inline int Ask_Point(int p, int q) {
            if(T[p].l == T[p].r)
                return T[p].sum;
            
            Spread(p);

            int mid = (T[p].l + T[p].r) >> 1;

            if(q <= mid)
                return Ask_Point(Ls, q);
            else if(q > mid)
                return Ask_Point(Rs, q);
        }
}S;

int L, R, q;

class Command {
	public :
		int opt, l, r;
}C[maxn];

inline bool check(int k) {

    S.Build(1, 1, n, k);

    for(int i = 1; i <= m; ++i) {
        int opt = C[i].opt, l = C[i].l, r = C[i].r;
        int cnt1 = S.Ask_Sum(1, l, r);
        
        switch(opt) {
            case 0 : {
                S.Add(1, r - cnt1 + 1, r, 1), S.Add(1, l, r - cnt1, 0);
                break;
            }
            
            case 1 : {
                S.Add(1, l, l + cnt1 - 1, 1), S.Add(1, l + cnt1, r, 0);
                break;
            }
        }
    }
    
//    int qk = S.Ask_Point(1, q);
//    cout << k << " " << qk << endl;
    
	return S.Ask_Point(1, q);
}

signed main() {
	freopen("seq.txt", "r", stdin);
	freopen("seq.txt", "w", stdout);
	
    n = read(), m = read();
    
    for(int i = 1; i <= n; ++i)
		a[i] = read();
	
	for(int i = 1; i <= m; ++i)
		C[i].opt = read(), C[i].l = read(), C[i].r = read();

	q = read();
	int ans;
	
	L = 1, R = n;
	while(L <= R) {
		int mid = (L + R) >> 1;
		
		if(check(mid)) 
			ans = mid, L = mid + 1;
		
		else R = mid - 1;
	}

    printf("%d\n", ans);
    return 0;
}

