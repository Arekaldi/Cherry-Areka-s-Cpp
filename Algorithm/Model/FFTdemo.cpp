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

const int maxn = 1 << 22;
int numberIndex[maxn];
int n, m, upBound = 1;
std :: complex <double> a[maxn], b[maxn];
std :: complex <double> w[maxn];


void FFT(std :: complex <double> *a, int n, int type) {
    if(n == 1)
        return;

    std :: complex <double> A1[(n >> 1)], A2[(n >> 1)];

    for(int i = 0; i < n; i += 2) {
        A1[i >> 1] = a[i];
        A2[i >> 1] = a[i | 1];
    }

    FFT(A1, n >> 1, type);
    FFT(A2, n >> 1, type);

    double nn = n * 1.0, theta = 2.0 * acos(-1) / nn;
    std :: complex <double> Wn = {cos(theta), (type ? -1 : 1) * sin(theta)};

    w[0] = 1;
    for(int i = 1; i <= n; ++i)
        w[i] = w[i - 1] * Wn;
    
    for(int i = 0; i < (n >> 1); ++i) {
        std :: complex <double> temp = A2[i] * w[i];
        a[i] = A1[i] + temp;
        a[i + (n >> 1)] = A1[i] - temp;
    }
    return;
}

std :: complex<double> Ares[maxn], Bres[maxn];

int main() {
    n = read(), m = read();

    while(upBound <= n + m)
        upBound <<= 1;

    for(int i = 0; i < upBound; ++i)
        numberIndex[i] = (numberIndex[i >> 1] >> 1) | ((i & 1) ? (upBound >> 1) : 0);

    for(int i = 0; i <= n; ++i)
        a[i] = read();
    for(int i = 0; i <= m; ++i)
        b[i] = read();

    FFT(a, upBound, 0);
    FFT(b, upBound, 0);

    for(int i = 0; i <= upBound; ++i)
        a[i] = a[i] * b[i];

    FFT(a, upBound, 1);

    for(int i = 0; i <= n + m; ++i) {
        double ans = a[i].real() / upBound + 0.5;
        int x = ans;
        printf("%d ", x);
    }
}