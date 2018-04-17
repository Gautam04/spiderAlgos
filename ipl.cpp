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
	map<string,team> teams;
	string teamNames[]={"CSK","MI","KKR","RCB","DD","KXIP","SRH","RR"};
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
	/*while(true)
	{

	}*/
}