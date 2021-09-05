#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

const int maxT = 5e2 + 1, maxn = 1e5 + 1;

int n, m, T, Len;

int pos[maxn], L[maxT], R[maxT];
char Lz[maxT], s[maxn];
int sum[maxT][26], num[26];

inline char is(char x) {
    if(x >= 'A' and x <= 'Z')
        return x;
    else
        return x - ('a' - 'A');
}

inline void Pushdown(int x) {
    int p = pos[x];

    if(Lz[p]) {
        for(int i = L[p]; i <= R[p]; ++i)
            s[i] = Lz[p];
        for(int i = 0; i < 26; ++i)
            sum[p][i] = 0;
        sum[p][Lz[p] - 'A'] = Len;
        Lz[p] = 0;
    }

    return;
}

inline int Ask(int x, int y, char k) {
    int p = pos[x], q = pos[y];
    int ans = 0;
    
    Pushdown(x), Pushdown(y);

    if(p == q) {
        for(int i = x; i <= y; ++i) {
            ans += (s[i] == k);
        }
        return ans;
    }

    for(int i = p + 1; i < q; ++i)
        ans += (Lz[i] == 0) ? sum[i][k - 'A'] : ((Lz[i] == k) * (R[i] - L[i] + 1));

    for(int i = x; i <= R[p]; ++i)
        ans += (s[i] == k);
    
    for(int i = L[q]; i <= y; ++i)
        ans += (s[i] == k);

    return ans;
}

//sdsd

inline void Infer(int x, int y) {

    for(int i = 0; i < 26; ++i)
        num[i] = 0;

    int p = pos[x], q = pos[y];

    Pushdown(x), Pushdown(y);

    if(p == q) {
        for(int i = x; i <= y; ++i)
            num[s[i] - 'A']++;
        return;
    }

    for(int i = p + 1; i < q; ++i) {
        if(Lz[i]) {
            num[Lz[i] - 'A'] += (R[i] - L[i] + 1);
        }
        else {
            for(int k = 0; k < 26; ++k)
                num[k] += sum[i][k];
        }
    }

    for(int i = x; i <= R[p]; ++i)
        num[s[i] - 'A']++;

    for(int i = L[q]; i <= y; ++i)
        num[s[i] - 'A']++;

    return;
}

inline void Change(int x, int y, char k) {
    
    if(y < x)
        return;

    int p = pos[x], q = pos[y];

    Pushdown(x), Pushdown(y);

    if(p == q) {
        for(int i = x; i <= y; ++i) {
            sum[p][s[i] - 'A']--;
            sum[p][k - 'A']++;
            s[i] = k;
        }
        return;
    }

    for(int i = p + 1; i < q; ++i)
        Lz[i] = k;

    for(int i = x; i <= R[p]; ++i) {
        sum[p][s[i] - 'A']--, sum[p][k - 'A']++;
        s[i] = k;
    }

    for(int i = L[q]; i <= y; ++i) {
        sum[q][s[i] - 'A']--, sum[q][k - 'A']++;
        s[i] = k;
    }

    return;
}

inline void Order(int x, int y, int opt) {
    Infer(x, y);

    if(opt == 1) {
        for(int i = 0; i < 26; ++i) {
            Change(x, x + num[i] - 1, i + 'A');
            x += num[i];
            num[i] = 0;
        }
    }
    
    else {
        for(int i = 25; i >= 0; --i) {
            Change(x, x + num[i] - 1, i + 'A');
            x += num[i];
            num[i] = 0;
        }
    }

    return;
}

inline void Print() {
    int x = 1, y = n;
    int p = pos[x], q = pos[y];
    Pushdown(x), Pushdown(y);
    for(int i = p; i <= q; ++i) {
        for(int j = L[i]; j <= R[i]; ++j) {
            if(Lz[i])
                putchar(Lz[i] - 'A' + 'a');
            else
                putchar(s[j] - 'A' + 'a');
        }
    }
}

signed main() {

    // #define Areka
    #ifdef Areka
        freopen("1.txt", "r", stdin);
        freopen("wans.txt", "w", stdout);
    #endif

    n = read(), m = read();

    Len = T = sqrt(n);

    for(int i = 1; i <= T; ++i)
        L[i] = (i - 1) * Len + 1, R[i] = i * Len;
    
    if(R[T] < n) {
        T++;
        L[T] = R[T - 1] + 1, R[T] = n;
    }

    for(int i = 1; i <= T; ++i)
        for(int j = L[i]; j <= R[i]; ++j)
            pos[j] = i;

    for(int i = 1; i <= n; ++i) {
        cin >> s[i];
        s[i] = is(s[i]);
        sum[pos[i]][s[i] - 'A']++;
    }

    for(int i = 1; i <= m; ++i) {
        int x, y, opt;
        scanf("%d%d%d", &x, &y, &opt);
        Order(x, y, opt);
    }

    Print();
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
