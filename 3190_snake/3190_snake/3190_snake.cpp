#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <unordered_map>

using namespace std;

/*
한시간안되게 걸린문제다.

초기 위치를 문제를 제대로 읽지 않아서 찾는데 시간이 오래걸렸다 문제를 제대로 읽자.!!!

dirrection을 바꾸는 거는 brainfuck 문제에서 배열 포인터 변경처럼 하나의 수식으로 깔끔하게 활용했다.

방향 전환을 하는 것은 앞에 있으면 sec으로 해야하고 뒤에 있으면 sec + 1을 해야한다 바꾼다고 무슨 차이가 있겠는가 했는데 차이가 있었다. 참고!!
앞에 있으면 ++sec을 하고 다시 돌아 오기 때문이고 뒤에 있으면 ++sec을 하기 전이기 때문이다.

dx dy를 북동남서 해서 했던 것은 간결하게 잘했다.

nx,ny를 계산하기 때문에 이 때의 시간은 현재시간 sec + 1이다. break를하고 나갈때 ans = sec + 1을 해주어야 한다.

사과 명령 자료구조도 vector가 아닌 map이 적당했다.

뱀이 7자 모양 등 다양한 굴곡이 있을때 어떻게 해야하지 고민을 많이 하면서 시간을 많이 보냈다.
하지만 단순히 머리와 마지막부분만 관리해주면서 처리하니 됐다.
뱀을 수직 수평 부분으로 나누어서 관리하려고 하니 수평,수직 판단을 해야해서 어려워졌다.
그래서 더 생각하지 않고 바로 수행했다.

처음에 제대로 안될때 뱀의 이동에 문제가 있었나 생각하고 이동부분을 수정했다. 그래서 head라는 것을 도입했는데
사과가 있을때와 없을때 모두 도입해야하는데 한쪽에만 도입했다.
그래서 결과가 이상하게 나왔다.
그리고 pair sorting을 했는데 꼬리가 머리보다 밑에 있으면 이상한 결과를 가져오기 때문에 처음에 넣었다가 제거했다.

*/

int N, K, L;
int IX, IY;
char ID;
int ans;
// N, E, S, W
int dx[] = {-1, 0, 1, 0};
int dy[] = {0 , 1, 0, -1};
typedef pair<int, int> PAIR;
typedef struct commnad_s {
	int x;
	char c;
	commnad_s():x(0),c(' ') {}
	commnad_s(int ix, char ic):x(ix), c(ic) {}
} commnad;
vector<PAIR> apple_locs;
vector<PAIR> snake;
vector<commnad> commnad_arr;
set<PAIR> apple_set;
map<int, char> commnad_map;

bool body_check(int x, int y) {

	for (int i = 0; i < snake.size(); ++i) {
		if (snake[i].first == x && snake[i].second == y)
			return true;
	}

	return false;
}

void processing() {
	int sec = 0;
	int dir = 1;
	while (true) {

		//stable_sort(snake.rbegin(), snake.rend());
		int nx = snake[0].first + dx[dir];
		int ny = snake[0].second + dy[dir];

		if (!(1 <= nx && nx<= N && 1 <= ny && ny <= N)) //  이 순간이 현재의 다음
			break;
		else if ((1 <= nx && ny <= N && 1 <= ny && ny<= N) && body_check(nx, ny)) //  이 순간이 현재의 다음
			break;
		else if (apple_set.find(make_pair(nx, ny)) != apple_set.end()) {
			apple_set.erase(make_pair(nx, ny));
			snake.insert(snake.begin(), make_pair(nx, ny));
		}
		else if (apple_set.find(make_pair(nx, ny)) == apple_set.end()) {
			snake.insert(snake.begin(), make_pair(nx, ny));
			snake.pop_back();
		}

		if (commnad_map.count(sec + 1)) {
			if (commnad_map[sec + 1] == 'L')
				dir = (dir + 3) % 4;
			else
				dir = (dir + 1) % 4;
		}

		++sec;
	}

	ans = sec + 1;
}

int main()
{
	freopen("input.txt","r",stdin);
	scanf("%d %d",&N,&K);

	for (int i = 0; i < K; ++i) {
		scanf("%d %d",&IX, &IY);
		apple_set.insert(make_pair(IX, IY));
		//apple_locs.push_back(make_pair(IX,IY));
	}

	scanf("%d", &L);
	for (int i = 0; i < L; ++i) {
		scanf("%d %c", &IX, &ID);
		//commnad_arr.push_back(commnad(IX,ID));
		commnad_map[IX] = ID;
	}

	snake.push_back(make_pair(1,1));

	processing();

	printf("%d",ans);
	return 0;
}

