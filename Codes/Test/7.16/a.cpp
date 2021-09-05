#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e6 + 1;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}
int bow[30];

double f[maxn], b[maxn], k[maxn];

char ch[maxn];

double ans;

signed main() {

	freopen("a.in" , "r" , stdin);
	freopen("a.out" , "w" ,stdout);

	cin >> (ch + 1);
	int len = strlen(ch + 1);
	for(int i = 1; i <= len; ++i) bow[ch[i] - 'A' + 1]++;
	k[1] = 1.0, b[1] = 0.5 * len;
	for(int i = 2; i <= len - 1; ++i) {
		double tm1, tm2;
		tm1 = 0.5 / i;
		tm2 = 1.0 / (1 - (i - 1) * tm1 * k[i - 1]);
		k[i] = (double) (i + 1) * tm1 * tm2;
		b[i] = ((i - 1) * tm1 * b[i - 1] + len * (len - 1) * tm1 / (len - i)) * tm2;
	}
	for(int i = len - 1; i >= 1; --i) f[i] = f[i + 1] * k[i] + b[i];
	for(int i = 1; i <= 26; ++i) ans += (double) bow[i] / len * f[bow[i]];
	printf("%.1f" , ans);
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
