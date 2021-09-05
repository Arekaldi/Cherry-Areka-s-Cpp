#include<bits/stdc++.h>
using namespace std;
int ans = (1 << 30);
int n,T;
const int maxn = 300;
int a[maxn];
int bow[maxn];
bool used[maxn];

void dfs(int now_p , int now_s) {
	if(now_s >= ans) return ;
	if(now_p == 0) {
		ans = min(ans , now_s);
		return ;
	}
	for(int i = 3 ; i <= 10 ; i ++) {//顺砸 
		bool ff = false;
		int end;
		if(!bow[i]) continue;
		bow[i] --;
		for(int j = i + 1 ; j <= 14 ; j ++) {
			if(!bow[j]) {
				end = j;
				ff = true;
				break;
			}
			bow[j] --;
			if(j - i >= 4) dfs(now_p - (j - i + 1) , now_s + 1);
		}
		for(int j = i ; j < end ; j ++) bow[j] ++;
	}
	for(int i = 3 ; i <= 12 ; i ++) {//连对 
		bool ff = false;
		int end;
		if(bow[i] < 2) continue;
		bow[i] -= 2; 
		for(int j = i + 1 ; i <= 14 ; j ++) {
			if(bow[j] < 2) {
				end = j;
				ff = true;
				break;
			}
			bow[j] -= 2;
			if(j - i >= 2) dfs(now_p - 2 * (j - i + 1) , now_s + 1);
		}
		for(int j = i ; j < end ; j ++) bow[j] += 2;
	}
	for(int i = 3 ; i <= 12 ; i ++) {//三顺子 
		bool ff = false;
		int end;
		if(bow[i] < 3) continue;
		bow[i] -= 3; 
		for(int j = i + 1 ; i <= 14 ; j ++) {
			if(bow[j] < 3) {
				end = j;
				ff = true;
				break;
			}
			bow[j] -= 3;
			if(j - i >= 2) dfs(now_p - 3 * (j - i + 1) , now_s + 1);
		}
		for(int j = i ; j < end ; j ++) bow[j] += 3;
	}
	if(now_p >= 6) {//四带 
		for(int i = 1 ; i <= 15 ; i ++) {
			if(bow[i] == 4) {
				bow[i] -= 4;
				for(int j = 1 ; j <= 15 ; j ++) {
					if(bow[j]) {
						bow[j] --;
						for(int k = j + 1 ; k <= 15 ; k ++) {
							if(bow[k]) {
								bow[k] --;
								dfs(now_p - 6 , now_s + 1);
								bow[k] ++;
							} 
						}
						bow[j] ++;
					}
				}
				for(int j = 1 ; j <= 15 ; j ++) {
					if(bow[j] >= 2) {
						bow[j] -= 2;
						for(int k = j + 1 ; k <= 15 ; k ++) {
							if(bow[k] >= 2) {
								bow[k] -= 2;
								dfs(now_p - 8 , now_s + 1);
								bow[k] += 2;
							} 
						}
						bow[j] += 2;
					}
				}
			}
		}
	}
	
	if(now_p >= 3) {
		for(int i = 1 ; i <= 15 ; i ++) {
			if(bow[i] >= 3) {
				bow[i] -= 3;
				for(int j = 1 ; j <= 17 ; j ++) {
					if(bow[j]) {//三带一 包括王 
						bow[j] --;
						dfs(now_p - 4 , now_s + 1);
						bow[j] ++;
					}
					if(bow[j] >= 2 and j <= 15) {//三带二 
						bow[j] -= 2;
						dfs(now_p - 5 , now_s + 1);
						bow[j] += 2;
					}
				}
				dfs(now_p - 3 , now_s + 1);//三张 
				bow[i] += 3;
			}
		}
	} 
	for(int i = 1 ; i <= 17 ; i ++) {
		if(bow[i] >= 2) {
			bow[i] -= 2;
			dfs(now_p - 2 , now_s + 1);
			bow[i] += 2;
		}
		if(bow[i]) {
			bow[i] --;
			dfs(now_p - 1 , now_s + 1);
			bow[i] ++;
		}
	}
}
int main() {
	cin >> T >> n;
	while(T --) {
		memset(bow , 0 , sizeof(bow));
		for(int i = 1 ; i <= n ; i ++) {
			int x;
			cin >> a[i] >> x;
			if(a[i] == 1) bow[14] ++;
			if(a[i] == 2) bow[15] ++;
			if(!a[i]) {
				if(x == 1) bow[16] ++;
				else bow[17] ++;
			}
			else bow[a[i]] ++;
		}
		ans = (1 << 30);
		dfs(n , 0);
		cout << ans << "\n";
	}
}