#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

const int maxn = 8e5 + 1;

class Node {
    public :
        int id, num;
        Node(int x, int y) : id(x), num(y) {}
};

stack < Node > S;

int n, ans;

signed main() {
    n = read();

    for(int i = 1; i <= n; ++i) {
        int g = read();
        if(S.empty()) {
            S.push(Node(i, g));
            continue;
        }
        Node x = S.top();
        if(g < x.num) 
            S.push(Node(i, g));
        else {
            int s1 = S.size();
            while(!S.empty()) {
                Node u = S.top();
                if(u.num > g) break;
                S.pop();
            }
            int s2 = S.size();
            ans += ((s1 + s2 - 1) * (s1 - s2)) >> 1;
            S.push(Node(i, g));
        }
    }

    int s1 = S.size(), s2 = 0;
    ans += ((s1 + s2 - 1) * (s1 - s2)) >> 1;
    
    cout << ans << endl;
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
