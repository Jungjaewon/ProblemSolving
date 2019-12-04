
#include <iostream>
#include <string>
#include <vector>
#define N 60001 // 개수 때문에 배열선언에 문제가 있을 것이라 생각하고 재귀로 했는데 메모제이션 안되니 당연히 안됨
int arr[N];
using namespace std;

int recur(int n) { // 시간초과 난다 메모제이션이 안된다 따라서 비 효율적 정확도는 맞음

	if (n == 1)
		return 1;
	else if (n == 2)
		return 2;

	return (recur(n - 1) + recur(n - 2)) % 1000000007;
}

int solution(int n) {
	arr[0] = 0; 
	arr[1] = 1;
	arr[2] = 2;

	for (int i = 3; i <= n; ++i)
		arr[i] = (arr[i - 1] % 1000000007 + arr[i - 2] % 1000000007) % 1000000007;

	return arr[n];
}

int main()
{
    std::cout << "Hello World!\n";
}

