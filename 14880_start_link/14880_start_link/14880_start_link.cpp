#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <cmath>


/*

20분만에 풀었다.

처음에는 몰랐는데 문제를 보니 이전에 풀었던 문제라고 직감했다.

dfs로 멤버를 고르고 N/2일때 작업을 시작했다.

vector를 쓰지 않고도 풀수있겠다. N/2로 정해져 있기 때문에 전역변수로 선언해서 덮어씌우면 될것 같다.

i == j continue를 하지 않았다. 왜냐 arr[i][i] 는 0이기 때문이다.

*/
using namespace std;

int arr[21][21];
int N;
int ans = 10e9;

int min_value(int a, int b) {
	if (a > b)
		return b;
	else
		return a;
}

int calculate_gap(const vector<int>& team1, const vector<int>& team2) {

	int sum1 = 0;
	int sum2 = 0;

	for (int i = 0; i < team1.size(); ++i)
		sum1 += team1[i];
	for (int i = 0; i < team2.size(); ++i)
		sum2 += team2[i];

	return abs(sum1 - sum2);
}

void dfs(int idx, int memberbit) {

	int cnt = 0;
	for (int i = 0; i < N; ++i) {
		if (memberbit & 1 << i)
			++cnt;
	}

	if (cnt == (N / 2)) {
		vector<int> team1;
		vector<int> team2;
		for (int i = 0; i < N; ++i) {
			if (memberbit & 1 << i)
				team1.push_back(i + 1);
			else
				team2.push_back(i + 1);
		}
		int sum1 = 0;
		int sum2 = 0;
		for (int i = 0; i < team1.size(); ++i) {
			for (int j = 0; j < team1.size(); ++j) {
				sum1 += arr[team1[i]][team1[j]];
			}
		}
		for (int i = 0; i < team2.size(); ++i) {
			for (int j = 0; j < team2.size(); ++j) {
				sum2 += arr[team2[i]][team2[j]];
			}
		}

		ans = min_value(ans, abs(sum1 - sum2));

	}
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
	scanf("%d",&N);

	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= N; ++j) {
			scanf("%d",&arr[i][j]);
		}
	}

	dfs(0, 0);

	printf("%d",ans);
	return 0;
}

