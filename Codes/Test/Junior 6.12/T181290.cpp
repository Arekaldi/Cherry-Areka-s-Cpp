#include <bits/stdc++.h>

using namespace std;

#define int long long

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

const int Mod = 1e9 + 7;


int Sum[1010], n, tot;
string a;
map <char, int> M;

signed main() {

    cin >> a;

    n = read();

    for(int i = 1; i <= n; ++i) {
        string b;
        cin >> b;
        int &k = M[b[0]];
        if(k == 0)
            k = ++tot;
        for(int j = 0; b[j]; ++j)
            M[b[j]] = k;
        Sum[k] += b.length();
    }
    
    int ans = 1;
    for(int i = 0; i < a.length(); ++i) {
        if(M[a[i]] == 0)
            M[a[i]] = ++tot, Sum[M[a[i]]] = 1;
        ans = (ans * Sum[M[a[i]]]) % Mod;
    }

    printf("%lld\n", ans);
    
    #ifndef ONLINE_JUDGE
        system("pause");
    #endif
    return 0;
}
