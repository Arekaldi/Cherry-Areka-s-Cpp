> C-背\dots \dots包？
>
> [doge]
>
> 23371041-李一鸣

## 题目描述

- 普通背包问题，唯一的区别是 $V$ 非常非常大，而 $W$ 比较小

## 解题思路

- 既然题目有如此特点，那么我们可以考虑更换一下背包问题的状态转移方程

- 考虑 $dp_{i, j}$ 为 决定第 $i$ 件物品，得到价值为 $j$ 所需要的最小体积

- 则枚举价值即可

- 转移方程如下：

  - $$
    dp_{i, j} = \left \{
    \begin {aligned}
    dp_{i - 1, j}, && j < w(i) \\
    min (dp_ {i - 1, j}, dp_{i - 1, j - w(i)} + v(i)), && j \ge w(i)
    \end{aligned}
    \right.
    $$

## 代码实现

```cpp
int n, vSum;
int v[510], w[510];
int f[2][250010];

int min2(int a, int b) {
    return a > b ? b : a;
}

signed main() {
    n = read(), vSum = read();
    for(int i = 1; i <= n; ++i)
        v[i] = read(), w[i] = read();
    for(int j = 1; j <= 250000; ++j)
        f[0][j] = 1e12 + 1;
    for(int i = 1; i <= n; ++i) {
        f[i & 1][0] = 0;
        for(int j = 1; j <= 250000; ++j) {
            if(j < w[i])
                f[i & 1][j] = f[(i & 1) ^ 1][j];
            else
                f[i & 1][j] = min2(f[(i & 1) ^ 1][j], f[(i & 1) ^ 1][j - w[i]] + v[i]);
        }
    }
    int ans = 0;
    for(int j = 250000; j >= 0; --j)
        if(f[n & 1][j] <= vSum) {
            ans = j;
            break;
        }
    write(ans);
    return 0;
}
```

