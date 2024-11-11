#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int read(void) {
    int x, f = 1;
    char ch;
    while(!isdigit(ch = getchar()))
    (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 1) + (x << 3) + (ch ^ 48));
    return x * f;
}

void write(int x)
{
    if(x < 0)
        putchar('-'), x = -x;
    if(x > 9)
        write(x / 10);
    putchar(x % 10 + '0');
    return;
}

int T, n, k;
int a[100010];
int lst[100010], nxt[100010];
int lstpos[100010], nxtpos[100010];
int pos[100010];

int main() {
    T = read();
    while(T--) {
        n = read(), k = read();
        memset(lstpos, 0, sizeof(lstpos));
        memset(nxtpos, 0, sizeof(nxtpos));
        memset(lst, 0, sizeof(lst));
        memset(nxt, 0, sizeof(nxt));
        memset(pos, 0, sizeof(pos));

        for(int i = 1; i <= n; i++)
            a[i] = read();
        
        for(int i = 1; i <= n; ++i) {
            if(pos[a[i]])
                lst[i] = pos[a[i]];
            pos[a[i]] = i;
        }
        memset(pos, 0, sizeof(pos));
        for(int i = n; i >= 1; --i) {
            if(pos[a[i]])
                nxt[i] = pos[a[i]];
            pos[a[i]] = i;
        }

        lstpos[1] = 0, nxtpos[n] = 0;
        for(int i = 2; i <= n; ++i)
            lstpos[i] = i - 1, nxtpos[i - 1] = i;

        int tot = 0;
        while(tot != n) {
            tot++;
            printf("%d ", k);
            if(tot == n)
                break;
            if(lst[k] || nxt[k]) {
                int now = k;
                if(lst[k] && nxt[k]) {
                    k = (k - lst[k] + 1) <= (nxt[k] - k + 1) ?
                        lst[k] : nxt[k];
                }
                else
                    k = lst[k] ? lst[k] : nxt[k];
                nxt[lst[now]] = nxt[now];
                lst[nxt[now]] = lst[now];
                nxtpos[lstpos[now]] = nxtpos[now];
                lstpos[nxtpos[now]] = lstpos[now]; 
            } 
            
            else {
                int now = k;
                if(lstpos[k] || nxtpos[k]) {
                    if(lstpos[k] && nxtpos[k])
                        k = (k - lstpos[k] + 1) <= (nxtpos[k] - k + 1) ?
                            lstpos[k] : nxtpos[k];
                    else
                        k = lstpos[k] ? lstpos[k] : nxtpos[k];
                    nxtpos[lstpos[now]] = nxtpos[now];
                    lstpos[nxtpos[now]] = lstpos[now];
                }
            }
        }
        putchar('\n');
    }
}