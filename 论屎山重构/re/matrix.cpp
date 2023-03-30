#ifndef LAYER
#define LAYER
#include<vector>
#include<algorithm>
#include<string>
#include<vector>
#include<cstdlib>
#include<time.h>
class mat
{
private:
	int hight, wight;
public:
	std::vector<double> matrix;
	mat(std::vector<std::vector<double>> &src);
	mat(int w, int h,int s);
	mat(mat* src);
	void PrintMat();
	void Printsize();
	void T();
    void reset(int wight_s,int hight_s);
	friend mat operator*(const mat& m1,const mat & m2);
	friend mat operator+(const mat& m1, const mat& m2);
	friend mat operator*(double k, const mat& m2);
	friend mat operator-(const mat& m1, const mat& m2);
};
int main()
{
    return 0 ;
}