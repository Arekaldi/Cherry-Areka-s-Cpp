#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}
int n, k, ans;

vector <int> v;
inline int G(int n, int x) {
    v.clear();
    for(int i = 2; i * i <= x; ++i) {
        if(x % i == 0)
            v.push_back(i);
        while(x % i == 0)
            x /= i;
    }
    if(x > 1)
        v.push_back(x);
    int sum = 0;
    for(int i = 1; i < (1 << v.size()); ++i) {
        int z = 1, num = 0;
        for(int j = 0; j < v.size(); ++j)
            if((i >> j) & 1)
                z *= v[j], ++num;
        if(num & 1)
            sum += n / z;
        else
            sum -= n / z;
    }
    return n - sum;
}

signed main() {
    n = read(), k = read();
    int Up = min(n, k);

    for(int d = 1; d <= Up; ++d)
        ans += G(n / d, k);
    
    printf("%d\n", ans * k);
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
