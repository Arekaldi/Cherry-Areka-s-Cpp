#include <stdio.h>

int t, m, n;

int A(int i, int j) {
    if(i == 0)
        return j + 1;
    else if(i > 0 && j == 0)
        return A(i - 1, 1);
    else
        return A(i - 1, A(i, j - 1));
}

int main() {
    scanf("%d", &t);
    for(int i = 0; i < t; i++) {
        scanf("%d %d", &m, &n);
        printf("%d\n", A(m, n));
    }
    return 0;
}