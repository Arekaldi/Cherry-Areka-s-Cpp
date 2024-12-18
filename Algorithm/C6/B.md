> B-位逆序置换
>
> 23371041-李一鸣

## 题目描述

- 给定 $n$ 个数 $a_n$，要求 $n$ 个数，满足 $b_m = a_n$，其中 $m = rev(n)$
- $rev(n)$是指： 假设 $n_{10} = (p_1p_2p_3 \dots p_n)_2$，则 $rev(n) = (p_np_{n-1} \dots p_2p_1)_2$

## 解题思路

- 本题题解其实是 `FFT` 算法的基础。
- 考虑求 $rev(n)$，一种朴素的思想是，将 $n$ 写成二进制，再逐个组合，但实现显然过于复杂。
- 可以这样考虑：在求 $rev(n)$ 时，$rev(n \gg 1)$ 显然已经求出，因此可以递推求解。
- 以 $(10001)_2$ 为例， $(10001)_2 \gg 1$ 为 $(01000)_2$， $rev$ 为 $(00010)_2$，因此，只需将其右移一位，再在第 $k$ 位上补全原数第 $0$ 位即可。

## 代码实现

```cpp
const int maxn = 1 << 11;

int dataIndex[maxn], a[maxn];

int main() {
    int n = read();
    int l = log2(n);
    for(int i = 0; i < n; ++i)
        a[i] = read();
    for(int i = 0; i < n; ++i)
        dataIndex[i] = dataIndex[i >> 1] >> 1 | ((i & 1) << (l - 1));
    for(int i = 0; i < n; ++i)
        printf("%d ", a[dataIndex[i]]);
    return 0;
}
```

