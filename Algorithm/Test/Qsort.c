#include <stdio.h>

int n;
int a[100010];

void qsort(int l, int r) {
    if (l >= r) return;
    int i = l, j = r, pivot = a[l];
    while(i <= j) {
        while(i <= j && a[i] <= pivot)
            i++;
        while(i <= j && a[j] >= pivot)
            j--;
        if(i > j)
            break;
        
        int temp = a[i];
        a[i] = a[j];
        a[j] = temp;
    }
    a[l] = a[j];
    a[j] = pivot;
    qsort(l, j-1);
    qsort(j+1, r);
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &a[i]);
    qsort(1, n);
    for (int i = 1; i <= n; ++i)
        printf("%d ", a[i]);
    return 0;
}