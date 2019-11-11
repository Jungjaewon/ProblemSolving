
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <cstring>


/*
1시간 30분만에 모든 기능을 구현했다.
scanf("%[^\n]",str);
에서 앞에 getchar() 했어야 했는데 까먹었다.
그리고 초기화를 잘못해서 char 배열에 문제가 있는줄 알고 string으로 바꾸었다.
string으로 출력하면 느리다. string을 char 배열로 바꾸는 것도 느리다.
char 배열로 하나씩 해도 널문자가 없어도 정삭동작한다.

처음에는 공간도형 때문에 잘 이해하지 못했다.
L R / U D / F R 는 서로 반대 방향이여서 기능을 쉽게 구현 할 수 있었다.
출력형식을 이해하지 못하겠다.


한면에서 11~ 13이 11이 13, 12가 12, 13이 11로가는 경우가 있다. 그렇기 때문에 제대로 된 파악을 하지 못했다.
이부분을 작업 해주어야 할 것같다.
*/
using namespace std;

int T;
int cnt;
char str[3100];
char up[4][4];
char bottom[4][4];
char front[4][4];
char rear[4][4];
char left_side[4][4];
char right_side[4][4];

vector<string> cmd_arr;

void init() {
	for (int i = 1; i <= 3; ++i) {
		for (int j = 1; j <= 3; ++j) {
			up[i][j] = 'w';
			bottom[i][j] = 'y';
			front[i][j] = 'r';
			rear[i][j] = 'o';
			left_side[i][j] = 'g';
			right_side[i][j] = 'b';
		}
	}
}

void print_out() {

	for (int i = 1; i <= 3; ++i) {

		for (int j = 1; j <= 3; ++j) {
			if (j == 1)
				printf("%c", bottom[i][j]);
			else
				printf("%c", up[i][j]);
		}
		printf("\n");
	}
}

void U_oper(bool mode, int idx) {

	vector<char> front_arr;
	vector<char> rear_arr;
	vector<char> left_arr;
	vector<char> right_arr;

	for (int i = 1; i <= 3; ++i) {
		front_arr.push_back(front[idx][i]);
		rear_arr.push_back(rear[idx][i]);
		left_arr.push_back(left_side[idx][i]);
		right_arr.push_back(right_side[idx][i]);
	}

	if (mode) {
		// front -> left
		for (int i = 0; i < front_arr.size(); ++i)
			left_side[idx][i + 1] = front_arr[i];
		// left -> rear
		for (int i = 0; i < left_arr.size(); ++i)
			rear[idx][i + 1] = left_arr[i];
		// rear-> right
		for (int i = 0; i < rear_arr.size(); ++i)
			right_side[idx][i + 1] = rear_arr[i];
		// right -> front
		for (int i = 0; i < right_arr.size(); ++i)
			front[idx][i + 1] = right_arr[i];
	}
	else {
		// front -> right
		for (int i = 0; i < front_arr.size(); ++i)
			right_side[idx][i + 1] = front_arr[i];
		// right -> rear
		for (int i = 0; i < right_arr.size(); ++i)
			rear[idx][i + 1] = right_arr[i];
		// rear - > left
		for (int i = 0; i < rear_arr.size(); ++i)
			left_side[idx][i + 1] = rear_arr[i];
		// left -> front
		for (int i = 0; i < left_arr.size(); ++i)
			front[idx][i + 1] = left_arr[i];
	}
}

void D_oper(bool mode) {
	if (mode) {
	}
	else {
	}
}

