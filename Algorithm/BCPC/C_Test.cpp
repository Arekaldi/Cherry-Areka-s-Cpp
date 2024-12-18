#include <stdio.h>

const int maxn = 11;
bool flag[maxn];//对1~n进行标记，未使用的为false
int result[maxn+2];//存放组合数结果
int m,n;

void myPrint();
//num表示result中已经存在多少个数，pre表示上一个数是多少
void DFS3(int num, int pre) {
    if (pre == n + 1) {
        // myPrint();
        return;
    }
    for (int i = num; i <= m; i++) {
        if (!flag[i]) {
            flag[i] = true;
            result[pre] = i;
            DFS3(i, pre + 1);
            flag[i] = false;
        }
    }
}

int main()
{
    while (scanf("%d %d", &m, &n) != EOF) {
        DFS3(1,1);
    }
    
}

void myPrint() {
    for (int i = 1; i <=n; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");
}