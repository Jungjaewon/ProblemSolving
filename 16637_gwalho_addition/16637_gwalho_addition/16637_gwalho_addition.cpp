
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stack>
#include <vector>
#include <algorithm>
#include <cstring>
#include <set>

/*
한시간안에 문제에서 요구하는 스택 계산기만 만들었음.
중간에 (를 만나면 내부적으로 돌아야하는데 그때 새로운 변수 대입을 안해서 삽질을 함.

적합한 식을 만들고 수를 결과를 계산하고 최대치를 갱신하면 된다.
적합한 식을 만드는 것이 관건이다.


vector insert를 하는 순간 모든 원소의 idx가 달라진다. 그래서 그러한 것을 고려해야한다.
*/

/*
숫자 인덱스를 파악하고 쌍을 만들어주고
선택하는 방식을 택했다. 인접하는 것을 택하면 안돼서 idx를 택하면 idx + 2를 해주었다.
그리고 idx를 택하지 않고 idx+1를 해주었다.
배열에 삽입하는것보다 새로이 만드는 것이 훨씬 간단하고 좋다.
*/
/*
int ans = -2e-32;
위에것 때문에 틀렸다.;;;;; 이거 때문에 19-10-05를 날린 것이다.;;
코드에는 문제가 없었다...;;;
아무리 봐도 맞을때는 코드바이 코드로 점검을 하자... 전체코드를... 
*/
using namespace std;

typedef struct p_pair_s {
	int start;
	int end;
	p_pair_s(): start(0),end(0) {}
	p_pair_s(int istart, int iend): start(istart),end(iend) {}

} p_pair;

int N;
//int ans = -987654321987654321;
 int ans = -2e32;
char expression[21];

int calculate(char t[300]) {

	stack<char> S;
	stack<int> digit;
	stack<char> exp;
	for (int i = strlen(t) - 1; i >= 0; --i) {
		if (t[i] != '\0') {
			S.push(t[i]);
			//printf("t[i] : %c\n", t[i]);
		}
	}

	while (!S.empty()) {
		char out = S.top(); S.pop();
		//printf("out : %c\n",out);
		if (out == '(') {
			while (S.top() != ')') {
				char inner = S.top(); S.pop();
				if ('0' <= inner && inner <= '9') {
					digit.push(inner - '0');
				}
				else if ('+' == inner || '-' == inner || '*' == inner) {
					exp.push(inner);
				}
			}
		}
		else if (out == ')') {
			;
		}
		else if ('0' <= out && out <= '9') {
			digit.push((out - '0'));
		}
		else if ('+' == out || '-' == out || '*' == out) {
			exp.push(out);
		}

		while ((digit.size() > exp.size()) && digit.size() > 1 && exp.size() >= 1) {
			int one = digit.top(); digit.pop();
			int two = digit.top(); digit.pop();
			char ex = exp.top(); exp.pop();
			//printf("%d %c %d\n",one,ex,two);
			// 순서!!
			if (ex == '+') {
				//printf("two : %d, exp +, one : %d\n", two, one);
				digit.push((two + one));
			}
			else if (ex == '-') {
				//printf("two : %d, exp -, one : %d\n", two, one);
				digit.push((two - one));
			}
				
			else if (ex == '*') {
				//printf("two : %d, exp *, one : %d\n",two,one);
				digit.push((two * one));
			}
				
		}
		
	}
	//printf("digit.size() : %d\n",digit.size());
	//printf("exp.size() : %d\n",exp.size());
	return digit.top();
}


void experssion_gen(int idx, vector<p_pair> member_pair,const vector<p_pair>& pair_arr) {

	if (idx >= pair_arr.size()) {

		vector<char> result;
		set<int> start_s;
		set<int> end_s;
		char cal_result[300];

		//for (const p_pair t : member_pair)
		//	printf("s : %d e : %d\n", t.start, t.end);

		for (int i = 0; i < member_pair.size(); ++i){
			start_s.insert(member_pair[i].start);
			end_s.insert(member_pair[i].end);
		}
		for (int i = 0; i < N; ++i) {
			if (start_s.find(i) != start_s.end()) {
				result.push_back('(');
				result.push_back(expression[i]);
			}
			else if (end_s.find(i) != end_s.end()) {
				result.push_back(expression[i]);
				result.push_back(')');
			}
			else if(expression[i] != '\0')
				result.push_back(expression[i]);
		}
		//for (const char t : result)
		//	printf("%c",t);
		//printf("\n");
		for (int i = 0; i < result.size(); ++i)
			cal_result[i] = result[i];
		cal_result[result.size()] = '\0';
		//printf("strlen(cal_result) : %d\n", strlen(cal_result));
		//for (int i = 0; i < strlen(cal_result); ++i) 
		//	printf("%c",cal_result[i]);
		//printf(" %ld\n", calculate(cal_result));
		//printf("\n");
		ans = max(ans,calculate(cal_result));
		//printf("\n");
		return;
	}

	//for (int i = idx; i < pair_arr.size(); ++i) {

	member_pair.push_back(pair_arr[idx]);
	experssion_gen(idx + 2, member_pair, pair_arr);
	member_pair.pop_back();
	experssion_gen(idx + 1, member_pair, pair_arr);
	//}

}

void processing() {

	vector<int> idx_arr;
	vector<p_pair> pair_arr;

	for (int i = 0; i < N; ++i) {
		if ('0' <= expression[i] && expression[i] <= '9') {
			idx_arr.push_back(i);
		}
	}
	for (int i = 0; i < idx_arr.size() - 1; ++i) {
		pair_arr.push_back(p_pair(idx_arr[i],idx_arr[i + 1]));
	}
	//for (const p_pair t : pair_arr)
	//	printf("start :  %d end : %d\n", t.start, t.end);

	experssion_gen(0, {}, pair_arr);

}

int main()
{

	/*
	char input[20] = "3+8*7-9*2";
	N = strlen(input);
	printf("%d", calculate(input));
	*/

	freopen("input.txt","r",stdin);
	scanf("%d", &N);
	getchar();


	for (int i = 0; i < N; ++i) {
		scanf("%c", &expression[i]);
	}
	if (N == 1) {
		printf("%c", expression[0]);
	}
	else {
		processing();
		printf("%d",ans);
	}
	
	return 0;
}
