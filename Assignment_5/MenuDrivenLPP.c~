#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

#define MValue 1000000

double mat[100][100], b[100], temp[100][100];
int basic[100];
int ieq_type[100];
int m, n;
int unbounded = 0;
int infinite = 0;
int table_no = 0;
int slack = 0, surplus = 0, artificial = 0;
int combos[100][10];
int count;
int key;
long long int solCount;
double * xg[100];

long long int nCr(int n, int r){
	int i;
	long long int result = 1;
	if(r > n/2) r = n - r;
	for(i = 1; i <= r; ++i){
		result *= (n-i+1);
		result /= i;
	}
	return result;
}

int transformToDominant(int m, int r, double M[m][m], double N[m], int V[], int R[])
    {
    	int i, j;
        int n = m;
        if (r == m)
        {
            double T[n][n+1];
            double P[n];
            for (i = 0; i < n; i++)
            {
            	P[i] = N[R[i]];
                for (j = 0; j < n; j++)
                    T[i][j] = M[R[i]][j];
            }

            for (i = 0; i < n; i++)
            {
            	N[i] = P[i];
                for (j = 0; j < n; j++)
                    M[i][j] = T[i][j];
            }

            return 1;
        }

        for (i = 0; i < n; i++)
        {
            if (V[i]) continue;

            double sum = 0;

            for (j = 0; j < n; j++)
                sum += fabs(M[i][j]);

            if (2 * fabs(M[i][r]) >= sum)
            {
                V[i] = 1;
                R[r] = i;

                if (transformToDominant(m, r + 1, M, N, V, R))
                    return 1;

                V[i] = 0;
            }
        }

        return 0;
}

int makeDominant(int m, double M[m][m], double N[m])
{
    int i;
    int visited[m];
    for(i = 0; i < m; ++i) visited[i] = 0;
    int rows[m];
    return transformToDominant(m, 0, M, N, visited, rows);
}

double * gaussElimination(int m, int n, double a[m][n], double b[m], int itr){
	int i, j, k;
	double ratio;
	double M[m][m];
    double * N = (double *) malloc(n * sizeof(double));

    for(i = 0; i < n; ++i)  N[i] = 0;

	for(i = 0; i < m; ++i){
		N[combos[itr][i]] = b[i];
		for(j = 0; j < m; ++j){
			M[i][j] = a[i][combos[itr][j]];
		}
	}

	makeDominant(m, M, N);

	for(i = 0; i < m-1; ++i){
		for(j = i + 1; j < m; ++j){
			ratio = M[j][i] / M[i][i];
			N[combos[itr][j]] -= N[combos[itr][i]] * ratio;
			for(k = i; k < m; ++k){
				M[j][k] -= M[i][k] * ratio;
			}
		}
	}

	for(i = m-1; i > 0; --i){
		for(j = i - 1; j >= 0; --j){
			ratio = M[j][i] / M[i][i];
			N[combos[itr][j]] -= N[combos[itr][i]] * ratio;
			M[j][i] = 0;
			//printf("M[%d][%d] = %lf\n", i, j, M[i][j]);
		}
	}

	for(i = 0; i < m; ++i){
		if(!M[i][i]){
			printf("No Solution\n");
			return NULL;
		}
		N[combos[itr][i]] /= M[i][i];
		M[i][i] = 1;
	}

	return N;
}

void concatCombination(int arr[], int data[], int start, int end,
                     int index, int r)
{
    int i, j;
    if (index == r){
    	for(j = 0; j < r; ++j){
    		combos[count][j] = data[j];
 		}
    	++count;
    	return;
    }

    for (i = start; i <= end && end-i+1 >= r-index; ++i)
    {
        data[index] = arr[i];
        concatCombination(arr, data, i+1, end, index+1, r);
    }
}

void getCombination(int arr[], int n, int r)
{
    int data[r];
    concatCombination(arr, data, 0, n-1, 0, r);
}

