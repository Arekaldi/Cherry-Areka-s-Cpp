/*
O(T(N + M + lgM + N))
*/

#include <bits/stdc++.h>

using namespace std;

inline int read() {
    int x = 0, f = 1;
    char ch = getchar();
    while(ch < '0' or ch > '9') {
        if(ch == '-') f = -1;
        ch = getchar();
    }
    while(ch >= '0' and ch <= '9') {
        x = (x << 1) + (x << 3) + (ch ^ 48);
        ch = getchar();
    }
    return x * f;
}

const int maxn = 1e6 + 1, maxm = 2e5 + 2;

int T;
queue <int> Q;

struct Node {
    int id, num;
}Cnt[maxm];

inline int G(int x) {
    return 10000 - (100 - x) * (100 - x);
}

bool Camp(Node a, Node b) {
	if(a.num == b.num)
		return a.id < b.id;
	else
	return a.num > b.num;
}

inline void init() {
    while(!Q.empty()) Q.pop();
    memset(Cnt, 0, sizeof(Cnt));
}

signed main() {
	
	freopen("grade.in", "r", stdin);
	freopen("grade.out", "w", stdout);
	
    T = read();
    int p = 0;
    while(p <= T) {
        p++;
        int N = read();
        init();
        int Mak = 0;
        for(int i = 1; i <= N; ++i) {
            int w = read();
            int x = G(w);
			Mak = Mak > x ? Mak : x;
            Cnt[x].num++;
            if(Cnt[x].num == 1) Cnt[x].id = x;
//            cout << Cnt[x].id << " " << Cnt[x].num << endl;
        }
        
        sort(Cnt + 0, Cnt + Mak + 1, Camp);
        int Max = Cnt[0].num;
        
//        for(int i = 0; i <= 10; ++i) cout << Cnt[i].id << " " << Cnt[i].num << endl;
        
        bool flag = false;
        for(int i = 0; i <= Mak; ++i) {
            if(Cnt[i].num == Max) Q.push(Cnt[i].id);
            else if(Cnt[i].num != 0){
                flag = true;
                break;
            }
        }

        if(!flag and Q.size() != 1)
            printf("Case #%d:\nBad Mushroom\n", p);
        
        else {
            printf("Case #%d:\n", p);
            while(Q.size() > 1) {
                printf("%d ", Q.front());
                Q.pop();
            }
            cout << Q.front() << endl; Q.pop();
        }

        if(p == T) break;
    }

    return 0;
}