void F_oper(bool mode,int idx) {

	vector<char> up_arr;
	vector<char> bottom_arr;
	vector<char> left_arr;
	vector<char> right_arr;

	for (int i = 1; i <= 3; ++i) {
		up_arr.push_back(up[idx][i]);
		bottom_arr.push_back(bottom[idx][i]);
		left_arr.push_back(left_side[idx][i]);
		right_arr.push_back(right_side[idx][i]);
	}
	if (mode) {

		// up -> right
		for (int i = 0; i < up_arr.size(); ++i)
			right_side[idx][i + 1] = up_arr[i];
		// right -> bottom
		for (int i = 0; i < right_arr.size(); ++i)
			bottom[idx][i + 1] = right_arr[i];
		// bottom -> left
		for (int i = 0; i < bottom_arr.size(); ++i)
			left_side[idx][i + 1] = bottom_arr[i];
		// left -> up
		for (int i = 0; i < left_arr.size(); ++i)
			up[idx][i + 1] = left_arr[i];
	}
	else {
		// up -> left
		for (int i = 0; i < up_arr.size(); ++i)
			left_side[idx][i + 1] = up_arr[i];
		// left -> bottom
		for (int i = 0; i < left_arr.size(); ++i)
			bottom[idx][i + 1] = left_arr[i];
		// bottom -> right
		for (int i = 0; i < bottom_arr.size(); ++i)
			right_side[idx][i + 1] = bottom_arr[i];
		// right -> up
		for (int i = 0; i < right_arr.size(); ++i)
			up[idx][i + 1] = right_arr[i];
	}
}

void B_oper(bool mode) {
	if (mode) {
	}
	else {
	}
}

void L_oper(bool mode, int idx) {

	vector<char> up_arr;
	vector<char> front_arr;
	vector<char> rear_arr;
	vector<char> bottom_arr;
	for (int i = 1; i <= 3; ++i) {
		up_arr.push_back(up[i][idx]);
		front_arr.push_back(front[i][idx]);
		rear_arr.push_back(rear[i][idx]);
		bottom_arr.push_back(bottom[i][idx]);
	}
	//cout << up_arr.size() << " " << front_arr.size() << " " << rear_arr.size() << bottom_arr.size() << "\n";

	if (mode) {
		// up - > rear
		for (int i = 0; i < up_arr.size(); ++i)
			rear[i + 1][idx] = up_arr[i];
		// rear -> bottom
		for (int i = 0; i < rear_arr.size(); ++i)
			bottom[i + 1][idx] = rear_arr[i];
		// bottom -> front
		for (int i = 0; i < bottom_arr.size(); ++i)
			front[i + 1][idx] = bottom_arr[i];
		// front -> up
		for (int i = 0; i < front_arr.size(); ++i)
			up[i + 1][idx] = front_arr[i];
	}
	else {
		// up -> front
		for (int i = 0; i < up_arr.size(); ++i)
			front[i + 1][idx] = up_arr[i];
		// front - > bottom
		for (int i = 0; i < front_arr.size(); ++i)
			bottom[i + 1][idx] = front_arr[i];
		// bottom -> rear
		for (int i = 0; i < bottom_arr.size(); ++i)
			rear[i + 1][idx] = bottom_arr[i];
		// rear -> up
		for (int i = 0; i < rear_arr.size(); ++i)
			up[i + 1][idx] = rear_arr[i];
	}
}

void R_oper(bool mode) {


	if (mode) {
	}
	else {
	}
}

void processing() {

	for (int i = 0; i < cmd_arr.size(); ++i) {
		string cmd = cmd_arr[i];
		bool mode;
		if (cmd[1] == '+')
			mode = true;
		else
			mode = false;

		if (cmd[0] == 'U') {
			U_oper(mode, 1);
		}
		else if (cmd[0] == 'D') {
			U_oper(!mode, 3);
		}
		else if (cmd[0] == 'F') {
			F_oper(mode, 3);
		}
		else if (cmd[0] == 'B') {
			F_oper(!mode, 1);
		}
		else if (cmd[0] == 'L') {
			L_oper(mode,1);
		}
		else if (cmd[0] == 'R') {
			L_oper(!mode,3);
		}

	}
}

int main()
{

	freopen("input.txt","r",stdin);
	init();
	scanf("%d",&T);

	for (int t = 0; t < T; ++t) {
		scanf("%d",&cnt);
		// getting command
		getchar();
		scanf("%[^\n]",str);
		char* temp = NULL;
		temp = strtok(str," ");

		while (temp != NULL) {
			cmd_arr.push_back(string(temp));
			temp = strtok(NULL," ");
		}

		//procesing
		processing();

		//print
		print_out();

		//clear
		init();
		cmd_arr.clear();
	}

	return 0;
}
