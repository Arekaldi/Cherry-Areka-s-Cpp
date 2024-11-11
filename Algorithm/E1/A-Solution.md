### A Solution
#### 解题思路
- 题目要求按照一定方式对同学们进行排序。
- 由于单个元素具有四个属性，分别实现排序为 $a_i$, $b_i$, $c_i$, $name$，所以我们需要一个结构体来存储这些信息。
- 通过 `qsort` 可以快速实现排序，因此我们通过 `qsort` 函数对数组进行排序。
- 按照题目要求写出 `cmp` 函数，用于比较两个 `struct` 结构体的大小。
#### 代码实现
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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

struct Node {
    char Name[10];
    int a, b, c;
};

int cmp(const void *a, const void *b) {
    struct Node *p1 = (struct Node *)a;
    struct Node *p2 = (struct Node *)b;
    int p1all = p1->a + p1->b + p1->c;
    int p2all = p2->a + p2->b + p2->c;
    if(p1all > p2all)
        return -1;
    else if(p1all < p2all)
        return 1;
    else {
        if(p1->a > p2->a)
            return -1;
        else if(p1->a < p2->a)
            return 1;
        else
            return strcmp(p1->Name, p2->Name);
    }
}

struct Node Stu[100010];

int main() {
    int n = read();
    for(int i = 1; i <= n; ++i)
        scanf("%s %d %d %d", Stu[i].Name, &Stu[i].a, &Stu[i].b, &Stu[i].c);
    qsort(Stu + 1, n, sizeof(struct Node), cmp);
    for(int i = 1; i <= n; ++i)
        puts(Stu[i].Name);
    return 0;
}
```