#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;


/*
한시간안에 못 풀었음
코드간소화를 하지 않음

*/
int N, L;
int temp;
int arr[101][101];
bool visited[101][101];
int ans = 0;

bool check_all_equal(vector<int> digit_arr) {

	int temp_int = digit_arr[0];

	for (int i = 1; i < digit_arr.size(); ++i) {
		if (temp_int != digit_arr[i])
			return false;
	}

	return true;
}

bool check(vector<int> digit_arr, vector<bool> bool_arr) {
	
	
	for (int position = 1; position <= N - L; ) {
	
		if (digit_arr[position] - 1 == digit_arr[position + 1]) {

			int index = position + 2;
			bool flag = false;
			int cnt = 0;
			while (cnt < L - 1) {

				if (digit_arr[position + 1] != digit_arr[index] || visited) {
					flag = false;
					break;
				}
			}
			if (flag) {
			}
			else {
			}
		}
		else if (digit_arr[position] == digit_arr[position + 1] - 1) {

			int index = position + 2;
		}
	}

	return true;

}

void processing() {

	set<int> col_history;
	set<int> row_history;

	// find all equal road
	for (int i = 1; i <= N; ++i) {
		vector<int> row_temp;
		vector<int> col_temp;

		for (int j = 1; j <= N; ++j) {
			row_temp.push_back(arr[i][j]);
		}
		for (int j = 1; j <= N; ++j) {
			col_temp.push_back(arr[j][i]);
		}

		if (check_all_equal(row_temp)) {
			for (int j = 1; j <= N; ++j) {
				visited[i][j] = true;
			}
			++ans;
			row_history.insert(i);
		}

		if (check_all_equal(col_temp)) {
			for (int j = 1; j <= N; ++j) {
				visited[j][i] = true;
			}
			++ans;
			col_history.insert(i);
		}
	}

	for (int i = 1; i <= N; ++i) {

		if (row_history.find(i) == row_history.end()) {
			vector<int> row_temp;
			for (int j = 1; j <= N; ++j) {
				row_temp.push_back(arr[i][j]);
			}

			vector<int> row_temp_reverse(row_temp.rbegin(), row_temp.rend());
			check(row_temp_reverse);

			if (check(row_temp)) {
				++ans;
			}
			
		}

		if (col_history.find(i) == col_history.end()) {
			vector<int> col_temp;


			for (int j = 1; j <= N; ++j) {
				col_temp.push_back(arr[i][j]);
			}
			vector<int> col_temp_reverse(col_temp.rbegin(), col_temp.rend());
			check(col_temp_reverse);

			if (check(col_temp)) {
				++ans;
			}
		}
	}
}

int main()
{

	freopen("input.txt","r",stdin);

	scanf("%d %d",&N,&L);

	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= N; ++j) {
			scanf("%d",&temp);
			arr[i][j] = temp;
		}
	}

	processing();

	printf("%d",ans);
	return 0;
}


