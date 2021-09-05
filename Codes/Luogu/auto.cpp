// AVX + Hignest
#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

vector <int> a;

string ss;


void write(int x)        
{        
    if(x < 0) {        
        putchar('-');        
        x = -x;        
    }        
    if(x > 9)        
        write(x/10);        
    putchar(x % 10 + '0');        
    return;        
}        


signed main() {
	clock();
	long long n = 9000;
	__int128 res = 0;
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= n; ++j)
			for(int k = 1; k <= n; ++k)
				
			}
	printf("%llu\n", (unsigned long long)res);
	write(res);
	puts("");
	double x = clock();
	printf("%.3f", x / CLOCKS_PER_SEC);
}
