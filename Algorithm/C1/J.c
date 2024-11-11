#include <stdio.h>

int put[100000], len;

void Add(int n) {
    if(n % 2 == 0)
        return;
    if(n == 1) {
        put[len++] = n;
        return;
    }
    put[len++] = n;
    Add((n + 1) / 2);
    Add((n - 1) / 2);
}

int main() {
    int n;
    scanf("%d", &n);
    if(n % 2 == 0) {
        printf("-1");
        return 0;
    }
    else {
        Add(n);
        for(int i = len - 1; i >= 0; --i)
            printf("%d ", put[i]);
    }
}