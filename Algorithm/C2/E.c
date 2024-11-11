#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

long long read(void) {
    long long x, f = 1;
    char ch;
    while(!isdigit(ch = getchar()))
    (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 1) + (x << 3) + (ch ^ 48));
    return x * f;
}

void write(long long x)
{
    if(x < 0)
        putchar('-'), x = -x;
    if(x > 9)
        write(x / 10);
    putchar(x % 10 + '0');
    return;
}

long long A[210][210], B[210][210];
long long C[210][210];

int main() {
    int T = read();
    while(T--) {
        long long n = read();
        memset(C, 0, sizeof(C));
        for(int i = 1; i <= n; ++i)
            for(int j = 1; j <= n; ++j)
                A[i][j] = read();
        for(int i = 1; i <= n; ++i)
            for(int j = 1; j <= n; ++j)
                B[i][j] = read();
        for(int i = 1; i <= n; ++i)
            for(int j = 1; j <= n; ++j)
                for(int k = 1; k <= n; ++k)
                    C[i][j] += A[i][k] * B[k][j];
        for(int i = 1; i <= n; ++i) {
            for(int j = 1; j <= n; ++j)
                write(C[i][j]), putchar(' ');
            putchar('\n');
        }
    }
    return 0;
}