#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

int a[5];
string s;

int Q[1001];

signed main() {

    a[1] = read(), a[2] = read(), a[3] = read();
    scanf("%s", s);

    sort(a + 1, a + 3);

    for(int i = 0; i < s.length(); ++i) cout << s[i];
    cout << endl;

    Q['A'] = a[1], Q['B'] = a[2], Q['C'] = a[3];

    for(int i = 0; i < s.length(); ++i)
        cout << 1 << " ";

    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
