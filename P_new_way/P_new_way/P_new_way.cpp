
#include <iostream>
#include <string>
#include <set>
#include <unordered_set>
#include <iostream>

using namespace std;

typedef struct history_s {
	int px;
	int py;
	int nx;
	int ny;
	history_s() :px(0), py(0), nx(0), ny(0) {}
	history_s(int ipx, int ipy, int inx, int iny) :px(ipx), py(ipy), nx(inx), ny(iny) {}

} history;

bool operator<(history a, history b) {

	if (a.px < b.px)
		return true;
	else if (a.px == b.px) {
		if (a.py < b.py)
			return true;
		else if (a.py == b.py) {
			if (a.nx < b.nx)
				return true;
			else if (a.nx == b.nx) {
				if (a.ny < a.ny)
					return true;
				else
					return false;
			}
			else
				return false;
		}
		else
			return false;
	}
	else
		return false;
}
int dx[] = { -1,1, 0, 0 };
int dy[] = { 0, 0, 1, -1 };

int cur_x = 0;
int cur_y = 0;
set<history> visited_check;


void move(const char& dir, int& answer) {

	int prev_x = cur_x;
	int prev_y = cur_y;

	if (dir == 'U' && (cur_x + dx[0]) >= -5) {
		cur_x += dx[0];
		cur_y += dy[0];
	}
	else if (dir == 'D' && (cur_x + dx[1]) <= 5) {
		cur_x += dx[1];
		cur_y += dy[1];
	}
	else if (dir == 'R' && (cur_y + dy[2]) <= 5) {
		cur_x += dx[2];
		cur_y += dy[2];

	}
	else if (dir == 'L' && (cur_y + dy[3]) >= -5) {
		cur_x += dx[3];
		cur_y += dy[3];
	}

	if (prev_x != cur_x || prev_y != cur_y) {
		if (visited_check.find({ prev_x,prev_y,cur_x,cur_y }) == visited_check.end()) {
			++answer;
			visited_check.insert({ prev_x,prev_y,cur_x,cur_y });
			//visited_check.insert({cur_x,cur_y,prev_x,prev_y}); when road is undirected.
		}
	}
}

int solution(string dirs)
{
	int answer = 0;
	for (int i = 0; i < dirs.size(); ++i)
		move(dirs[i], answer);
	return answer;
}

int main()
{
    std::cout << "Hello World!\n";
}
