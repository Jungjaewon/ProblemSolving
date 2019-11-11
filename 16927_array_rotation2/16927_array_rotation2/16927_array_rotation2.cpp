#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>


using namespace std;
int N, M, R;
int temp;
int arr[301][301];

void print_out() {

	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= M; ++j) {
			printf("%d ",arr[i][j]);
		}
		printf("\n");
	}
}

void processing() {
	int startX = 1;
	int startY = 1;
	int endX = N;
	int endY = M;

	while (startX < endX && startY < endY) {

		//printf("srartX : %d startY %d\n",startX,startY);
		//printf("endX : %d endY %d\n",endX,endY);

		vector<int> arr_contain;
		int cnt = 0;
		int temp;
		// read
		for (int y = startY; y <= endY; ++y)
			arr_contain.push_back(arr[startX][y]);
		for (int x = startX + 1; x <= endX -1; ++x)
			arr_contain.push_back(arr[x][endY]);
		for (int y = endY; y >= startY; --y)
			arr_contain.push_back(arr[endX][y]);
		for (int x = endX - 1; x >= startX + 1; --x)
			arr_contain.push_back(arr[x][startY]);


		//for (const int t : arr_contain)
		//	printf("%d ",t);
		//printf("\n");
		// rotation
		int newR = R % arr_contain.size();
		for (int i = 0; i < newR; ++i) {
			temp = arr_contain.front();
			arr_contain.erase(arr_contain.begin());
			arr_contain.push_back(temp);
		}

		// write
		for (int y = startY; y <= endY; ++y)
			arr[startX][y] = arr_contain[cnt++];
		for (int x = startX + 1; x <= endX - 1; ++x)
			arr[x][endY] = arr_contain[cnt++];
		for (int y = endY; y >= startY; --y)
			arr[endX][y] = arr_contain[cnt++];
		for (int x = endX - 1; x >= startX + 1; --x)
			arr[x][startY] = arr_contain[cnt++];


		// shift
		++startX;
		++startY;
		--endX;
		--endY;
	}
}

int main()
{

	freopen("input.txt","r",stdin);
	scanf("%d %d %d",&N,&M,&R);

	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= M; ++j) {
			scanf("%d",&temp);
			arr[i][j] = temp;
		}
	}
	processing();
	print_out();
	return 0;
}

