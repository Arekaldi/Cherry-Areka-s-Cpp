#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

const int maxn = 3e6 + 1;

int top, n, f[maxn], a[maxn];

class Node {
    public:
        int num, id;
        Node() {}
        Node(int a, int b) : num(a), id(b) {}
};

Node sta[maxn];

signed main() {
    n = read();
    for(int i = 1; i <= n; ++i)
        a[i] = read();
    sta[++top] = Node(a[1], 1);
    for(int i = 2; i <= n; ++i) {
        while(top >= 1 and sta[top].num < a[i])
            f[sta[top--].id] = i;
        sta[++top] = Node(a[i], i);
    }

    for(int i = 1; i <= n; ++i)
        cout << f[i] << " ";
    
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
