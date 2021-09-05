#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

#define int long long

int n, flag = 2;

const int Mod = 998244353;

vector <int> v1, v2;

signed main() {
    n = read();

    // if(n < 9)

    for(int i = 1; i <= n; ++i) {
        char op;
        cin >> op;
        int x = read();
        if(x < 0 and op == '+' and flag == 2)
            flag = 3;
        if(x < 0 and op == '*' and flag == 2)
            flag = 4;
        if((flag == 3 and x < 0 and op =='*') or (flag == 4 and x < 0  and op =='+'))
            flag = 5;
        if(op == '+')
            v1.push_back(x);
        else
            v2.push_back(x);
    }
    
    sort(v1.begin(), v1.end());
    sort(v2.begin(), v2.end());

    switch(flag) {
        case 2: {
            int p0 = 0, p1 = 0;
            int w = 0;
            while(p0 < v1.size()) {
                w += v1[p0];
                p0++;
                w %= Mod;
            }

            while(p1 < v2.size()) {
                w = (w * v2[p1]) % Mod;
                p1++;
            }

            cout << (w % Mod + Mod) % Mod;
            break;
        }
        case 3: {
            int w = 0;
            int p0 = 0, p1 = 0;
            while(p0 < v1.size()) {
                w += v1[p0];
                p0++;
                w %= Mod;
            }
            if(w > 0) {
                while(p1 < v2.size()) {
                    w = (w * v2[p1]) % Mod;
                    p1++;
                }
                cout << (w % Mod + Mod) % Mod;
            }
            else {
                p0 = 0, p1 = 0;
                int fushu = 0;
                while(v1[p0] <= 0)
                    fushu += v1[p0], p0++;
                int zhengshu = 0;
                while(p0 < v1.size())
                    zhengshu += v1[p0], p0++;
                if(zhengshu == 0) {
                    
                }
                while(p1 < v2.size()) {
                    zhengshu = (zhengshu * v2[p1]) % Mod;
                    p1++;
                }
                int w = zhengshu + fushu;
                cout << (w % Mod + Mod) % Mod;
            }
            break;
        }
    }
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
