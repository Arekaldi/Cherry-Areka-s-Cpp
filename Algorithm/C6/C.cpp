#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <algorithm>
#include <complex>

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

const int maxn = 1 << 19;
int numberIndex[maxn];
int n;
std :: complex <double> a[maxn];
std :: complex <double> w[maxn];

std :: complex <double> A[maxn];
void FFT(std :: complex <double> *a, int n, int type) {
    for(int i = 0; i < n; ++i)
        A[numberIndex[i]] = a[i];
    for(int mid = 1; mid <= n >> 1; mid <<= 1) {
        int lenOfInterval = mid << 1;
        double lenOfIntervalDouble = lenOfInterval * 1.0, theta = 2.0 * acos(-1.0) / lenOfIntervalDouble;
        std :: complex <double> Wn = {cos(theta), (type ? -1.0 : 1.0) * sin(theta)};
        for(int l = 0; l < n; l += lenOfInterval) {
            std :: complex <double> w = {1, 0};
            for(int p = l; p < l + mid; ++p) {
                std :: complex <double> temp1 = A[p], temp2 = w * A[mid + p];
                A[p] = temp1 + temp2;
                A[p + mid] = temp1 - temp2;
                w *= Wn;
            }
        }
    }
    for(int i = 0; i < n; ++i)
        a[i] = A[i];
}

const double eps = 1e-9;

int main() {
    int k = read();

    n = 1 << k;

    for(int i = 0; i < n; ++i)
        numberIndex[i] = (numberIndex[i >> 1] >> 1) | ((i & 1) ? (n >> 1) : 0);

    double nn = n * 1.0;

    for(int i = 0; i < n; ++i) {
        double x = read() * 1.0;
        a[i] = {x, 0};
    }

    FFT(a, n, 1);

    for(int i = 0; i < n; ++i) {
        double ans1 = a[i].real() / nn;
        double ans2 = a[i].imag() / nn;
        if(ans1 > -0.005 && ans1 <= 0)
            ans1 = 0.0001;
        if(ans2 > -0.005 && ans2 <= 0)
            ans2 = 0.0001;
        printf("%.2lf %.2lf\n", ans1, ans2);
    }
}