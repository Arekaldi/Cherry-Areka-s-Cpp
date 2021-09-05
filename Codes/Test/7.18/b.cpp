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

string mh;
vector <int> pos;
vector <int> ans;

signed main() {
    #define Areka
    #ifdef Areka
        freopen("b.in", "r", stdin);
        freopen("b.out", "w", stdout);
    #endif

    getline(cin, mh);
    int len = mh.length();
    for(int i = 0; i < len; ++i) {
        if(i == 0 or ((mh[i] == '+' or mh[i] == '-') and (mh[i - 1] >= '0' and mh[i - 1] <= '9')))
            pos.push_back(i);
    }

    int now = 0;
    for(int i = 0; i < pos.size(); ++i) {
        int ed = i == pos.size() - 1 ? len : pos[i + 1];
        int cnt = 0, num = 0, cnt_num = 0;
        for(int j = now; j < ed; ++j) {
            if(mh[j] == '+' or mh[j] == '-')
                cnt += (mh[j] == '+' ? 1 : -1);
            else if(mh[j] != '(')
                num = (num << 1) + (num << 3) + (mh[j] ^ 48);
            else {
                int k;
                for(k = j + 1; mh[k] != ')'; ++k)
                    cnt_num = (cnt_num << 1) + (cnt_num << 3) + (mh[k] ^ 48);
                j = k;
            }
        }
        ans.push_back(cnt * num * (cnt_num == 0 ? 1 : cnt_num));
        now = ed;
    }

    int Ans = 0;
    for(int i = 0; i < ans.size(); ++i)
        Ans += ans[i];

    printf("%lld\n", Ans);
    
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
