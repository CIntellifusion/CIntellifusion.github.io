#include "layer.h"
#include<vector>
#include<iostream>
#include<fstream>
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
int main()
{
    read_Mnist_Images(t10k_images, images);
	read_Mnist_Label(t10k_labels, labels);
	int batch_size = 8;
	Dataset* train = new Dataset(22, batch_size);
	train->PrintIdx(); printf("\n");

	train->shuffle();
	train->shuffle();
	train->load_batch();
	printf("the first batch\n");
	train->PrintIdx(); printf("\n");
	for (int i = 0; i < batch_size; i++)
	{
		printf("%d ", train->batch_idx[i]);
	}
	printf("\n");
	printf("the second batch\n");
	train->PrintIdx(); printf("\n");
	train->load_batch();
	for (int i = 0; i < batch_size; i++)
	{
		printf("%d ", train->batch_idx[i]);
	}
	printf("\n");
	printf("the third batch\n");
	train->load_batch();
	train->PrintIdx(); printf("\n");
	for (int i = 0; i < batch_size; i++)
	{
		printf("%d ", train->batch_idx[i]);
	}
	printf("\n");
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


