> D-2024-切钢条
>
> 23371041-李一鸣

## 题目描述

	- 给定 $n$ 和 $n$ 个长度，要求将一个长度为给定长度之和的钢条切割为给定的 $n$ 个长度。
	- 切割费用为当前锯开钢条长度的两倍。
	- 求最小切割费用。

## 解题思路

- 考虑正难则反思想，将长度固定的钢条切开不好实现，我们可以考虑将给定长度的钢条拼成一整根，拼接的费用则为拼成钢条费用的$2$ 倍。
- 于是问题抽象为以下问题：
  - 两个小元素可合成元素。
  - 大元素合成的费用是小元素之和（题目要求的 $2$ 倍关系可以在最后乘 $2$ ）。
  - 最终目标是合成一个元素。
- 因此自然联想到 `霍夫曼树/霍夫曼编码` ，将所有给定的钢条看作叶子节点，求出所有费用即可。

## 代码实现

```cpp
using namespace std;

priority_queue <int, vector<int>, greater<int> > q;

int n;
int lenAll;
int len[200010], sum[200010];

int cmp(int a, int b) {
    return a > b;
}

signed main() {
    n = read();
    for(int i = 1; i <= n; i++)
        len[i] = read(), lenAll += len[i], q.push(len[i]);
    sort(len + 1, len + 1 + n, cmp);
    for(int i = 1; i <= n; i++)
        sum[i] = sum[i - 1] + len[i];
    int ans = 0;
    while(q.size() > 1) {
        int now1 = q.top();
        q.pop();
        int now2 = q.top();
        q.pop();
        ans += 2 * (now1 + now2);
        q.push(now1 + now2);
    }
    printf("%lld\n", ans);
    return 0;
}
```

