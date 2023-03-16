#ifndef LAYER
#define LAYER
#include<vector>
#include<algorithm>
#include<string>
#include<vector>
#include<cstdlib>
#include<time.h>
/*IO */
/*End IO*/
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
	int Ghight();
	int Gwight();
    void reset(int wight_s,int hight_s);
	friend mat* operator*(const mat& m1,const mat & m2);
	friend mat* operator+(const mat& m1, const mat& m2);
	friend mat* operator*(double k, const mat& m2);
	friend mat* operator-(const mat& m1, const mat& m2);
};

class Dataset
{
private:
	int size;
	int batch_size;
	int loaded_size;
	int* sample_idx;
	
public:
	int* batch_idx;
	Dataset(int size_, int batch_size_);
	void shuffle();
	void load_batch();
	void PrintIdx();
	~Dataset();
};

/*layer*/
class dense 
{
private:
	int input_size, output_size, batch_size;
	mat* weight;
	mat* bias;
	mat* x;
	mat* db;
	mat* dw;
public:
	mat* out;
	dense(int in_size, int out_size, int ba_size);
	void forward(mat* input);
	mat* backward(mat* input);
	void PrintMem(int x);
	void GetPara(std::vector<mat*>& P, std::vector<mat*>& G);
	void PushPara(std::vector<mat*>& P);
};

class softmax_loss 
{
private:
	int  input_size,output_size, batch_size;
	std::vector<int> pre;
	mat* x;
	
public:
	mat* out;
	
	softmax_loss(int out_size,int ba_size);
	~softmax_loss();
	void forward(mat* input, std::vector<int>& label);
	mat* backward(std::vector<int>& label);
	double accuracy(std::vector<int>& label);
	void predict(std::vector<int>& prediction);
};
/*optimizer*/
class Mon
{
private:
	double lr;
	double mon;
	std::vector<mat*> v;
public:
	Mon(double lr_,double mon_);
	void update(std::vector<mat*> P,std::vector<mat*> G);
};
#endif