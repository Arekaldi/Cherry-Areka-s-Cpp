```cpp
for(int i = 1; i <= n; ++i) {x[i] = s[i]; c[x[i]]++;}
for(int i = 2; i <= m; ++i) c[i] += c[i - 1];
for(int i = n; i >= 1; --i) sa[c[x[i]]--] = i;
for(int k = 1; k <= n; k <<= 1) {
    int num = 0;
    for(int i = n - k + 1; i <= n; ++i) 
        y[++num] = i;
    for(int i = 1; i <= n; ++i)
        if(sa[i] > k) y[++num] = sa[i] - k;
 	num = 1; x[sa[1]] = 1;
    swap(x, y);
    for(int i = 2; i <= n; ++i) {
        
	}
}
```

