#include <stdio.h>
#include <math.h>
#include <string.h>
#include<stdlib.h>

double mat[100][100], b[100], temp[100][100];
int m, n;
int unbounded = 0;
int infinite = 0;
int table_no = 0;
int rowMin(){
    int i;
    int index = -1;
    float currMin = 0;
    for(i = 0 ; i < n ; i++){
          if(mat[m][i] > 0)	continue;
          if(mat[m][i] == 0){
               infinite = 1;
               return -1;
          }
          if(mat[m][i] < currMin){
               currMin = mat[m][i];
               index = i;
         }
    }
    //isBasic[index] = 1;
    //x[index] = matrix[m][index];
    return index;
}

int getPivotRow(int pivotCol){
	int i, index = -1;
	float currMin = 100000;
	for(i = 0 ; i < m; i++){
		if(mat[i][pivotCol] <= 0)	continue;
		if((mat[i][n]/mat[i][pivotCol]) < currMin){
			index = i;
			currMin = (mat[i][n]/mat[i][pivotCol]);
		}
	}
	return index;
}



void Simplex_Optimisation(){
    int i, j;
	printf("------------------------------------------------------\n");
	printf("Table %d:\n", table_no++);
	for(i = 0 ; i <= m ; i++){
		for(j = 0 ; j <= n; j++){
			printf("%lf\t", mat[i][j]);
		}
	printf("\n");
	}
	printf("------------------------------------------------------\n");

	int pivotRow, pivotCol;
	while((pivotCol = rowMin()) != -1){
		if((pivotRow = getPivotRow(pivotCol)) == -1){
			unbounded = 1;
			return;
		}

		for(i = 0 ; i <= m ; i++){
			for(j = 0 ; j <= n; j++){
				if(i == pivotRow && j == pivotCol)
					temp[i][j] = 1 / mat[i][j];
				else if(i == pivotRow)
					temp[i][j] = (mat[i][j])/mat[pivotRow][pivotCol];
				else if(j == pivotCol)
					temp[i][j] = ((-1)*mat[i][j])/mat[pivotRow][pivotCol];
				else{
					temp[i][j] = ((mat[pivotRow][pivotCol]*mat[i][j]) - (mat[pivotRow][j]*mat[i][pivotCol]))/mat[pivotRow][pivotCol];
				}
			}
		}
		printf("-----------------------------------------------------\n");
		printf("Table %d:\n\n", table_no);
		for(i = 0 ; i <=m ; i++){
			for(j = 0 ; j <= n; j++){
				mat[i][j] = temp[i][j];
				printf("%lf\t", mat[i][j]);
			}
			printf("\n");
		}
		printf("-----------------------------------------------------\n");
	}
}

int main(){
	int i, j;
	char inequality[10];

	printf("Enter the number of inequations (m):\n");
	scanf("%d", &m);

	printf("Enter the number of variables (n):\n");
	scanf("%d", &n);
	for(i = 0 ; i < m ; i++){
		printf("Enter coefficients, inequation sign and constant term of equation no %d seperated by spaces:\n" , i + 1);
		for(j = 0 ; j < n ; j++){
			scanf("%lf",&mat[i][j]);
		}
		scanf("%s", inequality);
		if (inequality[0] == '<'){
			scanf("%lf", &mat[i][j]);
		}
	}

	printf("Enter the coefficients of the %d variables in the objective function Z in order followed by the constant d:\n", n);
	for(j = 0; j <= n ; j++){
		scanf("%lf", &mat[m][j]);
		if(j != n)
			mat[m][j] = (-1)*mat[m][j];
	}
	Simplex_Optimisation();

	printf("------------------------------------------------------\n");
	if(infinite)	printf("There are infinitely many solutions\n");
	else if(unbounded)	printf("The problem is unbounded\n");
	else{
		printf("Optimal Solution:\n");
		for(i = 0; i < m; ++i){
			printf("x_%d* = %lf\t", i+1, mat[i][n]);
		}
	}
		printf("\nThe Maximum value of Z is %f \n", mat[m][n]);
	printf("-------------------------------------------------------\n");
	return 0;
}
