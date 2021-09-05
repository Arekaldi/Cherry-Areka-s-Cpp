#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

const int maxn = 5e5 + 1;

int a[maxn];

signed main() {
    int n = read(), ans;
    
    ans = a[1] = read();
    
    for(int i = 2; i <= n; ++i) {
        a[i] = read();
        ans ^= a[i];
    }
    
    if(!ans) {
    	puts("lose");
    	return 0;
	}

	for(int i = 1; i <= n; ++i) {
		if((a[i] ^ ans) < a[i]) {
			printf("%d %d\n", a[i] - (a[i] ^ ans), i);
			a[i] ^= ans;
			for(int j = 1; j <= n; ++j)
				printf("%d ", a[j]);
			puts("");
			goto Areka;		
		}
	}

Areka :    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}

// 110
// 011
// 101
// k ^ a[i]' == 0
// 

/*
1001
0101
1100
100
1000
*/

