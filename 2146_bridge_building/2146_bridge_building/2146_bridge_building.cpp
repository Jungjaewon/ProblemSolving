#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <queue>
#include <utility>
using namespace std;


/*
1시간 30분 조금 넘게 걸렸다.
처음에 섬을 구분하는 방법을 까먹어서 이전 것을 참조했다. 
이를 통해서 까먹었으니 연습을 꾸준히 해야겠다는 생각을 했다.

이차원 dfs에서는 각행에서 하나씩 선택 할 수 있다. 

가능한 육지 후보군을 넣을때 바다를 넣어버리는 실수를 했다.

섬을 확인하는 것을 자료구조 개선으로 활용을 해서 TRIP x,y,idx로 만들었다.
만약 섬의 다이렉션을 넣을 것이면 x,y,idx,d 로 쓸 수 있을 것이다.
*/
typedef pair<int, int> PAIR;
typedef pair<PAIR, int> TRIP;

int N;
int map_arr[101][101];
bool visited[101][101];
int dx[] = { -1,0,1,0 };
int dy[] = { 0,1,0,-1 };
int ans = 10e5;
int processing_cnt = 0;
int island_cnt = 0;
vector<vector<TRIP>> island_arr;

void reset_visited() {

	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= N; ++j) {
			if (visited[i][j])
				visited[i][j] = false;
		}
	}
}

bool idx_checking(int x, int y, int idx) {

	for (int i = 0; i < island_arr[idx].size(); ++i) {
		int tx = island_arr[idx][i].first.first;
		int ty = island_arr[idx][i].first.second;
		if (tx == x && ty == y)
			return true;
	}
	return false;
}

void finding(int x, int y, queue<PAIR>& Q) {

	int nx;
	int ny;

	for (int i = 0; i < 4; ++i) {
		nx = x + dx[i];
		ny = y + dy[i];

		if (1 <= nx && nx <= N && 1 <= ny && ny <= N && !visited[nx][ny] && map_arr[nx][ny] == 1) {
			visited[nx][ny] = true;
			Q.push(make_pair(nx,ny));
		}
	}
}

void finding_way(int x, int y, queue<PAIR>& Q, int idx) {

	int nx;
	int ny;

	for (int i = 0; i < 4; ++i) {
		nx = x + dx[i];
		ny = y + dy[i];

		if (1 <= nx && nx <= N && 1 <= ny && ny <= N && !visited[nx][ny] && map_arr[nx][ny] == 0) {
			visited[nx][ny] = true;
			Q.push(make_pair(nx, ny));
		}
	}
}

void finding_islands() {

	int idx = 0;
	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= N; ++j) {

			if (visited[i][j] || map_arr[i][j] == 0)
				continue;
			else {
				queue<PAIR> Q;
				Q.push(make_pair(i, j));
				visited[i][j] = true;
				vector<TRIP> land_arr;
				while (!Q.empty()) {
					PAIR temp = Q.front(); Q.pop();
					finding(temp.first, temp.second, Q);
					for (int k = 0; k < 4; ++k) {
						if (1 <= temp.first + dx[k] && temp.first + dx[k] <= N && 1 <= temp.second + dy[k] && temp.second + dy[k] <= N
							&& map_arr[temp.first + dx[k]][temp.second + dy[k]] != 1) {
							land_arr.push_back(make_pair(make_pair(temp.first, temp.second), idx));
						}
					}
				}
				island_arr.push_back({});
				island_arr.back() = land_arr;
				++idx;
			}
			

		}
			
	}
}

void processing(TRIP location) {

	int cnt = 0;
	int qsize = 0;
	int idx = location.second;
	queue<PAIR> Q;

	reset_visited();
	Q.push(make_pair(location.first.first, location.first.second));
	visited[location.first.first][location.first.second] = true;

	while (!Q.empty()) {

		qsize = Q.size();

		for (int i = 0; i < qsize; ++i) {
			PAIR temp = Q.front(); Q.pop();

			for (int j = 0; j < 4; ++j) {
				int nx = temp.first + dx[j];
				int ny = temp.second + dy[j];
				if (map_arr[nx][ny] == 1 && cnt != 0 && !idx_checking(nx,ny,idx)) {
					ans = min(ans, cnt);
					return;
				}
			}
			

			finding_way(temp.first, temp.second, Q, idx);
		}

		++cnt;
	}

}

void dfs(int idx, vector<TRIP> member_vector) {

	if (member_vector.size() == 1) {
		processing(member_vector[0]);
		++processing_cnt;
		//return;
	}
	else {
		for (int i = 0; i < island_arr[idx].size(); ++i) {
			member_vector.push_back(island_arr[idx][i]);
			dfs(idx + 1, member_vector);
			member_vector.pop_back();
		}
	}
}

int main()
{

	freopen("input.txt","r",stdin);
	scanf("%d",&N);


	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= N; ++j) {
			scanf("%d",&map_arr[i][j]);
		}
	}

	finding_islands();

	for (int i = 0; i < island_arr.size(); ++i) {
		island_cnt += island_arr[i].size();
		for (int j = 0; j < island_arr[i].size(); ++j) {
			processing(island_arr[i][j]);
			//int x = island_arr[i][j].first.first;
			//int y = island_arr[i][j].first.second;
			//printf("%d ", map_arr[x][y]);
		}
		//printf("\n");
	}
	//dfs(0, {});

	//printf("processing_cnt : %d\n", processing_cnt);
	//printf("island_cnt : %d\n", island_cnt);
	printf("%d",ans);
	return 0;
}

