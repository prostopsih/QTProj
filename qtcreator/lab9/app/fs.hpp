#pragma once
#include <vector>
#include <fstream>
#include <string>
#include <iostream>
using namespace std;

vector<string> readCSV(fstream &fin);
void write(fstream &fout, vector<string>& arr);

