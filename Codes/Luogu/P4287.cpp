#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

const int maxn = 5e6 + 10;

char ss[maxn], s[maxn];
int P[maxn], mx, mid, ans = -1;
int n, len = 1;

const char bd = '&', fr = '^';



signed main() {
    n = read();
    scanf("%s", (ss + 1));

    s[1] = bd;
    for(int i = 1; i <= n; ++i)
        s[++len] = ss[i], s[++len] = bd;

    s[++len]  = fr;

    for(int i = 1; i <= len; ++i) {
        if(mx > i)
            P[i] = min(mx - i, P[(mid << 1) - i]);
        else
            P[i] = 1;
        while(s[i - P[i]] == s[i + P[i]]) P[i]++;
        if(i + P[i] > mx) {
            if(i & 1) 
                for(int j = max(mx, i + 4); j < i + P[i]; ++j)
                    if(!((j - i) & 3) and P[i - ((j - i) >> 1)]  > ((j - i) >> 1))
                        ans = max(ans, (j - i));
            
            mid = i, mx = i + P[i];
        }
    }
    
    cout << ans << endl;
    
    return 0;
}

