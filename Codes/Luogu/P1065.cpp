#include<bits/stdc++.h>
using namespace std;
bool mac[21][100000];
struct node {
	int id,len;
}e[100010][21];
int last[10000];
int step[10000];
int n,m,ans;
int todo[10000];
int main() {
	int n,m;
	cin >> m >> n;
	for(int i = 1 ; i <= n * m ; i ++) cin >> todo[i];
	for(int i = 1 ; i <= n ; i ++) for(int j = 1 ; j <= m ; j ++) cin >> e[i][j].id;
	for(int i = 1 ; i <= n ; i ++) for(int j = 1 ; j <= m ; j ++) cin >> e[i][j].len;
	for(int i = 1 ; i <= n * m ; i ++) {
		int now = todo[i];
		step[now] ++;
		int ti = last[now];
		int now_s = 0;
		for(int j = ti + 1 ; j ; j ++) {
			
			if(!mac[e[now][step[now]].id][j]) {
				now_s ++;
//				cout << now << " " << e[now][step[now]].len << " " << now_s << " " << j << endl;
//				system("pause");
//				cout << "wdnmd";
				if(now_s == e[now][step[now]].len) {
					for(int k = j - e[now][step[now]].len + 1 ; k <= j ; k ++) mac[e[now][step[now]].id][k] = true;
					last[now] = j;
					ans = max(ans , last[now]);
					break;
				}
			}
			else now_s = 0;
		}
	}
	cout << ans;
}