
#include <string>
#include <vector>
#include <queue>
#include <iostream>

using namespace std;

typedef pair<int, int> PAIR;

void processing(int& ans, const int& n, vector<vector<int>>& adj_map, vector<bool>& visited) {

	int level = 1;
	int cnt = 0;
	queue<int> Q;
	visited[1] = true;
	for (int i = 2; i <= n; ++i) {
		if (adj_map[1][i] == 1) {
			Q.push(i);
			visited[i] = true;
		}
	}
	//cout << "q_size : " << Q.size() <<"\n";
	while (!Q.empty()) {

		int q_size = cnt = Q.size();
		for (int i = 0; i < q_size; ++i) {
			int end = Q.front(); Q.pop();
			for (int j = 1; j <= n; ++j) {
				if (visited[j] || adj_map[end][j] == 0 || end == j)
					continue;
				else {
					Q.push(j);
					visited[j] = true;
				}
			}
		}
		++level;
	}

	ans = cnt;
}

int solution(int n, vector<vector<int>> edge) {

	int answer = 0;
	vector<vector<int>> adj_map(n + 1, vector<int>(n + 1, 0));
	vector<bool> visited(n + 1, false);

	for (int i = 0; i < edge.size(); ++i) {
		int start = edge[i][0];
		int end = edge[i][1];
		adj_map[start][end] = 1;
		adj_map[end][start] = 1;
	}
	processing(answer, n, adj_map, visited);
	return answer;
}

int main()
{
    std::cout << "Hello World!\n";
}

