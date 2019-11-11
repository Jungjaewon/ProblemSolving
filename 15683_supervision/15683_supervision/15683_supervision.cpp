#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

/*
1시간 30분정도 했는데 구현만 했고 디버깅은 하지 못했다.
카메라의 영역 코드를 나누어 코딩작성시간을 줄였다.
위치, 카운트에 기반에서 CCTV를 분리하는 것에는 성공했는데 각각의 CCTV를 선택하는 괜찮은 방법을 잘 모르겠다.
동적할당을 써서 했는데 다른 좋은 방법이 있는 것 같다.
이 부분에 대해서는 남의 코드를 찾아봐야할 것 같다.
작업한 것의 히스토리를 기억해서 속도를 줄이는것도 좋을 것으로 생각된다 vector<pair<int,int>> history;

*/

/*
벡터 이차원 행렬을 dfs로 for문을 구현했다.
처음에 틀린 이유는 4번에 대해서 완전 구현을 하지 않아서 그렇다.
멤버 비트(벡터), index가 있으면 되고 첫번째 차원이 idx고 각 행에서 포문을 돌린다.
for문에 들어가는 변수를 중복으로 해서 에러를 만들었다.
*/

typedef pair<int, int> PAIR;

typedef struct CCTV {

	PAIR location;
	int type;
	int direction;
	CCTV() :location({0,0}),type(0), direction(0){}
	CCTV(PAIR i_location, int i_type, int i_direction) :location(i_location),type(i_type), direction(i_direction) {}
} CCTV_S;
int N, M, K;
int temp;
int under_area = -1;
int arr[9][9];
int copy_arr[9][9];
int ans = 100000;
int cctv_cnt = 0;

map<PAIR, vector<CCTV_S>> cctv_map;
vector<PAIR> blank_arr;
vector<PAIR> wall_arr;

vector<vector<CCTV_S>> cctv_2d_arr;

void check_area_type1(PAIR location,int direction) {

	if (direction == 1) { // right
		const int x = location.first;
		for (int y = location.second; y <= M; ++y) {
			if (0 < copy_arr[x][y] && copy_arr[x][y] < 6) {
				;
			}
			else if(copy_arr[x][y] == 6)
				break;
			else
				copy_arr[x][y] = under_area;
		}
	}
	else if (direction == 2) { //up
		const int y = location.second;
		for (int x = location.first; x >= 1; --x) {
			if (0 < copy_arr[x][y]  && copy_arr[x][y] < 6) {
				;
			}
			else if (copy_arr[x][y] == 6)
				break;
			else
				copy_arr[x][y] = under_area;
		}
	}
	else if (direction == 3) { // left
		const int x = location.first;
		for (int y = location.second; y >= 1; --y) {
			if (0 < copy_arr[x][y]  && copy_arr[x][y] < 6) {
				;
			}
			else if (copy_arr[x][y] == 6)
				break;
			else
				copy_arr[x][y] = under_area;
		}
	}
	else if (direction == 4) { // down
		const int y = location.second;
		for (int x = location.first; x <= N; ++x) {
			if (0 < copy_arr[x][y] && copy_arr[x][y] < 6) {
				;
			}
			else if (copy_arr[x][y] == 6)
				break;
			else
				copy_arr[x][y] = under_area;
		}
	}
}

void check_area_type2(PAIR location, int direction) {

	if (direction == 1) {
		check_area_type1(location, 1); // right
		check_area_type1(location, 3); // left
	}
	else if (direction == 2) {
		check_area_type1(location, 2); // up
		check_area_type1(location, 4); // down
	}
}

void check_area_type3(PAIR location, int direction) {

	if (direction == 1) { // right and up
		check_area_type1(location, 1); // right
		check_area_type1(location, 2); // up
	}
	else if (direction == 2) {
		check_area_type1(location, 2); // up
		check_area_type1(location, 3); // left
	}
	else if (direction == 3) {
		check_area_type1(location, 3); // left
		check_area_type1(location, 4); // down
	}
	else if (direction == 4) {
		check_area_type1(location, 4); // down
		check_area_type1(location, 1); // right
	}
}

void check_area_type4(PAIR location, int direction) {

	if (direction == 1) {
		check_area_type1(location, 2); // up
		check_area_type2(location, 1); // right left
	}
	else if (direction == 2) {
		check_area_type1(location, 4); // down
		check_area_type2(location, 1); // right left
	}
	else if (direction == 3) {
		check_area_type1(location, 1); // right
		check_area_type2(location, 2); // up down
	}
	else if (direction == 4) {
		check_area_type1(location, 3); // left
		check_area_type2(location, 2); // up down
	}
}

