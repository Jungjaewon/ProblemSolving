#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

/*
코드 자체는 20분정도 안에 다 구현을 했다.

디버깅에 오래 걸렸다. 30분이상.

이전 코드보다 간결하게 작성했다. 이게 dx dy dir를 이용한 덕분에 코드가 간결해졌다.

나머지 연산을 하는데 있어서 괄호를 안쳐서 결과가 이상하게 나왔다. 7,4에서 8,3으로 띄었다..?? 그래서
이전문제에서는 잘 해결했다.

그리고 초기 위치가 0~N-1까지 여서 개수가 안맞았다..,
"지도의 각 칸은 (r, c)로 나타낼 수 있고, r은 북쪽으로부터 떨어진 칸의 개수, c는 서쪽으로 부터 떨어진 칸의 개수이다." 
가 있으면 0~N-1 이다.

일번 이번 모드가 있는데 그것대로 구현했다.
*/
using namespace std;

int N, M;
int arr[51][51];
bool visited[51][51];
int dx[] = {-1, 0, 1,  0};
int dy[] = {0,  1, 0, -1};
int ans;

int rx,ry,dir;


void processing() {

	rx += 1;
	ry += 1;
	int nx;
	int ny;
	bool do_clean = true;
	while (true) {
	
		if (!visited[rx][ry] && do_clean) {
			//printf("cleaned : %d %d dir : %d\n", rx,ry,dir);
			visited[rx][ry] = true;
			ans += 1;
		}

		int cnt = 0;
		int cur_dir = dir;

		while (cnt != 4) {
			
			cur_dir = (cur_dir + 3) % 4;
			nx = rx + dx[cur_dir];
			ny = ry + dy[cur_dir];
			//printf("rx : %d, ry : %d, dir : %d, nx : %d, ny : %d\n",rx,ry,cur_dir, nx,ny);

			if (1 <= nx && nx <= N && 1 <= ny && ny <= M && !visited[nx][ny] && arr[nx][ny] == 0) 
				break;
			else
				++cnt;
		}
		//printf("rx : %d, ry : %d, cnt : %d, ans : %d\n",rx,ry,cnt,ans);
		if (cnt == 4) {
			nx = rx - dx[dir];
			ny = ry - dy[dir];
			if (1 <= nx && nx <= N && 1 <= ny && ny <= M && arr[nx][ny] == 0) {
				rx = nx;
				ry = ny;
				do_clean = false;
			}
			else if (1 <= nx && nx <= N && 1 <= ny && ny <= M && arr[nx][ny] == 1) 
				return;
		}
		else {
			rx = nx;
			ry = ny;
			do_clean = true;
			dir = cur_dir;
		}
	}
}

int main()
{
	freopen("input.txt","r",stdin);
	scanf("%d %d",&N,&M);

	scanf("%d %d %d",&rx,&ry,&dir);

	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= M; ++j) {
			scanf("%d",&arr[i][j]);
		}
	}

	processing();

	printf("%d", ans);
	return 0;
}

