#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <algorithm>
#include <complex>
#include <string>

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

const int maxn = 1 << 20;
int numberIndex[maxn];
int upBound = 1;
std :: complex <double> a[maxn], b[maxn];
std :: complex <double> A[maxn];
void FFT(std :: complex <double> *a, int n, int type) {
    for(int i = 0; i < n; ++i)
        A[numberIndex[i]] = a[i];
    for(int mid = 1; mid <= n >> 1; mid <<= 1) {
        int lenOfInterval = mid << 1;
        double lenOfIntervalDouble = lenOfInterval * 1.0, theta = 2.0 * acos(-1.0) / lenOfIntervalDouble;
        std :: complex <double> Wn = {cos(theta), (type ? -1 : 1) * sin(theta)};
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

std :: complex<double> Ares[maxn], Bres[maxn];
int output[maxn];
char inputa[maxn], inputb[maxn];

int main() {
    int T = read();
    while(T--) {
        int len = 0;
        upBound = 1;
        scanf("%s%s", inputa, inputb);
        int lena = strlen(inputa), lenb = strlen(inputb);
        for(int i = 0; i < lena; ++i)
            Ares[len++] = inputa[i] - '0';
        len = 0;
        for(int i = 0; i < lenb; ++i)
            Bres[len++] = inputb[i] - '0';
        for(int i = lena - 1; i >= 0; --i)
            a[lena - i - 1] = Ares[i];
        for(int i = lenb - 1; i >= 0; --i)
            b[lenb - i - 1] = Bres[i];

        while(upBound <= lena + lenb)
            upBound <<= 1;

        for(int i = 0; i < upBound; ++i)
            numberIndex[i] = (numberIndex[i >> 1] >> 1) | ((i & 1) ? (upBound >> 1) : 0);

        FFT(a, upBound, 0);
        FFT(b, upBound, 0);

        for(int i = 0; i <= upBound; ++i)
            a[i] = a[i] * b[i];

        FFT(a, upBound, 1);

        int lastAns = 0;
        len = 0;
        double uu = upBound * 1.0;
        for(int i = 0; i <= lena + lenb; ++i) {
            double ans = a[i].real() / uu + 0.5;
            int x = ans + lastAns;
            lastAns = x / 10;
            output[len++] = x % 10;
        }
        int p = len - 1;
        while(output[p - 1] == 0 && p > 0) p--;
        for(int i = p - 1; i >= 0; --i)
            printf("%d", output[i]);
        if(p == 0)
            puts("0");
        else
            puts("");
        memset(a, 0, sizeof(a));
        memset(b, 0, sizeof(b));
    }
    
}