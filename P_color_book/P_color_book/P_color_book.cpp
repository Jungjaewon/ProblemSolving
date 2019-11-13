#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <utility>

using namespace std;
typedef pair<int, int> PAIR;

int dx[] = { 0,1,0,-1 };
int dy[] = { 1,0,-1,0 };
bool visited[100][100];

void finding(const vector<vector<int>>& picture, int x, int y, queue<PAIR>& Q, const int m, const int n, const int value) {
	int nx;
	int ny;

	for (int i = 0; i < 4; ++i) {
		nx = x + dx[i];
		ny = y + dy[i];
		if (0 <= nx && nx <= (m - 1) && 0 <= ny && ny <= (n - 1) && !visited[nx][ny] && picture[nx][ny] == value) {
			Q.push(make_pair(nx, ny));
			visited[nx][ny] = true;
		}
	}

}

vector<int> bfs(const int m, const int n, const vector<vector<int>> picture) {

	for (int x = 0; x < m; ++x) {
		for (int y = 0; y < n; ++y) {
			visited[x][y] = false;
		}
	}

	int max_area = 0;
	int area_cnt = 0;

	for (int x = 0; x < m; ++x) {
		for (int y = 0; y < n; ++y) {
			if (visited[x][y] || picture[x][y] == 0)
				continue;

			++area_cnt;
			queue<PAIR> Q;
			int cnt = 0;
			int value = picture[x][y];
			Q.push(make_pair(x, y));
			visited[x][y] = true;
			while (!Q.empty()) {
				PAIR temp = Q.front(); Q.pop();
				finding(picture, temp.first, temp.second, Q, m, n, value);
				++cnt;
			}
			max_area = max(max_area, cnt);
		}
	}

	return { area_cnt, max_area };
}
vector<int> solution(int m, int n, vector<vector<int>> picture) {
	return bfs(m, n, picture);
}
int main()
{
    std::cout << "Hello World!\n";
	return 0;
}
