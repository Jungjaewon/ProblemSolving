// HackerRank_MarkandToys.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

// Complete the maximumToys function below.
int maximumToys(vector<int> prices, int k) {
	stable_sort(prices.begin(), prices.end());
	int idx = 0;
	int total_price = 0;
	int cnt = 0;

	int ptotal_price;
	int pcnt;

	while (true) {

		if (total_price <= k) {

			ptotal_price = total_price;
			pcnt = cnt;

			total_price += prices[idx++];
			++cnt;

			if (total_price > k)
				return pcnt;
		}
	}

	return cnt;
}


int main()
{
    std::cout << "Hello World!\n";
}
