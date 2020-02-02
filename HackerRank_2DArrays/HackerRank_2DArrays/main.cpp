#include <iostream>
#include <vector>

using namespace std;

typedef pair<int, int> pii;

/*
I solved hackerRank 2D array problem.
https://www.hackerrank.com/challenges/2d-array/problem?h_l=interview&playlist_slugs%5B%5D=interview-preparation-kit&playlist_slugs%5B%5D=arrays
*/

pii checking(int& i, int& j, vector<pii>& allLocation, const vector<vector<int>>& arr) {

	int sum = 0;

	for (pii loc : allLocation) {

		int x = loc.first;
		int y = loc.second;
		if (-1 < i + x && i + x < 6 && -1 < j + y && j + y < 6)
			sum += arr[i + x][j + y];
		else
			return { false,-1 };
	}

	return { true,sum };
}

int hourglassSum(vector<vector<int>> arr) {

	int maxValue = -10e4;
	int flag;
	vector<pii> allLocation;
	allLocation.push_back({ 0,0 });
	allLocation.push_back({ 0,1 });
	allLocation.push_back({ 0,2 });
	allLocation.push_back({ 1,1 });
	allLocation.push_back({ 2,0 });
	allLocation.push_back({ 2,1 });
	allLocation.push_back({ 2,2 });

	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++) {
			pii result = checking(i, j, allLocation, arr);
			flag = result.first;

			if (flag)
				maxValue = max(maxValue, result.second);
			else
				continue;
		}
	}

	return maxValue;
}


int main() {

	return 0;
}