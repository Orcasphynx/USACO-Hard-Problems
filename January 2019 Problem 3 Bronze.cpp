#include<bits/stdc++.h>
using namespace std;

//Problem Name: Guess The Animal
//Link: https://usaco.org/index.php?page=viewproblem2&cpid=893

int main(){
	//File stuff
	freopen("guess.in", "r", stdin);
	freopen("guess.out", "w", stdout);
	
	//variable that contains maximum amount of yeses so far
	int yesMax = 0;
	
	//number of animals;
	int N;
	cin >> N;
	
	//animals
	vector<string> animals;
	
	//vectors of characteristics
	vector<string> characteristics[N];
	for(int i = 0; i < N; i++){
		//getting the name of the animal
		string animal;
		cin >> animal;
		
		//recording it
		animals.push_back(animal);
		
		//number of characteristics
		int K;
		cin >> K;
		
		for(int j = 0; j < K; j++){
			//getting characteristic
			string c;
			cin >> c;
			
			characteristics[i].push_back(c);	
		}
	}
	
	//Now it gets interesting
	//They try to trick you by giving you the names of the animals
	//All you need is the characteristics vector (you don't really need to record the animal names)
	
	//maximum number of yeses you can get is equal to the maximum number of characteristics a "secret" animal shares with another animal
	//+1 if the secret animal's list's size is atleast one larger than that number
	
	//characteristic[a] = secret animal's list
	for(int a = 0; a < N; a++){
		//contains max number of characteristics it shares with another animal
		int max = 0;
		//loops through all the other lists
		for(int b = 0; b < N; b++){
			if(a == b){
				continue;
			}
			//sees how many characteristics the lists share
			int counter = 0;
			for(int c = 0; c < characteristics[a].size(); c++){
				for(int d = 0; d < characteristics[b].size(); d++){
					if(characteristics[a][c] == characteristics[b][d]){
						counter++;
						break;
					}
				}
			}
			//maximizes max
			if(max < counter){
				max = counter;
			}
		}
		//if max is less than the size of the secret animal's list, than an additional yes can happen in the game
		if(max < characteristics[a].size()){
			max += 1;
		}
		//maximizes yesMax
		if(yesMax < max){
			yesMax = max;
		}
	}

	
	//record answer
	cout << yesMax;
}
