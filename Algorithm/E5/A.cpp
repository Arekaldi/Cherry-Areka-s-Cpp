#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
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

const int maxn = 1 << 17;

int n, c[maxn];
int numberIndex[maxn];

std :: complex <double> operator * (int x, std :: complex <double> a) {
    double xx = x * 1.0;
    return std :: complex <double> {xx * a.real(), xx * a.imag()};
}


std :: complex <double> A[maxn], A1[maxn], A2[maxn];
void FFT(int n) {
    for(int i = 0; i < n; ++i)
        A[numberIndex[i]] = c[i];
    for(int mid = 1; mid <= n >> 1; mid <<= 1) {
        int lenOfInterval = mid << 1;
        double lenOfIntervalDouble = lenOfInterval * 1.0, theta = 2.0 * acos(-1.0) / lenOfIntervalDouble;
        std :: complex <double> Wn = {cos(theta), sin(theta)};
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
}


std :: complex <double> f(std :: complex <double> x, int upBound) {
    std :: complex <double> base = 1, res = 0;
    for(int i = 0; i < upBound; ++i) {
        res = res + c[i] * base;
        base = base * x;
    }
    return res;
}

int main() {
    int n = read();
    for(int i = 0; i < 1 << n; ++i)
        c[i] = read();
    for(int i = 0; i < 1 << n; ++i)
        numberIndex[i] = (numberIndex[i >> 1] >> 1) | ((i & 1) ? (1 << (n - 1)) : 0);
    std :: complex <double> z = {0, 0};
    FFT(1 << n);
    for(int i = 0; i < 1 << n; ++i) {
        z = z + cos(i) * A[i];
    }
    printf("%.2lf %.2lf\n", z.real(), z.imag());
}