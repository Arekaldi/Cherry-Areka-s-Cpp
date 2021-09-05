#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

string s;
int n, len;

signed main() {
    while(n = read()) {
        getline(cin, s);
        len = s.length();
        n = len / n; // 首先算出每份的长度
        int p = n - 1, k = n - 1;
        // p是指针(红色的)
        // k是用来判断这一段走没走完
        while(true) {
            putchar(s[p]);
            p--, k--;
            // 指针左移
            if(k == -1) {
                k = n - 1;
                p = p + (n << 1);
                //这一段走完了，指针右移
            }
            // 特判一下走完或者走出去
            if(p == len - n or p >= len) {
                if(p < len)
                    putchar(s[p]);
                break;
            }
        }
        puts("");
        //结束这一行的输出
    }
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}