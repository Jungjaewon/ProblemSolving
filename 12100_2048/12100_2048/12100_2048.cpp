#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>


/*
기능구현은 1시간에 했다.
배열 복사에서 문제가 발생했다.
배열을 그대로 넘기면 call by reference가 된다. 그렇기 때문에 원본이 상실된다.
따라서 반복적으로 원본을 가지고 있다가 복원하던가 재귀로 넘겨야한다.
위 아래 왼 오 를 배열 뒤집기로 간단하게 구현하였다.
액션을 적용하기 전 후를 구분을 못해서 수정을 했다.
*/
using namespace std;

int N;
int temp;
int gameboard[21][21];
int ans = 10e-4;

int find_max(int board[21][21]){

	int result = 10e-4;

	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= N; ++j) {

			if (board[i][j] > result)
				result = board[i][j];
		}
	}

	return result;
}

vector<int> operation(vector<int> arr) {

	vector<int> result;
	int i = 0;
	for (;i < arr.size();) {

		if ( i + 1 != arr.size() && arr[i] == arr[i + 1]) {
			result.push_back(arr[i] * 2);
			i = i + 2;
		}
		else {
			result.push_back(arr[i]);
			i = i + 1;
		}
	}

	int gap = N - result.size();
	for (int i = 0; i < gap; ++i)
		result.push_back(0);

	return result;
}

void copy(int src[21][21], int dst[21][21]) {

	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= N; ++j) {
			dst[i][j] = src[i][j];
		}
	}
}

void dfs(int level, int dir, int board[21][21]) {

	if (dir == 0 || dir == 2) { // up or down

		for (int i = 1; i <= N; ++i) {

			vector<int> temp_arr;
			for (int j = 1; j <= N; ++j) {
				if (board[j][i] != 0)
					temp_arr.push_back(board[j][i]);
			}
			if (dir == 0) { // up
				vector<int> result = operation(temp_arr);
				int idx = 1;
				for (int j = 0; j < result.size(); ++j) {
					board[idx++][i] = result[j];
				}


			}
			else if (dir == 2) {
				reverse(temp_arr.begin(), temp_arr.end());
				vector<int> result = operation(temp_arr);
				int idx = N;
				for (int j = 0; j < result.size(); ++j) {
					board[idx--][i] = result[j];
				}
			}

		}

	}
	else if (dir == 1 || dir == 3) { // right or left

		for (int i = 1; i <= N; ++i) {

			vector<int> temp_arr;
			for (int j = 1; j <= N; ++j) {
				if (board[i][j] != 0)
					temp_arr.push_back(board[i][j]);
			}

			if (dir == 1) { //right
				reverse(temp_arr.begin(), temp_arr.end());
				vector<int> result = operation(temp_arr);
				int idx = N;
				for (int j = 0; j < result.size(); ++j) {
					board[i][idx--] = result[j];
				}
			}
			else if (dir == 3) { //left
				vector<int> result = operation(temp_arr);
				int idx = 1;
				for (int j = 0; j < result.size(); ++j) {
					board[i][idx++] = result[j];
				}

			}

		}
	}

	/*
	printf("level : %d\n", level);
	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= N; ++j)
			printf("%d ", board[i][j]);
		printf("\n");
	}
	*/

	if (level >= 5) {
		ans = max(ans, find_max(board));
		return;
	}

	for (int i = 0; i < 4; ++i) {
		int temp_map[21][21];
		copy(board, temp_map);
		dfs(level + 1, i, temp_map);
	}

	
	
}

void processing() {

	for (int i = 0; i < 4; ++i) {
		int temp_map[21][21];
		copy(gameboard, temp_map);
		dfs(1, i, temp_map);
	}
}

int main()
{

	freopen("input.txt","r",stdin);
	scanf("%d",&N);

	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= N; ++j) {
			scanf("%d", &temp);
			gameboard[i][j] = temp;
		}

	}

	processing();

	printf("%d",ans);
	

	return 0;
}
