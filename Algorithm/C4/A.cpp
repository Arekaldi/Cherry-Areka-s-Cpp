#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

using namespace std;

#define int long long

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
    int weight, value;
};

// int cmp(Node a, Node b) {
//     int r1 = a.value * b.weight, r2 = b.value * a.weight;
//     return r1 > r2 ? -1 : 1;
// }

signed cmp(const void *a, const void *b) {
    Node *p1 = (Node*)a, *p2 = (Node*)b;
    int r1 = p1->value * p2->weight, r2 = p2->value * p1->weight;
    return r1 > r2 ? -1 : 1;
}

Node food[1010];
int n, k;

signed main() {
    n = read(), k = read();
    for(int i = 1; i <= n; ++i)
        food[i].value = read(), food[i].weight = read();
    qsort(food + 1, n, sizeof(Node), cmp);
    // for(int i = 1; i <= n; ++i)
    //     printf("%lld %lld\n", food[i].value, food[i].weight);
    double ans = 0;
    int nowEat = 0;
    for(int i = 1; i <= n; ++i) {
        if(nowEat + food[i].weight <= k) {
            ans += food[i].value;
            nowEat += food[i].weight;
        }
        else {
            double nowEatDouble = (double)nowEat;
            double r = k - nowEatDouble;
            ans += food[i].value * r / food[i].weight;
            break;
        }
    }
    printf("%.3lf\n", ans);
    return 0;
}