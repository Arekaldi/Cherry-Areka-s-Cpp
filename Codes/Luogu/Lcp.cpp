int suf[maxn][maxn];
int k = 0;
for(int i = 1; i <= n; ++i) rk[sa[i]] = i;
for(int i = 1; i <= n; ++i) {
    if(rk[i] == 1) continue;
	if(k) --k;
    int j = sa[rk[i] - 1];
    while(j + k <= n and i + k <= n and s[i + k] == s[j + k]) ++k;
    height[rk[i]] = k;
}