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

const int maxM = 10000010, maxn = 100100, Inf = 0x7ffffff;

struct edge {
    int to, val, next;
}E[maxM];

int n, m, s, t;

int tot = -1, dis[maxn], head[maxn];
int cur[maxn];


void Add_edge(int u, int v, int w) {
    E[++tot].to = v, E[tot].val = w, E[tot].next = head[u];
    head[u] = tot;
}

queue <int> Q;
bool Bfs(int s, int t) {
    for(int i = s; i <= t; ++i) dis[i] = -1;

    while(!Q.empty()) Q.pop();

    Q.push(s); dis[s] = 1;

    while(!Q.empty()) {
        int x = Q.front(); Q.pop();

        for(int i = head[x]; i > -1; i = E[i].next) {
            int v = E[i].to;
            if(dis[v] == -1 and E[i].val) {
                dis[v] = dis[x] + 1;
                Q.push(v);
            }
        }
    }

    return dis[t] != -1;
}

int Dfs(int x, int flew, int t) {
    if(x == t) return flew;

    int rest = flew;

    for(int i = cur[x]; i > -1 && rest; i = E[i].next) {
        int v = E[i].to, f = E[i].val;

        cur[x] = i;

        if(!f or dis[v] != dis[x] + 1) continue;

        int k = Dfs(v, min(rest, f), t);
        E[i].val -= k, E[i ^ 1].val += k;
        rest -= k;

        if(!k) dis[v] = 0;
    }
    return flew - rest;
}

int Dinic(int s, int t) {
    int ans = 0, k;
    while(Bfs(s, t)) {
        memcpy(cur, head, sizeof(head));
        k = Dfs(s, INT_MAX, t);
        ans += k;
    }
    return ans;
}

inline int id(int hang, int lie) {
    return (hang - 1) * n + lie;
}

int gx[] = {0, 0, 1, -1}, gy[] = {1, -1, 0, 0};
int ans;

signed main() {
    memset(head, -1, sizeof(head));
    m = read(), n = read();
    s = 0, t = m * n + 1;
    
    for(int i = 1; i <= m; ++i) {
        for(int j = 1; j <= n; ++j) {
            int x = read(); ans += x;
            if((i + j) & 1) {
                Add_edge(s, id(i, j), x), Add_edge(id(i, j), s, 0);
                
                for(int k = 0; k < 4; ++k) {
                    int x = i + gx[k], y = j + gy[k];
                    if(x < 1 or y < 1 or y > n or x > m) continue;
                    Add_edge(id(i, j), id(x, y), Inf), Add_edge(id(x, y), id(i, j), 0);
                }
            }
                
            else
                Add_edge(id(i, j), t, x), Add_edge(t, id(i, j), 0);
        }
    }

    ans = ans - Dinic(s, t);
    cout << ans << endl;
    // cout << ans << endl;
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif


    return 0;
}

//126929

/*
24 20 97 306 251 297 261 997 30 956 547 477 479 874 260 686 299 810 640 75 515 121 537 780 573 295 578 719 583 732 20 896 663 796 837 778 576 41 439 841 217 77 190 536 945 364 291 753 940 981 626 687 705 676 516 332 172 648 180 322 120 557 868 173 308 420 244 204 307 64 988 406 165 647 800 356 137 874 973 823 810 607 529 154 23 159 652 322 927 905 46 695 420 336 752 427 50 186 214 699 29 333 575 941 109 943 367 77 280 339 969 465 888 434 33 627 540 673 1 635 763 79 354 616 607 739 119 268 952 977 814 459 505 486 641 176 858 316 655 708 183 767 315 923 724 280 992 938 309 996 989 840 973 657 257 929 771 515 995 176 455 950 294 749 272 44 207 512 797 792 3 538 226 646 819 920 51 839 45 195 753 784 226 577 232 203 478 764 781 286 176 311 577 340 70 514 644 194 459 628 886 668 923 324 564 934 670 651 167 283 994 374 473 765 686 159 185 955 121 316 882 350 634 307 507 647 139 770 505 604 966 273 658 724 707 707 132 266 26 590 751 454 625 730 842 141 527 376 451 626 261 258 892 478 122 271 211 860 870 812 122 17 671 277 221 407 617 797 34 152 824 677 58 471 95 797 413 393 478 890 32 5 750 742 405 519 358 388 229 232 10 804 326 447 292 339 61 646 691 383 549 178 774 938 514 929 933 977 508 473 41 645 295 554 614 791 789 196 844 317 74 695 676 994 936 384 320 838 835 639 745 720 736 204 364 467 924 99 251 555 28 609 98 455 391 611 456 105 386 504 452 588 640 256 567 695 134 397 820 229 180 264 966 552 425 164 451 634 863 722 929 681 846 907 903 405 837 189 49 456 717 717 429 14 192 997 150 304 685 325 38 35 705 868 521 885 21 268 474 288 487 221 429 786 813 345 287 666 933 976 946 494 675 783 999 74 169 76 271 84 927 85 188 259 391 81 943 609 907 799 442 545 521 286 777 977 357 976 52 672 151 537 276 142 927 723 563 528 187 522 950 581 770 69 860 179 200 798 753 83 438 522 942 805 270 292 386 435 73 131 976 143 335 108 735 402 518 835 89 212 236 446 
*/