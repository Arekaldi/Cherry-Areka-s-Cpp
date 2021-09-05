#include<cstdio>
#include<cstring>
using namespace std;
long long T,n,siz[1000001],num[101],in,mx;
long long abbs(long long x)
{
    return x>=0?x:(-x);
}
int main()
{
    freopen("grade.in","r",stdin);
    freopen("grade.out","w",stdout);
    scanf("%lld",&T);
    while(T--)
    {
        memset(siz,0,sizeof(siz));
        memset(num,0,sizeof(num));
        mx=0;
        scanf("%lld",&n);
        for(long long i=1;i<=n;i++)
        {
            scanf("%lld",&in);
            in=abbs(100-in);
            siz[num[in]]--;
            num[in]++;
            if(num[in]>mx)mx=num[in];
            siz[num[in]]++;
        }
        if(siz[mx]*mx==n)
        {
            printf("Bad Mushroom\n");
        }
        else
        {
            for(long long i=100;i>=0;i--)
            {
                if(num[i]==mx)
                {
                    printf("%lld ",10000-i*i);
                }
            }
            printf("\n");
        }
    }
    fclose(stdin);fclose(stdout);
    return 0;
}