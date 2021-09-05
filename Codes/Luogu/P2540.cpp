#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

int T, n, ans;
int sum[21];

inline void Dfs(int x, int cst) {
    if(cst >= ans)
        return;
    if(x == 0) {
        ans = min(ans, cst);
        return;
    }

    for(int i = 3; i <= 13; ++i) {
        if(sum[i] < 3)
            continue;
        for(int j = i + 1; j <= 14; ++j) {
            if(sum[j] < 3)
                break;
            for(int k = i; k <= j; ++k)
                sum[k] -= 3;
            Dfs(x - ((j - i + 1) * 3), cst + 1);
            for(int k = i; k <= j; ++k)
                sum[k] += 3;
        }
    }

    for(int i = 3; i <= 12; ++i) {
        if(sum[i] < 2)
            continue;
        for(int j = i + 1; j <= 14; ++j) {
            if(sum[j] < 2)
                break;
            if(j - i >= 2) {
                for(int k = i; k <= j; ++k)
                    sum[k] -= 2;
                Dfs(x - ((j - i + 1) * 2), cst + 1);
                for(int k = i; k <= j; ++k)
                    sum[k] += 2;
            }
        }
    }

    for(int i = 3; i <= 10; ++i) {
        if(sum[i] == 0)
            continue;
        for(int j = i + 1; j <= 14; ++j) {
            if(sum[j] == 0)
                break;
            if(j - i >= 4) {
                for(int k = i; k <= j; ++k)
                    sum[k]--;
                Dfs(x - (j - i + 1), cst + 1);
                for(int k = i; k <= j; ++k)
                    sum[k]++;
            }
        }
    }
    
    int cnt1 = 0, cnt2 = 0, cnt3 = 0, cnt4 = 0;
    for(int i = 2; i <= 14; ++i)
        cnt1 += (sum[i] == 1), cnt2 += (sum[i] == 2),
        cnt3 += (sum[i] == 3), cnt4 += (sum[i] == 4);
    int ss = 0;
    cout << cst << endl;
    for(int i = 1; i <= 14; ++i) {
        cout << i << " " << sum[i] << endl;
    }
//    cout << cst << " " << cnt1 << " " << cnt2 << " " << cnt3 << " " << cnt4 << endl;
    if(cnt4 * 2 <= cnt2)
        ss += cnt4, cnt2 -= 2 * cnt4, cnt4 = 0;
    else
        ss += (cnt2 >> 1), cnt4 -= (cnt2 >> 1), cnt2 = (cnt2 & 1);
    if(cnt4 != 0) {
        if(cnt4 * 2 <= cnt1)
            ss += cnt4, cnt1 -= 2 * cnt4, cnt4 = 0;
        else
            ss += (cnt1 >> 1), cnt4 -= (cnt1 >> 1), cnt1 = (cnt1 & 1);
        if(cnt4 != 0)
            ss += cnt4;
    }
    if(cnt2 != 0) {
        int w = min(cnt2, cnt3);
        ss += w, cnt2 -= w, cnt3 -= w;
        if(cnt2 != 0)
            ss += cnt2;
        int ww = min(cnt1, cnt3);
        ss += ww, cnt1 -= ww, cnt3 -= ww;
        ss += cnt1 + min(sum[1], 1) + cnt3;
    }
    else {
        int w = min(cnt1, cnt3);
        ss += w, cnt1 -= w, cnt3 -= w;
        ss += cnt1 + cnt3 + min(sum[1], 1);
    }
    if(cst + ss < ans)
        ans = cst + ss;
    return;
}

signed main() {
    T = read(), n = read();
    while(T--) {
        for(int i = 1; i <= 14; ++i)
            sum[i] = 0;
        ans = n;
        for(int i = 1; i <= n; ++i) {
            int a = read(), b = read();
            if(a == 0)
                sum[1]++;
            else if(a == 1)
                sum[14]++;
            else
                sum[a]++;
        }

//         for(int i = 1; i <= 14; ++i) {
//             cout << i << " " << sum[i] << endl;
//         }

        Dfs(n, 0);
        printf("%d\n", ans);
    }
    
    #ifndef Areka
        getchar();
    #endif  

    return 0;
}