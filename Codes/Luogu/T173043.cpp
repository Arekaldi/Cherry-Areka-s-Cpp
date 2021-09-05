#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

const int maxn = 1e5 + 1;

int n;

int Cnt1, Cnt2, Cnt3, Cnt4, ans;

signed main() {
    n = read();
    for(int i = 1; i <= n; ++i) {
        string s;
        getline(cin, s);
        switch(s[0]) {
            case 'M' : Cnt1++; break;
            case 'C' : Cnt2++; break;
            case 'O' : Cnt3++; break;
            case 'I' : Cnt4++; break;
            default : break;
        }
    }

    cout << Cnt1 * Cnt3 * Cnt4 + Cnt1 * Cnt2 * Cnt3 + Cnt1 * Cnt2 * Cnt4 + Cnt2 * Cnt3 * Cnt4 << endl;


    return 0;
}

/*
1 + 2 + 2 + 
*/

/*
123 1
124 2
234 2
1
*/