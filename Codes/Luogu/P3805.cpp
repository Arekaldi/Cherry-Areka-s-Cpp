#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch = getchar();
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

const char bd = '∴', fr = '∵';
const int maxn = 31000000;

int P[31000000];
string sx, st;

signed main() {
    getline(cin, sx);
    st += fr;
    for(int i = 0; sx[i]; ++i) 
        st += bd, st += sx[i];
    
    st += bd;

    int l = st.length();

    int Mr = 0, mid = 0, ans = -2;

    for(int i = 0; i < l; ++i) {
        if(Mr > i) P[i] = min(Mr - i, P[(mid << 1) - i]);
        else P[i] = 1;
        while(st[i - P[i]] == st[i + P[i]]) P[i]++;
        if(i + P[i] > Mr) mid = i, Mr = i + P[i];
        ans = max(ans, P[i] - 1);
    }

    printf("%d\n", ans);
    
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
