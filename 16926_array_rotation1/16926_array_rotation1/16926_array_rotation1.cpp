#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>

/*
11 12 13 14 15
21 22 23 24 25
31 32 33 34 35
41 42 43 44 45
51 52 53 54 55

11 ~ 15 right
25 ~ 45 down
55 ~ 51 left
41 ~ 21 up

순으로 하면 처음 시도했던 방법보다 훨씬 깔끔하고 좋다. 
vector를 조정하면 시계 반시계 조정이 가능하다.
shifting 할때 for문을 사용하면 훨씬 빨라질 수 있다. 대략 5배가량 빨라진다.

*/
using namespace std;

int N, M, R;
int temp;
int arr[301][301];

void processing() {

	int start_x = 1;
	int start_y = 1;
	int end_x = N;
	int end_y = M; 
	vector<int> temp_arr;

	while (start_x <= end_x && start_y <= end_y) {

		// read step
		// left direction
		for (int y = start_y; y <= end_y; ++y) {
			temp_arr.push_back(arr[start_x][y]);
		}

		// down direction
		for (int x = start_x + 1; x < end_x; ++x) {
			temp_arr.push_back(arr[x][end_y]);
		}

		// right direction
		for (int y = end_y; y >= start_y; --y) {
			temp_arr.push_back(arr[end_x][y]);
		}

		// upper direction
		for (int x = end_x - 1; x > start_x; --x) {
			temp_arr.push_back(arr[x][start_y]);
		}

		// shifting
		for (int i = 0; i < R; ++i) {
			int temp_int = temp_arr.front();
			temp_arr.erase(temp_arr.begin());
			temp_arr.push_back(temp_int);
		}
		
		// write step
		int cnt = 0;
	
		for (int y = start_y; y <= end_y; ++y) {
			arr[start_x][y] = temp_arr[cnt++];
		}

		// down direction
		for (int x = start_x + 1; x < end_x; ++x) {
			arr[x][end_y] = temp_arr[cnt++];
		}

		// right direction
		for (int y = end_y; y >= start_y; --y) {
			arr[end_x][y] = temp_arr[cnt++];
		}

		// upper direction
		for (int x = end_x - 1; x > start_x; --x) {
			arr[x][start_y] = temp_arr[cnt++];
		}

		temp_arr.clear();
		start_x += 1;
		start_y += 1;
		end_x -= 1;
		end_y -= 1;

	}
}

int main()
{
	freopen("input.txt","r",stdin);

	scanf("%d %d %d",&N, &M, &R);

	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= M; ++j) {
			scanf("%d", &temp);
			arr[i][j] = temp;
		}
	}


	//for (int i = 0; i < R; ++i) {
		processing();
	//}

	// print arr
	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= M; ++j) {
			printf("%2d ", arr[i][j]);
		}
		printf("\n");
	}
	

}

