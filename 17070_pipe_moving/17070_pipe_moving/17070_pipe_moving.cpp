#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cmath>


/*
문제 자체는 어렵지 않았다.
코딩실수도 없었다.

문제는 카운팅을 하고 습관적으로 return을 했다. 그렇기 때문에 1을 세고 바로 종료했다.
return 하지 않았다면 40분만에 풀었을 것이고

고려하면 1시간 30분 미만으로 걸렸다. 잘못했으면 어제 처럼 시간을 썼을것 같다.

고로 프로그램 테스트 전 프로그램 다시 읽고 점검해야하는 것을 습관화해야겠다.
*/
using namespace std;

typedef pair<int, int> PAIR;

typedef struct state_s {

	PAIR first;
	PAIR second;
	state_s() :first({ 0,0 }), second({ 0,0 }) {}
	state_s(PAIR ifirst, PAIR isecond) :first(ifirst), second(isecond) {}
} STATE;
int N;
int arr[17][17];
int ans = 0;
PAIR loc1 = { 1,1 };
PAIR loc2 = { 1,2 };

void finding(queue<STATE> &Q, STATE state) {

	int fx = state.first.first;
	int fy = state.first.second;
	int sx = state.second.first;
	int sy = state.second.second;

	//printf("%d %d %d %d", fx, fy, sx, sy);
	if (abs(fy - sy) == 1 && abs(fx - sx) == 1) {
		//printf(" digoanl\n");
		if (1 <= sy + 1 && sy + 1 <= N && arr[sx][sy + 1] != 1) {
			//printf("diag 1, %d %d %d %d\n", sx, sy, sx, sy + 1);
			Q.push(STATE({ sx,sy }, { sx,sy + 1 }));
		}

		if (1 <= sx + 1 && sx + 1 <= N && arr[sx + 1][sy] != 1) {
			//printf("diag 2, %d %d %d %d\n", sx, sy, sx + 1, sy);
			Q.push(STATE({ sx,sy }, { sx + 1,sy }));
		}

		if (1 <= sy + 1 && sy + 1 <= N && arr[sx][sy + 1] != 1) {
			if (1 <= sx + 1 && sx + 1 <= N && arr[sx + 1][sy] != 1) {
				if (1 <= sx + 1 && sx + 1 <= N && 1 <= sy + 1 && sy + 1 <= N && arr[sx + 1][sy + 1] != 1) {
					//printf("diag 3, %d %d %d %d\n", sx, sy, sx + 1, sy + 1);
					Q.push(STATE({ sx,sy }, { sx + 1,sy + 1 }));
				}
			}
		}
	}
	else if (abs(fy - sy) == 1 && abs(fx - sx) == 0) { // garo
		//printf(" garo\n");
		// move right
		if (1 <= sy + 1 && sy + 1 <= N && arr[sx][sy + 1] != 1) {
			//printf("garo 1, %d %d %d %d\n", sx, sy, sx, sy + 1);
			Q.push(STATE({sx,sy},{sx,sy + 1}));
		}

		if (1 <= sy + 1 && sy + 1 <= N && arr[sx][sy + 1] != 1) {
			if (1 <= sx + 1 && sx + 1 <= N && arr[sx + 1][sy] != 1) {
				if (1 <= sx + 1 && sx + 1 <= N && 1 <= sy + 1 && sy + 1 <= N && arr[sx + 1][sy + 1] != 1) {
					//printf("garo 2, %d %d %d %d\n", sx, sy, sx + 1, sy + 1);
					Q.push(STATE({ sx,sy }, { sx + 1,sy + 1 }));
				}
			}
		}
	}
	else if (abs(fx - sx) == 1 && abs(fy - sy) == 0) { // sero
		//printf(" sero\n");
		if (1 <= sx + 1 && sx + 1 <= N && arr[sx + 1][sy] != 1) {
			//printf("sero 1, %d %d %d %d\n", sx, sy, sx + 1, sy);
			Q.push(STATE({ sx,sy }, { sx + 1,sy}));
		}

		if (1 <= sy + 1 && sy + 1 <= N && arr[sx][sy + 1] != 1) {
			if (1 <= sx + 1 && sx + 1 <= N && arr[sx + 1][sy] != 1) {
				if (1 <= sx + 1 && sx + 1 <= N && 1 <= sy + 1 && sy + 1 <= N && arr[sx + 1][sy + 1] != 1) {
					//printf("sero 2, %d %d %d %d\n", sx, sy, sx + 1, sy + 1);
					Q.push(STATE({ sx,sy }, { sx + 1,sy + 1 }));
				}
			}
		}
	}
}

void processing() {

	queue<STATE> Q;

	Q.push({loc1, loc2});

	while (!Q.empty()) {
	
		STATE temp = Q.front(); Q.pop();

		if ((temp.first.first == N && temp.first.second == N) || (temp.second.first == N && temp.second.second == N)) {
			ans += 1;
		}

		finding(Q, temp);
	}
}

int main()
{

	freopen("input.txt","r",stdin);
	scanf("%d",&N);

	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= N; ++j) {
			scanf("%d",&arr[i][j]);
		}
	}

	processing();
	printf("%d",ans);
	return 0;
}

