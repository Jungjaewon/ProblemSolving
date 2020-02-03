
#include <iostream>
#include <vector>
#include <functional>
#include <cstdio>
#include <algorithm>

using namespace std;

typedef pair<int, int> pii;

typedef struct cell_s {

	int value;
	bool sortFlag;
	vector<int> treeArr;
	cell_s() :value(0), treeArr({}), sortFlag(0) {}
	cell_s(int i_value, vector<int> i_treeArr, bool i_sortFlag) :value(i_value), treeArr(i_treeArr), sortFlag(i_sortFlag) {}

} cell;

vector<pii> candidate_location;
cell board[11][11];
int init[11][11];

int N, M, K;
int x, y, z;
int temp;

void spring_summer() {

	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= N; ++j) {

			auto& cellArr = board[i][j].treeArr;
			vector<int> tempArr;

			if (!board[i][j].sortFlag) {
				stable_sort(cellArr.begin(), cellArr.end());
				board[i][j].sortFlag = true;
			}
			
			int idx;
			for (idx = 0; idx < cellArr.size(); ++idx) {
				int age = cellArr[idx];
				if (age <= board[i][j].value) {
					board[i][j].value -= age;
					tempArr.push_back(age + 1);
				}
				else
					break;
			}

			for (; idx < cellArr.size(); ++idx) 
				board[i][j].value += int(cellArr[idx] / 2);
			
			cellArr.clear();
			board[i][j].treeArr = tempArr;

		}
	}
}

void fall() {

	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= N; ++j) {
			const auto &cellArr = board[i][j].treeArr;

			for (int age : cellArr) {
				if (age % 5 == 0) {
					for (const pii& path : candidate_location) {
						int dx = path.first;
						int dy = path.second;

						if (1 <= i + dx && i + dx <= N && 1 <= j + dy && j + dy <= N) {
							board[i + dx][j + dy].treeArr.push_back(1);
							if (board[i + dx][j + dy].sortFlag)
								board[i + dx][j + dy].sortFlag = false;
						}
					}
				}
			}
		}
	}

}

void winter() {
	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= N; ++j) {
			board[i][j].value += init[i][j];
		}
	}
}

int counting() {

	int ans = 0;
	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= N; ++j) {
			ans += board[i][j].treeArr.size();
		}
	}

	return ans;
}


void preprocessing() {
	candidate_location.push_back(make_pair(-1, -1));
	candidate_location.push_back(make_pair(-1, 0));

	candidate_location.push_back(make_pair(-1, 1));
	candidate_location.push_back(make_pair(0, -1));

	candidate_location.push_back(make_pair(0, 1));
	candidate_location.push_back(make_pair(1, -1));

	candidate_location.push_back(make_pair(1, 0));
	candidate_location.push_back(make_pair(1, 1));
}

void processing() {

	for (int i = 0; i < K; ++i) {

		spring_summer();
		fall();
		winter();
	}
}

int main()
{
	
	scanf("%d %d %d", &N, &M, &K);

	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= N; ++j) {
			scanf("%d", &temp);
			init[i][j] = temp;
			board[i][j].value = 5;
			board[i][j].sortFlag = false;
		}
	}

	for (int i = 0; i < M; ++i) {
		scanf("%d %d %d", &x, &y, &z);
		board[x][y].treeArr.push_back(z);
	}

	preprocessing();
	processing();
	
	printf("%d\n",counting());

	return 0;
}
