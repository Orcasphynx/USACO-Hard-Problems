#include<bits/stdc++.h>
using namespace std;

//Problem name: Contaminated Milk
//Link: https://usaco.org/index.php?page=viewproblem2&cpid=569

int main(){
	//file stuff
	freopen("badmilk.in",  "r", stdin);
	freopen("badmilk.out", "w", stdout);
	
	//N: number of people
	//M: number of types of milk
	//D: number of entries for people drinking milk
	//S: number of entries for people getting sick
	int N, M, D, S;
	cin >> N >> M >> D >> S;
	
	//I will create a map to contain for each of the M types of milk 
	//a map of with keys being the # of a person who drunk the milk and with values beign the time that person drunk it
	//if a person drunk a type of milk several times I will use the earliest time
	map<int, map<int, int> > party;
	//iterator
	map<int, map<int, int> >::iterator itr;
	
	for(int i = 0; i < D; i++){
		int person, milk, time;
		cin >> person >> milk >> time;
		if(party.count(milk) == 0){
			map<int, int> newMap;
			newMap.insert({person, time});
			party.insert({milk, newMap});
		}
		else{
			if(party[milk].count(person) == 0){
				party[milk].insert({person, time});
			}
			else if(party[milk][person] > time){
				party[milk][person] = time;
			}
		}
	}	
	
	
	//now I will see if each of the milks could be the culpurit
	//if not, I erase them
	for(int i = 0; i < S; i++){
		int person, time;
		cin >> person >> time;
		vector<int> needToRemove;
		for(itr = party.begin(); itr != party.end(); itr++){
			if(itr->second.count(person) == 0){
				needToRemove.push_back(itr->first);
			}
			//"strictly earlier"
			else if(itr->second[person] >= time){
				needToRemove.push_back(itr->first);
			}
		}
		for(int j = 0; j < needToRemove.size(); j++){
			party.erase(needToRemove[j]);
		}
		
	}
	
	//now, I return the size of the largest map of a people who drunk a certain type of milk
	int max = 0;
	for(itr = party.begin(); itr != party.end(); itr++){
		if(max < itr->second.size()){
			max = itr->second.size();
		}
	}
	
	cout << max;
	
	
}

