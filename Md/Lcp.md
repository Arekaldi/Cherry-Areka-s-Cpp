1. $Lcp(i, j) = Lcp(j, i)$

2. $Lcp(i, i) = len(sa[i]) = n - sa[i] + 1$

$\forall 1 \le i \le j \le k \le n, Lcp(i, k) = min(Lcp(i, j), Lcp(j, k))$

$height_i = Lcp(i, i - 1)$

$height_1 = 0$

$Lcp(i, k) = min(height_j), i + 1 \le j \le k$

```cpp
inv get_height() {
	rint k=0;
	for (rint i=1; i<=n; ++i) rk[sa[i]]=i;
	for (rint i=1; i<=n; ++i) {
		if (rk[i]==1) continue;//第一名height为0
		if (k) --k;//h[i]>=h[i-1]-1;
		rint j=sa[rk[i]-1];
		while (j+k<=n && i+k<=n && s[i+k]==s[j+k]) ++k;
		height[rk[i]]=k;//h[i]=height[rk[i]];
	}
	putchar(10);
	for (rint i=1; i<=n; ++i) putout(height[i]),putchar(' ');
}
```











```cpp
int suf[maxn][maxn];
int k = 0; // k -> last_h[i]
for(int i = 1; i <= n; ++i) rk[sa[i]] = i; // init(rk[])
for(int i = 1; i <= n; ++i) {
    if(rk[i] == 1) continue; // height[1] = 0
	if(k) --k; // h[i] >= h[i - 1] - 1;
    int j = sa[rk[i] - 1]; // Prove's k
    while(j + k <= n and i + k <= n and s[i + k] == s[j + k]) ++k;
    height[rk[i]] = k;
}
```



