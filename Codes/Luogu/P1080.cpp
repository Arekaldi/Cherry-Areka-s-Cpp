#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e3 + 1;

namespace BigIntegers {
    const int Maxw = 23000;
    typedef bitset<Maxw> i256;
    const int base = 1e8, wid = 8;

    inline i256 operator + (const i256 &x, const i256 &y) {
        return y.any() ? (x ^ y) + ((x & y) << 1) : x;
    }

    class BigInteger {
        public:
            i256 v;
            BigInteger() {}
            BigInteger(i256 v1) : v(v1) {}
            inline friend bool operator > (const BigInteger &a, const BigInteger &b) {
                i256 x = a.v, y = b.v;
                int l = 0, r = Maxw;
                while(true) {
                    int mid = (l + r) >> 1;
                    if(mid == l or mid == r)
                        break;
                    if(((x >> mid) ^ (y >> mid)).any())
                        l = mid;
                    else
                        r = mid;
                }
                return !(y >> l).any();
            }

            inline friend bool operator < (const BigInteger &a, const BigInteger &b) {
                return b > a;
            }
            
            inline friend bool operator <= (const BigInteger &a, const BigInteger &b) {
                return !(a > b);
            }
            
            inline friend bool operator >= (const BigInteger &a, const BigInteger &b) {
                return !(a < b);
            }

            inline friend bool operator == (const BigInteger &a, const BigInteger &b) {
                return !(a > b) and !(a < b);
            }

            inline friend BigInteger operator + (const BigInteger &a, const BigInteger &b) {
                i256 x = a.v, y = b.v;
                BigInteger ans;
                // cout << x.to_ulong() << " " << y.to_ulong() << endl;
                ans.v = x + y;
                // cout << 1 << endl;
                return ans;
            }

            inline friend BigInteger operator += (BigInteger &a, const BigInteger &b) {
                a.v = a.v + b.v;
                return a;
            }

            inline friend BigInteger operator - (const BigInteger &a, const BigInteger &b) {
                BigInteger ans;
                ans.v = ~b.v;
                ans.v = ans.v + i256(1);
                // cout << 1 << endl;
                return ans + a;
            }
            
            inline friend BigInteger operator -= (const BigInteger &a, const BigInteger &b) {
                BigInteger ans = a - b;
                return ans;
            }

            inline friend BigInteger operator * (const BigInteger &a, const BigInteger &b) {
                BigInteger x = a, y = b;
                BigInteger ans(i256(0));
                ans.v.reset();
                while(y.v.any()) {
                    if(y.v.test(0))
                        ans += x;
                    x.v <<= 1;
                    y.v >>= 1;
                }
                return ans;
            }

            inline friend BigInteger operator *= (BigInteger &a, BigInteger &b) {
                BigInteger ans = a * b;
                return ans;
            }

            inline friend pair <BigInteger, BigInteger> operator / (const BigInteger &a, const BigInteger &b) {
                BigInteger r, rr;
                r.v.reset(), rr.v.reset();
                for(int i = 64; i >= 0; --i) {
                    r.v <<= 1, rr.v <<= 1;
                    // cout << i << " " << r.v.to_ulong() << " " << rr.v.to_ulong() << endl;
                    if(a.v.test(i)) {
                        r.v ^= 1;
                        // cout << 1 << endl;
                    }
                    if(r >= b) {
                        // cout << r.v.to_ulong() << " " << b.v.to_ulong() << endl;
                        r -= b;
                        // cout << 1 << endl;
                        rr.v ^= 1;
                        // cout << 1 << endl;
                    }
                    // cout << 12 << endl;
                }
                return make_pair(r, rr);
            }

            inline friend BigInteger operator /= (BigInteger &a, BigInteger &b) {
                BigInteger ans = (a / b).first;
                return ans;
            }

            inline friend BigInteger operator % (BigInteger &a, BigInteger &b) {
                BigInteger ans = (a / b).second;
                return ans;
            }

            inline void Print() {
                i256 x = v;
                if(x.test(Maxw - 1)) {
                    putchar('-');
                    BigInteger o(i256(0));
                    x = (o - *this).v;
                }
                short out[Maxw], now = 0;
                memset(out, 0, sizeof(out));
                for(int i = Maxw - 2; i >= 0; --i) {
                    for(int j = 0; j <= now; ++j)
                        out[j] <<= 1;
                    if(x.test(i))
                        out[0]++;
                    for(short j = 0; j <= now; ++j)
                        if(out[j] > 9)
                            out[j + 1]++, out[j] %= 10, now = max(now, (short)(j + 1));
                }

                for(int i = now; i >= 0; --i)
                    putchar(out[i] ^ 48);
            }
    };

    inline BigInteger read() {
        BigInteger ans(i256(0));
        char ch; int f = 1;
        i256 &x = ans.v;
        while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
        for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
        return f ? ans : BigInteger(i256(0)) - ans;
    }
    
    class Node {
        public:
            BigInteger a, b;
            Node() : a(i256(0)), b(i256(0)) {}
    };

    inline bool Camp(Node g, Node f) {
        return g.a * g.b < f.a * f.b;
    }
}

namespace ReadInt {
    inline int read() {
        register int x = 0, f = 1;
        register char ch;
        while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
        for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
        return x * f;
    }
}

using namespace BigIntegers;

Node p[maxn];
int n;

signed main() {
    // n = ReadInt :: read() + 1;
    // BigInteger res(i256(0)), mul(i256(1));
    // for(int i = 1; i <= n; ++i)
    //     p[i].a = read(), p[i].b = read();
    // sort(p + 1, p + n + 1, Camp);
    // for(int i = 1; i <= n; ++i) {
    //     res = max(res, (mul / p[i].b).first);
    //     mul *= p[i].a;
    // }
    
    // printf("%lld\n", res);

    BigInteger a = read(), b = read();
    BigInteger ans = (a / b).first;
    ans.Print();

    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
