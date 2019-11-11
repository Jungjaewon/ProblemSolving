

#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <map>
#include <cstdio>

using namespace std;
char input_string[2500];
//char* input_string;
char* temp_string;
int T;
map<string, int> si_dict;
vector<string> string_arr;


string processing() {
	const string digit = string_arr[0];
	string head = "";
	int jarit_su = -1;
	int dot_location = digit.find(".");
	int ind = -1;
	bool last_flag = false;
	bool flag = false; // flag is True ; decimal number // flag is False ; interger;
	bool zero_decimal = false;
	//printf("dot_location : %d\n", dot_location);
	//fflush(stdout);
	if (dot_location != string::npos) { // the digit is decimal number; // X.XXXX or 0.XXXXXXX

		flag = true;

		if (digit[0] == '0' && digit[1] == '.') { // 0.XXXXXXXXX

			zero_decimal = true;

			for (int i = dot_location + 1; i < digit.size(); ++i) {
				if (digit[i] != '0') {
					ind = i;
					break;
				}
			}// find non first '0' index in the digit;

			if (ind == digit.size() - 1)
				last_flag = true;

			jarit_su = -(ind - 1);

		}
		else {  // XX.XXXXXXX

			for (int i = dot_location + 1; i < digit.size(); ++i) {
				if (digit[i] != '0') {
					ind = i;
					break;
				}
			}// find non first '0' index in the digit;

			jarit_su = (dot_location - 1);
		}

	}
	else { // the digit is integer;
		flag = false;
		jarit_su = digit.size() - 1;
	}

	if (string_arr.size() == 3) {
		head = string_arr[1];
		//printf("head : %s si_dict[head] %d jarit_su : %d\n",head.c_str(), si_dict[head], jarit_su);
		jarit_su = jarit_su + si_dict[head];
	}



	if (flag) { // flag is True ; decimal number

		string result = "";

		if (zero_decimal) { // 0.XXXXXXX
			result += digit[ind];
			if (last_flag == false)
				result += ".";

			for (int i = ind + 1; i < digit.size(); ++i) {
				result += digit[i];
			}

			result += " * 10^";
			result += to_string(jarit_su);
			result += " ";
			result += string_arr.back();

			return result;
		}
		else { // XX.XXXX

			result += digit[0];
			result += ".";

			for (int i = 1; i < digit.size(); ++i) {

				if (digit[i] == '.')
					continue;
				result += digit[i];
			}
			result += " * 10^";
			result += to_string(jarit_su);
			result += " ";
			result += string_arr.back();

			return result;
		}

	}
	else { // flag is False ; interger;

		string result = "";
		result += digit[0];
		result += ".";

		for (int i = 1; i < digit.size(); ++i) {
			result += digit[i];
		}
		result += " * 10^";
		result += to_string(jarit_su);
		result += " ";
		result += string_arr.back();

		return result;
	}
}

int main()
{

	si_dict["yotta"] = 24;
	si_dict["zetta"] = 21;
	si_dict["exa"] = 18;
	si_dict["peta"] = 15;
	si_dict["tera"] = 12;
	si_dict["giga"] = 9;
	si_dict["mega"] = 6;
	si_dict["kilo"] = 3;
	si_dict["hecto"] = 2;
	si_dict["deca"] = 1;
	si_dict["deci"] = -1;
	si_dict["centi"] = -2;
	si_dict["milli"] = -3;
	si_dict["micro"] = -6;
	si_dict["nano"] = -9;
	si_dict["pico"] = -12;
	si_dict["femto"] = -15;
	si_dict["ato"] = -18;
	si_dict["zepto"] = -21;
	si_dict["yocto"] = -24;


	scanf("%d", &T);
	getchar();
	for (int i = 0; i < T; ++i) {
		getchar();
		scanf("%[^\n]", input_string);
		//printf("'%s'\n", input_string);
		//fflush(stdout);
		temp_string = strtok(input_string, " ");
		while (temp_string != NULL) {
			string_arr.push_back(string(temp_string));
			//printf("%s\n", temp_string);
			//fflush(stdout);
			temp_string = strtok(NULL, " ");
		}

		printf("#%d ", i + 1);
		printf("%s", processing().c_str());
		printf("\n");

		// clear variables
		temp_string = NULL;
		string_arr.clear();
		input_string[0] = '\0';
	}
}

