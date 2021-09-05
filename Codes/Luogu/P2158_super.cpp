#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

signed main() {
	n = read();
	if(n == 1) {
		puts("0");
		return 0;
	}
	Get_Phi();
	printf("%d\n", (sum_phi[n - 1] << 1) + 1);

    
    clock_t b = clock();

    double s = b * 1.0;

    printf("%.6fs\n", (s) / CLOCKS_PER_SEC);
    return 0;
}
