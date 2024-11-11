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

#define int long long

void write(int x)
{
    if(x < 0)
        putchar('-'), x = -x;
    if(x > 9)
        write(x / 10);
    putchar(x % 10 + '0');
    return;
}

int cProblem[10010], eProblem[10010];
int n, A;

int max2(int a, int b) {
    return a > b? a : b;
}
int min2(int a, int b) {
    return a < b? a : b;
}

signed main() {
    int T = read();
    while(T--) {
        n = read(), A = read();
        for(int i = 1; i <= n; ++i)
            cProblem[i] = read();
        for(int i = 1; i <= n; ++i)
            eProblem[i] = read();
        int isPossible = 1;
        for(int i = 1; i <= n; ++i) {
            if(cProblem[i] >= 0 && eProblem[i] >= 0) {
                if(A >= cProblem[i] + eProblem[i])
                    A += cProblem[i] + eProblem[i];
                else if(A >= max2(cProblem[i], eProblem[i]))
                    A += max2(cProblem[i], eProblem[i]);
                else if(A >= min2(cProblem[i], eProblem[i]))
                    A += min2(cProblem[i], eProblem[i]);
                else {
                    printf("%d\n", i - 1);
                    isPossible = 0;
                    break;
                }
            }
            else {
                if(A >= max2(cProblem[i], eProblem[i]))
                    A += max2(cProblem[i], eProblem[i]);
                else if(A >= min2(cProblem[i], eProblem[i]))
                    A += min2(cProblem[i], eProblem[i]);
                else {
                    printf("%d\n", i - 1);
                    isPossible = 0;
                    break;
                }
            }
        }
        if(isPossible) {
            write(n);
            putchar('\n');
        }
    }
}