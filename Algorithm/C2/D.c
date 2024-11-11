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

char *Numbera, *Numberb;
char Numberc[10010];
int lenc;

int main() {
    int T = read();
    // int T = 1;
    Numbera = (char *)malloc(20010 * sizeof(char));
    Numberb = (char *)malloc(20010 * sizeof(char));
    while(T--) {
        fgets(Numbera, 2009, stdin), fgets(Numberb, 2009, stdin);
        memset(Numberc, 0, sizeof(Numberc));
        int lena = strlen(Numbera) - 1, lenb = strlen(Numberb) - 1;
        if(lena < lenb) {
            char *temp = Numbera;
            Numbera = Numberb;
            Numberb = temp;
            int templen = lena;
            lena = lenb;
            lenb = templen;
        }
        int i = lena - 1;
        lenc = lena + lenb;
        for(int j = lenb - 1; j >= 0; --j) {
            while(i >= 0) {
                int num1 = Numbera[i] - '0', num2 = Numberb[j] - '0';
                int mul = num1 * num2;
                int carry = mul / 10;
                int now = lena - i - 1 + lenb - j - 1;
                mul %= 10;
                Numberc[now] += mul, Numberc[now + 1] += carry;
                carry = 0;
                while(Numberc[now] > 9) {
                    carry = Numberc[now] / 10;
                    Numberc[now] %= 10;
                    now++;
                    lenc = now > lenc ? now : lenc;
                    Numberc[now] += carry, carry = 0;
                }
                i--;
            }
            i = lena - 1;
        }
        while(Numberc[lenc - 1] == 0 && lenc >= 1)
            lenc--;
        if(lenc == 0 && Numberc[0] == 0) {
            putchar('0');
            putchar('\n');
            continue;
        }
        for(int i = lenc - 1; i >= 0; --i)
            putchar(Numberc[i] + '0');
        putchar('\n');
    }
}