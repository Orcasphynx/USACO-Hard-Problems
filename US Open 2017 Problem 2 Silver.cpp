#include<bits/stdc++.h>
using namespace std;

//Problem Name: Bovine Genomics 
//Link: https://usaco.org/index.php?page=viewproblem2&cpid=739

int main(){
	//file stuff
	freopen("cownomics.in", "r", stdin);
	freopen("cownomics.out", "w", stdout);
	
	//N is the number of vows
	//M is the number of positions in the genome sequences
	int N, M;
	cin >> N >> M;
	
	//I record the data in these 2D arrays
	char spottyCow[N][M];
	char plainCow[N][M];
	
	for(int i = 0; i < N; i++){
		for(int j = 0; j < M; j++){
			cin >> spottyCow[i][j];
		}
	}
	
	for(int i = 0; i < N; i++){
		for(int j = 0; j < M; j++){
			cin >> plainCow[i][j];
		}
	}
	
	//accumilator
	int counter = 0;
	//a, b, and c represent positions
	//I am checking if just looking at a, b, and c is good enough (with the data we have) at guessing which cows are spotty or not
	//In other words, if none of the sequences of characters at positions a, b, and c for spotty cows have been shown to occur in plain cows, then it works
	for(int a = 0; a < M-2; a++){
		for(int b = a+1; b < M-1; b++){
			for(int c = b+1; c < M; c++){
				//boolean
				bool possible = true;
				for(int d = 0; d < N; d++){
					//to make the algorithm more efficient
					bool stillPossible = true;
					for(int e = 0; e < N; e++){
						if(spottyCow[d][a] == plainCow[e][a] && spottyCow[d][b] == plainCow[e][b] && spottyCow[d][c] == plainCow[e][c]){
							possible = false;
							stillPossible = false;
							break;
						}
					}
					if(!stillPossible) break;
				}
				if(possible) counter++;
			}
		}
	}
	
	//outputing data
	cout << counter << endl;
}
