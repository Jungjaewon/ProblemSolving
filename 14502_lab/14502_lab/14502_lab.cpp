#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <utility>
#include <queue>
#include <algorithm>


/*
finding 함수에서 arr[new_x][new_x] 문제가 있었다.
그리고 int bit수가 32개인데 멤버의 개수가 32개를 넘었다 매우 주의를 해야한다. 최대 멤버수를 확인해야한다. 
*** big problem 이문제가 dfs를 제대로 동작하지 않게 만든다. -> 무한루프 발생 or runtime error 발생

*/
using namespace std;
int N, M;
int blank = 0;
int wall = 1;
int virus = 2;
int arr[9][9];
bool visited[9][9];
int temp;
int member_size;
int ans = -100000;

typedef pair<int, int> PAIR;
int d1[] = { 0,1,0,-1 };
int d2[] = { 1,0,-1,0 };

vector<PAIR> blank_arr;
vector<PAIR> virus_arr;
vector<int> member_arr;

void reset_visited() {

	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= M; ++j) {
			visited[i][j] = false;
		}
	}
}

int check_safety_area() {

	int cnt = 0;
	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= M; ++j) {

			if (arr[i][j] == blank && !visited[i][j])
				++cnt;
		}
	}

	return cnt;
}

void finding(int x, int y, queue<PAIR>&Q) {
	int new_x;
	int new_y;

	for (int i = 0; i < 4; ++i) {
		new_x = x + d1[i];
		new_y = y + d2[i];

		if (1 <= new_x && new_x <= N && 1 <= new_y && new_y <= M && !visited[new_x][new_y]) {

			if (arr[new_x][new_y] == blank) {
				Q.push(make_pair(new_x, new_y));
				visited[new_x][new_y] = true;
			}
		}
	}

}

void bfs(vector<int> member_arr) {

	for (int i = 0; i < member_arr.size(); ++i) {
		if (member_arr[i] == 1) {
			visited[blank_arr[i].first][blank_arr[i].second] = true;
		}
	}

	queue<PAIR> Q;

	for (int i = 0; i < virus_arr.size(); ++i) {
	
		Q.push(make_pair(virus_arr[i].first, virus_arr[i].second));
		visited[virus_arr[i].first][virus_arr[i].second] = true;
	}

	while (!Q.empty()) {
	
		PAIR temp = Q.front();
		Q.pop();
		finding(temp.first, temp.second, Q);
	}

	ans = max(ans, check_safety_area());
}

int main()
{

	freopen("input.txt","r",stdin);

	scanf("%d %d",&N,&M);
	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= M; ++j) {
			scanf("%d",&temp);
			arr[i][j] = temp;
			if (temp == blank) {
				blank_arr.push_back(make_pair(i,j));
			}
			else if (temp == virus) {
				virus_arr.push_back(make_pair(i, j));
			}
		}
	}
	member_size = blank_arr.size();
	member_arr.push_back(1);
	member_arr.push_back(1);
	member_arr.push_back(1);

	for (int i = 0; i < member_size - 3; ++i) {
		member_arr.push_back(0);
	}
	stable_sort(member_arr.begin(), member_arr.end());

	do {
		bfs(member_arr);
		reset_visited();
	} while (next_permutation(member_arr.begin(), member_arr.end()));

	printf("%d",ans);
	return 0;
}
