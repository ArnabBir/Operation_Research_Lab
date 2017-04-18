#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define M 10000
int mm;
int iter1=1,iter2=1;
	/* Returns the index of the most negative element*/
int neg(float** T,int m,int n){
	int i,in1=-2;
	float mostneg=1;
	for(i=0;i<n;i++){
		if(T[m][i]<=0){
			mostneg=T[m][i];
			in1=i;
			break;
		}
	}
	for(i=0;i<n;i++){
		if(mostneg>T[m][i] && mostneg!=1){
			mostneg=T[m][i];
			in1=i;
		}
	}
	return in1;
}
int neg1(float** T,int m,int n,int* x){
	int i,in1=-2;
	float mostneg=1;
	for(i=0;i<n;i++){
		if(T[m][i]<=0 && x[i]!=0){
			mostneg=T[m][i];
			in1=i;
			break;
		}
	}
	for(i=0;i<n;i++){
		if(mostneg>T[m][i] && mostneg!=1&& x[i]!=0){
			mostneg=T[m][i];
			in1=i;
		}
	}
	return in1;
}
/* Taking the index of pivot element of the Simplex Tableau taking care of unbounded case */
int pivot(float** T,int m,int n){
	int i,j,pl=-1,count=0;float piv1,q=0,p;
	int in1=neg(T,m,n);
	for(i=0;i<m;i++){
		if(T[i][in1]>0){
			piv1=T[i][n]/T[i][in1];
			pl=i;
			break;
		}
	}
	for(i=0;i<m;i++){
		if(T[i][in1]>0){
			q=T[i][n]/T[i][in1];
			if(piv1>q){
			piv1=q;
			pl=i;
			}
		}
	}
	return pl;
}

int pivot1(float** T,int m,int n,int*x){
	int i,j,pl=-1,count=0;float piv1,q=0,p;
	int in1=neg1(T,m,n,x);
	for(i=0;i<m;i++){
		if(T[i][in1]>0){
			piv1=T[i][n]/T[i][in1];
			pl=i;
			break;
		}
	}
	for(i=0;i<m;i++){
		if(T[i][in1]>0){
			q=T[i][n]/T[i][in1];
			if(piv1>q){
			piv1=q;
			pl=i;
			}
		}
	}
	return pl;
}
/*Printing the matrix T*/
void printMatrix(float** T,int m,int n){
	int i,j;
	for(i=0;i<m+1;i++){
	    for(j=0;j<n+1;j++){
	    	if(T[i][j]>=0){
	    		if(T[i][j]==-0.0)
	    			T[i][j]=0;
	        	printf(" %.2f ",T[i][j]);
	    	}
	        else
	        	printf("%.2f ",T[i][j]);
	    }
	    printf("\n");
	}
	printf("\n");

}
void printarr(float* T,int n){
	int i,j;
	for(j=0;j<n+1;j++){
    	if(T[j]>=0){
    		if(T[j]==-0.0)
    			T[j]=0.0;
        	printf(" %.2f ",T[j]);
    	}
        else
        	printf("%.2f ",T[j]);
    
	}
	printf("\n");

}
void printBFS(float** T1,int m,int n1,int* x,int* z){
	int i;
	printf("Basic Feasible Solutions :");
	for(i=0;i<n1;i++){
		if(x[i]>0)
			printf("X%d=0.0000 ",x[i]);
	}
	for(i=0;i<m;i++){
		if(z[i]>0)
			printf("X%d=%.4f ",z[i],T1[i][n1]);
	}
	printf("\n");
}

