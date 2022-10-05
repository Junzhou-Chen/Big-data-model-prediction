#include "csv.h"
int getLong(string line) {
	int numsize = 0;
	for (auto a : line)
		if (a == ',') numsize++;
	return numsize + 1;
}

vector<vector<string>> csvRead(string filename)
{
	vector<vector<string>> result;
	ifstream infile(filename, ios::in);
	string line;
	getline(infile, line);
	int sizex = getLong(line);
	while (getline(infile, line)) {
		stringstream ss(line);
		string str;
		vector<string> lineReader;
		for (int i = 0; i < sizex; i++) {
			getline(ss, str, ',');
			lineReader.push_back(str);
		}
		result.push_back(lineReader);
	}
	return result;
}