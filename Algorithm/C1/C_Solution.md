### C Solution
#### 解题思路
- 题目要求输出 `n` 个字符串中最长的前20个字符串。
- 由于题目的空间限制为 `4096kb`，因此，我们不能暴力的存下所有的字符串。
- 需要有一个输入字符串，通过插入排序获得前20个字符串的长度，当输入长度小于最小的字符串长度时，直接舍弃该字符串。
- 最后，通过结构体排序，将字符串按输入顺序输出。

#### 代码实现
```c
#include <stdio.h>

struct String {
    char *str;
    int len;
    int index;
};

struct String Names[22];
char *input_str;
int All_Name_Number = 1;
int index1 = 0;

int cmp(const void *a, const void *b) {
    struct String *p1 = (struct String *)a;
    struct String *p2 = (struct String *)b;
    return p1->index - p2->index;
}

int main() {
    input_str = (char *)malloc(sizeof(char) * 1010);
    Names[1].len = 0;
    while(fgets(input_str, 1010, stdin) != NULL) {
        ++index1;
        int len = strlen(input_str);
        for(int i = 1; i <= All_Name_Number; ++i) {
            if(Names[i].len < len) {
                for(int j = All_Name_Number; j > i; --j)
                    Names[j] = Names[j - 1];
                Names[i].str = (char *)malloc(sizeof(char) * 1010);
                strcpy(Names[i].str, input_str);
                Names[i].len = len;
                Names[i].index = index1;
                ++All_Name_Number;
                if(All_Name_Number == 21) {
                    free(Names[All_Name_Number].str);
                    Names[All_Name_Number].str = NULL;
                    --All_Name_Number;
                }
                break;
            }
        }
    }
    qsort(Names + 1, All_Name_Number, sizeof(struct String), cmp);
    for(int i = 1; i <= All_Name_Number; ++i)
        printf("%s", Names[i].str);
    return 0;
}
```