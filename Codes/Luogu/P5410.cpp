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

const int maxn = 2e7 + 1;
int nxt[maxn], ext[maxn];

char s[maxn], t[maxn];
int lens, lent;

inline void Get_nxt() {
    nxt[0] = lent;
    int cnt = 0;
    while(t[cnt] == t[cnt + 1] and cnt + 1 < lent) cnt++;
    nxt[1] = cnt;
    // nxt1暴力匹配即可
    int pos = 1;
    for(int i = 2; i < lent; ++i) {
        if(i + nxt[i - pos] < nxt[pos] + pos)
            nxt[i] = nxt[i - pos];
        //若没有越界，则更新
        else {
            //若越界，则去最小值，并往后暴力更新
            int now = nxt[pos] + pos - i;
            now = now < 0 ? 0 : now;
            while(t[now] == t[i + now] and i + now < lent)
                now++;
            nxt[i] = now;
            pos = i;
        }
    }
    return;
}

signed main() {
    scanf("%s%s", s, t);

    lens = strlen(s), lent = strlen(t);
    
    Get_nxt();

    int cnt = 0;
    int Len = min(lent, lens);
    while(s[cnt] == t[cnt] and cnt < Len) cnt++;
    ext[0] = cnt;
    //ext0暴力匹配，从0开始
    int pos = 0;
    for(int i = 1; i < lens; ++i) {
        if(i + nxt[i - pos] < ext[pos] + pos)
            ext[i] = nxt[i - pos];
        //若没有越界，则更新
        else {
            //若越界，则去最小值，并往后暴力更新
            int now = ext[pos] + pos - i;
            now = now < 0 ? 0 : now;
            while(t[now] == s[i + now] and i + now < lens and now < lent)
                now++;
            ext[i] = now;
            pos = i;
        }
    }

    int ans = 0;

    for(int i = 0; i < lent; ++i)
        ans ^= ((i + 1) * (nxt[i] + 1));

    printf("%lld\n", ans);

    ans = 0;
    for(int i = 0; i < lens; ++i)
        ans ^= ((i + 1) * (ext[i] + 1));

    printf("%lld\n", ans);

    return 0;
}
