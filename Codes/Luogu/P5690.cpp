#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

int m, d;
int day[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

signed main() {
    scanf("%d-%d", &m, &d);
    int res = 0;
    if(m > 12 and m % 10 == 2)
        m = 12, res++;
    else if(m > 12 and m < 20)
        m = 12, res++;
    else if(m > 20 and m % 10 != 0)
        m %= 10, res++;
    else if(m > 20 and m % 10 == 0)
        m = 1, res += 2;
    if(day[m] < d or d == 0)
        res++;

    cout << res;
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}