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
	float oversPlayed;
	float oversAgainst;
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
		temp.name=teamNames[i];
		temp.rr=0;
		temp.scored=0;
		temp.against=0;
		temp.points=0;
		temp.wins=0;
		temp.loss=0;
		temp.oversPlayed=0;
		temp.oversAgainst=0;
		teams[teamNames[i]]=temp;
	}
	fstream f;
	f.open("schedule.dat",ios::binary|ios::in);
	while(!f.eof())
	{
		match m;
		float overs1,overs2,actualOvers1,actualOvers2;
		int score1,score2;
		string t1,t2;
		f.read((char*)&m,sizeof(m));
		t1=m.team1;
		t2=m.team2;
		cout<<"\nMatch to be played next\n";
		cout<<m.team1<<" v "<<m.team2<<endl;
		cout<<"Enter the runs scored by "<<m.team1<<" and the number of overs it took them\n";
		cin>>score1>>overs1;
		cout<<"Enter the runs scored by "<<m.team2<<" and the number of overs it took them\n";
		cin>>score2>>overs2;
		actualOvers1=overs1+(overs1-(int)overs1)/0.6;
		actualOvers2=overs2+(overs2-(int)overs2)/0.6;
		teams[t1].scored+=score1;
		teams[t2].scored+=score2;
		teams[t1].against+=score2;
		teams[t2].against+=score1;
		teams[t1].oversPlayed+=actualOvers1;
		teams[t2].oversPlayed+=actualOvers2;
		teams[t1].oversAgainst+=20;
		teams[t2].oversAgainst+=20;
		teams[t1].rr=teams[t1].scored/teams[t1].oversPlayed -teams[t1].against/teams[t1].oversAgainst; 
		teams[t2].rr=teams[t2].scored/teams[t2].oversPlayed -teams[t2].against/teams[t2].oversAgainst;
		if(score1>score2)
		{
			teams[t1].wins++;
			teams[t1].points+=2;
			teams[t2].loss++;
		} 
		else
		{
			teams[t2].wins++;
			teams[t2].points+=2;
			teams[t1].loss++;
		}
		cout<<endl<<t1<<"  Points:"<<teams[t1].points<<"   NRR:"<<teams[t1].rr;
		cout<<endl<<t2<<"  Points:"<<teams[t2].points<<"   NRR:"<<teams[t2].rr;

	}
	f.close();
	
}