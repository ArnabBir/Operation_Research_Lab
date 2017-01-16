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

double * gaussSeidel( int m, int n, double a[m][n], double b[m], double er, int itr){
	int key, i, j;
		double x0[n], sum;
	double * x = (double *) malloc(n * sizeof(double));

	for(i = 0; i < n; ++i){
			x0[i] = 0;
			x[i] = 0;
	}

//	for(i = 0; i < m; ++i){
//		if(!a[i][combos[itr][i]]) return x;
//	}


	do{
		key = 0;

		for(i = 0; i < m; ++i){
			sum = b[i];
			for(j = 0; j < m; ++j)
				if(j != i)
					sum -= a[i][combos[itr][j]] * x0[combos[itr][j]];

			x[combos[itr][i]] = sum / a[i][combos[itr][i]];
			if(fabs((x[combos[itr][i]] - x0[combos[itr][i]]) / x[combos[itr][i]]) > er){
				key = 1;
				x0[combos[itr][i]] = x[combos[itr][i]];
			}
		}

	}while(key == 1);

	return x;
}

void concatCombination(int arr[], int data[], int start, int end,
                     int index, int r)
{
    int i, j;
    if (index == r){
    	for(j = 0; j < r; ++j){
    		//printf("%d\t", data[j]);
    		combos[count][j] = data[j];
 		}
 		printf("\n");
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
	int i, j, n, m;
	double er;

	printf("Enter the dimension of the matrix (m x n):\n");
	scanf("%d%d", &m, &n);

 	long long int solCount = nCr(n, m);
	/*
	combos = (int **)malloc( solCount * sizeof(int *));
    for (i=0; i<m; i++)
         combos[i] = (int *)malloc(m * sizeof(int));
*/
	printf("Enter the stopping Criteria (er) :\n");
	scanf("%lf", &er);

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
	//for(i = 0; i < n; ++i)	printf("%d", indices[i]);
	getCombination(indices, n, m);
/*
    for(i = 0; i < solCount; ++i){
        for(j = 0; j < m; ++j)
            printf("%d\t", combos[i][j]);
        printf("\n");
    }
    */

	if(count != solCount) printf("Error : All combinations not found!\n");

	double * x[solCount];

	printf("Solutions:\n");

	for(j = 0; j < solCount; ++j){
		printf("j = %d", j);
		x[j] = gaussSeidel(m, n, a, b, er, j);
        for(i = 0; i < n; ++i)
            printf("x_%d = %lf\t", i, x[j][i]);
        printf("\n");
	}

	return 0;
}
