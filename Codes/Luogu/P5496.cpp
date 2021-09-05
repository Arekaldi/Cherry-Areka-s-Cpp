#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

const int maxn = 5e6 + 1;

char s[maxn];

class Perticulery_AuM {
    private:
        int len[maxn], fail[maxn], ch[maxn][26],
            num[maxn];
        int now, tot = 1, lst;

    public:

        inline void init() {
            len[1] = -1, len[0] = 0;
            fail[0] = 1;
            lst = 0, now = 0;
        }

        inline int Find_fail(int x, int i) {
            while(i - len[x] - 1 < 0 or s[i - len[x] - 1] != s[i])
                x = fail[x];
            return x;
        }

        inline void Insert(int p) {
            if(p >= 1)
                s[p] = (s[p] + lst - 97) % 26 + 97;
            // 强制在线
            int A = Find_fail(now, p);
            // 设 s[p] = X
            // 首先跳 fail 找到一个节点满足 XAX 是当前加入串的回文子串
            if(!ch[A][s[p] - 'a']) {
                // 如果没有能适配的 A 就留单个字符即 s[p]
                tot++;
                // 接下来建立新建节点的 fail 指针
                fail[tot] = ch[Find_fail(fail[A], p)][s[p] - 'a'];
                /*  从 A 出发，即可找到 XAX 的最长回文后缀 XBX，
                    将对应节点设为 fail 指针所指的对象即可。
                */
                /*
                    显然，这个节点是不需新建的，A 的前 len_b 位和后 len_b 位相同，
                    都是 B，前 len_b 位的两端根据回文串对应关系，都是 X，后面被钦定了是 X，
                    于是这个节点 XBX 肯定已经被包含了。
                */
                ch[A][s[p] - 'a'] = tot;
                len[tot] = len[A] + 2;
                num[tot] = num[fail[tot]] + 1;
            }
            now = ch[A][s[p] - 'a'];
            lst = num[now];
            printf("%d ", lst);
        }
};

Perticulery_AuM P;

signed main() {
    cin >> s;
    P.init();
    
    int len = strlen(s);
    for(int i = 0; i < len; ++i)
        P.Insert(i);

    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
