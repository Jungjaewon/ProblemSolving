
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <deque>

using namespace std;

int T;
int N;
int A;
int B;
int Temp;
int last_hour;
vector<int> post_arr;

void reading( queue<int>& Q, vector<int>& result, int cur_hour) {
	int read_size = ceil(double(Q.size() / 2.0));
	for (int i = 0; i < read_size; ++i) {
		Q.pop();
		result.push_back(cur_hour);
	}
}

vector<int> processing() {

	vector<int> result;
	int the_oldest_one = -1;
	queue<int> Q;

	for (int cur_hour = 1; cur_hour < last_hour; ++cur_hour) {

		if (post_arr.size() >= 1 && cur_hour == post_arr.front()) { // intert post to the box.
			Q.push(post_arr.front());
			post_arr.erase(post_arr.begin());
			if (Q.size() == 1)
				the_oldest_one = Q.front();
		}


		if (the_oldest_one != -1 && (cur_hour - the_oldest_one) == B) {
			reading(Q, result, cur_hour);
			the_oldest_one = Q.front();
		}
		else if (Q.size() == A) {
			reading(Q, result, cur_hour);
			the_oldest_one = Q.front();
		}

	}

	return result;
}

int main()
{

	scanf("%d",&T);

	for (int i = 0; i < T; ++i) {

		scanf("%d %d %d",&N,&A,&B);

		for (int j = 0; j < N; ++j) {
			scanf("%d",&Temp);
			post_arr.push_back(Temp);
		}

		printf("#%d", i + 1);
		//stable_sort(post_arr.begin(),post_arr.end());
		last_hour = 100 * post_arr.back();
		auto result_arr = processing();
		for (const int item : result_arr)
			printf(" %d", item);
		printf("\n");

		// Variable clear!!
		post_arr.clear();
	}
	return 0;
}