void printsol(float** T1,int m,int n1,int n,int* x,int* z){//Printing the Solution
	int i;
	printf("Optimum Solution: ");
	for(i=0;i<n1;i++){
		if(x[i]>0 && x[i]<=n)
			printf("X%d=0.0000 ",x[i]);
	}
	for(i=0;i<m;i++){
		if(z[i]>0 && z[i]<=n)
			printf("X%d=%.4f ",z[i],T1[i][n1]);
	}
	if(mm==1)
    	printf("\nOptimum Value: %.4f\n\n",T1[m][n1]);
    else
    	printf("\nOptimum Value: %.4f\n\n",-T1[m][n1]);

}
float** simplex(float** T0,float*Z,int m,int n1,int n,int *x,int* z0){
	/*Variable Declaration and Initialisation pl=pivot location row p=pivot element	*/
	int pl,in1,i,j,temp,m0=0;;
	float **T1,**S0,p,*s;
	int f=0;
	printf("\nPHASE-1:Initial Simplex Tableau:\n");
	printMatrix(T0,m+1,n1);

	/*Initializing T1*/
	T1=(float**)malloc((m+2)* sizeof(float*));
	for(i=0;i<m+2;i++)
	    T1[i]=(float*)malloc((n1+1)* sizeof(float));

	S0=(float**)malloc((m+2)* sizeof(float*));
	for(i=0;i<m+2;i++)
	    S0[i]=(float*)malloc((n1+1)* sizeof(float));
	/*Simplex*/
	while(1){
	pl=0,in1=0;
	in1=neg(T0,m,n1);
	if(in1==-2){
		printf("Not Feasible\n");
		return NULL;
	}
	pl=pivot(T0,m,n1);

	if(pl==-1){
		printf("Solution is Unbounded!\n");
		return NULL;
	}
	if(fabs(T0[m][in1])<=0.0005){
		for(i=0;i<m+2;i++)
			for(j=0;j<n1+1;j++){
				if(x[j]==0 &j!=n1)
					S0[i][j]=0;
				else
					S0[i][j]=T0[i][j];
			}
		printf("All artificial variables are zero.\nPHASE-1:Final Simplex Tableau:\n");
		printMatrix(S0,m+1,n1);
		printf("Final Solution is %.2f",S0[m][n1]);
		return S0;
	}
    for(i=0;i<m+2;i++)
    	for(j=0;j<n1+1;j++)
    		T1[i][j]=T0[i][j];
	
    temp=x[in1];
    x[in1]=z0[pl];
    z0[pl]=temp;
	p=T0[pl][in1];
    for(i=0;i<m+2;i++){
    	for(j=0;j<n1+1;j++){
    		T1[pl][j]=T0[pl][j]/p;
    		if(j!=in1)
    			T1[i][in1]=-(T0[i][in1]/p);
    		else
    			T1[pl][j]=(1/p);
    	}
    }
    for(i=0;i<m+2;i++)
    	for(j=0;j<n1+1;j++)
    		if(i!=pl && j!=in1)
    			T1[i][j]=T0[i][j]-(T0[i][in1]*T0[pl][j])/p;

    for(i=0;i<m+2;i++)
    	for(j=0;j<n1+1;j++)
    		T0[i][j]=T1[i][j];
    printf("Iteration Number: %d\n",iter1 );
    printBFS(T1,m,n1,x,z0);
    printf("Objective Value is: %.2f\n\n",T1[m][n1] );
    iter1++;

	}
}
float** tpsimplex(float** T0,int m,int n1,int n,int * x,int *z0){
	int pl,in1,i,j,temp,ct;
	float **T1,p,*s;
	int f=0;
	printf("\nPHASE-2:Initial Simplex Tableau:\n");
	printMatrix(T0,m,n1);

	/*Initializing T1*/
	T1=(float**)malloc((m+1)* sizeof(float*));
	for(i=0;i<m+1;i++)
	    T1[i]=(float*)malloc((n1+1)* sizeof(float));

	/*Simplex*/
	while(1){
	pl=0,in1=0;
	in1=neg1(T0,m,n1,x);
	if(in1==-2){
		printf("PHASE-2:Final Simplex Tableau:\n");
	    printMatrix(T0,m,n1);
	    printsol(T0,m,n1,n,x,z0);
		return T0;
	}
	pl=pivot1(T0,m,n1,x);
	if(pl==-1&& x[in1]!=0){
		printf("Solution is Unbounded!\n");
		return NULL;
	}
	if(fabs(T0[m][in1])<=0.005){
		if(f==0){
			printf("Alternate Solution exists!\n");
			printf("PHASE-2:Final Simplex Tableau:\n");
		    printMatrix(T0,m,n1);
			printsol(T0,m,n1,n,x,z0);
		}
		if(f==1){
			printf("PHASE-2 Final Simplex Tableau:\n");
		    printMatrix(T0,m,n1);
			printsol(T0,m,n1,n,x,z0);
			// printf("Final Solution is %.2f",T0[m][n1]);
			return T0;
		}
		f++;
	}
    for(i=0;i<m+1;i++)
    	for(j=0;j<n1+1;j++)
    		T1[i][j]=T0[i][j];
	
    temp=x[in1];
    x[in1]=z0[pl];
    z0[pl]=temp;
	p=T0[pl][in1];
    for(i=0;i<m+1;i++){
    	for(j=0;j<n1+1;j++){
    		T1[pl][j]=T0[pl][j]/p;
    		if(j!=in1)
    			T1[i][in1]=-(T0[i][in1]/p);
    		else
    			T1[pl][j]=(1/p);
    	}
    }
    for(i=0;i<m+1;i++)
    	for(j=0;j<n1+1;j++)
    		if(i!=pl && j!=in1)
    			T1[i][j]=T0[i][j]-(T0[i][in1]*T0[pl][j])/p;

    for(i=0;i<m+1;i++)
    	for(j=0;j<n1+1;j++)
    		T0[i][j]=T1[i][j];

    printf("Iteration Number: %d\n",iter2 );
    printBFS(T1,m,n1,x,z0);
    printf("Objective Value is: %.2f\n\n",T1[m][n1] );
    iter2++;

	}
}
void main(){
	int i,j,m,n,n1,in1=0,pl=0,*flag,ct,k=0;
    float **T0,**A,*Z,*F,p,*s,**S0,**S1;
    static int *x,*z0;
    printf("Enter the number of equations(m) : ");
    scanf("%d", &m);
    printf("Enter the number of unknowns(n): ");
    scanf("%d", &n);
    n1=n;ct=n;
    A=(float**)malloc((m)* sizeof(float*));
    for(i=0;i<m;i++)
        A[i]=(float*)malloc((n+1)* sizeof(float));
    printf("Enter the augmented matrix A:\n");
    for(i=0;i<m;i++){
        for(j=0;j<n+1;j++){
            scanf("%f",&A[i][j]);
        }
    }

    flag=(int*)malloc(m*sizeof(int));
    printf("Enter: 1 if >=, 0 if '==', -1 if <= one by one:\n");
    for(i=0;i<m;i++){
    	scanf("%d",&flag[i]);
    	if(flag[i]==1)
    		n1+=1;
    }
    Z=(float*)malloc((n1+1)*sizeof(float));
    printf("Enter the coefficients of expression(Z): \n");
    for(i=0;i<n;i++)
    	scanf("%f",&Z[i]);
    for(i=n;i<n1+1;i++)
		Z[i]=0;

    s=(float*)malloc((n1+1)*sizeof(float));
    for(i=0;i<n1+1;i++)
    	s[i]=0;

 	printf("Enter 1 for Maximize and 0 for Minimize Z: \n");
 	scanf("%d",&mm);

 	/* Making Initial Simplex Tableau */
	T0=(float**)malloc((m+2)* sizeof(float*));
	for(i=0;i<m+2;i++){
	    T0[i]=(float*)malloc((n1+1)* sizeof(float));
	    for(j=0;j<n1+1;j++)
	    	T0[i][j]=0;
	}
	for(i=0;i<m;i++){
	    for(j=0;j<n;j++){
	        T0[i][j]=A[i][j];
	    }
    	if(flag[i]==1){
        	T0[i][ct]=-1;
        	ct++;
        	continue;
    	}
	}
	for(i=0;i<m;i++){
	    T0[i][n1]=A[i][n];

	}
	for(i=0;i<n1+1;i++){
		for(j=0;j<m;j++){
			if(flag[j]>=0)
				s[i]+=T0[j][i];
			}
	}
	for(j=0;j<n1+1;j++){
		if(mm==1)
			T0[m][j]=-s[j];}

	for(j=0;j<n1+1;j++){
		if(mm==1)
			T0[m+1][j]=-Z[j];

	}
	/* Initialising x and z*/
	z0=(int*)malloc(m*sizeof(int));
	for(i=0;i<m;i++)
		if(flag[i]>=0)
			z0[i]=0;
		else
			z0[i]=-i-1;
	x=(int*)malloc(n1*sizeof(int));
	for(i=0;i<n1;i++)
		x[i]=(i+1);

	/*Initialising for Next Phase*/
 	S0=(float**)malloc((m+1)* sizeof(float*));
 	for(i=0;i<m+1;i++){
 	    S0[i]=(float*)malloc((n1+1)* sizeof(float));
 	}

 	S1=(float**)malloc((m+2)* sizeof(float*));
 	for(i=0;i<m+2;i++){
 	    S1[i]=(float*)malloc((n1+1)* sizeof(float));
 	}
	S1=simplex(T0,Z,m,n1,n,x,z0);
	for(i=0;i<m+2;i++){
		if(i!=m){
		S0[k]=S1[i];
		k++;}
	}
	printf("\n................................\n");
	tpsimplex(S0,m,n1,n,x,z0);
	printf("\n................................\n");
}
