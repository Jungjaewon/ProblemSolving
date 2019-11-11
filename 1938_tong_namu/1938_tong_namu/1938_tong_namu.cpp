#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>
#include <cstring>

using namespace std;


/*
1:50분쯤 들여서 동작하게 한것 같다. 허나 메모리 초과가 떴다.
배열을 계속복사해서 그렇다.

char형 입력을 받는데 getchar를 깜빡했고
struct에 char형 배열이 있을때 그냥 for문으로 복사를 하는게 빠르다. strcpy를 썼는데 문제가 발생해서 쓰레기 값이 들어갔다.

배열에서 어떤 내용을 밀 때 다지우고 새로 다시 쓰는 것이 좋다.
하나씩 하면 덮어씌어지면서 제대로 된 결과가 나오지 않는다.

구현 난이도는 높지 않다.


큐에 들어가는 visited check의 순서를 바꾸었다 그러니 틀렸다. 아오
큐에는 넣을때 visited true를 해야한다.
*/

typedef pair<int, int> PAIR;

int N;
char temp;
char tree_map[51][51];
char target_map[51][51];
bool visited1[51][51];
bool visited2[51][51];
bool visited3[51][51];
int dx[] = { -1,1,0,0 };
int dy[] = { 0,0,-1,1 };
int ans = 10e5;

typedef struct State_s {

	char state[51][51];
	int cnt;
	State_s() :cnt(0) {
		for (int i = 1; i <= N; ++i) {
			for (int j = 1; j <= N; ++j) {
				state[i][j] = ' ';
			}
		}
	}
	State_s(char istate[51][51], int icnt) : cnt(icnt) {
		for (int i = 1; i <= N; ++i) {
			for (int j = 1; j <= N; ++j) {
				state[i][j] = istate[i][j];
			}
		}
	}

} STATE;

bool checking(char input_arr[][51]) {

	int cnt = 0;
	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= N; ++j) {
			if (input_arr[i][j] == 'B' && target_map[i][j] == 'E') {
				++cnt;
			}
		}
	}

	if (cnt == 3)
		return true;
	else
		return false;
}

void copy_map(char dst_arr[][51], char src_arr[][51]) {
	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= N; ++j) {
			dst_arr[i][j] = src_arr[i][j];
		}
	}
}

vector<PAIR> find_B(char input_arr[][51]) {

	vector<PAIR> result;

	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= N; ++j) {
			if (input_arr[i][j] == 'B')
				result.push_back(make_pair(i, j));
		}
	}

	return result;
}

bool check_around(char input_arr[][51], const vector<PAIR> B_arr, int idx) {

	for (int i = 0; i < B_arr.size(); ++i) {
		int nx = B_arr[i].first + dx[idx];
		int ny = B_arr[i].second + dy[idx];
		if (!(1 <= nx && nx <= N && 1 <= ny && ny <= N))
			return false;
		else if (1 <= nx && nx <= N && 1 <= ny && ny <= N && input_arr[nx][ny] == '1')
			return false;
	}

	return true;
}

bool do_rotation(char input_arr[][51], const vector<PAIR> B_arr) {

	if (B_arr[0].first + 1 == B_arr[1].first) { // vertical
		// rotation check
		if (check_around(input_arr, B_arr, 2) && check_around(input_arr, B_arr, 3)) {
			int middle_x = B_arr[1].first;
			int middle_y = B_arr[1].second;
			input_arr[middle_x + 1][middle_y] = '0';
			input_arr[middle_x - 1][middle_y] = '0';
			input_arr[middle_x][middle_y + 1] = 'B';
			input_arr[middle_x][middle_y - 1] = 'B';
		}
		else
			return false;
	}
	else { //  horizontal
		// rotation check
		if (check_around(input_arr, B_arr, 0) && check_around(input_arr, B_arr, 1)) {
			int middle_x = B_arr[1].first;
			int middle_y = B_arr[1].second;
			input_arr[middle_x][middle_y + 1] = '0';
			input_arr[middle_x][middle_y - 1] = '0';
			input_arr[middle_x + 1][middle_y] = 'B';
			input_arr[middle_x - 1][middle_y] = 'B';
		}
		else
			return false;
	}

	return true;
}

bool operation(char input_arr[][51], int cmd) {

	vector<PAIR> B_arr = find_B(input_arr);
	if (cmd == 4) {
		if (do_rotation(input_arr, B_arr))
			return true;
		else
			return false;
	}
	else if (0 <= cmd && cmd <= 3) {

		// checking command can be operated.
		for (int i = 0; i < B_arr.size(); ++i) {
			int nx = B_arr[i].first + dx[cmd];
			int ny = B_arr[i].second + dy[cmd];
			if (!(1 <= nx && nx <= N && 1 <= ny && ny <= N))
				return false;
			else if (1 <= nx && nx <= N && 1 <= ny && ny <= N && input_arr[nx][ny] == '1')
					return false;
		}

		for (int i = B_arr.size() - 1; i > -1; --i) {
			int x = B_arr[i].first;
			int y = B_arr[i].second;
			input_arr[x][y] = '0';

		}
		for (int i = B_arr.size() - 1; i > -1; --i) {
			int nx = B_arr[i].first + dx[cmd];
			int ny = B_arr[i].second + dy[cmd];
			input_arr[nx][ny] = 'B';
		}

		return true;
	}
}

void bfs() {


	queue<STATE> Q;
	Q.push(STATE(tree_map, 0));
	while (!Q.empty()) {

		STATE temp = Q.front(); Q.pop();

		/*
		printf("temp.cnt : %d\n", temp.cnt);
		for (int i = 1; i <= N; ++i) {
			for (int j = 1; j <= N; ++j) {
				printf("%c",temp.state[i][j]);
			}
			printf("\n");
		}
		*/
		
		if (checking(temp.state)) {
			ans = min(ans, temp.cnt);
			break;
		}

		for (int cmd = 0; cmd < 5; ++cmd) {
			char temp_arr[51][51];
			copy_map(temp_arr, temp.state);
			if (operation(temp_arr, cmd)) {
				vector<PAIR> t_result = find_B(temp_arr);
				if (visited1[t_result[0].first][t_result[0].second] && visited2[t_result[1].first][t_result[1].second] && visited3[t_result[2].first][t_result[2].second])
					;
				else {
					visited1[t_result[0].first][t_result[0].second] = true;
					visited2[t_result[1].first][t_result[1].second] = true;
					visited3[t_result[2].first][t_result[2].second] = true;
					Q.push({ temp_arr, temp.cnt + 1 });
				}
			}
				
		}
	}
}

int main()
{

	freopen("input.txt","r",stdin);
	scanf("%d", &N);
	getchar();
	//input
	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= N; ++j) {
			scanf("%c", &temp);
			tree_map[i][j] = temp;
			target_map[i][j] = '0';
			if (temp == 'E') {
				target_map[i][j] = temp;
				tree_map[i][j] = '0';
			}
		}
		getchar();
	}

	//processing
	bfs();

	//print
	if (ans == 10e5)
		printf("0");
	else
		printf("%d", ans);

	return 0;
}

