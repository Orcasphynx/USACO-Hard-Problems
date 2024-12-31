#include<bits/stdc++.h>
using namespace std;

//Problem Name: Stuck in a Rut
//Link: https://usaco.org/index.php?page=viewproblem2&cpid=1061

int main(){
	//number of cows
	int num;
	cin >> num;
	
	//solution array
	int grass[num];
	
	//first, I organize all the cows into vectors depending on if they are going north or east
	//the most inner pair of integers are the initial coordinates of the cow 
	//the other integer is the index of the cow for the solution
	vector<pair<pair<int, int>, int> > eastCows;
	vector<pair<pair<int, int>, int> > northCows;
	

	for(int i = 0; i < num; i++){
		char direction;
		cin >> direction;
		
		pair<int, int> loc;
		cin >> loc.first;
		cin >> loc.second;
		
		pair<pair<int, int>, int> cow;
		cow.first = loc;
		cow.second = i;
		
		if(direction == 'E'){
			eastCows.push_back(cow);
		}
		else northCows.push_back(cow);
	}
	
	//second I sort the vectors using a selection sort(note that the xs and ys are all unique, which makes this much easier)
	//for the cows going east, I sort the cows from least y-coordinate to highest y-coordinate
	for(int i = 0; i < eastCows.size()-1; i++){
		int min_index = i;
		for(int j = i+1; j < eastCows.size(); j++){
			if(eastCows[min_index].first.second > eastCows[j].first.second){
				min_index = j;
			}
		}
		pair<pair<int, int>, int> temp = eastCows[min_index];
		eastCows[min_index] = eastCows[i];
		eastCows[i] = temp;
	}
	
	//for the cows going north, I sort the cows from least x-coordinate to highest x-coordinate
	for(int i = 0; i < northCows.size()-1; i++){
		int min_index = i;
		for(int j = i+1; j < northCows.size(); j++){
			if(northCows[min_index].first.first > northCows[j].first.first){
				min_index = j;
			}
		}
		pair<pair<int, int>, int> temp = northCows[min_index];
		northCows[min_index] = northCows[i];
		northCows[i] = temp;
	}
	
	//now things get interesting
	//I work through all the cows that go east from least x-coordinate to highest x-coordinate and put the amount of grass they eat into the solution array (if infinity, -1)
	
	//the important thing to remember is that since I am working in to out, I can REMOVE cows from the vectors once I find their solutions
	while(!eastCows.empty()){
		//its best to have the counter variable outside the loop for this instance in case the following loop does not run period
		int j;
		//now I see how this cow going east interacts with the cows going north (I stop the for loop if the cow stops)
		for(j = 0; j < northCows.size();)
		{
			//if the cow going north starts at a higher y-value, I ignore it
			if(northCows[j].first.second > eastCows[0].first.second){
				j++;
			}
			//if the cow going north starts at a lower x-value, I also ignore it
			else if(northCows[j].first.first < eastCows[0].first.first){
				j++;
			}
			//if the cows reach the same patch of land at the same time, I can still continue as per the rules
			else if(abs(eastCows[0].first.second - northCows[j].first.second) == abs(eastCows[0].first.first - northCows[j].first.first)){
				j++;
			}
			//if the distance the cow going east has to go to reach the intersection is longer than the other cow's
			//then the northbound cow blocks the eastbound cow, so I remove the cow going east and break the inner for loop after recording the solution
			else if(abs(eastCows[0].first.second - northCows[j].first.second) < abs(eastCows[0].first.first - northCows[j].first.first)){
				grass[eastCows[0].second] = abs(eastCows[0].first.first - northCows[j].first.first);
				eastCows.erase(eastCows.begin());
				break;
			}
			//if otherwise, then I erase the cow going north, but the loop can continue
			else if(abs(eastCows[0].first.second - northCows[j].first.second) > abs(eastCows[0].first.first - northCows[j].first.first)){
				grass[northCows[j].second] = abs(eastCows[0].first.second - northCows[j].first.second);
				northCows.erase(northCows.begin()+j);
			}
		}
		//if we have gone through all the northbound cows and none of them have blocked the eastbound cow, I assume it continues eating onto enternity
		if(j == northCows.size()){
			grass[eastCows[0].second] = -1;
			eastCows.erase(eastCows.begin());
		}
	}
	
	//any remaining north cows have nothing stopping them from eating forever
	for(int i = 0; i < northCows.size();i++){
		grass[northCows[i].second] = -1;
	}
	
	//now I just print everything out
	for(int i = 0; i < num; i++){
		if(grass[i] == -1){
			cout << "Infinity" << endl;
		}
		else cout << grass[i] << endl;
	}
	
}
