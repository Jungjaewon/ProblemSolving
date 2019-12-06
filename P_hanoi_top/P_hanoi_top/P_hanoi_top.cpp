#include <string>
#include <vector>
#include <iostream>

using namespace std;

void hanoi(int n, int from, int by, int to, vector<vector<int>>& answer) {

	if (n == 1)
		answer.push_back({ from,to });
	else {
		hanoi(n - 1, from, to, by, answer);
		answer.push_back({ from,to });
		hanoi(n - 1, by, from, to, answer);
	}
}

vector<vector<int>> solution(int n) {
	vector<vector<int>> answer;
	hanoi(n, 1, 2, 3, answer);
	return answer;
}

int main() {

	return 0;
}