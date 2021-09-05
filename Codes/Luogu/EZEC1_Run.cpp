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
    while(true) {
        system("cd E:\\Cpp");
        system("treerand.exe");
        system("trees.exe");
        system("trees_std.exe");
		bool a = system("fc w.out a.out");
		if(a) {
			printf("WA\n");
			break;
		}
		else
			puts("AC");
    }
    
    
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
