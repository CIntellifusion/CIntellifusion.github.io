#include<vector>
#include<algorithm>
#include<string>
#include "mat.h"
#include<assert.h>
mat::mat(std::vector<std::vector<type>>& src)
{
	hight = src.size();
	wight = src[0].size();
	for (int i = 0; i < hight; i++)
	{
		for (int j = 0; j < wight; j++)
			matrix.push_back(src[i][j]);
	}
}
void mat::T()
{
	std::vector<type> t;
	//printf("T: hight %d ,wight %d\n", hight, wight);
	for (int i = 0; i < hight; i++)
	{
		for (int j = 0; j < wight; j++)
		{
			t.push_back(matrix[j + i * wight]);
		}
	}
	
	int temp = hight;
	hight = wight;
	wight = temp;
	//printf("T: hight %d ,wight %d\n", hight, wight);
	matrix.swap(t);
}

void mat::PrintMat()
{
	for (int i = 0; i < hight; i++)
	{
		for (int j = 0; j < wight; j++)
			printf("%lf ", matrix[i* wight + j ]);
		printf("\n");
	}
	
	
	
}
mat* operator*(const mat& m1, const mat& m2)
{
	//printf("m1 %d,m2 %d\n", m1.wight, m2.hight);
	//printf("m1 %d,m2 %d\n", m2.wight, m1.hight);
	assert(m1.wight== m2.hight);
	int hight_r = m1.hight;
	int wight_r = m2.wight;
	double dot = 0;
	std::vector<std::vector<type>> res;
	std::vector<type> temp;
	for (int h = 0; h < m1.hight; h++)
	{
		for (int w = 0; w < m2.wight; w++)
		{
			/*two vector dot*/
			for (int i = 0; i < m1.wight; i++)
			{
				dot += m1.matrix[h*m1.wight+i] * m2.matrix[i*m2.wight+w];
			}
			
			temp.push_back(dot);
			dot = 0;
		}
		res.push_back(temp);
		temp.clear();
	}
	mat* M = new mat(res);
	return M;

}
mat* operator+(const mat& m1, const mat& m2)
{
	assert(m1.hight == m2.hight);
	assert(m1.wight == m2.wight);
	std::vector<std::vector<type>> temp;
	std::vector<type> res;
	for (int i = 0; i < m1.hight * m1.wight; i++)
		res.push_back(m1.matrix[i] + m2.matrix[i]);
	temp.push_back(res);
	mat* M = new mat(temp);
	M->hight = m1.hight;
	M->wight = m1.wight;
	return M;

}
