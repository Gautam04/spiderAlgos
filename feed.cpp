#include<iostream>
#include<fstream>
#include<string>
using namespace std;

struct match
{
	char t1[5];
	char t2[5];
};

int main()
{
	fstream f;
	f.open("schedule.dat",ios::out|ios::binary);
	for(int i=0;i<56;++i)
	{
		match m;
		cout<<"Enter the teams\n";
		cin>>m.t1;
		cin>>m.t2;
		f.write((char*)&m,sizeof(m));
	}
	f.close();
}