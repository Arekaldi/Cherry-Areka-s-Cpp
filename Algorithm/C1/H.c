#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


int read(void) {
    int x, f = 1;
    char ch;
    while(!isdigit(ch = getchar()))
    (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 1) + (x << 3) + (ch ^ 48));
    return x * f;
}

#define int long long

int n, k, Arr[100010];
int ans;

void Merge_Sort(int l, int r) {
    if(l == r)
        return;
    int *New_Array = (int *)malloc(sizeof(int) * (r - l + 1));
    int mid = (l + r) >> 1;
    Merge_Sort(l, mid), Merge_Sort(mid + 1, r);
    int p = l, q = mid + 1, now = 1;
    while(p <= mid && q <= r) {
        if(Arr[p] > Arr[q] * k)
            ans += (mid - p + 1), q++;
        else
            p++;
    }
    p = l, q = mid + 1;
    while(p <= mid && q <= r)
        New_Array[now++] = (Arr[p] <= Arr[q]) ? Arr[p++] : Arr[q++];
    while(p <= mid)
        New_Array[now++] = Arr[p++];
    while(q <= r)
        New_Array[now++] = Arr[q++];
    for(int i = l; i <= r; ++i)
        Arr[i] = New_Array[i - l + 1];
    return;
}

int main() {
    scanf("%lld%lld", &n, &k);
    // n = read(), k = read();
    for(int i = 1; i <= n; ++i)
        // Arr[i] = read();
        scanf("%lld", &Arr[i]);
    Merge_Sort(1, n);
    printf("%lld\n", ans);
}