void check_area_type5(PAIR location, int direction) {
	check_area_type2(location, 1);// right left
	check_area_type2(location, 2);// up down
}

void copy_map() {

	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= M; ++j) {
			copy_arr[i][j] = arr[i][j];
		}
	}
}

int counting() {
	int cnt = 0;

	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= M; ++j) {
			if (copy_arr[i][j] == 0)
				++cnt;
		}
	}

	return cnt;
}

void processing(vector<CCTV_S>& selected_arr) {
	
	for (const CCTV_S cctv : selected_arr) {
		if (cctv.type == 1) {
			check_area_type1(cctv.location, cctv.direction);
		}
		else if (cctv.type == 2) {
			check_area_type2(cctv.location, cctv.direction);
		}
		else if (cctv.type == 3) {
			check_area_type3(cctv.location, cctv.direction);
		}
		else if (cctv.type == 4) {
			check_area_type4(cctv.location, cctv.direction);
		}
		else if (cctv.type == 5) {
			check_area_type5(cctv.location, cctv.direction);
		}
	}
}

void dfs(int idx, vector<CCTV_S> selected_arr) {

	if (selected_arr.size() == cctv_2d_arr.size()) {
		// do procesding
		copy_map();
		processing(selected_arr);
		/*
		for (int i = 1; i <= N; ++i) {
			for (int j = 1; j <= M; ++j) {
				printf("%3d ",copy_arr[i][j]);
			}
			printf("\n");
		}
		printf("counting() : %d\n", counting());
		printf("\n");
		printf("\n");
		*/
		
		ans = min(ans, counting());
	}
	else {
		for (int i = 0; i < cctv_2d_arr[idx].size(); ++i) {
			selected_arr.push_back(cctv_2d_arr[idx][i]);
			dfs(idx + 1, selected_arr);
			selected_arr.pop_back();
		}
	}
}

int applying(vector<CCTV_S>& selected_arr) {

	for (int i = 0; i < selected_arr.size(); ++i) {
		
		CCTV_S cctv = selected_arr[i];
		if (cctv.type == 1) {
			check_area_type1(cctv.location, cctv.direction);
		}
		else if (cctv.type == 2) {
			check_area_type2(cctv.location, cctv.direction);
		}
		else if (cctv.type == 3) {
			check_area_type3(cctv.location, cctv.direction);
		}
		else if (cctv.type == 4) {
			check_area_type4(cctv.location, cctv.direction);
		}
		else if (cctv.type == 5) {
			check_area_type5(cctv.location, cctv.direction);
		}
	}

	return counting();
}


int main()
{

	freopen("input.txt","r",stdin);
	scanf("%d %d",&N,&M);

	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= M; ++j) {
			scanf("%d",&temp);
			arr[i][j] = temp;
			if (temp == 0) { // blank
				blank_arr.push_back(make_pair(i,j));
			}
			else if (temp == 6) { // wall
				wall_arr.push_back(make_pair(i, j));
			}
			else if (0 < temp && temp < 6) {

				++cctv_cnt;
				
				if (temp == 1) {
					cctv_2d_arr.push_back({});
					for (int k = 1; k <= 4; ++k) {
						cctv_2d_arr.back().push_back(CCTV_S(make_pair(i, j), temp, k));
					}
				}
				else if (temp == 2) {
					cctv_2d_arr.push_back({});
					for (int k = 1; k <= 2; ++k) {
						cctv_2d_arr.back().push_back(CCTV_S(make_pair(i, j), temp, k));
					}
				}
				else if (temp == 3) {
					cctv_2d_arr.push_back({});
					for (int k = 1; k <= 4; ++k) {
						cctv_2d_arr.back().push_back(CCTV_S(make_pair(i, j), temp, k));
					}
				}
				else if (temp == 4) {
					cctv_2d_arr.push_back({});
					for (int k = 1; k <= 4; ++k) {
						cctv_2d_arr.back().push_back(CCTV_S(make_pair(i, j), temp, k));
					}
				}
				else if (temp == 5) {
					cctv_2d_arr.push_back({});
					cctv_2d_arr.back().push_back(CCTV_S(make_pair(i, j), temp, 1));
				}
			}
		}
	}

	dfs(0, {});

	printf("%d",ans);
	return 0;
}

