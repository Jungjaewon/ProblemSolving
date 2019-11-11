#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>


/*
30분 만에 풀었다.

이전번에 백준에서 풀어본 문제 같은데 안푼것으로 되어 있었다.

식계산은 스택으로 구현했고
연산자는 next_permutation으로 했다.

계산 부분은 벡터에 넣고 빼고로 해서 구현할 수 있는데 삽입/삭제 때문에 코드가 더러워질 것 같다.

넥퍼뮤 부분은 dfs로 가능할까? 선택이니 안될 것이다. 내가 생각한 dfs는 멤버를 선택하는 방법

printf("%d\n%d",ans_max,ans_min); 해서 printf 호출을 한번으로 줄였다.
*/

/*
https://suriisurii.tistory.com/11
에서는

숫자 첫번째를 두고 인덱스를 늘려가면서 
+,-,*,/ 를 전부 하나씩 다한다. dfs 방식으로 
1 (+,-,*,/)  2 (+,-,*,/)  3 (+,-,*,/)  4 

숫자 개수만큼 내려가면 값을 계산


*/
using namespace std;

int N;
int oper_plus, oper_minus, oper_times, oper_div;
int temp;
int ans_max = -10e9;
int ans_min = 10e9;

vector<int> arr;
vector<char> oper_arr;

int calculator() {

	stack<int> S;

	for (int i = arr.size() - 1; i >= 0; --i) 
		S.push(arr[i]);

	for (int i = 0; i < oper_arr.size(); ++i) {

		int first = S.top(); S.pop();
		int second = S.top(); S.pop();

		if (oper_arr[i] == '+')
			S.push(first + second);
		else if (oper_arr[i] == '-') 
			S.push(first - second);
		else if (oper_arr[i] == '*') 
			S.push(first * second);
		else if (oper_arr[i] == '/') {
			if (first < 0 && second > 0)
				S.push(-((-first) / second));
			else
				S.push(first / second);
		}
	}

	return S.top();
}

int main()
{

	freopen("input.txt","r",stdin);
	scanf("%d",&N);

	for (int i = 0; i < N; ++i) {
		scanf("%d",&temp);
		arr.push_back(temp);
	}

	scanf("%d %d %d %d",&oper_plus, &oper_minus, &oper_times, &oper_div);

	for (int i = 0; i < oper_plus; ++i)
		oper_arr.push_back('+');
	for (int i = 0; i < oper_minus; ++i)
		oper_arr.push_back('-');
	for (int i = 0; i < oper_times; ++i)
		oper_arr.push_back('*');
	for (int i = 0; i < oper_div; ++i)
		oper_arr.push_back('/');

	stable_sort(oper_arr.begin(), oper_arr.end());

	do {
		int result = calculator();
		ans_max = max(ans_max, result);
		ans_min = min(ans_min, result);
	} while (next_permutation(oper_arr.begin(), oper_arr.end()));

	printf("%d\n%d",ans_max,ans_min);

	return 0;
}
