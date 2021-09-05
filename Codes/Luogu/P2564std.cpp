#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e6 + 10; 
//int Q[maxn];
int head = 1,tail = 0;
int n,m;
//vector < int > a[maxn];
int bow[maxn + 1000];
struct node {
	int pos,col;
}q[maxn];
bool cmp(node a , node b) {
	return a.pos < b.pos;
}
int main() {
	int Maxx = 0;
	cin >> n >> m;
	int tot = 0;
	for(int i = 1 ; i <= m ; i ++) {
		int t;
		cin >> t;
		while(t --) {
			int x;
			cin >> x;
			q[++ tot].pos = x;
			q[tot].col = i;
		}
	}
	sort(q + 1 , q + n + 1 , cmp);
	int cnt = 0;
	int minn = (1 << 30);
	int ml,mr;
	while(head <= n and tail <= n) {
		++ tail;
		if(bow[q[tail].col] == 0) cnt ++;
		bow[q[tail].col] ++;
		while(head <= tail and bow[q[head].col] > 1) bow[q[head].col] --,head ++;
//		cout << tail << " " << cnt << endl;
		if(cnt == m) {
			if(q[tail].pos - q[head].pos + 1 < minn) {
				minn = q[tail].pos - q[head].pos + 1;
//				ml = head,mr = tail;
			}
		}
	}
	cout << minn - 1;
}