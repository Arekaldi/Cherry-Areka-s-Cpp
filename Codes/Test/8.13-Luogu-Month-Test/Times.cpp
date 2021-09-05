#include <stdio.h>

int main(int i)
{
    if (i ^ 448)
        main(-~i);
    if (--i % 64)
    {
        char a = -~7[__TIME__ - i / 8 % 8][">'txiZ^(~z?" - 48];
        char b = ";;;====~$::199"[i * 2 & 8 | i / 64] / (i & 2 ? 1 : 8) % 8;
        char c = a >> b;
        putchar(32 | (c & 1));
    }
    else
        putchar(10);

    return 0;
}