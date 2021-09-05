#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

const int maxn = 1e6 + 1;
const int maxN = 5e3 + 1;

vector <int> V[maxN];
int a[maxn];
int n, m;
double Sn;
int pos[maxn], add[maxn];
int L[maxn], R[maxn];
int t;

class Cut_num {
    public :
        inline void Resort(int k) {
            V[k].clear();
            for(int i = L[k]; i <= R[k]; ++i)
                V[k].push_back(a[i]);
            
            sort(V[k].begin(), V[k].end());
        }
        
        inline void Add(int l, int r, int c) {
            int p = pos[l], q = pos[r];
            for(int i = l; i <= min(R[p], r); ++i)
            	a[i] += c;
            Resort(p);
        	if(p != q) {
        		for(int i = L[q]; i <= r; ++i)
        			a[i] += c;
        		Resort(q);
			}
			for(int i = p + 1; i < q; ++i)
				add[i] += c;
        }

        inline int Ask(int l, int r, int k) {
            int p = pos[l], q = pos[r];
            int ans = 0;
            
            for(int i = l; i <= min(R[p], r); ++i)
                if(a[i] + add[p] >= k) ans++;
            
            if(p != q)
                for(int i = L[q]; i <= r; ++i)
                    if(a[i] + add[q] >= k) ans++;
            
            for(int i = p + 1; i < q; ++i) {
                int x = k - add[i];
                ans += V[i].end() - lower_bound(V[i].begin(), V[i].end(), x);
			}

            return ans;
        }
}C;

inline void init() {
    Sn = sqrt(n);
    t = Sn;

    for(int i = 1; i <= t; ++i) 
        L[i] = (i - 1) * Sn + 1, R[i] = i * Sn;
        
    if(R[t] < n) {
        ++t;
        L[t] = R[t - 1] + 1;
        R[t] = n;
	}
    
    for(int i = 1; i <= t; ++i)
        for(int j = L[i]; j <= R[i]; ++j)
            pos[j] = i;
            
    for(int i = 1; i <= t; ++i)
        C.Resort(i);
}



signed main() {
//	freopen("1.in", "r", stdin);
//	freopen("2.txt", "w", stdout);

    n = read(), m = read();

    for(int i = 1; i <= n; ++i)
        a[i] = read();
    
    init();

    for(int i = 1 ; i <= m; ++i) {
        char opt;
        cin >> opt;
        int l = read(), r = read(), c = read();
        if(opt == 'M')
            C.Add(l, r, c);
        else
            printf("%d\n", C.Ask(l, r, c));
    }
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}