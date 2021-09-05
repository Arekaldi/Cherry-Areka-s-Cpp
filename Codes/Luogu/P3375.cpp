#include <bits/stdc++.h>

using namespace std;

#define RE register
#define int long long

inline int read() {
	RE int x = 0, f = 1;
	RE char ch = getchar();
	while(ch < '0' or ch > '9') {
		f = ch == '-' ? -1 : f;
		ch = getchar();
	}
	while(ch >= '0' and ch <= '9') {
		x = (x << 1) + (x << 3) + (ch ^48);
		ch = getchar();
	}
	return x * f;
}

const int maxn = 1e6 + 1;

int nxt[maxn], j;

char s1[maxn], s2[maxn];

signed main() {
	cin >> (s1 + 1) >> (s2 + 1);
	int len1 = strlen(s1 + 1), len2 = strlen(s2 + 1);
	for(int i = 1; i <= len2; ++i) {
		while(j and s2[j + 1] != s2[i])
			j = nxt[j];
		if(s2[j + 1] == s2[i])
			j++;
		nxt[i] = j;
		if(i == 1)
			nxt[i] = j = 0;
	}
	j = 0;
	for(int i = 1; i <= len1; ++i) {
		while(j and s2[j + 1] != s1[i])
			j = nxt[j];
		if(s2[j + 1] == s1[i])
			j++;
		if(j == len2)
			printf("%d\n", i - len2 + 1);
	}
	for(int i = 1; i <= len2; ++i)
		cout << nxt[i] << " ";
}