int rowMin(){
    int i;
    int index = -1;
    float currMin = 0;
    for(i = 0 ; i < n ; i++){
          if(mat[m][i] > 0)	continue;
          /*if(mat[m][i] == 0){
               infinite = 1;
               return -1;
          }
          */
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
    table_no = 0;
    if(key == 5){
		printf("------------------------------------------------------\n");
		printf("Table %d:\n", table_no);
		for(i = 0 ; i <= m ; i++){
			for(j = 0 ; j <= n; j++){
				printf("%lf\t", mat[i][j]);
			}
		printf("\n");
		}
		printf("------------------------------------------------------\n");
	}
	++table_no;
	int pivotRow, pivotCol, swap_pos;
	while((pivotCol = rowMin()) != -1){
		if((pivotRow = getPivotRow(pivotCol)) == -1){
			unbounded = 1;
			return;
		}
		swap_pos = basic[pivotCol];
		basic[pivotCol] = basic[n-m+pivotRow];
		basic[n-m+pivotRow] = swap_pos;
		for(i = 0 ; i <= m ; i++){
			for(j = 0 ; j <= n; j++){
				if(i == pivotRow && j == pivotCol)
					temp[i][j] = 1;
				else if(i == pivotRow)
					temp[i][j] = (mat[i][j])/mat[pivotRow][pivotCol];
				else if(j == pivotCol)
					temp[i][j] = 0;
				else{
					temp[i][j] = mat[i][j] - mat[pivotRow][j] / mat[pivotRow][pivotCol] * mat[i][pivotCol];
				}
			}
		}


			if(key == 5)	printf("-----------------------------------------------------\n");
			if(key == 5)	printf("Table %d:\n\n", table_no++);
			for(i = 0 ; i <=m ; i++){
				for(j = 0 ; j <= n; j++){
					mat[i][j] = temp[i][j];
					if(key == 5)	printf("%lf\t", mat[i][j]);
				}
				if(key == 5)	printf("\n");
			}
			if(key == 5)	printf("-----------------------------------------------------\n");
			if(key == 4){
				printf("Basic Variables:\nIteration %d:\n\n", table_no++);
				for(i = 0; i < m; ++i)
					printf("x_%d = %lf\t", basic[n-m + i], mat[i][n]);
			}
			if(key == 3){
				printf("Non Basic Variables:\nIteration %d:\n\n", table_no++);
				for(i = 0; i < m; ++i)
					printf("x_%d\t", basic[i]);
			}
	}
}

int main(){
	int i, j;
	int type;
	double factor;
	int inequality;
	printf("Enter the type of the problem:\n1.	Maximization\n2.	Minimization\n\n");
	scanf("%d", &type);
	switch(type){
		case 1:
			factor = 1.0;
			break;
		case 2:
			factor = -1.0;
			break;
		default:
			printf("Wrong input!\n");
	}

	printf("Enter the number of inequations (m):\n");
	scanf("%d", &m);

	printf("Enter the number of variables (n):\n");
	scanf("%d", &n);
	//getchar();
	for(i = 0; i < m; ++i){
		printf("Enter the sign of inequality of %d th inequation:\n", i+1);
		printf("1 -> less than or equal to (<=)\n");
		printf("2 -> equal to (=)\n");
		printf("3 -> greater than or equal to (>=)\n");
		scanf("%d", &inequality);
		printf("%d\n", inequality);
		if(inequality == 1){
			ieq_type[i] = -1;
			++slack;
		}
		else if(inequality == 2){
			ieq_type[i] = 0;
			++artificial;
		}
		else if(inequality == 3){
			ieq_type[i] = 1;
			++surplus;
			++artificial;
		}
	}

	for(i = 0 ; i < m ; i++){
		printf("Enter coefficients and constant term of inequation no %d:\n" , i+1);
		for(j = 0 ; j < n ; j++){
			scanf("%lf",&mat[i][j]);
		}

		scanf("%lf", &mat[i][m+n+surplus]);
	}
	for(i = 0; i < m; ++i)	mat[i][n+surplus+i] = 1;
	int negcoeff = 0;
	for(i = 0; i < m; ++i){
		if(ieq_type[i] == 1){
			mat[i][n + negcoeff++] = -1;
		}
	}

	printf("Enter coefficients of the %d variables in the objective function Z followed by the constant:\n", n);
	printf("If there is no constant, enter 0 as the constant value.\n");
	for(j = 0; j < n ; j++){
		scanf("%lf", &mat[m][j]);
		if(j != n)
			mat[m][j] = -factor * mat[m][j];
	}

	for(i = 0; i < surplus; ++i)	mat[m][n+i] = 0;
	for(i = 0; i < m; ++i){
		mat[m][n+surplus+i] = 0;
		if(ieq_type[i] == 0 || ieq_type[i] == 1)	mat[m][n+surplus+i] = MValue;
	}

	//n += m + surplus;
	scanf("%lf", &mat[m][n]);

	for(i = 0; i < n; ++i){
		basic[i] = i+1;
	}

	int indices[n];
	double a[m][n];
	double b[m];
	do{
		printf("(1) List of all BFS\n(2)No. of iterations to solve the problem\n(3) List of all nonbasic variables along with net evaluation in ith iteration\n");
		printf("(4) List of all basic variables along with min ratios in ith iteration\n(5) Simplex table of ith iteration\n (6) Optimal Soution\n(7) End\n\n");
		printf("Select an option\n");
		scanf("%d", &key);
		switch(key){
			case 1:
				solCount = nCr(n, m);
				for(i = 0; i < m; ++i)
					for(j = 0; j < n; ++j)
						a[i][j] = mat[i][j];
        			for(i = 0; i < m; ++i)
					b[i] = mat[i][n+m+surplus];
				count = 0;
				for(i = 0; i < n; ++i)	indices[i] = i;
				getCombination(indices, n, m);
				for(j = 0; j < solCount; ++j)
					xg[j] = gaussElimination(m, n, a, b, j);
				printf("Total number of basic soultions = %d\n\n", count);
				count = 0;
				for(j = 0; j < solCount; ++j){
					printf("Solution %d:\n", ++count);
					for(i = 0; i < n; ++i){
						printf("x_%d = %lf\t", i+1, xg[j][i] );
					}
					printf("\n");
				}
				break;
			case 2:
				n += m + surplus;
				Simplex_Optimisation();
				printf("Number of iterations:\t%d\n", table_no);
				n-= m + surplus;
				break;
			case 3:
				n += m + surplus;
				Simplex_Optimisation();
				n-= m + surplus;
				break;
			case 4:
				n += m + surplus;
				Simplex_Optimisation();
				n-= m + surplus;
				break;
			case 5:
				n += m + surplus;
				Simplex_Optimisation();
				n-= m + surplus;
				break;
			case 6:
				n += m + surplus;
				Simplex_Optimisation();
				if(infinite)	printf("There are infinitely many solutions\n");
				else if(unbounded)	printf("The problem is unbounded\n");
				else{
					double x[n];
					for(i = 0; i < n; ++i)	x[i] = 0;
					int index = 0;
					printf("Optimal Solution:\n");
					for(i = 0; i < m; ++i){
						//printf("x_%d* = %lf\t", basic[n-m + i], mat[i][n]);
						x[basic[n-m + i] - 1] = mat[i][n];
					}
					for(i = 0; i < n; ++i)	printf("x_%d = %lf\t", i+1, x[i]);
					printf("\nThe optimal value of Z is %lf \n", factor*mat[m][n]);
				}
				n-= m + surplus;
		}
	}while(key != 7);

	printf("------------------------------------------------------\n");

	return 0;
}
