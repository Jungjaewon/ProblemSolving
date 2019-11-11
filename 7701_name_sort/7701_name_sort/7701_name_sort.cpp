

#include <cstdio>
#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include <vector>
#include <set>


using namespace std;

int T;
int N;
char temp[51];
vector<string> name_arr;
set<string> name_set;

bool custom_cmp(string a, string b) {

	if (a.size() == b.size()) {
	
		if (a < b)
			return true;
		else if (a == b)
			return true;
		else
			return false;
	}
	else if (a.size() < b.size()) {
		return true;
	}
	else if (a.size() > b.size()) {
		return false;
	}

}

int main()
{

	scanf("%d",&T);

	for (int i = 0; i < T; ++i) {
	
		scanf("%d", &N);

		for (int j = 0; j < N; ++j) {
			scanf("%s",temp);
			//name_arr.push_back(string(temp));
			name_set.insert(string(temp));
		}
		vector<string> name_arr(name_set.begin(), name_set.end());
		stable_sort(name_arr.begin(), name_arr.end(), custom_cmp);
		cout << "#" << i + 1 << "\n";
		for (const string name : name_arr)
			printf("%s\n", name.c_str());

		name_set.clear();
		//name_arr.clear();
	}
}

