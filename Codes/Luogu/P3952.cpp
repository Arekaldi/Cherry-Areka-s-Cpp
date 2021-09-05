#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

bool vis[310];
int sta[310], top;

signed main() {
    int T = read();
    while(T--) {
        int cnt = 0, tot = 0, res = 0, pp = 0;
        bool flag = false;
        memset(vis, false, sizeof(vis));
        memset(sta, 0, sizeof(sta));
        top = 0;
        int L = read();
        string anss; cin >> anss;
        string ans = "", an = "";
        getchar();
        for(int i = 1; i <= L; ++i) {
            string cpp; getline(cin, cpp);
            int num1 = 0, num2 = 0, num = 0, start = 0;
            if(i == 19)
                num1 = 0;
            for(int j = 0; cpp[j]; ++j) {
                if(cpp[j] == ' ')
                    continue;
                if(cpp[0] == 'E') {
                    if(pp != 0)
                        cnt = pp;
                    res = max(res, cnt), cnt--;
                    cnt = max(cnt, 0);
                    vis[sta[top--]] = false;
                    break;
                }
                if(j == 2) {
                    if(cpp[j] == 'l')
                        j = 2;
                    if(vis[cpp[j]])
                        flag = true;
                    vis[cpp[j]] = true;
                    sta[++top] = cpp[j];
                }
                num = 0;
                while(isdigit(cpp[j])) {
                    if(j == 4)
                        start = 1;
                    num = (num * 10) + (cpp[j] - '0');
                    j++;
                }
                if(num != 0) {
                    if(start and num1 == 0)
                        num1 = num;
                    else if(num2 == 0)
                        num2 = num;
                }
                // if(j == 7)
                    // cout << cpp[j] << endl;
                if(cpp[j] == 'n' and j > 4 and (num1 or num2)) {
                    cnt++;
                    break;
                }
            }
            if(num1 > num2 and num1 != 0 and num2 != 0 and pp == 0)
                pp = cnt;
            if(num2 == 62)
                num2 = 62;
            if(num1 == 0 and num2 != 0 and pp == 0)
                pp = cnt;
            if(cpp[0] == 'F')
                tot++;
            else
                tot--;
            if(tot < 0)
                flag = true;
            if(tot < pp)
                pp = 0;
        }
        if(tot != 0)
            flag = true;
        // cout << res << endl;
        while(res) {
            an += (res % 10) + '0';
            res /= 10;
        }
        string nes;
        for(int j = an.length() - 1; j >= 0; --j)
            nes += an[j];
        ans = "O(n^" + nes + ")";
        if(flag) {
            puts("ERR");
            goto Areka;
        }
        if(ans == anss)
            puts("Yes");
        else if(cnt == 0 and anss[2] == '1')
            puts("Yes");
        else
            puts("No");
        Areka:
            continue;
    }
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
