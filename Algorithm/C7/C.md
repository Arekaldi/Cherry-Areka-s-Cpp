> C-车厢调度
>
> 23371041-李一鸣

## 题目描述

- 给定 $n$ 和 $1 \to n$ 的序列，求能否用一个栈得到给定的序列。

## 解题思路

- 考虑正常如何得到给定序列：
  - 模拟即可
  - 当遍历到 $i$ 时，若 $i$ 没有入栈
    - 首先应将 $1 \to i$ 中没有入栈的元素按顺序入栈。
    - 然后将 $i$ 弹出。
  - 否则，应检查  $i$ 是否在栈顶，若不在栈顶，则无法得到序列。
  - 当遍历结束时，即可得到给定序列。

## 代码实现

```cpp
#include <stdio.h>
#include <stack>
#include <string.h>

const int maxn = 1e4 + 1;
std :: stack <int> s;
int p[maxn], vis[maxn];

int main() {
    int T, n;
    scanf("%d", &T);
    while(T--) {
        scanf("%d", &n);
        while(!s.empty())
            s.pop();
        memset(vis, 0, sizeof(vis));
        for(int i = 1; i <= n; ++i)
            scanf("%d", &p[i]);
        int flag = 1;
        for(int i = 1; i <= n; ++i) {
            if(!vis[p[i]]) {
                for(int j = 1; j <= p[i]; ++j) {
                    if(!vis[j])
                        s.push(j), vis[j] = 1;
                }
                s.pop();
            }
            else {
                if(s.top() != p[i]) {
                    flag = 0;
                    break;
                }
                s.pop();
            }
        }
        puts(flag ? "YES" : "NO");
    }
}
```