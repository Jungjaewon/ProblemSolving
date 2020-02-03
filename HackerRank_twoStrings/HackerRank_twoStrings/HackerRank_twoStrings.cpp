
#include <iostream>
#include <set>
#include <string>

using namespace std;

// Complete the twoStrings function below.
string twoStrings(string s1, string s2) {
	set<char> char_set;
	for (char a : s1)
		char_set.insert(a);

	for (char a : s2) {

		if (char_set.find(a) != char_set.end()) {
			return "YES";
		}

	}
	return "NO";
}

int main()
{
    std::cout << "Hello World!\n";
}
