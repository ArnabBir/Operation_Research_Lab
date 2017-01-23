#include<stdio.h>
#include<math.h>
#include<stdlib.h>

int combos[100][10];
int count;

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

int main(){
	int i, j, n, m, choice, maxindex;
	double maximum, summation;
	printf("Enter the dimension of the matrix (m x n):\n");
	scanf("%d%d", &m, &n);

 	long long int solCount = nCr(n, m);

	printf("Enter the matrix : \n");
	double a[m][n];
	for(i = 0; i < m; ++i)
		for(j = 0; j < n; ++j)
			scanf("%lf", &a[i][j]);

        printf("Enter the values of B : \n");
        double b[m];
	for(i = 0; i < m; ++i)
		scanf("%lf", &b[i]);

	count = 0;
	int indices[n];
	for(i = 0; i < n; ++i)	indices[i] = i;

	getCombination(indices, n, m);

	if(count != solCount) printf("Error : All combinations not found!\n");

	double * x[solCount];

	count = 0;

	int isDegenerate[solCount];
	int isFeasible[solCount];
	for(j = 0; j < solCount; ++j){
		x[j] = gaussElimination(m, n, a, b, j);
		if(x[j] == NULL){
			isFeasible[j] = 0; 
			isDegenerate[j] = -1;
			continue;
		}
		isDegenerate[j] = 0;
        for(i = 0; i < m; ++i){
        	if(x[j][i] == 0){
        		isDegenerate[j] = 1;
        		break;
        	} 
        }
        isFeasible[j] = 1;
        for(i = 0; i < n; ++i){
        	if(x[j][i] < 0){
        		isFeasible[j] = 0;
        		break;
        	}
        }
        ++count;
	}
	printf("Total number of basic soultions = %d\n\n", count);
	do{
		printf("Enter your choice:\n\n1. Degenerate Basic Solutions:\n2. Nondegenerate Basic Solutions:\n3. Basic Feasible Solutions:\n4. Extreme points:\n5. End\n\n");
		scanf("%d", &choice);
		switch(choice){
			case 1:
				count = 0;
				for(j = 0; j < solCount; ++j){
					if(isDegenerate[j]){
						printf("Solution %d:\n", ++count);
						for(i = 0; i < n; ++i){
							printf("x_%d = %lf\t", i+1, x[j][i] );
						}
						printf("\n");
					}
				}
				break;
			case 2:
				count = 0;
				for(j = 0; j < solCount; ++j){
					if(!isDegenerate[j]){
						printf("Solution %d:\n", ++count);
						for(i = 0; i < n; ++i){
							printf("x_%d = %lf\t", i+1, x[j][i] );
						}
						printf("\n");
					}
				}
				break;
			case 3:
				count = 0;
				for(j = 0; j < solCount; ++j){
					if(isFeasible[j]){
						printf("Solution %d:\n", ++count);
						for(i = 0; i < n; ++i){
							printf("x_%d = %lf\t", i+1, x[j][i] );
						}
						printf("\n");
					}
				}
				break;
			case 4:
				count = 0;
				for(j = 0; j < solCount; ++j){
					if(isFeasible[j]){
						printf("Point %d:\n", ++count);
						printf("(");
						for(i = 0; i < n; ++i){
							printf("\t%lf", x[j][i] );
						}
						printf(")");
						printf("\n");
					}
				}
				break;
			case 5:
				break;
			default:
				printf("Wrong input... Try again.");
		}
	}while(choice != 5);
	printf("LPP:\n\nEnter the coefficeients of the objective function:\n");
	double c[n];
	for(i = 0; i < n; ++i)	scanf("%lf", &c[i]);
	maximum = 0;
	maxindex = -1;
	for(j = 0; j < solCount; ++j){
		if(isFeasible[j]){
			summation = 0;
			for(i = 0; i < n; ++i){
				summation += c[i] * x[j][i];
			}
			if(summation > maximum){
				maximum = summation;
				maxindex = j;
			}
		}
	}
	if(maxindex == -1)	printf("No optimal solution\n");
	else{
		printf("Maximum value:\t%lf\n", maximum);
		printf("Point:\n");
		printf("(");
		for(i = 0; i < n; ++i){
			printf("\t%lf", x[maxindex][i]);
		}
		printf(")");
		printf("\n");
	}

	return 0;
}
