#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

using namespace std;
int arr[20][20];
int commands[1000];

int N, M;
int x, y;
int K;

/*
대략 54분 정도에 풀었다.
주사위를 파악하는데 시간이 걸리고 틀리면 안되니까 그림을 그려서 오래걸렸다.

배열을 활용해서 간단하게 굴렸을때 결과를 보이게 했다.
STL 안쓰고 구현했고
이 문제는 0~N-1의 범위를 사용했다.

*/

typedef struct dice_s {

	int upper;
	int lower;
	int left;
	int right;
	int front;
	int rear;
	dice_s(): upper(0),lower(0),left(0),right(0),front(0),rear(0) {};
	dice_s(int iupper, int ilower, int ileft, int iright, int ifront, int irear): upper(iupper),lower(ilower),left(ileft),right(iright),front(ifront),rear(irear) {};
} DICE;

void processing() {


	DICE dice;
	bool do_action;
	for (int i = 0; i < K; ++i) {
		do_action = false;
		if(commands[i] == 1){ //east
			if (!(y + 1 == M)) {
				do_action = true;
				int temp_arr[] = { dice.right, dice.lower, dice.left, dice.upper };
				dice.lower = temp_arr[0];
				dice.left = temp_arr[1];
				dice.upper = temp_arr[2];
				dice.right = temp_arr[3];

				++y;
				if (arr[x][y] == 0)
					arr[x][y] = dice.lower;
				else {
					dice.lower = arr[x][y];
					arr[x][y] = 0;
				}
			}
		}
		else if (commands[i] == 2) { //west
			if (!(y - 1 == -1)) {
				do_action = true;
				int temp_arr[] = { dice.left, dice.upper,dice.right, dice.lower};
				dice.lower = temp_arr[0];
				dice.left = temp_arr[1];
				dice.upper = temp_arr[2];
				dice.right = temp_arr[3];

				--y;
				if (arr[x][y] == 0)
					arr[x][y] = dice.lower;
				else {
					dice.lower = arr[x][y];
					arr[x][y] = 0;
				}
			}
		}
		else if (commands[i] == 3) { //north
			if (!(x - 1 == -1)) {
				do_action = true;
				int temp_arr[] = { dice.rear, dice.lower, dice.front, dice.upper};
				dice.lower = temp_arr[0];
				dice.front = temp_arr[1];
				dice.upper = temp_arr[2];
				dice.rear = temp_arr[3];

				--x;
				if (arr[x][y] == 0)
					arr[x][y] = dice.lower;
				else {
					dice.lower = arr[x][y];
					arr[x][y] = 0;
				}
			}
		}
		else if (commands[i] == 4) { //south
			if (!(x + 1 == N)) {
				do_action = true;
				int temp_arr[] = {dice.front, dice.upper, dice.rear,dice.lower};
				//temp_arr.push_back(temp_arr.front());
				//temp_arr.erase(temp_arr.begin());
				dice.lower = temp_arr[0];
				dice.front = temp_arr[1];
				dice.upper = temp_arr[2];
				dice.rear = temp_arr[3];

				++x;
				if (arr[x][y] == 0)
					arr[x][y] = dice.lower;
				else {
					dice.lower = arr[x][y];
					arr[x][y] = 0;
				}
			}
		}

		if(do_action)
			printf("%d\n", dice.upper);
	}

}

int main()
{
	freopen("input.txt","r",stdin);
	scanf("%d %d %d %d %d",&N,&M,&x,&y,&K);

	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j)
			scanf("%d",&arr[i][j]);
	}

	for (int i = 0; i < K; ++i)
		scanf("%d",&commands[i]);

	processing();

	return 0;
}
