#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int mm;

/* Printing the matrix T */

void printMatrix(float** T,int m,int n){
	int i,j;
	printf("\n");
	for(i=0;i<m;i++){
	    for(j=0;j<n;j++){
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
	for(j=0;j<n;j++){
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
void getCofactor(float **A,float ** temp,int p, int q, int n){
    int i = 0, j = 0,row,col;
    for(row = 0; row < n; row++)
        for(col = 0; col < n; col++){
        	if(row!=p && col!=q){
        		temp[i][j]=A[row][col];j++;
        		if(j==n-1){
        			j=0;i++;
        		}
        	}
        }

}

float determinant(float **A, int n)
{
    float D = 0;
    int sign=1,i;
    if (n == 1)
        return A[0][0];
    float** temp;
    temp=(float**)malloc((n)* sizeof(float*));
    for(i=0;i<n;i++)
        temp[i]=(float*)malloc(n* sizeof(float));
 
     // Iterate for each element of first row
    for (i=0;i<n;i++)
    {
        getCofactor(A,temp,0, i, n);
        D += sign * A[0][i] * determinant(temp, n - 1);
        sign = -sign;
    }
    return D;
}
 
void adjoint(float **A,float **adj,int n)
{
    int sign = 1,i,j;
    if (n == 1){
        adj[0][0] = 1;
        return;
    }
    float** temp;
    temp=(float**)malloc((n)* sizeof(float*));
    for(i=0;i<n;i++)
        temp[i]=(float*)malloc(n* sizeof(float));
 
    // temp is used to store cofactors of A[][]
    for (i=0; i<n; i++)
        for (j=0; j<n; j++)
        {
            getCofactor(A, temp, i, j, n);
            sign = ((i+j)%2==0)? 1: -1;
            adj[j][i] = (sign)*(determinant(temp, n-1));
        }
}
float** inv(float **A,int n)
{
    // Find determinant of A[][]
    int i,j;
    float det = determinant(A, n);
    if (det == 0)
        return NULL;
 
    // Find adjoint
    float** adj;
    adj=(float**)malloc((n)* sizeof(float*));
    for(i=0;i<n;i++)
        adj[i]=(float*)malloc(n* sizeof(float));
    adjoint(A, adj,n);
 	
    // Find Inverse using formula "inverse(A) = adj(A)/det(A)"
 	float** inverse;
 	inverse=(float**)malloc((n)* sizeof(float*));
 	for(i=0;i<n;i++)
 	    inverse[i]=(float*)malloc(n* sizeof(float));
    for (i=0; i<n; i++)
        for (j=0; j<n; j++)
            inverse[i][j] = adj[i][j]/det;
 
    return inverse;
}

float** matmul(float **A,int r1,int c1,float**B,int r2,int c2){
	float** C;
	int i,j,k;
	C=(float**)malloc((r1)* sizeof(float*));
	for(i=0;i<r1;i++)
	    C[i]=(float*)malloc(c2* sizeof(float));
	for (i = 0; i < r1; i++)
	    for (j = 0; j < c2; j++){
	        C[i][j] = 0;
	        for (k = 0; k < r2; k++)
	            C[i][j] += A[i][k]*B[k][j];
	    }
	return C;
}

void revisedsimplex(float** A,float* Z,int m,int n){
	int i,j,ent,dep,*x,*s;
    float min,min2,**B,**T0,**T1,p,**b,**xB,**alpha,**cB,**C,**Y,**P,r,q,**ZC,temp,Sol,temp2,temp3;
	 	/*Initialise B(mxm)*/
 	B=(float**)malloc((m)* sizeof(float*));
 	for(i=0;i<m;i++)
 	    B[i]=(float*)malloc(m* sizeof(float));
 	for(i=0;i<m;i++){
 		for(j=0;j<m;j++){
 			if(i==j)
 				B[i][j]=1;
 			else
 				B[i][j]=0;
 		}
 	}
 	/*Initialise array for tracking x and s*/
 	s=(int*)malloc(m*sizeof(int));
 	for(i=0;i<m;i++)
 		s[i]=-i-1;
 	x=(int*)malloc(n*sizeof(int));
 	for(i=0;i<n;i++)
 		x[i]=(i+1);

	/*Initialise b(mx1),xB(mx1),alpha(mx1),cB(1xm),C(1xn)*/
 	b=(float**)malloc((m)* sizeof(float*));
	for(i=0;i<m;i++){
		b[i]=(float*)malloc(sizeof(float));
	}
	for(i=0;i<m;i++){
		b[i][0]=A[i][n];
	}
 	xB=(float**)malloc((m)* sizeof(float*));
	for(i=0;i<m;i++){
		xB[i]=(float*)malloc(sizeof(float));
	}
 	alpha=(float**)malloc((m)* sizeof(float*));
	for(i=0;i<m;i++){
		alpha[i]=(float*)malloc(sizeof(float));
	}

	cB=(float**)malloc((1)* sizeof(float*));
	cB[0]=(float*)malloc(m*sizeof(float));
	for(i=0;i<m;i++){
		cB[0][i]=0;
	}
	C=(float**)malloc((1)* sizeof(float*));
	C[0]=(float*)malloc(n*sizeof(float));
	for(i=0;i<n;i++){
		C[0][i]=Z[i];
	}
	/*Initialise Y(1xm),P(mxn)*/
	Y=(float**)malloc((1)* sizeof(float*));
	Y[0]=(float*)malloc(m*sizeof(float));

	P=(float**)malloc((m)* sizeof(float*));
	for(i=0;i<m;i++)
	    P[i]=(float*)malloc(n*sizeof(float));
	for(i=0;i<m;i++)
		for(j=0;j<n;j++)
			P[i][j]=A[i][j];
	xB=matmul(inv(B,m),m,m,b,m,1);
	Y=matmul(cB,1,m,inv(B,m),m,m);
	while(1){
	/*Step 1:We find min in the matrix ZC*/
	ent=-1,min=-1,dep=-1,min2=-1;
	for(i=0;i<n;i++){
		q=matmul(Y,1,m,P,m,n)[0][i]-C[0][i];
		if(q<0){
		min2=q;
		ent=i;
		break;}
	}
	for(i=0;i<n;i++){
		q=matmul(Y,1,m,P,m,n)[0][i]-C[0][i];
		if(min2>q){
		min2=q;
		ent=i;
		}
	}
	//if no negatives we stop
	if(ent==-1){
		printf("\n\nOptimum Solution: ");
		for(i=0;i<m;i++)
			if(s[i]>0)
				printf("X%d=%.2f ",s[i],xB[i][0]);
		for(i=0;i<n;i++)
			if(x[i]>0)
				printf("X%d=0.0000 ",x[i]);

			// else
			// 	printf("S%d=%.2f ",-s[i],xB[i][0]);
		printf("\nOptimal Value=%.2f\n",Sol);
		return;
	}



	/*Step2:Now to determine leaving variable */
	
	alpha=matmul(inv(B,m),m,m,P,m,n);
	// printMatrix(alpha,m,n);
	for(i=0;i<m;i++){
		if(alpha[i][ent]>0){
		min=xB[i][0]/alpha[i][ent];
		dep=i;
		break;}
	}
	for(i=0;i<m;i++){
		r=xB[i][0]/alpha[i][ent];
		if(r<min && alpha[i][ent]>0){
			min=r;
			dep=i;
		}
	}

	/*Step3:Getting new B,P,xB*/

	for(i=0;i<m;i++){
		temp=B[i][dep];
		B[i][dep]=P[i][ent];
		P[i][ent]=temp;
	}

	temp2=cB[0][dep];
	cB[0][dep]=C[0][ent];
	C[0][ent]=temp2;

	temp3=x[ent];
	x[ent]=s[dep];
	s[dep]=temp3;

	xB=matmul(inv(B,m),m,m,b,m,1);
	Y=matmul(cB,1,m,inv(B,m),m,m);
	Sol=matmul(cB,1,m,xB,m,1)[0][0];
	}
	
}



void main(){
		int i,j,m,n,in,*flag;
	    float **A,*Z,**T0,**T1,p,*xB,**Y,**P,r;

	    /*Enter m and n*/
	    printf("Enter the number of equations(m) : ");
	    scanf("%d", &m);
	    printf("Enter the number of unknowns(n): ");
	    scanf("%d", &n);
	    // m=2;n=2;
	    // m=3;n=2;

	    /*init A and Enter A*/
	    A=(float**)malloc((m)* sizeof(float*));
	    for(i=0;i<m;i++)
	        A[i]=(float*)malloc((n+1)* sizeof(float));
	    printf("Enter the augmented matrix A:\n");
	    for(i=0;i<m;i++){
	        for(j=0;j<n+1;j++){
	            scanf("%f",&A[i][j]);
	        }
	    }

	    /* Init Z and Enter Z */
	    Z=(float*)malloc((n+1)*sizeof(float));
	    printf("Enter the coefficients of expression(Z): \n");
	    for(i=0;i<n;i++){
	    	scanf("%f",&Z[i]);
	    }
	    Z[n]=0;
	    // printarr(Z,n);
	 	revisedsimplex(A,Z,m,n);
}