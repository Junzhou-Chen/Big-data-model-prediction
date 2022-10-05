#pragma once
#ifndef _CSV_H_
#include <iostream> 
#include <string>
#include <unordered_map>
#include <vector>
//#include <windows.h>
#include <armadillo>

using namespace std;
using namespace arma;
int getLong(string line);
vector<vector<string>> csvRead(string filename);
#endif // !_CSV_H_

