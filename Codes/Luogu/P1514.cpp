#include<bits/stdc++.h>
using namespace std;
const int maxn = 250010 + 100;
int n,m;
int id(int x , int y) {
	return (x - 1) * m + y;
}
int high[510][510];

queue < int > q;
bool vis[510][510];
int cnt;
int l[510][510],r[510][510];
int dx[5] = {0 , 0 , 1 , -1};
int dy[5] = {1 , -1 , 0 , 0};
vector < pair <int, int> > ss;

inline bool Camp(pair <int, int> a, pair <int, int> b) {
	return a.first == b.first ? a.second > b.second : a.first < b.first;
}

void dfs(int x , int y) {
	vis[x][y] = true;
	for(int i = 0 ; i < 4 ; i ++) {
		int xx = x + dx[i],yy = y + dy[i];
		if(xx > n or xx < 0 or yy > m or yy < 0) continue;
		if(high[xx][yy] >= high[x][y]) continue;
		if(!vis[xx][yy]) dfs(xx , yy);
		l[x][y] = min(l[x][y] , l[xx][yy]);
		r[x][y] = max(r[x][y] , r[xx][yy]);
	}
}
int main() {
	cin >> n >> m;
	for(int i = 1 ; i <= n ; i ++) {
		for(int j = 1 ; j <= m ; j ++) {
			cin >> high[i][j];
		}
	}
	memset(l , 0x3f , sizeof(l));
	for(int i = 1 ; i <= m ; i ++) l[n][i] = r[n][i] = i;
	for(int i = 1 ; i <= m ; i ++) if(!vis[1][i]) dfs(1 , i);
	bool is_w = false;
	int cnt = 0;
	for(int i = 1 ; i <= m ; i ++) {
		if(!vis[n][i]) {
			is_w = true;
			cnt ++;
		}
	}
	if(is_w) {
		cout << 0 << "\n" << cnt;
		return 0;
	}

    for(int i = 1; i <= m; ++i) {
		if(l[1][i] == 0x3f3f3f3f and r[1][i] == 0)
			continue;
        ss.push_back(make_pair(l[1][i], r[1][i]));
	}
    sort(ss.begin(), ss.end(), Camp);
	int res = 1, maxr = ss[0].second;

	for(int i = 1; i < ss.size(); ++i) {
		if(maxr == m)
			break;
		if(ss[i].second <= maxr)
			continue;
		res++;
		maxr = max(maxr, ss[i].second);
	}

    printf("1\n%d\n", res);
	getchar();
	return 0;
}