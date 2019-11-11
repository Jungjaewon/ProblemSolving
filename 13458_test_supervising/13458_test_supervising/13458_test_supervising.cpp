

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
using namespace std;
/*
실제 문제는 빨리 풀었음. 그다지 어렵지 않음.
허나 printf("%d"); 가 문제를 만들었음 
N, A,B,C 범위가 넓어지면서 ans가 값이 커질수가 있음
따라서 "%lld"가 되어야하고 int 를 long long으로 사용해야한다.
한시간 7분만에 남의 내용 확인하고 해결
*/
int N;
int A, B, C;
long long ans = 0;

vector<int> test_room;

int main()
{

	freopen("input.txt","r",stdin);

	scanf("%d",&N);

	for (int i = 0; i < N; ++i) {
		scanf("%d",&A);
		test_room.push_back(A);
	}
	scanf("%d %d",&B,&C);

	for (int i = 0; i < test_room.size(); ++i) {
		test_room[i] = test_room[i] - B;
		++ans;
		if (test_room[i] < 0)
			test_room[i] = 0;
	}


	for (int i = 0; i < test_room.size(); ++i) {

		if (test_room[i] == 0)
			continue;
		ans += (test_room[i] / C);
		int ret = test_room[i] % C;
		if (ret != 0)
			ans += 1;
	}

	printf("%lld",ans);
	return 0;

}

