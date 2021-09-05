#include <bits/stdc++.h>

using namespace std;

#define int long long

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

const int maxn = 1e6 + 1;

// 设 s_i + i = a_i, s_j + j + L = b_j

// 2 * a_i * b_j + f_i - a_i ^ 2 = f_j + b_j ^ 2

// 设 b_j = x, f_i - a_i ^ 2 = b, f_j + b_j ^ 2 = y

// 有 2 * a_i * x + b = y 

int n, L;
int f[maxn], Q[maxn];
// dp数组 队列

double S[maxn];
// 前缀和

inline double readd() {
	double a;
	scanf("%lf", &a);
	return a;
}

inline double a(int x) {
	return S[x] + (double)x;
}

inline double b(int x) {
	return S[x] + (double)x + (double)L + 1.0;
}

inline double X(int x) {
	return b(x);
}

inline double Y(int x) {
	return (double)f[x] + b(x) * b(x);
}

inline double K(int x, int y) {
	return (Y(x) - Y(y)) / (X(x) - X(y));
}

signed main() {
	n = read(), L = read();
	
	for(int i = 1; i <= n; ++i) {
		double x = readd();
		S[i] = S[i - 1] + x;
	}
	
	int bot = 1, top = 1;
	for(int i = 1; i <= n; ++i) {
		while(K(Q[bot], Q[bot + 1]) < a(i) * 2.0 and bot < top)
			bot++;
		int j = Q[bot];
		f[i] = f[j] + (a(i) - b(j)) * (a(i) - b(j));
		while(K(Q[top - 1], Q[top]) > K(Q[top - 1], i) and bot < top)
			top--;
		Q[++top] = i;
	}

	printf("%lld\n", f[n]);

    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}