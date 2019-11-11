#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cmath>

using namespace std;
typedef pair<int, int> PAIR;
typedef pair<pair<int, int>, pair<int, int>> TRIP;
vector<vector<TRIP>> island_arr;
int N, M;
int map_arr[11][11];
int copy_arr[11][11];
int adj[7][7];
bool check_visited[7];
bool visited[11][11];
bool impossible = true;
int dx[] = {0,1,0,-1};
int dy[] = {1,0,-1,0};
int ans = 10e5;
int num_islands = 0;
int building_cnt = 0;


/*
시험장에서 어쩌피 못풀 문제였다.
지금 코드로 예제 케이스는 모두 돌아가나 히든케이스에서 막힌다.
시험장에서 못풀었다고 억울해 할필요가 없었던 것이다.

finding 함수에서 큐를 참조자로 선언하지 않아서 섬이 제대로 나누어지지 않아 고생좀 했다. 삽질 실전에서 섬나누는 방법에서 실수(방문체크를 안함, 20분 날림)를 한것과 같다.

4 9
0 0 1 1 1 0 0 2 0
3 0 0 1 0 0 0 2 0
0 0 4 0 0 5 0 2 0
6 0 0 0 0 0 0 2 0

4,5 번이 연결되면 1번과 자동으로 연결된다 전체 연결 함수확인 방법을 바꾸면 해결 할 수 있다.
자료구조를 개선해서하면 문제를 풀 수 있을 것 같다.
adj matrix를 만들어서 모두 true이면 cnt를 갱신한다.

*/

/*
자료구조 수정으로 통과
원본 섬에 idx를 기록하고 adj matrix를 만들어서 mst를 형성 했는지 확인
adj를 만든 후 reset_visited를 해서 순서를 바꾸어서 해결함.

모두 연결하고 단순히 BFS하면 1이니까 다리와 섬을 구분하지 못한다. 는 점을 다음번에는 기억해야한다.
문제가 생겼을때 redo할 필요 없이 그냥 return으로 버리는 것도 기억해야한다. 안그러면 시간낭비
*/

void copy_map() {

	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= M; ++j) {
			if(copy_arr[i][j] != map_arr[i][j])
				copy_arr[i][j] = map_arr[i][j];
		}
	}
}

void reset_visited() {


	for (int i = 1; i <= num_islands; ++i) {
		check_visited[i] = false;
	}
	for (int i = 1; i <= num_islands; ++i) {
		for (int j = 1; j <= num_islands; ++j) {
			adj[i][j] = 0;
		}
	}
	/*
	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= M; ++j) {
			if (visited[i][j])
				visited[i][j] = false;
		}
	}
	*/
}

bool checking_all() {
	
	/*
	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= M; ++j) {
			if (!visited[i][j] && copy_arr[i][j] == 1)
				return false;
		}
	}
	*/
	for (int i = 1; i <= num_islands; ++i)
		if (!check_visited[i])
			return false;

	return true;
}

void finding_map(int x, int y, queue<PAIR>& Q) {

	for (int i = 0; i < 4; ++i) {
		int nx = x + dx[i];
		int ny = y + dy[i];

		if (1 <= nx && nx <= N && 1 <= ny && ny <= M && !visited[nx][ny] && map_arr[nx][ny] == 1) {
			visited[nx][ny] = true;
			Q.push(make_pair(nx, ny));
		}
	}
}

void finding_copy(int x, int y, queue<PAIR>& Q) {

	for (int i = 0; i < 4; ++i) {
		int nx = x + dx[i];
		int ny = y + dy[i];

		if (1 <= nx && nx <= N && 1 <= ny && ny <= M && !visited[nx][ny] && copy_arr[nx][ny] == 1) {
			visited[nx][ny] = true;
			Q.push(make_pair(nx, ny));
		}
	}
}

