#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
/*
한시간 안에 푸는 것을 실패했다. // 시간재는중 중간에 10분정도 딴짓했다. 그리고 총 1시간 15분 미만으로 걸렸다.
finding 하는 것에 있어서 원본이 중요해서 출발 미세먼지를 나머지로 바꾸고 퍼지는 것은 copy_arr에 두고 작업을 다한뒤 합쳤다.
이 방식이 처음보는 방식이었다.
행렬 회전에 있어서 read and write step을 함수화 가능한지봐야 겠다.
*/
using namespace std;

typedef pair<int, int> PAIR;
int R, C, T;
int temp;
int d1[] = {0,1,0,-1};
int d2[] = {1,0,-1,0};
int ans = 0;
int arr[51][51];
int copy_arr[51][51];
vector<PAIR> air_cleaner;

void finding(queue<PAIR>& Q, PAIR location) {

	int new_x;
	int new_y;
	int blowed;
	int remain;
	int current_dust = arr[location.first][location.second];

	vector<PAIR> temp_arr;

	for (int i = 0; i < 4; ++i) {
		new_x = location.first + d1[i];
		new_y = location.second + d2[i];
		if (1 <= new_x && new_x <= R && 1 <= new_y && new_y <= C && arr[new_x][new_y] != -1) {
			temp_arr.push_back(make_pair(new_x,new_y));
		}
	}
	blowed = (current_dust / 5);
	remain = current_dust - blowed * temp_arr.size();
	for (const PAIR loc : temp_arr) {
		copy_arr[loc.first][loc.second] += blowed;
	}
	arr[location.first][location.second] = remain;
}

void reset_copyarr() {

	for (int i = 1; i <= R; ++i) {
		for (int j = 1; j <= C; ++j) {
			copy_arr[i][j] = 0;
		}
	}
}

void summation() {

	for (int i = 1; i <= R; ++i) {
		for (int j = 1; j <= C; ++j) {
			arr[i][j] += copy_arr[i][j];
		}
	}
}

void upper_cleaner() {

	PAIR upper_machine = air_cleaner[0];
	vector<int> upper_arr;
	int start_x = upper_machine.first;
	int start_y = upper_machine.second;

	/* read step*/

	// right
	for (int y = start_y + 1; y <= C; ++y) {
		upper_arr.push_back(arr[start_x][y]);
	}

	// upper
	for (int x = start_x - 1; x > 1; --x) {
		upper_arr.push_back(arr[x][C]);
	}

	// left
	for (int y = C; y >= 1; --y) {
		upper_arr.push_back(arr[1][y]);
	}

	// down
	for (int x = 2; x < start_x; ++x) {
		upper_arr.push_back(arr[x][1]);
	}

	/* cleaning */
	upper_arr.pop_back();
	upper_arr.insert(upper_arr.begin(), 0);

	/* write step */
	int cnt = 0;
	for (int y = start_y + 1; y <= C; ++y) {
		arr[start_x][y] = upper_arr[cnt++];
	}

	// upper
	for (int x = start_x - 1; x > 1; --x) {
		arr[x][C] = upper_arr[cnt++];
	}

	// left
	for (int y = C; y >= 1; --y) {
		arr[1][y] = upper_arr[cnt++];
	}

	// down
	for (int x = 2; x < start_x; ++x) {
		arr[x][1] = upper_arr[cnt++];
	}
}

void lower_cleaner() {

	PAIR lower_machine = air_cleaner[1];
	int start_x = lower_machine.first;
	int start_y = lower_machine.second;
	vector<int> lower_arr;


	/* read step*/

	// right
	for (int y = start_y + 1; y <= C; ++y) {
		lower_arr.push_back(arr[start_x][y]);
	}

	// down
	for (int x = start_x + 1; x < R; ++x) {
		lower_arr.push_back(arr[x][C]);
	}

	//left
	for (int y = C; y >= 1; --y) {
		lower_arr.push_back(arr[R][y]);
	}

	// upeer
	for (int x = R -1; x > start_x; --x) {
		lower_arr.push_back(arr[x][1]);
	}

	/* cleaning */
	lower_arr.pop_back();
	lower_arr.insert(lower_arr.begin(), 0);


	/* write step */

	int cnt = 0;

	// right
	for (int y = start_y + 1; y <= C; ++y) {
		arr[start_x][y] = lower_arr[cnt++];
	}

	// down
	for (int x = start_x + 1; x < R; ++x) {
		arr[x][C] = lower_arr[cnt++];
	}

	//left
	for (int y = C; y >= 1; --y) {
		arr[R][y] = lower_arr[cnt++];
	}

	// upeer
	for (int x = R - 1; x > start_x; --x) {
		arr[x][1] = lower_arr[cnt++];
	}

}

int counting() {

	
	int sum = 0;
	for (int i = 1; i <= R; ++i) {
		for (int j = 1; j <= C; ++j) {

			if (arr[i][j] > 0) {
				sum += arr[i][j];
			}
		}
	}

	return sum;
}

void processing() { 

	for (int i = 0; i < T; ++i) {
	
		// wave
		reset_copyarr();
		queue<PAIR> Q;
		for (int i = 1; i <= R; ++i) {
			for (int j = 1; j <= C; ++j) {
				if (arr[i][j] > 0)
					Q.push(make_pair(i,j));
			}
		}
		while (!Q.empty()) {
			PAIR loc = Q.front();
			Q.pop();
			finding(Q, loc);
		}
		summation();

		// cleaner
		upper_cleaner();
		lower_cleaner();
	}

	ans = counting();
}

int main()
{

	freopen("input.txt","r", stdin);

	scanf("%d %d %d",&R,&C,&T);

	for (int i = 1; i <= R; ++i) {
		for (int j = 1; j <= C; ++j) {
			scanf("%d",&temp);
			arr[i][j] = temp;

			if (temp == -1) {
				air_cleaner.push_back(make_pair(i,j));
			}
		}
	}

	processing();

	printf("%d",ans);
	return 0;
}


