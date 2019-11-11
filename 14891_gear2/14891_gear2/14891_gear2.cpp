#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>

using namespace std;

/*

프로그램 기능구현에는 25분정도 걸린 것 같다.

1시간 30분안에 풀지 못했다.
입력받는 부분에 문제가 있었다.
입력이 100111 이면 scanf("%d"); 가 아니라 scanf("%c"); scanf("%1d");로 풀어야 한다. getchar를 까먹지 않아야하고 위치도 중요하다.
그리고 이를 숫자로 변경하거나 아니면 그냥 사용하는것이 좋다.
이를 까먹어서 35분정도 시간을 날린것 같다.

prev_six, prev_two를 반대로 사용했다.

테스트 케이스 세번째르 돌리다가 뻑난다 왜인지 모르겠다.

코드간결화는 최대한 하도록하자!! 너무 힘든  것이 아니면

그냥 돌다가 터지면 배열 인덱스를 실수 한 것이다. 그러니 배열을 확인하도록 하자. visited[i]를 해서 터졌다. 코드를 꼼꼼하게


 1 * -1 = -1, -1 * -1 = 1 로 방향을 반대로 바꿀수 있다.

 Aㅏ.......
 idx - 1 > 0 가 아니라 idx - 1 > -1이였어야했다.. 앞처럼하면 0에 접근이 안된다;;;.... Aㅏ......
 코드가 맞다고 생각하면 인덱스 체크를 해보자 0~N-1, 1~N

 출력결과를 기반하여 디버깅을 하지말고 손디버깅을 하면 머리속에서 만들어진 알고리즘을 적용 받지 않을 것 같다.
*/

typedef struct order_s {
	int idx;
	bool dir; // bool 로 바꿔도 좋을 것 같다.

	order_s():idx(0),dir(0) {}
	order_s(int iidx, bool idir):idx(iidx),dir(idir) {}
} order;
typedef vector<int> vi;
vector<vi> gear_arr;
vector<order> order_arr;
char temp;
int K;
int iidx, idir;
int ans;
bool visited[4];

void move(int idx, bool dir) {
	
	int prev_two = gear_arr[idx][2];
	int prev_six = gear_arr[idx][6];
	visited[idx] = true;

	// current move
	if (dir) {
		int temp = gear_arr[idx].back();
		gear_arr[idx].pop_back();
		gear_arr[idx].insert(gear_arr[idx].begin(), temp);
	}
	else {
		int temp = gear_arr[idx].front();
		gear_arr[idx].erase(gear_arr[idx].begin());
		gear_arr[idx].push_back(temp);
	}
	

	//if (idx - 1 > -1 && !visited[idx - 1])
	//	printf("idx - 1 : %d ,gear_arr[idx - 1][2]  : %d, p_six : %d\n", idx - 1, gear_arr[idx - 1][2], prev_six);
	if (idx - 1 > -1 && !visited[idx - 1] && gear_arr[idx - 1][2] != prev_six) {
			move(idx - 1, !dir);
	}
	//if(idx + 1 < 4 && !visited[idx + 1])
	//	printf("idx + 1 : %d, gear_arr[idx + 1][6]  : %d, p_two : %d\n", idx + 1, gear_arr[idx + 1][6], prev_two);
	if (idx + 1 < 4 && !visited[idx + 1] && gear_arr[idx + 1][6] != prev_two) {
			move(idx + 1, !dir);
	}
	//printf("happyyyyy\n");
	//fflush(stdout);
}

void processing() {

	for (int i = 0; i < order_arr.size(); ++i) {
		move(order_arr[i].idx, order_arr[i].dir); // 1 :clock, -1 : clock
		for (int j = 0; j < 4; ++j)
			visited[j] = false;// 아 븅신....
		/*
		for (int k = 0; k < 4; ++k) {
			for (int h = 0; h < 8; ++h) {
				printf("%d", gear_arr[k][h]);
			}
			printf("\n");
		}
		printf("\n");
		*/
	}

	if (gear_arr[0][0] == 1)
		ans += 1;
	if (gear_arr[1][0] == 1)
		ans += 2;
	if (gear_arr[2][0] == 1)
		ans += 4;
	if (gear_arr[3][0] == 1)
		ans += 8;
}

int main()
{
	freopen("input.txt", "r", stdin);

	for (int i = 0; i < 4; ++i) {
		gear_arr.push_back({});
		
		for (int j = 0; j < 8; ++j) {
			scanf("%c",&temp);
			gear_arr[gear_arr.size() - 1].push_back(temp - '0');
		}
		getchar();
		
	}
	
	scanf("%d",&K);
	for (int i = 0; i < K; ++i) {
		scanf("%d %d", &iidx, &idir);
		//printf("iidx : %d, idir : %d\n",iidx, idir);
		if(idir == 1)
			order_arr.push_back(order(iidx - 1, true));
		else if(idir == -1)
			order_arr.push_back(order(iidx - 1, false));
	}
	processing();

	printf("%d", ans);
	return 0;
}

