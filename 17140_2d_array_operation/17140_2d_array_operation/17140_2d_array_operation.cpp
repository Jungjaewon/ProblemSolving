#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <unordered_map>

using namespace std;

/*
1시간 넘게 걸렸음
R operation이면 col이 줄어들고
C operation이면 row가 줄어들고 하는 것을 놓침
그리고 연산전 새로운 결과를 업데이트하기 전에 이전것을 0으로 초기화하는 것을 깜빡함.
cmp_fun 만들때 오류를 냄 // 멘붕옴 run-time error 발생시킬 수 있음.
틀렸을때 디버깅할 수 없는 문제이고 로직에서 에러를 찾아야함.
R,C 연산 후 col, row가 줄어들 때, 원래 이전에 있던 것을 제거해야한다. 새로생긴 것과 아닌것의 갭때문에 문제를 일으킨다.
*/

typedef struct item {

	int digit;
	int count;
	item() :digit(0),count(0){}
	item(int i_digit, int i_count) :digit(i_digit),count(i_count){}

} item_s;

int R, C, K;
int row = 3;
int col = 3;
int temp_row;
int temp_col;
int arr[101][101];
int ans;
int temp;
unordered_map<int, int> sort_map;
unordered_map<int, int>::iterator iter;


bool cmp_func(item_s a, item_s b) {

	if (a.count < b.count)
		return true;
	else if (a.count == b.count) {
		if (a.digit < b.digit)
			return true;
		else if (a.digit == b.digit)
			return true;
		else
			return false;
	}
	else
		return false;

}

void RC_operation(vector<int> input_arr, const int idx, bool mode) {

	// mode true R 
	// mode false C
	vector<item_s> result_arr;
	
	for (int i = 0; i < input_arr.size(); ++i) {

		if (input_arr[i] == 0)
			continue;

		if (sort_map.count(input_arr[i]) == 0 ) {
			sort_map[input_arr[i]] = 1;
		}
		else {
			sort_map[input_arr[i]] += 1;
		}
	}

	for (iter = sort_map.begin(); iter != sort_map.end(); ++iter) {
		result_arr.push_back(item_s(iter->first,iter->second));
	}


	stable_sort(result_arr.begin(), result_arr.end(), cmp_func);
	/*
	for (int i = 0; i < result_arr.size(); ++i) {
		printf("%d %d,",result_arr[i].digit, result_arr[i].count);
	}
	printf("\n");
	*/
	

	if (mode) { // R mode
		temp_col = max(temp_col, int(result_arr.size() * 2));
		int cnt = 1;
		for (int i = 1; i <= col; ++i) {
			arr[idx][i] = 0;
		}
		for (int i = 0; i < result_arr.size(); ++i) {
			
			arr[idx][cnt] = result_arr[i].digit;
			arr[idx][cnt + 1] = result_arr[i].count;
			cnt += 2;
		}
	}
	else { // C mode
		temp_row = max(temp_row, int(result_arr.size() * 2));
		int cnt = 1;
		for (int i = 1; i <= row; ++i) {
			arr[i][idx] = 0;
		}
		for (int i = 0; i < result_arr.size(); ++i) {

			arr[cnt][idx] = result_arr[i].digit;
			arr[cnt + 1][idx] = result_arr[i].count;
			cnt += 2;
		}
	}
	sort_map.clear();
}

void processing() {

	int sec = 0;

	if (arr[R][C] == K) {
		ans = sec;
		return;
	}

	while (true) {

		vector<int> input_arr;
		if (row >= col) {
			for (int i = 1; i <= row; ++i) {
				for (int j = 1; j <= col; ++j) {
					input_arr.push_back(arr[i][j]);
				}
				RC_operation(input_arr, i, true);
				input_arr.clear();
			}
			col = temp_col;
			temp_col = 0;
		}
		else {
			for (int i = 1; i <= col; ++i) {
				for (int j = 1; j <= row; ++j) {
					input_arr.push_back(arr[j][i]);
				}
				RC_operation(input_arr, i, false);
				input_arr.clear();
			}
			row = temp_row;
			temp_row = 0;
		}
		/*
		printf("row : %d, col %d\n",row,col);
		for (int i = 1; i <= row; ++i) {
			for (int j = 1; j <= col; ++j) {
				printf("%d ",arr[i][j]);
			}
			printf("\n");
		}
		printf("\n");
		*/

		++sec;
		if (arr[R][C] == K) {
			ans = sec;
			return;
		}
		else if (sec >= 99) {
			ans = -1;
			return;
		}
	}
}

int main()
{

	freopen("input.txt", "r", stdin);

	scanf("%d %d %d",&R, &C, &K);

	for (int i = 1; i <= 3; ++i) {
		for (int j = 1; j <= 3; ++j) {
			scanf("%d", &temp);
			arr[i][j] = temp;
		}
	}
	processing();
	printf("%d",ans);
	return 0;
}
