
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

typedef pair<int, int> PAIR;

int N;
int arr[101][101];
bool visited[101][101];
int temp;
int max_value = -100000;
int ans = -100000;

int d1[] = {0,1,0,-1};
int d2[] = {1,0,-1,0};

void finding(int x, int y, queue<PAIR>& Q) {

	int new_x;
	int new_y;
	for (int i = 0; i < 4; ++i) {
		new_x = x + d1[i];
		new_y = y + d2[i];

		if (1 <= new_x && new_x <= N && 1 <= new_y && new_y <= N && !visited[new_x][new_y]) {
			Q.push(make_pair(new_x, new_y));
			visited[new_x][new_y] = true;
		}
	}
}

void reset_visited() {
	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= N; ++j) {
			visited[i][j] = false;
		}
	}
}


void bfs() {

	queue<PAIR> Q;
	int cnt = 0;


	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= N; ++j) {
			if (!visited[i][j]) {

				Q.push(make_pair(i,j));
				visited[i][j] = true;
				
				while (!Q.empty()) {

					PAIR temp_pair = Q.front();
					Q.pop();
					finding(temp_pair.first, temp_pair.second, Q);
				}
				++cnt;
			}
		}
	}

	ans = max(ans,cnt);

}

void flooding(int water_level) {

	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= N; ++j) {
			if (arr[i][j] <= water_level) {
				visited[i][j] = true;
			}
		}
	}

}
void processing() {

	for (int rain = 0; rain <= max_value - 1; ++rain) {
		
		if (rain == 0) {
			ans = 1;
		}
		else {
			flooding(rain);
			bfs();
			reset_visited();
			//printf("rain %d %d\n",rain, ans);
		}

	}
}

int main()
{

	freopen("input.txt","r",stdin);

	scanf("%d",&N);

	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= N; ++j) {
			scanf("%d", &temp);
			arr[i][j] = temp;
			max_value = max(max_value, temp);
		}
	}

	processing();
	printf("%d", ans);


}

