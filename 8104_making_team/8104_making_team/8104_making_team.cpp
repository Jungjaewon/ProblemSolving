

#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;
int T;
int N, K;


int vector_sum(vector<int> arr) {
	int sum = 0;

	for (int i = 0; i < arr.size(); ++i) {
		//printf("%d ",arr[i]);
		sum += arr[i];
	}
	return sum;
}

vector<int> get_mat(vector<vector<int>>& matrix) {

	bool flag = true;
	vector<int> temp;

	for (int i = 0; i < N; ++i) {

		if (flag) {

			temp.push_back(matrix[i].front());
			matrix[i].erase(matrix[i].begin());
		}
		else {
			temp.push_back(matrix[i].back());
			//matrix[i].erase(matrix[i].end());
			matrix[i].pop_back();
		}

		flag = !flag;
	}

	return temp;
}

void processing() {

	int total = N * K;
	int n_loc = 0;
	bool flag = true;
	vector<vector<int>> matrix(N);

	for (int i = 1; i <= total; ++i) {

		matrix[n_loc].push_back(i);
		//printf("%d, %d\n", n_loc, i);
		if (i % (K) == 0)
			++n_loc;
	}

	for (int i = 0; i < K; ++i) {

		vector<int> temp = get_mat(matrix);
		printf("%d ", vector_sum(temp));
	}
}

int main()
{
   
	//processing();
	scanf("%d", &T);

	for (int i = 0; i < T; ++i) {
	
		scanf("%d %d",&N,&K);

		printf("#%d ",T);
		processing();
		printf("\n");
	}
}
