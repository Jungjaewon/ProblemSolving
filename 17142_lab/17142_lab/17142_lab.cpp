/*
 * 17142.cpp
 *
 *  Created on: 2019. 5. 9.
 *      Author: woodc
 */

#include <iostream>
#include <algorithm>
#include <utility>
#include <vector>
#include <queue>

int map[51][51];
bool visited[51][51];
using namespace std;

int dir1[] = { 0, 1, 0, -1 };
int dir2[] = { 1, 0, -1, 0 };
int msize;
int m;

typedef pair<int, int> PAIR;

vector<PAIR> v_location;
vector<int> result;
int v_location_size;
int min_time = 10000;
bool check = true;
enum SET {
	BLANK, WALL, VIRUS
};

void reset_visited() {

	for (int i = 1; i <= msize; ++i) {
		for (int j = 1; j <= msize; ++j) {
			visited[i][j] = false;
		}
	}
}

bool spread_check(PAIR tmp) {

	int x = tmp.first;
	int y = tmp.second;

	if (x == 1 && y == 1)
		return false;
	else if (x == 1 && y == msize)
		return false;
	else if (x == msize && y == 1)
		return false;
	else if (x == msize && y == msize)
		return false;

	for (int i = 0; i < 4; ++i) {
		int new_x = x + dir1[i];
		int new_y = y + dir2[i];
		if (0 < new_x && new_x <= msize && 0 < new_y && new_y <= msize) {
			if (map[new_x][new_y] == WALL || visited[new_x][new_y] == true)
				;
			else
				return true;
		}
	}

	return false;
}

void finding(queue<PAIR>& q, PAIR tmp) {

	for (int i = 0; i < 4; ++i) {
		int new_x = tmp.first + dir1[i];
		int new_y = tmp.second + dir2[i];

		if (0 < new_x && new_x <= msize && 0 < new_y && new_y <= msize) {

			if (map[new_x][new_y] == BLANK && visited[new_x][new_y] == false) {
					q.push(make_pair(new_x, new_y));
					visited[new_x][new_y] = true;
			}
			else if (map[new_x][new_y] == VIRUS && visited[new_x][new_y] == false) {

				if (spread_check(make_pair(new_x, new_y))) {
							q.push(make_pair(new_x, new_y));
							visited[new_x][new_y] = true;
				}
			}
		}
	}
}

bool checking() {

	for (int i = 1; i <= msize; ++i) {
		for (int j = 1; j <= msize; ++j) {

			if (map[i][j] == BLANK && visited[i][j] == false) {
				return false;
			}
		}
	}
	return true;
}

void calculating(int member_bit) {

	int second = 0;
	int q_size;
	queue<PAIR> q;
	PAIR tmp;

	vector<PAIR> member_mem;
	for (int i = 0; i < v_location_size; ++i) {

		if (member_bit & 1 << i) {
			q.push(v_location[i]);
			visited[v_location[i].first][v_location[i].second] = true;
			member_mem.push_back(v_location[i]);
		}
	}

	while (!q.empty()) {

		q_size = q.size();

		for (int i = 0; i < q_size; ++i) {
			tmp = q.front();
			q.pop();
			//visited[tmp.first][tmp.second] = true;
			finding(q, tmp);
			
		}

		if (q.empty())
			;
		else {
			++second;
		}
	}

	if (checking() == false)
		;
	else {
		check = false;
		if (second < min_time)
			min_time = second;
	}
}

void dfs(int member_bit, int idx) {

	int cnt = 0;

	for (int i = 0; i < v_location_size; ++i) { // member counting

		if (member_bit & 1 << i) {
			++cnt;
		}
	}

	if (cnt == m) {
		calculating(member_bit);
		reset_visited();
		return;
	}

	for (int i = idx; i < v_location_size; ++i) {

		member_bit = member_bit | (1 << i);
		dfs(member_bit, i + 1);
		member_bit = member_bit & ~(1 << i);

	}
}

int main() {

	int temp;
	int blank_cnt = 0;

	//freopen("input.txt", "r", stdin);

	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> msize >> m;

	for (int i = 1; i <= msize; ++i) {
		for (int j = 1; j <= msize; ++j) {
			cin >> temp;
			map[i][j] = temp;
			if (temp == VIRUS)
				v_location.push_back(make_pair(i, j));
			else if (temp == BLANK)
				++blank_cnt;
			else if (temp == WALL)
				;
		}
	}

	if (blank_cnt == 0) {
		cout << "0";
		return 0;
	}

	v_location_size = v_location.size();

	int member_bit = 0;

	dfs(member_bit, 0);

	if (check)
		cout << "-1";
	else
		cout << min_time;

	return 0;
}