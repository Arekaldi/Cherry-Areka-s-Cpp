#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

const int maxn = 5e5 + 1;

char s[maxn];
int n;
string ans;

signed main() {
    n = read();
    
    int len = 0;
    for(int i = 1; i <= n; ++i) {
        s[++len] = getchar(); getchar();
    }

    ans += '.';

    // cout << len << endl;

    int head = 1;
    while(head <= len) {
        if(s[head] < s[len]) ans += s[head], head++;
        else if(s[len] < s[head]) ans += s[len], len--;
        else if(s[len] == s[head]) {
            int head1 = head, len1 = len;
            int flag = 0;
            while(head1 <= len1) {
                if(s[head1] < s[len1]) {flag = 1; break;}
                else if(s[head1] > s[len1]) {flag = 2; break;}
                else head1++, len1--;
            }
            if(flag == 0) {
                while(head <= len) ans += s[head], head++;
                break;
            }
            else {
                ans += s[flag == 1 ? head : len];
                flag == 1 ? head++ : len--;
            }
        }
    }

    // cout << ans << endl;
//    cout << ans.length() << endl;
    for(int i = 1; i <= n; ++i) {
        int num = 0;
        cout << ans[i];
        if(i % 80 == 0) cout << endl;
    }
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
