#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

class Tree{
    private :
        int f = read();
    public :
        int ma() {return f * 10;};
}T;

signed main() {
    cout << T.ma() << endl;
    
    
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
