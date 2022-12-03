#include<vector>
#include<iostream>
using namespace std;
int main()
{
    vector<int> s;
    cout<<s.size()<<endl;
    for(int i=0;i<10;i++)
    s.push_back(i);
    cout<<s.size()<<endl;
    s.clear();
    cout<<s.size()<<endl;
}