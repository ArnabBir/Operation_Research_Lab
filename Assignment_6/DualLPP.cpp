#include <iostream>
#include <cstdlib>
#include <cmath>
using namespace std;

double mat[100][100], temp[100][100], b[100];
int table_no = 0;
bool unbounded = false, infinite = false;
int basic[100];
int m, n;

int colMin(){
	double currMin = 0;
	int index = -1;
	for(int i = 0; i < m; ++i){
		if(mat[i][n+m] > 0)	continue; 
		if(mat[i][n+m] < currMin){
			currMin = mat[i][n+m];
			index = i;
		}
	}
	return index;
}

int rowMin(int pivotRow){
	int index = -1;
	int currMin = 9999999;
	for(int j = 0; j < n+m; ++j){
		if(mat[m][j] == 0)	continue;
		if(mat[pivotRow][j] == 0)	continue;
		if(abs(mat[m][j] / mat[pivotRow][j])  < currMin){
			currMin = abs(mat[m][j] / mat[pivotRow][j]);
			index = j;
		}
	}
	return index;
}

void DualOptimize(){
	cout<<"----------------------------------------------"<<endl;
	cout<<"Table No:\t"<<table_no++<<endl;
	for(int i = 0; i <= m; ++i){
		for(int j = 0; j <= n+m; ++j){
			cout<<mat[i][j]<<"\t";
		}
		cout<<endl;
	}
	cout<<"----------------------------------------------"<<endl;

	int pivotCol, pivotRow;
	while((pivotRow = colMin()) != -1){
		if((pivotCol = rowMin( pivotRow)) == -1){
			unbounded = true;
			return;
		}
		int swap_pos = basic[pivotCol];
		basic[pivotCol] = basic[pivotRow+n];
		basic[pivotRow+n] = swap_pos;
		for(int i = 0; i <= m; ++i){
			for(int j = 0; j <= n+m; ++j){
				if(i == pivotRow && j == pivotCol){
					temp[i][j] = 1;
				}
				else if(j == pivotCol){
					temp[i][j] = 0;
				}
				else if(i == pivotRow){
					temp[i][j] = mat[i][j] / mat[pivotRow][pivotCol];
				}
				else{
					temp[i][j] = mat[i][j] - mat[pivotRow][j] / mat[pivotRow][pivotCol] * mat[i][pivotCol];
				}
			}
		}

		cout<<"----------------------------------------------"<<endl;
		cout<<"Table No:\t"<<table_no++<<endl;
		for(int i = 0; i <= m; ++i){
			for(int j = 0; j <= n+m; ++j){
				mat[i][j] = temp[i][j];
				cout<<mat[i][j]<<"\t";
			}
			cout<<endl;
		}
		cout<<"----------------------------------------------"<<endl;
	}
}

int main(){
	bool isMax;
	int choice;
	cout<<"Enter 1. Max or 2. Min"<<endl;
	cin>>choice;
	if(choice == 1)	isMax = true;
	else isMax = false;

	int type[m];
	cout<< "Enter the values of m and n :"<<endl;
	cin>>m>>n;
	for(int i = 0; i < m; ++i){
		cout<<"Enter the sign of the inequations in the correct order:"<<endl;
		cout<<"1.\t>=\n2.\t=\n3.\t<=\n"<<endl;
		cin>>type[i];
	}
	
	for(int i = 0; i < m; ++i){
		cout<<"Enter ..."<<endl;
		for(int j = 0; j < n; ++j){
			cin>>mat[i][j];
		}
		cin>>mat[i][n+m];
	}
	for(int i = 0; i < m; ++i){
		if(type[i] == 1){
			for(int j = 0; j < n; ++j){
				mat[i][j] *= -1.0;
			}
			mat[i][n+m] *= -1.0;
		}
	}


	for(int i = 0; i < m; ++i){
		mat[i][n+i] = 1;
	}
	cout<<"Enter O.B. Func:\n"<<endl;
	for(int j = 0; j < n; ++j){
		cin>>mat[m][j];
		mat[m][j] *= -1;
	}
	cin>>mat[m][n+m];

	if(isMax == false){
		for(int j = 0; j <= n+m; ++j){
			mat[m][j] *= -1;
		}
	}
	for(int j = 0; j < n+m; ++j){
		basic[j] = j + 1;
	}

	DualOptimize();

	if(infinite)	cout<<"infinite solution"<<endl;
	else if(unbounded)	cout<<"unbounded solution"<<endl;
	else{
		double x[n];
		for(int j = 0; j < n; ++j)	x[j] = 0;
		cout<<"Optimal solution:"<<endl;
		for(int i = 0; i < m; ++i){
			x[basic[n + i] - 1] = mat[i][n+m];
		}
		for(int j = 0; j < n+m; ++j){
			cout<<"X_"<<j+1<<" = "<<x[j]<<"\t"<<endl;
		}
		if(isMax == true)	cout<<"Optimal value of Z :"<<mat[m][n+m]<<endl;
		else	cout<<"Optimal value of Z :"<<-mat[m][n+m]<<endl;
	}
	return 0;
}