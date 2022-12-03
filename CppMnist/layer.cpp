#include<vector>
#include<algorithm>
#include<string>
#include<assert.h>
#include<random>
#include<time.h>
#include <string.h>
#include "layer.h"
#include <iostream>
#include <fstream>
#include <string>
/*matrix*/
mat::mat(std::vector<std::vector<double>>& src)
{
	hight = src.size();
	wight = src[0].size();
	for (int i = 0; i < hight; i++)
	{
		for (int j = 0; j < wight; j++)
			matrix.push_back(src[i][j]);
	}
	
	std::vector<std::vector<double>> T;
	src.swap(T);
}
mat::mat(int h, int w,int s)
{
	hight = h;
	wight = w;
	if(s==-1)
	{
		std::default_random_engine e1(time(0));
		std::normal_distribution<double> distribution(0, 1.0);
		for (int i = 0; i < h * w; i++)
			matrix.push_back(distribution(e1));
	}
	else
	{
		for (int i = 0; i < h * w; i++)
			matrix.push_back(s);
	}
}
mat::mat(mat* src)
{
	matrix.assign(src->matrix.begin(), src->matrix.end());
	wight = src->Ghight();
	hight = src->Ghight();
}
void mat::T()
{
	std::vector<double> t;
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
	std::vector<std::vector<double>> res;
	std::vector<double> temp;
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
	std::vector<std::vector<double>> temp;
	std::vector<double> res;
	int size = m1.hight * m1.wight;
	for (int i = 0; i <size ; i++)
		res.push_back(m1.matrix[i] + m2.matrix[i]);
	temp.push_back(res);
	mat* M = new mat(temp);
	M->hight = m1.hight;
	M->wight = m1.wight;
	return M;

}
mat* operator*(double k, const mat& m2)
{
	int size = m2.hight*m2.wight;
	mat* m  = new mat(m2);
	for(int i=0;i<size;i++)
	{
		m->matrix[i] *= k;
	}
	return m;
}
mat* operator-(const mat& m1, const mat& m2)
{
	assert(m1.hight==m2.hight);
	assert(m1.wight==m2.wight);
	int size = m2.hight*m2.wight;
	mat * m = new mat(m1);
	for(int i=0;i<size;i++)
	m->matrix[i]-=m2.matrix[i];
	return m;
}
void mat::reset(int w,int h)
{
    if(w*h!=wight*hight)
    {
        printf("wrong size given\n");
        return;
    }
    wight = w;
    hight = h;
}
void mat::Printsize(){printf("matrix size:(%d,%d)\n",hight,wight);}
int mat:: Ghight(){return hight;}
int mat::Gwight(){return wight;}
/*IO*/


/*Dataset*/


Dataset::Dataset(int size_, int batch_size_)
{
	size = size_;
	batch_size = batch_size_;
	loaded_size = 0;
	sample_idx = (int*)malloc(sizeof(int) * size);
	if (sample_idx) memset(sample_idx, 0, sizeof(int) * size);
	else { printf("unable to alloc memory for datset\n"); exit(0); }
	for (int i = 0; i < size; i++)
	{
		*(sample_idx + i) = i;
	}
	batch_idx = (int*)malloc(sizeof(int) * batch_size);
	if (!batch_idx) { printf("unable to alloc memory for datset\n"); exit(0); }
	else memset(batch_idx, 0, sizeof(int) * batch_size);
}
void Dataset::PrintIdx()
{
	for (int i = 0; i < size; i++)
		printf("%d ", sample_idx[i]);
}
void Dataset::shuffle()
{
	int t1, t2;
	for (int i = 0; i < (size / 4); i++)
	{
		t1 = rand()%(size-1);
		t2 = rand()%(size-1);
		int temp = sample_idx[t1];
		sample_idx[t1] = sample_idx[t2];
		sample_idx[t2] = temp;
	}
}
void Dataset::load_batch()
{
	//printf(" loaded_size %d\n", loaded_size);
	if(size-loaded_size>batch_size)
	{
		for (int i = 0; i < batch_size; i++)
		{
			batch_idx[i] = sample_idx[loaded_size + i];
		}
		loaded_size += batch_size;
	}
	else
	{
		for (int i = 0; i < size - loaded_size-1; i++)
		{
			batch_idx[i] = sample_idx[loaded_size + i];
		}
		loaded_size = 0;
		//printf("1 loaded_size %d\n", loaded_size);
	}
}
Dataset::~Dataset()
{
	free(sample_idx);
	free(batch_idx);
	return;
}

/*layer*/

/*dense*/

