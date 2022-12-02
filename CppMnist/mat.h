#pragma once
#ifndef MAT
#define MAT
#include<vector>
#include<algorithm>
#include<string>
#define type double
class mat
{
private:
	int hight, wight;
	std::vector<type> matrix;
	
	//mat operator*(const mat& m1);
public:
	mat(std::vector<std::vector<type>> &src);
	void PrintMat();
	void T();
	friend mat* operator*(const mat& m1,const mat & m2);
	friend mat* operator+(const mat& m1, const mat& m2);
};




#endif