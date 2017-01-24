#include<stdio.h>
#include<math.h>

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

double * gaussSeidel( int m, int n, double a[m][n], double b[m], double er, int itr){
	int key, i, j;
	double x0[n], sum;
	double * x = (double *) malloc(n * sizeof(double));
	double M[m][m];
	double N[m];
	for(i = 0; i < n; ++i){
			x0[i] = 0;
			x[i] = 0;
	}

	for(i = 0; i < m; ++i){
		N[i] = b[i];
		for(j = 0; j < m; ++j){
			M[i][j] = a[i][combos[itr][j]];
		}
	}

    makeDominant(m, M, N);

	do{
		key = 0;

		for(i = 0; i < m; ++i){
			sum = N[i];
			for(j = 0; j < m; ++j)
				if(j != i)
					sum -= M[i][j] * x0[combos[itr][j]];

			x[combos[itr][i]] = sum / M[i][i];
			if(fabs((x[combos[itr][i]] - x0[combos[itr][i]]) / x[combos[itr][i]]) > er){
				key = 1;
				x0[combos[itr][i]] = x[combos[itr][i]];
			}
		}

	}while(key == 1);

	return x;
}

int main(){
	
	int i, j, n, m, choice, maxindex;
	double maximum, summation;

	printf("Enter the number of inequations (m):\n");
	scanf("%d", &m);
	
	printf("Enter the number of variables (n):\n");
	scanf("%d", &n);

 	long long int solCount = nCr(n, m);

	double a[m][n+m];
	double b[m];
	
	printf("Enter the Inequations : \n");
	for(i = 0; i < m; ++i){
		for(j = 0; j < n; ++j)
			scanf("%lf", &a[i][j]);
		for(j = n; j < n+m; ++j){
			if((j-n) == i){
				a[i][j] = 1;
			}
			else{
				a[i][j] = 0;
			}
		}
	}
		
    printf("Enter the values of RHS : \n");

	for(i = 0; i < m; ++i)
		scanf("%lf", &b[i]);

	printf("LPP:\n\nEnter the coefficeients of the objective function:\n");
	double c[n];
	for(i = 0; i < n; ++i)	scanf("%lf", &c[i]);	
	
	return 0;
}
