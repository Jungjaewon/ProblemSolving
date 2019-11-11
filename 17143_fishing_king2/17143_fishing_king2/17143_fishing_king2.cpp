#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <utility>
#include <cstdio>
using namespace std;


/*
19-10-14
어제 처음에 시도 할때는 채점 진행이 되지 않았다.
그래서 예상과 다르게 동작이 돼서 문제가 발생됐다.
오늘도 시간을 보내면서 배열에서 순회를 할때는 범위가 미만인지 초과인지 제대로 확인을 해야겠다.
이 문제에서는 상어가 먼저 이동을 하고 방향을 전환했다.

테스트 케이스 중에는 양끝에 있지만 방향전환이 안되어 있는 상어들이 있을 것이다. 그래서 문제가 됐다.

그리고 스피드가 1000이상가기 때문에 % 연산을 해주어야한다. 시험에서 변수의 범위를 잘 체크해야겠다.
*/
int px = 0;
int py = 0;
int R, C, M;
int ix, iy, is, id, iz;
int ans = 0;

int dx[] = { -1,-1,1, 0,0 };
int dy[] = { -1, 0,0,1,-1 };
typedef pair<int, int> PAIR;
typedef struct shark_s {
	int speed;
	int dir;
	int size;
	bool exist;
	shark_s() : speed(0), dir(0), size(0), exist(false) {}
	shark_s(int ispeed, int idir, int isize, bool iexist) : speed(ispeed), dir(idir), size(isize), exist(iexist) {}
} SHARK;

SHARK arr[101][101];
map<pair<int, int>, vector<SHARK>> shark_map;

void moving_fishing() {

	++py;
	printf("px : %d, py : %d\n",px,py);
	for (int i = 1; i <= R; ++i) {
		if (arr[i][py].exist) {
			ans += arr[i][py].size;
			printf("X : %d, Y : %d, Size : %d, dir : %d, speed : %d\n",i,py, arr[i][py].size, arr[i][py].dir, arr[i][py].speed);
			arr[i][py] = { 0,0,0,false };
			return;
		}
	}
}
void shark_moving() {
	for (int i = 1; i <= R; ++i) {
		for (int j = 1; j <= C; ++j) {

			if (!arr[i][j].exist)
				continue;
			else {
				int speed;
				int oring_speed = arr[i][j].speed;
				int size = arr[i][j].size;
				int dir = arr[i][j].dir;
				if (dir == 1 || dir == 2)
					speed = oring_speed % (2 * (R - 1));
				else
					speed = oring_speed % (2 * (C - 1));
				arr[i][j] = { 0,0,0,false };
				int x = i;
				int y = j;
				while (speed) {
					
					if (x == 1 && dir == 1)
						dir = 2;
					else if (x == R && dir == 2)
						dir = 1;
					else if (y == C && dir == 3)
						dir = 4;
					else if (y == 1 && dir == 4)
						dir = 3;
					//printf("dir : %d, dx[dir] : %d , dy[dir] : %d",dir, dx[dir], dy[dir]);
					x += dx[dir]; 
					y += dy[dir];
					
					--speed;
				}
				//printf("X: %d, Y : %d\n",x,y);
				shark_map[make_pair(x, y)].push_back(SHARK(oring_speed, dir, size, true));
			}
		}
	}
	map<pair<int, int>, vector<SHARK>>::iterator iter;

	for (iter = shark_map.begin(); iter != shark_map.end(); ++iter) {
		vector<SHARK> temp_arr = iter->second;
		if (temp_arr.size() == 0)
			continue;
		else if (temp_arr.size() == 1) {
			PAIR temp_loc = iter->first;
			arr[temp_loc.first][temp_loc.second] = SHARK(temp_arr[0].speed, temp_arr[0].dir, temp_arr[0].size, true);
		}
		else if (temp_arr.size() > 1) {
			//printf("temp_arr.size()  : %d\n", temp_arr.size());
			PAIR temp_loc = iter->first;
			int idx = 0;
			int qsize = temp_arr[0].size;
			for (int i = 1; i < temp_arr.size(); ++i) {
				if (temp_arr[i].size > qsize) {
					qsize = temp_arr[i].size;
					idx = i;
				}
			}
			//printf("bite  winner size %d \n", temp_arr[idx].size);
			arr[temp_loc.first][temp_loc.second] = SHARK(temp_arr[idx].speed, temp_arr[idx].dir, temp_arr[idx].size, true);
		}
		iter->second.clear();
	}

	shark_map.clear();
}

int main()
{
	freopen("input.txt","r",stdin);
	scanf("%d %d %d", &R, &C, &M);

	if (M > 0) {
		for (int i = 0; i < M; ++i) {
			scanf("%d %d %d %d %d", &ix, &iy, &is, &id, &iz);
			printf("ix : %d, iy : %d, is : %d, id : %d, iz : %d\n",ix,iy,is,id,iz);
			arr[ix][iy] = { is,id,iz, true };
		}
		for (int i = 0; i < C; ++i) {
			moving_fishing();
			shark_moving();
		}
	}
	printf("%d", ans);
	return 0;
}

