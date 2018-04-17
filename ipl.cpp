#include<iostream>
#include<bits/stdc++.h>
#include<string>
using namespace std;
#define numTeams 8


struct team
{
	string name;
	float rr;
	int scored;
	int against;
	int points;
	int wins;
	int loss;
};

struct match
{
	char team1[5];
	char team2[5];
};


int main()
{
	map<string,team> teams;
	
	char teamNames[][5]={"CSK","MI","KKR","RCB","DD","KXIP","SRH","RR"};
	for(int i=0;i<numTeams;++i)
	{
		team temp;
		temp.rr=0;
		temp.scored=0;
		temp.against=0;
		temp.points=0;
		temp.wins=0;
		temp.loss=0;
		teams[teamNames[i]]=temp;
	}
	fstream f;
	f.open("schedule.dat",ios::binary|ios::in);
	while(!f.eof())
	{
		match m;
		f.read((char*)&m,sizeof(m));
		cout<<m.team
		cout<<endl;
	}
	f.close();
	
}