void finding_islands() {

	int idx = 1;
	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= M; ++j) {

			if (visited[i][j] || map_arr[i][j] == 0)
				continue;
			else {
				queue<PAIR> Q;
				Q.push(make_pair(i, j));
				visited[i][j] = true;
				vector<TRIP> each_land;
				
				while (!Q.empty()) {

					PAIR temp = Q.front(); Q.pop();
					finding_map(temp.first, temp.second, Q);
					for (int k = 0; k < 4; ++k) {
						int nx = temp.first + dx[k];
						int ny = temp.second + dy[k];

						if (1 <= nx && nx <= N && 1 <= ny && ny <= M && map_arr[nx][ny] != 1) {
							each_land.push_back(make_pair(make_pair(temp.first, temp.second), make_pair(k, idx)));
						}
					}
					
				}
				island_arr.push_back(each_land);
				++idx;
			}
		}
	}

	num_islands = island_arr.size();
	for (int i = 0; i < island_arr.size(); ++i) {
		for (int j = 0; j < island_arr[i].size(); ++j) {

			int x = island_arr[i][j].first.first;
			int y = island_arr[i][j].first.second;
			map_arr[x][y] = i + 1;
		}
	}
}

void copy_bfs() {

	/*
	queue<PAIR> Q;
	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= M; ++j) {
			if (visited[i][j] || copy_arr[i][j] == 0)
				continue;
			Q.push(make_pair(i, j));
			visited[i][j] = true;
			while (!Q.empty()) {
				PAIR temp = Q.front(); Q.pop();
				finding_copy(temp.first, temp.second, Q);
			}
		}
	}
	*/

	queue<int> Q;
	Q.push(1);
	check_visited[1] = true;

	while (!Q.empty()) {
		int target = Q.front(); Q.pop();
		for (int i = 1; i <= num_islands; ++i) {
			if (check_visited[i] || adj[target][i] == 0)
				continue;
			Q.push(i);
			check_visited[i] = true;
		}
	}
}
void building(vector<TRIP> member_vector) {

	//copy_map();
	reset_visited();
	int cnt = 0;
	int prev_cnt = 0;
	for (int i = 0; i < member_vector.size(); ++i) {
		int dir = member_vector[i].second.first;
		int idx = member_vector[i].second.second;
		int nx = member_vector[i].first.first + dx[dir];
		int ny = member_vector[i].first.second + dy[dir];

		prev_cnt = cnt;
		while (1 <= nx && nx <= N && 1 <= ny && ny <= M && !(map_arr[nx][ny] >= 1)) {
			cnt += 1;
			//copy_arr[nx][ny] = 1;
			nx += dx[dir];
			ny += dy[dir];
		}
		//printf("gap %d\n",gap);
		// cancel
		if (!(1 <= nx && nx <= N && 1 <= ny && ny <= M)) {
			//printf("nx : %d,  ny  %d, dir : %d\n",nx,ny,dir);
			return;
			/*
			cnt = prev_cnt;
			nx -= dx[dir];
			ny -= dy[dir];
			while (gap > 0) {
				copy_arr[nx][ny] = 0;
				nx -= dx[dir];
				ny -= dy[dir];
				--gap;
			}
			do_bfs = false;
			break;
			*/
		}
		else if (abs(cnt - prev_cnt) <= 1) {
			return;
			/*
			cnt = prev_cnt;
			while (gap > 0) {
				copy_arr[nx][ny] = 0;
				nx -= dx[dir];
				ny -= dy[dir];
				--gap;
			}
			do_bfs = false;
			break;
			*/
		}
		else {
			adj[idx][map_arr[nx][ny]] = 1;
			adj[map_arr[nx][ny]][idx] = 1;
		}
	}

	//if(do_bfs){
	copy_bfs();
	//}

	//if (do_bfs && checking_all()) {
	if (checking_all()) {
		ans = min(ans, cnt);
		impossible = false;
	}
	else
		;


}

void dfs(int idx, vector<TRIP> member_vector) {

	if (num_islands == member_vector.size()) {
		building(member_vector);
		return;
	}
	else if (num_islands - 1 == member_vector.size()) {
		building(member_vector);
	}
	
	for (int i = 0; i < island_arr[idx].size(); ++i) {
		member_vector.push_back(island_arr[idx][i]);
		dfs(idx + 1 , member_vector);
		member_vector.pop_back();
	}

}

int main()
{
	freopen("input.txt","r",stdin);

	scanf("%d %d",&N,&M);

	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= M; ++j) {
			scanf("%d",&map_arr[i][j]);
		}
	}

	finding_islands();
	/*
	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= M; ++j) {
			printf("%d ",map_arr[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	printf("num_islands : %d\n", num_islands);
	*/
	dfs(0, {});
	if (impossible)
		printf("-1");
	else
		printf("%d",ans);

	return 0;
}
