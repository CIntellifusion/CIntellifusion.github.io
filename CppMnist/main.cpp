# define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<iostream>
#include<vector>
#include<math.h>
#include "mat.h"
#include "IO.h"
#define type double
using namespace std;

void driver_mat();
void driver_IO();
int main()
{
	driver_mat();
	return 0;
}
void driver_IO()
{

	vector<double>labels;
	read_Mnist_Label("D:\\c++\\CppMnist\\MNIST\\raw\\t10k-labels-idx3-ubyte", labels);
	for (auto iter = labels.begin(); iter != labels.end(); iter++)
	{
		cout << *iter << " ";
	}

	vector<vector<double>>images;
	read_Mnist_Images("D:\\c++\\CppMnist\\MNIST\\raw\\t10k-images-idx3-ubyte", images);
	for (int i = 0; i < images.size(); i++)
	{
		for (int j = 0; j < images[0].size(); j++)
		{
			cout << images[i][j] << " ";
		}
	}
}
void driver_mat()
{
	vector<vector<type>> temp; vector<type> t1;
	double d;
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			printf("scanf value\n");
			scanf("%lf", &d);
			t1.push_back(d);
		}
		temp.push_back(t1);
		t1.clear();
	}
	mat* m1 = new mat(temp);
	mat* m2 = new mat(temp);
	printf("before tranfrom\n");
	m1->PrintMat();
	m1->T();
	printf("after transform\n");
	m1->PrintMat();

	mat* m3 =(*m1)*(*m2);
	m3->PrintMat();

	m1->T();
	mat* m4 = (*m1) + (*m2);
	m4->PrintMat();
}