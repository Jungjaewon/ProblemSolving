

#include <iostream>
#include <cstdio>
#include <map>
#include <queue>
#include <set>
#include <vector>

#define N_SIZE 101
using namespace std;

typedef struct xy {

	int x;
	int y;

	xy(int ix, int iy) :x(ix), y(iy) {}
	xy() :x(0), y(0) {}

} xy_s;

int T;
int N;
int M;
int Start;
int End;
int result;
bool visited[N_SIZE];
bool relationship[N_SIZE][N_SIZE];

void bfs(int node) {
// https://greatepig.tistory.com/40 // dfs
// https://willbfine.tistory.com/395 // union-find

	queue<int> q;
	q.push(node);
	visited[node] = true;
	while (!q.empty()) {
		node = q.front();
		q.pop();

		for (int i = 1; i <= N; ++i) {
			if ( visited[i] || ( relationship[node][i] == false))
				continue;
			q.push(i);
			visited[i] = true;
		}
	}

}

void dfs(int node) {

	visited[node] = true;

	for (int i = 1; i <= N; ++i) {
		if (visited[i] || (relationship[node][i] == false))
			continue;
		else
			dfs(node);
	
	}
}

void reset() {

	for (int i = 1; i <= N; ++i)
		visited[i] = false;

	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= N; ++j)
			relationship[i][j] = false;
	
	}
}

int main()
{
	scanf("%d", &T);

	for (int i = 0; i < T; ++i) {

		scanf("%d %d", &N, &M);


		for (int j = 0; j < M; ++j) {
			scanf("%d %d", &Start, &End);
			relationship[Start][End] = true; // undirected graph
			relationship[End][Start] = true;
		}

		int cnt = 0;
		for (int j = 1; j <= N; ++j) {
			if (!visited[j]) {
				bfs(j);
				++cnt;
			}
		}

		printf("#%d %d\n", i + 1, cnt);
		reset();
	}
}

