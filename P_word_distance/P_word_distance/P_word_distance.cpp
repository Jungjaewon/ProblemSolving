#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

bool visited[50];
int ans;

/*
처음에는 단순히 루프를 써서 구하려고 했는데
최소를 구할 수 있을지 말지가 결정이 안된다. 그렇기 때문에

distance 함수를 구하고 visited[i]가 false인 것들에 대해서 dfs를 실행했다.

begin이 taget과 같으면 값을 업데이트 하고 종료
브루트포스 방식이다.

find에 대해서 벡터 자체에 함수가 있는줄 알았는데 없었다. 있는지 없는지 검증을 할 때는 end()를 사용하여야한다.

이 문제도 어느 것이 최소 인지 수학적으로 계산을 할 수가 없다 따라서 다 해봐야한다.

예전에 어떻게 풀었는지 생각하다가 생각안나서 포문으로 접근 했다 근데 최소에 대해서 도저히 방법이 없다.
*/
int cal_distance(const string& a, const string& b) {
	int cnt = 0;
	for (int i = 0; i < a.size(); ++i) {
		if (a[i] != b[i])
			++cnt;
	}
	return cnt;
}

void dfs(string begin, const string& target, const vector<string>& words, int depth) {

	if (begin == target) {
		ans = min(ans, depth);
		return;
	}

	for (int i = 0; i < words.size(); ++i) {
		if (!visited[i] && cal_distance(begin, words[i]) == 1) {
			visited[i] = true;
			dfs(words[i], target, words, depth + 1);
			visited[i] = false;
		}
	}

}
int solution(string begin, string target, vector<string> words) {
	if (find(words.begin(), words.end(), target) == words.end())
		return 0;

	for (int i = 0; i < words.size(); ++i)
		visited[i] = false;
	ans = 10e5;
	dfs(begin, target, words, 0);
	return ans;
}

int main()
{
    std::cout << "Hello World!\n";
}
