
#include "csv.h"
#include "data.h"
#include <time.h>
vector<vector<string>> dataMake(vector<vector<string>> strs) {
	// 构建title标签
	// map 构建
	map<string, int> map_num1 = { {"80后", 2,},
								{"70后", 3,},
								{"60后", 4,},
								{"90后", 5,},
								{"50后", 6,},
								{"40后", 7,},
								{"00后", 8,},
								{"20后", 9,} };

	map<string, int> map_num2 = { {"21~40", 10,},
								{"41~60", 11,},
								{"61~80", 12,},
								{"1~20", 13,},
								{"80~100", 14,} };
	map<string, int> map_num3 = { {"5G", 15,},
								{"3G", 16,},
								{"4G", 17,},
								{"2G", 18,},
								{"未知", 19,} };

	// map存储位置
	ifstream infile("C:/Users/13747/Desktop/大数据比赛/title2.csv", ios::in);
	string line;
	vector<string> title;
	getline(infile, line);
	int sizex = getLong(line);
	stringstream ss(line);
	string str;
	for (int i = 0; i < sizex; i++) {
		getline(ss, str, ',');
		title.push_back(str);
	}
	cout << title.size() << endl;

	map<string, int> map_num;
	for (int i = 0; i < title.size(); i++) {
		map_num.insert({ title[i],i });
	}
	// map存储位置end

	vector<vector<string>> data_train;
	data_train.push_back(title);
	for (int i = 0; i < strs.size(); i++) {
		vector<string> str_init(title.size(), "0");
		int mm = 0;
		str_init[0] = strs[i][0];
		// labe 1
		str_init[1] = strs[i][1];
		// labe 2
		int num = map_num1[strs[i][2]];
		str_init[num] = "1";
		// labe 3
		num = map_num2[strs[i][3]];
		str_init[num] = "1";
		// labe 4
		num = map_num3[strs[i][4]];
		str_init[num] = "1";
		// labe 5
		if (strs[i][5] == "1") {
			str_init[20] = "1";
		}
		if (strs[i][6] == "1") {
			str_init[21] = "1";
		}
		num = stoi(strs[i][7]) + 21;
		str_init[num] = "1";
		num = map_num[strs[i][8]];
		str_init[num] = "1";
		num = map_num[strs[i][10]];
		str_init[num] = "1";
		data_train.push_back(str_init);
	}


	return data_train;
}