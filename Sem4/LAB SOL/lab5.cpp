/*
	Name : Kshitij Agrawal
	Roll.no : 17EC10063	
	Date : 05/02/19
	PC : 28
	Topic : DP Algorithms
*/

#include<iostream>
#include<stdlib.h>
using namespace std;

bool realizable(int *a,int n,int t)
{
	int s = 0,i,j,k;
	for(i = 0;i < n;i++)
	{
		s += a[i];
	}
	int **dp = (int**)malloc((n + 1) * sizeof(int*));
	for(i=0;i<=n;i++)
	{
		dp[i] = (int *)malloc((2*s + 1)*sizeof(int));
		for(j=0;j<=2*s;j++)
			dp[i][j] = 0;
	}
	t += s;
	dp[0][s] = 1;	//Correponds to sum = 0, as the sum is shifted by +s
	for(i=1;i<=n;i++)
	{
		for(j=0;j<=2*s;j++)
		{
			if(dp[i - 1][j])
			{
				dp[i][j - a[i - 1]] = 1;
				dp[i][j + a[i - 1]] = 1;
			}
		}
	}
/*	for(i=0;i<=n;i++)
	{
		for(j=0;j<=2*s;j++)
			cout << dp[i][j] << ' ';
		cout << '\n';
	}
*/	
	cout << "+++ Part 1: Realizability check\n";
	if(dp[n][t] == 1)
		cout << "\tThe value " << t - s << " is realizable\n";
	else
		cout << "\tThe value " << t - s << " is not realizable\n";
	bool f = dp[n][t];
	for(i=0;i<n;i++)
		free(dp[i]);
	free(dp);
	return f;
}

void showone(int *a,int n,int t)
{
	int s = 0,i,j,k;
	for(i = 0;i < n;i++)
	{
		s += a[i];
	}
	int **dp = (int**)malloc((n + 1) * sizeof(int*));
	for(i=0;i<=n;i++)
	{
		dp[i] = (int *)malloc((2*s + 1)*sizeof(int));
		for(j=0;j<=2*s;j++)
			dp[i][j] = 0;
	}
	t += s;
	dp[0][s] = 1;	//Correponds to sum = 0, as the sum is shifted by +s
	for(i=1;i<=n;i++)
	{
		for(j=0;j<=2*s;j++)
		{
			if(dp[i - 1][j])
			{
				dp[i][j - a[i - 1]] = 1;
				dp[i][j + a[i - 1]] = 1;
			}
		}
	}
	cout << "+++ Part 2: One solution\n";
	if(dp[n][t] == 0)
	{
		cout << "\tThe value " << t - s << " is not realizable\n";
		return;
	}
	i = n;
	j = t;
	cout << "\tSolution:";
	while(i > 0 && j >= 0)
	{
		if(j - a[i - 1] >= 0)
		{
			if(dp[i - 1][j + a[i - 1]]){
				cout << " - " << a[i - 1];
				j += a[i - 1];
			}
			else
			{
				cout << " + " << a[i - 1];
				j -= a[i - 1];
			}
		}
		else
		{
			cout << " - " << a[i - 1];
			j += a[i - 1];
		}
		i--;
	}
	cout << " = " << t - s << '\n';
}

void print(int **dp,int *a,int i,int t,int *p,int *q,int n,int f,int *c)
{
	if(i == 0)//Array formed print it
	{
		(*c)++;
		cout << "Solution " << *c << " : ";
		for(int j = 0;j < n;j++)
		{
			if(p[j] > 0)
			{
				cout << " + ";
				cout << p[j] << ' ';
			}
			else
			{
				cout << " - ";
				cout << q[j] << ' ';
			}
		}
		cout << " = " << f;
		cout << '\n';
		return;		
	}
	if(t - a[i - 1] >= 0)
	{
		//if(t + a[i - 1] <= 2*f)
		if(dp[i - 1][t + a[i - 1]])
		{
			q[i - 1] = a[i - 1];
			p[i - 1] = 0;
			print(dp,a,i - 1,t + a[i -1],p,q,n,f,c);
		}
		if(dp[i - 1][t - a[i - 1]])
		{
			p[i - 1] = a[i - 1];
			q[i - 1] = 0;
			print(dp,a,i - 1,t - a[i -1],p,q,n,f,c);
		}
	}
	else
	{
		if(dp[i - 1][t + a[i - 1]])
		{
			p[i - 1] = a[i - 1];
			q[i - 1] = 0;
			print(dp,a,i - 1,t + a[i -1],p,q,n,f,c);
		}
	}
}
void showall(int *a,int n,int t)
{
	int s = 0,i,j,k;
	for(i = 0;i < n;i++)
	{
		s += a[i];
	}
	int **dp = (int**)malloc((n + 1) * sizeof(int*));
	int *plus = (int*)malloc(n * sizeof(int));
	int *minus = (int*)malloc(n * sizeof(int));	
	for(i=0;i<=n;i++)
	{
		dp[i] = (int *)malloc((2*s + 1)*sizeof(int));
		for(j=0;j<=2*s;j++)
			dp[i][j] = 0;
	}
	t += s;
	dp[0][s] = 1;
	for(i=1;i<=n;i++)
	{
		for(j=0;j<=2*s;j++)
		{
			if(dp[i - 1][j])
			{
				dp[i][j - a[i - 1]] = 1;
				dp[i][j + a[i - 1]] = 1;
			}
		}
	}
	int c = 0;
	cout << "+++ Part 3: All solutions\n";
	if(dp[n][t])
		print(dp,a,n,t,plus,minus,n,t - s,&c);
	else
		cout << "\tThe value " << t - s << " is not realizable\n";
}
int main(int argc, char const *argv[])
{
	int n,i,j,t;
	cout << "n = ";
	cin >> n;
	cout << "The input array:\n";
	int *a = (int*)malloc(n*sizeof(int));
	for(i=0;i<n;i++)
		cin >> a[i];
	cout << "Target = ";
	cin >> t;
	bool f = realizable(a,n,t);
	showone(a,n,t);
	showall(a,n,t);
	return 0;
}


/*

81 78 38 32 78 68 30 53 54 81 76 30 97 3 70 94 64 49 66 71

*/