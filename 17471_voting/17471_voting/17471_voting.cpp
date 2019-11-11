#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>
using namespace std;

int population[11];
int adjmap[11][11];
bool visited[11];
int N;
int temp;
int temp1;
bool impossible = true;
int MIN = 10e5; 

int calculating_gap(vector<int> arr1, vector<int> arr2) {

	int sum1 = 0;
	int sum2 = 0;

	for (int i = 0; i < arr1.size(); ++i)
		sum1 += population[arr1[i]];

	for (int i = 0; i < arr2.size(); ++i)
		sum2 += population[arr2[i]];

	return abs(sum1 - sum2);
}

bool check_bfs(const vector<int>& team) {

	for (int i = 0; i < team.size(); ++i) {
		visited[team[i]] = false;
	}
	queue<int> Q;
	Q.push(team[0]);
	visited[team[0]] = true;

	while (!Q.empty()) {

		int curr_node = Q.front();
		Q.pop();
	
		for (int i = 0; i < team.size(); ++i) {
			if (visited[team[i]] || adjmap[curr_node][team[i]] == 0)
				continue;

			Q.push(team[i]);
			visited[team[i]] = true;
		}
	}

	for (int i = 0; i < team.size(); ++i)
		if (!visited[team[i]])
			return false;

	return true;
}

void processing(int memberbit) {

	vector<int> team1;
	vector<int> team2;
	for (int i = 0; i < N; ++i) {
		if (memberbit & 1 << i)
			team1.push_back(i + 1);
		else
			team2.push_back(i + 1);
	}

	if (check_bfs(team1) && check_bfs(team2)) {
		//printf("calculating_gap(team1, team2) : %d\n", calculating_gap(team1, team2));
		MIN = min(MIN, calculating_gap(team1, team2));
		impossible = false;
	}
	else
		;
}

void dfs(int idx, int memberbit) {

	int cnt = 0;

	for (int i = 0; i < N; ++i) {
		if (memberbit & 1 << i)
			++cnt;
	}

	if (0 < cnt && cnt < N) {

		processing(memberbit);
		for (int i = idx; i < N; ++i) {
			memberbit = memberbit | 1 << i;
			dfs(i + 1, memberbit);
			memberbit = memberbit & ~(1 << i);
		}
	}
	else if (cnt == N)
		;
	else {
		for (int i = idx; i < N; ++i) {
			memberbit = memberbit | 1 << i;
			dfs(i + 1, memberbit);
			memberbit = memberbit & ~(1 << i);
		}
	}
}

int main()
{

	freopen("input.txt","r",stdin);
	scanf("%d", &N);

	for (int i = 1; i <= N; ++i)
		scanf("%d", &population[i]);

	for (int i = 1; i <= N; ++i) {

		scanf("%d", &temp);
		adjmap[i][i] = 1;
		for (int j = 0; j < temp; ++j) {
			scanf("%d",&temp1);
			adjmap[i][temp1] = 1;
		}
	}

	/*
	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= N; ++j)
			printf("%d ",adjmap[i][j]);
		printf("\n");
	}
	*/

	dfs(0,0);

	if (impossible)
		printf("%d",-1);
	else
		printf("%d",MIN);

	return 0;
}

