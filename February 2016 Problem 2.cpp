#include<cmath>
#include<cstdio>
#include<iostream>
#include<vector>
using namespace std;

//Problem Name: Load Balancing
//Link: https://usaco.org/index.php?page=viewproblem2&cpid=619

//Note: this solution should also work for the bronze version of the problem as well with a few changes
int main(){
	//file stuff
	freopen("balancing.in", "r", stdin);
	freopen("balancing.out", "w", stdout);
	
	//inputing number of cows
	int M;
	cin >> M;
	
	//contains all the cows and their locations
	vector<pair<int, int> > cows;
	
	//contains all the x coordinates seperately
	vector<int> xCoordinates;
	//contains all the y coordinates seperately
	vector<int> yCoordinates;
	
	//records data
	for(int i = 0; i < M; i++){
		int x, y;
		cin >> x >> y;
		
		xCoordinates.push_back(x);
		yCoordinates.push_back(y);
		
		pair<int, int> coordinates;
		coordinates.first = x;
		coordinates.second = y;
		
		cows.push_back(coordinates);
	}
	
	//sort x coordinates
	for(int i = 0; i < xCoordinates.size()-1; i++){
		int min_index = i;
		for(int j = i+1; j < xCoordinates.size(); j++){
			if(xCoordinates[min_index] > xCoordinates[j]){
				min_index = j;
			} 
		}
		int temp = xCoordinates[min_index];
		xCoordinates[min_index] = xCoordinates[i];
		xCoordinates[i] = temp;
	}
	
	//sort y coordinates
	for(int i = 0; i < yCoordinates.size()-1; i++){
		int min_index = i;
		for(int j = i+1; j < yCoordinates.size(); j++){
			if(yCoordinates[min_index] > yCoordinates[j]){
				min_index = j;
			} 
		}
		int temp = yCoordinates[min_index];
		yCoordinates[min_index] = yCoordinates[i];
		yCoordinates[i] = temp;
	}
	
	//minimum maximum value the quadrants could have (I set it to some value that won't contest another reasonable value given the problem specifics (no more than a thousand cows)
	int minMax = 2000;
	
	//for any partition after an x valuee
	for(int i = 0; i < xCoordinates.size(); i++){
		int a, b;
		a = xCoordinates[i]+1;
		//for any possible partition after a y value
		for(int j = 0; j < yCoordinates.size(); j++){
			b = yCoordinates[j]+1;
			
			//quadrants
			int quadrants[4];
			quadrants[0] = 0;
			quadrants[1] = 0;
			quadrants[2] = 0;
			quadrants[3] = 0;
			
			//given this partitioning, how many cows would be in each quadratn
			for(int g = 0; g < cows.size(); g++){
				if(a < cows[g].first && b < cows[g].second){
					quadrants[0]++;
				}
				else if(a < cows[g].first && b > cows[g].second){
					quadrants[1]++;
				}
				else if(a > cows[g].first && b < cows[g].second){
					quadrants[2]++;
				}
				else quadrants[3]++;
			}
			
			//finds maximum number of cows in a quadrant
			int max = 0;
			for(int g = 0; g < 4; g++){
				if(quadrants[g] > max){
					max = quadrants[g];
				}
			}
			
			//sees if this is a lower maximum
			if(minMax > max){
				minMax = max;
			}
		}
	}
	
	//prints data
	cout << minMax;
	
}
