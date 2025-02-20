#include<bits/stdc++.h>
using namespace std;

//Problem name: Bull In A China Shop
//Link: https://usaco.org/index.php?page=viewproblem2&cpid=640

int main(){
	//file stuff
	freopen("bcs.in", "r", stdin);
	freopen("bcs.out", "w", stdout);
	
	//take in N and K
	int N, K;
	
	cin >> N >> K;
	
	//vector to hold original set up
	vector<pair<int, int> > original;
	
	//getting coordinates of setup components ('#')
	for(int i = 0; i < N; i++){
		for(int j = 0; j < N; j++){
			char character;
			cin >> character;
			if(character == '#'){
				pair<int, int> newPair;
				newPair.first = i;
				newPair.second = j;
				original.push_back(newPair);
			}
		}
	}
	
	//vector to hold all the pieces possible
	vector<vector<pair<int, int> > > pieces;
	
	//getting coordinates of all the components of all the pieces
	for(int a = 0; a < K; a++){
		vector<pair<int, int> > onePiece;
		for(int b = 0; b < N; b++){
			for(int c = 0; c < N; c++){
				char character;
				cin >> character;
				if(character == '#'){
					pair<int, int> newPair;
					newPair.first = b;
					newPair.second = c;
					onePiece.push_back(newPair);
				}
			}
		}
		pieces.push_back(onePiece);
	}
	
	//values to hold best pieces
	int important1 = -1;
	int important2 = -1;
	
	//loops through all the binary combinations of pieces
	for(int first = 0; first < K-1; first++){
		for(int second = first + 1; second < K; second++){
			//only check needed to do problem within timelimit
			//checks to see if the total components of the two pieces selected equals the amount of the original's components
			if(pieces[first].size()+pieces[second].size() == original.size()){
				//loops through all possible translations (x and y) of the first piece
				for(int a = -N+1; a <= N-1; a++){
					for(int b = -N+1; b <= N-1; b++){
						
						vector<pair<int, int> > piece1;
						piece1.clear();
						
						for(int i = 0; i < pieces[first].size(); i++){
							pair<int, int> newPair;
							newPair.first = pieces[first][i].first+a;
							newPair.second = pieces[first][i].second+b;
						
							
							piece1.push_back(newPair);
						}
						
						//loops through all possible translations (x and y) of the second piece
						for(int c = -N+1; c <= N-1; c++){
							for(int d = -N+1; d <= N-1; d++){
								
								vector<pair<int,int> > combined;
								combined.clear();
								
								
								
								combined = piece1; 
								
								for(int j = 0; j < pieces[second].size(); j++){
									pair<int, int> newPair;
									newPair.first = pieces[second][j].first+c;
									newPair.second = pieces[second][j].second+d;
									
									combined.push_back(newPair);
								}
					
								
								//notice that I did not check to see if any of the coordinates are invalid or if there are two equal coordinates
								//the program works even though I don't check them (checking them only saves time)
								
								//I need to sort the vector before I can compare it to the original as the second piece might add coordinates to the overall vector in any position
								for(int k = 0; k < combined.size()-1; k++){
									int min_index = k;
									pair<int, int> minimumPair = combined[k];
									for(int l = k+1; l < combined.size(); l++){
										if((minimumPair.first > combined[l].first) || (minimumPair.first == combined[l].first && minimumPair.second > combined[l].second)){
											min_index = l;
											minimumPair = combined[l];
										}
									}
									pair<int, int> temp = combined[k];
									combined[k] = combined[min_index];
									combined[min_index] = temp;
								}
								
								
								//I compare, if valid I set the values I will print to +1 "first" and +1 "second"
								//+1 because 0 in indexes correlates to piece 1
								if(combined == original){
									important1 = first+1;
									important2 = second+1;
								}
							}
						}
					}
				}
			}
		}
	}
	
	cout << important1 << " " << important2;
	
}
