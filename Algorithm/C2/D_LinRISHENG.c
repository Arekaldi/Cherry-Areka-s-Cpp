/**/

#include <stdio.h>
#include <string.h>
int main()
{
    int t = 1;
    scanf("%d", &t);
    getchar();
    while (t--)
    {
        int a[1000] = {0}, b[1000] = {0}, ans[1010] = {0}, cnt1 = 0, cnt2 = 0;
        char str1[2010] = {0}, str2[2010] = {0};
        char format1[10] = {0}, format2[10] = {0};
        // fgets(str1, 2010, stdin);
        // fgets(str2, 2010, stdin);
        scanf("%s", str1);
        getchar();
        scanf("%s", str2);
        int len1 = strlen(str1), len2 = strlen(str2);
        for (int i = len1 - 4; i >= 0; i -= 4)
        {
            sscanf(&str1[i], "%4d", &a[cnt1++]);
        }
        if (len1 % 4)
        {
            sprintf(format1, "%%%dd", len1 % 4);
            sscanf(str1, format1, &a[cnt1++]);
        }
        for (int i = len2 - 4; i >= 0; i -= 4)
        {
            sscanf(&str2[i], "%4d", &b[cnt2++]);
        }
        if (len2 % 4)
        {
            sprintf(format2, "%%%dd", len2 % 4);
            sscanf(str2, format2, &b[cnt2++]);
        }
        for (int i = 0; i < cnt1; i++)
        {
            for (int j = 0; j < cnt2; j++)
            {
                int tmp = a[i] * b[j];
                ans[i + j] += tmp % 10000;
                ans[i + j + 1] += tmp / 10000;
            }
        }
        int cnt3 = 1;
        for (int i = 0; i < 999; i++)
        {
            ans[i + 1] += ans[i] / 10000;
            ans[i] %= 10000;
            if (ans[i])
            {
                cnt3 = i + 1;
            }
        }
        printf("%d", ans[cnt3 - 1]);
        for (int i = cnt3 - 2; i >= 0; i--)
        {
            printf("%04d", ans[i]);
        }
        printf("\n");
    }
    return 0;
}