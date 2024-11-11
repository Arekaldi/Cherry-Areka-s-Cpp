#include <assert.h>
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

struct Node {
    int x, y;
};

struct Node Pos[2000001];
int tot = 0;

int main() {
    int n = read(), q = read();
    for(int i = 1; i <= n; ++i)
        Pos[n - i + 1].x = i, Pos[n - i + 1].y = 0;
    for(int i = 1; i <= q; ++i) {
        int opt = read();
        if(opt == 1) {
            tot++;
            Pos[n + tot].x = Pos[n + tot - 1].x, Pos[n + tot].y = Pos[n + tot - 1].y;
            char X;
            scanf("%c", &X);
            switch(X) {
                case 'R':
                    Pos[n + tot].x++;
                    break;
                case 'L':
                    Pos[n + tot].x--;
                    break;
                case 'U':
                    Pos[n + tot].y++;
                    break;
                case 'D':
                    Pos[n + tot].y--;
                    break;
                default:
                    assert(0);
                    break;
            }
        }
        else {
            int ques = read();
            printf("%d %d\n", Pos[n + tot - ques + 1].x, Pos[n + tot - ques + 1].y);
        }
    }
}