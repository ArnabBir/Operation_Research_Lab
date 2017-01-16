#include<stdio.h>
#include<math.h>

int main(){
	int key, i, j, k, n;
	double er, sum;
	printf("Enter the dimension of the matrix :\n");
	scanf("%d", &n);
	
	printf("Enter the stopping Criteria (er) :\n");
	scanf("%lf", &er);

	printf("Enter the matrix : \n");
	double a[n][n];
	for(i = 0; i < n; ++i)
		for(j = 0; j < n; ++j)
			scanf("%lf", &a[i][j]);
	
        printf("Enter the values of B : \n");	
        double b[n];
	for(i = 0; i < n; ++i)
		scanf("%lf", &b[i]);
	
	double x[n];

	double x0[n];
	
	for(i = 0; i < n; ++i)
			x0[i] = 0;
	
	do{
		key = 0;

		for(i = 0; i < n; ++i){
			sum = b[i];
			for(j = 0; j < n; ++j)
				if(j != i)
					sum = sum - a[i][j] * x0[j];
				
			x[i] = sum / a[i][i];
			if(fabs((x[i] - x0[i]) / x[i]) > er){
				key = 1;
				x0[i] = x[i];
			}
		}
 
	}while(key == 1);
	
	printf("Solution:\n\n");
	for(i = 0; i < n; ++i)
		printf("x_%d = %lf\t", i+1, x[i]);
 	printf("\n");
	return 0;
}

