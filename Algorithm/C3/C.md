> C-2024-矩阵链乘题解
> 23371041-李一鸣

## 题目要求
- 求 $n$ 个 矩阵连乘，共有多少种求法

## 解题思路
- 考虑 $k$ 个矩阵连乘，$A \times A \times \dots \times A$。
- 由于矩阵乘法满足乘法分配率，我们可以考虑将这 $k$ 个矩阵分为 $i$ 和 $k - i$ 两部分， 最终的方案数就是 $\sum _ {i = 1} ^ {k - 1} f(i) \times f(k - i)$。
- 复杂度分析： 由于 $1 \le n \le 35$，算法复杂度为 $\Theta(n^2)$，所以可以通过题目。

## 代码实现
```c
signed main() {
    n = read();
    dp[1] = 1;
    for(int i = 2; i <= n; ++i) {
        int sum = 0;
        for(int j = 1; j < i; ++j)
            sum += dp[j] * dp[i - j];
        dp[i] = sum;
    }
    printf("n  : P(n)\n");
    for(int i = 1; i <= n; ++i)
        printf("%-3lld: %lld\n", i, dp[i]);
    return 0;
}
```