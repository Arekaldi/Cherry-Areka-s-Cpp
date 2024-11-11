#include <stdio.h>
#include <math.h>

int t, n, a[100], tot;

void FindNumber(int x) {
    if(x == n) {
        int res = 0;
        for(int i = 0; i < x; ++i)
            res = res ^ a[i];
        if(res != 0)
            return;
        if(a[x - 1] < 13) {
            for(int i = 0; i < x; ++i)
                printf("%d ", a[i]);
        printf("\n");
        }
    }
    else {
        int up = 24;
        for(int i = (x == 0 ? 0 : a[x - 1] + 1); i <= up; ++i) {
            int flag = 0;
            for(int j = 0; j < x; ++j)
                if(a[j] == i) {
                    flag = 1;
                    break;
                }
            if(flag)
                continue;
            a[x] = i;
            FindNumber(x + 1);
            a[x] = 0;
        }
    }
}

int main() {
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        FindNumber(0);
    }
}