#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

const int M = 2e7 + 10, N = 30010;

string s;
int n, nt;

struct Node {
    int ch[2], mark;
}T[M];

class Triet {
    public :
        void Insert(int x) {
            int p = 0;
            for(int i = x; s[i]; ++i) {
                int cht = s[i] - '0';
                if(!T[p].ch[cht]) T[p].ch[cht] = ++nt;
                p = T[p].ch[cht];
                T[p].mark++;
            }
        }
        void Ask(int p) {
            // cout << p << endl;
            if(T[p].mark > 1) cout << T[p].mark << endl;
            if(T[p].ch[0]) Ask(T[p].ch[0]);
            if(T[p].ch[1]) Ask(T[p].ch[1]);
        }
}Trie;

signed main() {
    n = read();
    getline(cin, s);
    int num = 0;
    for(int o = 0; s[o]; ++o) 
        Trie.Insert(o);

    Trie.Ask(0);
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
