#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <algorithm>
#include <cmath>
#include <map>

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

class Person {
    public:
        int gender;
        double utr;
        bool operator < (const Person &a) const {
            return utr > a.utr;
        }
};

Person p[31];

int tot = 0;
double ans = 80;
double cap[9];

std :: map <int, bool> visStatus;

double checkStatus(int status, int n) {
    tot = 0;
    Person newPerson[9];
    int genderNumber = 0;
    double sum = 0;
    for(int i = 1; i <= n; ++i) {
        if((status >> (i - 1)) & 1)
            newPerson[++tot] = p[i], genderNumber += p[i].gender;
    }

    if(genderNumber < 2)
        return -1;

    std :: sort(newPerson + 1, newPerson + tot + 1);

    for(int i = 1; i <= tot; ++i) {
        if(cap[i] < newPerson[i].utr)
            return -1;
        if((i & 1) ^ 1 && fabs(newPerson[i].utr - newPerson[i - 1].utr) > 4.0)
            return -1;
        sum += newPerson[i].utr;
    }

    return 79.0 - sum;
}

void printStatus(int status, int n) {
    for(int i = 1; i <= n; ++i)
        if((status >> (i - 1)) & 1)
            write(i), putchar(' ');
    putchar('\n');
}

void findPerson(int n, int status, int now, int last) {
    if(visStatus[status] == 1)
        return;
    visStatus[status] = 1;
    // printStatus(status, n);
    if(now == 9) {
        double temp = checkStatus(status, n);
        ans = temp == -1 ? ans : std :: min(ans, temp);
        return;
    }

    for(int i = last + 1; i <= n; ++i) {
        if((status >> (i - 1)) & 1)
            continue;
        findPerson(n, status | (1 << (i - 1)), now + 1, i);
    }
}

int main() {
    int n = read();
    cap[1] = cap[2] = 12, cap[3] = cap[4] = 10.5, cap[5] = cap[6] = 9, cap[7] = cap[8] = 8;
    for(int i = 1; i <= n; ++i)
        scanf("%lf", &p[i].utr);

    for(int i = 1; i <= n; ++i)
        p[i].gender = read();

    std :: sort(p + 1, p + n + 1);
    
    findPerson(n, 0, 1, 0);

    if(ans == 80.0)
        puts("-1");
    else
        printf("%.2lf\n", ans);
}