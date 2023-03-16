#include<vector>
#include<iostream>
#include<fstream>
#include<stdlib.h>
#include "layer.h"
#include<stdio.h>
using namespace std;
const char train_images[] = "D:\\c++\\CppMnist\\MNIST\\raw\\train - images - idx3 - ubyte";
const char train_labels[] = "D:\\c++\\CppMnist\\MNIST\\raw\\train-labels-idx1-ubyte";
const char t10k_images[] = "D:\\c++\\CppMnist\\MNIST\\raw\\t10k-images-idx3-ubyte";
const char t10k_labels[] = "D:\\c++\\CppMnist\\MNIST\\raw\\t10k-labels-idx1-ubyte";
vector<vector<double>> images;
vector<double> labels;
int ReverseInt(int i);
void read_Mnist_Label(std::string filename, std::vector<double>& labels);
void read_Mnist_Images(std::string filename, std::vector<std::vector<double>>& images);
void Normalization(vector<vector<double>>& batch);
void Try(int epoch,int batch_size,int lr,int mon);
int main()
{
	double lr = 0.001;
	double mon = 0.98;
	int epoch = 20;
	int batch_size =20;

	srand(time(0));
    read_Mnist_Images(t10k_images, images);
	read_Mnist_Label(t10k_labels, labels);
	Try(epoch,batch_size,lr,mon);
}

void Try(int epoch,int batch_size,int lr,int mon)
{
	vector<vector<double>> batch;
	vector<int> label;
	Dataset* train = new Dataset(10000, batch_size);
	train->shuffle();
	train->shuffle();
	int hidden=64;
	int output = 10;
	int round = (10000/batch_size)+1;
	dense* L1 = new dense(784,hidden, batch_size);
	dense* L2 = new dense(hidden,output,batch_size);
	
	softmax_loss* activation = new softmax_loss(10,batch_size);

	Mon* opt1 = new Mon(lr,mon);
	Mon* opt2 = new Mon(lr,mon);
	vector<double> temp;
	std::vector<mat*> P;std::vector<mat*> G;
	for(int i=0;i<epoch;i++)
	{
		printf("****************EPOCH %d**************...\n",i);
		double acc=0;
		for(int r = 0;r<round;r++)
		{
			/*get a batch and tranform it into matrix*/
			train->load_batch();
			for (int i = 0; i < batch_size; i++)
			{
				int idx = *(train->batch_idx + i);
				temp.assign(images[idx].begin(), images[idx].end());
				batch.push_back(temp);
				temp.clear();
				label.push_back(labels[idx]);
			}
			Normalization(batch);

			/*forward propagation*/
			mat* batchs = new mat(batch);
			//printf("batch size:");batchs->Printsize();
			
			L1->forward(batchs);
			mat* out1 = L1->out;
		
			L2->forward(out1);
			mat* out2 = L2->out;
	
			activation->forward(out2,label);

		
			/*backwad propagtion*/
			mat* back1 =activation->backward(label);
			
			acc+=activation->accuracy(label);
			
			mat* back2 = L2->backward(back1);
			
			mat* back3 = L1->backward(back2);

			/*updata paramaters */
			
			
			/*这里有可能不会更新原来的地址*/
			//printf("before update");//L1->PrintMem(1);
			L1->GetPara(P,G);
			opt1->update(P,G);
			//printf("main L1 P[0]:");P[0]->Printsize();
			//printf("main L1 P[1]:");P[1]->Printsize();
			L1->PushPara(P);

			L2->GetPara(P,G);
			opt2->update(P,G);
			L2->PushPara(P);
			//printf("main L2 P[0]:");P[0]->Printsize();
			//printf("main L2 P[1]:");P[1]->Printsize();
			batch.clear();
			label.clear();
			delete batchs;
			delete out1;
			delete out2;
			delete back1;
			delete back2;
			delete back3;
			P.clear();
			G.clear();	
		}
		printf("in EPOCH correct sample: %lf\n",acc);
	}
}
int ReverseInt(int i)
{
	unsigned char ch1, ch2, ch3, ch4;
	ch1 = i & 255;
	ch2 = (i >> 8) & 255;
	ch3 = (i >> 16) & 255;
	ch4 = (i >> 24) & 255;
	return((int)ch1 << 24) + ((int)ch2 << 16) + ((int)ch3 << 8) + ch4;
}

void read_Mnist_Label(std::string filename, std::vector<double>& labels)
{
	ifstream file(filename, ios::binary);
	if (file.is_open())
	{
		int magic_number = 0;
		int number_of_images = 0;
		file.read((char*)&magic_number, sizeof(magic_number));
		file.read((char*)&number_of_images, sizeof(number_of_images));
		magic_number = ReverseInt(magic_number);
		number_of_images = ReverseInt(number_of_images);
		cout << "magic number = " << magic_number << endl;
		cout << "number of images = " << number_of_images << endl;


		for (int i = 0; i < number_of_images; i++)
		{
			unsigned char label = 0;
			file.read((char*)&label, sizeof(label));
			labels.push_back((double)label);
		}

	}
	else printf("unable to open file of labels\n");
}

void read_Mnist_Images(string filename, vector<vector<double>>& images)
{
	ifstream file(filename, ios::binary);
	if (file.is_open())
	{
		int magic_number = 0;
		int number_of_images = 0;
		int n_rows = 0;
		int n_cols = 0;
		//unsigned char label;
		file.read((char*)&magic_number, sizeof(magic_number));
		file.read((char*)&number_of_images, sizeof(number_of_images));
		file.read((char*)&n_rows, sizeof(n_rows));
		file.read((char*)&n_cols, sizeof(n_cols));
		magic_number = ReverseInt(magic_number);
		number_of_images = ReverseInt(number_of_images);
		n_rows = ReverseInt(n_rows);
		n_cols = ReverseInt(n_cols);

		cout << "magic number = " << magic_number << endl;
		cout << "number of images = " << number_of_images << endl;
		cout << "rows = " << n_rows << endl;
		cout << "cols = " << n_cols << endl;

		for (int i = 0; i < number_of_images; i++)
		{
			vector<double>tp;
			for (int r = 0; r < n_rows; r++)
			{
				for (int c = 0; c < n_cols; c++)
				{
					unsigned char image = 0;
					file.read((char*)&image, sizeof(image));
					tp.push_back(image);
				}
			}
			images.push_back(tp);
		}
	}
}
void Normalization(vector<vector<double>>& batch)
{
	int line = batch.size();
	int col = batch[0].size();
	int maxm = 255;
	for(int i=0;i<line;i++)
	{
		for(int j=0;j<col;j++)
		{
			batch[i][j]/=maxm;
		}
	}
	return;
}
