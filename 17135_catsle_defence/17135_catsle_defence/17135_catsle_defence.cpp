#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <set>

/*
1시간 10분 안에 문제를 다 풀었다.
이름만 보고 어려운 문제인줄 알았는데 쉽게 잘 풀었다.

스트럭쳐에idx를 넣어서 해결한 것은 좋은 해결책인것 같다.

vector에서 insert, erase를 하면 idx가 바뀐다 그래서 
배열에서 삭제할때는 삭제할것의 정보를 바꾼다.
한번바꾼것을 또 바꾸지 않게 if문을 추가할 수 있다.
그리고 나중에 필터링 한다.

배열을 정렬할때는 개수가 0개인지 아닌지 확인하여야한다.
접근하면 바로 터진다.
*/
using namespace std;

typedef pair<int, int> PAIR;

typedef struct target_s {
	PAIR loc;
	int idx;
	int dist;

	target_s() : loc({0,0}),dist(0), idx(0){}
	target_s(PAIR iloc, int idist, int iidx) : loc(iloc),dist(idist), idx(iidx) {}
} target;

typedef vector<target> TARGET_ARR;
int N, M, D;
int arr[16][16];
int ans = -987654321;
vector<PAIR> enemy_arr;

int dist(PAIR a, PAIR b) {
	return abs(a.first - b.first) + abs(a.second - b.second);
}

vector<PAIR> move_down(vector<PAIR> enemy) {
	vector<PAIR> result;
	for (int i = 0; i < enemy.size(); ++i) {
		int x = enemy[i].first;
		int y = enemy[i].second;
		if (x + 1 <= N)
			result.push_back(make_pair(x + 1, y));
	}
	return result;
}

bool cmp(target a, target b) {

	PAIR a_pair = a.loc;
	PAIR b_pair = b.loc;
	int adist = a.dist;
	int bdist = b.dist;

	if (adist < bdist)
		return true;
	else if (adist == bdist) {
		if (a_pair.second < b_pair.second)
			return true;
		else
			return false;
	}
	else
		return false;

}

vector<PAIR> hunting(vector<PAIR>& achor, vector<PAIR> enemy, int& result) {

	vector<TARGET_ARR> available;
	vector<PAIR> result_arr;
	for (int i = 0; i < achor.size(); ++i) {
		available.push_back({});
		for (int j = 0; j < enemy.size(); ++j) {

			int rdist = dist(achor[i], enemy[j]);
			if (rdist <= D)
				available[available.size() - 1].push_back(target({enemy[j].first, enemy[j].second }, rdist, j));
		}
	}

	for (int i = 0; i < available.size(); ++i) {

		if (available[i].size() != 0) {
			stable_sort(available[i].begin(), available[i].end(), cmp);
			target t = available[i][0];

			if (!(enemy[t.idx].first == -1 && enemy[t.idx].second == -1)) {
				enemy[t.idx].first = -1;
				enemy[t.idx].second = -1;
				result += 1;
			}
		}
		
	}

	for (int i = 0; i < enemy.size(); ++i) {
		if (enemy[i].first == -1 && enemy[i].second == -1)
			;
		else
			result_arr.push_back(enemy[i]);
	}

	return result_arr;
}

void do_game(int memberbit) {

	vector<PAIR> acher_arr;
	vector<PAIR> enemy_copy = enemy_arr;

	int result = 0;

	for (int i = 0; i < M; ++i) {
		if (memberbit & (1 << i)) {
			acher_arr.push_back(make_pair(N + 1, i + 1));
		}
	}
	
	while (enemy_copy.size() != 0) {
		enemy_copy = hunting(acher_arr, enemy_copy, result);
		enemy_copy = move_down(enemy_copy);
	}

	ans = max(ans,result);
}

void dfs(int idx, int memberbit) {

	int cnt = 0;
	for (int i = 0; i < M; ++i) {
		if (memberbit & (1 << i))
			++cnt;
	}

	if (cnt == 3) {
		do_game(memberbit);
		return;
	}

	for (int i = idx; i < M; ++i) {
		memberbit = memberbit | 1 << i;
		dfs(i + 1, memberbit);
		memberbit = memberbit & ~(1 << i);
	}

}

int main()
{

	freopen("input.txt","r",stdin);
	scanf("%d %d %d",&N,&M,&D);

	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= M; ++j) {
			scanf("%d",&arr[i][j]);
			if (arr[i][j] == 1)
				enemy_arr.push_back(make_pair(i,j));
		}
	}
	//printf("enemy_arr.size() : %d\n", enemy_arr.size());
	dfs(0,0);

	printf("%d",ans);
	return 0;
}
