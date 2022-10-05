#include <iostream> 
#include <string>
#include <unordered_map>
#include <vector>
//#include <windows.h>
#include <armadillo>
#include "csv.h"
#include "data.h"
using namespace std;
using namespace arma;



void getMes(vector<vector<string>> strs, int target) {

	unordered_map<string, int> mash;
	vector<string> title;
	for (auto i : strs) {
		if (mash.find(i[target]) == mash.end()) {
			title.push_back(i[target]);
			mash.insert({ i[target], 1 });
		}
	}
	for (auto i : title)
		cout << i << ',';
	cout << endl << title.size() << endl;
}
// 1: 2
// 2: 8
// 3: 5
// 4: 5
// 5: 2
// 6: 2
// 7: 3
// 8: 37
// 9: 5
// 10: 32
// 11: 551
int main()
{
	auto data_train = csvRead("C:/Users/13747/Desktop/大数据比赛/data_ predict.csv");
	auto user_train = csvRead("C:/Users/13747/Desktop/大数据比赛/user_train.csv");
	
	ofstream outFile("C:/Users/13747/Desktop/大数据比赛/abc.csv", ios::out);
	map<string, int> map_num2 = { {"景区类别1", 1,},
							{"景区类别2", 2,},
							{"景区类别3", 3,},
							{"景区类别4", 4,} };
	if (!outFile)
	{
		// out part
		cout << "打开文件失败！" << endl;

		return false;
	}

	int size = data_train[0].size();
	for (int i = 0; i < data_train.size();i++) {
		//outFile << data_train[i][3] << ",";
		outFile << data_train[i][0] << ",";
		//outFile << data_train[i][2] << ",";
		vector<string> str = user_train[stoi(data_train[i][1]) - 1];
		for (int j = 0; j < str.size() - 1; j++) {
			outFile << str[j] << ",";
		}
		outFile << str[str.size() - 1] << endl;
		
		

	}
	outFile.close();

    return 0;
}



