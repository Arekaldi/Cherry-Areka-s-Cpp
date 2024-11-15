#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <algorithm>
#include <queue>
#include <vector>
#include <stack>
using namespace std;

int dist[1010][1010];
int step[1010][1010];
int graph[1010][1010];
int tt, n, m;

struct Node {
	int id;
	int dist;
	int step;

	bool operator < (const Node& other) const {
		return this->dist > other.dist;
	}
};

void dijkstra(int s) {
	for (int i = 1; i <= n; i++) {
		dist[s][i] = INT_MAX;
	}
	dist[s][s] = 0;
	step[s][s] = 0;
	priority_queue<Node> q;
	q.push({ s, 0 , 0 });

	while (!q.empty()) {
		int u = q.top().id, uDist = q.top().dist, uStep = q.top().step;
		q.pop();

		if (dist[s][u] != uDist) {
			continue;
		}

		for (int i = 1; i <= n; i++) {
			if (graph[u][i] && dist[s][i] > uDist + graph[u][i]) {
				dist[s][i] = uDist + graph[u][i];
				step[s][i] = step[s][u] + 1;
				q.push({ i, dist[s][i] , step[s][i]});
			}
		}
	}
}

int main() {
	scanf("%d", &tt);
	while (tt--) {
		scanf("%d%d", &n, &m);
		memset(graph, 0, sizeof graph);
		for (int i = 1; i <= m; i++) {
			int u, v, w;
			scanf("%d%d%d", &u, &v, &w);
			if (graph[u][v]) {
				graph[u][v] = min(graph[u][v], w);
			} else {
				graph[u][v] = w;
			}
		}

		for (int i = 1; i <= n; i++) {
			dijkstra(i);
		}


		double ans = 1e7;
		bool has = false;
		for (int i = 1; i <= n; i++) {
			for (int j = i + 1; j <= n; j++) {
				if (dist[i][j] != INT_MAX && dist[j][i] != INT_MAX) {
					double temp = (dist[i][j] + dist[j][i])  * 1.0/ (step[i][j] + step[j][i]) *1.0;
					ans = min(ans, temp);
					has = true;
				}
			}
		}

		for (int i = 1; i <= n; i++) {
			if (graph[i][i]) {
				ans = min(ans, (double)graph[i][i]);
				has = true;
			}
		}

		if (has) {
			printf("%.4lf\n", ans);
		} else {
			printf("0.0000\n");
		}
	}

	return 0;
}