dense::dense(int in_size, int out_size, int ba_size)
{
	input_size = in_size;
	output_size = out_size;
	batch_size = ba_size;
	
	weight = new mat(input_size, output_size, -1);
	bias = new mat(batch_size, output_size, 1);
	x = new mat(batch_size, input_size, 0);  
	out =new mat(batch_size, output_size, 1);
	dw = new mat(input_size, output_size, 0);
	db = new mat(batch_size, output_size, 0);
}
void dense::forward(mat* input)
{
	//private variable cannot access, later write a function 
	//assert(input->matrix.size() == batch_size);
	//assert(input->matrix[0].size() == input_size);
	mat* f1 = (*input *(* weight)) ;
	mat* trash = out;
	delete trash;
	out = (*f1+*bias);
	trash = f1;
	delete trash;
}
mat* dense::backward(mat* dinput)
{
	weight->T();
	mat* dx = ((*dinput) *(*weight));
	mat* trash = dw;
	weight->T();
	x->T();
	dw =( *x * (*dinput));
	delete trash;
	x->T();
	//db = np.sum(dinput,axis=0)
	return dx;
}
void dense::PrintMem(int x)
{
	if (x==1)
	{
		printf("weight ");
		weight->Printsize();
		//weight->PrintMat();
	}
	if (x == 2)
	{
		printf("bias ");
		bias->Printsize();
		//bias->PrintMat();
	}
	if (x == 3)
	{
		printf("out ");
		out->Printsize();
		out->PrintMat();
	}
	if (x == 4)
	{
		printf("dw ");
		dw->Printsize();
		dw->PrintMat();
	}
	if (x == 5)
	{
		printf("db ");
		db->Printsize();
		db->PrintMat();
	}
}
void dense::GetPara(std::vector<mat*>& P, std::vector<mat*>& G)
{
	P.clear();
	G.clear();
	P.push_back(weight);
	P.push_back(bias);
	G.push_back(dw);
	G.push_back(db);
}
void dense::PushPara(std::vector<mat*>& P)
{
	weight = P[0];
	bias = P[1];
}
/*softmax_with_loss*/


softmax_loss::softmax_loss(int out_size, int ba_size)
{
	output_size = out_size;
	batch_size = ba_size;
	x = new mat(batch_size, output_size, 0);
	out =new mat(batch_size, output_size, 1);
}
mat* softmax_loss::backward(std::vector<int>& label)
{
	mat* M = new mat(batch_size, output_size, 0);
	for (int j = 0; j < batch_size; j++)
	{
		int row = j * output_size;
		int L;
		for (int i = 0; i < output_size; i++)
		{
			if (label[j] == i)L = 1;
			else L = 0;
			M->matrix[row + i] = out->matrix[row + i] - L;
		}
	}
	return M;
}
void softmax_loss::forward(mat* input,std::vector<int>& label)
{
	assert(label.size() == batch_size);
	
	std::vector<double> S;
	double s = 0;
	for (int j = 0; j < batch_size; j++)
	{
		for (int i = 0; i < output_size; i++)
		{
			int idx = j * input_size + i;
			double t = exp(input->matrix[idx]);
			out->matrix[idx] = t;
			s += t;
		}
		S.push_back(s);
		s = 0;
	}
	int len = input_size * output_size;
	int line =0;
	for (int i = 0; i < len; i++)
		{
			if((i+1)%output_size==0)line++;
			x->matrix[i] /= S[line];
		}
	for (int j = 0; j < batch_size; j++)
	{
		for (int i = 0; i < output_size;i++)
		{
			int t=0;
			int idx = j * input_size + i;
			if(label[j]==i)t=1;
			else t=0;
			x->matrix[idx] = -1*t * log(out->matrix[idx]+1e-7);
		}
	}


}
void softmax_loss::predict(std::vector<int>& prediction)
{
	prediction.clear();
	pre.clear();
	for (int j = 0; j < batch_size; j++)
	{
		int temp = 0;
		int max = 0;
		for (int i = 0; i < output_size; i++)
		{
			if (out->matrix[j * output_size + i] > max)
			{
				max = out->matrix[j * output_size + i];
				temp = i;
			}
			//printf("pre size:%d\n",pre.size());
			prediction.push_back(temp);
			pre.push_back(temp);
			temp = 0;
		}
	}
}
softmax_loss::~softmax_loss()
{
	delete& x;
	delete& out;
}
double softmax_loss::accuracy(std::vector<int>& label)
{
	std::vector<int> pre1;
	if(pre.size()==0)predict(pre1);
	//printf("size of pre %d\n",pre.size());
	double acc=0;
	
	for(int i=0;i<batch_size;i++)
	{//printf("acc ");
		if(pre[i]==label[i])
		acc++;
	}
	//printf("acc:%lf\n",acc/batch_size);
	return acc;
}
/*optimizer*/
Mon::Mon(double lr_,double mon_)
{
	lr = lr_;
	mon = mon_;
}
void Mon::update(std::vector<mat*> P,std::vector<mat*> G)
{
	int size = P.size();
	if(v.size()==0)
	{
		for(int i =0;i<size;i++)
	{
		mat* m = new mat(P[i]->Ghight(),P[i]->Gwight(),0);
		v.push_back(m);
	}

	}
	mat* trash;
	for(int i =0;i<size;i++)
	{
		/*这里属实是给我挖了大坑了*/
		mat* f1 = mon*(*v[i]);
		mat* f2 = lr*(*G[i]);
		
		mat* t1  = *f1 -*f2;

		trash = f1;
		delete trash;
		trash = f2;
		delete trash;
		

		trash = v[i];
		v[i] = t1;
		delete trash;

		t1 = (*P[i])+(*v[i]);
		P[i] = t1;
		trash = P[i];
		delete trash;
		
	}
	//printf("P[0]:");P[0]->Printsize();
	//printf("P[1]:");P[1]->Printsize();
}