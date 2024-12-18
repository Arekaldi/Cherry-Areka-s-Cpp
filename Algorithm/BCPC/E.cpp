#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <algorithm>
#include <cmath>
#include <map>
#include <unordered_map>

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

int ans[27];
// 计算最大伤害的函数
std :: pair <int, int> maxDamage(char *s) {
    int n = strlen(s), ans1, ans2;

    double max_damage = 0.0,  damage = 0.0;

    memset(ans, 0x3f, sizeof(ans));

    std :: unordered_map<char, int> char_count;

    for(int i = 1; i <= 26; ++i) {

        int l = 0, unique_count = 0;

        for (int r = 0; r < n; ++r) {
            char_count[s[r]]++;

            unique_count = char_count.size();

            int length = r - l + 1;
            if(unique_count == i)
                ans[i] = std :: min(ans[i], length);


            while ((unique_count == i && char_count[s[l]] > 1) || unique_count > i) {
                char_count[s[l]]--;
                if (char_count[s[l]] == 0)
                    char_count.erase(s[l]), unique_count--;
                l++;
                length = r - l + 1;
            }

            if(unique_count == i)
                ans[i] = std :: min(ans[i], length);
        }

        while(!char_count.empty())
            char_count.erase(char_count.begin());
    }

    for(int i = 1; i <= 26; ++i) {
        // printf("%d ", ans[i]);
        damage = (double)(i * i) / ans[i];
        if(damage > max_damage) {
            ans1 = i, ans2 = ans[i];
            max_damage = damage;
        }
    }
    // puts("");
    return std :: make_pair(ans1 * ans1, ans2);
}

char s[100010];

int gcd(int a, int b) {
    return (b == 0) ? a : gcd(b, a % b);
}

int main() {
    
    scanf("%s", s);

    std ::pair <int, int> p = maxDamage(s);

    int g = gcd(p.first, p.second);

    printf("%d %d\n", p.first / g, p.second / g);

    return 0;
}
