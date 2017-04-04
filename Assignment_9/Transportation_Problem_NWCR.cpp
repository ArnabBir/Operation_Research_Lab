#include<iostream>
#include<iomanip>
#include<algorithm>
#define MAX 100

using namespace std;

int m, n;
int s[MAX], d[MAX];
double mat[MAX][MAX];
int val[MAX][MAX] = {0};

void TransportOptimize(){

	for(int i =0; i < m; ++i){
		for(int j = 0; j < n; ++j){
			if(s[i] == 0 || d[j] == 0)	continue;
			int temp = min(s[i], d[j]);
			cout<<s[i]<<"\t"<<d[j]<<"\t"<<temp<<endl;
			val[i][j] = temp;
			s[i] -= temp;
			d[j] -= temp;
		}		
	}
}

double getCost(){
	
	double cost = 0;
	for(int i =0; i < m; ++i){
		for(int j = 0; j < n; ++j){
			cost += mat[i][j] * val[i][j];
		}
	}

	return cost;
}

int main(){
	cout<<"Enter the number of Sources:"<<endl;
	cin>>m;
	cout<<"Enter the number of Destinations:"<<endl;
	cin>>n;
	cout<<"Enter the supply matrix:"<<endl;
	for(int i = 0; i < m; ++i){
		for(int j = 0; j < n; ++j){
			cin>>mat[i][j];
		}
	}

	cout<<"Enter the value of availibilities:"<<endl;
	for(int i = 0; i < m; ++i){
		cin>>s[i];
	}

	cout<<"Enter the value of demands:"<<endl;

	for(int i = 0; i < n; ++i){
		cin>>d[i];
	}	

	TransportOptimize();
	cout<<"Total cost in NCWR method:\t"<<getCost()<<endl;

	return 0;
}
