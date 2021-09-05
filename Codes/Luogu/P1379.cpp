#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

map <int, bool> M;

queue < pair <int, int> > q;

int a[4][4];

inline int Bfs(int s, int t) {
    q.push(make_pair(s, 0));
    while(!q.empty()) {
        int x = q.front().first, c = q.front().second;
        q.pop();
        if(M[x])
            continue;
        M[x] = true;
        if(x == t)
            return c;
        for(int i = 3; i >= 1; --i) {
            for(int j = 3; j >= 1; --j) {
                a[i][j] = x % 10;
                x /= 10;
            }
        }
        int nowx, nowy;
        for(int i = 1; i <= 3; ++i) {
            for(int j = 1; j <= 3; ++j) {
                if(a[i][j] == 0) {
                    nowx = i, nowy = j;
                    break;
                }
            }
        }
        if(nowx != 1) {
            swap(a[nowx - 1][nowy], a[nowx][nowy]);
            int nx = 0;
            for(int i = 1; i <= 3; ++i)
                for(int j = 1; j <= 3; ++j)
                    nx = nx * 10 + a[i][j];
            q.push(make_pair(nx, c + 1));
            swap(a[nowx - 1][nowy], a[nowx][nowy]);
        }
        if(nowx != 3) {
            swap(a[nowx + 1][nowy], a[nowx][nowy]);
            int nx = 0;
            for(int i = 1; i <= 3; ++i)
                for(int j = 1; j <= 3; ++j)
                    nx = nx * 10 + a[i][j];
            q.push(make_pair(nx, c + 1));
            swap(a[nowx + 1][nowy], a[nowx][nowy]);
        }
        if(nowy != 1) {
            swap(a[nowx][nowy - 1], a[nowx][nowy]);
            int nx = 0;
            for(int i = 1; i <= 3; ++i)
                for(int j = 1; j <= 3; ++j)
                    nx = nx * 10 + a[i][j];
            q.push(make_pair(nx, c + 1));
            swap(a[nowx][nowy - 1], a[nowx][nowy]);
        }
        if(nowy != 3) {
            swap(a[nowx][nowy + 1], a[nowx][nowy]);
            int nx = 0;
            for(int i = 1; i <= 3; ++i)
                for(int j = 1; j <= 3; ++j)
                    nx = nx * 10 + a[i][j];
            q.push(make_pair(nx, c + 1));
            swap(a[nowx][nowy + 1], a[nowx][nowy]);
        }
    }
}

signed main() {
    int s, t = 123804765;
    printf("%d\n", Bfs(s = read(), t));
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
