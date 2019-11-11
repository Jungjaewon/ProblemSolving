
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef struct operation_s {

	int r;
	int c;
	int s;
	operation_s() {}
	operation_s(int ir, int ic, int is):r(ir), c(ic), s(is) {}

} operation;

vector<operation> oper_arr;
int N, M, K;
int temp_arr[51][51];
int solve[51][51];
int ir, ic, is;
int Min = 10e8;

void rotation_oper(int sx, int sy, int ex, int ey) {

	while (sx < ex && sy < ey) {
		vector<int> arr;
		int cnt = 0;
		// read_part
		// left
		for (int y = sy; y <= ey; ++y)
			arr.push_back(temp_arr[sx][y]);
		// down
		for (int x = sx + 1; x < ex; ++x)
			arr.push_back(temp_arr[x][ey]);
		// right
		for (int y = ey; sy <= y; --y)
			arr.push_back(temp_arr[ex][y]);
		// up
		for (int x = ex - 1; sx < x; --x)
			arr.push_back(temp_arr[x][sy]);

		// move
		int t = arr.back();
		arr.pop_back();
		arr.insert(arr.begin(),t);

		// write_part
		for (int y = sy; y <= ey; ++y)
			temp_arr[sx][y] = arr[cnt++];
		// down
		for (int x = sx + 1; x < ex; ++x)
			temp_arr[x][ey] = arr[cnt++];
		// right
		for (int y = ey; sy <= y; --y)
			temp_arr[ex][y] = arr[cnt++];
		// up
		for (int x = ex - 1; sx < x; --x)
			temp_arr[x][sy] = arr[cnt++];

		++sx;
		++sy;
		--ex;
		--ey;
	}
}

void copy_arr() {

	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= M; ++j) {
			temp_arr[i][j] = solve[i][j];
		}
	}
}

bool cmp(operation a, operation b) {

	if (a.r < b.r)
		return true;
	else if (a.r == b.r) {

		if (a.c < b.c)
			return true;
		else if (a.c == b.c) {
			if (a.s < b.s)
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

bool operator<(operation a, operation b) {

	if (a.r < b.r)
		return true;
	else if (a.r == b.r) {

		if (a.c < b.c)
			return true;
		else if (a.c == b.c) {
			if (a.s < b.s)
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

int calculating() {

	int result = 10e5;
	int sum;
	for (int i = 1; i <= N; ++i) {
		sum = 0;
		for (int j = 1; j <= M; ++j) {
			sum += temp_arr[i][j];
		}
		result = min(result, sum);
	}

	return result;
}

void processing() {

	copy_arr();
	for (int i = 0; i < oper_arr.size(); ++i) {
		int sx = oper_arr[i].r - oper_arr[i].s;
		int sy = oper_arr[i].c - oper_arr[i].s;
		int ex = oper_arr[i].r + oper_arr[i].s;
		int ey = oper_arr[i].c + oper_arr[i].s;
		rotation_oper(sx, sy, ex, ey);
	}

	Min = min(calculating(),Min);
}

int main()
{

	freopen("input.txt","r",stdin);

	scanf("%d %d %d",&N,&M,&K);

	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= M; ++j) {
			scanf("%d",&solve[i][j]);
		}
	}

	for (int i = 0; i < K; ++i) {
		scanf("%d %d %d",&ir,&ic,&is);
		oper_arr.push_back(operation(ir,ic,is));
	}

	stable_sort(oper_arr.begin(), oper_arr.end(), cmp);

	do {
		processing();
		
	} while (next_permutation(oper_arr.begin(), oper_arr.end()));


	printf("%d", Min);
	return 0;
}
