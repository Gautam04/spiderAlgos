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
	string team1;
	string team2;
	int score1;
	int score2;
	float overs1;
	float overs2;
	bool rainAffected;
};


int main()
{
	string teamNames[]={"CSK","MI","KKR","RCB","DD","KXIP","SRH","RR"};
	team teams[numTeams];
	for(int i=0;i<numTeams;++i)
	{
		teams[i].name = teamNames[i];
		teams[i].rr=0;
		teams[i].scored=0;
		teams[i].against=0;
		teams[i].points=0;
		teams[i].wins=0;
		teams[i].loss=0;
	}
}