#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

const int maxn = 2e2 + 1;

class Robot {
    public:
        int x, y, fc;
        int srk;
};

class Tank {
    public:
        int p1, p2;
        int w1, w2, pl;
        int bot, top;
        int st[201];
        int fc;
};

Robot r;
Tank t;

bool flag = false;
int HeFa = 0;
int n, m;
int mp[maxn][maxn];
int wg[] = {-1, -1, 1, 1};
int cle[] = {1, -1};

namespace Operator_Set {
    inline bool Walk(int wk) {
        if(r.fc == 0 or r.fc == 2) {
            int nx = r.x + wg[r.fc] * wk;
            if(nx < 0 or nx >= n)
                return false;
        }
        else {
            int ny = r.y + wg[r.fc] * wk;
            if(ny < 0 or ny >= m)
                return false;
        }

        while(wk--) {
            if(r.fc == 0 or r.fc == 2) {
                r.x += wg[r.fc];
                if(mp[r.x][r.y] != 0)
                    return false;
            }
            else {
                r.y += wg[r.fc];
                if(mp[r.x][r.y] != 0)
                    return false;
            }
        }

        return true;
    }
    
    inline bool Circle(int x, int opt) {
        if(!opt)
            t.fc = (t.fc + cle[x] + 4) % 4;
        else
            r.fc = (r.fc + cle[x] + 4) % 4;
        return true;
    }
    
    inline bool GtinFire(int x) {
        if(t.w1 + t.w2 >= t.pl)
            return false;
        t.p1 -= (x & 1), t.p2 -= (x ^ 1);
        t.w1 += (x & 1), t.w2 += (x ^ 1);
        t.st[++t.top] = (x & 1);
        return true;
    }
    
    inline bool Fire() {
        if((t.w1 == 0 and t.w2 == 0) or t.top < t.bot)
            return true;
            
        int x = r.x, y = r.y;
        int lst = t.st[t.top--];
        t.w1 -= (lst & 1), t.w2 -= (lst ^ 1);
        while(true) {
            if(t.fc == 0 or t.fc == 2) {
                x += wg[t.fc];
                if(x < 0 or x >= n or y < 0 or y >= m)
                    break;
                if(mp[x][y] != 0 and mp[x][y] != 3) {
                    if(mp[x][y] == 1)
                        break;
                    if(mp[x][y] == 2) {
                        if(lst == 0)
                            mp[x][y] = 5;
                        else
                            mp[x][y] = 0, r.srk++;
                        break;
                    }
                    if(mp[x][y] == 5) {
                        mp[x][y] = 0, r.srk++;
                        break;
                    }
                }
            }
            if(t.fc == 1 or t.fc == 3) {
                y += wg[t.fc];
                if(x < 0 or x >= n or y < 0 or y >= m)
                    break;
                if(mp[x][y] != 0 and mp[x][y] != 3) {
                    if(mp[x][y] == 1)
                        break;
                    if(mp[x][y] == 2) {
                        if(lst == 0)
                            mp[x][y] = 5;
                        else
                            mp[x][y] = 0, r.srk++;
                        break;
                    }
                    if(mp[x][y] == 5) {
                        mp[x][y] = 0, r.srk++;
                        break;
                    }
                }
            }
        }
        return true;
    }

    inline void Print(bool opt) {
        flag = true;
        HeFa = 1;
        puts(opt ? "Complete" : "ERROR");
        printf("%d %d\n", r.x, r.y);
        printf("%d\n", r.srk);
        printf("%d %d %d %d\n", t.fc, r.fc, t.p1, t.p2);
    }
}

using namespace Operator_Set;

signed main() {
    #define Areka
    #ifdef Areka
        freopen("robo.in", "r", stdin);
        freopen("robo.out", "w", stdout);
    #endif
    
    int T = read();
    while(T--) {
        flag = false, HeFa = 0;
        t.p1 = t.p2 = t.w1 = t.w2 = 0, t.pl = 0;
        t.fc = r.fc = r.x = r.y = 0;
        t.bot = t.top = 1;
        r.srk = 0;
        n = read(), m = read();
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j)
                mp[i][j] = read();
        r.x = read(), r.y = read(), t.pl = read(), t.p1 = read(), t.p2 = read();
        int k = read();
        for(int i = 1; i <= k; ++i) {
        	if(HeFa != 0) {
        		string s;
        		getline(cin, s);
        		continue;
        	}
            string opt;
            cin >> opt;
            Robot r1 = r;
            Tank t1 = t;
            if(opt == "FT") {
                int x = read();
                if((x < 0 or x > 1) or !Circle(x, 0)) {
                    r = r1, t = t1;
                    Print(false);
                }
            }
            else if(opt == "FF") {
                int x = read();
                if((x < 0 or x > 1) or !GtinFire(x)) {
                    r = r1, t = t1;
                    Print(false);
                }
            }
            else if(opt == "FE") {
                char ch = getchar();
                if(ch == ' ' or !Fire()) {
                    r = r1, t = t1;
                    Print(false);
                }
            }
            else if(opt == "WT") {
                int x = read();
                if((x < 0 or x > 1) or !Circle(x, 1)) {
                    r = r1, t = t1;
                    Print(false);
                }
            }
            else if(opt == "WG") {
                int x = read();
                if((x < 0 or x >= max(m, n)) or !Walk(x)) {
                    r = r1, t = t1;
                    Print(false);
                }
            }
            else if(opt == "END") {
                r = r1, t = t1;
                Print(true);
                getchar();
            }
        }

        if(!flag)
            Print(false);
    }

    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
