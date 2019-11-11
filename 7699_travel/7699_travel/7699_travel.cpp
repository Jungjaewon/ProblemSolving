
#include <iostream>

using namespace std;

int T;
int R;
int C;
char temp;
int result = -10000;
int map[21][21];

int d1[] = {0,1,0,-1};
int d2[] = {1,0,-1,0};

void processing(int visit_bit, int x, int y, int cnt) {

	bool flag = false;
	for (int i = 0; i < 4; ++i) {
		int new_x = x + d1[i];
		int new_y = y + d2[i];
		bool check = visit_bit & (1 << map[new_x][new_y]);
		if (!check && 0 < new_x && new_x <= R && 0 < new_y && new_y <= C) {
			processing(visit_bit | (1 << map[new_x][new_y]), new_x, new_y, cnt + 1);
			flag = true;
		}
	
	}

	if (!flag && cnt > result) { // no possible , ending
		result = cnt;
	}
}
int main()
{
	cin >> T;


	for (int i = 0; i < T; ++i) {
	
		cin >> R >> C;

		for (int j = 1; j <= R; ++j) {
			for (int k = 1; k <= C; ++k) {
				cin >> temp;
				map[j][k] = temp - 'A';
			}
		}

		processing(1 << map[1][1], 1, 1, 1);

		cout << "#" << i + 1 << " " << result <<"\n";
		result = -10000;
	}
}


