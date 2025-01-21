#include<bits/stdc++.h>
using namespace std;

//Problem Name: Sleeping in Class
//Link: https://usaco.org/index.php?page=viewproblem2&cpid=1203

int main(){
	//getting number of test cases
	int T;
	cin >> T;
	
	//looping through test cases
	for(int a = 0; a < T; a++){
		//getting number of perioids
		int N;
		cin >> N;
		
		//recording data and summation of data
		vector<int> log;
		int sum = 0;
		for(int b = 0; b < N; b++){
			int record;
			cin >> record;
			sum += record;
			log.push_back(record);
		}
		
		//number of modifications
		int mod;
		
		//the algorithm works by seeing which least number of modifications work as follows:
		//if an integer average of the sum /(the original size - the number of modifications) is not possible, it will skip checking that number of modifications
		//it will then see if it can make a log with all the numbers being that average given you can only combine two consecutive logs
		//it will continue adding values from left to right with the accumulator "comb" until comb is == average or > average;
		//if == average, it sets comb to 0 (we need to start seeing if we can make a new occurence of the average rather than focusing on the one we already can make)
		//if > average, it breaks the loop (we can't make the occurence of the average)
		//if the system reaches the end of the loop, we can produce the ideal log with that number of modifications, so we return it as it is the minimum number required
		for(mod = 0; mod < N; mod++){
			//makes algorithm more efficient by checking this
			if(sum%(N-mod) == 0){
				int average = sum/(N-mod);
				bool possible = false;
				int comb = 0;
				for(int c = 0; c < log.size(); c++){
					if(comb < average){
						comb+= log[c];	
					}
					if(comb == average){
						comb = 0;
					}
					if(comb > average){
						break;
					}
					if(c == log.size()-1) possible = true;
				}
				if(possible) break;
			} 
		}
		
		//returning data
		cout << mod << endl;
	}
}
