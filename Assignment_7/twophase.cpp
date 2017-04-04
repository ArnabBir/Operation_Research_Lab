//				Lab3 Code

#include <iostream>
#include <iomanip> 
#include <vector>

using namespace std;

int min_index(float *lastrow, int length)
{
	int index=0;
	for (int i=1; i<length; i++)
	{
		if (lastrow[i]<lastrow[index])
			index=i;
	}
	if (lastrow[index]>=0)
		return -1;
	else
		return index;
}

int min_col_index(float *temp, int length)
{
	int index=0;
	for (int i=1; i<length; i++)
	{
		if (temp[i]<temp[index])
			index=i;
	}
	return index;
}

void print(int n, int m, float **A)
{
	int i, j;
	cout<<"----------------"<<endl;
	for (i=0; i<m; i++){
		for (j=0; j<(n); j++)
			cout<<setw(10)<<setprecision(5)<<A[i][j];
		cout<<endl;
	}
	// cout<<"----------------"<<endl;
}

void simplex(float **activeA, int n, int m, int max_min)
{
	float lastrow[n+1], *temp;
	int i, j, pivot_col=0, pivot_row, count;
	bool stop=true, unbounded=false;

	for (i=0; i<n; i++)
	{
		if (activeA[m][i]<=0)
			stop=false;

	}

	if (stop==true){
		if (max_min==1)
			cout<<endl<<"Optimal Solution is "<<activeA[m][n]<<endl;
		if (max_min==2)
			cout<<endl<<"Optimal Solution is "<<(-1)*activeA[m][n]<<endl;

		for (i=0; i<m; i++)
		{
			if (activeA[i][n+1]<50)
				cout<<"x"<<activeA[i][n+1]<<" is "<<activeA[i][n]<<endl;
		}

		for (i=0; i<n; i++)
		{
			if (activeA[m+2][i]<50)
				cout<<"x"<<activeA[m+2][i]<<" is "<<0<<endl;
		}

		return;
	}

	pivot_col=min_index(activeA[m], n);

	//If the last element corresponding to pivot choosen pivot col is zero, Alternate solution exists.
	if (activeA[m][pivot_col]==0)
	{
		if (max_min==1)
			cout<<endl<<"Alternate Solution Exists. Optimal Solution is "<<activeA[m][n]<<endl;
		if (max_min==2)
			cout<<endl<<"Alternate Solution Exists. Optimal Solution is "<<(-1)*activeA[m][n]<<endl;

		for (i=0; i<m; i++)
		{
			if (activeA[i][n+1]<50)
				cout<<"x"<<activeA[i][n+1]<<" is "<<activeA[i][n]<<endl;
		}

		for (i=0; i<n; i++)
		{
			if (activeA[m+2][i]<50)
				cout<<"x"<<activeA[m+2][i]<<" is "<<0<<endl;
		}

		return;
	}


	//Unboundedness Checking
	count=0;
	for (i=0; i<m; i++)
	{
		if (activeA[i][pivot_col]<=0)
			count++;
	}
	if (count==m){
		cout<<"Solution is Unbounded"<<endl;
		return;
	}

	//creating temp array for choosing pivot_row
	temp=new float [m];
	for (i=0; i<m; i++)
	{
		if (activeA[i][pivot_col]>0)
			temp[i]=activeA[i][n]/activeA[i][pivot_col];
		else
			temp[i]=1000000;
	}
	pivot_row=min_col_index(temp, m);
	cout<<"Row Column"<<pivot_row<<"  "<<pivot_col<<endl;

	float swap;
	swap=activeA[m+2][pivot_col];
	activeA[m+2][pivot_col]=activeA[pivot_row][n+1];
	activeA[pivot_row][n+1]=swap;

	//make new table
	float pivot=activeA[pivot_row][pivot_col];
	for (i=0; i<=m+1; i++)
	{
		for(j=0; j<=n; j++)
		{
			if (i!= pivot_row && j!= pivot_col)
			{
				activeA[i][j]=(activeA[i][j]*activeA[pivot_row][pivot_col]-activeA[pivot_row][j]*activeA[i][pivot_col])/activeA[pivot_row][pivot_col];
			}
		}
	}

	for (i=0; i<=n; i++)
		activeA[pivot_row][i]=activeA[pivot_row][i]/pivot;

	for (i=0; i<=m+1; i++)
		activeA[i][pivot_col]=-activeA[i][pivot_col]/pivot;
	activeA[pivot_row][pivot_col]=1/pivot;
	
	print(n+1, m+1, activeA);

	simplex(activeA, n, m, max_min);
}


int main()
{
	int n, m, i, j, geq, leq, eq, M=1000, max_min;
	float **A, *b, **activeA, *z, temp;

	cout<<"Enter No of Equations : ";
	cin>>m;

	cout<<"Enter No of Unknwons : ";
	cin>>n;

    cout<<"Enter the number of >=, =, <= contraints : "<<endl;
    cin>>geq>>eq>>leq;

    A= new float* [m]; 
    activeA = new float* [m+1+1+1];

    for (i=0; i<m; i++){
        A[i]= new float [n];
        activeA[i]= new float [n+geq+1+1];
    }
    activeA[m]= new float [n+geq+1];
    activeA[m+1]= new float [n+geq+1];
    activeA[m+2]= new float [n+geq+1];

	cout<<"Enter the matrix A in order (e.g first 1) >= 2) = 3) <= ,contraints) : \n";
	for (i=0; i<m; i++){
		for (j=0; j<n; j++){
			cin>>A[i][j];
			activeA[i][j]=A[i][j];
		}
	}

	for (i=0; i<geq; i++)
	{
		for (j=0; j<m; j++){
			if (i==j)
				activeA[j][n+i]=-1;
			else
				activeA[j][n+i]=0;
		}
	}

	cout<<"Enter the column vector 'b' : \n";
    b=new float [m];
	for (i=0; i<m; i++){
		cin>>b[i];
		activeA[i][n+geq]=b[i];
	}

	for (i=0; i<geq+eq; i++)
	{
		for (j=0; j<n+geq+1; j++)
			activeA[m][j]-=activeA[i][j];
	}

	for (i=0; i<n+geq; i++)
	{
		activeA[m+2][i]=i+1;
	}

	for (i=0; i<m; i++)
	{
		activeA[i][n+geq+1]=51+i;
	}

	cout<<"Enter the choice : 1 -- Maximize, 2 -- Minimize"<<endl;
	cin>>max_min;

	cout<<"Enter the objective function z :\n";
	z=new float [n];
	for (i=0; i<n; i++){
		cin>>z[i];
		if (max_min==1)
			activeA[m+1][i]=-z[i];
		if (max_min==2)
			activeA[m+1][i]=z[i];
	}

	print(n+geq+1, m+1, activeA);
	cout<<"Phase I starts"<<endl;
	simplex(activeA, n+geq, m, max_min);

	cout<<"Phase I complete"<<endl;

	for (i=0; i<=n+geq; i++)
		activeA[m][i]=activeA[m+1][i];

	for (i=0; i<n+geq; i++)
	{
		if (activeA[m+2][i]>=50)
		{
			for (j=0; j<m+2; j++)
				activeA[j][i]=0;
		}
	}

	simplex(activeA, n+geq, m, max_min);

	print(n+geq+2, m+3, activeA);
	
	return 0;

}
