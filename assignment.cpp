#include <bits/stdc++.h>
using namespace std;

/*
	Class Abhimanyu to simulate fighting of Abhimanyu in Chakravyuha
	properties:
		max_power : starting power or maximum power of Abhimanyu
		current_power : 
		skips : that can be skipped by Abhimanyu
		recharges : number of times Abhimanyu can recharge to its full power
*/

class abhimanyu{
	private:
		int max_power;					
		int current_power;		
		int skips;
		int recharges;		

		/*
			pos : current circle of Abhimanyu
			prev : previous enemy is killed(1) or skipped(0)
			chakravyuha : enemy's power
			dp : to store current state's value to be reused 
		*/
		bool helper(int pos, int prev, vector<int>& chakravyuha, map<vector<int>, int>& dp){
			if(current_power<0){
				return 0;
			}
			if(pos==chakravyuha.size()){
				return 1;
			}
			vector<int> state={pos, current_power, skips, recharges, prev};
			if(dp.find(state)!=dp.end()){
				return dp[state];
			}

			bool ans=false;
			// skipping current enemy if skips are remaining
			if(skips>0){
				skips--;
				ans|=helper(pos+1, 0, chakravyuha, dp);
				skips++;
			}

			//calculating enemy power to battle
			int enemy_power=chakravyuha[pos];
			if(3==pos || 7==pos){
				if(prev){
					enemy_power+=chakravyuha[pos-1]/2;
				}
				else{
					enemy_power+=chakravyuha[pos-1];
				}
			}

			//battle enemy if there is enough power else recharge
			if(current_power>=enemy_power){
				current_power-=enemy_power;
				ans|=helper(pos+1, 1, chakravyuha, dp);
				current_power+=enemy_power;
			}
			else if(recharges>0){
				int initial_power=current_power;
				current_power=max_power;
				recharges--;
				ans|=helper(pos, prev, chakravyuha, dp);
				recharges++;
				current_power=initial_power;
			}

			return dp[state]=ans;
		}				
	
	public:
		abhimanyu(int power, int skips, int recharges){
			this->max_power=power;
			this->current_power=power;
			this->skips=skips;
			this->recharges=recharges;
		}


		bool simulate(vector<int> chakravyuha){                     // simulate abhimanyu's escape to check if he can cross circles
			map<vector<int>, int> dp;
			return helper(0, 1, chakravyuha, dp);
		}
};

int main() {
	int max_power;
	int skips;
	int recharges;	
	vector<int> chakravyuha;
	while(true){
		cout<<"Enter Abhimanyu's power : ";
		cin>>max_power;
		if(max_power<=0){
			cout<<"power needs to be positive constant"<<endl;
			continue;
		}
		break;
	}
	while(true){
		cout<<"Enter how many times Abhimanyu can skip enemy : ";
		cin>>skips;
		if(skips<0){
			cout<<"skips needs to be non negative constant"<<endl;
			continue;
		}
		break;
	}
	while(true){
		cout<<"Enter how many times Abhimanyu can recharge : ";
		cin>>recharges;
		if(recharges<0){
			cout<<"recharges needs to be non negative constant"<<endl;
			continue;
		}
		break;
	}

	cout<<"Enter 11 enemy power at each circle"<<endl;
	for(int i=0;i<11;i++){
		int enemy;
		cin>>enemy;
		chakravyuha.push_back(enemy);
	}

	abhimanyu obj=abhimanyu(max_power, skips, recharges);

	if(obj.simulate(chakravyuha)){
		cout<<"Abhimanyu can cross 11 circles"<<endl;
	}
	else{
		cout<<"Abhimanyu can not cross 11 circles"<<endl;
	}
	
	return 0;
}