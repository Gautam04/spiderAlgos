#include<iostream>
#include<bits/stdc++.h>
#include<string>
using namespace std;
#define numTeams 8
#define V 38
#define MAX 100000
#define pii pair <int,int>
#define pip pair <pii,int>

int numMatches=56;

struct team
{
	int id;
	string name;
	float rr;
	int scored;
	int against;
	int points;
	int wins;
	int left;
	int loss;
	float oversPlayed;
	float oversAgainst;
	map<string,int> remaining;
};

map<string,team> teams;
char teamNames[][5]={"CSK","MI","KKR","RCB","DD","KXIP","SRH","RR"};
map<string,int> matches;
bool qualify[numTeams];


struct match
{
	char team1[5];
	char team2[5];
};


bool cmp(team a,team b)
{
	return a.wins>b.wins;
}

bool BFS(vector<vector<int> > residualCapacity, int parent[], int source, int sink)
{
    //BFS for maxFlow
    int n = residualCapacity.size();
    bool visited[n];//= {};
    fill_n(visited, n, false);
    queue<int> Q;
    Q.push(source);
    visited[source]=true;
    bool foundPath=false;
    while(!Q.empty())
    {
        int current = Q.front();
        Q.pop();
        for( int v=0; v< n; v++)
        {
            int cost = residualCapacity[current][v];
            if(!visited[v] && cost>0)
            {
                parent[v]=current;
                visited[v]=true;
                Q.push(v);
                if(v==sink)
                {
                    foundPath=true;
                    break;
                }
            }
        }
    }
    return foundPath;
}

int maxFlow(vector<pip> capacity, int source, int sink, int n)
{
    int x = capacity.size();
    vector<vector<int> > residualCapacity (n, (vector<int> (n,0) ));
    for (int i = 0; i < x; i++)
    {
        int from = capacity[i].first.first;
        int to = capacity[i].first.second;
        int cap = capacity[i].second;
        residualCapacity[from][to] += cap;
    }


    int parent[n];
    //list<list<int> > augmentedPaths;
    int maxFlow=0;
    while(BFS(residualCapacity, parent, source, sink))
    {
        //list<int> augmentedPath;
        int flow = MAX;
        int v = sink;

        while(v!=source)
        {
            //augmentedPath.push_back(v);
            int u = parent[v];
            if(flow > residualCapacity[u][v])
                flow = residualCapacity[u][v];
            v=u;
        }
        //augmentedPath.push_back(source);
        //augmentedPath.reverse();
        //augmentedPaths.push_back(augmentedPath);
        maxFlow += flow;

        v=sink;
        while(v!=source)
        {
            int u = parent[v];
            residualCapacity[u][v] -= flow;
            //residualCapacity[v][u] -= flow;
            v=u;
        }
    }
    return maxFlow;
}

bool flow(string t)
{
	vector<team> temp;
	vector<pip> edges;
	vector<vector<int> > residual; 
	int i,src,dest,gameNode;
	map<string,int> vertex;
	int maxWins = teams[t].wins + teams[t].left;
	for(i=0;i<numTeams;++i)
	{
		vertex[teamNames[i]]=i;
	}
	src=i;
	dest=i+1;
	gameNode=i+2;
	for(int j=0;j<numTeams;++j)
		temp.push_back(teams[teamNames[j]]);
		
	sort(temp.begin(),temp.end(),cmp);
	if(maxWins<temp[3].wins)
	{
		return false;
	}
	//residual[src][gameNode]=numMatches;
	for(int j=0;j<numTeams;++j)
	{
		for(int k=j+1;k<numTeams;++k)
		{
			/*residual[src][gameNode]=teams[teamNames[i]].remaining[teamNames[j]];
			residual[gameNode][vertex[teamNames[j]]]=1000;
			residual[gameNode][vertex[teamNames[k]]]=1000;*/
			edges.push_back(pip(pii(src,gameNode),teams[teamNames[j]].remaining[teamNames[k]]));
			edges.push_back(pip(pii(gameNode,vertex[teamNames[j]]),1000));
			edges.push_back(pip(pii(gameNode,vertex[teamNames[k]]),1000));
			gameNode++;			
		}
	}
	for(i=0;i<numTeams;i++)
	{
		//residual[vertex[teamNames[i]]][dest]=maxWins - teams[teamNames[i]].wins;
		edges.push_back(pip(pii(vertex[teamNames[i]],dest),maxWins-teams[teamNames[i]].wins));
	}
	int currentCap = maxFlow(edges, src, dest, gameNode);
	return currentCap>=numMatches;

	
}


int main()
{
	for(int i=0;i<numTeams;++i)
	{
		team temp;
		temp.id=i+1;
		temp.name=teamNames[i];
		temp.rr=0;
		temp.scored=0;
		temp.left=14;
		temp.against=0;
		temp.points=0;
		temp.wins=0;
		temp.loss=0;
		temp.oversPlayed=0;
		temp.oversAgainst=0;
		for(int j=0;j<numTeams;++j)
		{
			if(teamNames[j]==teamNames[i])
			{
				temp.remaining[teamNames[j]]=0;
			}
			else
			temp.remaining[teamNames[j]]=2;

			
		}
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
		teams[t2].remaining[t1]-=1;
		teams[t1].remaining[t2]-=1;
		teams[t1].left--;
		teams[t2].left--;
		numMatches--;
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
		cout<<endl<<"Matches remainig between the two teams : "<<teams[t1].remaining[t2];
		numMatches--;
		
		
		for(int j=0;j<numTeams;++j)
		{
			qualify[j]=flow(teamNames[j]);
		}
		for(int j=0;j<numTeams;++j)
		{
			if(qualify[j])
			cout<<"\nYes";
			else
			cout<<"\nNo";
		}
		
	}
	f.close();
	
}
