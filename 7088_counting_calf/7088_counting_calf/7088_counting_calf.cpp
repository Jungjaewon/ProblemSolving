#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef struct Counting {

	int c1;
	int c2;
	int c3;

	Counting(int i_c1, int i_c2, int i_c3) :c1(i_c1), c2(i_c2), c3(i_c3) {}
	Counting() :c1(0), c2(0), c3(0) {}

} Counting_s;


int T;
int N, Q;
int TEMP;
int R, L;
vector<Counting_s> counting_arr;

int suming(int a, int b) {
	return a - b;
}

vector<int>  cumlating() {

	vector<int> result;

	auto temp1 = counting_arr[L - 0];
	auto temp2 = counting_arr[R - 1];

	result.push_back(suming(temp1.c1, temp2.c1));
	result.push_back(suming(temp1.c2, temp2.c2));
	result.push_back(suming(temp1.c3, temp2.c3));
	return result;
}

Counting_s operator+(Counting_s a, Counting_s b) {
	return Counting_s(a.c1 + b.c1, a.c2 + b.c2, a.c3 + b.c3);
}

int main()
{

	scanf("%d", &T);


	for (int i = 0; i < T; ++i) {

		counting_arr.clear();
		counting_arr.push_back(Counting_s(0, 0, 0));

		scanf("%d %d", &N, &Q);


		for (int j = 0; j < N; ++j) {
			int a = 0, b = 0, c = 0;
			scanf("%d", &TEMP);

			if (TEMP == 1)
				++a;
			else if (TEMP == 2)
				++b;
			else if (TEMP == 3)
				++c;


			auto last_one = counting_arr.back();
			counting_arr.push_back(last_one + Counting_s(a, b, c));
			
			//calf_arr.push_back(Calf_s(j + 1, TEMP));
		}

		//for(const Counting_s item : counting_arr)
		//    printf("%d %d %d\n",item.c1,item.c2,item.c3);

		printf("#%d\n", i + 1);
		for (int k = 0; k < Q; ++k) {
			scanf("%d %d", &R, &L);
			auto result = cumlating();
			printf("%d %d %d\n", result[0], result[1], result[2]);
		}

	}

	return 0;
}
