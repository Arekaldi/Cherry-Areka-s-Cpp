#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <vector>

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

void getAnsSequence(int n) {
    std :: vector <int> even, odd;
    for(int i = 1; i <= n; i += 2)
        odd.push_back(i);
    for(int i = 2; i <= n; i += 2)
        even.push_back(i);

    for(int i = 0; i < even.size(); ++i)
        printf("%d ", even[i]);
    for(int i = 0; i < odd.size(); ++i)
        printf("%d ", odd[i]);
    puts("");
}

int main() {
    int T = read();
    while(T--) {
        int n = read();
        getAnsSequence(n);
    }
}