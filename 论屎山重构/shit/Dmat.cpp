#include<vector>
#include "layer.h"
using namespace std;
int main()
{
 mat* m1 = new mat(2,3,-1);
 mat* m2 = new mat(3,4,-1);
 printf("the first mat:\n");
 m1->PrintMat();
 
 printf("the first mat:\n");
 m2->PrintMat();

 mat* m3 = (*m1)*(*m2);

 printf("the result is \n");
 m3->PrintMat();
printf("reset  \n");
m3->reset(2,4);
m3->PrintMat();
}
