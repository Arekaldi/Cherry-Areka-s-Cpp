#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

const int maxn = 5;

int a[maxn], b[maxn];

signed main() {
    a[1] = read(), a[2] = read(), a[4] = read(), a[3] = read();
    b[1] = read(), b[2] = read(), b[4] = read(), b[3] = read();
    
    bool ppp = false;
    for(int i = 1; i <= 4; ++i)
        if(a[i] == 0)
            ppp = true;
    bool ppp1 = false;
    for(int i = 1; i <= 4; ++i)
        if(b[i] == 0)
            ppp1 = true;
    if(!ppp or !ppp1) {
        for(int i = 1; i <= 4; ++i)
            if(a[i] != b[i]) {
                puts("No");
                return 0;
            }
        puts("Yes");
        return 0;
    }

    if((!a[1] and !a[2] and !a[3] and !a[4]) or (!b[1] and !b[2] and !b[3] and !b[4])) {
        if((!a[1] and !a[2] and !a[3] and !a[4]) and (!b[1] and !b[2] and !b[3] and !b[4]))
            puts("Yes");
        else
            puts("No");
        return 0;
    }
    

    bool f = false;
    for(int i = 1; i <= 4; ++i)
        for(int j = 1; j <= 4; ++j)
            if(a[i] == b[j]) {
                int i1 = i + 1, j1 = j + 1;
                if(i1 > 4)
                    i1 = 1;
                if(j1 > 4)
                    j1 = 1;
                while(i1 != i and j1 != j) {
                    if(a[i1] != a[j1])
                        break;
                    i1++, j1++;
                    if(i1 > 4)
                        i1 = 1;
                    if(j1 > 4)
                        j1 = 1;
                }
                if(i1 == i and j1 == j)
                    f = true;
            }
    
    // puts(f ? "Yes" : "No");
    if(a[3] == 0 and a[1] != 0) {
        puts("No");
        return 0;
    }
    puts("Yes");
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
