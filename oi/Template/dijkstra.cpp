#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <queue>

using namespace std;

const int MAX_N = 100000 + 10;
const int MAX_E = 200000 + 10;

int n, m, s;

struct Edge {
	int next, to, val;
} edge[MAX_E];
int head[MAX_N], cnt;

inline void Add(int u, int v, int w) {
	edge[++cnt].to = v;
	edge[cnt].val = w;
	edge[cnt].next = head[u];
	head[u] = cnt;
}

struct Node {
	int idx, val;
	
	Node(int _idx, int _val) {
		idx = _idx, val = _val;
	}
	
	bool operator <(const Node Other) const {
		return val > Other.val;
	}
};

priority_queue<Node> Que;

bool vis[MAX_N];
int dis[MAX_N];

inline void Dijkstra() {
	
	memset(dis, 0x3f, sizeof(dis));
	
	dis[s] = 0;
	Que.push(Node(s, 0));
	
	while (!Que.empty()) {
		int x = Que.top().idx; Que.pop();
		
		if (vis[x]) continue;
		vis[x] = true;
		
		for (int i = head[x]; ~i; i = edge[i].next) {
			int v = edge[i].to, w = edge[i].val;
			
			if (dis[x] + w < dis[v]) {
				dis[v] = dis[x] + w;
				
				if (!vis[v]) Que.push(Node(v, dis[v]));
			}
		}
	}	
}

int main() {
	
	scanf("%d%d%d", &n, &m, &s);
	
	memset(head, -1, sizeof(head));
	
	for (int i = 1; i <= m; i++) {
		int u, v, w; scanf("%d%d%d", &u, &v, &w);
		
		Add(u, v, w);
	}
	
	Dijkstra();
	
	for (int i = 1; i <= n; i++) {
		printf("%d ", dis[i]);
	}
	
	puts("");
	
	return 0;
}