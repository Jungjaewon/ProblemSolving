
#include <iostream>
#include <cstdio>
#include <vector>
#include <deque>
#include <algorithm>

// Pass!!!
using namespace std;

int T;
int N;
int W;
vector<int> boxes;

int find_max(vector<int> arr) {

	if (arr.size() == 0)
		return 0;

	int max_v = arr[0];
	for (int i = 1; i < arr.size(); ++i) {
		max_v = max(max_v, arr[i]);
	}
	return max_v;
}

bool check(vector<int> arr) {

	int max_value = find_max(arr);
	int size_arr = arr.size();

	if (max_value * size_arr >= 50)
		return true;
	else
		return false;
}

bool check(int value) {

	if (value >= 50)
		return true;
	else
		return false;
}

int processing() {
	
	int cnt = 0;

	stable_sort(boxes.begin(), boxes.end());
	vector<int> temp_box;
	bool flag = false;
	while (boxes.size() != 0) 
	
	{
		if(!flag){ // extract from back-side / flag is false
			temp_box.push_back(boxes.back());
			boxes.pop_back();
			flag = true;
		}
		else { // extract from front-side /  flag is true
			temp_box.push_back(boxes[0]);
			boxes.erase(boxes.begin());
			flag = false;
		}

		if (check(boxes) == true && check(temp_box) == true) {
			++cnt;
			flag = false;
		}
		else if (check(boxes) == true && check(temp_box) == false) {
			flag = true;
			continue;
		}
		else if (check(boxes) == false && check(temp_box) == true) {
			flag = true;

			if (boxes.size() == 0)
				++cnt;
			continue;
		}
		else if (check(boxes) == false && check(temp_box) == false) {
			flag = true;
			continue;
		}

		temp_box.clear(); // one job done
	}

	return cnt;

}

int main()
{

	scanf("%d",&T);

	for (int i = 0; i < T; ++i)
	{

		scanf("%d", &N);

		for (int j = 0; j < N; ++j) {
			
			scanf("%d",&W);
			boxes.push_back(W);
		}

		printf("#%d %d\n", i + 1, processing());
		boxes.clear();
	}

}


