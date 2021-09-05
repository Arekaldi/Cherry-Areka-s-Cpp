#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}



class Edge {
    public:
        int frm, to, val;
};

signed main() {
    
    
    
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
