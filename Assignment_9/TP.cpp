#include <iostream>
#include <iomanip>
#define MAX 5
#define m 3 //Number of Sources
#define n 4// Number of Destination
#define FORN(i,n) for(int i=0;i<n;i++)

using namespace std;


float mat[MAX][MAX] = {{7,3,5,5},{5,5,7,6},{8,6,6,5},{6,1,6,4}};
float a[MAX] = {34,15,12,19};
float b[MAX] = {21,25,17,17};

float temp[MAX][MAX], aa[MAX], bb[MAX];

float u[m] = {0}, v[n] = {0};

void copy(){
	// FORN(i, MAX)
	// 	FORN(j,MAX)
	// 		temp[i][j] = mat[i][j];
	FORN(i, MAX)
		aa[i] = a[i];
	FORN(i, MAX)
		bb[i] = b[i];
}

float printTemp(){
	float cost = 0;
    static int no=0;
    // cout<<"Tableau no."<<(++no)<<endl;
     for(int i = 0 ; i <m ; i++){
          for(int j = 0 ; j < n; j++){
          		cost += mat[i][j] * temp[i][j];
               cout << fixed<<setw(7)<<setprecision(1)<<std::setfill(' ') <<mat[i][j]<<"*"<<temp[i][j] << " ";
          }
          cout << endl;
     }
     cout<<endl;
     return cost;
}

bool min_row_col(float row, float col){
	if (row<col) return true;
	else return false;
}

int main(){
	// Using NWCR Method
	copy(); //Copy to temp variable

	int min_row = MAX + 1, min_col = MAX + 1;

	int i = 0;
	int j = 0;
	u[0] = 0;
	v[0] = mat[0][0] - u[0];
	while (i<m && j<n){
		// cout<<"a";
			if (min_row_col(aa[i], bb[j])){
				// Minimum in row
				temp[i][j] = aa[i];
				bb[j] -= aa[i];
				i++;
				u[i] = mat[i][j] - v[j];
			}
			else {
				temp[i][j] = bb[j];
				aa[i] -= bb[j];
				j++;
				v[j] = mat[i][j] - u[i];
			}
		}
    cout<<"Cost : "<<printTemp()<<endl;

    cout<<"\nDuality Test:\n";
    bool optimal = true;
    FORN(i,m){
        FORN(j,n)
            if (u[i] + v[j] <= mat[i][j] ) cout<<"w "; else cout<<"x ", optimal=false;
        cout<<endl;
    }
    cout<<endl;
    if (optimal)
        cout<<"Optimal Solution";
    else
        cout<<"Not optimal Solution";

    cout<<endl;


}
