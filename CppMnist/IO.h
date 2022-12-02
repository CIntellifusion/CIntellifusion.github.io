#pragma once
#ifndef IO
#define IO

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;
#define type double

int ReverseInt(int i);
void read_Mnist_Label(string filename, vector<double>& labels);
void read_Mnist_Images(string filename, vector<vector<double>>& images);
#endif // !IO
