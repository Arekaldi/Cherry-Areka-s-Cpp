#include<bits/stdc++.h>
#define int long long 
#define g() getchar()
#define il inline

using namespace std;
// const int N = 1e6 + 10;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;

il int re()
{
	int x = 0, p = 1;
	char ch = g();
	while(ch > '9' || ch < '0') {if(ch == '-') p = -1; ch = g();}
	while(ch <= '9' and ch >= '0') {x = (x << 3) + (x << 1) + (ch ^ 48); ch = g();}
	return x * p;
}

int row, n, m, k, Ans;
struct Maritx
{
    int a[300][300];
    Maritx() {
        memset(a, 0, sizeof(a));
    }
    il friend Maritx operator * (const Maritx &a, const Maritx &b)
    {
        Maritx c;
        memset(c.a, 0, sizeof(c.a));
        for(int i = 0; i < row; ++i)
            for(int j = 0; j < row; ++j)
                for(int k = 0; k < row; ++k)
                    c.a[i][j] = ((1ll * a.a[i][k] * b.a[k][j]) % mod) % mod;
        return c;
    }
}A, B;


inline void Qpow(Maritx &ans, Maritx D, int y)
{
//    cout << 1 << endl;
//	Maritx ans;
	memset(ans.a, 0, sizeof(ans.a));
    while(y > 0)
    {
        if(y & 1) ans = ans * D;
        D = D * D;
        y >>= 1;
    }
//    return ans;
}


int count(unsigned int x)
{
    // x=(x&0x55555555)+(x>>1&0x55555555);
    // x=(x&0x33333333)+(x>>2&0x33333333);
    // x=(x&0x0F0F0F0F)+(x>>4&0x0F0F0F0F);
    // x=(x&0x00FF00FF)+(x>>8&0x00FF00FF);
    // x=(x&0x0000FFFF)+(x>>16&0x0000FFFF);
    int res = 0;
    while(x) {
        res++;
        x -= (x & (-x));
    }
    return x;
}

signed main()
{
    n = re(), m = re(), k = re();
    int fina = (1 << m);
    row = fina;
    for(int i = 0, j; i < fina; ++i)
    {
        if(count(i) > k) continue;
        j = i >> 1;
        A.a[j][i] = 1;
        j = (i >> 1) | (1 << (m - 1));
        if(count(i) > k) continue;
        A.a[j][i] = 1;
    }
    Maritx C;
    cout << C.a[0][0] << endl;
//    cout<<1<<endl;
    // Maritx res;
    cout << 1 << endl;
	Qpow(C, A, n);
    return 0;
//    cout << 1 << endl;
//    for(int i = 0; i < row; ++i)
//    {
//        Ans = (Ans + C.a[i][i]) % mod;
//    }
//    printf("%d", Ans);
//    getchar();
}