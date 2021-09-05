#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

const int maxn = 2e2 + 1;

int s[maxn][maxn], a[maxn][maxn];

int d, n;

signed main() {
    d = read(), n = read();
    for(int i = 1; i <= n; ++i) {
        int x = read() + 1, y = read() + 1, k = read();
        a[x][y] = k;
    }
    
    for(int i = 1; i <= 129; ++i)
        for(int j = 1; j <= 129; ++j)
            s[i][j] = s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1] + a[i][j];
    
    // cout << s[1][1] << endl;

    int ans = 1, res = 0;
    for(int i = 1; i <= 129; ++i) {
        for(int j = 1; j <= 129; ++j) {
            int yx = min(129, i + d), yy = min(129, j + d);
            int zx = max(1, i - d), zy = max(1, j - d);
            int fu = s[yx][yy] - s[zx - 1][yy] - s[yx][zy - 1] + s[zx - 1][zy - 1];
            if(fu > res)
                ans = 1, res = fu;
            else if(fu == res)
                ans++;
        }
    }
    cout << ans << " " << res << endl;
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}

/*
We were both young when I first saw you

I closed my eyes and the flashback starts

I'm standing there

On a balcony in summer air

See the lights see the party the ball gowns

See you make your way through the crowd

And say hello

Little did I know

That you were Romeo you were throwing pebbles

And my daddy said stay away from Juliet

And I was crying on the staircase

Begging you please don't go

And I said

Romeo take me somewhere we can be alone

I'll be waiting all there's left to do is run

You'll be the prince and I'll be the princess

It's a love story

Baby just say yes

So I sneak out to the garden to see you

We keep quiet cause we're dead if they knew

So close your eyes

Escape this town for a little while

Oh oh

Cause you were Romeo I was the scarlet letter

And my daddy said stay away from Juliet

But you were everything to me

I was begging you please don't go

And I said

Romeo take me somewhere we can be alone

I'll be waiting all there's left to do is run

You'll be the prince and I'll be the princess

It's a love story

Baby just say yes

Romeo save me

They’re trying to tell me how to feel

This love is difficult but it's real

Don't be afraid we'll make it out of this mess

It's a love story

Baby just say yes

Oh oh

I got tired of waiting

Wondering if you were ever coming around

My faith in you was fading

When I met you on the outskirts of town

And I said

Romeo save me

I've been feeling so alone

I keep waiting for you but you never come

Is this in my head

I don't know what to think

He knelt to the ground and pulled out a ring

And said

Marry me Juliet you'll never have to be alone

I love you and that's all I really know

I talked to your dad

Go pick out a white dress

It's a love story

Baby just say yes

Oh oh oh

Oh oh oh oh

'Cause we were both young when I first saw you
*/